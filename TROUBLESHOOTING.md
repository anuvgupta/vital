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