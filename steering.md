# Vital project steering

## Core Information

- In the subfolder `vital` we have the codebase for open source synthesizer Vital, which is built using JUCE.

## Latest Updates

- We recently added a sidepanel (via `side_panel.cpp`) where we will add functionality next
- We added a textarea and a button to the sidepanel at the bottom


## Key Learnings & Common Issues

- **Adding new UI sections requires two steps**:
  - **Naming conflicts**: JUCE has built-in classes like `juce::SidePanel`. Naming your class `SidePanel` causes "reference to 'SidePanel' is ambiguous" errors. Solution: prefix with `Vital` (e.g., `VitalSidePanel`).
  - **Unity builds**: This project uses unity builds - `.cpp` files have `compile="0"` in `vital.jucer` and are NOT compiled directly. Instead, they're `#include`d in aggregate files under `src/unity_build/`. If you see "Undefined symbol: ClassName::ClassName()" linker errors, add `#include "your_file.cpp"` to the appropriate unity build file (e.g., `interface_editor_sections.cpp` for editor sections).

- **OpenGlTextEditor setup order matters**: When using `OpenGlTextEditor` (multiline textarea):
  - Call `setMultiLine(true, true)` AFTER `addOpenGlComponent(editor->getImageComponent())`, not before. Otherwise triggers `VITAL_ASSERT(false)` in `OpenGlComponent::findValue()` because the image component has no parent yet.
  - Root cause: `setMultiLine()` can trigger `resized()` which calls `image_component_.findValue(Skin::kLabelBackgroundRounding)` - fails if parent not set.
  - For multiline editors, must explicitly call `setFont()` - the auto-font in `visibilityChanged()` only applies to single-line.
  - Must call `redoImage()` after setting colors/placeholder text to update the OpenGL texture.
  - Reference working examples: `SaveSection::setTextColors()`, `PresetBrowser` comments setup.

