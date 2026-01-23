/* Copyright 2013-2019 Matt Tytel
 *
 * vital is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * vital is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with vital.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "JuceHeader.h"
#include "open_gl_multi_quad.h"
#include "open_gl_image_component.h"
#include "synth_section.h"
#include "synth_button.h"

#include <vector>
#include <string>

struct ChatMessage {
  std::string text;
  bool is_user;  // true = user message (dark grey), false = response (light grey)
  
  ChatMessage(const std::string& t, bool user) : text(t), is_user(user) {}
};

class ChatPanelSection : public SynthSection, public TextEditor::Listener, public ScrollBar::Listener {
  public:
    static constexpr int kInputHeight = 80;
    static constexpr int kButtonWidth = 60;
    static constexpr int kButtonHeight = 30;
    static constexpr int kPadding = 8;
    static constexpr int kMessagePadding = 6;
    static constexpr int kBubbleRounding = 8;
    static constexpr int kScrollBarWidth = 12;
    static constexpr float kScrollSensitivity = 200.0f;

    ChatPanelSection(const String& name);
    virtual ~ChatPanelSection() = default;

    void paintBackground(Graphics& g) override;
    void resized() override;
    
    void textEditorReturnKeyPressed(TextEditor& editor) override;
    void textEditorTextChanged(TextEditor& editor) override;
    void buttonClicked(Button* clicked_button) override;
    
    void scrollBarMoved(ScrollBar* scroll_bar, double range_start) override;
    void mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) override;
    
    void sendMessage();
    void addUserMessage(const std::string& text);
    void addResponseMessage(const std::string& text);
    
    void renderOpenGlComponents(OpenGlWrapper& open_gl, bool animate) override;

  private:
    void paintMessages(Graphics& g);
    void paintMessageBubble(Graphics& g, const ChatMessage& message, int y, int width, int height);
    int calculateMessageHeight(const std::string& text, int width);
    int getTotalMessagesHeight();
    void setScrollBarRange();
    void updateMessageDisplay();

    OpenGlQuad background_;
    OpenGlQuad input_background_;
    
    std::vector<ChatMessage> messages_;
    float view_position_;
    
    std::unique_ptr<OpenGlTextEditor> input_editor_;
    std::unique_ptr<OpenGlToggleButton> send_button_;
    std::unique_ptr<OpenGlScrollBar> scroll_bar_;
    
    std::unique_ptr<PlainTextComponent> title_text_;
    
    Rectangle<int> messages_area_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ChatPanelSection)
};
