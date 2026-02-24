---
name: Side Panel Button Rearchitect
overview: "Consolidate the bottom VOICE CHAT and SEND buttons into inline textarea controls: a dual-purpose circular button (mic/send) in the bottom-right of the textarea, and a VOICE CHAT button to the left of it inside the textarea."
todos:
  - id: add-send-icon
    content: Add Paths::sendArrowIcon() to paths.h - an up-pointing arrow for the send button
    status: completed
  - id: add-members
    content: "Add new members to side_panel.h: action_circle_bg_, send_icon_shape_, action_button_is_send_, action_button_bounds_, textEditorTextChanged override, updateActionButtonState()"
    status: completed
  - id: constructor
    content: "Update constructor in side_panel.cpp: create action_circle_bg_ (purple circle), send_icon_shape_ (arrow icon); hide old action_button_ and repurpose voice_chat_button_"
    status: completed
  - id: resized
    content: "Rewrite resized() layout: remove bottom button row, extend textarea to bottom of window (minus padding) to absorb freed space, position circular action button and voice chat button inside textarea area"
    status: completed
  - id: text-changed
    content: Implement textEditorTextChanged() and updateActionButtonState() to swap mic/send icon based on textarea content
    status: completed
  - id: mouse-events
    content: Update mouseUp/mouseMove/mouseExit to handle the new circular action button hit area (send or mic depending on state)
    status: completed
  - id: cleanup
    content: Remove or hide old button references, update voice chat recording indicator positioning, verify all existing functionality preserved
    status: in_progress
isProject: false
---

# Side Panel Button Rearchitect

## Current State

The side panel bottom area currently has:

1. **Text area** (180px tall) with a small mic icon overlay at bottom-right and a cancel-edit X at top-right
2. **Two large buttons** below the textarea: `VOICE CHAT` (60% width) and `SEND` (40% width), each 50px tall
3. The mic icon overlay at bottom-right of textarea triggers "talk mode" (auto-stop on silence)

## Target State

Remove the two large bottom buttons entirely. Move their functionality **inside** the textarea:

1. **Bottom-right of textarea: Dual-purpose circular button** (mic icon / send arrow)
  - When textarea is **empty**: shows microphone icon on a purple circle background -- clicking triggers talk recording (same as current mic icon behavior)
  - When textarea **has text**: instantly switches to an **up-arrow send icon** on the same purple circle -- clicking sends the message (same as current SEND button)
  - Purple background = `Skin::kUiActionButton` color, rendered as `OpenGlQuad` with `kCircleFragment` shader
  - Same mic icon (`Paths::microphoneIcon2()`) and size as current
  - Hover/press states: opacity/color changes matching current button conventions
  - Recording indicator (red dot) still appears at top-right of the button when recording
2. **Left of the circular button: VOICE CHAT button** (inside the textarea)
  - A smaller, inline text button reading "VOICE CHAT" (same label as current)
  - Positioned to the left of the circular mic/send button, at the bottom of the textarea
  - Same toggle behavior: click to start voice chat, shows "STOP" when active
3. **Removed elements:**
  - `action_button_` (the big SEND button) -- removed from layout (or hidden permanently)
  - The old `voice_chat_button_` large button at bottom -- removed from layout (or hidden permanently)
  - The old `mic_icon_shape_` overlay at bottom-right -- replaced by the new dual-purpose button
  - The old `voice_chat_recording_indicator_` that sat above the old VOICE CHAT button -- repositioned to the new location

## Files to Change

### [side_panel.h](src/interface/editor_sections/side_panel.h)

- Add `textEditorTextChanged(TextEditor&)` override to detect when to swap mic/send icon
- Add new member: `std::unique_ptr<OpenGlQuad> action_circle_bg`_ (purple circle background for the dual-purpose button)
- Add new member: `std::unique_ptr<PlainShapeComponent> send_icon_shape`_ (up-arrow icon for send mode)
- Add helper: `void updateActionButtonState()` -- checks if textarea has text, swaps between mic icon and send icon, updates the circle background color for hover
- Add tracking bool: `bool action_button_is_send_ = false` to know which mode the button is in
- Add bounds tracking: `Rectangle<int> action_button_bounds`_ for hit testing the circular button

### [side_panel.cpp](src/interface/editor_sections/side_panel.cpp)

**Constructor changes:**

- Create `action_circle_bg`_ as `OpenGlQuad(Shaders::kCircleFragment)` with purple color from `Skin::kUiActionButton`
- Create `send_icon_shape`_ as `PlainShapeComponent` with a new `Paths::sendArrowIcon()` (up arrow in circle)
- Keep `mic_icon_shape`_ but repurpose it as the mic icon for the dual-purpose button
- Remove `action_button`_ text label setup (or just hide the button permanently)
- Hide `voice_chat_button_`'s old large layout (repurpose as smaller inline)

`**resized()` changes:**

- Remove the bottom button row layout (lines ~483-501 for VOICE CHAT and SEND buttons)
- **Textarea now extends to the bottom of the window** (minus padding). Currently the textarea ends at `button_y - margin` and the buttons occupy `button_y` to `getHeight() - padding`. With the buttons gone, the textarea bottom edge becomes `getHeight() - padding`, giving it roughly 50px + margin more vertical space.
- Position the circular action button (purple circle bg + mic/send icon) at bottom-right inside the textarea area, with small padding from edges
- Position the VOICE CHAT button to the left of the circular button, inside the textarea, at the bottom
- Position recording indicators relative to the new button positions

`**textEditorTextChanged()` (new):**

- Call `updateActionButtonState()` to swap between mic/send mode

`**updateActionButtonState()` (new):**

- Check `prompt_editor_->getText().isEmpty()`
- If empty: show `mic_icon_shape_`, hide `send_icon_shape_`, set `action_button_is_send_ = false`
- If not empty: hide `mic_icon_shape_`, show `send_icon_shape_`, set `action_button_is_send_ = true`

`**mouseUp()` changes:**

- Update the mic icon click handler to use `action_button_bounds_` instead of `mic_icon_bounds_`
- When `action_button_is_send_` is true, call `submitMessage()` instead of toggling recording

`**mouseMove()` changes:**

- Track hover state over `action_button_bounds_` instead of old `mic_icon_bounds_`
- Update hover appearance (purple circle lightens on hover)

`**buttonClicked()` changes:**

- Keep voice chat button handling, just the button is repositioned

### [paths.h](src/interface/look_and_feel/paths.h)

- Add `static Path sendArrowIcon()` -- an up-pointing arrow icon (simple arrow/chevron pointing up, suitable for a send button). This will be an SVG path or programmatic path similar to the existing icon style.

## Layout Sketch

The textarea now sits at the very bottom of the panel (minus padding), absorbing the ~60px previously used by the button row. The buttons live *inside* the textarea.

```
+-------------------------------------------+
|  SOUND DESIGNER                      [x]  |
+-------------------------------------------+
|                                           |
|  (chat messages area)                     |
|                                           |
+-------------------------------------------+
|  Describe your synth patch...             |
|                                           |
|                                           |
|                                           |
|                                           |
|  [VOICE CHAT]                    (O mic)  |  <-- bottom of window (padding only below)
+-------------------------------------------+
   ^-- textarea extends to bottom edge
```

When text is present:

```
|  Here is my typed message...              |
|                                           |
|                                           |
|                                           |
|                                           |
|  [VOICE CHAT]                    (O ^  )  |  <-- send arrow replaces mic
+-------------------------------------------+
```

