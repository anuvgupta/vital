# Vital project steering

## Core Information

- In the subfolder `vital` we have the codebase for open source synthesizer Vital, which is built using JUCE.

## Latest Updates

- We recently added a sidepanel (via `side_panel.cpp`) where we will add functionality next
- We added a textarea and a button to the sidepanel at the bottom


## Key Learnings & Common Issues

- **OpenGlTextEditor setup order matters**: When using `OpenGlTextEditor` (multiline textarea):
  - Call `setMultiLine(true, true)` AFTER `addOpenGlComponent(editor->getImageComponent())`, not before. Otherwise triggers `VITAL_ASSERT(false)` in `OpenGlComponent::findValue()` because the image component has no parent yet.
  - Root cause: `setMultiLine()` can trigger `resized()` which calls `image_component_.findValue(Skin::kLabelBackgroundRounding)` - fails if parent not set.
  - For multiline editors, must explicitly call `setFont()` - the auto-font in `visibilityChanged()` only applies to single-line.
  - Must call `redoImage()` after setting colors/placeholder text to update the OpenGL texture.
  - Reference working examples: `SaveSection::setTextColors()`, `PresetBrowser` comments setup.

