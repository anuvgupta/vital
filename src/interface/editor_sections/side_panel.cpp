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

#include "side_panel.h"

#include "fonts.h"
#include "skin.h"
#include "synth_button.h"

// ============================================================================
// ChatMessage Implementation
// ============================================================================

int ChatMessage::calculateHeight(const String& text, int width, float fontSize) {
  Font font = Fonts::instance()->proportional_light().withPointHeight(fontSize);
  int text_width = width - 2 * kPadding;

  // Use JUCE's TextLayout to calculate wrapped text height
  AttributedString attr_string;
  attr_string.setText(text);
  attr_string.setFont(font);
  attr_string.setJustification(Justification::topLeft);

  TextLayout layout;
  layout.createLayout(attr_string, (float)text_width);

  return (int)layout.getHeight() + 2 * kPadding;
}

// ============================================================================
// VitalSidePanel Implementation
// ============================================================================

VitalSidePanel::VitalSidePanel() : SynthSection("side_panel") {
  // Set up custom OpenGL scrollbar
  scroll_bar_ = std::make_unique<OpenGlScrollBar>();
  addAndMakeVisible(scroll_bar_.get());
  addOpenGlComponent(scroll_bar_->getGlComponent());
  scroll_bar_->addListener(this);

#if !defined(NO_TEXT_ENTRY)
  prompt_editor_ = std::make_unique<OpenGlTextEditor>("Prompt");
  prompt_editor_->setJustification(Justification::topLeft);
  addAndMakeVisible(prompt_editor_.get());
  addOpenGlComponent(prompt_editor_->getImageComponent());
  prompt_editor_->setMultiLine(true, true);
  prompt_editor_->setReturnKeyStartsNewLine(false);  // Enter submits, Shift+Enter for newline
  prompt_editor_->addListener(this);
#endif

  action_button_ = std::make_unique<OpenGlToggleButton>("Send");
  addButton(action_button_.get());
  action_button_->setUiButton(true);
  action_button_->setText("SEND");

  setSkinOverride(Skin::kNone);
}

VitalSidePanel::~VitalSidePanel() {
  scroll_bar_->removeListener(this);
}

void VitalSidePanel::paintBackground(Graphics& g) {
  paintBody(g);
  paintBorder(g);

  // Draw panel title
  g.setColour(findColour(Skin::kBodyText, true));
  g.setFont(Fonts::instance()->proportional_regular().withPointHeight(28.0f));

  int title_height = 30;
  int padding = findValue(Skin::kLargePadding);
  Rectangle<int> title_bounds(padding, padding, getWidth() - 2 * padding, title_height);
  g.drawText("CHAT", title_bounds, Justification::centredLeft);

  // Draw chat messages
  paintChatMessages(g);
}

void VitalSidePanel::paintChatMessages(Graphics& g) {
  if (chat_bounds_.isEmpty())
    return;

  // Set up clipping region for chat area
  Graphics::ScopedSaveState save_state(g);
  g.reduceClipRegion(chat_bounds_);

  Font font = Fonts::instance()->proportional_light().withPointHeight(ChatMessage::kFontSize);
  g.setFont(font);

  Colour bubble_color = findColour(Skin::kWidgetPrimary1, true).darker(0.4f);
  Colour text_color = findColour(Skin::kBodyText, true);
  Colour system_text_color = text_color.withAlpha(0.7f);

  for (const auto& message : messages_) {
    // Calculate message position relative to chat area with scroll offset
    int msg_y = chat_bounds_.getY() + message.y_position - scroll_position_;
    int msg_bottom = msg_y + message.height;

    // Skip if completely outside visible area
    if (msg_bottom < chat_bounds_.getY() || msg_y > chat_bounds_.getBottom())
      continue;

    Rectangle<int> msg_bounds(chat_bounds_.getX(), msg_y,
                               chat_bounds_.getWidth(), message.height);

    if (message.type == ChatMessage::kUser) {
      // Draw rounded rectangle background for user messages
      g.setColour(bubble_color);
      g.fillRoundedRectangle(msg_bounds.toFloat(), ChatMessage::kCornerRadius);
      g.setColour(text_color);
    } else {
      g.setColour(system_text_color);
    }

    // Draw text with padding
    Rectangle<int> text_bounds(msg_bounds.getX() + ChatMessage::kPadding,
                                msg_bounds.getY() + ChatMessage::kPadding,
                                msg_bounds.getWidth() - 2 * ChatMessage::kPadding,
                                msg_bounds.getHeight() - 2 * ChatMessage::kPadding);
    g.drawFittedText(message.text, text_bounds, Justification::topLeft, 100, 1.0f);
  }
}

void VitalSidePanel::resized() {
  static constexpr float kScrollBarWidth = 10.0f;

  int padding = findValue(Skin::kLargePadding);
  int widget_margin = findValue(Skin::kWidgetMargin);

  int button_height = 50;
  int button_width = getWidth() - 2 * padding;
  int textarea_height = 180;
  int title_height = 30;

  // Button at the bottom
  int button_y = getHeight() - padding - button_height;
  action_button_->setBounds(padding, button_y, button_width, button_height);
  action_button_->getGlComponent()->text().setTextSize(22.0f);

  // Textarea above the button
  int textarea_y = button_y - widget_margin - textarea_height;
#if !defined(NO_TEXT_ENTRY)
  if (prompt_editor_) {
    prompt_editor_->setBounds(padding, textarea_y, button_width, textarea_height);

    Colour empty_color = findColour(Skin::kBodyText, true);
    empty_color = empty_color.withAlpha(0.5f * empty_color.getFloatAlpha());
    prompt_editor_->setTextToShowWhenEmpty("Describe your synth patch. What do you want to hear?", empty_color);
    prompt_editor_->setColour(CaretComponent::caretColourId, findColour(Skin::kTextEditorCaret, true));
    prompt_editor_->setColour(TextEditor::textColourId, findColour(Skin::kBodyText, true));
    prompt_editor_->setColour(TextEditor::highlightedTextColourId, findColour(Skin::kBodyText, true));
    prompt_editor_->setColour(TextEditor::highlightColourId, findColour(Skin::kTextEditorSelection, true));

    float font_size = 24.0f;
    prompt_editor_->setFont(Fonts::instance()->proportional_light().withPointHeight(font_size));
    prompt_editor_->redoImage();
  }
#endif

  // Chat area between title and textarea
  int chat_top = padding + title_height + widget_margin;
  int chat_bottom = textarea_y - widget_margin;
  int chat_height = chat_bottom - chat_top;
  int chat_width = button_width - (int)kScrollBarWidth - widget_margin;

  chat_bounds_ = Rectangle<int>(padding, chat_top, chat_width, chat_height);

  // Scrollbar on the right side of chat area
  scroll_bar_->setBounds(padding + chat_width + widget_margin, chat_top,
                         (int)kScrollBarWidth, chat_height);
  scroll_bar_->setColor(findColour(Skin::kLightenScreen, true));

  // Layout messages and update scrollbar
  layoutMessages();

  SynthSection::resized();
}

void VitalSidePanel::buttonClicked(Button* clicked_button) {
  if (clicked_button == action_button_.get()) {
    submitMessage();
    for (Listener* listener : listeners_)
      listener->sidePanelButtonClicked();
  }
  else {
    SynthSection::buttonClicked(clicked_button);
  }
}

void VitalSidePanel::textEditorReturnKeyPressed(TextEditor& editor) {
  submitMessage();
}

void VitalSidePanel::scrollBarMoved(ScrollBar* scrollBar, double newRangeStart) {
  scroll_position_ = (int)newRangeStart;
  repaintBackground();
}

void VitalSidePanel::submitMessage() {
#if !defined(NO_TEXT_ENTRY)
  if (!prompt_editor_)
    return;

  String text = prompt_editor_->getText().trim();
  if (text.isEmpty())
    return;

  // Add user message
  addMessage(text, ChatMessage::kUser);

  // Clear the input
  prompt_editor_->clear();
  prompt_editor_->redoImage();

  // Add thinking indicator
  addMessage("Thinking...", ChatMessage::kSystem);

  // Notify listeners
  for (Listener* listener : listeners_)
    listener->sidePanelMessageSubmitted(text);
#endif
}

void VitalSidePanel::addMessage(const String& text, ChatMessage::Type type) {
  messages_.emplace_back(text, type);
  layoutMessages();
  scrollToBottom();
  repaintBackground();
}

void VitalSidePanel::clearThinkingMessage() {
  // Remove the last message if it's a "Thinking..." system message
  if (!messages_.empty()) {
    auto& last = messages_.back();
    if (last.type == ChatMessage::kSystem && last.text == "Thinking...") {
      messages_.pop_back();
      layoutMessages();
      repaintBackground();
    }
  }
}

void VitalSidePanel::addResponseMessage(const String& text) {
  clearThinkingMessage();
  addMessage(text, ChatMessage::kSystem);
}

void VitalSidePanel::layoutMessages() {
  static constexpr int kMessageSpacing = 8;

  int message_width = chat_bounds_.getWidth();
  if (message_width <= 0)
    return;

  int y_position = 0;

  for (auto& message : messages_) {
    int height = ChatMessage::calculateHeight(message.text, message_width, ChatMessage::kFontSize);
    message.y_position = y_position;
    message.height = height;
    y_position += height + kMessageSpacing;
  }

  // Calculate total content height
  total_content_height_ = y_position > 0 ? y_position - kMessageSpacing : 0;

  setScrollBarRange();
}

void VitalSidePanel::scrollToBottom() {
  int visible_height = chat_bounds_.getHeight();

  if (total_content_height_ > visible_height) {
    scroll_position_ = total_content_height_ - visible_height;
    scroll_bar_->setCurrentRange(scroll_position_, visible_height);
  } else {
    scroll_position_ = 0;
  }
}

void VitalSidePanel::setScrollBarRange() {
  int visible_height = chat_bounds_.getHeight();
  scroll_bar_->setRangeLimits(0.0, std::max(total_content_height_, visible_height));
  scroll_bar_->setCurrentRange(scroll_position_, visible_height, dontSendNotification);
}
