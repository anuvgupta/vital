# Plan: Fix All JSON Leaking Into Conversation History + Display Bug

## Context
Testing revealed that the previous "JSON history fix" (Change 1) only handled one of three response formats. The LLM returns JSON in three ways, and we only handled case 2:

1. **Pure JSON, no fences** (most common) — `{"settings":{"osc_2_on":1.0}}` — leaks into history verbatim
2. **Text + JSON with fences** — `"Here's the change:\n\`\`\`json\n{...}\n\`\`\`"` — handled by `extractFenceContent` ✓
3. **Text + JSON without fences** (LLM violates prompt rule) — `"I'll fix that.\n\n{"settings":{...}}"` — leaks into history AND displayed raw to user

## Files to Modify
- `src/common/claude_api_client.cpp` — fix history storage (lines 490-499) and enhance `extractFenceContent`
- `src/interface/editor_sections/full_interface.cpp` — fix display-side parsing (line 1272 area)

## Change 1: Enhance `extractFenceContent` to handle all 3 cases

**File:** `src/common/claude_api_client.cpp`, lines 263-294

Currently `extractFenceContent` only detects code fences. Enhance it to also detect:
- **Case 1 (raw JSON):** If no fence found, check if trimmed response starts with `{` — if so, try to find `{"settings"` and treat the whole thing as JSON with no text.
- **Case 3 (inline JSON without fences):** If no fence found and response doesn't start with `{`, search for `{"settings"` substring. If found, split: text before = `textOut`, from `{"settings"` onward = `jsonOut`.

**Implementation — add after the `if (fenceStart < 0) return;` block:**

```cpp
void ClaudeApiClient::extractFenceContent(const String& response, String& textOut, String& jsonOut) {
  textOut = String();
  jsonOut = String();

  // --- Case 2: code fences ---
  int fenceStart = response.indexOf(String("```"));
  if (fenceStart >= 0) {
    textOut = response.substring(0, fenceStart).trim();

    int contentStart = response.substring(fenceStart).indexOf(String("\n"));
    if (contentStart < 0)
      return;

    contentStart += fenceStart + 1;
    int fenceEnd = response.substring(contentStart).indexOf(String("```"));
    if (fenceEnd < 0) {
      jsonOut = response.substring(contentStart).trim();
      return;
    }

    fenceEnd += contentStart;
    jsonOut = response.substring(contentStart, fenceEnd).trim();

    String trailing = response.substring(fenceEnd + 3).trim();
    if (trailing.isNotEmpty()) {
      if (textOut.isNotEmpty())
        textOut += " ";
      textOut += trailing;
    }
    return;
  }

  // --- No fences found — check for raw/inline JSON ---
  String trimmed = response.trim();

  // Case 1: pure raw JSON (starts with '{')
  if (trimmed.startsWith("{")) {
    jsonOut = trimmed;
    return;
  }

  // Case 3: text followed by inline JSON without fences
  int jsonStart = response.indexOf("{\"settings\"");
  if (jsonStart < 0)
    jsonStart = response.indexOf("{\n\"settings\"");
  if (jsonStart > 0) {
    textOut = response.substring(0, jsonStart).trim();
    jsonOut = response.substring(jsonStart).trim();
  }
}
```

This makes `extractFenceContent` a comprehensive "split response into text + JSON" utility that handles all 3 formats.

## Change 2: History storage in `sendMessagesAsync` (already correct logic)

**File:** `src/common/claude_api_client.cpp`, lines 494-499

The existing code at lines 496-499 already does the right thing:
```cpp
if (jsonOnly.isNotEmpty())
  addMessage("assistant", textOnly.isNotEmpty() ? textOnly : String("(preset updated)"));
else
  addMessage("assistant", responseText);
```

With the enhanced `extractFenceContent` from Change 1, this now works for all 3 cases:
- Case 1: `jsonOnly` = raw JSON, `textOnly` = empty → stores `"(preset updated)"`
- Case 2: `jsonOnly` = fenced JSON, `textOnly` = surrounding text → stores text only
- Case 3: `jsonOnly` = inline JSON, `textOnly` = preceding text → stores text only

**No code change needed here** — Change 1 fixes this automatically.

## Change 3: Fix display-side parsing in `full_interface.cpp`

**File:** `src/interface/editor_sections/full_interface.cpp`, line 1272

Currently:
```cpp
String jsonToParse = jsonBlock.isNotEmpty() ? jsonBlock : response.trim();
```

This already uses `extractFenceContent` at line 1269. With the enhanced version from Change 1, `jsonBlock` will now be populated for all 3 cases. So this line will correctly use the extracted JSON for parsing.

**However**, for case 3, `textMessage` will now also be populated (the "I'll fix that" text), so the display path at lines 1288-1314 will correctly show only the text portion instead of the raw response.

**No code change needed here either** — Change 1 fixes this automatically.

## Summary of actual code changes

Only `extractFenceContent` needs to change. The downstream consumers (`sendMessagesAsync` history storage and `full_interface.cpp` display) already handle the `textOut`/`jsonOut` split correctly — they just weren't receiving the right values because `extractFenceContent` was too narrow.

## Verification
1. Build: `build_windows.bat --skip-regenerate --no-run`
2. Clear the old log: delete `api_requests.log`
3. Test all 3 response types:
   - Simple param change ("turn on osc 2") → case 1: pure JSON, should store "(preset updated)" in history
   - Sound design or complex request → may trigger case 2 or 3
   - Ask a question + request a change ("what's the cutoff? also increase it") → case 2/3: text + JSON
4. Check `api_requests.log` — verify conversation history in subsequent requests shows only short text/placeholders for assistant entries, no JSON diffs
5. Verify the last-message display bug is fixed: when LLM returns text+JSON without fences, only the text should show in chat, and the JSON should be applied silently
