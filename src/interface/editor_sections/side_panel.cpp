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
#include "open_gl_image_component.h"
#include "skin.h"
#include "synth_button.h"

VitalSidePanel::VitalSidePanel() : SynthSection("side_panel") {
#if !defined(NO_TEXT_ENTRY)
  prompt_editor_ = std::make_unique<OpenGlTextEditor>("Prompt");
  prompt_editor_->setJustification(Justification::topLeft);
  addAndMakeVisible(prompt_editor_.get());
  addOpenGlComponent(prompt_editor_->getImageComponent());
  prompt_editor_->setMultiLine(true, true);
  prompt_editor_->setReturnKeyStartsNewLine(true);
#endif

  action_button_ = std::make_unique<OpenGlToggleButton>("Send");
  addButton(action_button_.get());
  action_button_->setUiButton(true);
  action_button_->setText("SEND");

  setSkinOverride(Skin::kNone);
}

VitalSidePanel::~VitalSidePanel() { }

void VitalSidePanel::paintBackground(Graphics& g) {
  paintBody(g);
  paintBorder(g);

  // Draw panel title
  g.setColour(findColour(Skin::kBodyText, true));
  g.setFont(Fonts::instance()->proportional_regular().withPointHeight(14.0f));
  
  int title_height = 30;
  int padding = findValue(Skin::kLargePadding);
  Rectangle<int> title_bounds(padding, padding, getWidth() - 2 * padding, title_height);
  g.drawText("CHAT", title_bounds, Justification::centredLeft);
}

void VitalSidePanel::resized() {
  int padding = findValue(Skin::kLargePadding);
  int widget_margin = findValue(Skin::kWidgetMargin);
  
  int button_height = 30;
  int button_width = getWidth() - 2 * padding;
  int textarea_height = 80;
  
  // Button at the bottom
  int button_y = getHeight() - padding - button_height;
  action_button_->setBounds(padding, button_y, button_width, button_height);
  
  // Textarea above the button
#if !defined(NO_TEXT_ENTRY)
  if (prompt_editor_) {
    int textarea_y = button_y - widget_margin - textarea_height;
    prompt_editor_->setBounds(padding, textarea_y, button_width, textarea_height);
    
    Colour empty_color = findColour(Skin::kBodyText, true);
    empty_color = empty_color.withAlpha(0.5f * empty_color.getFloatAlpha());
    prompt_editor_->setTextToShowWhenEmpty("Describe your synth patch. What do you want to hear?", empty_color);
    prompt_editor_->setColour(CaretComponent::caretColourId, findColour(Skin::kTextEditorCaret, true));
    prompt_editor_->setColour(TextEditor::textColourId, findColour(Skin::kBodyText, true));
    prompt_editor_->setColour(TextEditor::highlightedTextColourId, findColour(Skin::kBodyText, true));
    prompt_editor_->setColour(TextEditor::highlightColourId, findColour(Skin::kTextEditorSelection, true));
  }
#endif

  SynthSection::resized();
}

void VitalSidePanel::buttonClicked(Button* clicked_button) {
  if (clicked_button == action_button_.get()) {
    for (Listener* listener : listeners_)
      listener->sidePanelButtonClicked();
  }
  else {
    SynthSection::buttonClicked(clicked_button);
  }
}
