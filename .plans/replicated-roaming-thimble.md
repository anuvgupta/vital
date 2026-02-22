# Plan: Fix Preset JSON Context Pollution in Conversation History

## Context
Every time the user sends a message, `sendApiRequest` in `full_interface.cpp` fetches the current synth state as JSON and passes it to `ClaudeApiClient::sendMessages`. Inside `sendMessagesAsync`, this preset context is currently added to `conversation_history_` via `addMessage("user", preset_context)` — meaning it persists across turns. After N turns, the history contains N stale preset snapshots, wasting context window tokens. Only the most recent snapshot matters (each one is cumulative), and it should not be stored in history since it's re-fetched fresh every time.

## Goal
- Preset JSON is injected into each API call payload just before the latest user message(s)
- Preset JSON is never stored in `conversation_history_`
- Old turns in history contain only the actual user text and assistant responses

## File to Change
**`src/common/claude_api_client.cpp`** — `sendMessagesAsync` only

## Current Flow (broken)
```
addMessage("user", preset_context)   ← goes into history (bad)
addMessage("user", user_message)     ← goes into history
build messagesArray from full history
```

## New Flow
```
addMessage("user", user_message)     ← goes into history (good)
build messagesArray from history[0 .. size-messages.size()]   ← all prior turns
if preset_json: inject preset context message here            ← ephemeral, not in history
append the last messages.size() messages from history         ← current turn user message(s)
```

## Exact Change in `sendMessagesAsync`

### Remove (lines 192–195):
```cpp
if (preset_json.isNotEmpty()) {
    String preset_context = "This is the current preset JSON:\n```json\n" + preset_json + "\n```";
    addMessage("user", preset_context);
}
```

### Replace the messagesArray build loop (lines 225–231) with:
```cpp
// Number of new user messages we just added for this turn
int new_message_count = messages.size();
int history_size = (int)conversation_history_.size();
int prior_count = history_size - new_message_count;

// Add all prior-turn messages (no preset snapshots)
Array<var> messagesArray;
for (int i = 0; i < prior_count; ++i) {
    const auto& msg = conversation_history_[i];
    DynamicObject::Ptr msgObj = new DynamicObject();
    msgObj->setProperty("role", msg.role);
    msgObj->setProperty("content", msg.content);
    messagesArray.add(var(msgObj.get()));
}

// Inject current preset context just before this turn's user message(s)
if (preset_json.isNotEmpty()) {
    String preset_context = "This is the current preset JSON:\n```json\n" + preset_json + "\n```";
    DynamicObject::Ptr presetMsg = new DynamicObject();
    presetMsg->setProperty("role", "user");
    presetMsg->setProperty("content", preset_context);
    messagesArray.add(var(presetMsg.get()));
}

// Add this turn's user message(s)
for (int i = prior_count; i < history_size; ++i) {
    const auto& msg = conversation_history_[i];
    DynamicObject::Ptr msgObj = new DynamicObject();
    msgObj->setProperty("role", msg.role);
    msgObj->setProperty("content", msg.content);
    messagesArray.add(var(msgObj.get()));
}
```

## Result per Turn (API payload)
```
Turn 1 API call:  [preset_context_T1], [user_msg_1]
Turn 2 API call:  [user_msg_1], [assistant_1], [preset_context_T2], [user_msg_2]
Turn 3 API call:  [user_msg_1], [assistant_1], [user_msg_2], [assistant_2], [preset_context_T3], [user_msg_3]
```
History only ever holds: user messages + assistant responses. No preset snapshots.

## Verification
- Build Windows: `cmd.exe /c "cd /d C:\Users\anuvc\Documents\Code\Workspace\synth\vital && build_windows.bat --skip-regenerate --no-run"`
- Send 3+ chat messages and check the `DBG("ClaudeApiClient: Sending request: ...")` log output to confirm:
  - Only 1 preset JSON block per API call (the current one)
  - History messages contain no preset JSON blocks
  - The preset context appears just before each latest user message in the payload
