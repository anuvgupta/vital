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
#include "shaders.h"
#include <cmath>

// ============================================================================
// ChatMessage Implementation
// ============================================================================

namespace {

static constexpr int kBlockSpacing = 6;
static constexpr int kCodeBlockPadding = 8;
static constexpr int kListIndent = 16;
static constexpr int kQuoteBorderWidth = 3;
static constexpr int kQuoteIndent = 10;
static constexpr float kHeadingScale[] = { 1.5f, 1.3f, 1.15f, 1.0f, 0.9f, 0.85f };

static const String kAskButtonLabel = "ASK";
static const String kTalkButtonLabel = "TALK";
static const String kStopButtonLabel = "STOP";
static const String kSubmitButtonText = "COOK";

Font getRegularFont(float size) {
    return Fonts::instance()->proportional_regular().withPointHeight(size);
}

Font getBoldFont(float size) {
    return Fonts::instance()->proportional_bold().withPointHeight(size);
}

Font getMonoFont(float size) {
    return Fonts::instance()->monospace().withPointHeight(size);
}

Font getItalicFont(float size) {
    return Fonts::instance()->proportional_italic().withPointHeight(size);
}

Font getBoldItalicFont(float size) {
    return Fonts::instance()->proportional_bold_italic().withPointHeight(size);
}

AttributedString buildStyledString(const std::vector<StyledRun>& runs, float fontSize, Colour textColour) {
    AttributedString attr;
    attr.setJustification(Justification::topLeft);

    for (const auto& run : runs) {
        Font font;
        if (run.code) {
            font = getMonoFont(fontSize * 0.9f);
        } else if (run.bold && run.italic) {
            font = getBoldItalicFont(fontSize);
        } else if (run.bold) {
            font = getBoldFont(fontSize);
        } else if (run.italic) {
            font = getItalicFont(fontSize);
        } else {
            font = getRegularFont(fontSize);
        }
        attr.append(run.text, font, textColour);
    }

    return attr;
}

int measureBlockHeight(const MarkdownBlock& block, int width, float fontSize) {
    switch (block.type) {
        case MarkdownBlock::kHeading: {
            int level = jlimit(1, 6, block.level);
            float scale = kHeadingScale[level - 1];
            auto attr = buildStyledString(block.runs, fontSize * scale, Colours::white);
            TextLayout layout;
            layout.createLayout(attr, (float)width);
            return (int)std::ceil(layout.getHeight());
        }

        case MarkdownBlock::kCodeBlock: {
            Font mono = getMonoFont(fontSize * 0.85f);
            AttributedString attr;
            attr.setText(block.code_text);
            attr.setFont(mono);
            attr.setJustification(Justification::topLeft);
            TextLayout layout;
            layout.createLayout(attr, (float)(width - 2 * kCodeBlockPadding));
            return (int)std::ceil(layout.getHeight()) + 2 * kCodeBlockPadding;
        }

        case MarkdownBlock::kListItem: {
            int indent = kListIndent * block.level;
            int text_width = width - indent;
            auto attr = buildStyledString(block.runs, fontSize, Colours::white);
            TextLayout layout;
            layout.createLayout(attr, (float)text_width);
            return (int)std::ceil(layout.getHeight());
        }

        case MarkdownBlock::kBlockQuote: {
            int indent = kQuoteBorderWidth + kQuoteIndent;
            auto attr = buildStyledString(block.runs, fontSize, Colours::white);
            TextLayout layout;
            layout.createLayout(attr, (float)(width - indent));
            return (int)std::ceil(layout.getHeight());
        }

        case MarkdownBlock::kHorizontalRule:
            return 8;

        case MarkdownBlock::kParagraph:
        default: {
            auto attr = buildStyledString(block.runs, fontSize, Colours::white);
            TextLayout layout;
            layout.createLayout(attr, (float)width);
            return (int)std::ceil(layout.getHeight());
        }
    }
}

} // anonymous namespace

int ChatMessage::calculateHeight(const String& text, int width, float fontSize) {
  Font font = Fonts::instance()->proportional_regular().withPointHeight(fontSize);
  int text_width = width - 2 * kPadding;

  AttributedString attr_string;
  attr_string.setText(text);
  attr_string.setFont(font);
  attr_string.setJustification(Justification::topLeft);

  TextLayout layout;
  layout.createLayout(attr_string, (float)text_width);

  return (int)std::ceil(layout.getHeight()) + 2 * kPadding;
}

int ChatMessage::calculateMarkdownHeight(const std::vector<MarkdownBlock>& blocks, int width, float fontSize) {
  int text_width = width - 2 * kPadding;
  int total = 0;
  int total_chars = 0;

  for (size_t i = 0; i < blocks.size(); ++i) {
      if (i > 0)
          total += kBlockSpacing;
      total += measureBlockHeight(blocks[i], text_width, fontSize);
      for (const auto& run : blocks[i].runs)
          total_chars += run.text.length();
      total_chars += blocks[i].code_text.length();
  }

  int height = total + 2 * kPadding;

  // Extra buffer for long messages to prevent cutoff
  if (total_chars > 200)
      height += (int)(fontSize * 0.5f);

  return height;
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

  action_button_ = std::make_unique<OpenGlToggleButton>("Cook");
  addButton(action_button_.get());
  action_button_->setUiButton(true);
  action_button_->setText(kSubmitButtonText);

  ask_button_ = std::make_unique<OpenGlToggleButton>("Ask");
  addButton(ask_button_.get());
  ask_button_->setUiButton(true);
  ask_button_->setText(kAskButtonLabel);

  talk_button_ = std::make_unique<OpenGlToggleButton>("Talk");
  addButton(talk_button_.get());
  talk_button_->setUiButton(true);
  talk_button_->setText(kTalkButtonLabel);

  mic_capture_ = std::make_unique<MicrophoneCapture>();

  ask_recording_indicator_ = std::make_unique<OpenGlQuad>(Shaders::kCircleFragment);
  addOpenGlComponent(ask_recording_indicator_.get());
  ask_recording_indicator_->setColor(Colours::red.withAlpha(0.9f));
  ask_recording_indicator_->setActive(false);

  talk_recording_indicator_ = std::make_unique<OpenGlQuad>(Shaders::kCircleFragment);
  addOpenGlComponent(talk_recording_indicator_.get());
  talk_recording_indicator_->setColor(Colours::red.withAlpha(0.9f));
  talk_recording_indicator_->setActive(false);

  setSkinOverride(Skin::kNone);

  initializeApiClient();
  initializeDeepgramClient();
}

VitalSidePanel::~VitalSidePanel() {
  stopRecording();
  scroll_bar_->removeListener(this);
}

void VitalSidePanel::paintBackground(Graphics& g) {
  paintBody(g);
  paintBorder(g);

  // Draw panel title
  g.setColour(findColour(Skin::kBodyText, true));
  g.setFont(Fonts::instance()->proportional_regular().withPointHeight(size_ratio_ * 16.0f));

  int title_height = 30;
  int padding = findValue(Skin::kLargePadding);
  Rectangle<int> title_bounds(padding, padding, getWidth() - 2 * padding, title_height);
  g.drawText("SOUND DESIGNER", title_bounds, Justification::centredLeft);

  // Draw chat messages
  paintChatMessages(g);
}

void VitalSidePanel::paintChatMessages(Graphics& g) {
  if (chat_bounds_.isEmpty())
    return;

  Graphics::ScopedSaveState save_state(g);
  g.reduceClipRegion(chat_bounds_);

  float font_size = size_ratio_ * ChatMessage::kBaseFontSize;
  Font font = Fonts::instance()->proportional_regular().withPointHeight(font_size);
  g.setFont(font);

  Colour bubble_color = findColour(Skin::kWidgetPrimary1, true).darker(0.4f);
  Colour text_color = findColour(Skin::kBodyText, true);
  Colour system_text_color = text_color.withAlpha(0.98f);
  Colour code_bg_color = Colours::black.withAlpha(0.3f);
  Colour quote_border_color = text_color.withAlpha(0.3f);
  Colour hr_color = text_color.withAlpha(0.2f);

  for (const auto& message : messages_) {
    int msg_y = chat_bounds_.getY() + message.y_position - scroll_position_;
    int msg_bottom = msg_y + message.height;

    if (msg_bottom < chat_bounds_.getY() || msg_y > chat_bounds_.getBottom())
      continue;

    Rectangle<int> msg_bounds(chat_bounds_.getX(), msg_y,
                               chat_bounds_.getWidth(), message.height);

    if (message.type == ChatMessage::kUser) {
      g.setColour(bubble_color);
      g.fillRoundedRectangle(msg_bounds.toFloat(), ChatMessage::kCornerRadius);
    }

    Rectangle<float> text_bounds((float)(msg_bounds.getX() + ChatMessage::kPadding),
                                  (float)(msg_bounds.getY() + ChatMessage::kPadding),
                                  (float)(msg_bounds.getWidth() - 2 * ChatMessage::kPadding),
                                  (float)(msg_bounds.getHeight() - 2 * ChatMessage::kPadding));

    // User messages and non-markdown system messages: plain text
    if (message.type == ChatMessage::kUser || message.blocks.empty()) {
      Colour col = (message.type == ChatMessage::kUser) ? text_color : system_text_color;
      AttributedString attr_text;
      attr_text.setText(message.text);
      attr_text.setFont(font);
      attr_text.setColour(col);
      attr_text.setJustification(Justification::topLeft);

      TextLayout text_layout;
      text_layout.createLayout(attr_text, text_bounds.getWidth());
      text_layout.draw(g, text_bounds);
      continue;
    }

    // Markdown rendering for system messages
    float y = text_bounds.getY();
    float width = text_bounds.getWidth();
    float x = text_bounds.getX();
    float fontSize = font_size;  // Uses scaled font_size from above

    for (size_t i = 0; i < message.blocks.size(); ++i) {
      if (i > 0)
        y += kBlockSpacing;

      const auto& block = message.blocks[i];

      switch (block.type) {
        case MarkdownBlock::kHeading: {
          int level = jlimit(1, 6, block.level);
          float scale = kHeadingScale[level - 1];
          auto attr = buildStyledString(block.runs, fontSize * scale, system_text_color);
          TextLayout layout;
          layout.createLayout(attr, width);
          layout.draw(g, Rectangle<float>(x, y, width, layout.getHeight()));
          y += layout.getHeight();
          break;
        }

        case MarkdownBlock::kCodeBlock: {
          Font mono = getMonoFont(fontSize * 0.85f);
          AttributedString attr;
          attr.setText(block.code_text);
          attr.setFont(mono);
          attr.setColour(system_text_color);
          attr.setJustification(Justification::topLeft);
          TextLayout layout;
          float inner_width = width - 2 * kCodeBlockPadding;
          layout.createLayout(attr, inner_width);
          float block_height = layout.getHeight() + 2 * kCodeBlockPadding;

          g.setColour(code_bg_color);
          g.fillRoundedRectangle(x, y, width, block_height, 4.0f);

          layout.draw(g, Rectangle<float>(x + kCodeBlockPadding, y + kCodeBlockPadding,
                                           inner_width, layout.getHeight()));
          y += block_height;
          break;
        }

        case MarkdownBlock::kListItem: {
          int indent = kListIndent * block.level;
          float item_x = x + indent;
          float item_width = width - indent;

          // Draw bullet or number
          String marker = block.ordered ? String(block.list_index) + ". " : String(CharPointer_UTF8("\xe2\x80\xa2 "));
          Font marker_font = getRegularFont(fontSize);
          g.setColour(system_text_color);
          g.setFont(marker_font);
          float marker_width = marker_font.getStringWidthFloat(marker);
          g.drawText(marker, Rectangle<float>(item_x, y, marker_width, fontSize), Justification::topLeft);

          auto attr = buildStyledString(block.runs, fontSize, system_text_color);
          TextLayout layout;
          layout.createLayout(attr, item_width - marker_width);
          layout.draw(g, Rectangle<float>(item_x + marker_width, y,
                                           item_width - marker_width, layout.getHeight()));
          y += layout.getHeight();
          break;
        }

        case MarkdownBlock::kBlockQuote: {
          g.setColour(quote_border_color);
          g.fillRect(x, y, (float)kQuoteBorderWidth, (float)measureBlockHeight(block, (int)width, fontSize));

          float quote_x = x + kQuoteBorderWidth + kQuoteIndent;
          float quote_width = width - kQuoteBorderWidth - kQuoteIndent;
          Colour quote_color = system_text_color.withAlpha(0.7f);
          auto attr = buildStyledString(block.runs, fontSize, quote_color);
          TextLayout layout;
          layout.createLayout(attr, quote_width);
          layout.draw(g, Rectangle<float>(quote_x, y, quote_width, layout.getHeight()));
          y += layout.getHeight();
          break;
        }

        case MarkdownBlock::kHorizontalRule: {
          g.setColour(hr_color);
          g.fillRect(x, y + 3.0f, width, 2.0f);
          y += 8.0f;
          break;
        }

        case MarkdownBlock::kParagraph:
        default: {
          auto attr = buildStyledString(block.runs, fontSize, system_text_color);
          TextLayout layout;
          layout.createLayout(attr, width);
          layout.draw(g, Rectangle<float>(x, y, width, layout.getHeight()));
          y += layout.getHeight();
          break;
        }
      }
    }
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

  // Button row at the bottom: ASK | TALK | COOK
  // Left half = ASK + TALK, right half = COOK
  int button_y = getHeight() - padding - button_height;
  int button_gap = widget_margin;
  int half_width = (button_width - button_gap) / 2;
  int ask_width = (half_width - button_gap) / 2;
  int talk_width = half_width - ask_width - button_gap;
  int cook_width = button_width - half_width - button_gap;

  int ask_x = padding;
  int talk_x = ask_x + ask_width + button_gap;
  int cook_x = talk_x + talk_width + button_gap;

  ask_button_->setBounds(ask_x, button_y, ask_width, button_height);
  ask_button_->getGlComponent()->text().setTextSize(size_ratio_ * 12.5f);
  ask_button_->getGlComponent()->text().setFontType(PlainTextComponent::kTitle);
  ask_button_->getGlComponent()->text().redrawImage(true);
  updateAskButtonColors();

  talk_button_->setBounds(talk_x, button_y, talk_width, button_height);
  talk_button_->getGlComponent()->text().setTextSize(size_ratio_ * 12.5f);
  talk_button_->getGlComponent()->text().setFontType(PlainTextComponent::kTitle);
  talk_button_->getGlComponent()->text().redrawImage(true);
  updateTalkButtonColors();

  action_button_->setBounds(cook_x, button_y, cook_width, button_height);
  action_button_->getGlComponent()->text().setTextSize(size_ratio_ * 12.5f);
  action_button_->getGlComponent()->text().setFontType(PlainTextComponent::kTitle);
  action_button_->getGlComponent()->text().redrawImage(true);

  // Recording indicators (small red dots above ASK/TALK buttons)
  int indicator_size = 8;
  int ask_ind_x = ask_x + ask_width - indicator_size - 6;
  int ask_ind_y = button_y - indicator_size - 4;
  ask_recording_indicator_->setBounds(ask_ind_x, ask_ind_y, indicator_size, indicator_size);

  int talk_ind_x = talk_x + talk_width - indicator_size - 6;
  int talk_ind_y = button_y - indicator_size - 4;
  talk_recording_indicator_->setBounds(talk_ind_x, talk_ind_y, indicator_size, indicator_size);

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

    float editor_font_size = size_ratio_ * 14.0f;
    prompt_editor_->setFont(Fonts::instance()->proportional_regular().withPointHeight(editor_font_size));
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
  else if (clicked_button == ask_button_.get()) {
    if (recording_mode_ == kRecordingAsk) {
      stopRecording();
    } else {
      if (recording_mode_ == kRecordingTalk)
        stopRecording();
      startAskRecording();
    }
  }
  else if (clicked_button == talk_button_.get()) {
    if (recording_mode_ == kRecordingTalk) {
      stopRecording();
    } else {
      if (recording_mode_ == kRecordingAsk)
        stopRecording();
      startTalkRecording();
    }
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

void VitalSidePanel::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& wheel) {
  static constexpr float kScrollSensitivity = 200.0f;

  // Only scroll if mouse is in chat area
  if (!chat_bounds_.contains(e.getPosition()))
    return;

  int visible_height = chat_bounds_.getHeight();
  int max_scroll = std::max(0, total_content_height_ - visible_height);

  scroll_position_ -= (int)(wheel.deltaY * kScrollSensitivity);
  scroll_position_ = std::max(0, std::min(scroll_position_, max_scroll));

  setScrollBarRange();
  repaintBackground();
}

void VitalSidePanel::initializeApiClient() {
  ClaudeApiClient& api_client = ClaudeApiClient::instance();
  if (api_client.initialize())
    addMessage("Ready to create!", ChatMessage::kSystem);
  else
    addMessage("API key not configured. Use the menu to set your API key path.", ChatMessage::kSystem);
}

void VitalSidePanel::initializeDeepgramClient() {
  DeepgramClient& dg = DeepgramClient::instance();
  if (dg.initialize())
    DBG("DeepgramClient initialized successfully");
  // No chat message needed - mic button will show error if key not set
}

void VitalSidePanel::startAskRecording() {
  DeepgramClient& dg = DeepgramClient::instance();
  if (!dg.isInitialized()) {
    addMessage("Deepgram API key not configured. Use the menu to set it.", ChatMessage::kSystem);
    return;
  }

  bool connected = dg.connect(
    // Transcript callback (called on message thread via MessageManager::callAsync)
    [this](const String& transcript, bool is_final) {
      if (is_final && transcript.trim().isNotEmpty()) {
        // Clear partial preview from text editor
#if !defined(NO_TEXT_ENTRY)
        if (prompt_editor_) {
          prompt_editor_->clear();
          prompt_editor_->redoImage();
        }
#endif
        // Remove existing thinking indicator
        clearThinkingMessage();

        // Submit as if the user typed it
        addMessage(transcript.trim(), ChatMessage::kUser);
        addMessage("Thinking...", ChatMessage::kSystem);

        for (Listener* listener : listeners_)
          listener->sidePanelMessageSubmitted(transcript.trim());
      } else if (!is_final) {
        // Show interim result as preview in text editor
#if !defined(NO_TEXT_ENTRY)
        if (prompt_editor_) {
          prompt_editor_->setText(transcript, false);
          prompt_editor_->redoImage();
        }
#endif
      }
    },
    // Error callback
    [this](const String& error) {
      addMessage("Voice error: " + error, ChatMessage::kSystem);
      stopRecording();
    }
  );

  if (!connected) {
    addMessage("Failed to connect to Deepgram.", ChatMessage::kSystem);
    return;
  }

  bool capturing = mic_capture_->startCapture(
    [](const void* data, int num_bytes) {
      DeepgramClient::instance().sendAudioData(data, num_bytes);
    },
    [this]() {
      DBG("VitalSidePanel: Silence timeout - stopping ASK recording");
      stopRecording();
    }
  );

  if (!capturing) {
    dg.disconnect();
    addMessage("Failed to access microphone.", ChatMessage::kSystem);
    return;
  }

  recording_mode_ = kRecordingAsk;
  ask_button_->setText(kStopButtonLabel);
  ask_button_->getGlComponent()->text().redrawImage(true);
  updateAskButtonColors();
  ask_recording_indicator_->setActive(true);
  addMessage("Listening... speak your instructions.", ChatMessage::kSystem);
}

void VitalSidePanel::startTalkRecording() {
  // TODO: Implement always-on talk mode with local VAD gating
  // For now, just toggle the visual state
  recording_mode_ = kRecordingTalk;
  talk_button_->setText(kStopButtonLabel);
  talk_button_->getGlComponent()->text().redrawImage(true);
  updateTalkButtonColors();
  talk_recording_indicator_->setActive(true);
  addMessage("Talk mode active (coming soon).", ChatMessage::kSystem);
}

void VitalSidePanel::stopRecording() {
  if (recording_mode_ == kRecordingNone)
    return;

  if (recording_mode_ == kRecordingAsk) {
    mic_capture_->stopCapture();

    // Grab any pending transcript from the text editor before disconnecting
    // (interim results are previewed there; if endpointing never triggered,
    //  this is the only copy of the transcription)
    String pending_text;
#if !defined(NO_TEXT_ENTRY)
    if (prompt_editor_)
      pending_text = prompt_editor_->getText().trim();
#endif

    DeepgramClient::instance().disconnect();

    ask_button_->setText(kAskButtonLabel);
    ask_button_->getGlComponent()->text().redrawImage(true);
    ask_recording_indicator_->setActive(false);

#if !defined(NO_TEXT_ENTRY)
    if (prompt_editor_) {
      prompt_editor_->clear();
      prompt_editor_->redoImage();
    }
#endif

    // Submit any pending transcript as a chat message
    if (pending_text.isNotEmpty()) {
      clearThinkingMessage();
      addMessage(pending_text, ChatMessage::kUser);
      addMessage("Thinking...", ChatMessage::kSystem);
      for (Listener* listener : listeners_)
        listener->sidePanelMessageSubmitted(pending_text);
    }
  }
  else if (recording_mode_ == kRecordingTalk) {
    // TODO: Stop always-on talk mode resources when implemented
    talk_button_->setText(kTalkButtonLabel);
    talk_button_->getGlComponent()->text().redrawImage(true);
    talk_recording_indicator_->setActive(false);
  }

  recording_mode_ = kRecordingNone;
  updateAskButtonColors();
  updateTalkButtonColors();
}

void VitalSidePanel::submitMessage() {
#if !defined(NO_TEXT_ENTRY)
  if (!prompt_editor_)
    return;

  String text = prompt_editor_->getText().trim();
  if (text.isEmpty())
    return;

  // Remove existing thinking indicator so user message appears above it
  clearThinkingMessage();

  // Add user message
  addMessage(text, ChatMessage::kUser);

  // Clear the input
  prompt_editor_->clear();
  prompt_editor_->redoImage();

  // Add thinking indicator (always at the end, after all user messages)
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

  float scaled_font_size = size_ratio_ * ChatMessage::kBaseFontSize;
  int y_position = 0;

  for (auto& message : messages_) {
    int height;
    if (message.type == ChatMessage::kSystem && !message.blocks.empty())
      height = ChatMessage::calculateMarkdownHeight(message.blocks, message_width, scaled_font_size);
    else
      height = ChatMessage::calculateHeight(message.text, message_width, scaled_font_size);
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

void VitalSidePanel::updateAskButtonColors() {
  if (recording_mode_ == kRecordingAsk) {
    // Use the original non-primary button grey for STOP state
    ask_button_->setColour(Skin::kUiActionButton, findColour(Skin::kUiButton, true));
    ask_button_->setColour(Skin::kUiActionButtonHover, findColour(Skin::kUiButtonHover, true));
    ask_button_->setColour(Skin::kUiActionButtonPressed, findColour(Skin::kUiButtonPressed, true));
  } else {
    // Remove overrides to use default bright purple
    ask_button_->removeColour(Skin::kUiActionButton);
    ask_button_->removeColour(Skin::kUiActionButtonHover);
    ask_button_->removeColour(Skin::kUiActionButtonPressed);
  }
  ask_button_->getGlComponent()->setColors();
}

void VitalSidePanel::updateTalkButtonColors() {
  if (recording_mode_ == kRecordingTalk) {
    // Use the original non-primary button grey for STOP state
    talk_button_->setColour(Skin::kUiActionButton, findColour(Skin::kUiButton, true));
    talk_button_->setColour(Skin::kUiActionButtonHover, findColour(Skin::kUiButtonHover, true));
    talk_button_->setColour(Skin::kUiActionButtonPressed, findColour(Skin::kUiButtonPressed, true));
  } else {
    // Remove overrides to use default bright purple
    talk_button_->removeColour(Skin::kUiActionButton);
    talk_button_->removeColour(Skin::kUiActionButtonHover);
    talk_button_->removeColour(Skin::kUiActionButtonPressed);
  }
  talk_button_->getGlComponent()->setColors();
}
