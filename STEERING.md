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
- Users can give technical descriptions of parameters/settings to tweak, ie specific settings and numerical values: "increase the filter cutoff a bit, no more than 5%". This is handled directly by the preset generation layer with knowledge of the parameter schema.
- Users can also give non-technical sound design descriptions, ie. "make it more dreamy" or "i want a mario video game blippy chiptuney coin sound". These are automatically detected by the router and translated into technical instructions via a sound design translation layer before execution.
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

**Build Commands:** Cross-platform script auto-detects OS: `./build.sh`. Platform-specific: `./build_macos.sh`, `build_windows.bat`, `./build_linux.sh`. Flags (all scripts): `--config=Debug|Release` (default Debug), `--skip-regenerate` (skip Projucer re-export, faster rebuilds), `--no-run` (build only, don't launch), `--clean` (clean before build). Typical agent build: `./build.sh --skip-regenerate --no-run`.

### AI Chatbot Addition

**Multi-Layer Agentic Chat Flow:** User messages first go through a "router" layer that analyzes the request without the full system prompt/schema. The router uses Claude tool_use (forced via `tool_choice`) to parse the message into atomic actions via three paths: (1) **pass-through** -- single simple requests go directly to preset generation; (2) **split-complex** -- multi-step requests are split into sequential sub-actions executed with status updates ("Step N/M: ..."); (3) **sound design required** -- non-technical descriptions ("blippy", "warm analog pad") are detected via a `sound_design_required` boolean in the tool schema, translated into numbered technical parameter instructions by a separate Claude call (using `SOUND_DESIGN_PROMPT.md` + `SOUND_DESIGN_GUIDE.md`), then re-routed through the router for splitting and execution. The translation is an internal intermediate step -- not shown in chat and not stored in conversation history. An `is_sound_design_reroute_` flag prevents infinite loops if the translation itself triggers sound design detection. Each sub-action is added to conversation history so the LLM maintains context. The router system prompt is externalized to `prompts/system_prompts/ROUTER_PROMPT.md` (loaded at runtime like other prompts) and includes a compact "VITAL TECHNICAL TERMS" reference listing all parameter categories and names, enabling accurate technical vs non-technical classification. The prompt is tuned to batch simple independent changes together and minimize splitting. The router also returns `save_required` (boolean) and `preset_name` (string) fields -- when the user wants to save, the preset is written to `{user_preset_dir}/Sound Designer/{name}.vital` either immediately (save-only, no actions) or after all actions complete, with a confirmation message shown in chat.

**Side Panel (`side_panel.h/cpp`):** `VitalSidePanel` extends `SynthSection` and provides the chat UI. It contains a scrollable message area (manual scroll tracking, no `juce::Viewport`), an `OpenGlTextEditor` for input, and a submit button. Messages are rendered directly in `paintBackground()` -> `paintChatMessages()` using `TextLayout` for word-wrapped text. System messages support markdown rendering. When the message list is empty, `paintChatMessages()` renders a centered intro screen: speech waveform icon (120px, 0.45 alpha) above "Talk to your synthesizer" tagline (0.55 alpha), vertically centered in the chat area; the intro path also resets `restore_button_bounds_` to prevent stale button rendering. A clear button (x icon) in the title row resets the chat to its initial state: clears all messages, stops any active recording, clears the text editor, and calls `ClaudeApiClient::clearConversation()` to reset conversation history. The panel also manages **autosave checkpoints**: each message send/receive triggers a preset snapshot saved to `<data_dir>/autosaves/checkpoint_<timestamp>.vital`. Hovering over a user message reveals a restore button (return arrow SVG icon) that implements an instant **edit mode** (Claude web UI pattern): clicking removes the user message and everything after it, restores the message text to the input box for editing, and saves a snapshot to undo if user presses ESC / clicks the X cancel button. The `EditModeSnapshot` struct captures full messages, checkpoints, full API conversation history snapshot (via `ClaudeApiClient::getHistorySnapshot()` / `restoreHistory()`), and synth state for complete rollback. Edit mode is implemented as a state machine via `enterEditMode()` / `cancelEditMode()` / `exitEditMode()`; ESC key handler and cancel button both trigger rollback via `cancelEditMode()`. Submitting or clearing discards the snapshot via `exitEditMode()`. **CRITICAL INVARIANT:** During edit-mode restore, `removeCheckpointsAfter()` removes checkpoint entries from the vector but must NOT delete their `.vital` files from disk — the snapshot holds references to these files for `cancelEditMode()` to restore. File cleanup is deferred to `exitEditMode()`, which diffs the snapshot against the current checkpoint vector and deletes only orphaned files. On clear, checkpoints are archived by session name; on startup, orphaned checkpoints are archived to `unsaved_session/`. Capped at 50 checkpoints per session and 20 archived sessions. Added `updateStatusMessage()` to replace the last system message in-place (used for status transitions like "Breaking it down..." → "Step 1/N..."); both `updateStatusMessage()` and `clearThinkingMessage()` scan backwards from the end to find their target message type, handling interleaved kUser messages from queued sends. "Thinking..." indicator is created in `sidePanelMessageSubmitted()` (not `submitMessage()`) so it only appears when the message is actually processed, not when queued. Also stores the original user message before sound design reroute via `addToHistory("user", message)` to preserve the original request in history when sound design translation occurs.

**Listener Pattern:** `VitalSidePanel` defines an inner `Listener` class. `FullInterface` implements this listener and handles `sidePanelMessageSubmitted()` -- it now calls `routeAndExecute()` instead of directly sending to the API. For single-action requests, the behavior is identical (transparent routing). For multi-action requests, `routeAndExecute()` stores the actions and calls `executeNextAction()` sequentially. Queued messages (sent while processing) are dequeued one at a time via `queued_messages_.remove(0)` at each of the 3 queue processing points. **Async callback safety**: A generation counter (`api_request_generation_`) on `FullInterface` invalidates in-flight API callbacks when the user triggers any chat-reset action. Each callback captures the generation at creation; invalidation points bump it; callbacks silently discard stale responses. Invalidation points: `sidePanelRestoreRequested()`, `sidePanelCancelEditRequested()`, `sidePanelClearRequested()`.

**API Client (`claude_api_client.h/cpp`):** Singleton (`ClaudeApiClient::instance()`) that manages the Anthropic Claude API integration. Loads API key from a user-configured file path (stored in Vital's app settings). Loads `SYSTEM_PROMPT.md`, `PRESET_SCHEMA.md`, and `ROUTER_PROMPT.md` from the app bundle Resources directory at init. Maintains conversation history (max 20 messages). HTTP requests run on a background thread via `Thread::launch()`; responses are delivered back to the UI thread via `MessageManager::callAsync()`. Implements Anthropic API prompt caching: the system prompt (including preset schema) is sent as a cacheable content block with 1-hour ephemeral TTL, reducing subsequent request costs by ~90% on the cached portion. **Message format**: Both `routeMessageAsync()` and `sendMessagesAsync()` send a single user message with XML-tagged sections (`<conversation_history>` for prior turns as context only, `<current_preset>` for the preset JSON in main API calls, `<current_request>` for the actual message to act on). This prevents the LLM from conflating old requests with the current one. When the LLM returns pure JSON with no text, the assistant history stores `"Done."` as a short natural placeholder. Added `routeMessage()` method: makes a lightweight API call with tool_use to parse user messages into actions (router uses Sonnet model, system prompt loaded from `ROUTER_PROMPT.md`, no preset schema). Added `addToHistory()` public method to manually add user messages to history without API call (used for storing original message in multi-action flow). Added `sendSoundDesignTranslation()` / `sendSoundDesignTranslationAsync()` methods: separate Claude call using `SOUND_DESIGN_PROMPT.md` + `SOUND_DESIGN_GUIDE.md` to translate non-technical descriptions into technical parameter instructions (output not stored in history). `kMaxTokens` increased from 1024 to 4096 for preset generation; `kSoundDesignMaxTokens = 1024` for translation calls. Added `splitResponseText()` utility to detect and extract JSON from assistant responses via 3 methods: pure JSON without fences (trimmed response starts with `{`), text + JSON with markdown fences, and text + inline JSON (finds `{"settings"` substring). Only text portion is stored in history. Renamed from `extractFenceContent()` because the function's scope expanded to handle all 3 cases (not just fence extraction). Added `logRequest()` method that logs API calls to `api_requests.log` with timestamp, endpoint label, request/response sizes, token usage (input, output, cache read, cache create), and full request/response bodies for cost analysis.

**Preset Manipulation Flow:** User message -> current preset serialized to JSON (base64 stripped) -> injected ephemerally into the API request's message array (not stored in conversation history) -> Claude returns a JSON merge patch (RFC 7396 style, only changed keys) -> `mergeJson()` recursively applies the diff to the current preset -> `loadStateFromJson()` applies the result to the live synth engine. Array elements are merged element-by-element; placeholder strings from base64 stripping are preserved (not overwritten). Assistant responses are processed by `ClaudeApiClient::splitResponseText()` to separate conversational text from JSON (via 3 detection modes: pure JSON without fences, text + fenced JSON, text + inline JSON); only the text portion is stored in history.

**Markdown Rendering (`markdown_parser.h/cpp`):** Uses vendored md4c (C library, MIT license, in `third_party/md4c/`) with a SAX callback approach. Parses markdown into `MarkdownBlock`/`StyledRun` structs. The side panel renders these blocks with support for headings, bold/italic/monospace, fenced code blocks, bullet/numbered lists, block quotes, and horizontal rules. Uses Vital's `Fonts::instance()->proportional_regular()` (Lato) with `.boldened()` for bold text.

**Voice Input (Deepgram STT):** The side panel has two voice input controls, both inline within the textarea (no separate button row). A **dual-purpose circular action button** sits at the bottom-right of the textarea with a purple circle background (`action_circle_bg_`, an `OpenGlQuad`). It operates as a 3-state machine (`ActionButtonMode` enum: `kActionMic`, `kActionSend`, `kActionStop`): shows mic icon when textarea is empty (starts talk recording), up-arrow send icon when text is present (sends message), and rounded-square stop icon when talk recording is active (stops recording). State transitions are driven by `textEditorTextChanged()` and recording state changes via `updateActionButtonState()`. A smaller **VOICE CHAT button** sits at the bottom-left of the textarea; it shrinks and gets more rounding when in STOP mode. The textarea extends to the bottom of the panel (no button row below it). **Silence detection** uses Deepgram-activity-based inactivity timeout (replaced old amplitude-based approach). `VitalSidePanel` inherits `juce::Timer` and polls every 250ms via `timerCallback()`, checking `last_deepgram_activity_ms_` (updated whenever Deepgram returns a non-empty transcript, and for VOICE CHAT also when the AI response is received via `addResponseMessage()`). A `recording_start_ms_` tracks when recording began for the grace period. **TALK mode**: 3-second grace period (no inactivity check), then 2-second inactivity timeout; also stops immediately on Deepgram `is_final` transcript (timer is a safety net). **VOICE CHAT mode**: 5-second grace period, then 10-second inactivity timeout; inactivity timer is refreshed when the AI response arrives so users waiting for a reply are not cut off. These grace and timeout values (and the 250ms polling interval) are **tested and tuned for natural customer usage patterns**; see `side_panel.cpp` `timerCallback()` and TROUBLESHOOTING.md. MicrophoneCapture's amplitude silence callback is passed as `nullptr` for both modes (amplitude detection code remains but is inert). Both use `MicrophoneCapture` (dedicated `AudioDeviceManager` with 1 input, 0 outputs, resampling to 16kHz) and stream audio over WebSocket to Deepgram's Nova-3 STT API via `DeepgramClient` (singleton, PIMPL pattern hiding IXWebSocket dependency). Interim transcripts update the text editor as a live preview; final transcripts are auto-submitted as chat messages. Recording state is tracked via `RecordingMode` enum (`kRecordingNone`, `kRecordingTalk`, `kRecordingVoiceChat`). The Deepgram API key is stored via the same file-path-in-config pattern as the Claude API key. IXWebSocket is vendored in `third_party/ixwebsocket/` for WebSocket+TLS; TLS backends are per-platform: Apple Secure Transport on macOS, mbedTLS 3.6.5 on Windows (vendored in `third_party/mbedtls/`). `ix::initNetSystem()` / `ix::uninitNetSystem()` are called in `DeepgramClient` for Windows `WSAStartup`/`WSACleanup`. macOS mic permission is handled in a separate `mic_permission_mac.mm` file (compiled independently, not in unity build) to avoid AVFoundation/JUCE namespace conflicts. The silence timeout configuration menu items in `synth_preset_selector.cpp` are currently commented out. Future: local VAD gating for VOICE CHAT mode to avoid streaming silence to Deepgram (which charges per-second for all audio including silence).

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

- [full_interface.h/cpp](src/interface/editor_sections/full_interface.cpp) - Main UI container, handles VitalSidePanel listener callbacks and keyboard shortcuts (Cmd+K / Ctrl+K)
- [synth_section.h/cpp](src/interface/editor_sections/synth_section.h) - Base class for all UI sections, includes `paintBackground()` for OpenGL rendering
- [synth_button.h](src/interface/editor_components/synth_button.h) - OpenGlToggleButton, SynthButton components
- [side_panel.h/cpp](src/interface/editor_sections/side_panel.cpp) - **Our AI chat panel (VitalSidePanel)** with listener pattern, checkpoint/restore, and `focusPromptEditor()`
- [paths.h](src/interface/look_and_feel/paths.h) - SVG icon paths including `restoreIcon()`, `microphoneIcon2()`, `sendArrowIcon()`, `stopIcon()`
- [open_gl_image_component.h](src/interface/editor_components/open_gl_image_component.h) - OpenGlTextEditor, PlainTextComponent, OpenGlAutoImageComponent
- [open_gl_multi_quad.h](src/interface/editor_components/open_gl_multi_quad.h) - OpenGlQuad (rounded rectangles), OpenGlScrollBar
- [open_gl_component.h/cpp](src/interface/editor_components/open_gl_component.cpp) - Base OpenGL component, parent/findValue system
- [modulation_matrix.h/cpp](src/interface/editor_sections/modulation_matrix.cpp) - Reference for scrollable lists with OpenGL (pre-allocated rows pattern)
- [save_section.cpp](src/interface/editor_sections/save_section.cpp) - Reference for OpenGlTextEditor setup patterns
- [preset_browser.cpp](src/interface/editor_sections/preset_browser.cpp) - Reference for multiline text editor setup

**API Client & Router:**

- [claude_api_client.h/cpp](src/common/claude_api_client.cpp) - Singleton Claude API client with router layer, prompt caching, async API calls
- [SYSTEM_PROMPT.md](prompts/system_prompts/SYSTEM_PROMPT.md) - System prompt for Claude API assistant
- [PRESET_SCHEMA.md](prompts/system_prompts/PRESET_SCHEMA.md) - Parameter schema with scaling formulas
- [ROUTER_PROMPT.md](prompts/system_prompts/ROUTER_PROMPT.md) - Router system prompt with Vital technical terms reference
- [SOUND_DESIGN_PROMPT.md](prompts/system_prompts/SOUND_DESIGN_PROMPT.md) - System prompt for sound design translation
- [SOUND_DESIGN_GUIDE.md](prompts/system_prompts/SOUND_DESIGN_GUIDE.md) - Sound design cookbook for translation layer
- [full_interface.h/cpp](src/interface/editor_sections/full_interface.cpp) - Main UI container with routeAndExecute(), executeNextAction() for multi-action orchestration
- [synth_preset_selector.cpp](src/interface/editor_components/synth_preset_selector.cpp) - Menu bar with preset loading, skin, and API key file selection

**Voice Input (Deepgram STT):**

- [deepgram_client.h/cpp](src/common/deepgram_client.cpp) - Singleton Deepgram WebSocket STT client (PIMPL pattern)
- [microphone_capture.h/cpp](src/common/microphone_capture.cpp) - Mic capture with 16kHz resampling
- [mic_permission_mac.mm](src/common/mic_permission_mac.mm) - macOS mic permission request (separate from unity build)
- [ixwebsocket/](third_party/ixwebsocket/) - Vendored IXWebSocket library for WebSocket+TLS
- [mbedtls/](third_party/mbedtls/) - Vendored mbedTLS 3.6.5 for Windows TLS

**Markdown Rendering:**

- [markdown_parser.h/cpp](src/common/markdown_parser.cpp) - md4c-based parser producing MarkdownBlock/StyledRun structs
- [md4c.h/md4c.c](third_party/md4c/) - Vendored C markdown parser (MIT)

**Plans & Analysis:**

- [harmonic-questing-bird.md](.plans/harmonic-questing-bird.md) - Token cost reduction plan with history write-point audit
- [harmonic-questing-bird-2.md](.plans/harmonic-questing-bird-2.md) - Multi-action behavior fixes

**Build System:**

- [vital.jucer](standalone/vital.jucer) - JUCE project file (source of truth for builds)
- [common.cpp](src/unity_build/common.cpp) - Unity build file for common/utility classes
- [interface_editor_sections.cpp](src/unity_build/interface_editor_sections.cpp) - Unity build file for editor sections
