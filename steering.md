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
- We created a build script `vital/build_macos.sh` because we are developing on MacOS. This runs Projucer CLI to build the project to MacOS (Xcode) and other targets. Then it uses Xcode CLI to run the debug app. We can use this script with `--no-run` argument to verify that new changes build/compile successfully.
- We added a sidepanel (via `side_panel.cpp`) where we will continue to add functionality
- We added a textarea and a button to the sidepanel, near the bottom
- We implemented a chat interface with scrollable message area, user message bubbles, and "Thinking..." indicator

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

- **Vital uses OpenGL-only rendering - standard JUCE paint() doesn't work**:
    - Vital's UI is rendered entirely via OpenGL. Standard JUCE `Component::paint()` methods on child components **do not get called**.
    - If you add a child Component with `addAndMakeVisible()` and implement `paint()`, it will NOT render.
    - **Solution for dynamic UI content**: Draw directly in `paintBackground()` which IS called during the OpenGL render cycle (it renders to a texture).
    - For scrollable content, handle scrolling manually with scroll position tracking rather than using `juce::Viewport`.
    - Reference: Our chat message implementation in `side_panel.cpp` uses `paintChatMessages()` called from `paintBackground()`.

- **Creating OpenGL components dynamically causes crashes**:
    - `OpenGlQuad`, `PlainTextComponent`, and other OpenGL components require shader initialization in the OpenGL context.
    - Creating these dynamically (e.g., when user submits a message) and trying to render them causes `EXC_BAD_ACCESS` because shaders aren't initialized yet.
    - The shaders get initialized during the render cycle via `init(OpenGlWrapper&)`, but if you try to use the component before that, it crashes.
    - **Solution**: Either pre-allocate OpenGL components at startup (like `ModulationMatrix` does with rows), or use direct `Graphics` drawing in `paintBackground()` instead.

- **TextEditor::Listener for Enter key handling**:
    - Implement `TextEditor::Listener` and override `textEditorReturnKeyPressed()` to handle Enter key submission.
    - Set `setReturnKeyStartsNewLine(false)` so Enter submits instead of creating a newline (users can use Shift+Enter for newlines).

## Key Files Reference

**Core Serialization:**

- [load_save.cpp](vital/src/common/load_save.cpp) - JSON serialization/deserialization
- [synth_parameters.cpp](vital/src/common/synth_parameters.cpp) - All parameter definitions with ranges
- [synth_constants.h](vital/src/common/synth_constants.h) - Numeric constants
- [synth_strings.h](vital/src/interface/look_and_feel/synth_strings.h) - String values for enums

**Line Generator (LFOs and Line Source wavetables):**

- [line_generator.cpp](vital/src/common/line_generator.cpp) - Line shape format and built-in waveform definitions
- [line_generator.h](vital/src/common/line_generator.h) - LineGenerator class with initSaw, initSquare, etc.

**Wavetables:**

- [wave_line_source.cpp](vital/src/common/wavetable/wave_line_source.cpp) - **Line Source component (PREFERRED)**
- [wave_line_source.h](vital/src/common/wavetable/wave_line_source.h) - Line Source class definition
- [wave_source.cpp](vital/src/common/wavetable/wave_source.cpp) - Wave Source component (base64 encoded)
- [wavetable_creator.cpp](vital/src/common/wavetable/wavetable_creator.cpp) - Wavetable rendering and JSON handling
- [wavetable_component_factory.cpp](vital/src/common/wavetable/wavetable_component_factory.cpp) - Component type registry
- [wavetable_group.cpp](vital/src/common/wavetable/wavetable_group.cpp) - Default wavetable creation

**Samples:**

- [sample_source.cpp](vital/src/synthesis/producers/sample_source.cpp) - Sample data format

**UI / Interface:**

- [full_interface.h/cpp](vital/src/interface/editor_sections/full_interface.cpp) - Main UI container, manages all sections and layout
- [synth_section.h/cpp](vital/src/interface/editor_sections/synth_section.h) - Base class for all UI sections, includes `paintBackground()` for OpenGL rendering
- [synth_button.h](vital/src/interface/editor_components/synth_button.h) - OpenGlToggleButton, SynthButton components
- [side_panel.h/cpp](vital/src/interface/editor_sections/side_panel.cpp) - **Our custom AI chat panel (VitalSidePanel)** with chat messages, scrolling, Enter key handling
- [open_gl_image_component.h](vital/src/interface/editor_components/open_gl_image_component.h) - OpenGlTextEditor, PlainTextComponent, OpenGlAutoImageComponent
- [open_gl_multi_quad.h](vital/src/interface/editor_components/open_gl_multi_quad.h) - OpenGlQuad (rounded rectangles), OpenGlScrollBar
- [open_gl_component.h/cpp](vital/src/interface/editor_components/open_gl_component.cpp) - Base OpenGL component, parent/findValue system
- [modulation_matrix.h/cpp](vital/src/interface/editor_sections/modulation_matrix.cpp) - Reference for scrollable lists with OpenGL (pre-allocated rows pattern)
- [save_section.cpp](vital/src/interface/editor_sections/save_section.cpp) - Reference for OpenGlTextEditor setup patterns
- [preset_browser.cpp](vital/src/interface/editor_sections/preset_browser.cpp) - Reference for multiline text editor setup

**Build System:**

- [interface_editor_sections.cpp](vital/src/unity_build/interface_editor_sections.cpp) - Unity build file for editor sections
