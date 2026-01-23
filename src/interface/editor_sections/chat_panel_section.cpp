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

#include "chat_panel_section.h"
#include "fonts.h"
#include "skin.h"

ChatPanelSection::ChatPanelSection(const String& name) : SynthSection(name),
                                                          background_(Shaders::kRoundedRectangleFragment),
                                                          input_background_(Shaders::kRoundedRectangleFragment),
                                                          view_position_(0.0f) {
  addOpenGlComponent(&background_);
  addOpenGlComponent(&input_background_);
  
  title_text_ = std::make_unique<PlainTextComponent>("Chat", "CHAT");
  addOpenGlComponent(title_text_.get());
  title_text_->setFontType(PlainTextComponent::kLight);
  title_text_->setJustification(Justification::centredLeft);

#if !defined(NO_TEXT_ENTRY)
  input_editor_ = std::make_unique<OpenGlTextEditor>("ChatInput");
  input_editor_->addListener(this);
  input_editor_->setMultiLine(true, true);
  input_editor_->setReturnKeyStartsNewLine(false);
  addAndMakeVisible(input_editor_.get());
  addOpenGlComponent(input_editor_->getImageComponent());
#endif

  send_button_ = std::make_unique<OpenGlToggleButton>("Send");
  send_button_->setButtonText("Send");
  send_button_->setUiButton(true);
  send_button_->addListener(this);
  addAndMakeVisible(send_button_.get());
  addOpenGlComponent(send_button_->getGlComponent());

  scroll_bar_ = std::make_unique<OpenGlScrollBar>();
  addAndMakeVisible(scroll_bar_.get());
  addOpenGlComponent(scroll_bar_->getGlComponent());
  scroll_bar_->addListener(this);
}

void ChatPanelSection::paintBackground(Graphics& g) {
  // Paint the background
  g.setColour(findColour(Skin::kBody, true));
  g.fillRoundedRectangle(getLocalBounds().toFloat(), findValue(Skin::kBodyRounding));
  
  paintMessages(g);
}

void ChatPanelSection::resized() {
  float size_ratio = getSizeRatio();
  int padding = kPadding * size_ratio;
  int input_height = kInputHeight * size_ratio;
  int button_width = kButtonWidth * size_ratio;
  int button_height = kButtonHeight * size_ratio;
  int scroll_bar_width = kScrollBarWidth * size_ratio;
  int title_height = 24 * size_ratio;
  
  // Background
  background_.setBounds(getLocalBounds());
  background_.setRounding(findValue(Skin::kBodyRounding));
  background_.setColor(findColour(Skin::kBody, true));
  
  // Title
  title_text_->setBounds(padding, padding, getWidth() - 2 * padding, title_height);
  title_text_->setTextSize(14.0f * size_ratio);
  title_text_->setColor(findColour(Skin::kBodyText, true));
  
  // Messages area (above input, below title)
  int messages_top = title_height + padding * 2;
  int messages_height = getHeight() - messages_top - input_height - padding * 2;
  messages_area_ = Rectangle<int>(padding, messages_top, 
                                   getWidth() - 2 * padding - scroll_bar_width, 
                                   messages_height);
  
  // Scroll bar
  scroll_bar_->setBounds(getWidth() - scroll_bar_width - padding, messages_top,
                         scroll_bar_width, messages_height);
  setScrollBarRange();
  
  // Input area at the bottom
  int input_y = getHeight() - input_height - padding;
  int input_width = getWidth() - button_width - 3 * padding;
  
  input_background_.setBounds(padding, input_y, getWidth() - 2 * padding, input_height);
  input_background_.setRounding(kBubbleRounding * size_ratio);
  input_background_.setColor(findColour(Skin::kTextEditorBackground, true));
  
  if (input_editor_) {
    input_editor_->setBounds(padding + 4, input_y + 4, input_width - 8, input_height - 8);
    
    Colour text_color = findColour(Skin::kBodyText, true);
    input_editor_->setColour(CaretComponent::caretColourId, findColour(Skin::kTextEditorCaret, true));
    input_editor_->setColour(TextEditor::textColourId, text_color);
    input_editor_->setColour(TextEditor::highlightedTextColourId, findColour(Skin::kBodyText, true));
    input_editor_->setColour(TextEditor::highlightColourId, findColour(Skin::kTextEditorSelection, true));
    input_editor_->setTextToShowWhenEmpty("Type a message...", text_color.withAlpha(0.5f));
    input_editor_->redoImage();
  }
  
  send_button_->setBounds(getWidth() - button_width - padding, 
                          input_y + (input_height - button_height) / 2,
                          button_width, button_height);
}

void ChatPanelSection::paintMessages(Graphics& g) {
  if (messages_.empty())
    return;
  
  float size_ratio = getSizeRatio();
  int padding = kPadding * size_ratio;
  int message_padding = kMessagePadding * size_ratio;
  int bubble_rounding = kBubbleRounding * size_ratio;
  int max_bubble_width = messages_area_.getWidth() * 0.85f;
  
  Font message_font = Fonts::instance()->proportional_light().withPointHeight(12.0f * size_ratio);
  g.setFont(message_font);
  
  int current_y = messages_area_.getY() - static_cast<int>(view_position_);
  
  for (const auto& message : messages_) {
    int text_width = max_bubble_width - 2 * message_padding;
    int text_height = calculateMessageHeight(message.text, text_width);
    int bubble_height = text_height + 2 * message_padding;
    
    // Only paint if visible
    if (current_y + bubble_height > messages_area_.getY() && current_y < messages_area_.getBottom()) {
      int bubble_width = std::min(max_bubble_width, 
                                   static_cast<int>(message_font.getStringWidth(message.text)) + 2 * message_padding + 10);
      bubble_width = std::max(bubble_width, 60);
      
      int bubble_x;
      if (message.is_user) {
        // User messages align right, dark grey
        bubble_x = messages_area_.getRight() - bubble_width;
        g.setColour(Colour(0xff3a3a3a));
      } else {
        // Response messages align left, lighter grey
        bubble_x = messages_area_.getX();
        g.setColour(Colour(0xff5a5a5a));
      }
      
      // Draw bubble background
      g.fillRoundedRectangle(static_cast<float>(bubble_x), static_cast<float>(current_y),
                             static_cast<float>(bubble_width), static_cast<float>(bubble_height),
                             static_cast<float>(bubble_rounding));
      
      // Draw text
      g.setColour(Colours::white);
      g.drawFittedText(message.text, 
                       bubble_x + message_padding, current_y + message_padding,
                       bubble_width - 2 * message_padding, text_height,
                       Justification::topLeft, 100, 1.0f);
    }
    
    current_y += bubble_height + message_padding;
  }
}

void ChatPanelSection::paintMessageBubble(Graphics& g, const ChatMessage& message, 
                                           int y, int width, int height) {
  // This is called from paintMessages for individual bubbles
}

int ChatPanelSection::calculateMessageHeight(const std::string& text, int width) {
  float size_ratio = getSizeRatio();
  Font message_font = Fonts::instance()->proportional_light().withPointHeight(12.0f * size_ratio);
  
  AttributedString attributed;
  attributed.append(text);
  attributed.setFont(message_font);
  attributed.setJustification(Justification::topLeft);
  
  TextLayout layout;
  layout.createLayout(attributed, static_cast<float>(width));
  
  return static_cast<int>(layout.getHeight()) + 4;
}

int ChatPanelSection::getTotalMessagesHeight() {
  if (messages_.empty())
    return 0;
  
  float size_ratio = getSizeRatio();
  int message_padding = kMessagePadding * size_ratio;
  int max_bubble_width = messages_area_.getWidth() * 0.85f;
  int text_width = max_bubble_width - 2 * message_padding;
  
  int total_height = 0;
  for (const auto& message : messages_) {
    int text_height = calculateMessageHeight(message.text, text_width);
    total_height += text_height + 2 * message_padding + message_padding;
  }
  
  return total_height;
}

void ChatPanelSection::setScrollBarRange() {
  int total_height = getTotalMessagesHeight();
  int visible_height = messages_area_.getHeight();
  
  scroll_bar_->setRangeLimits(0.0, std::max(total_height, visible_height));
  scroll_bar_->setCurrentRange(view_position_, visible_height);
}

void ChatPanelSection::updateMessageDisplay() {
  setScrollBarRange();
  
  // Auto-scroll to bottom when new message is added
  int total_height = getTotalMessagesHeight();
  int visible_height = messages_area_.getHeight();
  if (total_height > visible_height) {
    view_position_ = total_height - visible_height;
    scroll_bar_->setCurrentRange(view_position_, visible_height);
  }
  
  repaintBackground();
}

void ChatPanelSection::textEditorReturnKeyPressed(TextEditor& editor) {
  sendMessage();
}

void ChatPanelSection::textEditorTextChanged(TextEditor& editor) {
  // Optional: could add typing indicator here
}

void ChatPanelSection::buttonClicked(Button* clicked_button) {
  if (clicked_button == send_button_.get()) {
    sendMessage();
  }
}

void ChatPanelSection::scrollBarMoved(ScrollBar* scroll_bar, double range_start) {
  view_position_ = static_cast<float>(range_start);
  repaintBackground();
}

void ChatPanelSection::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) {
  if (messages_area_.contains(e.getPosition())) {
    float scroll_amount = wheel.deltaY * kScrollSensitivity * getSizeRatio();
    int total_height = getTotalMessagesHeight();
    int visible_height = messages_area_.getHeight();
    
    view_position_ = std::max(0.0f, std::min(view_position_ - scroll_amount,
                                              static_cast<float>(total_height - visible_height)));
    scroll_bar_->setCurrentRange(view_position_, visible_height);
    repaintBackground();
  } else {
    SynthSection::mouseWheelMove(e, wheel);
  }
}

void ChatPanelSection::sendMessage() {
  if (input_editor_ == nullptr)
    return;
  
  String text = input_editor_->getText().trim();
  if (text.isEmpty())
    return;
  
  // Add user message
  addUserMessage(text.toStdString());
  
  // Clear input
  input_editor_->setText("");
  
  // Add dummy response
  addResponseMessage("This is a response");
}

void ChatPanelSection::addUserMessage(const std::string& text) {
  messages_.emplace_back(text, true);
  updateMessageDisplay();
}

void ChatPanelSection::addResponseMessage(const std::string& text) {
  messages_.emplace_back(text, false);
  updateMessageDisplay();
}

void ChatPanelSection::renderOpenGlComponents(OpenGlWrapper& open_gl, bool animate) {
  SynthSection::renderOpenGlComponents(open_gl, animate);
}
