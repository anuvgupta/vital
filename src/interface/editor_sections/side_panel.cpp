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

VitalSidePanel::VitalSidePanel() : SynthSection("side_panel") {
  action_button_ = std::make_unique<OpenGlToggleButton>("Action");
  addButton(action_button_.get());
  action_button_->setUiButton(true);
  action_button_->setText("Action");

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
  g.drawText("SIDE PANEL", title_bounds, Justification::centredLeft);
}

void VitalSidePanel::resized() {
  int padding = findValue(Skin::kLargePadding);
  int widget_margin = findValue(Skin::kWidgetMargin);
  
  int title_height = 30;
  int button_height = 30;
  int button_width = getWidth() - 2 * padding;
  
  int button_y = padding + title_height + widget_margin;
  action_button_->setBounds(padding, button_y, button_width, button_height);

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
