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
#include "synth_section.h"
#include "open_gl_multi_quad.h"

class OpenGlToggleButton;
class OpenGlTextEditor;
class Fonts;

// Simple data structure for chat messages
struct ChatMessage
{
    enum Type
    {
        kUser,
        kSystem
    };

    String text;
    Type type;
    int y_position = 0;
    int height = 0;

    ChatMessage(const String &t, Type tp) : text(t), type(tp) {}

    static int calculateHeight(const String &text, int width, float fontSize);

    static constexpr int kPadding = 12;
    static constexpr float kFontSize = 25.0f;
    static constexpr float kCornerRadius = 8.0f;
};

class VitalSidePanel : public SynthSection,
                       public TextEditor::Listener,
                       public ScrollBar::Listener
{
public:
    class Listener
    {
    public:
        virtual ~Listener() = default;
        virtual void sidePanelButtonClicked() = 0;
        virtual void sidePanelMessageSubmitted(const String &message) {}
    };

    VitalSidePanel();
    virtual ~VitalSidePanel();

    void paintBackground(Graphics &g) override;
    void paintBackgroundShadow(Graphics &g) override { paintTabShadow(g); }
    void resized() override;
    void buttonClicked(Button *clicked_button) override;

    // TextEditor::Listener
    void textEditorReturnKeyPressed(TextEditor &editor) override;

    // ScrollBar::Listener
    void scrollBarMoved(ScrollBar *scrollBar, double newRangeStart) override;

    // Mouse wheel scrolling
    void mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) override;

    void addListener(Listener *listener) { listeners_.push_back(listener); }

    // Chat methods
    void submitMessage();
    void addMessage(const String &text, ChatMessage::Type type);
    void clearThinkingMessage();
    void addResponseMessage(const String &text);

private:
    void layoutMessages();
    void scrollToBottom();
    void setScrollBarRange();
    void paintChatMessages(Graphics &g);

    std::vector<Listener *> listeners_;
    std::unique_ptr<OpenGlTextEditor> prompt_editor_;
    std::unique_ptr<OpenGlToggleButton> action_button_;

    // Chat state
    std::unique_ptr<OpenGlScrollBar> scroll_bar_;
    std::vector<ChatMessage> messages_;
    Rectangle<int> chat_bounds_;
    int total_content_height_ = 0;
    int scroll_position_ = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VitalSidePanel)
};
