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

- **Accessing protected methods on SynthBase**:
    - `SynthBase::saveToJson()` is protected - can't call directly from UI code like `FullInterface`.
    - **Solution**: Add a public wrapper method like `getStateAsJson()` (wraps `saveToJson()`) or `loadStateFromJson()` (wraps `loadFromJson()`).
    - This project uses an older nlohmann json version - use `.count("key")` instead of `.contains("key")`.