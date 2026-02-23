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
  prompt_editor_->addMouseListener(this, false);
#endif

  action_button_ = std::make_unique<OpenGlToggleButton>("Cook");
  addButton(action_button_.get());
  action_button_->setUiButton(true);
  action_button_->setText(kSubmitButtonText);
  action_button_->setVisible(false);

  voice_chat_button_ = std::make_unique<OpenGlToggleButton>("VoiceChat");
  addButton(voice_chat_button_.get());
  voice_chat_button_->setUiButton(true);
  voice_chat_button_->setText(kVoiceChatButtonLabel);
  voice_chat_button_->setMouseCursor(MouseCursor::PointingHandCursor);

  clear_button_ = std::make_unique<OpenGlToggleButton>("Clear");
  addButton(clear_button_.get());
  clear_button_->setVisible(false);
  clear_button_->setBounds(0, 0, 0, 0);

  clear_circle_bg_ = std::make_unique<OpenGlQuad>(Shaders::kCircleFragment);
  addOpenGlComponent(clear_circle_bg_.get());
  clear_circle_bg_->setActive(false);

  clear_x_icon_ = std::make_unique<PlainShapeComponent>("clear_x_icon");
  addOpenGlComponent(clear_x_icon_.get());
  clear_x_icon_->setShape(Paths::clearXIcon());
  clear_x_icon_->setUseAlpha(true);
  clear_x_icon_->setColor(Colours::white);
  clear_x_icon_->setActive(false);

  cancel_edit_button_ = std::make_unique<OpenGlToggleButton>("CancelEdit");
  addButton(cancel_edit_button_.get());
  cancel_edit_button_->setUiButton(true);
  cancel_edit_button_->setText("");
  cancel_edit_button_->setVisible(false);
  cancel_edit_button_->setMouseCursor(MouseCursor::PointingHandCursor);

  cancel_edit_x_icon_ = std::make_unique<PlainShapeComponent>("cancel_edit_x_icon");
  addOpenGlComponent(cancel_edit_x_icon_.get());
  cancel_edit_x_icon_->setShape(Paths::cancelEditXIcon());
  cancel_edit_x_icon_->setUseAlpha(true);
  cancel_edit_x_icon_->setColor(Colours::white);
  cancel_edit_x_icon_->setActive(false);

  mic_capture_ = std::make_unique<MicrophoneCapture>();

  action_circle_bg_ = std::make_unique<OpenGlQuad>(Shaders::kCircleFragment);
  addOpenGlComponent(action_circle_bg_.get());
  action_circle_bg_->setActive(true);

  voice_chat_recording_indicator_ = std::make_unique<OpenGlQuad>(Shaders::kCircleFragment);
  addOpenGlComponent(voice_chat_recording_indicator_.get());
  voice_chat_recording_indicator_->setColor(Colours::red.withAlpha(0.9f));
  voice_chat_recording_indicator_->setActive(false);

  mic_icon_shape_ = std::make_unique<PlainShapeComponent>("mic_icon");
  addOpenGlComponent(mic_icon_shape_.get());
  mic_icon_shape_->setShape(Paths::microphoneIcon2());
  mic_icon_shape_->setUseAlpha(true);
  mic_icon_shape_->setColor(Colours::white.withAlpha(0.7f));
  mic_icon_shape_->setActive(true);

  send_icon_shape_ = std::make_unique<PlainShapeComponent>("send_icon");
  addOpenGlComponent(send_icon_shape_.get());
  send_icon_shape_->setShape(Paths::sendArrowIcon());
  send_icon_shape_->setUseAlpha(true);
  send_icon_shape_->setColor(Colour(0xFF222222));
  send_icon_shape_->setActive(false);

  stop_icon_shape_ = std::make_unique<PlainShapeComponent>("stop_icon");
  addOpenGlComponent(stop_icon_shape_.get());
  stop_icon_shape_->setShape(Paths::stopIcon());
  stop_icon_shape_->setUseAlpha(true);
  stop_icon_shape_->setColor(Colour(0xFF222222));
  stop_icon_shape_->setActive(false);

  mic_recording_indicator_ = std::make_unique<OpenGlQuad>(Shaders::kCircleFragment);
  addOpenGlComponent(mic_recording_indicator_.get());
  mic_recording_indicator_->setColor(Colours::red.withAlpha(0.9f));
  mic_recording_indicator_->setActive(false);

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

  // Draw restore button outside the clip region so it isn't clipped
  if (!restore_button_bounds_.isEmpty()) {
    auto rb = restore_button_bounds_.toFloat();
    float icon_size = size_ratio_ * 12.0f;
    float box_padding = size_ratio_ * 6.0f;
    float box_size = icon_size + box_padding * 2.0f;

    Colour bg_colour = findColour(Skin::kWidgetPrimary1, true).darker(hovering_restore_button_ ? 0.2f : 0.35f);
    g.setColour(bg_colour);
    g.fillRoundedRectangle(rb, size_ratio_ * 5.0f);

    Path icon = Paths::restoreIcon();
    float draw_size = icon_size * 1.25f;
    float draw_offset = (box_size - draw_size) * 0.5f;
    Rectangle<float> icon_bounds(rb.getX() + draw_offset, rb.getY() + draw_offset,
                                  draw_size, draw_size);
    g.setColour(findColour(Skin::kBodyText, true).withAlpha(0.85f));
    g.fillPath(icon, icon.getTransformToScaleToFit(icon_bounds, true));
  }
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
  Colour step_text_color = text_color.withAlpha(0.45f);
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
      float icon_size = size_ratio_ * 12.0f;
      float box_padding = size_ratio_ * 6.0f;
      float box_size = icon_size + box_padding * 2.0f;
      float box_x = (float)msg_bounds.getRight() - box_size * (3.0f / 4.0f);
      float box_y = (float)msg_bounds.getY() - box_size * (1.0f / 4.0f);

      restore_button_bounds_ = Rectangle<int>((int)box_x, (int)box_y,
                                               (int)box_size, (int)box_size);
    }

    int pad = (message.type == ChatMessage::kUser) ? ChatMessage::kPadding : ChatMessage::kSystemPadding;
    Rectangle<float> text_bounds((float)(msg_bounds.getX() + pad),
                                  (float)(msg_bounds.getY() + pad),
                                  (float)(msg_bounds.getWidth() - 2 * pad),
                                  (float)(msg_bounds.getHeight() - 2 * pad));

    // User messages and non-markdown system messages: plain text
    if (message.type == ChatMessage::kUser || message.blocks.empty()) {
      Colour col = (message.type == ChatMessage::kUser) ? text_color :
                   (message.type == ChatMessage::kStep) ? step_text_color : system_text_color;
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

    // Markdown rendering for system/step messages
    Colour msg_text_color = (message.type == ChatMessage::kStep) ? step_text_color : system_text_color;
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
          auto attr = buildStyledString(block.runs, fontSize * scale, msg_text_color);
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
          attr.setColour(msg_text_color);
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
          g.setColour(msg_text_color);
          g.setFont(marker_font);
          float marker_width = marker_font.getStringWidthFloat(marker);
          g.drawText(marker, Rectangle<float>(item_x, y, marker_width, fontSize), Justification::topLeft);

          auto attr = buildStyledString(block.runs, fontSize, msg_text_color);
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
          Colour quote_color = msg_text_color.withAlpha(0.7f);
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
          auto attr = buildStyledString(block.runs, fontSize, msg_text_color);
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

  int content_width = getWidth() - 2 * padding;
  int textarea_height = 180;
  int title_height = 30;

  // Clear button circle in the title row (top right)
  int clear_area = title_height;
  int clear_circle_size = (int)(22.0f * size_ratio_);
  int clear_circle_x = getWidth() - padding - clear_area + (clear_area - clear_circle_size) / 2;
  int clear_circle_y = padding + (clear_area - clear_circle_size) / 2;
  clear_button_bounds_ = Rectangle<int>(clear_circle_x, clear_circle_y, clear_circle_size, clear_circle_size);
  clear_circle_bg_->setBounds(clear_circle_x, clear_circle_y, clear_circle_size, clear_circle_size);
  clear_circle_bg_->setColor(Colours::white.withAlpha(0.13f));

  int clear_icon_size = (int)(13.5f * size_ratio_);
  int clear_icon_off = (clear_circle_size - clear_icon_size) / 2;
  clear_x_icon_->setBounds(clear_circle_x + clear_icon_off, clear_circle_y + clear_icon_off,
                            clear_icon_size, clear_icon_size);
  clear_x_icon_->redrawImage(true);

  // Hide old large SEND button (functionality moved to inline action circle)
  action_button_->setBounds(0, 0, 0, 0);
  action_button_->setVisible(false);

  // Textarea extends to the bottom of the window (minus padding)
  int textarea_y = getHeight() - padding - textarea_height;
#if !defined(NO_TEXT_ENTRY)
  if (prompt_editor_) {
    prompt_editor_->setBounds(padding, textarea_y, content_width, textarea_height);

    Colour empty_color = findColour(Skin::kBodyText, true);
    empty_color = empty_color.withAlpha(0.5f * empty_color.getFloatAlpha());
    prompt_editor_->setTextToShowWhenEmpty("Describe your sound, or tell me what to do next", empty_color);
    prompt_editor_->setColour(CaretComponent::caretColourId, findColour(Skin::kTextEditorCaret, true));
    prompt_editor_->setColour(TextEditor::textColourId, findColour(Skin::kBodyText, true));
    prompt_editor_->setColour(TextEditor::highlightedTextColourId, findColour(Skin::kBodyText, true));
    prompt_editor_->setColour(TextEditor::highlightColourId, findColour(Skin::kTextEditorSelection, true));

    float editor_font_size = size_ratio_ * 14.0f;
    prompt_editor_->setFont(Fonts::instance()->proportional_regular().withPointHeight(editor_font_size));
    prompt_editor_->redoImage();
  }
#endif

  // Circular action button (mic/send) at bottom-right of textarea
  {
    int circle_size = (int)(32.0f * size_ratio_);
    int circle_padding = (int)(6.0f * size_ratio_);
    int circle_x = padding + content_width - circle_size - circle_padding;
    int circle_y = textarea_y + textarea_height - circle_size - circle_padding;
    action_button_bounds_ = Rectangle<int>(circle_x, circle_y, circle_size, circle_size);

    action_circle_bg_->setBounds(circle_x, circle_y, circle_size, circle_size);

    int mic_size = (int)(16.245f * size_ratio_);
    int mic_off = (circle_size - mic_size) / 2;
    mic_icon_shape_->setBounds(circle_x + mic_off, circle_y + mic_off, mic_size, mic_size);
    mic_icon_shape_->redrawImage(true);

    int send_size = (int)(13.92f * size_ratio_);
    int send_off = (circle_size - send_size) / 2;
    send_icon_shape_->setBounds(circle_x + send_off, circle_y + send_off, send_size, send_size);
    send_icon_shape_->redrawImage(true);

    int stop_size = (int)(12.48f * size_ratio_);
    int stop_off = (circle_size - stop_size) / 2;
    stop_icon_shape_->setBounds(circle_x + stop_off, circle_y + stop_off, stop_size, stop_size);
    stop_icon_shape_->redrawImage(true);

    int ind_size = 8;
    int ind_x = circle_x + circle_size - ind_size + 2;
    int ind_y = circle_y - 2;
    mic_recording_indicator_->setBounds(ind_x, ind_y, ind_size, ind_size);
  }

  // VOICE CHAT / STOP button inside textarea, to the left of the action circle
  {
    int vc_padding = (int)(6.0f * size_ratio_);
    bool is_stop = (recording_mode_ == kRecordingVoiceChat);

    int vc_height = is_stop ? (int)(24.0f * size_ratio_) : (int)(26.0f * size_ratio_);
    int vc_width = is_stop ? (int)(50.0f * size_ratio_) : (int)(90.0f * size_ratio_);
    int vc_y = textarea_y + textarea_height - vc_height - vc_padding;
    int vc_x = padding + vc_padding;

    voice_chat_button_->setBounds(vc_x, vc_y, vc_width, vc_height);
    voice_chat_button_->getGlComponent()->background().setRounding(is_stop ? vc_height * 0.3f : vc_height * 0.15f);
    voice_chat_button_->getGlComponent()->text().setTextSize(size_ratio_ * (is_stop ? 8.0f : 9.5f));
    voice_chat_button_->getGlComponent()->text().setFontType(PlainTextComponent::kTitle);
    voice_chat_button_->getGlComponent()->text().redrawImage(true);
    updateVoiceChatButtonColors();

    int indicator_size = 8;
    int vc_ind_x = vc_x + vc_width - indicator_size + 2;
    int vc_ind_y = vc_y - 2;
    voice_chat_recording_indicator_->setBounds(vc_ind_x, vc_ind_y, indicator_size, indicator_size);
  }

  // Cancel edit button overlapping top-right of textarea
  if (cancel_edit_button_) {
    int cancel_size = 24;
    int cancel_x = padding + content_width - cancel_size - 4;
    int cancel_y = textarea_y + 4;
    cancel_edit_button_->setBounds(cancel_x, cancel_y, cancel_size, cancel_size);
    cancel_edit_button_->getGlComponent()->text().setTextSize(size_ratio_ * 14.0f);
    cancel_edit_button_->getGlComponent()->text().setFontType(PlainTextComponent::kTitle);
    cancel_edit_button_->getGlComponent()->text().redrawImage(true);
    updateCancelEditButtonColors();

    int cancel_icon_size = (int)(12.0f * size_ratio_);
    int cancel_icon_off = (cancel_size - cancel_icon_size) / 2;
    if (cancel_edit_x_icon_) {
      cancel_edit_x_icon_->setBounds(cancel_x + cancel_icon_off, cancel_y + cancel_icon_off,
                                     cancel_icon_size, cancel_icon_size);
      cancel_edit_x_icon_->redrawImage(true);
    }
  }

  // Chat area between title and textarea
  int chat_top = padding + title_height + widget_margin;
  int chat_bottom = textarea_y - (int)(widget_margin * 1.75f);
  int chat_height = chat_bottom - chat_top;
  int chat_width = content_width - (int)kScrollBarWidth - widget_margin;

  chat_bounds_ = Rectangle<int>(padding, chat_top, chat_width, chat_height);

  // Scrollbar on the right side of chat area
  scroll_bar_->setBounds(padding + chat_width + widget_margin, chat_top,
                         (int)kScrollBarWidth, chat_height);
  scroll_bar_->setColor(findColour(Skin::kLightenScreen, true));

  updateActionButtonState();

  // Layout messages and update scrollbar
  layoutMessages();

  SynthSection::resized();
}

void VitalSidePanel::buttonClicked(Button* clicked_button) {
  if (clicked_button == cancel_edit_button_.get()) {
    cancelEditMode();
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

void VitalSidePanel::textEditorTextChanged(TextEditor& editor) {
  updateActionButtonState();
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
        if (recording_mode_ != kRecordingTalk)
          return;
#if !defined(NO_TEXT_ENTRY)
        if (prompt_editor_) {
          prompt_editor_->clear();
          prompt_editor_->redoImage();
        }
#endif
        addMessage(transcript.trim(), ChatMessage::kUser);

        for (Listener* listener : listeners_)
          listener->sidePanelMessageSubmitted(transcript.trim());

        stopRecording();
      } else if (!is_final) {
        last_deepgram_activity_ms_ = Time::getMillisecondCounterHiRes();
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

  bool capturing = mic_capture_->startCapture(
    [](const void* data, int num_bytes) {
      DeepgramClient::instance().sendAudioData(data, num_bytes);
    }
  );

  if (!capturing) {
    dg.disconnect();
    addMessage("Failed to access microphone.", ChatMessage::kSystem);
    return;
  }

  recording_mode_ = kRecordingTalk;
  mic_recording_indicator_->setActive(true);
  updateActionButtonState();
  recording_start_ms_ = last_deepgram_activity_ms_ = Time::getMillisecondCounterHiRes();
  startTimer(250);  // Poll every 250ms. Grace/timeout values in timerCallback().
  addMessage("Listening...", ChatMessage::kSystem);
}

void VitalSidePanel::startVoiceChatRecording() {
  DeepgramClient& dg = DeepgramClient::instance();
  if (!dg.isInitialized()) {
    addMessage("Deepgram API key not configured. Use the menu to set it.", ChatMessage::kSystem);
    return;
  }

  AlertWindow::showMessageBoxAsync(AlertWindow::InfoIcon,
    "Voice Chat",
    "Voice chat will stay active until you press STOP or 10 seconds of silence is detected.");

  bool connected = dg.connect(
    [this](const String& transcript, bool is_final) {
      if (is_final && transcript.trim().isNotEmpty()) {
        last_deepgram_activity_ms_ = Time::getMillisecondCounterHiRes();
#if !defined(NO_TEXT_ENTRY)
        if (prompt_editor_) {
          prompt_editor_->clear();
          prompt_editor_->redoImage();
        }
#endif
        addMessage(transcript.trim(), ChatMessage::kUser);

        for (Listener* listener : listeners_)
          listener->sidePanelMessageSubmitted(transcript.trim());
      } else if (!is_final) {
        last_deepgram_activity_ms_ = Time::getMillisecondCounterHiRes();
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

  bool capturing = mic_capture_->startCapture(
    [](const void* data, int num_bytes) {
      DeepgramClient::instance().sendAudioData(data, num_bytes);
    }
  );

  if (!capturing) {
    dg.disconnect();
    addMessage("Failed to access microphone.", ChatMessage::kSystem);
    return;
  }

  recording_mode_ = kRecordingVoiceChat;
  voice_chat_button_->setVisible(false);
  mic_recording_indicator_->setActive(true);
  updateActionButtonState();
  recording_start_ms_ = last_deepgram_activity_ms_ = Time::getMillisecondCounterHiRes();
  startTimer(250);  // Poll every 250ms. Grace/timeout values in timerCallback().
  addMessage("Listening until you stop...", ChatMessage::kSystem);
}

void VitalSidePanel::timerCallback() {
  if (recording_mode_ == kRecordingNone) {
    stopTimer();
    return;
  }

  double now = Time::getMillisecondCounterHiRes();
  // Grace period: no inactivity check until elapsed. Tuned for natural usage.
  // See STEERING.md and TROUBLESHOOTING.md for rationale.
  double grace_ms = (recording_mode_ == kRecordingTalk) ? 3000.0 : 5000.0;

  if ((now - recording_start_ms_) < grace_ms)
    return;

  double inactive_ms = now - last_deepgram_activity_ms_;
  // Inactivity timeout: stop recording after silence. TALK 2s, VOICE CHAT 10s.
  // Tested and tuned for natural customer usage patterns.
  double timeout_ms = (recording_mode_ == kRecordingTalk) ? 2000.0 : 10000.0;

  if (inactive_ms >= timeout_ms) {
    DBG("VitalSidePanel: Deepgram inactivity timeout (" + String(inactive_ms / 1000.0, 1)
        + "s) - stopping " + String(recording_mode_ == kRecordingTalk ? "TALK" : "VOICE CHAT"));
    stopRecording();
  }
}

void VitalSidePanel::stopRecording() {
  if (recording_mode_ == kRecordingNone)
    return;

  stopTimer();
  mic_capture_->stopCapture();

  String pending_text;
#if !defined(NO_TEXT_ENTRY)
  if (prompt_editor_)
    pending_text = prompt_editor_->getText().trim();
#endif

  DeepgramClient::instance().disconnect();

  if (recording_mode_ == kRecordingTalk) {
    // Mic icon will update on next repaint
  }
  else if (recording_mode_ == kRecordingVoiceChat) {
    voice_chat_button_->setVisible(true);
  }

#if !defined(NO_TEXT_ENTRY)
  if (prompt_editor_) {
    prompt_editor_->clear();
    prompt_editor_->redoImage();
  }
#endif

  if (pending_text.isNotEmpty()) {
    exitEditMode();

    addMessage(pending_text, ChatMessage::kUser);
    for (Listener* listener : listeners_)
      listener->sidePanelMessageSubmitted(pending_text);
  }

  recording_mode_ = kRecordingNone;
  mic_recording_indicator_->setActive(false);
  updateVoiceChatButtonColors();
  resized();
}

void VitalSidePanel::submitMessage() {
#if !defined(NO_TEXT_ENTRY)
  if (!prompt_editor_)
    return;

  String text = prompt_editor_->getText().trim();
  if (text.isEmpty())
    return;

  // Commit and exit edit mode if active (cleans up orphaned checkpoint files)
  exitEditMode();

  // Add user message
  addMessage(text, ChatMessage::kUser);

  // Clear the input
  prompt_editor_->clear();
  prompt_editor_->redoImage();

  // Notify listeners (they decide whether to add "Thinking..." based on
  // whether the message is processed immediately or queued)
  for (Listener* listener : listeners_)
    listener->sidePanelMessageSubmitted(text);
#endif
}

void VitalSidePanel::addMessage(const String& text, ChatMessage::Type type) {
  messages_.emplace_back(text, type);
  layoutMessages();
  scrollToBottom();
  repaintBackground();
  saveChatLog();
}

void VitalSidePanel::clearThinkingMessage() {
  // Scan backwards for "Thinking..." — it may not be at back() if a queued
  // user message was appended after it during multi-action processing.
  for (int i = (int)messages_.size() - 1; i >= 0; --i) {
    if (messages_[i].type == ChatMessage::kSystem && messages_[i].text == "Thinking...") {
      messages_.erase(messages_.begin() + i);
      layoutMessages();
      repaintBackground();
      return;
    }
  }
}

void VitalSidePanel::removeStatusMessage(const String& text) {
  // Scan backwards and remove the first matching system message
  for (int i = (int)messages_.size() - 1; i >= 0; --i) {
    if (messages_[i].type == ChatMessage::kSystem && messages_[i].text == text) {
      messages_.erase(messages_.begin() + i);
      layoutMessages();
      repaintBackground();
      return;
    }
  }
}

void VitalSidePanel::updateStatusMessage(const String& text, ChatMessage::Type newType) {
  // Scan backwards to find the last system/step message — this ensures
  // step messages are still reachable when a user message was interleaved
  // (e.g. user sent a queued message during multi-action processing).
  for (int i = (int)messages_.size() - 1; i >= 0; --i) {
    auto& msg = messages_[i];
    if (msg.type == ChatMessage::kSystem || msg.type == ChatMessage::kStep) {
      msg.text = text;
      msg.type = newType;
      msg.blocks = parseMarkdown(text);
      layoutMessages();
      scrollToBottom();
      repaintBackground();
      saveChatLog();
      return;
    }
  }
  // Fallback: add as new system message
  addMessage(text, ChatMessage::kSystem);
}

void VitalSidePanel::addResponseMessage(const String& text) {
  if (recording_mode_ == kRecordingVoiceChat)
    last_deepgram_activity_ms_ = Time::getMillisecondCounterHiRes();
  clearThinkingMessage();
  addMessage(text, ChatMessage::kSystem);
}

void VitalSidePanel::saveChatLog() {
  File log_file = File::getSpecialLocation(File::userDesktopDirectory).getChildFile("vial_chat_log.txt");
  String content;
  content += "=== Vial Chat Log (" + Time::getCurrentTime().toString(true, true, true) + ") ===\n\n";

  for (int i = 0; i < (int)messages_.size(); ++i) {
    const auto& msg = messages_[i];
    String role = (msg.type == ChatMessage::kUser) ? "USER" :
                  (msg.type == ChatMessage::kStep) ? "STEP" : "SYSTEM";
    content += "--- [" + String(i) + "] " + role + " ---\n";
    content += msg.text + "\n\n";
  }

  log_file.replaceWithText(content);
}

void VitalSidePanel::layoutMessages() {
  static constexpr int kSystemSpacing = 4;    // Between adjacent system/step messages
  static constexpr int kUserSpacing = 12;     // Around user messages (before or after)

  int message_width = chat_bounds_.getWidth();
  if (message_width <= 0)
    return;

  float scaled_font_size = size_ratio_ * ChatMessage::kBaseFontSize;
  int y_position = 0;

  for (int i = 0; i < (int)messages_.size(); ++i) {
    auto& message = messages_[i];

    // Add spacing before this message (except the first)
    if (i > 0) {
      bool prev_is_user = messages_[i - 1].type == ChatMessage::kUser;
      bool curr_is_user = message.type == ChatMessage::kUser;
      // Use larger spacing if either adjacent message is a user message
      y_position += (prev_is_user || curr_is_user) ? kUserSpacing : kSystemSpacing;
    }

    int height;
    if (message.type != ChatMessage::kUser && !message.blocks.empty())
      height = ChatMessage::calculateMarkdownHeight(message.blocks, message_width, scaled_font_size);
    else
      height = ChatMessage::calculateHeight(message.text, message_width, scaled_font_size);
    message.y_position = y_position;
    message.height = height;
    y_position += height;
  }

  // Calculate total content height
  total_content_height_ = y_position;

  // Hide clear button when chat is empty (only the initial system message)
  bool has_user_messages = std::any_of(messages_.begin(), messages_.end(),
      [](const ChatMessage& m) { return m.type == ChatMessage::kUser; });
  clear_button_active_ = has_user_messages;
  clear_circle_bg_->setActive(has_user_messages);
  clear_x_icon_->setActive(has_user_messages);
  if (has_user_messages) clear_x_icon_->redrawImage(true);

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

void VitalSidePanel::clearChat() {
  // Stop any active recording
  if (isRecording())
    stopRecording();

  // Commit and exit edit mode if active (cleans up orphaned checkpoint files)
  exitEditMode();

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

  // Cancel any in-flight API requests
  for (Listener* l : listeners_)
    l->sidePanelClearRequested();

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
    Colour dimmed = Colours::white.withAlpha(0.13f);
    Colour dimmed_hover = Colours::white.withAlpha(0.22f);
    Colour dimmed_pressed = Colours::white.withAlpha(0.28f);
    voice_chat_button_->setColour(Skin::kUiActionButton, dimmed);
    voice_chat_button_->setColour(Skin::kUiActionButtonHover, dimmed_hover);
    voice_chat_button_->setColour(Skin::kUiActionButtonPressed, dimmed_pressed);
  }
  voice_chat_button_->setColour(Skin::kUiButtonText, Colours::white);
  voice_chat_button_->getGlComponent()->setColors();
}

void VitalSidePanel::updateCancelEditButtonColors() {
  Colour dimmed = Colours::white.withAlpha(0.13f);
  Colour dimmed_hover = Colours::white.withAlpha(0.22f);
  Colour dimmed_pressed = Colours::white.withAlpha(0.28f);
  cancel_edit_button_->setColour(Skin::kUiActionButton, dimmed);
  cancel_edit_button_->setColour(Skin::kUiActionButtonHover, dimmed_hover);
  cancel_edit_button_->setColour(Skin::kUiActionButtonPressed, dimmed_pressed);
  cancel_edit_button_->setColour(Skin::kUiButtonText, Colours::white);
  cancel_edit_button_->getGlComponent()->setColors();
}

void VitalSidePanel::updateActionButtonState() {
#if !defined(NO_TEXT_ENTRY)
  bool has_text = prompt_editor_ && prompt_editor_->getText().trim().isNotEmpty();
#else
  bool has_text = false;
#endif

  bool is_recording = (recording_mode_ == kRecordingTalk || recording_mode_ == kRecordingVoiceChat);

  ActionButtonMode new_mode;
  if (is_recording)
    new_mode = kActionStop;
  else if (has_text)
    new_mode = kActionSend;
  else
    new_mode = kActionMic;

  if (new_mode != action_button_mode_) {
    mic_icon_shape_->setActive(new_mode == kActionMic);
    send_icon_shape_->setActive(new_mode == kActionSend);
    stop_icon_shape_->setActive(new_mode == kActionStop);

    if (new_mode == kActionMic) {
      mic_icon_shape_->setColor(Colours::white.withAlpha(0.7f));
      mic_icon_shape_->redrawImage(true);
    }
    if (new_mode == kActionSend) {
      send_icon_shape_->setColor(Colour(0xFF222222));
      send_icon_shape_->redrawImage(true);
    }
    if (new_mode == kActionStop) {
      stop_icon_shape_->setColor(Colour(0xFF222222));
      stop_icon_shape_->redrawImage(true);
    }

    action_button_mode_ = new_mode;
  }

  switch (action_button_mode_) {
    case kActionMic:
      action_circle_bg_->setColor(Colours::white.withAlpha(action_button_hovered_ ? 0.22f : 0.13f));
      break;
    case kActionSend: {
      Colour purple = findColour(Skin::kUiActionButton, true);
      action_circle_bg_->setColor(action_button_hovered_ ? purple.brighter(0.15f) : purple);
      break;
    }
    case kActionStop:
      action_circle_bg_->setColor(action_button_hovered_ ? Colours::white.darker(0.1f) : Colours::white);
      break;
  }
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

// NOTE: pass delete_files=false during edit-mode restore. The snapshot holds
// references to these files and cancelEditMode needs them intact. Files are
// cleaned up later by exitEditMode() when the edit is committed or discarded.
void VitalSidePanel::removeCheckpointsAfter(int message_index, bool delete_files) {
  auto it = std::remove_if(checkpoints_.begin(), checkpoints_.end(),
      [message_index](const ChatCheckpoint& cp) {
        return cp.ui_message_index > message_index;
      });
  if (delete_files) {
    for (auto del = it; del != checkpoints_.end(); ++del)
      del->autosave_file.deleteFile();
  }
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

void VitalSidePanel::exitEditMode() {
  if (!edit_mode_)
    return;

  // During edit-mode restore, removeCheckpointsAfter() removed entries from the
  // checkpoint vector but deliberately preserved the .vital files on disk (so
  // cancelEditMode could restore them). Now that the edit is being committed or
  // discarded (not cancelled), delete any orphaned files that are no longer
  // referenced by the current checkpoint vector.
  if (edit_snapshot_) {
    for (const auto& old_cp : edit_snapshot_->saved_checkpoints) {
      bool still_referenced = std::any_of(checkpoints_.begin(), checkpoints_.end(),
          [&](const ChatCheckpoint& cp) { return cp.autosave_file == old_cp.autosave_file; });
      if (!still_referenced && old_cp.autosave_file.exists())
        old_cp.autosave_file.deleteFile();
    }
  }

  edit_mode_ = false;
  edit_snapshot_.reset();
  if (cancel_edit_button_)
    cancel_edit_button_->setVisible(false);
  if (cancel_edit_x_icon_)
    cancel_edit_x_icon_->setActive(false);
}

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

  // Trigger the restore (truncates messages, restores synth state, truncates API history).
  // IMPORTANT: sidePanelRestoreRequested removes checkpoint entries from the vector but
  // does NOT delete their .vital files from disk. The snapshot above holds references to
  // those files, and cancelEditMode() needs them intact to fully restore state. Orphaned
  // files are cleaned up by exitEditMode() when the edit is committed or discarded.
  bool restored = false;
  for (Listener* l : listeners_)
    restored = l->sidePanelRestoreRequested(message_index) || restored;

  if (!restored) {
    // Restore failed — discard snapshot and bail out
    edit_snapshot_.reset();
    return;
  }

  // Set edit mode state
  edit_mode_ = true;

  // Put the message text in the textbox
#if !defined(NO_TEXT_ENTRY)
  if (prompt_editor_) {
    prompt_editor_->setText(message_text, false);
    prompt_editor_->moveCaretToEnd();
    prompt_editor_->redoImage();
    prompt_editor_->grabKeyboardFocus();
  }
#endif

  // Show cancel button
  if (cancel_edit_button_) {
    cancel_edit_button_->setVisible(true);
    updateCancelEditButtonColors();
  }
  if (cancel_edit_x_icon_) {
    cancel_edit_x_icon_->setActive(true);
    cancel_edit_x_icon_->redrawImage(true);
  }

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
  if (cancel_edit_x_icon_)
    cancel_edit_x_icon_->setActive(false);

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
  auto pos = e.getEventRelativeTo(this).getPosition();

  // Track clear button circle hover
  bool over_clear = clear_button_active_ && clear_button_bounds_.contains(pos);
  if (over_clear != clear_button_hovered_) {
    clear_button_hovered_ = over_clear;
    clear_circle_bg_->setColor(over_clear ? Colours::white.withAlpha(0.2f) : Colours::white.withAlpha(0.13f));
    setMouseCursor(over_clear ? MouseCursor::PointingHandCursor : MouseCursor::NormalCursor);
  }

  // Track action button (mic/send circle) hover
  bool over_action = !action_button_bounds_.isEmpty() && action_button_bounds_.contains(pos);
  if (over_action != action_button_hovered_) {
    action_button_hovered_ = over_action;
    updateActionButtonState();
    if (prompt_editor_)
      prompt_editor_->setMouseCursor(over_action ? MouseCursor::PointingHandCursor : MouseCursor::IBeamCursor);
  }

  if (!chat_bounds_.contains(pos)) {
    if (hovered_message_index_ != -1) {
      hovered_message_index_ = -1;
      restore_button_bounds_ = {};
      repaintBackground();
    }
    return;
  }

  // If mouse is over the restore button, keep the current hover state
  bool over_button = !restore_button_bounds_.isEmpty() && restore_button_bounds_.contains(pos);
  if (over_button) {
    if (!hovering_restore_button_) {
      hovering_restore_button_ = true;
      setMouseCursor(MouseCursor::PointingHandCursor);
      repaintBackground();
    }
    return;
  }
  if (hovering_restore_button_) {
    hovering_restore_button_ = false;
    setMouseCursor(MouseCursor::NormalCursor);
    repaintBackground();
  }

  int mouse_y = pos.getY() - chat_bounds_.getY() + scroll_position_;
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
  if (clear_button_hovered_) {
    clear_button_hovered_ = false;
    clear_circle_bg_->setColor(Colours::white.withAlpha(0.13f));
  }
  if (action_button_hovered_) {
    action_button_hovered_ = false;
    updateActionButtonState();
  }
  if (hovered_message_index_ != -1 || hovering_restore_button_) {
    hovered_message_index_ = -1;
    hovering_restore_button_ = false;
    restore_button_bounds_ = {};
    repaintBackground();
  }
}

void VitalSidePanel::mouseUp(const MouseEvent& e) {
  auto pos = e.getEventRelativeTo(this).getPosition();

  // Clear chat circle click
  if (clear_button_active_ && clear_button_bounds_.contains(pos)) {
    clearChat();
    return;
  }

  // Action circle click — send, stop recording, or start talk recording
  if (!action_button_bounds_.isEmpty() && action_button_bounds_.contains(pos)) {
    if (action_button_mode_ == kActionSend) {
      submitMessage();
      for (Listener* listener : listeners_)
        listener->sidePanelButtonClicked();
    } else if (action_button_mode_ == kActionStop) {
      stopRecording();
    } else {
      if (recording_mode_ == kRecordingVoiceChat)
        stopRecording();
      startTalkRecording();
    }
    return;
  }

  if (hovered_message_index_ < 0 || restore_button_bounds_.isEmpty())
    return;

  if (!restore_button_bounds_.contains(pos))
    return;

  enterEditMode(hovered_message_index_);
}
