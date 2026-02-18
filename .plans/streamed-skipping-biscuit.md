# Add Cmd+K / Ctrl+K Shortcut to Focus Chat Input

## Context
When using the synth, after clicking on knobs or other UI elements, keyboard focus moves away from the chat input. The user wants a quick shortcut (Cmd+K on macOS, Ctrl+K on Windows/Linux) to refocus the chat prompt editor without needing to click on it.

## Approach
Handle `keyPressed` at the `FullInterface` level so it works in both standalone and plugin contexts. The `FullInterface` component is the shared top-level UI in both modes.

### Changes

#### 1. `src/interface/editor_sections/side_panel.h` — Add public focus method
Add a `focusPromptEditor()` method to `VitalSidePanel`:
```cpp
void focusPromptEditor();
```

#### 2. `src/interface/editor_sections/side_panel.cpp` — Implement focus method
```cpp
void VitalSidePanel::focusPromptEditor() {
  if (prompt_editor_)
    prompt_editor_->grabKeyboardFocus();
}
```

#### 3. `src/interface/editor_sections/full_interface.h` — Override `keyPressed`
Add `keyPressed` override to `FullInterface`:
```cpp
bool keyPressed(const KeyPress& key, Component* originatingComponent) override;
```
Note: `SynthSection` inherits from `Component` which has `keyPressed`. We can override it directly.

#### 4. `src/interface/editor_sections/full_interface.cpp` — Implement shortcut
```cpp
bool FullInterface::keyPressed(const KeyPress& key, Component* originatingComponent) {
  if (key == KeyPress('k', ModifierKeys::commandModifier, 0)) {
    if (side_panel_ && side_panel_->isVisible())
      side_panel_->focusPromptEditor();
    return true;
  }
  return SynthSection::keyPressed(key, originatingComponent);
}
```

#### 5. Ensure `FullInterface` receives key events
`FullInterface` needs `setWantsKeyboardFocus(true)` so it can intercept keys. Check if this is already set; if not, add it in the constructor.

### Standalone note
The standalone `MainWindow` already uses `ApplicationCommandManager` for Cmd+S/O/etc. Since we're putting this in `FullInterface::keyPressed`, it will be checked when FullInterface or any child has focus. The `ApplicationCommandManager`'s `KeyMappings` listener fires first for registered commands, but since Cmd+K is not registered there, it will fall through to component key handlers.

However — if focus is on a completely different component (like a slider), the key event goes to that component first. JUCE propagates `keyPressed` up the component hierarchy, so as long as no intermediate component consumes Cmd+K, it will reach `FullInterface`. This should work since sliders/knobs don't consume Cmd+K.

## Files to Modify
1. `src/interface/editor_sections/side_panel.h` — add `focusPromptEditor()` declaration
2. `src/interface/editor_sections/side_panel.cpp` — implement `focusPromptEditor()`
3. `src/interface/editor_sections/full_interface.h` — add `keyPressed` override
4. `src/interface/editor_sections/full_interface.cpp` — implement Cmd+K handler

## Verification
- Build on Windows: `cmd.exe /c "cd /d C:\Users\anuvc\Documents\Code\Workspace\synth\vital && build_windows.bat --skip-regenerate --no-run"`
- Test: Click a knob to move focus away, then press Ctrl+K — chat prompt should receive focus
- Test: Type text after Ctrl+K — text should appear in the chat prompt editor
