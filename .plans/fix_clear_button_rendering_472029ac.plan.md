---
name: Fix clear button rendering
overview: "The clear button's OpenGL background still renders because `renderTextButton()` has a bug where `kJustText` style check is unreachable when text is inactive, and `setAlpha(0.0f)` has no effect on OpenGL rendering. The fix is to follow the proven action_button_ pattern: hide the toggle button entirely and handle clicks via manual hit testing."
todos:
  - id: revert-constructor
    content: Revert clear_button_ constructor to hide it entirely (setVisible(false), setBounds(0,0,0,0)), remove setNoBackground/setAlpha
    status: completed
  - id: add-members
    content: Add clear_button_bounds_ and clear_button_hovered_ members to side_panel.h
    status: completed
  - id: update-resized
    content: "In resized(): remove clear_button_ bounds/text setup, store circle bounds in clear_button_bounds_"
    status: completed
  - id: update-layout
    content: "In layoutMessages(): only toggle circle/icon active state, remove clear_button_->setVisible()"
    status: completed
  - id: add-mouseup
    content: "In mouseUp(): add hit test for clear_button_bounds_ -> clearChat()"
    status: completed
  - id: add-hover
    content: "In mouseMove()/mouseExit(): add hover detection for clear circle, update cursor"
    status: completed
  - id: cleanup-buttonclicked
    content: Remove clear_button_ branch from buttonClicked()
    status: completed
isProject: false
---

# Fix Clear Button Rendering

## Root Cause

The rendering pipeline works as follows:

1. `addButton()` in [synth_section.cpp](src/interface/editor_sections/synth_section.cpp) registers the button's `OpenGlButtonComponent` into `open_gl_components`_
2. `renderOpenGlComponents()` iterates that list and calls `render()` on every component where `isVisible()` is true -- it does **not** check alpha
3. `OpenGlButtonComponent::renderTextButton()` in [synth_button.cpp](src/interface/editor_components/synth_button.cpp) has a bug: when text is inactive, it renders the background quad **before** checking if the style is `kJustText`:

```cpp
if (!text_.isActive()) {
    background_.setColor(active_color);
    background_.render(open_gl, animate);  // ALWAYS renders
    return;  // Returns BEFORE the kJustText check below
}
if (style_ != kJustText) { ... }  // Never reached when text inactive
```

So `setAlpha(0.0f)` and `setNoBackground()` both fail -- the rounded rect always draws when the button is visible.

## Solution: Follow the action_button_ Pattern

The existing `action_button`_ is successfully hidden by setting `setBounds(0,0,0,0)` + `setVisible(false)`, with clicks handled manually in `mouseUp()`. Apply the same approach to `clear_button_`.

### Changes in [side_panel.cpp](src/interface/editor_sections/side_panel.cpp)

**Constructor:** Revert `clear_button`_ to minimal setup -- no `setNoBackground()`, no `setAlpha()`. Set it invisible from the start (just like `action_button_`):

```cpp
clear_button_ = std::make_unique<OpenGlToggleButton>("Clear");
addButton(clear_button_.get());
clear_button_->setVisible(false);
clear_button_->setBounds(0, 0, 0, 0);
```

`**resized()`:** Remove clear_button_ bounds/text sizing. Keep only the circle bg and X icon positioning. Store the circle bounds in a member variable (`clear_button_bounds`_) for hit testing.

`**layoutMessages()`:** Remove `clear_button_->setVisible(has_user_messages)` since the toggle button stays permanently hidden. Only toggle `clear_circle_bg_->setActive()` and `clear_x_icon_->setActive()`.

`**mouseUp()`:** Add hit testing for the clear circle (before the action button check):

```cpp
if (!clear_button_bounds_.isEmpty() && clear_button_bounds_.contains(pos)) {
    clearChat();
    return;
}
```

`**mouseMove()`:** Add hover detection for the clear circle to change cursor to pointing hand.

`**buttonClicked()`:** Remove the `clear_button_` branch (no longer needed since clicks go through mouseUp).

### Changes in [side_panel.h](src/interface/editor_sections/side_panel.h)

- Add `Rectangle<int> clear_button_bounds_;` member
- Add `bool clear_button_hovered_ = false;` member (for hover state/cursor)

