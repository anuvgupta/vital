# Vital Project Steering

## Core Information
- In the current base folder/repository, we have the codebase for open source synthesizer Vital, which is built using JUCE.
- Vital is a spectral warping wavetable synthesizer with three oscillators, a sampler, and an extensive modulation matrix, using JSON-based .vital preset files that store wavetable data.
- JUCE is a widely used framework for audio application and plug-in development, open source C++ codebase, for standalone software on cross-platform, and VST, AU, etc. plug-ins.
- JUCE version we are using is JUCE 6

## Code guidelines
- When committing changes, include any updates in `STEERING.md` file and `.agents` folder, as well as other docs: `TROUBLESHOOTING.md`, `CHANGELOG.md`, `TODO.md`
- Don't include co-author line on commits, ie. `Co-Authored-By: Claude Opus 4.5 <noreply@anthropic.com>"` - leave this out, not necessary for commit messages
- Claude API model selection
    - NEVER use Opus 4 (`claude-opus-4-*`) rather than Opus 4.5. Opus 4, meaning 4.0 or any version between/including 4.0 and 4.4, are extremely expensive compared to Opus 4.5 or Sonnet. Use Opus 4.5 (`claude-opus-4-5-*`) if you need the highest capability tier.
    - Default model should be Opus 4.5 or Sonnet 4.5. Constants are in `claude_api_client.cpp`.

## Project Proposal
- We are building an AI agent/chatbot panel for Vital synth, where the user can describe a synth sound or a modification to a parameter/knob on the synthesizer in natural language. The chatbot will then generate a new preset or update the current preset with the desired settings.
- Users primarily will give technical descriptions of parameters/settings to tweak, ie specific settings and numerical values: "increase the filter cutoff a bit, no more than 5%". This should be possible with knowledge of the codebase and maybe a handbook on sound design & the Vital software manual itself.
- In future we can add support for non-technical descriptions, ie. "make it more dreamy" or "i want a mario video game blippy chiptuney coin sound".
- Target audience is music producers, both professional and amateur

## Open Tasks
**Please see `TODO.md` for list of current and closed tasks.**

## Latest Updates
**Please see `CHANGELOG.md` for list of latest updates.**

## Key Learnings & Common Issues
**Please see `TROUBLESHOOTING.md` for key learnings and common issues.**

## Core Architecture

### Original Vital Synth

**Synthesis Engine:** Vital is a spectral warping wavetable synth with 3 oscillators, a sampler, filter routing, effects chain, and a flexible modulation matrix. The synthesis code lives in `src/synthesis/` with producers (oscillators, sample source), processors (filters, effects), and a voice/polyphony framework.

**Preset System:** Presets are JSON files (`.vital` extension) serialized via `load_save.cpp` using nlohmann JSON. Each preset contains all parameter values plus embedded wavetable data. Wavetables can be stored as "Wave Source" (base64-encoded raw samples) or "Line Source" (control points and curves -- much more compact and LLM-friendly). Parameters are defined in `synth_parameters.cpp` with min/max ranges and scaling types (linear, quadratic, exponential, etc.). `SynthBase` provides the core `saveToJson()`/`loadFromJson()` methods (protected; we added public wrappers `getStateAsJson()`/`loadStateFromJson()`).

**UI / Rendering:** The entire UI is rendered via OpenGL -- standard JUCE `paint()` calls on child components do NOT work. All visual content must go through `paintBackground()` (rendered to texture during the OpenGL cycle) or use Vital's OpenGL component classes (`OpenGlQuad`, `PlainTextComponent`, `OpenGlTextEditor`, etc.). These components require shader initialization during the render cycle, so they cannot be created dynamically at runtime without crashes. The pattern used throughout is to pre-allocate components at startup. UI sections inherit from `SynthSection` which provides the OpenGL rendering infrastructure.

**Build System:** Uses JUCE 6 with Projucer-generated Xcode/VS projects. The project uses **unity builds** -- individual `.cpp` files have `compile="0"` in `vital.jucer` and are `#include`d into aggregate files under `src/unity_build/`. New source files must be added to the appropriate unity build file or they will produce linker errors.

### AI Chatbot Addition

**Side Panel (`side_panel.h/cpp`):** `VitalSidePanel` extends `SynthSection` and provides the chat UI. It contains a scrollable message area (manual scroll tracking, no `juce::Viewport`), an `OpenGlTextEditor` for input, and a submit button. Messages are rendered directly in `paintBackground()` -> `paintChatMessages()` using `TextLayout` for word-wrapped text. System messages support markdown rendering. A clear button (x icon) in the title row resets the chat to its initial state: clears all messages, stops any active recording, clears the text editor, and calls `ClaudeApiClient::clearConversation()` to reset conversation history.

**Listener Pattern:** `VitalSidePanel` defines an inner `Listener` class. `FullInterface` implements this listener and handles `sidePanelMessageSubmitted()` -- it serializes the current preset to JSON (stripping base64 data), passes it along with the user message to the API client, and applies the returned JSON diff to the live preset.

**API Client (`claude_api_client.h/cpp`):** Singleton (`ClaudeApiClient::instance()`) that manages the Anthropic Claude API integration. Loads API key from a user-configured file path (stored in Vital's app settings). Loads `SYSTEM_PROMPT.md` and `PRESET_SCHEMA.md` from the app bundle Resources directory at init. Maintains conversation history (max 20 messages). HTTP requests run on a background thread via `Thread::launch()`; responses are delivered back to the UI thread via `MessageManager::callAsync()`. Implements Anthropic API prompt caching: the system prompt (including preset schema) is sent as a cacheable content block with 1-hour ephemeral TTL, reducing subsequent request costs by ~90% on the cached portion.

**Preset Manipulation Flow:** User message -> current preset serialized to JSON (base64 stripped) -> injected as context in API call -> Claude returns a JSON merge patch (RFC 7396 style, only changed keys) -> `mergeJson()` recursively applies the diff to the current preset -> `loadStateFromJson()` applies the result to the live synth engine. Array elements are merged element-by-element; placeholder strings from base64 stripping are preserved (not overwritten).

**Markdown Rendering (`markdown_parser.h/cpp`):** Uses vendored md4c (C library, MIT license, in `third_party/md4c/`) with a SAX callback approach. Parses markdown into `MarkdownBlock`/`StyledRun` structs. The side panel renders these blocks with support for headings, bold/italic/monospace, fenced code blocks, bullet/numbered lists, block quotes, and horizontal rules. Uses Vital's `Fonts::instance()->proportional_regular()` (Lato) with `.boldened()` for bold text.

**Voice Input (Deepgram STT):** The side panel has two voice input modes via VOICE CHAT and TALK buttons, plus SEND for text submission. Layout: [VOICE CHAT (half-width)] [TALK (quarter)] [SEND (quarter)]. **VOICE CHAT** is always-on mode -- stays recording until manual stop or 20 seconds of silence (hardcoded via `silence_timeout_override` parameter on `MicrophoneCapture::startCapture()`). Shows an `AlertWindow` popup on start warning the user they must manually end. **TALK** auto-stops on silence using user-configured timeout (default 2.5s). Both use `MicrophoneCapture` (dedicated `AudioDeviceManager` with 1 input, 0 outputs, resampling to 16kHz) and stream audio over WebSocket to Deepgram's Nova-3 STT API via `DeepgramClient` (singleton, PIMPL pattern hiding IXWebSocket dependency). Interim transcripts update the text editor as a live preview; final transcripts are auto-submitted as chat messages. Both show "STOP" when active; clicking one while the other is active stops the first before starting the new mode. Recording state is tracked via `RecordingMode` enum (`kRecordingNone`, `kRecordingTalk`, `kRecordingVoiceChat`). The Deepgram API key is stored via the same file-path-in-config pattern as the Claude API key. IXWebSocket is vendored in `third_party/ixwebsocket/` for WebSocket+TLS. macOS mic permission is handled in a separate `mic_permission_mac.mm` file (compiled independently, not in unity build) to avoid AVFoundation/JUCE namespace conflicts. The silence timeout configuration menu items in `synth_preset_selector.cpp` are currently commented out. Future: local VAD gating for VOICE CHAT mode to avoid streaming silence to Deepgram (which charges per-second for all audio including silence).

## Key Files Reference

**Core Serialization:**

- [load_save.cpp](src/common/load_save.cpp) - JSON serialization/deserialization
- [synth_parameters.cpp](src/common/synth_parameters.cpp) - All parameter definitions with ranges
- [synth_constants.h](src/common/synth_constants.h) - Numeric constants
- [synth_strings.h](src/interface/look_and_feel/synth_strings.h) - String values for enums
- [synth_base.h](src/common/synth_base.h) - SynthBase with `getStateAsJson()` / `loadStateFromJson()` wrappers

**Line Generator (LFOs and Line Source wavetables):**

- [line_generator.cpp](src/common/line_generator.cpp) - Line shape format and built-in waveform definitions
- [line_generator.h](src/common/line_generator.h) - LineGenerator class with initSaw, initSquare, etc.

**Wavetables:**

- [wave_line_source.cpp](src/common/wavetable/wave_line_source.cpp) - **Line Source component (PREFERRED)**
- [wave_line_source.h](src/common/wavetable/wave_line_source.h) - Line Source class definition
- [wave_source.cpp](src/common/wavetable/wave_source.cpp) - Wave Source component (base64 encoded)
- [wavetable_creator.cpp](src/common/wavetable/wavetable_creator.cpp) - Wavetable rendering and JSON handling
- [wavetable_component_factory.cpp](src/common/wavetable/wavetable_component_factory.cpp) - Component type registry
- [wavetable_group.cpp](src/common/wavetable/wavetable_group.cpp) - Default wavetable creation

**Samples:**

- [sample_source.cpp](src/synthesis/producers/sample_source.cpp) - Sample data format

**UI / Interface:**

- [full_interface.h/cpp](src/interface/editor_sections/full_interface.cpp) - Main UI container, handles VitalSidePanel listener callbacks
- [synth_section.h/cpp](src/interface/editor_sections/synth_section.h) - Base class for all UI sections, includes `paintBackground()` for OpenGL rendering
- [synth_button.h](src/interface/editor_components/synth_button.h) - OpenGlToggleButton, SynthButton components
- [side_panel.h/cpp](src/interface/editor_sections/side_panel.cpp) - **Our AI chat panel (VitalSidePanel)** with listener pattern for message submission
- [open_gl_image_component.h](src/interface/editor_components/open_gl_image_component.h) - OpenGlTextEditor, PlainTextComponent, OpenGlAutoImageComponent
- [open_gl_multi_quad.h](src/interface/editor_components/open_gl_multi_quad.h) - OpenGlQuad (rounded rectangles), OpenGlScrollBar
- [open_gl_component.h/cpp](src/interface/editor_components/open_gl_component.cpp) - Base OpenGL component, parent/findValue system
- [modulation_matrix.h/cpp](src/interface/editor_sections/modulation_matrix.cpp) - Reference for scrollable lists with OpenGL (pre-allocated rows pattern)
- [save_section.cpp](src/interface/editor_sections/save_section.cpp) - Reference for OpenGlTextEditor setup patterns
- [preset_browser.cpp](src/interface/editor_sections/preset_browser.cpp) - Reference for multiline text editor setup

**API Client:**

- [claude_api_client.h/cpp](src/common/claude_api_client.cpp) - Singleton Claude API client with prompt caching, async API calls
- [SYSTEM_PROMPT.md](agents/vital-assistant/SYSTEM_PROMPT.md) - System prompt for Claude API assistant
- [PRESET_SCHEMA.md](agents/vital-assistant/PRESET_SCHEMA.md) - Parameter schema with scaling formulas
- [synth_preset_selector.cpp](src/interface/editor_components/synth_preset_selector.cpp) - Menu bar with preset loading, skin, and API key file selection

**Voice Input (Deepgram STT):**

- [deepgram_client.h/cpp](src/common/deepgram_client.cpp) - Singleton Deepgram WebSocket STT client (PIMPL pattern)
- [microphone_capture.h/cpp](src/common/microphone_capture.cpp) - Mic capture with 16kHz resampling
- [mic_permission_mac.mm](src/common/mic_permission_mac.mm) - macOS mic permission request (separate from unity build)
- [ixwebsocket/](third_party/ixwebsocket/) - Vendored IXWebSocket library for WebSocket+TLS

**Markdown Rendering:**

- [markdown_parser.h/cpp](src/common/markdown_parser.cpp) - md4c-based parser producing MarkdownBlock/StyledRun structs
- [md4c.h/md4c.c](third_party/md4c/) - Vendored C markdown parser (MIT)

**Build System:**

- [common.cpp](src/unity_build/common.cpp) - Unity build file for common/utility classes
- [interface_editor_sections.cpp](src/unity_build/interface_editor_sections.cpp) - Unity build file for editor sections
