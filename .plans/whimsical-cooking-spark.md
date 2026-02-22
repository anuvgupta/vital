# Autosave Presets, Checkpointing & Restore Chat

## Context

Users interacting with the AI chat to design synth patches have no way to go back to a previous state. If the AI makes an unwanted change, the user must manually undo or start over. This feature adds automatic checkpointing of the synth preset at each message exchange, with a hover-activated restore button on each message to revert to that point in the conversation.

## Files to Modify

| File | Changes |
|------|---------|
| `src/interface/editor_sections/side_panel.h` | Add `ChatCheckpoint` struct, hover state, restore button bounds, new methods |
| `src/interface/editor_sections/side_panel.cpp` | Implement hover tracking, restore button rendering, click handling, checkpoint management, cleanup |
| `src/interface/editor_sections/full_interface.h` | Add `saveAutosaveCheckpoint()` helper, `restoreCheckpoint()` method |
| `src/interface/editor_sections/full_interface.cpp` | Wire autosave triggers in message submit + response callback, implement restore logic |
| `src/common/claude_api_client.h` | Add `truncateHistoryTo(int)` and `getHistorySize()` public methods |
| `src/common/claude_api_client.cpp` | Implement `truncateHistoryTo()` |

No new files needed.

## Implementation Steps

### Step 1: Add API history truncation to ClaudeApiClient

In `claude_api_client.h`, add public methods:
```cpp
void truncateHistoryTo(int size);
int getHistorySize() const { return (int)conversation_history_.size(); }
```

In `claude_api_client.cpp`:
```cpp
void ClaudeApiClient::truncateHistoryTo(int size) {
    if (size >= 0 && size < (int)conversation_history_.size())
        conversation_history_.resize(size);
}
```

### Step 2: Add ChatCheckpoint struct and state to VitalSidePanel

In `side_panel.h`, add before the class:
```cpp
struct ChatCheckpoint {
    int ui_message_index;    // index into messages_
    int api_history_size;    // conversation_history_.size() at save time
    File autosave_file;      // path to .vital file on disk
};
```

Add to `VitalSidePanel` private members:
```cpp
std::vector<ChatCheckpoint> checkpoints_;
int hovered_message_index_ = -1;
Rectangle<int> restore_button_bounds_;  // set during paint for hit testing
```

Add public methods:
```cpp
int getMessageCount() const { return (int)messages_.size(); }
void addCheckpoint(int ui_message_index, int api_history_size, File autosave_file);
void truncateMessagesTo(int count);
void removeCheckpointsAfter(int message_index);
const ChatCheckpoint* getCheckpoint(int message_index) const;
```

### Step 3: Wire autosave triggers in FullInterface

**A. On user message send** — in `FullInterface::sidePanelMessageSubmitted()`, after setting `api_request_in_flight_ = true` and before `sendApiRequest()`:
1. Get synth state: `gui->getSynth()->getStateAsJson()`
2. Write to `LoadSave::getDataDirectory().getChildFile("autosaves")/checkpoint_<timestamp>.vital`
3. Call `panel->addCheckpoint(panel->getMessageCount() - 2, ClaudeApiClient::instance().getHistorySize(), file)`
   - `-2` because messages_ has [... userMsg, "Thinking..."] at this point

**B. On response received** — in the `sendApiRequest()` callback, after `panel->addResponseMessage(msg)` succeeds (both the JSON-preset path ~line 1157 and the text-only path ~line 1180):
1. Save synth state to autosave file
2. Call `panel->addCheckpoint(panel->getMessageCount() - 1, ClaudeApiClient::instance().getHistorySize(), file)`

**Helper** in `FullInterface`:
```cpp
File saveAutosaveCheckpoint(SynthBase* synth) {
    File dir = LoadSave::getDataDirectory().getChildFile("autosaves");
    if (!dir.exists()) dir.createDirectory();
    File file = dir.getChildFile("checkpoint_" + String(Time::currentTimeMillis()) + ".vital");
    json state = synth->getStateAsJson();
    file.replaceWithText(String(state.dump()));
    return file;
}
```

### Step 4: Implement hover tracking in VitalSidePanel

Add `mouseMove()` override — check if cursor is in `chat_bounds_`, find which message the y-coordinate (adjusted for scroll) falls within, set `hovered_message_index_` and `repaintBackground()` if changed.

Add `mouseExit()` override — reset `hovered_message_index_ = -1` and repaint.

### Step 5: Draw restore button on hovered messages

In `paintChatMessages()`, after rendering each message, check:
1. Is this message's index == `hovered_message_index_`?
2. Does a checkpoint exist for this index? (search `checkpoints_`)

If yes, draw a small circular arrow icon (JUCE Path arc + arrowhead) in the top-right corner of the message area. Size: ~20x20 scaled by `size_ratio_`. Store bounds in `restore_button_bounds_` for hit testing.

The icon: a ~270-degree arc with an arrowhead at the end, drawn with the same `text_color` used for messages.

### Step 6: Handle restore button click

Add `mouseUp()` override in `VitalSidePanel`. If click is within `restore_button_bounds_` and `hovered_message_index_ >= 0`:

Show confirmation using native `AlertWindow` (same pattern as voice chat button at line 664 of side_panel.cpp):
```cpp
AlertWindow::showOkCancelBox(AlertWindow::QuestionIcon,
    "Restore Checkpoint",
    "Restore synth to this point in the conversation? Messages after this point will be removed.",
    "Restore", "Cancel", nullptr,
    ModalCallbackFunction::create([this, idx](int result) {
        if (result == 1)
            for (Listener* l : listeners_)
                // Notify FullInterface to handle the restore
    }));
```

Add listener method to `VitalSidePanel::Listener`:
```cpp
virtual void sidePanelRestoreRequested(int message_index) {}
```

### Step 7: Implement restore logic in FullInterface (with user→system message remapping)

`FullInterface::sidePanelRestoreRequested(int message_index)`:

**Key behavior**: If the clicked message is a **user message** (kUser), remap to the **next system message's checkpoint** instead. This is because clicking restore on "make me a bass pad" should restore to the state *after* Claude applied that bass pad, not before. If the clicked message is a **system message** (kSystem), use its checkpoint directly.

Implementation in `sidePanelRestoreRequested()`:
1. Check `panel->getMessageType(message_index)` — need to add a `getMessageType(int)` accessor to VitalSidePanel
2. If it's `kUser`, look for a checkpoint at `message_index + 1` (the next system message). If that checkpoint doesn't exist, fall back to the checkpoint at `message_index` itself.
3. Use the resolved checkpoint's `autosave_file` and `api_history_size`
4. **Truncation point**: Always truncate UI to `message_index + 1` for user messages (keep user msg + its response) or `message_index + 1` for system messages (keep through that response). Actually: use the resolved checkpoint's `ui_message_index + 1` as the truncation point.
5. Load preset, truncate UI, truncate API history, remove stale checkpoints, cancel in-flight requests

**New accessor needed** in `VitalSidePanel`:
```cpp
ChatMessage::Type getMessageType(int index) const;
```

**Files to modify**: `side_panel.h` (add accessor), `side_panel.cpp` (implement accessor), `full_interface.cpp` (update restore logic)

### Step 8: Cleanup & Archiving

**On `clearChat()`**: Instead of deleting autosave files, archive them by moving the current `autosaves/` contents into a named subdirectory. The subdirectory name is derived from the first user message's first 7 words (sanitized for filesystem safety — replace non-alphanumeric chars with `_`, truncate to reasonable length). Example: `autosaves/make_me_a_deep_bass_pad_with/`.

Implementation in `VitalSidePanel::clearChat()`:
1. Find the first `kUser` message in `messages_` to get the session name
2. Take the first 7 words, sanitize (replace non-alnum with `_`, lowercase, limit to ~60 chars)
3. Create subdirectory under `autosaves/` with that name (append `_2`, `_3` etc. if exists)
4. Move all checkpoint files into that subdirectory
5. Clear `checkpoints_` vector

**On app startup**: No cleanup — archived sessions stay in named subdirectories under `autosaves/`. Current session's loose checkpoint files (from a crash without clearChat) get archived into an `unsaved_session/` subdirectory.

**Cap**: Limit to 50 checkpoints per session. When exceeded, delete the oldest checkpoint file and remove from vector. Also limit archived sessions to 20 — when archiving, if there are already 20 archived subdirectories, delete the oldest one.

## Key Design Decisions

- **No new files**: All logic fits into existing side_panel and full_interface files
- **Native AlertWindow for confirmation**: Matches existing voice chat button pattern (side_panel.cpp:664), avoids creating a custom overlay class
- **Autosave directory**: `LoadSave::getDataDirectory()/autosaves/` — sits alongside User/, Presets/, etc.
- **File naming**: `checkpoint_<millisecond_timestamp>.vital` — unique, naturally ordered
- **Checkpoint tracks both UI index and API history size**: Needed because the two vectors are independent and not 1:1 mapped

## Existing Functions to Reuse

- `SynthBase::getStateAsJson()` / `saveToJson()` — `src/common/synth_base.cpp:298`
- `SynthBase::loadStateFromJson()` / `loadFromJson()` — `src/common/synth_base.cpp:340`
- `LoadSave::getDataDirectory()` — `src/common/load_save.cpp:1773`
- `SynthGuiInterface::updateFullGui()` / `notifyFresh()` — existing GUI refresh pattern
- `AlertWindow::showOkCancelBox` — JUCE built-in, already used for voice chat confirmation

## Verification

1. **Build**: Run Windows build with `build_windows.bat --skip-regenerate --no-run`
2. **Manual test flow**:
   - Open synth, open side panel chat
   - Send a message, receive a response — verify `autosaves/` folder is created with 2 checkpoint files (one for user msg, one for response)
   - Send another message/response — verify 2 more checkpoint files
   - Hover over earlier messages — verify restore button appears on messages that have checkpoints
   - Click restore on an earlier message — verify confirmation dialog appears
   - Confirm restore — verify: preset reverts, messages after that point disappear, subsequent messages to API don't include removed conversation
   - Click CLEAR — verify autosave files are moved into a named subdirectory (e.g. `autosaves/make_me_a_deep_bass/`)
   - Start a new chat session — verify new checkpoints go into fresh `autosaves/` root
   - Restart app — verify any loose checkpoint files from a crash are archived into `unsaved_session/`
