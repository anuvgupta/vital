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
#include "load_save.h"
#include "paths.h"
#include "skin.h"
#include "synth_button.h"
#include "shaders.h"
#include <cmath>
#include <algorithm>

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

static const String kTalkButtonLabel = "SPEAK";
static const String kVoiceChatButtonLabel = "VOICE CHAT";
static const String kStopButtonLabel = "STOP";
static const String kSubmitButtonText = "SEND";

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
  int text_width = width - 2 * kSystemPadding;
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

  int height = total + 2 * kSystemPadding;

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

  talk_button_ = std::make_unique<OpenGlToggleButton>("Talk");
  addButton(talk_button_.get());
  talk_button_->setUiButton(true);
  talk_button_->setText(kTalkButtonLabel);

  voice_chat_button_ = std::make_unique<OpenGlToggleButton>("VoiceChat");
  addButton(voice_chat_button_.get());
  voice_chat_button_->setUiButton(true);
  voice_chat_button_->setText(kVoiceChatButtonLabel);

  clear_button_ = std::make_unique<OpenGlToggleButton>("Clear");
  addButton(clear_button_.get());
  clear_button_->setUiButton(true);
  clear_button_->setText(String(CharPointer_UTF8("\xc3\x97")));

  cancel_edit_button_ = std::make_unique<OpenGlToggleButton>("CancelEdit");
  addButton(cancel_edit_button_.get());
  cancel_edit_button_->setUiButton(true);
  cancel_edit_button_->setText(String(CharPointer_UTF8("\xc3\x97")));
  cancel_edit_button_->setVisible(false);

  mic_capture_ = std::make_unique<MicrophoneCapture>();

  talk_recording_indicator_ = std::make_unique<OpenGlQuad>(Shaders::kCircleFragment);
  addOpenGlComponent(talk_recording_indicator_.get());
  talk_recording_indicator_->setColor(Colours::red.withAlpha(0.9f));
  talk_recording_indicator_->setActive(false);

  voice_chat_recording_indicator_ = std::make_unique<OpenGlQuad>(Shaders::kCircleFragment);
  addOpenGlComponent(voice_chat_recording_indicator_.get());
  voice_chat_recording_indicator_->setColor(Colours::red.withAlpha(0.9f));
  voice_chat_recording_indicator_->setActive(false);

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

  restore_button_bounds_ = {};

  for (int msg_idx = 0; msg_idx < (int)messages_.size(); ++msg_idx) {
    const auto& message = messages_[msg_idx];
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

    // Draw restore button only on hovered user messages that have a restorable checkpoint
    bool has_checkpoint = false;
    if (message.type == ChatMessage::kUser) {
      has_checkpoint = getCheckpoint(msg_idx + 1) != nullptr || getCheckpoint(msg_idx) != nullptr;
    }

    if (msg_idx == hovered_message_index_ && has_checkpoint) {
      float icon_size = size_ratio_ * 10.0f;
      float box_padding = size_ratio_ * 7.0f;
      float box_size = icon_size + box_padding * 2.0f;
      float box_x = (float)msg_bounds.getRight() - box_size;
      float box_y = (float)msg_bounds.getY() - box_size * 0.5f;

      restore_button_bounds_ = Rectangle<int>((int)box_x, (int)box_y,
                                               (int)box_size, (int)box_size);

      // Rounded rectangle background — darken on hover over button
      Colour bg_colour = findColour(Skin::kWidgetPrimary1, true).darker(hovering_restore_button_ ? 0.35f : 0.2f);
      g.setColour(bg_colour);
      g.fillRoundedRectangle(box_x, box_y, box_size, box_size, size_ratio_ * 5.0f);

      // Draw restore icon centered in the box
      Path icon = Paths::restoreIcon();
      float icon_x = box_x + (box_size - icon_size) * 0.5f;
      float icon_y = box_y + (box_size - icon_size) * 0.5f;
      Rectangle<float> icon_bounds(icon_x, icon_y, icon_size, icon_size);
      g.setColour(text_color.withAlpha(0.85f));
      g.fillPath(icon, icon.getTransformToScaleToFit(icon_bounds, true));
    }

    int pad = (message.type == ChatMessage::kUser) ? ChatMessage::kPadding : ChatMessage::kSystemPadding;
    Rectangle<float> text_bounds((float)(msg_bounds.getX() + pad),
                                  (float)(msg_bounds.getY() + pad),
                                  (float)(msg_bounds.getWidth() - 2 * pad),
                                  (float)(msg_bounds.getHeight() - 2 * pad));

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

  // Clear button in the title row (top right)
  int clear_size = title_height;
  int clear_x = getWidth() - padding - clear_size;
  int clear_y = padding;
  clear_button_->setBounds(clear_x, clear_y, clear_size, clear_size);
  clear_button_->getGlComponent()->text().setTextSize(size_ratio_ * 16.0f);
  clear_button_->getGlComponent()->text().setFontType(PlainTextComponent::kTitle);
  clear_button_->getGlComponent()->text().redrawImage(true);

  // Button row at the bottom: VOICE CHAT | TALK | SEND
  // VOICE CHAT (big, half width) | TALK (small) | SEND (small)
  int button_y = getHeight() - padding - button_height;
  int button_gap = widget_margin;
  int voice_chat_width = (button_width - 2 * button_gap) / 2;
  int side_width = button_width - voice_chat_width - 2 * button_gap;
  int talk_width = side_width / 2;
  int send_width = side_width - talk_width;

  int voice_chat_x = padding;
  int talk_x = voice_chat_x + voice_chat_width + button_gap;
  int send_x = talk_x + talk_width + button_gap;

  talk_button_->setBounds(talk_x, button_y, talk_width, button_height);
  talk_button_->getGlComponent()->text().setTextSize(size_ratio_ * 12.5f);
  talk_button_->getGlComponent()->text().setFontType(PlainTextComponent::kTitle);
  talk_button_->getGlComponent()->text().redrawImage(true);
  updateTalkButtonColors();

  voice_chat_button_->setBounds(voice_chat_x, button_y, voice_chat_width, button_height);
  voice_chat_button_->getGlComponent()->text().setTextSize(size_ratio_ * 12.5f);
  voice_chat_button_->getGlComponent()->text().setFontType(PlainTextComponent::kTitle);
  voice_chat_button_->getGlComponent()->text().redrawImage(true);
  updateVoiceChatButtonColors();

  action_button_->setBounds(send_x, button_y, send_width, button_height);
  action_button_->getGlComponent()->text().setTextSize(size_ratio_ * 11.0f);
  action_button_->getGlComponent()->text().setFontType(PlainTextComponent::kTitle);
  action_button_->getGlComponent()->text().redrawImage(true);

  // Recording indicators (small red dots above TALK/VOICE CHAT buttons)
  int indicator_size = 8;
  int talk_ind_x = talk_x + talk_width - indicator_size - 6;
  int talk_ind_y = button_y - indicator_size - 4;
  talk_recording_indicator_->setBounds(talk_ind_x, talk_ind_y, indicator_size, indicator_size);

  int vc_ind_x = voice_chat_x + voice_chat_width - indicator_size - 6;
  int vc_ind_y = button_y - indicator_size - 4;
  voice_chat_recording_indicator_->setBounds(vc_ind_x, vc_ind_y, indicator_size, indicator_size);

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

  // Cancel edit button overlapping top-right of textarea
  if (cancel_edit_button_) {
    int cancel_size = 24;
    int cancel_x = padding + button_width - cancel_size - 4;
    int cancel_y = textarea_y + 4;
    cancel_edit_button_->setBounds(cancel_x, cancel_y, cancel_size, cancel_size);
    cancel_edit_button_->getGlComponent()->text().setTextSize(size_ratio_ * 14.0f);
    cancel_edit_button_->getGlComponent()->text().setFontType(PlainTextComponent::kTitle);
    cancel_edit_button_->getGlComponent()->text().redrawImage(true);
  }

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
  else if (clicked_button == clear_button_.get()) {
    clearChat();
  }
  else if (clicked_button == cancel_edit_button_.get()) {
    cancelEditMode();
  }
  else if (clicked_button == talk_button_.get()) {
    if (recording_mode_ == kRecordingTalk) {
      stopRecording();
    } else {
      if (recording_mode_ == kRecordingVoiceChat)
        stopRecording();
      startTalkRecording();
    }
  }
  else if (clicked_button == voice_chat_button_.get()) {
    if (recording_mode_ == kRecordingVoiceChat) {
      stopRecording();
    } else {
      if (recording_mode_ == kRecordingTalk)
        stopRecording();
      startVoiceChatRecording();
    }
  }
  else {
    SynthSection::buttonClicked(clicked_button);
  }
}

void VitalSidePanel::textEditorReturnKeyPressed(TextEditor& editor) {
  submitMessage();
}

void VitalSidePanel::textEditorEscapeKeyPressed(TextEditor& editor) {
  if (edit_mode_)
    cancelEditMode();
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
  archiveLooseCheckpointsOnStartup();

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

void VitalSidePanel::startTalkRecording() {
  DeepgramClient& dg = DeepgramClient::instance();
  if (!dg.isInitialized()) {
    addMessage("Deepgram API key not configured. Use the menu to set it.", ChatMessage::kSystem);
    return;
  }

  bool connected = dg.connect(
    [this](const String& transcript, bool is_final) {
      if (is_final && transcript.trim().isNotEmpty()) {
#if !defined(NO_TEXT_ENTRY)
        if (prompt_editor_) {
          prompt_editor_->clear();
          prompt_editor_->redoImage();
        }
#endif
        clearThinkingMessage();
        addMessage(transcript.trim(), ChatMessage::kUser);
        addMessage("Thinking...", ChatMessage::kSystem);

        for (Listener* listener : listeners_)
          listener->sidePanelMessageSubmitted(transcript.trim());
      } else if (!is_final) {
#if !defined(NO_TEXT_ENTRY)
        if (prompt_editor_) {
          prompt_editor_->setText(transcript, false);
          prompt_editor_->redoImage();
        }
#endif
      }
    },
    [this](const String& error) {
      addMessage("Voice error: " + error, ChatMessage::kSystem);
      stopRecording();
    }
  );

  if (!connected) {
    addMessage("Failed to connect to Deepgram.", ChatMessage::kSystem);
    return;
  }

  // Silence callback stops recording in TALK mode
  bool capturing = mic_capture_->startCapture(
    [](const void* data, int num_bytes) {
      DeepgramClient::instance().sendAudioData(data, num_bytes);
    },
    [this]() {
      DBG("VitalSidePanel: Silence timeout - stopping TALK recording");
      stopRecording();
    }
  );

  if (!capturing) {
    dg.disconnect();
    addMessage("Failed to access microphone.", ChatMessage::kSystem);
    return;
  }

  recording_mode_ = kRecordingTalk;
  talk_button_->setText(kStopButtonLabel);
  talk_button_->getGlComponent()->text().redrawImage(true);
  updateTalkButtonColors();
  talk_recording_indicator_->setActive(true);
  addMessage("Listening...", ChatMessage::kSystem);
}

void VitalSidePanel::startVoiceChatRecording() {
  static constexpr float kVoiceChatSilenceTimeout = 20.0f;

  DeepgramClient& dg = DeepgramClient::instance();
  if (!dg.isInitialized()) {
    addMessage("Deepgram API key not configured. Use the menu to set it.", ChatMessage::kSystem);
    return;
  }

  // Show confirmation popup (cross-platform native dialog)
  AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
    "Voice Chat",
    "Voice chat will stay active until you press STOP or 20 seconds of silence is detected.");

  bool connected = dg.connect(
    [this](const String& transcript, bool is_final) {
      if (is_final && transcript.trim().isNotEmpty()) {
#if !defined(NO_TEXT_ENTRY)
        if (prompt_editor_) {
          prompt_editor_->clear();
          prompt_editor_->redoImage();
        }
#endif
        clearThinkingMessage();
        addMessage(transcript.trim(), ChatMessage::kUser);
        addMessage("Thinking...", ChatMessage::kSystem);

        for (Listener* listener : listeners_)
          listener->sidePanelMessageSubmitted(transcript.trim());
      } else if (!is_final) {
#if !defined(NO_TEXT_ENTRY)
        if (prompt_editor_) {
          prompt_editor_->setText(transcript, false);
          prompt_editor_->redoImage();
        }
#endif
      }
    },
    [this](const String& error) {
      addMessage("Voice error: " + error, ChatMessage::kSystem);
      stopRecording();
    }
  );

  if (!connected) {
    addMessage("Failed to connect to Deepgram.", ChatMessage::kSystem);
    return;
  }

  // 12-second hardcoded silence timeout for VOICE CHAT mode
  bool capturing = mic_capture_->startCapture(
    [](const void* data, int num_bytes) {
      DeepgramClient::instance().sendAudioData(data, num_bytes);
    },
    [this]() {
      DBG("VitalSidePanel: Silence timeout - stopping VOICE CHAT recording");
      stopRecording();
    },
    kVoiceChatSilenceTimeout
  );

  if (!capturing) {
    dg.disconnect();
    addMessage("Failed to access microphone.", ChatMessage::kSystem);
    return;
  }

  recording_mode_ = kRecordingVoiceChat;
  voice_chat_button_->setText(kStopButtonLabel);
  voice_chat_button_->getGlComponent()->text().redrawImage(true);
  updateVoiceChatButtonColors();
  voice_chat_recording_indicator_->setActive(true);
  addMessage("Listening until you stop...", ChatMessage::kSystem);
}

void VitalSidePanel::stopRecording() {
  if (recording_mode_ == kRecordingNone)
    return;

  mic_capture_->stopCapture();

  String pending_text;
#if !defined(NO_TEXT_ENTRY)
  if (prompt_editor_)
    pending_text = prompt_editor_->getText().trim();
#endif

  DeepgramClient::instance().disconnect();

  if (recording_mode_ == kRecordingTalk) {
    talk_button_->setText(kTalkButtonLabel);
    talk_button_->getGlComponent()->text().redrawImage(true);
    talk_recording_indicator_->setActive(false);
  }
  else if (recording_mode_ == kRecordingVoiceChat) {
    voice_chat_button_->setText(kVoiceChatButtonLabel);
    voice_chat_button_->getGlComponent()->text().redrawImage(true);
    voice_chat_recording_indicator_->setActive(false);
  }

#if !defined(NO_TEXT_ENTRY)
  if (prompt_editor_) {
    prompt_editor_->clear();
    prompt_editor_->redoImage();
  }
#endif

  if (pending_text.isNotEmpty()) {
    clearThinkingMessage();
    addMessage(pending_text, ChatMessage::kUser);
    addMessage("Thinking...", ChatMessage::kSystem);
    for (Listener* listener : listeners_)
      listener->sidePanelMessageSubmitted(pending_text);
  }

  recording_mode_ = kRecordingNone;
  updateTalkButtonColors();
  updateVoiceChatButtonColors();
}

void VitalSidePanel::submitMessage() {
#if !defined(NO_TEXT_ENTRY)
  if (!prompt_editor_)
    return;

  String text = prompt_editor_->getText().trim();
  if (text.isEmpty())
    return;

  // Exit edit mode if active (discard snapshot, hide cancel button)
  if (edit_mode_) {
    edit_mode_ = false;
    edit_snapshot_.reset();
    if (cancel_edit_button_)
      cancel_edit_button_->setVisible(false);
  }

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

void VitalSidePanel::updateStatusMessage(const String& text) {
  if (!messages_.empty()) {
    auto& last = messages_.back();
    if (last.type == ChatMessage::kSystem) {
      last.text = text;
      last.blocks = parseMarkdown(text);
      layoutMessages();
      scrollToBottom();
      repaintBackground();
      return;
    }
  }
  // Fallback: add as new system message
  addMessage(text, ChatMessage::kSystem);
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

void VitalSidePanel::updateTalkButtonColors() {
  if (recording_mode_ == kRecordingTalk) {
    talk_button_->setColour(Skin::kUiActionButton, findColour(Skin::kUiButton, true));
    talk_button_->setColour(Skin::kUiActionButtonHover, findColour(Skin::kUiButtonHover, true));
    talk_button_->setColour(Skin::kUiActionButtonPressed, findColour(Skin::kUiButtonPressed, true));
  } else {
    talk_button_->removeColour(Skin::kUiActionButton);
    talk_button_->removeColour(Skin::kUiActionButtonHover);
    talk_button_->removeColour(Skin::kUiActionButtonPressed);
  }
  talk_button_->getGlComponent()->setColors();
}

void VitalSidePanel::clearChat() {
  // Stop any active recording
  if (isRecording())
    stopRecording();

  // Archive checkpoints before clearing
  archiveCheckpoints();

  // Clear UI messages
  messages_.clear();
  total_content_height_ = 0;
  scroll_position_ = 0;
  hovered_message_index_ = -1;
  restore_button_bounds_ = {};
  setScrollBarRange();

  // Clear text editor
#if !defined(NO_TEXT_ENTRY)
  if (prompt_editor_) {
    prompt_editor_->clear();
    prompt_editor_->redoImage();
  }
#endif

  // Clear API conversation history
  ClaudeApiClient::instance().clearConversation();

  // Show ready message
  addMessage("Ready to create!", ChatMessage::kSystem);
}

void VitalSidePanel::focusPromptEditor() {
  if (prompt_editor_)
    prompt_editor_->grabKeyboardFocus();
}

void VitalSidePanel::updateVoiceChatButtonColors() {
  if (recording_mode_ == kRecordingVoiceChat) {
    voice_chat_button_->setColour(Skin::kUiActionButton, findColour(Skin::kUiButton, true));
    voice_chat_button_->setColour(Skin::kUiActionButtonHover, findColour(Skin::kUiButtonHover, true));
    voice_chat_button_->setColour(Skin::kUiActionButtonPressed, findColour(Skin::kUiButtonPressed, true));
  } else {
    voice_chat_button_->removeColour(Skin::kUiActionButton);
    voice_chat_button_->removeColour(Skin::kUiActionButtonHover);
    voice_chat_button_->removeColour(Skin::kUiActionButtonPressed);
  }
  voice_chat_button_->getGlComponent()->setColors();
}

// ============================================================================
// Checkpoint Methods
// ============================================================================

void VitalSidePanel::addCheckpoint(int ui_message_index, int api_history_size, File autosave_file) {
  static constexpr int kMaxCheckpoints = 50;

  if ((int)checkpoints_.size() >= kMaxCheckpoints) {
    checkpoints_.front().autosave_file.deleteFile();
    checkpoints_.erase(checkpoints_.begin());
  }

  checkpoints_.push_back({ ui_message_index, api_history_size, std::move(autosave_file) });
}

void VitalSidePanel::truncateMessagesTo(int count) {
  if (count >= 0 && count < (int)messages_.size()) {
    messages_.erase(messages_.begin() + count, messages_.end());
    layoutMessages();
    scrollToBottom();
    repaintBackground();
  }
}

void VitalSidePanel::removeCheckpointsAfter(int message_index) {
  auto it = std::remove_if(checkpoints_.begin(), checkpoints_.end(),
      [message_index](const ChatCheckpoint& cp) {
        return cp.ui_message_index > message_index;
      });
  for (auto del = it; del != checkpoints_.end(); ++del)
    del->autosave_file.deleteFile();
  checkpoints_.erase(it, checkpoints_.end());
}

const ChatCheckpoint* VitalSidePanel::getCheckpoint(int message_index) const {
  for (const auto& cp : checkpoints_) {
    if (cp.ui_message_index == message_index)
      return &cp;
  }
  return nullptr;
}

static String sanitizeForFilename(const String& text, int max_words = 7) {
  StringArray words = StringArray::fromTokens(text, " ", "");
  String result;
  int count = std::min(max_words, words.size());
  for (int i = 0; i < count; ++i) {
    if (i > 0) result += "_";
    for (int j = 0; j < words[i].length(); ++j) {
      juce_wchar c = words[i][j];
      if (CharacterFunctions::isLetterOrDigit(c))
        result += String::charToString(CharacterFunctions::toLowerCase(c));
      else
        result += "_";
    }
  }
  return result.substring(0, 60);
}

void VitalSidePanel::archiveCheckpoints() {
  if (checkpoints_.empty())
    return;

  File autosave_dir = LoadSave::getDataDirectory().getChildFile("autosaves");
  if (!autosave_dir.exists())
    return;

  // Find first user message for naming
  String session_name = "unnamed_session";
  for (const auto& msg : messages_) {
    if (msg.type == ChatMessage::kUser && msg.text != "Thinking...") {
      session_name = sanitizeForFilename(msg.text);
      if (session_name.isEmpty())
        session_name = "unnamed_session";
      break;
    }
  }

  // Find unique subdirectory name
  File archive_dir = autosave_dir.getChildFile(session_name);
  int suffix = 2;
  while (archive_dir.exists()) {
    archive_dir = autosave_dir.getChildFile(session_name + "_" + String(suffix));
    suffix++;
  }
  archive_dir.createDirectory();

  // Move checkpoint files into archive
  for (auto& cp : checkpoints_) {
    if (cp.autosave_file.exists())
      cp.autosave_file.moveFileTo(archive_dir.getChildFile(cp.autosave_file.getFileName()));
  }
  checkpoints_.clear();

  // Cap archived sessions to 20
  static constexpr int kMaxArchivedSessions = 20;
  Array<File> subdirs;
  autosave_dir.findChildFiles(subdirs, File::findDirectories, false);
  if (subdirs.size() > kMaxArchivedSessions) {
    subdirs.sort();
    for (int i = 0; i < subdirs.size() - kMaxArchivedSessions; ++i)
      subdirs[i].deleteRecursively();
  }
}

void VitalSidePanel::archiveLooseCheckpointsOnStartup() {
  File autosave_dir = LoadSave::getDataDirectory().getChildFile("autosaves");
  if (!autosave_dir.exists())
    return;

  // Find any loose .vital files (not in subdirectories)
  Array<File> loose_files;
  autosave_dir.findChildFiles(loose_files, File::findFiles, false, "*.vital");
  if (loose_files.isEmpty())
    return;

  File archive_dir = autosave_dir.getChildFile("unsaved_session");
  int suffix = 2;
  while (archive_dir.exists()) {
    archive_dir = autosave_dir.getChildFile("unsaved_session_" + String(suffix));
    suffix++;
  }
  archive_dir.createDirectory();

  for (auto& file : loose_files)
    file.moveFileTo(archive_dir.getChildFile(file.getFileName()));
}

// ============================================================================
// Edit Mode
// ============================================================================

void VitalSidePanel::enterEditMode(int message_index) {
  if (edit_mode_ || message_index < 0 || message_index >= (int)messages_.size())
    return;

  if (messages_[message_index].type != ChatMessage::kUser)
    return;

  // Save the message text before any modifications
  String message_text = messages_[message_index].text;

  // Save snapshot for cancel/undo
  edit_snapshot_ = std::make_unique<EditModeSnapshot>();
  edit_snapshot_->saved_messages = messages_;
  edit_snapshot_->saved_checkpoints = checkpoints_;

  // Save current state via listeners before restoring
  for (Listener* l : listeners_) {
    edit_snapshot_->saved_api_history_size = l->sidePanelGetApiHistorySize();
    edit_snapshot_->saved_synth_checkpoint = l->sidePanelSaveCheckpoint();
  }

  // Trigger the restore (truncates messages, restores synth state, truncates API history)
  for (Listener* l : listeners_)
    l->sidePanelRestoreRequested(message_index);

  // Set edit mode state
  edit_mode_ = true;

  // Put the message text in the textbox
#if !defined(NO_TEXT_ENTRY)
  if (prompt_editor_) {
    prompt_editor_->setText(message_text, false);
    prompt_editor_->redoImage();
    prompt_editor_->grabKeyboardFocus();
  }
#endif

  // Show cancel button
  if (cancel_edit_button_)
    cancel_edit_button_->setVisible(true);

  // Clear hover state since messages changed
  hovered_message_index_ = -1;
  hovering_restore_button_ = false;
  restore_button_bounds_ = {};
}

void VitalSidePanel::cancelEditMode() {
  if (!edit_mode_ || !edit_snapshot_)
    return;

  // Restore messages and checkpoints from snapshot
  messages_ = std::move(edit_snapshot_->saved_messages);
  checkpoints_ = std::move(edit_snapshot_->saved_checkpoints);

  // Restore synth state and API history via listener
  for (Listener* l : listeners_)
    l->sidePanelCancelEditRequested(edit_snapshot_->saved_synth_checkpoint,
                                     edit_snapshot_->saved_api_history_size);

  // Clear textbox
#if !defined(NO_TEXT_ENTRY)
  if (prompt_editor_) {
    prompt_editor_->clear();
    prompt_editor_->redoImage();
  }
#endif

  // Hide cancel button and exit edit mode
  if (cancel_edit_button_)
    cancel_edit_button_->setVisible(false);

  edit_mode_ = false;
  edit_snapshot_.reset();

  layoutMessages();
  scrollToBottom();
  repaintBackground();
}

// ============================================================================
// Mouse Events for Hover/Restore
// ============================================================================

void VitalSidePanel::mouseMove(const MouseEvent& e) {
  if (!chat_bounds_.contains(e.getPosition())) {
    if (hovered_message_index_ != -1) {
      hovered_message_index_ = -1;
      restore_button_bounds_ = {};
      repaintBackground();
    }
    return;
  }

  // If mouse is over the restore button, keep the current hover state
  bool over_button = !restore_button_bounds_.isEmpty() && restore_button_bounds_.contains(e.getPosition());
  if (over_button) {
    if (!hovering_restore_button_) {
      hovering_restore_button_ = true;
      repaintBackground();
    }
    return;
  }
  if (hovering_restore_button_) {
    hovering_restore_button_ = false;
    repaintBackground();
  }

  int mouse_y = e.getPosition().getY() - chat_bounds_.getY() + scroll_position_;
  int new_hovered = -1;

  for (int i = 0; i < (int)messages_.size(); ++i) {
    if (mouse_y >= messages_[i].y_position &&
        mouse_y < messages_[i].y_position + messages_[i].height) {
      new_hovered = i;
      break;
    }
  }

  if (new_hovered != hovered_message_index_) {
    hovered_message_index_ = new_hovered;
    restore_button_bounds_ = {};
    repaintBackground();
  }
}

void VitalSidePanel::mouseExit(const MouseEvent& e) {
  if (hovered_message_index_ != -1 || hovering_restore_button_) {
    hovered_message_index_ = -1;
    hovering_restore_button_ = false;
    restore_button_bounds_ = {};
    repaintBackground();
  }
}

void VitalSidePanel::mouseUp(const MouseEvent& e) {
  if (hovered_message_index_ < 0 || restore_button_bounds_.isEmpty())
    return;

  if (!restore_button_bounds_.contains(e.getPosition()))
    return;

  enterEditMode(hovered_message_index_);
}
