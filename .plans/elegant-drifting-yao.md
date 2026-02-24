# Voice Chat Button Behavior Refactor

## Context
Currently, when the user clicks the "VOICE CHAT" button, that button itself transforms into a "STOP" button with a recording indicator. The user wants the behavior to mirror talk mode: clicking "VOICE CHAT" should make the voice chat button **disappear** and the **action button** (the circular mic/send/stop button) should become a stop button with the recording indicator. When stop is clicked, remaining text is sent (same as current behavior) and the voice chat button reappears.

## Changes — `side_panel.cpp`

### 1. `updateActionButtonState()` (~line 1156)
Change the mode selection logic so voice chat recording **also** triggers `kActionStop`:
```
- bool is_talk_recording = (recording_mode_ == kRecordingTalk);
+ bool is_recording = (recording_mode_ == kRecordingTalk || recording_mode_ == kRecordingVoiceChat);
```
And use `is_recording` instead of `is_talk_recording` for the stop condition.

### 2. `startVoiceChatRecording()` (~line 837-842)
Instead of changing the voice chat button text to "STOP" and showing its indicator:
- **Hide** the voice chat button: `voice_chat_button_->setVisible(false)`
- **Show** the action button's recording indicator: `mic_recording_indicator_->setActive(true)`
- Call `updateActionButtonState()` (which will now set `kActionStop` for voice chat mode too)
- Remove the lines that set voice chat button text to "STOP" and activate `voice_chat_recording_indicator_`

### 3. `stopRecording()` — voice chat branch (~line 892-896)
Instead of restoring voice chat button text:
- **Show** the voice chat button: `voice_chat_button_->setVisible(true)`
- Restore its text to `kVoiceChatButtonLabel` (keep this for safety)
- Deactivate `voice_chat_recording_indicator_` (keep, for safety)
- The `mic_recording_indicator_->setActive(false)` on line 914 already handles the action button indicator

### 4. Action button click handler (~line 1568-1574)
The existing `kActionStop` handler calls `stopRecording()` — this already works for both modes since `stopRecording()` handles both `kRecordingTalk` and `kRecordingVoiceChat`. No change needed here.

### 5. `resized()` voice chat button layout (~line 580-601)
The `is_stop` sizing logic can be simplified since the button will be hidden during recording. But we should keep it for robustness. The key change: the button visibility is already handled by `setVisible()`.

### 6. Action button mic click (~line 1570-1573)
Currently when clicking mic while voice chat is active, it stops voice chat then starts talk. Since the voice chat button is now hidden during recording, the action button will be in stop mode — so clicking it calls `stopRecording()` via the `kActionStop` branch. This is correct behavior.

## Files to Modify
- `src/interface/editor_sections/side_panel.cpp` — all changes in this single file

## Verification
1. Build the project using the Windows build script
2. Test: Click "VOICE CHAT" → button should disappear, action button becomes stop with red indicator
3. Test: Click stop → recording stops, remaining text sent, voice chat button reappears
4. Test: Silence timeout → same behavior as clicking stop
5. Test: Talk mode still works as before (mic → stop → mic)
6. Test: Action button shows send mode when text is typed during voice chat (actually no — it should show stop during voice chat regardless of text)
