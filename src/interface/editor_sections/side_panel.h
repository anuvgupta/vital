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

class OpenGlToggleButton;
class OpenGlTextEditor;

class VitalSidePanel : public SynthSection {
  public:
    class Listener {
      public:
        virtual ~Listener() = default;
        virtual void sidePanelButtonClicked() = 0;
    };

    VitalSidePanel();
    virtual ~VitalSidePanel();

    void paintBackground(Graphics& g) override;
    void paintBackgroundShadow(Graphics& g) override { paintTabShadow(g); }
    void resized() override;
    void buttonClicked(Button* clicked_button) override;

    void addListener(Listener* listener) { listeners_.push_back(listener); }

  private:
    std::vector<Listener*> listeners_;
    std::unique_ptr<OpenGlTextEditor> prompt_editor_;
    std::unique_ptr<OpenGlToggleButton> action_button_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VitalSidePanel)
};
