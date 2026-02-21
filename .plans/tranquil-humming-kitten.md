# Chat Interface Implementation Plan for VitalSidePanel

## Overview

Add a scrollable chat area with message bubbles to VitalSidePanel, supporting:
- Enter key or button click to submit messages
- Text validation (reject empty/whitespace)
- User messages displayed in dark rounded bubbles
- System messages (like "Thinking...") displayed without bubbles
- Auto-scroll to latest message

## Architecture Decision

**Keep everything in side_panel.h/cpp** using nested classes rather than creating separate files. This:
- Avoids unity build complexity
- Keeps chat logic contained
- Follows the pattern used by ModulationViewport (nested in modulation_matrix.h)

## Files to Modify

1. **[side_panel.h](src/interface/editor_sections/side_panel.h)** - Add new classes and members
2. **[side_panel.cpp](src/interface/editor_sections/side_panel.cpp)** - Implement chat functionality

## Implementation Details

### 1. Add ChatViewport Class (nested in side_panel.h)

```cpp
class ChatViewport : public Viewport {
  public:
    class Listener {
      public:
        virtual ~Listener() = default;
        virtual void chatScrolled(int position) = 0;
    };

    void addListener(Listener* listener) { listeners_.push_back(listener); }
    void visibleAreaChanged(const Rectangle<int>& visible_area) override {
      for (Listener* listener : listeners_)
        listener->chatScrolled(visible_area.getY());
      Viewport::visibleAreaChanged(visible_area);
    }
  private:
    std::vector<Listener*> listeners_;
};
```

### 2. Add ChatMessage Class (nested in side_panel.h)

Represents a single message with optional rounded background:

```cpp
class ChatMessage : public SynthSection {
  public:
    enum Type { kUser, kSystem };

    ChatMessage(const String& text, Type type);
    void resized() override;
    void paintBackground(Graphics& g) override;
    int calculateHeight(int width) const;

  private:
    String text_;
    Type type_;
    OpenGlQuad background_;  // Only rendered for kUser type
    std::unique_ptr<PlainTextComponent> text_component_;
};
```

### 3. Modify VitalSidePanel Class

**New inheritance:**
- Add `TextEditor::Listener` for Enter key handling
- Add `ScrollBar::Listener` for scrollbar sync
- Add `ChatViewport::Listener` for scroll notifications

**New members:**
```cpp
ChatViewport chat_viewport_;
Component chat_container_;
std::unique_ptr<OpenGlScrollBar> scroll_bar_;
std::vector<std::unique_ptr<ChatMessage>> messages_;
CriticalSection open_gl_critical_section_;  // Thread safety
```

**New methods:**
```cpp
void textEditorReturnKeyPressed(TextEditor& editor) override;
void scrollBarMoved(ScrollBar*, double range_start) override;
void chatScrolled(int position) override;
void submitMessage();
void addMessage(const String& text, ChatMessage::Type type);
void layoutMessages();
void scrollToBottom();
void setScrollBarRange();
```

### 4. Key Implementation Steps

#### Constructor changes:
1. Create and add chat_viewport_ with chat_container_ as viewed component
2. Create OpenGlScrollBar and add its OpenGL component
3. **Change `setReturnKeyStartsNewLine(false)`** so Enter submits instead of newline
4. Add `this` as listener to prompt_editor_

#### resized() changes:
1. Calculate chat area bounds: from title bottom to textarea top
2. Position chat_viewport_ in that area
3. Position scroll_bar_ on right edge of chat area
4. Call layoutMessages()

#### submitMessage():
```cpp
void VitalSidePanel::submitMessage() {
    String text = prompt_editor_->getText().trim();
    if (text.isEmpty())
        return;

    addMessage(text, ChatMessage::kUser);
    prompt_editor_->clear();
    prompt_editor_->redoImage();
    addMessage("Thinking...", ChatMessage::kSystem);

    for (Listener* listener : listeners_)
        listener->sidePanelMessageSubmitted(text);
}
```

#### addMessage():
1. Create ChatMessage with text and type
2. Add to messages_ vector
3. Add as child to chat_container_
4. Register OpenGL components with addOpenGlComponent()
5. Call layoutMessages()
6. Call scrollToBottom()

#### layoutMessages():
1. Lock critical section
2. Calculate total height (sum of message heights + spacing)
3. Position each message vertically
4. Resize chat_container_ to total height
5. Call setScrollBarRange()

### 5. Color Scheme

| Element | Skin Color |
|---------|------------|
| User bubble bg | `kWidgetPrimary1` darkened by 0.3 |
| Message text | `kBodyText` |
| System text | `kBodyText` with 0.7 alpha |
| Scrollbar | `kLightenScreen` |

### 6. Thread Safety

Use `CriticalSection open_gl_critical_section_` and lock when:
- Modifying messages_ vector
- Modifying chat_container_ children
- In scrollBarMoved() when changing viewport position

Pattern from ModulationMatrix:
```cpp
void VitalSidePanel::scrollBarMoved(ScrollBar*, double range_start) {
    ScopedLock lock(open_gl_critical_section_);
    chat_viewport_.setViewPosition(Point<int>(0, (int)range_start));
}
```

### 7. Update Listener Interface

Add new callback for message submission:
```cpp
class Listener {
  public:
    virtual ~Listener() = default;
    virtual void sidePanelButtonClicked() = 0;
    virtual void sidePanelMessageSubmitted(const String& message) {}  // New, with default
};
```

## Verification Steps

1. Build the project: `./build_macos.sh --no-run`
2. Run the app and open the side panel
3. Test scenarios:
   - Type text and press Enter - message should appear in dark bubble
   - Click Send button - same behavior
   - Submit empty/whitespace - nothing should happen
   - "Thinking..." should appear after user message
   - Multiple messages should scroll properly
   - Scrollbar should appear when content exceeds viewport

## Potential Issues & Mitigations

1. **Text height calculation before parent set**: Calculate height using explicit font, not Skin values, until component is added
2. **OpenGL rendering during scroll**: Use CriticalSection to prevent race conditions
3. **Message limit**: Consider capping at 50-100 messages to prevent memory growth (can add later)
