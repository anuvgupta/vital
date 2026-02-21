# Change Restore Button to Claude-style "Edit & Retry"

## Context
Currently, clicking the restore button on a user message shows a confirmation dialog, then restores the synth state and truncates messages. The user wants the Claude web UI pattern: clicking the button instantly removes the message (and everything after), puts the text back in the textbox for editing, and restores the synth state. ESC key or a cancel (X) button in the textbox area undoes the edit action, restoring all removed messages.

## Design: Edit Mode State Machine

**States:**
- **Normal mode**: current behavior, no edit in progress
- **Edit mode**: user clicked restore, messages truncated, text in textbox, cancel available

**Transitions:**
- Normal → Edit: user clicks restore button on a user message
- Edit → Normal (submit): user presses Enter / clicks Send — submit the (possibly edited) message, discard saved state
- Edit → Normal (cancel): user presses ESC or clicks cancel (X) — restore all saved messages/checkpoints/synth state

**Saved state during edit mode** (new struct `EditModeSnapshot`):
- `std::vector<ChatMessage> saved_messages` — full message list before truncation
- `std::vector<ChatCheckpoint> saved_checkpoints` — full checkpoint list
- `int saved_api_history_size` — API history size before truncation
- `File saved_synth_checkpoint` — synth state file before edit (to restore on cancel)

## Changes

### 1. Add edit mode state — `side_panel.h`
```cpp
struct EditModeSnapshot {
    std::vector<ChatMessage> saved_messages;
    std::vector<ChatCheckpoint> saved_checkpoints;
    int saved_api_history_size = 0;
    File saved_synth_checkpoint;
};
```
- Add `bool edit_mode_ = false;`
- Add `std::unique_ptr<EditModeSnapshot> edit_snapshot_;`
- Add cancel button: `std::unique_ptr<OpenGlToggleButton> cancel_edit_button_;`
- Add `void enterEditMode(int message_index);`
- Add `void cancelEditMode();`
- Add `bool isInEditMode() const;`
- Override `textEditorEscapeKeyPressed(TextEditor&)` (already a `TextEditor::Listener`)

### 2. Modify `mouseUp()` — `side_panel.cpp` (~line 1153)
- Remove `AlertWindow::showOkCancelBox` confirmation dialog
- Instead call `enterEditMode(idx)` which notifies listeners

### 3. Implement `enterEditMode()` — `side_panel.cpp`
1. Save snapshot: copy `messages_`, `checkpoints_`, get API history size via listener callback
2. Grab text from `messages_[idx].text`
3. Call `l->sidePanelRestoreRequested(idx)` — this truncates messages, restores synth, truncates API history
4. Set textbox text to saved user message text, focus it
5. Set `edit_mode_ = true`, show cancel button
6. Change placeholder text to "Edit your message or press Esc to cancel"

### 4. Implement `cancelEditMode()` — `side_panel.cpp`
1. Restore `messages_` and `checkpoints_` from snapshot
2. Call listener to restore synth state from `saved_synth_checkpoint` and restore API history size
3. Clear textbox, hide cancel button
4. Set `edit_mode_ = false`, discard snapshot
5. `layoutMessages()`, `repaintBackground()`

### 5. Handle ESC key — `side_panel.cpp`
- Override `textEditorEscapeKeyPressed()`: if `edit_mode_`, call `cancelEditMode()`

### 6. Handle submit during edit mode — `side_panel.cpp`
- In `submitMessage()`: if `edit_mode_`, set `edit_mode_ = false`, discard snapshot, hide cancel button, then proceed with normal submit

### 7. Cancel edit button — `side_panel.cpp`
- Create `cancel_edit_button_` (X button) positioned at top-right of textarea
- Initially hidden, shown only during edit mode
- In `buttonClicked()`: if cancel button clicked, call `cancelEditMode()`
- In `resized()`: position it overlapping the top-right corner of `prompt_editor_`

### 8. Add listener methods for edit mode — `side_panel.h`
- Add `virtual int sidePanelGetApiHistorySize() { return 0; }` to Listener
- Add `virtual void sidePanelCancelEditRequested(const File& checkpoint, int api_history_size) {}` to Listener

### 9. Implement cancel restore in `full_interface.cpp`
- `sidePanelCancelEditRequested()`: load synth state from the saved checkpoint file, restore API history size, update GUI
- `sidePanelGetApiHistorySize()`: return `ClaudeApiClient::instance().getHistorySize()`

### 10. Modify `sidePanelRestoreRequested()` — `full_interface.cpp` (~line 1219)
- Use the user message's own checkpoint (not remap to next system message)
- Truncate messages to `message_index` (removes the user message itself)
- Rest stays the same

## Files to Modify
- `src/interface/editor_sections/side_panel.h` — edit mode state, new methods, cancel button, listener additions
- `src/interface/editor_sections/side_panel.cpp` — `mouseUp()`, `enterEditMode()`, `cancelEditMode()`, ESC handler, submit changes, cancel button setup
- `src/interface/editor_sections/full_interface.h` — override new listener methods
- `src/interface/editor_sections/full_interface.cpp` — implement cancel restore, modify `sidePanelRestoreRequested()`

## Verification
1. Build: `cmd.exe /c "cd /d C:\Users\anuvc\Documents\Code\Workspace\synth\vital && build_windows.bat --skip-regenerate --no-run"`
2. Test edit flow: hover user message → click restore → text appears in textbox, messages truncated, cancel (X) visible
3. Test cancel: press ESC or click X → all messages restored, textbox cleared, synth state restored
4. Test submit: edit text → press Enter → new message sent, old messages stay removed
5. Test submit without editing: click restore → immediately press Enter → same as retry
