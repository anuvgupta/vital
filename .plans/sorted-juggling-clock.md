# Plan: Message Queue for Rapid Chat Messages

## Problem

Currently, if a user sends messages in rapid succession while waiting for an API response:
- Multiple `Thread::launch()` calls fire concurrent HTTP requests
- `conversation_history_` in `ClaudeApiClient` has no protection against concurrent writes from multiple background threads
- Multiple "Thinking..." indicators get added to the chat
- Responses arrive in unpredictable order, potentially corrupting conversation state

## Design Decisions

1. **Queue lives in `FullInterface`** — it's the coordinator between UI and API. It has access to synth state (for fresh preset JSON at send time) and controls the response processing.

2. **Thread safety is free** — both `sidePanelMessageSubmitted()` (from UI events) and the API callback (via `MessageManager::callAsync`) run on the JUCE message thread. No mutex needed.

3. **Batch queued messages** — when the API responds and there are queued messages, send all of them in one API call as separate user messages. This is natural for the Anthropic API (consecutive user messages are fine) and means the user's corrections/additions are all visible to Claude at once.

4. **Fresh preset JSON at send time** — queued messages don't capture preset JSON when queued. Instead, a fresh snapshot is taken when the batch is actually sent, reflecting any changes the previous response applied.

5. **On API failure, clear the queue** — don't hammer a broken API. The user sees the error and can re-send manually.

6. **Single "Thinking..." indicator** — don't add duplicates while waiting.

## Changes

### 1. `FullInterface` (full_interface.h + full_interface.cpp)

**New members in `full_interface.h`:**
```cpp
// Message queue state (all accessed on message thread only)
bool api_request_in_flight_ = false;
StringArray queued_messages_;
```

**Modified `sidePanelMessageSubmitted()`:**
```cpp
void FullInterface::sidePanelMessageSubmitted(const String& message) {
  if (api_request_in_flight_) {
    // Queue the message — it's already displayed in the chat by VitalSidePanel
    queued_messages_.add(message);
    return;
  }

  api_request_in_flight_ = true;
  sendApiRequest({ message });  // new helper
}
```

**New helper `sendApiRequest(const StringArray& messages)`:**
Extracts the common logic from current `sidePanelMessageSubmitted`:
- Gets fresh preset JSON from synth state
- Calls `ClaudeApiClient::sendMessages()` with all messages + callback
- In the callback:
  - Processes response (clear thinking, apply preset patch, show response)
  - Checks if `queued_messages_` is non-empty
  - If yes: drains queue into a StringArray, adds "Thinking..." back, calls `sendApiRequest()` recursively
  - If no: sets `api_request_in_flight_ = false`
- On failure: clears `queued_messages_`, sets `api_request_in_flight_ = false`

**New declaration in `full_interface.h`:**
```cpp
void sendApiRequest(const StringArray& messages);
```

### 2. `ClaudeApiClient` (claude_api_client.h + claude_api_client.cpp)

**New method:**
```cpp
void sendMessages(const StringArray& messages, ResponseCallback callback,
                  const String& preset_json = String());
```

This is similar to current `sendMessage` but accepts multiple messages. Internally:
- Adds preset_json context as a user message (once)
- Adds each message as a separate user message to `conversation_history_`
- Sends the full history to the API

The existing `sendMessage()` can be kept as a convenience wrapper that calls `sendMessages()` with a single-element array.

**New async method:**
```cpp
void sendMessagesAsync(const StringArray& messages, ResponseCallback callback,
                       const String& preset_json);
```

### 3. `VitalSidePanel` (side_panel.h + side_panel.cpp)

**Modify `submitMessage()`:**
- Check if the last message is already a "Thinking..." indicator
- Only add "Thinking..." if one isn't already showing
- Everything else stays the same (display user message, clear input, notify listeners)

**Add public method:**
```cpp
bool isShowingThinking() const;
```
Returns true if the last message is a "Thinking..." system message. Used by FullInterface when re-adding "Thinking..." for queued batch sends.

## Message Flow — Happy Path

```
User sends "increase cutoff"
  → VitalSidePanel: shows message + "Thinking..."
  → FullInterface: api_request_in_flight_ = true, calls sendApiRequest(["increase cutoff"])
  → ClaudeApiClient: background thread fires HTTP request

User sends "add reverb" (while waiting)
  → VitalSidePanel: shows message, skips duplicate "Thinking..."
  → FullInterface: api_request_in_flight_ is true → queued_messages_ = ["add reverb"]

User sends "wet at 50%" (while still waiting)
  → VitalSidePanel: shows message, skips duplicate "Thinking..."
  → FullInterface: queued_messages_ = ["add reverb", "wet at 50%"]

API response arrives for "increase cutoff"
  → FullInterface callback: process response, apply preset changes
  → clearThinkingMessage(), addResponseMessage(...)
  → Queue non-empty → drain to ["add reverb", "wet at 50%"]
  → addMessage("Thinking...", kSystem)
  → sendApiRequest(["add reverb", "wet at 50%"]) with FRESH preset JSON

API response arrives for batched messages
  → FullInterface callback: process response
  → Queue empty → api_request_in_flight_ = false
```

## Files Modified

| File | Changes |
|------|---------|
| `src/interface/editor_sections/full_interface.h` | Add `api_request_in_flight_`, `queued_messages_`, `sendApiRequest()` |
| `src/interface/editor_sections/full_interface.cpp` | Refactor `sidePanelMessageSubmitted()`, add `sendApiRequest()` with queue drain logic |
| `src/common/claude_api_client.h` | Add `sendMessages()` and `sendMessagesAsync()` |
| `src/common/claude_api_client.cpp` | Implement `sendMessages()`/`sendMessagesAsync()` |
| `src/interface/editor_sections/side_panel.h` | Add `isShowingThinking()` |
| `src/interface/editor_sections/side_panel.cpp` | Guard against duplicate "Thinking..." in `submitMessage()`, implement `isShowingThinking()` |
