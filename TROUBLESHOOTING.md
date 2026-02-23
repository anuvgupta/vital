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

- **Voice recording inactivity timeouts (grace + timeout)**:
    - TALK: 3s grace, 2s inactivity timeout. VOICE CHAT: 5s grace, 10s inactivity timeout. Polling: 250ms. VOICE CHAT also refreshes the timer when the AI response arrives.
    - These values are **tested and tuned for natural customer usage patterns**. See `side_panel.cpp` `timerCallback()` for the constants and STEERING.md for full description. Change with care.

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

- **ChatMessage markdown blocks not updating when text changes**:
    - `updateStatusMessage()` was replacing `message.text` but not `message.blocks` (the parsed markdown structure), so the UI showed stale content or nothing at all because rendering uses `blocks` not `text`.
    - `ChatMessage` constructor parses markdown into `blocks` via `parseMarkdown()`, creating `MarkdownBlock` and `StyledRun` structs that are cached. Simply reassigning `text` breaks this invariant.
    - **Solution**: After updating `message.text`, also call `message.blocks = parseMarkdown(text)` to re-parse. Apply this whenever modifying ChatMessage content after construction.
    - File: `src/interface/editor_sections/side_panel.cpp` (`updateStatusMessage()` method)

- **System message padding conflict in chat UI**:
    - System messages were using same padding constant (`kPadding=12`) as user messages, but system status messages ("Step 1/N...", "Breaking it down...") looked vertically oversized/clunky compared to user bubbles.
    - The `kPadding` constant was used for both top/bottom padding on all message types, but system messages are typically simpler and need less space.
    - **Solution**: Split padding into `kPadding=14` for user/assistant messages and `kSystemPadding=4` for system messages. Update `calculateHeight()` and `paint()` calls to use the appropriate constant based on message type.
    - File: `src/interface/editor_sections/side_panel.h/cpp`

- **CRITICAL: Restore button broken after first use — checkpoint files deleted during edit mode**:
    - After clicking restore on a message (entering edit mode), then cancelling or clearing, subsequent restores to the same or later messages silently fail. The restore button appears (checkpoint objects exist in memory) but clicking it does nothing — messages are not truncated and the API conversation history is NOT cleaned up, causing stale context to be sent to the LLM.
    - **Root cause**: `sidePanelRestoreRequested()` called `removeCheckpointsAfter()` which deleted checkpoint `.vital` files from disk. But `enterEditMode()` saved a snapshot of the checkpoint vector BEFORE the restore. On cancel, `cancelEditMode()` restored the checkpoint objects into memory — but their files were gone. Subsequent restores found the checkpoint via `getCheckpoint()` but `autosave_file.exists()` returned false → early return, no truncation, no API history cleanup.
    - **Secondary issues**: (1) `clearChat()` didn't reset `edit_mode_`, so after restore→clear, `edit_mode_` was stuck true and `enterEditMode()` returned early on subsequent calls. (2) `processRecordedSpeech()` (voice input) didn't clear `edit_mode_` like `submitMessage()` does.
    - **Solution**: (1) Added `delete_files` parameter to `removeCheckpointsAfter(int, bool)` — `sidePanelRestoreRequested` passes `false` to preserve files for cancel. (2) Extracted `exitEditMode()` private helper that diffs snapshot checkpoints against current vector and deletes only orphaned files, then resets edit state. Called from `submitMessage()`, `processRecordedSpeech()`, and `clearChat()`. (3) `sidePanelRestoreRequested` now returns `bool`; `enterEditMode` checks success before setting `edit_mode_ = true`.
    - **Key invariant**: During edit-mode restore, checkpoint files must remain on disk until the edit is committed (`exitEditMode`) or cancelled (`cancelEditMode`). The snapshot holds file references that must stay valid.
    - Files: `src/interface/editor_sections/side_panel.h`, `src/interface/editor_sections/side_panel.cpp`, `src/interface/editor_sections/full_interface.h`, `src/interface/editor_sections/full_interface.cpp`

- **Router splitting too aggressively for simple requests**:
    - "turn on osc 2, turn on osc 3, turn on reverb, raise envelope release" was split into 4 separate API calls because the router prompt didn't encourage batching independent changes.
    - Each sub-action includes full system prompt + preset schema + conversation history, so aggressive splitting causes significant latency and token waste (even though each individual call is cheaper).
    - **Solution**: Update router system prompt (`kRouterSystemPrompt` in `claude_api_client.cpp`) to explicitly instruct batching of simple independent changes and cap at 3-5 actions for realistic workflows. Guidance: "Group simple, independent changes together... Only split when genuinely complex sound design where each step builds meaningfully on previous."
    - File: `src/common/claude_api_client.cpp` (line ~29, `kRouterSystemPrompt` constant)

- **JSON truncation from insufficient max_tokens on preset generation calls**:
    - When Claude generates comprehensive JSON diffs (e.g., after sound design translation produces many parameter changes), the response can exceed the `kMaxTokens` limit. If truncated mid-JSON, the raw incomplete JSON text is displayed in the chat instead of being parsed and applied as a preset update.
    - **Solution**: Increased `kMaxTokens` from 1024 to 4096 for preset generation calls. Added a separate `kSoundDesignMaxTokens = 1024` for sound design translation calls (which produce shorter text output, not JSON).
    - File: `src/common/claude_api_client.cpp`

- **Sound design translation must NOT be stored in conversation history**:
    - The sound design translation layer converts non-technical descriptions ("blippy jangly lead") into numbered technical instructions, then re-routes them through the router. If the translation is stored in conversation history, it pollutes context with intermediate instructions the user never wrote.
    - **Solution**: The `sendSoundDesignTranslation()` method uses its own system prompt and does not add its output to `conversation_history_`. The translation is treated as an internal intermediate step — only the original user message and final preset changes appear in history.
    - Files: `src/common/claude_api_client.h`, `src/common/claude_api_client.cpp`

- **Infinite loop guard needed for sound design re-routing**:
    - Sound design translations are re-routed through the router (`routeAndExecute()`). If the translation itself triggers `sound_design_required` again, it would loop infinitely.
    - **Solution**: Added `is_sound_design_reroute_` flag on `FullInterface` that is set `true` before re-routing. Inside `routeAndExecute()`, if `sound_design_required && is_sound_design_reroute_`, the sound design path is skipped and the message is treated as a normal request.
    - Files: `src/interface/editor_sections/full_interface.h`, `src/interface/editor_sections/full_interface.cpp`

- **Fabricated model IDs break when new features use old constants**:
    - `kModelSonnet` had a hardcoded constant `claude-sonnet-4-5-20241022` (a date that never existed — actual release was 20250929). This bug was never caught because Sonnet wasn't used in the codebase until we switched the router to Sonnet 4.5 for cost reduction. Then API calls started failing with a 404 "Unknown model" error.
    - **Root cause**: Constants were created early in development, never validated against Anthropic's API docs, and were never called until a code path was added that references them.
    - **Solution**: Always verify model IDs against current Anthropic API documentation when creating or updating constants. The fix: `kModelSonnet = "claude-sonnet-4-5-20250929"`, `kModelOpus = "claude-opus-4-5-20251101"`. Use these as the new defaults and never invent dates.
    - Files: `src/common/claude_api_client.cpp` (constants at top of file)

- **Stale API responses corrupt UI after edit-mode restore**:
    - When a user clicks "restore" on a conversation checkpoint while an API request is in-flight, the async callback still fires and appends response messages to the now-truncated chat UI, corrupting the restored state.
    - **Root cause**: Async callbacks (in `routeAndExecute()`, sound design translation, `sendApiRequest()`) capture references to UI state but have no way to know the conversation was invalidated between request dispatch and response delivery.
    - **Solution**: Added a generation counter (`api_request_generation_`) to `FullInterface`. Each async callback captures the current generation value at creation time. Invalidation points (`sidePanelRestoreRequested()`, `sidePanelCancelEditRequested()`) bump the counter. When a callback fires, it compares its captured generation against the current value and silently discards the response if they don't match.
    - **Pattern**: Generation counter for async callback invalidation — capture before lambda, check inside lambda, bump at invalidation points. Useful anywhere async work can be superseded by user actions.
    - Files: `src/interface/editor_sections/full_interface.h`, `src/interface/editor_sections/full_interface.cpp`

- **Stale API responses arrive after "clear conversation"**:
    - Pressing the clear conversation button while an API response was streaming/in-flight would still deliver the response to the now-cleared chat UI. The same generation counter pattern already used for restore/cancel-edit was not applied to the clear flow.
    - **Root cause**: `VitalSidePanel::clearChat()` cleared the UI messages and called `ClaudeApiClient::clearConversation()`, but never notified `FullInterface` to bump `api_request_generation_`. The restore and cancel-edit flows already did this correctly via their respective listener callbacks.
    - **Solution**: Added `sidePanelClearRequested()` to the `VitalSidePanel::Listener` interface, called from `clearChat()` before clearing API history. `FullInterface` implements it with the same 6-line invalidation block (bump generation counter, reset in-flight flag, clear queues) used by restore and cancel-edit.
    - **Key lesson**: The generation counter pattern (`api_request_generation_`) is the canonical way to invalidate in-flight async API callbacks. **Any new flow that resets chat state must also bump this counter.** Current invalidation points: `sidePanelRestoreRequested()`, `sidePanelCancelEditRequested()`, `sidePanelClearRequested()`.
    - Files: `src/interface/editor_sections/side_panel.h`, `src/interface/editor_sections/side_panel.cpp`, `src/interface/editor_sections/full_interface.h`, `src/interface/editor_sections/full_interface.cpp`

- **Mic icon invisible when drawn in paintBackground() — covered by OpenGL text editor**:
    - Drawing a microphone icon in `paintBackground()` was invisible because `OpenGlTextEditor` renders in the GL pass on top of the background texture.
    - **Solution**: Use `PlainShapeComponent` (an `OpenGlImageComponent` subclass) which renders in the GL pass alongside other OpenGL components. Set `setUseAlpha(true)` to enable non-premultiplied alpha blending so the color uniform's alpha channel works for hover effects.
    - For mouse interaction on overlaid icons inside a text editor: use `prompt_editor_->addMouseListener(this, false)` to forward events, and `e.getEventRelativeTo(this).getPosition()` to convert coordinates to the parent component's space.
    - To fix cursor staying as I-beam over the icon area, call `prompt_editor_->setMouseCursor()` based on hover state.
    - Files: `src/interface/editor_sections/side_panel.h`, `src/interface/editor_sections/side_panel.cpp`

- **Programmatic SVG icon paths render as black boxes when using stroked paths with bounding-box markers**:
    - Creating icons via JUCE `Path` with `addLineSegment()` / `startNewSubPath()` produces thin stroked lines. When rendered in a small area, the invisible bounding-box rectangles dominate the visual and the icon appears as a solid black box.
    - **Solution**: Use SVG path data (the `d` attribute from an SVG) parsed via `Drawable::createFromSVG()` or stored as a `Path` via `parseSVGPath()`. SVG paths produce clean filled shapes that scale correctly. Added `sendArrowIcon()` and `stopIcon()` to `paths.h` using this approach.
    - File: `src/interface/look_and_feel/paths.h`

- **Queued messages during multi-action leaving stranded step messages + queue dropping messages**:
    - When a user sent messages while multi-action was in progress, `submitMessage()` added a "Thinking..." system message that pushed the active step message out of reach of `updateStatusMessage()` (which only checked `messages_.back()`). Additionally, `clearThinkingMessage()` also only checked `back()`, so it couldn't find "Thinking..." when a queued user message sat after it. Separately, all 3 queue processing points used `pending.swapWith(queued_messages_)` then only processed `pending[0]`, silently dropping `pending[1+]`.
    - **Solution**: (1) `updateStatusMessage()` and `clearThinkingMessage()` now scan backwards from the end to find their target message types (kSystem/kStep or "Thinking..." respectively), handling interleaved kUser messages. (2) Moved "Thinking..." creation from `submitMessage()` to `sidePanelMessageSubmitted()` so it's only added when the message is actually processed, not when queuing. (3) Fixed all 3 queue dequeue points to use `queued_messages_.remove(0)` (one at a time) instead of `swapWith` (which dropped all but the first).
    - **Key lesson**: Methods operating on "the last message" need backward scanning when messages can be interleaved by async user input. Queue processing must dequeue one-at-a-time, not swap-and-drop.
    - Files: `src/interface/editor_sections/side_panel.cpp`, `src/interface/editor_sections/full_interface.cpp`

- **OpenGlButtonComponent::renderTextButton() always renders background quad — cannot hide with style or alpha**:
    - `kJustText` button style check is unreachable in `renderTextButton()` when button text is inactive (non-toggled state) — background quad draws unconditionally before the style branch.
    - `setAlpha(0.0f)` on JUCE Component has NO effect on OpenGL rendering. Vital's GL pipeline bypasses the standard JUCE alpha entirely.
    - `OpenGlQuad` has `setActive()` but no `isActive()` getter — track state with your own boolean if needed.
    - **Solution**: Set bounds to `(0,0,0,0)` + `setVisible(false)` to truly hide an OpenGL button. Handle clicks via `mouseUp()` hit testing on the parent component. For custom-rendered replacements, use `OpenGlQuad` (background) + `PlainShapeComponent` (icon) with manual hover/click logic.
    - Files: `src/interface/editor_sections/side_panel.cpp`, `src/interface/look_and_feel/paths.h`

- **Double "Thinking..." messages in voice recording modes**:
    - Both the Deepgram `is_final` callback (TALK/VOICE CHAT) AND `FullInterface::sidePanelMessageSubmitted()` were adding "Thinking..." messages. Result: two "Thinking..." indicators stacked in the chat UI.
    - **Root cause**: When voice input was first implemented, "Thinking..." was added explicitly in the recording callbacks. Later, "Thinking..." creation was centralized in `sidePanelMessageSubmitted()` (documented in TROUBLESHOOTING), but the voice callbacks were never updated to remove their redundant copies.
    - **Solution**: Removed `clearThinkingMessage()` + `addMessage("Thinking...", ...)` from three places: TALK `is_final` callback, VOICE CHAT `is_final` callback, and `stopRecording()` pending-text path. `sidePanelMessageSubmitted()` is the single canonical place that adds "Thinking...".
    - **Key lesson**: When centralizing behavior (like "Thinking..." creation), audit ALL code paths that trigger it — including async callbacks in voice recording flows. This bug recurred because the TALK `is_final` callback still had 3x `clearThinkingMessage()` + 1x `addMessage("Thinking...", kSystem)` that were missed in the first fix. Always grep for ALL call sites.
    - Files: `src/interface/editor_sections/side_panel.cpp`

- **Race condition between Deepgram async callback and timer-based recording stop**:
    - In TALK mode, both the Deepgram `is_final` callback (via `MessageManager::callAsync`) and the inactivity timer could fire and call `stopRecording()` / submit the same message, causing duplicate submissions.
    - **Root cause**: `MessageManager::callAsync` captures callback copies — disconnecting Deepgram doesn't prevent already-queued callbacks from running. The timer and callback had no mutual exclusion.
    - **Solution**: (1) TALK `is_final` callback now calls `stopRecording()` directly (timer is just a safety net). (2) Added `recording_mode_ != kRecordingTalk` guard in the callback to skip execution if recording already stopped.
    - **Key lesson**: `MessageManager::callAsync` queues copies — stopping/disconnecting the source doesn't cancel already-enqueued lambdas. Always guard with state checks.
    - Files: `src/interface/editor_sections/side_panel.cpp`

- **Side effects lost when removing a function call that had them (intro screen bugs)**:
    - Replacing `addMessage("Ready to create!", kSystem)` in `clearChat()` and `initializeApiClient()` with a centered logo intro screen removed implicit calls to `layoutMessages()`, `scrollToBottom()`, `repaintBackground()`, and `saveChatLog()` that `addMessage` triggered internally.
    - **Bug 1 (clear button not working):** After `clearChat()` emptied messages, no `repaintBackground()` was triggered, so the UI never refreshed to show the intro screen. Fix: add `layoutMessages()` + `repaintBackground()` at end of `clearChat()`.
    - **Bug 2 (lingering restore button):** The intro early-return in `paintChatMessages()` skipped the `restore_button_bounds_ = {}` reset that was inside the message-rendering loop. Since `paintBackground()` draws the restore button outside `paintChatMessages()`, it persisted on the intro screen. Fix: add `restore_button_bounds_ = {};` inside the `if (is_intro)` block.
    - **Bug 3 (clear button staying visible):** `layoutMessages()` sets `clear_button_active_` based on message count, but wasn't called after clearing. Same root cause as Bug 1.
    - **Key lesson:** When removing a function call that had side effects, trace ALL effects of the removed call and ensure each is still triggered where needed.
    - File: `src/interface/editor_sections/side_panel.cpp`

- **Multi-action one-shotting from parent message in conversation history**:
    - When multi-action flows split a request into sub-actions (e.g., "blippy jangly synth" → sound design translation → 3 sequential parameter changes), the LLM received the full original message (or translation text) in `conversation_history_` alongside the first sub-action. It read the full scope upfront and completed all steps on the first API call, returning "already done" text for subsequent sub-actions (massive token waste).
    - **Root cause**: `FullInterface::executeNextAction()` called `addToHistory("user", message)` at line 1180 in `full_interface.cpp` before executing sub-actions. This stored the full original message in history, giving the LLM context it shouldn't have for sequential execution.
    - **Solution**: (1) Removed line 1180 `addToHistory("user", message)` call. Keep the line 1154 call which stores the original user request ("make it blippy") before sound design reroute — this is needed for follow-up context. (2) Removed `cleanupSubActionHistory()` method entirely from `ClaudeApiClient` and its header declaration. Each sub-action's prompt + response stays in history permanently as the actual record of work done. No post-completion cleanup needed. (3) Removed `pre_multi_action_history_size_` member and all its reset calls from `FullInterface` (it tracked history size before multi-action to enable cleanup — no longer needed).
    - **Result**: Sound design multi-action history = original message + sub-action 1 + response + sub-action 2 + response. Non-sound-design = sub-action 1 + response + sub-action 2 + response. Each sub-action executes independently without seeing the full plan.
    - Files: `src/interface/editor_sections/full_interface.cpp/h`, `src/common/claude_api_client.cpp/h`