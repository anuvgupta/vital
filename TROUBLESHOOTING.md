## Vital Project Troubleshooting

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

- **Use `TextLayout` for both measuring and drawing text, never `drawFittedText`**:
    - `drawFittedText` and `TextLayout` use different word-wrapping algorithms. If you calculate height with `TextLayout` but draw with `drawFittedText`, they disagree on line breaks.
    - When `drawFittedText` needs more lines than the allocated height, it **shrinks the font** to fit, causing tiny unreadable text.
    - **Solution**: Use `TextLayout::createLayout()` + `TextLayout::draw()` for rendering. This matches the wrapping used in `ChatMessage::calculateHeight()`.
    - Fixed in `VitalSidePanel::paintChatMessages()` in `side_panel.cpp`.

- **JUCE 6 API differences**: This project uses JUCE 6. Newer APIs like `URL::InputStreamOptions` and `URL::ParameterHandling` (JUCE 7+) don't exist. Use legacy overloads, e.g. `url.createInputStream(false, nullptr, nullptr, "", 5000)`.

- **TextEditor::Listener for Enter key handling**:
    - Implement `TextEditor::Listener` and override `textEditorReturnKeyPressed()` to handle Enter key submission.
    - Set `setReturnKeyStartsNewLine(false)` so Enter submits instead of creating a newline (users can use Shift+Enter for newlines).

- **Background threading for HTTP requests in JUCE**:
    - Never make HTTP requests on the UI thread - it blocks the entire interface.
    - Use `Thread::launch()` with a lambda to run HTTP work on a background thread.
    - Use `MessageManager::callAsync()` to deliver results back to the UI thread for safe component access.
    - Example pattern in `ClaudeApiClient::sendMessage()`: launches background thread, captures callback, invokes callback via `callAsync()`.
    - When building JSON in JUCE, use `DynamicObject` for objects and `Array<var>` for arrays, then `JSON::toString(var(...))` to serialize.

- **Font selection for styled text in Vital's OpenGL rendering**:
    - Vital provides `Fonts::instance()->proportional_regular()` (Lato) and `proportional_title()` (Montserrat Light). When creating bold text, use `proportional_regular().boldened()` rather than `proportional_title()` which is a completely different font family and weight.
    - Root cause: `proportional_title()` looks nothing like a bold variant of the body font, causing jarring visual inconsistency in markdown rendering.

- **Claude API model selection - NEVER use Opus 4 (non-4.5)**:
    - Use `claude-sonnet-4-5-20241022` (Sonnet 4.5) or `claude-opus-4-5-20251101` (Opus 4.5) only.
    - **NEVER use Opus 4** (`claude-opus-4-*`) - it is extremely expensive compared to Sonnet 4 and not worth the cost difference for this use case. Opus 4.5 is the correct choice if you need the highest capability tier.
    - Constants `kModelSonnet` and `kModelOpus` are defined in `claude_api_client.cpp`. Default is Sonnet.

- **Accessing protected methods on SynthBase**:
    - `SynthBase::saveToJson()` is protected - can't call directly from UI code like `FullInterface`.
    - **Solution**: Add a public wrapper method like `getStateAsJson()` (wraps `saveToJson()`) or `loadStateFromJson()` (wraps `loadFromJson()`).
    - This project uses an older nlohmann json version - use `.count("key")` instead of `.contains("key")`.

- **JUCE TextEditor placeholder text shows ellipsis instead of wrapping**:
    - JUCE's `TextEditor::paintOverChildren()` hardcodes `drawText(..., true)` which enables ellipsis for placeholder text, even in multiline editors.
    - Pre-calculating wrap in `resized()` fails because component dimensions aren't set yet.
    - **Solution**: Override `paintOverChildren()` to calculate word wrapping at paint time when dimensions and font are accurate. Add a `wrapText()` helper to split text into lines. Store placeholder text/color locally since JUCE's members are private (override `setTextToShowWhenEmpty()`).
    - Fixed in `OpenGlTextEditor` class in `src/interface/editor_components/open_gl_image_component.h`.

- **Projucer customPList XML nesting matters**:
    - Adding entries like `NSMicrophoneUsageDescription` outside the `<dict>` block causes the plist to be silently malformed. Xcode won't warn you; the key just won't appear in the built Info.plist.
    - **Solution**: Ensure all plist entries are inside `<dict>...</dict>` in the `customPList` field of `vital.jucer`.

- **AVFoundation/JUCE namespace conflicts in unity builds**:
    - Including `<AVFoundation/AVFoundation.h>` in a `.mm` file that's part of a unity build causes type collisions with JUCE (e.g., `Point`, `Rectangle`, `String`).
    - **Solution**: Create a separate `.mm` file (e.g., `mic_permission_mac.mm`) that is compiled independently (not included in any unity build file). Set `compile="1"` in the jucer for this file, or exclude it from unity build includes.

- **macOS hardened runtime silently blocks microphone access**:
    - Even with `NSMicrophoneUsageDescription` in Info.plist, if the hardened runtime is enabled (default for signed apps), mic access is silently denied -- no permission dialog, no error, just silent audio buffers of zeros.
    - **Solution**: Add `com.apple.security.device.audio-input` to the entitlements file. In Projucer, set `hardenedRuntimeOptions="com.apple.security.device.audio-input"` in `vital.jucer`. Also call `[AVCaptureDevice requestAccessForMediaType:AVMediaTypeAudio]` explicitly before opening audio devices.

- **Deepgram endpointing may not trigger on manual stop**:
    - If the user stops recording quickly, Deepgram's voice activity detection / endpointing may never fire, leaving only interim (non-final) transcripts. The `is_final` field in the response will be false.
    - **Solution**: On manual stop, grab whatever text is currently displayed in the prompt editor (from interim transcripts) and submit it directly, rather than waiting for a final transcript from Deepgram.

- **Separate AudioDeviceManager for mic input to avoid interfering with synth**:
    - Using the synth's existing `AudioDeviceManager` for mic capture can reconfigure audio routing and break synth output.
    - **Solution**: Create a dedicated `AudioDeviceManager` in `MicrophoneCapture` with 1 input channel and 0 output channels. This keeps mic recording fully isolated from synth audio.

- **JUCE 6 vs JUCE 7 AlertWindow API**:
    - `MessageBoxIconType::InfoIcon` and similar enum-class-style icon types are JUCE 7+ API. Using them in JUCE 6 causes compilation errors.
    - **Solution**: Use `AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon, ...)` which is the JUCE 6 API. The icon type enum lives on `AlertWindow` directly in JUCE 6, not in a separate `MessageBoxIconType` enum class.

- **Cross-platform resource file loading — AI chat broken on Windows**:
    - `ClaudeApiClient::loadSystemPrompt()` and `loadPresetSchema()` search for `SYSTEM_PROMPT.md` and `PRESET_SCHEMA.md` at runtime. The first search path (`../../Resources/` relative to exe) only works inside a macOS `.app` bundle. On Windows, `build_windows.bat` copies these files next to the `.exe`, but that directory was never checked.
    - Without the system prompt and schema, Claude has no instructions to output JSON, so it responds conversationally -- the raw markdown text appears in the chat instead of preset changes being applied.
    - **Solution**: Added `executable.getParentDirectory()` (exe-adjacent directory) as a search path between the macOS bundle path and the user data dir fallback. Search order: (1) `../../Resources/` for macOS bundles, (2) same dir as exe for Windows, (3) user data dir as fallback.
    - File: `src/common/claude_api_client.cpp`

- **Windows Voice Chat crash -- null TLS socket in ixwebsocket**:
    - `IXWEBSOCKET_USE_SECURE_TRANSPORT=1` is Apple's Security.framework TLS backend. On Windows, no TLS implementation matched, so `ix::Socket::createTLSSocket()` returned null, crashing on dereference when connecting to `wss://api.deepgram.com`.
    - Secondary issue: `ix::initNetSystem()` (calls `WSAStartup`) was never called on Windows, so all socket operations would fail even without the TLS problem.
    - **Solution**: (1) Move `IXWEBSOCKET_USE_SECURE_TRANSPORT` to macOS-only exporter `extraDefs` in `vital.jucer`. (2) Add mbedTLS 3.6.5 as vendored library (`third_party/mbedtls/`), enable via `IXWEBSOCKET_USE_MBED_TLS=1` + `IXWEBSOCKET_USE_MBED_TLS_MIN_VERSION_3=1` in VS2019 exporter. (3) Add `ix::initNetSystem()` / `ix::uninitNetSystem()` to `DeepgramClient`. (4) Link `crypt32.lib` and `bcrypt.lib` for Windows.
    - Files: `standalone/vital.jucer`, `src/common/deepgram_client.cpp`, `third_party/mbedtls/`

- **Unity build Windows header pollution via ixwebsocket**:
    - Including `IXNetSystem.h` in `deepgram_client.cpp` pulls `<winsock2.h>` and `<windows.h>`, which define `min`/`max` macros. In a unity build, these macros leak into every subsequent `#include`, breaking all `std::min`/`std::max` calls with cryptic template errors.
    - **Solution**: Use forward declarations (`namespace ix { void initNetSystem(); void uninitNetSystem(); }`) instead of `#include "IXNetSystem.h"`. This avoids pulling Windows headers into the unity build translation unit.
    - File: `src/common/deepgram_client.cpp`

- **Projucer regeneration overwrites manual vcxproj edits**:
    - Any manual edits to generated project files (e.g., `Vial_App.vcxproj`) are lost when Projucer re-exports from `vital.jucer`. This includes added source files, include paths, library dependencies, and preprocessor defines.
    - **Solution**: Always make changes in `vital.jucer` (the source of truth). Add source files as `FILE` entries, put per-platform defines in exporter `extraDefs`, and put libraries in exporter `externalLibraries`.

- **mbedTLS 3.x requires both crypt32.lib and bcrypt.lib on Windows**:
    - mbedTLS uses `BCryptGenRandom` for entropy, requiring `bcrypt.lib`. Certificate validation uses Windows certificate store APIs from `crypt32.lib`. Missing either causes unresolved symbol linker errors.
    - The `IXWEBSOCKET_USE_MBED_TLS_MIN_VERSION_3=1` define is required for mbedTLS 3.x because `mbedtls_pk_parse_keyfile` changed from 4 to 5 parameters between v2 and v3.

- **MSVC `vector::resize()` requires default constructor even when shrinking**:
    - `ChatMessage` had no default constructor (uses member initializer for `MessageType`). Calling `messages_.resize(n)` to truncate the vector caused MSVC compile error: `ChatMessage::ChatMessage: no appropriate default constructor available`.
    - Root cause: MSVC's STL instantiates the default-construct path of `vector::resize()` at compile time regardless of whether you only shrink. GCC/Clang may not.
    - **Solution**: Use `messages_.erase(messages_.begin() + n, messages_.end())` instead of `resize(n)`. `erase()` only requires move/copy, not default construction.
    - File: `src/interface/editor_sections/side_panel.cpp`

- **SVG icons can be embedded as string literals in Paths class**:
    - Instead of adding SVG files to BinaryData (which requires Projucer regeneration), you can embed SVG markup directly as a `const char*` and use `Drawable::createFromSVG(XmlDocument::parse(svgString))` or the `fromSvgData()` pattern.
    - Used for the restore/return arrow icon in `src/interface/look_and_feel/paths.h`.

- **Conversation history context pollution in ClaudeApiClient**:
    - `sendMessagesAsync` was calling `addMessage("user", preset_context)` every turn, storing stale preset JSON snapshots in `conversation_history_`. These accumulated and wasted context window tokens since the preset is re-fetched fresh each turn anyway.
    - Additionally, assistant responses containing full preset JSON blobs inside markdown code fences were stored verbatim in history, further polluting context with stale data.
    - **Solution**: (1) Inject preset JSON ephemerally into the `messagesArray` built for each API call (just before the current user message) without adding it to `conversation_history_`. (2) Strip JSON fence content from assistant responses before storing in history using `extractFenceContent()`. (3) Extract the inline fence-stripping logic from `full_interface.cpp` into a shared static utility `ClaudeApiClient::extractFenceContent()`.
    - Files: `src/common/claude_api_client.h`, `src/common/claude_api_client.cpp`, `src/interface/editor_sections/full_interface.cpp`

- **UTF-8 special characters render as garbage in JUCE button text**:
    - Passing raw UTF-8 hex bytes like `"\xc3\x97"` (multiplication sign) to `setButtonText()` renders as "A" with diacritical marks (e.g., "Å") because JUCE interprets the bytes as Latin-1, not UTF-8.
    - **Solution**: Wrap UTF-8 byte sequences with `String(CharPointer_UTF8("\xc3\x97"))`. This is the established pattern in the Vital codebase (used for bullet characters in markdown rendering in `side_panel.cpp`). Applies to any non-ASCII Unicode character in button labels or drawn text.