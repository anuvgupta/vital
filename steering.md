# Vital Project Steering


## Core Information

- In the subfolder `vital` we have the codebase for open source synthesizer Vital, which is built using JUCE.
- Vital is a spectral warping wavetable synthesizer with three oscillators, a sampler, and an extensive modulation matrix, using JSON-based .vital preset files that store wavetable data.
- JUCE is a widely used framework for audio application and plug-in development, open source C++ codebase, for standalone software on cross-platform, and VST, AU, etc. plug-ins.


## Project Proposal

- We are building an AI agent/chatbot panel for Vital synth, where the user can describe a synth sound or a modification to a parameter/knob on the synthesizer in natural language. The chatbot will then generate a new preset or update the current preset with the desired settings.
- Users primarily will give technical descriptions of parameters/settings to tweak, ie specific settings and numerical values: "increase the filter cutoff a bit, no more than 5%". This should be possible with knowledge of the codebase and maybe a handbook on sound design & the Vital software manual itself.
- In future we can add support for non-technical descriptions, ie. "make it more dreamy" or "i want a mario video game blippy chiptuney coin sound".
- Target audience is music producers, both professional and amateur


## Latest Updates

- We drafted a document outlining the preset format/schema, based on the Vital codebase and some example presets: `vital/preset_schema.md`
    - We learned that waveforms can be stored as "Wave Source" (base64, not really LLM-friendly) OR "Line Source" (control points / curves, very LLM-friendly). We will prefer line source for preset generation. We will deal with wave source later.
- We recently added a sidepanel (via `side_panel.cpp`) where we will continue to add functionality
- We added a textarea and a button to the sidepanel, near the bottom


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

