# Multi-Layer Agentic Chat Flow

## Context
Currently, every user chat message goes directly to Claude with the full system prompt + preset schema, expecting a JSON diff response. This works for simple commands but doesn't handle complex multi-step requests well. We want to add a "router" layer that first analyzes the user's message and either passes it through as-is or breaks it into sequential sub-actions.

## Architecture

```
User message
    ↓
Router Call (Claude w/ tool_use, no preset schema)
    ↓
┌─────────────────────────────────┐
│ tool_use: route_actions         │
│ { "actions": ["action1", ...] } │
└─────────────────────────────────┘
    ↓
Single action?  ──→  Pass through to existing preset generation call
Multiple actions? ──→  Show "Breaking it down..." → execute each sequentially
```

## Files to Modify

1. **`src/common/claude_api_client.h`** — Add new `routeMessage()` method
2. **`src/common/claude_api_client.cpp`** — Implement router API call with tool_use
3. **`src/interface/editor_sections/full_interface.cpp`** — Wire up the two-step flow
4. **`src/interface/editor_sections/full_interface.h`** — Add helper declarations

## Implementation

### Step 1: Add router method to ClaudeApiClient

**`claude_api_client.h`** — Add:
```cpp
using RouterCallback = std::function<void(const StringArray& actions, bool success, const String& error)>;

void routeMessage(const String& message, RouterCallback callback);
```
And private:
```cpp
void routeMessageAsync(const String& message, RouterCallback callback);
```

**`claude_api_client.cpp`** — Implement `routeMessage()` and `routeMessageAsync()`:

- **Model**: Same as existing (`kModelOpus`)
- **Max tokens**: 512 (routing is lightweight)
- **System prompt**: Short routing-specific prompt (hardcoded constant string):
  > "You are a routing assistant for a synthesizer preset tool. Analyze the user's request and break it into atomic preset modification actions. Each action should be a single, self-contained instruction. For simple requests, return a single action. For complex multi-part requests, split into ordered steps. For questions or non-modification requests, return the original request as a single action."
- **Messages**: Include full conversation history (for context understanding), plus current user message
- **No preset JSON** — the router doesn't need it
- **Tool definition**:
```json
{
  "name": "route_actions",
  "description": "Route user request into sequential preset modification actions",
  "input_schema": {
    "type": "object",
    "properties": {
      "actions": {
        "type": "array",
        "items": { "type": "string" },
        "description": "Ordered list of atomic actions to execute sequentially"
      }
    },
    "required": ["actions"]
  }
}
```
- **`tool_choice`**: `{ "type": "tool", "name": "route_actions" }` — forces tool use
- **Response parsing**: Iterate `content` array, find block with `"type": "tool_use"`, parse `input.actions` array
- **History**: The router call itself is NOT stored in conversation history (transparent infrastructure). But the original user message IS stored (see Step 2).

### Step 2: Modify FullInterface flow

**`full_interface.h`** — Add new member variables and methods:
```cpp
// Multi-action state
StringArray pending_actions_;
int total_actions_ = 0;
int current_action_index_ = 0;
String original_routed_message_;  // The original user message that was split

void routeAndExecute(const String& message);
void executeNextAction();
```

**`full_interface.cpp`** — Changes:

1. `sidePanelMessageSubmitted()` — Change `sendApiRequest(messages)` call to `routeAndExecute(message)`. Checkpoint logic stays the same.

2. New method `routeAndExecute(const String& message)`:
   ```
   - Call ClaudeApiClient::routeMessage(message, callback)
   - In callback (on message thread):
     - If error/failure: show error, clear api_request_in_flight_
     - If 1 action:
       - Pass through: call sendApiRequest({message}) as today (original message)
     - If multiple actions:
       - Store original message: original_routed_message_ = message
       - Store actions: pending_actions_ = actions, total_actions_ = count
       - current_action_index_ = 0
       - Replace "Thinking..." with "Breaking it down..."
       - Call executeNextAction()
   ```

3. New method `executeNextAction()`:
   ```
   - Get next action: pending_actions_[current_action_index_]
   - Replace thinking/status message with "Step N/M: <action>..."
   - current_action_index_++
   - Build StringArray with the action text
   - Call sendApiRequest(action_messages) — but with a twist:
     we need to modify the response callback to chain to executeNextAction()
   ```

4. Modify `sendApiRequest()` to support chaining:
   - After successful preset application, check if `pending_actions_` has remaining items
   - If yes: update status message, call `executeNextAction()`
   - If no: show completion message, clear state, check queued_messages_ as before
   - This reuses the existing response handling (JSON parsing, merge, etc.)

### Step 3: Handle conversation history for multi-action

When the router splits a message into multiple actions:
1. The **original user message** is added to conversation history first (by routeAndExecute, manually via `ClaudeApiClient::addMessage("user", message)` — need to make addMessage public or add a helper)
2. Each **sub-action** is also sent as a user message through `sendApiRequest()` → `sendMessages()` which adds them to history
3. Each **assistant response** (the JSON diff) is stored as usual

So the conversation history looks like:
```
user: "make a dark dubstep bass with wobble and distortion"  ← original
user: "Create a dark bass sound with saw wave"               ← sub-action 1
assistant: [response text]
user: "Add LFO modulation to filter for wobble"              ← sub-action 2
assistant: [response text]
user: "Add distortion effect"                                ← sub-action 3
assistant: [response text]
```

This means the LLM sees the full context of what the user originally asked plus what's been done so far.

**Note**: Need to either make `addMessage()` public or add a public `addUserMessage()` method to ClaudeApiClient for storing the original message without sending an API call.

## UI Flow

**Simple request** ("increase filter cutoff"):
```
User: "increase filter cutoff"
[Thinking...]  ← shown during router + execution (single status, replaced in-place)
Assistant: "Done!"  ← same as today
```

**Complex request** ("make a dark dubstep bass with wobble"):
```
User: "make a dark dubstep bass with wobble and distortion"
[Thinking...]     ← during router call
[Breaking it down...]  ← replaces Thinking after router returns
[Step 1/3: Creating dark bass sound...]  ← replaces Breaking it down
  (preset applied silently)
[Step 2/3: Adding wobble LFO...]  ← replaces previous step
  (preset applied silently)
[Step 3/3: Adding distortion...]  ← replaces previous step
  (preset applied silently)
Assistant: "All set!"  ← final completion message
```

All intermediate status updates replace the same "thinking" message slot — the user sees one changing status line, not a flood of messages.

**Side panel change needed**: `clearThinkingMessage()` currently only matches `"Thinking..."` exactly. Need to add a `updateStatusMessage(const String& text)` method to `VitalSidePanel` that replaces the last system message's text in-place (if it's a kSystem message). This is used for the "Breaking it down..." → "Step 1/3..." transitions. Add to **`side_panel.h`** and **`side_panel.cpp`**.

Files also modified:
5. **`src/interface/editor_sections/side_panel.h`** — Add `updateStatusMessage()` declaration
6. **`src/interface/editor_sections/side_panel.cpp`** — Implement `updateStatusMessage()`

## Follow-up: Optimize router splitting granularity

**Problem**: The router splits too aggressively — "turn on osc 2, turn on osc 3, turn on reverb, raise envelope release" becomes 4 separate API calls, each with full preset schema + conversation history. These are all simple parameter changes that can be done in one prompt.

**Fix**: Update `kRouterSystemPrompt` in `claude_api_client.cpp` (line 29) to instruct the router to batch simple commands together and only split when genuinely necessary.

New prompt:
```
"You are a routing assistant for a synthesizer preset modification tool. "
"Analyze the user's request and decide how to execute it. "
"Group simple, independent changes together in a single action — things like toggling parameters, "
"adjusting values, or enabling/disabling features can all be handled in one step. "
"Only split into multiple actions when a request involves genuinely complex, "
"multi-layered sound design where each step builds meaningfully on the previous "
"(e.g. 'create a dark dubstep bass with wobble modulation and distorted reverb'). "
"Each action can contain multiple simple instructions. Aim for the fewest actions possible. "
"For questions or non-modification requests, return the original request as a single action."
```

**File**: `src/common/claude_api_client.cpp` line 29

## Follow-up: Smarter step message display

**Problem**: Currently every completed step gets a completion phrase ("Tuned it up.", "Crunched it.") which clutters the chat. Most steps only produce JSON (no text), so the completion phrases are noise.

**New behavior**:
- Step completes with **no text output** (just JSON) + **more steps remaining**: replace current step message with next step message (no completion phrase)
- Step completes with **text output** + **more steps remaining**: replace step message with the text, then add next step as new message below
- **Final step** with no text: replace step message with single completion phrase
- **Final step** with text: replace step message with the text

**File**: `src/interface/editor_sections/full_interface.cpp` — modify the multi-action branch in `sendApiRequest()` response callback (lines ~1226-1236 and ~1286-1294)

**Change in JSON-parsed success path** (line ~1228):
```cpp
if (is_multi_action) {
    if (current_action_index_ < pending_actions_.size()) {
        // More steps: if text output, show it then add next step; if no text, just replace with next step
        if (textMessage.isNotEmpty()) {
            panel->updateStatusMessage(textMessage);
            executeNextAction();  // executeNextAction adds a NEW message
        } else {
            executeNextAction();  // replaces current step message with next step
            // But executeNextAction currently uses addMessage — need to change to updateStatusMessage when no text shown
        }
        return;
    }
    // Final step
    String msg = textMessage.isNotEmpty() ? textMessage : getCompletionPhrase();
    panel->updateStatusMessage(msg);
}
```

**Key change in `executeNextAction()`**: Need a parameter or check to decide between `addMessage` (after text was shown) vs `updateStatusMessage` (replacing silently). Simplest: add a bool parameter `replaceExisting`:
```cpp
void executeNextAction(bool replaceExisting = false);
```
- `replaceExisting = true` → use `panel->updateStatusMessage("Step N/M: ...")`
- `replaceExisting = false` → use `panel->addMessage("Step N/M: ...", kSystem)`

## Verification
1. Build on Windows: `cmd.exe /c "cd /d C:\Users\anuvc\Documents\Code\Workspace\synth\vital && build_windows.bat --skip-regenerate --no-run"`
2. Test simple message → should pass through with single action (no visible difference)
3. Test multi-action where steps produce no text → step messages replace each other, single completion at end
4. Test multi-action where a step produces text → text shown, next step added below
5. Test restore/checkpoint → should still work correctly
