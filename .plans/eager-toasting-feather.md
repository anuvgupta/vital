# Replace SPEAK Button with Mic Icon Overlay on Textarea

## Context
The SPEAK button currently takes up space in the bottom button row alongside VOICE CHAT and SEND. We want to move the speak/talk functionality into a microphone icon that overlays the bottom-right corner of the textarea, freeing up space so SEND can expand to fill the width previously shared with SPEAK. VOICE CHAT remains as a separate button next to SEND.

## Changes

### 1. Add mic icon to `Paths` (`src/interface/look_and_feel/paths.h`)
- Add a `static Path microphoneIcon()` method with an inline SVG microphone path (similar pattern to `restoreIcon()`)

### 2. Remove talk button, add mic icon overlay (`src/interface/editor_sections/side_panel.h`)
- Remove `talk_button_` (`OpenGlToggleButton`)
- Remove `talk_recording_indicator_` (`OpenGlQuad`)
- Add `mic_icon_overlay_` — a small custom component (or `OpenGlQuad`) positioned at bottom-right of textarea
- Add `mic_icon_hovered_` bool for hover state tracking
- Add `mic_icon_recording_` bool (or reuse `recording_mode_ == kRecordingTalk`)

### 3. Update layout and behavior (`src/interface/editor_sections/side_panel.cpp`)

**Constructor:**
- Remove `talk_button_` and `talk_recording_indicator_` creation
- Create mic icon overlay component — use an `OpenGlImageComponent` that we paint a mic path + optional red dot onto, positioned as a child overlapping the textarea's bottom-right

**`resized()`:**
- Remove talk button positioning
- Change button row to two buttons: VOICE CHAT (left ~half) | SEND (right ~half)
  - SEND expands to fill the space previously shared with SPEAK
- Position mic icon overlay at bottom-right of textarea bounds:
  - Size: ~24x24 (scaled by `size_ratio_`)
  - Position: `textarea_x + textarea_width - icon_size - padding`, `textarea_y + textarea_height - icon_size - padding`

**`buttonClicked()`:**
- Remove `talk_button_` click handling

**Mic icon interaction (new):**
- Override `mouseMove()`/`mouseEnter()`/`mouseExit()` to track hover over the mic icon bounds
- Override `mouseDown()` to detect clicks on the mic icon bounds
- On click: if not recording, call `startTalkRecording()`; if recording talk, call `stopRecording()`
- Repaint mic icon on hover/recording state changes

**Mic icon rendering:**
- Draw the microphone `Path` from `Paths::microphoneIcon()`
- Default state: white at ~0.5 alpha
- Hover state: white at ~0.85 alpha
- Recording state: draw a small red filled circle (8x8) overlapping the icon's top-right corner (same red dot style as current `talk_recording_indicator_`)

**`stopRecording()`:**
- Remove references to `talk_button_` text/color updates and `talk_recording_indicator_`
- Instead trigger repaint of the mic icon overlay area

**`updateTalkButtonColors()`:**
- Remove entirely (no longer needed)

### 4. Update `startTalkRecording()` / `stopRecording()`
- Replace `talk_button_` text toggling with mic icon state update + repaint
- Replace `talk_recording_indicator_->setActive()` with repaint of mic overlay area

## Files to Modify
- `src/interface/look_and_feel/paths.h` — add `microphoneIcon()`
- `src/interface/editor_sections/side_panel.h` — remove talk button members, add mic overlay members
- `src/interface/editor_sections/side_panel.cpp` — all layout/behavior changes

## Implementation Approach
Rather than creating a separate child component, use **direct hit-testing on the side panel** — track mic icon bounds as a `Rectangle<int>`, paint the icon in `paint()` or `paintOverChildren()`, and handle mouse events by checking if clicks/hovers fall within that rectangle. This matches the existing pattern used for the restore icon on chat messages (painted directly, hit-tested in `mouseDown`). The red recording dot can be drawn directly alongside the mic icon path.

## Verification
- Build on Windows: `cmd.exe /c "cd /d C:\Users\anuvc\Documents\Code\Workspace\synth\vital && build_windows.bat --skip-regenerate --no-run"`
- Visual check: mic icon visible at bottom-right of textarea, dims when not hovered, brightens on hover
- Click mic icon → recording starts, red dot appears on icon
- Click again → recording stops, red dot disappears
- SEND button spans full width (minus VOICE CHAT)
- VOICE CHAT button unchanged
- No regressions in voice chat recording flow
