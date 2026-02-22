# Plan: Fix Multi-Action One-Shotting via History Isolation

## Context
After implementing the initial token cost reduction changes, testing revealed that the LLM one-shots the entire request on the first sub-action because it sees the full original message (or sound design translation) in conversation history alongside the sub-action. Subsequent sub-actions get "already done" text responses, wasting tokens. Fix: don't store the original/translation message in history for multi-action flows; only store the individual sub-action prompts and their responses.

## Files to Modify
- `src/interface/editor_sections/full_interface.cpp` — remove two `addToHistory` calls, remove all `cleanupSubActionHistory` calls and `pre_multi_action_history_size_` resets
- `src/interface/editor_sections/full_interface.h` — remove `pre_multi_action_history_size_` member
- `src/common/claude_api_client.cpp` — remove `cleanupSubActionHistory` implementation
- `src/common/claude_api_client.h` — remove `cleanupSubActionHistory` declaration

## Changes

### 1. Remove multi-action parent message from history (`full_interface.cpp`)

**Line ~1182:** Remove `ClaudeApiClient::instance().addToHistory("user", message);`

This line stores whatever `message` was passed to `routeAndExecute()` before sub-actions begin. In the sound design case, this is the translation text (full numbered plan). In the non-sound-design case, this is the user's original multi-part request. Either way, it gives the LLM full scope and causes one-shotting.

After removal, only the individual sub-actions are stored (via `sendMessagesAsync` line 311).

### 2. Keep sound design reroute `addToHistory` (`full_interface.cpp`)

**Line ~1154:** `ClaudeApiClient::instance().addToHistory("user", message);` — **KEEP this line.**

This stores the original user message ("make it blippy") before the translation is re-routed. It stays because:
- `message` here is the original user request (captured in the lambda), not the translation
- It provides follow-up context ("what did the user actually ask for?")
- The translation text does NOT get stored here — it's the `message` param at line 1182, which we're removing

### 3. Remove `cleanupSubActionHistory` and `pre_multi_action_history_size_` entirely

Since sub-action prompts now **stay** in history permanently (they're the actual record of what was done), the post-completion cleanup is no longer needed.

**`full_interface.cpp`:** Remove all of these:
- `pre_multi_action_history_size_ = ClaudeApiClient::instance().getHistorySize();` (line ~1183)
- All `if (pre_multi_action_history_size_ >= 0) cleanupSubActionHistory(...)` blocks (2 locations: JSON final step ~1308, text-only final step ~1374)
- All `pre_multi_action_history_size_ = -1;` resets (6 locations: executeNextAction early return, error path, load failure, JSON final step, text-only final step, restore, cancel-edit)

**`full_interface.h`:** Remove `int pre_multi_action_history_size_ = -1;` member

**`claude_api_client.cpp`:** Remove `cleanupSubActionHistory` method implementation

**`claude_api_client.h`:** Remove `void cleanupSubActionHistory(int saved_size);` declaration

## Expected History After Multi-Action

### Sound design multi-action (before → after)

Before (broken):
```
user: "make an 808 bass"                          ← original msg (line 1154)
user: "1. Set osc to sine 2. Configure env..."     ← translation (line 1182, causes one-shot)
user: "Set osc 1 to sine..."                       ← sub-action 1 (LLM sees plan, does everything)
assistant: "{huge JSON with all changes}"
user: "Configure envelope..."                      ← sub-action 2
assistant: "Already done!"                         ← wasted
```

After (fixed):
```
user: "make an 808 bass"                           ← original msg preserved (line 1154)
user: "Set osc 1 to sine..."                       ← sub-action 1 (no full plan visible)
assistant: "(preset updated)"                      ← focused response
user: "Configure envelope with instant attack..."  ← sub-action 2
assistant: "(preset updated)"                      ← focused response
```

### Non-sound-design multi-action (before → after)

Before (broken):
```
user: "change osc to saw, lower filter, add chorus, adjust attack"  ← original (line 1182)
user: "Change osc to saw, lower filter"            ← sub-action 1 (LLM sees full request, does all)
assistant: "{huge JSON}"
user: "Add chorus, adjust attack"                  ← sub-action 2
assistant: "Already done!"                         ← wasted
```

After (fixed):
```
user: "Change osc to saw, lower filter"            ← sub-action 1 only
assistant: "(preset updated)"
user: "Add chorus, adjust attack"                  ← sub-action 2
assistant: "(preset updated)"
```

## Verification
1. Build: `build_windows.bat --skip-regenerate --no-run`
2. Test sound design request (e.g., "make an 808 bass") — should trigger translation → router splits → each sub-action executes independently with unique JSON responses
3. Check `api_requests.log` — verify each sub-action's messages array does NOT contain the translation or original message, only prior sub-actions
4. Test follow-up message after multi-action — verify LLM has enough context from sub-action history to understand what was done
