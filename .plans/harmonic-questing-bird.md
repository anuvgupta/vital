# Plan: Reduce Token Costs & Fix Conversation History

## Context
API costs are dominated by input tokens ($10-14/day on Opus). Root causes: JSON preset data leaking into conversation history, sub-action prompts persisting permanently, sound design translations stored as fake "user" messages, router using expensive Opus model, and the 296KB cookbook being sent on every sound design call. This plan fixes all history pollution, switches the router to Sonnet, renames the cookbook file reference, and adds request logging for future analysis.

## Files to Modify
- `src/common/claude_api_client.cpp` (main changes)
- `src/common/claude_api_client.h` (add logging method, add history cleanup method)
- `src/interface/editor_sections/full_interface.cpp` (multi-action cleanup, reroute fix)
- `build_windows.bat` (rename cookbook → SOUND_DESIGN_GUIDE.md)
- `build_macos.sh` (rename cookbook → SOUND_DESIGN_GUIDE.md)
- `build_linux.sh` (rename cookbook → SOUND_DESIGN_GUIDE.md)

## Full history write-point audit
All writes go through `addMessage()`. Every call site:
1. `claude_api_client.cpp:311` — user messages in `sendMessagesAsync` (truncated to 1024 chars) — **OK**
2. `claude_api_client.cpp:460` — assistant responses in `sendMessagesAsync` — **BUG: JSON leaks** (Change 1)
3. `full_interface.cpp:1180` — `addToHistory("user", message)` for multi-action original message — **BUG: stores translation text on reroute** (Change 2b)

No other writes exist (no direct push_back, no other addToHistory callers besides line 1180).

---

## Change 1: Fix JSON leaking into assistant history entries

**File:** `src/common/claude_api_client.cpp`, line 456-460

**Problem:** When Claude returns a response that starts with a code fence (no text before it), `extractFenceContent` sets `textOnly=""` and `jsonOnly="<huge JSON>"`. The fallback `textOnly.isNotEmpty() ? textOnly : responseText` stores the ENTIRE response including JSON.

**Fix:** Replace line 460:
```cpp
// OLD:
addMessage("assistant", textOnly.isNotEmpty() ? textOnly : responseText);

// NEW:
if (jsonOnly.isNotEmpty())
  addMessage("assistant", textOnly.isNotEmpty() ? textOnly : String("(preset updated)"));
else
  addMessage("assistant", responseText);
```

If a JSON fence was found, store only the natural language text (or a placeholder). If no fence, it's text-only — store as-is.

---

## Change 2a: Don't persist sub-action prompts in conversation history

**Problem:** In multi-action flow, each sub-action string gets stored as a "user" message via `sendMessagesAsync` line 311, and its response at line 460. A 3-action split creates 6 extra history entries. The sub-action user prompts are noise for future context.

**Approach:**
- Before executing sub-actions, save the current history size
- Sub-actions add to history normally (needed for API context during execution)
- After ALL sub-actions complete, remove sub-action "user" entries but keep meaningful "assistant" responses

**Implementation:**
1. Add `int pre_multi_action_history_size_ = -1;` member to `FullInterface`
2. In `full_interface.cpp` line 1180 area, after `addToHistory("user", message)`, save `pre_multi_action_history_size_ = ClaudeApiClient::instance().getHistorySize();`
3. After all multi-action steps complete (lines ~1307-1309 and ~1370-1372), call cleanup
4. New method `cleanupSubActionHistory(int saved_size)` on `ClaudeApiClient`:
   - Iterates from `saved_size` to end of history
   - Keeps "assistant" entries with meaningful content (not "(preset updated)")
   - Removes "user" entries (the sub-action prompts)

## Change 2b: Store original user message before sound design reroute

**Problem:** When sound design translation is re-routed via `routeAndExecute(translation)` at full_interface.cpp:1155, the translation replaces the original user message in history. The original message ("make it blippy") is lost from API history.

**Fix:** Before calling `routeAndExecute(translation)` at line 1155, store the original user message:
```cpp
// Line ~1154, before routeAndExecute(translation):
ClaudeApiClient::instance().addToHistory("user", message);  // original user msg
is_sound_design_reroute_ = true;
routeAndExecute(translation);
```

The `message` variable in the lambda captures the original user message (from routeAndExecute's parameter). The translation will also get stored by the normal sendMessagesAsync flow, so history will contain both: original request + technical translation. This provides good context for follow-ups.

---

## Change 1b: Handle malformed fence edge case in extractFenceContent

**File:** `src/common/claude_api_client.cpp`, lines 262-290

**Problem:** If Claude returns a response with an opening ` ``` ` but no closing one, `extractFenceContent` returns early at line 279 with `textOnly` set to text before the fence but `jsonOnly` empty. Then at line 460, since `jsonOnly` is empty, the `else` branch stores the entire `responseText` including the unclosed fence content (which is likely JSON).

**Fix:** When we detect an opening fence but no closing fence, treat everything after the fence as JSON content and only return the text before the fence:

```cpp
int fenceEnd = response.substring(contentStart).indexOf(String("```"));
if (fenceEnd < 0) {
  // Unclosed fence — treat content after fence as JSON, keep only text before fence
  jsonOut = response.substring(contentStart).trim();
  return;
}
```

This ensures that even with malformed output, the JSON-like content after the opening fence doesn't leak into history.

---

## Change 3: Switch router to Sonnet

**File:** `src/common/claude_api_client.cpp`, line 486

**Change:** `requestBody->setProperty("model", kModel);` → `requestBody->setProperty("model", kModelSonnet);`

The router just classifies requests via tool_use with ~50-100 output tokens. Sonnet is 60x cheaper on input ($3/MTok vs Opus at $15/MTok) and perfectly capable of this simple classification.

**Also verify:** Router does NOT include preset JSON — confirmed, `routeMessageAsync` only sends system prompt + conversation history + current message. No preset JSON.

---

## Change 4: Rename cookbook file reference to SOUND_DESIGN_GUIDE.md

**File:** `src/common/claude_api_client.cpp`, lines 198, 201, 205

Replace all 3 occurrences of `"SYNTHESIZER_COOKBOOK.md"` with `"SOUND_DESIGN_GUIDE.md"`.

**Build scripts** — update the RESOURCE_FILES arrays:
- `build_windows.bat:220` — change `SYNTHESIZER_COOKBOOK.md` to `SOUND_DESIGN_GUIDE.md`
- `build_macos.sh:244` — change `SYNTHESIZER_COOKBOOK.md` to `SOUND_DESIGN_GUIDE.md`
- `build_linux.sh:274` — change `SYNTHESIZER_COOKBOOK.md` to `SOUND_DESIGN_GUIDE.md`

---

## Change 5: Add request/response logging

**File:** `src/common/claude_api_client.h` — add method declaration:
```cpp
void logRequest(const String& endpoint_label, const String& request_body,
                const String& response_body, const var& parsed_response);
```

**File:** `src/common/claude_api_client.cpp` — implement logging:

```cpp
void ClaudeApiClient::logRequest(const String& endpoint_label, const String& request_body,
                                  const String& response_body, const var& parsed_response) {
  File log_dir = LoadSave::getDataDirectory();
  File log_file = log_dir.getChildFile("api_requests.log");

  String timestamp = Time::getCurrentTime().toISO8601(true);

  // Extract token usage from API response if available
  String usage_info;
  if (parsed_response.isObject() && parsed_response.hasProperty("usage")) {
    var usage = parsed_response["usage"];
    int input_tokens = usage.getProperty("input_tokens", 0);
    int output_tokens = usage.getProperty("output_tokens", 0);
    int cache_read = usage.getProperty("cache_read_input_tokens", 0);
    int cache_create = usage.getProperty("cache_creation_input_tokens", 0);
    usage_info = " | input_tokens=" + String(input_tokens)
               + " output_tokens=" + String(output_tokens)
               + " cache_read=" + String(cache_read)
               + " cache_create=" + String(cache_create);
  }

  String log_entry = "--- " + timestamp + " | " + endpoint_label + " ---\n"
                   + "REQUEST_CHARS=" + String(request_body.length())
                   + " RESPONSE_CHARS=" + String(response_body.length())
                   + usage_info + "\n"
                   + "REQUEST:\n" + request_body + "\n"
                   + "RESPONSE:\n" + response_body + "\n\n";

  log_file.appendText(log_entry);
}
```

**Call sites** — add `logRequest()` after parsing response in all 3 async methods:
1. `sendMessagesAsync` — after line 408: `logRequest("sendMessage", jsonBody, response, parsedResponse);`
2. `routeMessageAsync` — after line 588: `logRequest("routeMessage", jsonBody, response, parsedResponse);`
3. `sendSoundDesignTranslationAsync` — after line 755: `logRequest("soundDesignTranslation", jsonBody, response, parsedResponse);`

Note: `jsonBody` is already in scope in all 3 methods. `response` is the raw string. Need to ensure `jsonBody` is accessible at the log call site (it's declared before the HTTP call in all 3 methods, so it's in scope).

---

## Verification
1. Build the app: `build_windows.bat --skip-regenerate --no-run`
2. Run the app and send a few test messages:
   - Simple parameter change → should use router (Sonnet) + sendMessage (Opus)
   - Sound design request (e.g., "warm analog pad") → should use router + sound design translation + re-route
   - Multi-step request → should use router + multiple sendMessage calls
3. Check `api_requests.log` in data directory — verify:
   - Router calls show `kModelSonnet` in request body
   - Request/response sizes and token counts are logged
   - Sound design translation loads `SOUND_DESIGN_GUIDE.md`
4. After a multi-turn conversation, verify conversation history doesn't contain JSON by checking log entries — the messages array in subsequent requests should only have short natural language entries
