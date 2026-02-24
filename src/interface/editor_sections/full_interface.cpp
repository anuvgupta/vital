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

#include "full_interface.h"

#include "about_section.h"
#include "bank_exporter.h"
#include "bend_section.h"
#include "claude_api_client.h"
#include "delete_section.h"
#include "download_section.h"
#include "expired_section.h"
#include "extra_mod_section.h"
#include "skin.h"
#include "effects_interface.h"
#include "fonts.h"
#include "sound_engine.h"
#include "keyboard_interface.h"
#include "load_save.h"
#include "master_controls_interface.h"
#include "modulation_interface.h"
#include "modulation_manager.h"
#include "modulation_matrix.h"
#include "modulation_meter.h"
#include "wavetable_edit_section.h"
#include "overlay.h"
#include "portamento_section.h"
#include "preset_browser.h"
#include "synthesis_interface.h"
#include "synth_gui_interface.h"
#include "text_look_and_feel.h"
#include "update_check_section.h"
#include "voice_section.h"

FullInterface::FullInterface(SynthGuiData* synth_data) : SynthSection("full_interface"), width_(0), resized_width_(0),
                                                         last_render_scale_(0.0f), display_scale_(1.0f),
                                                         pixel_multiple_(1), setting_all_values_(false),
                                                         unsupported_(false), animate_(true),
                                                         enable_redo_background_(true), needs_download_(false),
                                                         open_gl_(open_gl_context_) {
  full_screen_section_ = nullptr;
  Skin default_skin;
  setSkinValues(default_skin, true);
  default_skin.copyValuesToLookAndFeel(DefaultLookAndFeel::instance());

  bool synth = synth_data->wavetable_creators[0];
  if (synth) {
    synthesis_interface_ = std::make_unique<SynthesisInterface>(&auth_,
                                                                synth_data->mono_modulations,
                                                                synth_data->poly_modulations);

    for (int i = 0; i < vital::kNumOscillators; ++i) {
      wavetable_edits_[i] = std::make_unique<WavetableEditSection>(i, synth_data->wavetable_creators[i]);
      addSubSection(wavetable_edits_[i].get());
      wavetable_edits_[i]->setVisible(false);
      wavetable_edits_[i]->setWaveFrameSlider(synthesis_interface_->getWaveFrameSlider(i));
    }

    addSubSection(synthesis_interface_.get());
  }

  effects_interface_ = std::make_unique<EffectsInterface>(synth_data->mono_modulations);
  addSubSection(effects_interface_.get());
  effects_interface_->setVisible(false);
  effects_interface_->addListener(this);

  master_controls_interface_ = std::make_unique<MasterControlsInterface>(synth_data->mono_modulations,
                                                                         synth_data->poly_modulations,
                                                                         synth);
  addSubSection(master_controls_interface_.get());
  master_controls_interface_->setVisible(false);

  if (synthesis_interface_) {
    for (int i = 0; i < vital::kNumOscillators; ++i)
      master_controls_interface_->passOscillatorSection(i, synthesis_interface_->getOscillatorSection(i));
  }

  header_ = std::make_unique<HeaderSection>();
  addSubSection(header_.get());
  header_->addListener(this);

  modulation_interface_ = std::make_unique<ModulationInterface>(synth_data);
  addSubSection(modulation_interface_.get());

  extra_mod_section_ = std::make_unique<ExtraModSection>("extra_mod_section", synth_data);
  addSubSection(extra_mod_section_.get());

  keyboard_interface_ = std::make_unique<KeyboardInterface>(synth_data->synth->getKeyboardState());
  addSubSection(keyboard_interface_.get());

  bend_section_ = std::make_unique<BendSection>("BEND");
  addSubSection(bend_section_.get());

  portamento_section_ = std::make_unique<PortamentoSection>("PORTAMENTO");
  addSubSection(portamento_section_.get());

  voice_section_ = std::make_unique<VoiceSection>("VOICE");
  addSubSection(voice_section_.get());

  side_panel_ = std::make_unique<VitalSidePanel>();
  addSubSection(side_panel_.get());
  side_panel_->addListener(this);

  modulation_matrix_ = std::make_unique<ModulationMatrix>(synth_data->modulation_sources, synth_data->mono_modulations);
  addSubSection(modulation_matrix_.get());
  modulation_matrix_->setVisible(false);
  modulation_matrix_->addListener(this);
  createModulationSliders(synth_data->mono_modulations, synth_data->poly_modulations);

  preset_browser_ = std::make_unique<PresetBrowser>();
  addSubSection(preset_browser_.get());
  preset_browser_->setVisible(false);

  popup_browser_ = std::make_unique<PopupBrowser>();
  addSubSection(popup_browser_.get());
  popup_browser_->setVisible(false);

  popup_selector_ = std::make_unique<SinglePopupSelector>();
  addSubSection(popup_selector_.get());
  popup_selector_->setVisible(false);
  popup_selector_->setAlwaysOnTop(true);
  popup_selector_->setWantsKeyboardFocus(true);

  dual_popup_selector_ = std::make_unique<DualPopupSelector>();
  addSubSection(dual_popup_selector_.get());
  dual_popup_selector_->setVisible(false);
  dual_popup_selector_->setAlwaysOnTop(true);
  dual_popup_selector_->setWantsKeyboardFocus(true);

  popup_display_1_ = std::make_unique<PopupDisplay>();
  addSubSection(popup_display_1_.get());
  popup_display_1_->setVisible(false);
  popup_display_1_->setAlwaysOnTop(true);
  popup_display_1_->setWantsKeyboardFocus(false);

  popup_display_2_ = std::make_unique<PopupDisplay>();
  addSubSection(popup_display_2_.get());
  popup_display_2_->setVisible(false);
  popup_display_2_->setAlwaysOnTop(true);
  popup_display_2_->setWantsKeyboardFocus(false);

  bank_exporter_ = std::make_unique<BankExporter>();
  addSubSection(bank_exporter_.get());
  bank_exporter_->setVisible(false);
  header_->setBankExporter(bank_exporter_.get());

  save_section_ = std::make_unique<SaveSection>("save_section");
  addSubSection(save_section_.get(), false);
  addChildComponent(save_section_.get());
  preset_browser_->setSaveSection(save_section_.get());
  header_->setSaveSection(save_section_.get());
  header_->setBrowser(preset_browser_.get());

  delete_section_ = std::make_unique<DeleteSection>("delete_section");
  addSubSection(delete_section_.get(), false);
  addChildComponent(delete_section_.get());
  preset_browser_->setDeleteSection(delete_section_.get());

  download_section_ = std::make_unique<DownloadSection>("download_section", &auth_);
  addSubSection(download_section_.get(), false);
  addChildComponent(download_section_.get());
  download_section_->setAlwaysOnTop(true);
  download_section_->addListener(this);

  about_section_ = std::make_unique<AboutSection>("about");
  addSubSection(about_section_.get(), false);
  addChildComponent(about_section_.get());

  if (synthesis_interface_)
    synthesis_interface_->toFront(true);

  master_controls_interface_->toFront(true);
  effects_interface_->toFront(true);
  modulation_interface_->toFront(true);
  extra_mod_section_->toFront(true);
  keyboard_interface_->toFront(true);
  bend_section_->toFront(true);
  portamento_section_->toFront(true);
  voice_section_->toFront(true);
  side_panel_->toFront(true);
  modulation_manager_->toFront(false);
  preset_browser_->toFront(false);
  bank_exporter_->toFront(false);
  about_section_->toFront(true);
  save_section_->toFront(true);
  delete_section_->toFront(true);
  popup_browser_->toFront(true);
  popup_selector_->toFront(true);
  dual_popup_selector_->toFront(true);
  popup_display_1_->toFront(true);
  popup_display_2_->toFront(true);
  download_section_->toFront(true);

  update_check_section_ = std::make_unique<UpdateCheckSection>("update_check");
  addSubSection(update_check_section_.get(), false);
  addChildComponent(update_check_section_.get());
  update_check_section_->setAlwaysOnTop(true);
  update_check_section_->addListener(this);

  if (LoadSave::isExpired()) { 
    expired_section_ = std::make_unique<ExpiredSection>("expired");
    addSubSection(expired_section_.get());
    expired_section_->setAlwaysOnTop(true);
  }

#if NDEBUG && !NO_AUTH
  bool authenticated = LoadSave::authenticated();
  bool work_offline = LoadSave::shouldWorkOffline();
  authentication_ = std::make_unique<AuthenticationSection>(&auth_);
  authentication_->addListener(this);
  addSubSection(authentication_.get(), false);
  addChildComponent(authentication_.get());
  authentication_->setVisible(!authenticated && !work_offline);
  authentication_->init();
  if (!work_offline)
    authentication_->create();
#endif

  setAllValues(synth_data->controls);
  setOpaque(true);
  setSkinValues(default_skin, true);

  needs_download_ = UpdateMemory::getInstance()->incrementChecker();

  open_gl_context_.setContinuousRepainting(true);
  open_gl_context_.setOpenGLVersionRequired(OpenGLContext::openGL3_2);
  open_gl_context_.setSwapInterval(0);
  open_gl_context_.setRenderer(this);
  open_gl_context_.setComponentPaintingEnabled(false);
  open_gl_context_.attachTo(*this);
}

FullInterface::FullInterface() : SynthSection("EMPTY"), open_gl_(open_gl_context_) {
  Skin default_skin;
  setSkinValues(default_skin, true);

  open_gl_context_.setContinuousRepainting(true);
  open_gl_context_.setOpenGLVersionRequired(OpenGLContext::openGL3_2);
  open_gl_context_.setSwapInterval(0);
  open_gl_context_.setRenderer(this);
  open_gl_context_.setComponentPaintingEnabled(false);
  open_gl_context_.attachTo(*this);

  reset();
  setOpaque(true);
}

FullInterface::~FullInterface() {
  UpdateMemory::getInstance()->decrementChecker();

  open_gl_context_.detach();
  open_gl_context_.setRenderer(nullptr);
}

void FullInterface::paintBackground(Graphics& g) {
  g.fillAll(findColour(Skin::kBackground, true));
  paintChildrenShadows(g);

  if (effects_interface_ == nullptr)
    return;

  int padding = getPadding();
  int bar_width = 6 * padding;
  g.setColour(header_->findColour(Skin::kBody, true));
  int y = header_->getBottom();
  int height = keyboard_interface_->getY() - y;
  int x1 = extra_mod_section_->getRight() + padding;
  g.fillRect(x1, y, bar_width, height);

  if (synthesis_interface_) {
    int x2 = synthesis_interface_->getRight() + padding;
    g.fillRect(x2, y, bar_width, height);
  }

  paintKnobShadows(g);
  paintChildrenBackgrounds(g);
}

void FullInterface::copySkinValues(const Skin& skin) {
  ScopedLock open_gl_lock(open_gl_critical_section_);
  skin.copyValuesToLookAndFeel(DefaultLookAndFeel::instance());
  setSkinValues(skin, true);
}

void FullInterface::reloadSkin(const Skin& skin) {
  copySkinValues(skin);
  Rectangle<int> bounds = getBounds();
  setBounds(0, 0, bounds.getWidth() / 4, bounds.getHeight() / 4);
  setBounds(bounds);
}

void FullInterface::dataDirectoryChanged() {
  preset_browser_->loadPresets();
}

void FullInterface::noDownloadNeeded() {
  update_check_section_->startCheck();
}

void FullInterface::needsUpdate() {
  if (!download_section_->isVisible() && !update_check_section_->isVisible())
    update_check_section_->setVisible(true);  
}

void FullInterface::loggedIn() {
#if !defined(NO_TEXT_ENTRY)
  if (needs_download_)
    download_section_->triggerDownload();
#endif
}

void FullInterface::repaintChildBackground(SynthSection* child) {
  if (!background_image_.isValid() || setting_all_values_)
    return; 

  if (child->getParentComponent() == synthesis_interface_.get()) {
    repaintSynthesisSection();
    return;
  }

  if (effects_interface_ != nullptr && effects_interface_->isParentOf(child))
    child = effects_interface_.get();

  background_.lock();
  Graphics g(background_image_);
  paintChildBackground(g, child);
  background_.updateBackgroundImage(background_image_);
  background_.unlock();
}

void FullInterface::repaintSynthesisSection() {
  if (synthesis_interface_ == nullptr || !synthesis_interface_->isVisible() || !background_image_.isValid())
    return;

  background_.lock();
  Graphics g(background_image_);
  int padding = findValue(Skin::kPadding);
  g.setColour(findColour(Skin::kBackground, true));
  g.fillRect(synthesis_interface_->getBounds().expanded(padding));
  paintChildShadow(g, synthesis_interface_.get());
  paintChildBackground(g, synthesis_interface_.get());

  background_.updateBackgroundImage(background_image_);
  background_.unlock();
}

void FullInterface::repaintOpenGlBackground(OpenGlComponent* component) {
  if (!background_image_.isValid())
    return;

  background_.lock();
  Graphics g(background_image_);
  paintOpenGlBackground(g, component);
  background_.updateBackgroundImage(background_image_);
  background_.unlock();
}

void FullInterface::redoBackground() {
  int width = std::ceil(display_scale_ * getWidth());
  int height = std::ceil(display_scale_ * getHeight());
  if (width < vital::kMinWindowWidth || height < vital::kMinWindowHeight)
    return;

  ScopedLock open_gl_lock(open_gl_critical_section_);

  background_.lock();
  background_image_ = Image(Image::RGB, width, height, true);
  Graphics g(background_image_);
  paintBackground(g);
  background_.updateBackgroundImage(background_image_);
  background_.unlock();
}

void FullInterface::checkShouldReposition(bool resize) {
  float old_scale = display_scale_;
  int old_pixel_multiple = pixel_multiple_;
  display_scale_ = getDisplayScale();
  pixel_multiple_ = std::max<int>(1, display_scale_);

  if (resize && (old_scale != display_scale_ || old_pixel_multiple != pixel_multiple_))
    resized();
}

void FullInterface::resized() {
  checkShouldReposition(false);

  width_ = getWidth();
  if (!enable_redo_background_)
    return;

  resized_width_ = width_;

  ScopedLock lock(open_gl_critical_section_);
  static constexpr int kTopHeight = 48;

  if (effects_interface_ == nullptr)
    return;

  int left = 0;
  int top = 0;
  int width = std::ceil(getWidth() * display_scale_);
  int height = std::ceil(getHeight() * display_scale_);
  Rectangle<int> bounds(0, 0, width, height);

  float width_ratio = getWidth() / (1.0f * vital::kDefaultWindowWidth);
  float ratio = width_ratio * display_scale_;
  float height_ratio = getHeight() / (1.0f * vital::kDefaultWindowHeight);
  if (width_ratio > height_ratio + 1.0f / vital::kDefaultWindowHeight) {
    ratio = height_ratio;
    width = height_ratio * vital::kDefaultWindowWidth * display_scale_;
    left = (getWidth() - width) / 2;
  }
  if (height_ratio > width_ratio + 1.0f / vital::kDefaultWindowHeight) {
    ratio = width_ratio;
    height = ratio * vital::kDefaultWindowHeight * display_scale_;
    top = (getHeight() - height) / 2;
  }

  setSizeRatio(ratio);

  if (expired_section_)
    expired_section_->setBounds(bounds);

  if (authentication_)
    authentication_->setBounds(bounds);

  popup_browser_->setBounds(bounds);

  int padding = getPadding();
  int voice_padding = findValue(Skin::kLargePadding);
  int extra_mod_width = findValue(Skin::kModulationButtonWidth);
  int main_x = left + extra_mod_width + 2 * voice_padding;
  int top_height = kTopHeight * ratio;

  int knob_section_height = getKnobSectionHeight();
  int keyboard_section_height = knob_section_height * 0.7f;
  int voice_height = height - top_height - keyboard_section_height;

  int section_one_width = 350 * ratio;
  int section_two_width = section_one_width;
  int audio_width = section_one_width + section_two_width + padding;
  int side_panel_width = vital::kSidePanelWidth * ratio;
  int modulation_width = width - audio_width - extra_mod_width - side_panel_width - 5 * voice_padding;

  header_->setTabOffset(extra_mod_width + 2 * voice_padding);
  header_->setBounds(left, top, width - side_panel_width - voice_padding, top_height);
  Rectangle<int> main_bounds(main_x, top + top_height, audio_width, voice_height);

  if (synthesis_interface_)
    synthesis_interface_->setBounds(main_bounds);
  effects_interface_->setBounds(main_bounds.withRight(main_bounds.getRight() + voice_padding));
  modulation_matrix_->setBounds(main_bounds);
  int modulation_height = voice_height - knob_section_height - padding;
  modulation_interface_->setBounds(main_bounds.getRight() + voice_padding,
                                   main_bounds.getY(), modulation_width, modulation_height);

  int voice_y = top + height - knob_section_height - keyboard_section_height;

  int portamento_width = 4 * (int)findValue(Skin::kModulationButtonWidth);
  int portamento_x = modulation_interface_->getRight() - portamento_width;
  portamento_section_->setBounds(portamento_x, voice_y, portamento_width, knob_section_height);

  int voice_width = modulation_interface_->getWidth() - portamento_width - padding;
  voice_section_->setBounds(modulation_interface_->getX(), voice_y, voice_width, knob_section_height);

  bend_section_->setBounds(left + voice_padding, top + height - knob_section_height - padding,
                           extra_mod_width, knob_section_height);

  int extra_mod_height = height - top_height - knob_section_height - padding - 1;
  extra_mod_section_->setBounds(left + voice_padding, top + top_height, extra_mod_width, extra_mod_height);

  int keyboard_height = keyboard_section_height - voice_padding - padding;
  int keyboard_x = extra_mod_section_->getRight() + voice_padding;
  int keyboard_width = modulation_interface_->getRight() - keyboard_x;
  keyboard_interface_->setBounds(keyboard_x, top + height - keyboard_height - padding, keyboard_width, keyboard_height);

  // Side panel on the right edge (with padding on right to match left side)
  int side_panel_x = left + width - side_panel_width - voice_padding;
  int side_panel_height = height - top_height - padding;
  side_panel_->setBounds(side_panel_x, top + top_height, side_panel_width, side_panel_height);

  about_section_->setBounds(bounds);
  update_check_section_->setBounds(bounds);
  save_section_->setBounds(bounds);
  delete_section_->setBounds(bounds);
  download_section_->setBounds(bounds);

  Rectangle<int> browse_bounds(main_bounds.getX(), main_bounds.getY(),
                               width - main_bounds.getX(), main_bounds.getHeight());
  preset_browser_->setBounds(browse_bounds);
  bank_exporter_->setBounds(browse_bounds);
  SynthSection::resized();

  modulation_manager_->setBounds(bounds);
  
  for (int i = 0; i < vital::kNumOscillators; ++i) {
    if (wavetable_edits_[i])
      wavetable_edits_[i]->setBounds(left, 0, width, height);
  }

  if (synthesis_interface_) {
    for (int i = 0; i < vital::kNumOscillators; ++i)
      master_controls_interface_->setOscillatorBounds(i, synthesis_interface_->getOscillatorBounds(i));
  }
  master_controls_interface_->setBounds(main_bounds);

  if (full_screen_section_) {
    Rectangle<float> relative = synthesis_interface_->getOscillatorSection(0)->getWavetableRelativeBounds();
    int total_width = getWidth() / relative.getWidth();
    full_screen_section_->setBounds(-total_width * relative.getX(), 0, total_width, getHeight());
  }

  if (getWidth() && getHeight())
    redoBackground();
}

void FullInterface::setOscilloscopeMemory(const vital::poly_float* memory) {
  if (header_)
    header_->setOscilloscopeMemory(memory);
  if (master_controls_interface_)
    master_controls_interface_->setOscilloscopeMemory(memory);
}

void FullInterface::setAudioMemory(const vital::StereoMemory* memory) {
  if (header_)
    header_->setAudioMemory(memory);
  if (master_controls_interface_)
    master_controls_interface_->setAudioMemory(memory);
}

void FullInterface::createModulationSliders(const vital::output_map& mono_modulations,
                                            const vital::output_map& poly_modulations) {
  std::map<std::string, SynthSlider*> all_sliders = getAllSliders();
  std::map<std::string, SynthSlider*> modulatable_sliders;

  for (auto& destination : mono_modulations) {
    if (all_sliders.count(destination.first))
      modulatable_sliders[destination.first] = all_sliders[destination.first];
  }

  modulation_manager_ = std::make_unique<ModulationManager>(getAllModulationButtons(),
                                                            modulatable_sliders, mono_modulations, poly_modulations);
  modulation_manager_->setOpaque(false);
  addSubSection(modulation_manager_.get());
}

void FullInterface::animate(bool animate) {
  if (animate_ != animate)
    open_gl_context_.setContinuousRepainting(animate);

  animate_ = animate;
  SynthSection::animate(animate);
}

void FullInterface::reset() {
  ScopedLock lock(open_gl_critical_section_);

  if (modulation_interface_)
    modulation_interface_->reset();

  setting_all_values_ = true;
  SynthSection::reset();
  modulationChanged();
  if (effects_interface_ && effects_interface_->isVisible())
    effects_interface_->redoBackgroundImage();

  setWavetableNames();
  setting_all_values_ = false;
  repaintSynthesisSection();
}

void FullInterface::setAllValues(vital::control_map& controls) {
  ScopedLock lock(open_gl_critical_section_);
  setting_all_values_ = true;
  SynthSection::setAllValues(controls);
  setting_all_values_ = false;
}

void FullInterface::setWavetableNames() {
  for (int i = 0; i < vital::kNumOscillators; ++i) {
    if (wavetable_edits_[i])
      synthesis_interface_->setWavetableName(i, wavetable_edits_[i]->getName());
  }
}

void FullInterface::startDownload() {
  if (auth_.loggedIn() || authentication_ == nullptr)
    download_section_->triggerDownload();
  else
    authentication_->setVisible(true);
}

void FullInterface::newOpenGLContextCreated() {
  double version_supported = OpenGLShaderProgram::getLanguageVersion();
  unsupported_ = version_supported < kMinOpenGlVersion;
  if (unsupported_) {
    NativeMessageBox::showMessageBoxAsync(AlertWindow::WarningIcon, "Unsupported OpenGl Version",
                                          String("Vial requires OpenGL version: ") + String(kMinOpenGlVersion) +
                                          String("\nSupported version: ") + String(version_supported));
    return;
  }

  shaders_ = std::make_unique<Shaders>(open_gl_context_);
  open_gl_.shaders = shaders_.get();
  open_gl_.display_scale = display_scale_;
  last_render_scale_ = display_scale_;

  background_.init(open_gl_);
  initOpenGlComponents(open_gl_);
}

void FullInterface::renderOpenGL() {
  if (unsupported_)
    return;

  float render_scale = open_gl_.context.getRenderingScale();
  if (render_scale != last_render_scale_) {
    last_render_scale_ = render_scale;
    MessageManager::callAsync([=] { checkShouldReposition(true); });
  }

  ScopedLock lock(open_gl_critical_section_);
  open_gl_.display_scale = display_scale_;
  background_.render(open_gl_);
  modulation_manager_->renderMeters(open_gl_, animate_);
  renderOpenGlComponents(open_gl_, animate_);
}

void FullInterface::openGLContextClosing() {
  if (unsupported_)
    return;

  background_.destroy(open_gl_);
  destroyOpenGlComponents(open_gl_);
  open_gl_.shaders = nullptr;
  shaders_ = nullptr;
}

void FullInterface::showAboutSection() {
  ScopedLock lock(open_gl_critical_section_);
  about_section_->setVisible(true);
}

void FullInterface::deleteRequested(File preset) {
  delete_section_->setFileToDelete(preset);
  delete_section_->setVisible(true);
}

void FullInterface::tabSelected(int index) {
  ScopedLock lock(open_gl_critical_section_);
  bool make_visible = !preset_browser_->isVisible() && !bank_exporter_->isVisible();

  if (synthesis_interface_)
    synthesis_interface_->setVisible(index == 0 && make_visible);

  effects_interface_->setVisible(index == 1 && make_visible);
  modulation_matrix_->setVisible(index == 2 && make_visible);
  master_controls_interface_->setVisible(index == 3 && make_visible);
  modulation_manager_->setModulationAmounts();
  modulation_manager_->resized();
  modulation_manager_->setVisibleMeterBounds();
  modulation_manager_->hideUnusedHoverModulations();
  redoBackground();
}

void FullInterface::clearTemporaryTab(int current_tab) {
  ScopedLock lock(open_gl_critical_section_);
  preset_browser_->setVisible(false);
  bank_exporter_->setVisible(false);
  modulation_interface_->setVisible(true);
  portamento_section_->setVisible(true);
  voice_section_->setVisible(true);
  tabSelected(current_tab);
}

void FullInterface::setPresetBrowserVisibility(bool visible, int current_tab) {
  ScopedLock lock(open_gl_critical_section_);
  preset_browser_->setVisible(visible);
  modulation_interface_->setVisible(!visible);
  portamento_section_->setVisible(!visible);
  voice_section_->setVisible(!visible);
  synthesis_interface_->setVisible(!visible);

  if (visible) {
    tabSelected(-1);
    bank_exporter_->setVisible(false);
    preset_browser_->repaintBackground();
    preset_browser_->grabKeyboardFocus();
    header_->setTemporaryTab("PRESET BROWSER");
  }
  else {
    tabSelected(current_tab);
    header_->setTemporaryTab("");
  }
}

void FullInterface::setBankExporterVisibility(bool visible, int current_tab) {
  ScopedLock lock(open_gl_critical_section_);
  bank_exporter_->setVisible(visible);
  modulation_interface_->setVisible(!visible);
  portamento_section_->setVisible(!visible);
  voice_section_->setVisible(!visible);
  synthesis_interface_->setVisible(!visible);

  if (visible) {
    tabSelected(-1);
    preset_browser_->setVisible(false);
    bank_exporter_->repaintBackground();
    header_->setTemporaryTab("EXPORT BANK");
  }
  else {
    tabSelected(current_tab);
    header_->setTemporaryTab("");
  }
}

void FullInterface::bankImported() {
  preset_browser_->loadPresets();
}

void FullInterface::effectsMoved() {
  modulation_manager_->setVisibleMeterBounds();
}

void FullInterface::modulationsScrolled() {
  modulation_manager_->setVisibleMeterBounds();
}

bool FullInterface::keyPressed(const KeyPress& key) {
  if (key == KeyPress('k', ModifierKeys::commandModifier, 0)) {
    if (side_panel_ && side_panel_->isVisible())
      side_panel_->focusPromptEditor();
    return true;
  }
  return SynthSection::keyPressed(key);
}

void FullInterface::setFocus() {
  if (authentication_ && authentication_->isShowing())
    authentication_->setFocus();
  else if (synthesis_interface_ && synthesis_interface_->isShowing())
    synthesis_interface_->setFocus();
}

void FullInterface::notifyChange() {
  if (header_)
    header_->notifyChange();
}

void FullInterface::notifyFresh() {
  if (header_)
    header_->notifyFresh();
}

void FullInterface::externalPresetLoaded(const File& preset) {
  if (preset_browser_)
    preset_browser_->externalPresetLoaded(preset);
}

void FullInterface::showFullScreenSection(SynthSection* full_screen) {
  ScopedLock lock(open_gl_critical_section_);
  full_screen_section_ = full_screen;

  if (full_screen_section_) {
    addSubSection(full_screen_section_);
    full_screen_section_->setBounds(getLocalBounds());
  }

  for (int i = 0; i < vital::kNumOscillators; ++i)
    wavetable_edits_[i]->setVisible(false);

  bool show_rest = full_screen == nullptr;
  header_->setVisible(show_rest);
  synthesis_interface_->setVisible(show_rest);
  modulation_interface_->setVisible(show_rest);
  keyboard_interface_->setVisible(show_rest);
  extra_mod_section_->setVisible(show_rest);
  modulation_manager_->setVisible(show_rest);
  voice_section_->setVisible(show_rest);
  bend_section_->setVisible(show_rest);
  portamento_section_->setVisible(show_rest);
  side_panel_->setVisible(show_rest);
  redoBackground();
}

void FullInterface::showWavetableEditSection(int index) {
  if (!wavetableEditorsInitialized())
    return;

  ScopedLock lock(open_gl_critical_section_);
  for (int i = 0; i < vital::kNumOscillators; ++i)
    wavetable_edits_[i]->setVisible(i == index);

  bool show_rest = index < 0;
  header_->setVisible(show_rest);
  synthesis_interface_->setVisible(show_rest);
  modulation_interface_->setVisible(show_rest);
  keyboard_interface_->setVisible(show_rest);
  extra_mod_section_->setVisible(show_rest);
  modulation_manager_->setVisible(show_rest);
  voice_section_->setVisible(show_rest);
  bend_section_->setVisible(show_rest);
  portamento_section_->setVisible(show_rest);
  side_panel_->setVisible(show_rest);
  redoBackground();
}

std::string FullInterface::getLastBrowsedWavetable(int index) {
  return wavetable_edits_[index]->getLastBrowsedWavetable();
}

std::string FullInterface::getWavetableName(int index) {
  return wavetable_edits_[index]->getName();
}

std::string FullInterface::getSignedInName() {
  if (authentication_ == nullptr || !auth_.loggedIn())
    return "";
  
  return authentication_->getSignedInName();
}

void FullInterface::signOut() {
  if (authentication_)
    authentication_->signOut();
}

void FullInterface::signIn() {
  if (authentication_) {
    authentication_->create();
    authentication_->setVisible(true);
  }
}

void FullInterface::hideWavetableEditSection() {
  showWavetableEditSection(-1);
}

void FullInterface::loadWavetableFile(int index, const File& wavetable) {
  if (wavetable_edits_[index])
    wavetable_edits_[index]->loadFile(wavetable);
}

void FullInterface::loadWavetable(int index, json& wavetable_data) {
  if (wavetable_edits_[index])
    wavetable_edits_[index]->loadWavetable(wavetable_data);
}

void FullInterface::loadDefaultWavetable(int index) {
  if (wavetable_edits_[index])
    wavetable_edits_[index]->loadDefaultWavetable();
}

void FullInterface::resynthesizeToWavetable(int index) {
  if (wavetable_edits_[index])
    wavetable_edits_[index]->resynthesizeToWavetable();
}

void FullInterface::saveWavetable(int index) {
  save_section_->setIsPreset(false);
  save_section_->setSaveBounds();
  save_section_->setFileExtension(vital::kWavetableExtension);
  save_section_->setFileType("Wavetable");
  File destination = LoadSave::getUserWavetableDirectory();
  if (!destination.exists())
    destination.createDirectory();
  save_section_->setDirectory(destination);
  save_section_->setFileData(getWavetableJson(index));
  save_section_->setVisible(true);
}

void FullInterface::saveLfo(const json& data) {
  save_section_->setIsPreset(false);
  save_section_->setFileExtension(vital::kLfoExtension);
  save_section_->setFileType("LFO");
  save_section_->setDirectory(LoadSave::getUserLfoDirectory());
  save_section_->setFileData(data);
  save_section_->setVisible(true);
}

json FullInterface::getWavetableJson(int index) {
  if (wavetable_edits_[index])
    return wavetable_edits_[index]->getWavetableJson();
  return json();
}

bool FullInterface::loadAudioAsWavetable(int index, const String& name, InputStream* audio_stream,
                                         WavetableCreator::AudioFileLoadStyle style) {
  if (wavetable_edits_[index])
    return wavetable_edits_[index]->loadAudioAsWavetable(name, audio_stream, style);

  delete audio_stream;
  return true;
}

void FullInterface::popupBrowser(SynthSection* owner, Rectangle<int> bounds, std::vector<File> directories,
                                 String extensions, std::string passthrough_name,
                                 std::string additional_folders_name) {
  popup_browser_->setIgnoreBounds(getLocalArea(owner, owner->getLocalBounds()));
  popup_browser_->setBrowserBounds(getLocalArea(owner, bounds));
  popup_browser_->setVisible(true);
  popup_browser_->grabKeyboardFocus();
  popup_browser_->setOwner(owner);
  popup_browser_->loadPresets(directories, extensions, passthrough_name, additional_folders_name);
}

void FullInterface::popupBrowserUpdate(SynthSection* owner) {
  if (popup_browser_)
    popup_browser_->setOwner(owner);
}

void FullInterface::popupSelector(Component* source, Point<int> position, const PopupItems& options,
                                  std::function<void(int)> callback, std::function<void()> cancel) {
  popup_selector_->setCallback(callback);
  popup_selector_->setCancelCallback(cancel);
  popup_selector_->showSelections(options);
  Rectangle<int> bounds(0, 0, std::ceil(display_scale_ * getWidth()), std::ceil(display_scale_ * getHeight()));
  popup_selector_->setPosition(getLocalPoint(source, position), bounds);
  popup_selector_->setVisible(true);
}

void FullInterface::dualPopupSelector(Component* source, Point<int> position, int width,
                                      const PopupItems& options, std::function<void(int)> callback) {
  dual_popup_selector_->setCallback(callback);
  dual_popup_selector_->showSelections(options);
  Rectangle<int> bounds(0, 0, std::ceil(display_scale_ * getWidth()), std::ceil(display_scale_ * getHeight()));
  dual_popup_selector_->setPosition(getLocalPoint(source, position), width, bounds);
  dual_popup_selector_->setVisible(true);
}

void FullInterface::popupDisplay(Component* source, const std::string& text,
                                 BubbleComponent::BubblePlacement placement, bool primary) {
  PopupDisplay* display = primary ? popup_display_1_.get() : popup_display_2_.get();
  display->setContent(text, getLocalArea(source, source->getLocalBounds()), placement);
  display->setVisible(true);
}

void FullInterface::hideDisplay(bool primary) {
  PopupDisplay* display = primary ? popup_display_1_.get() : popup_display_2_.get();
  if (display)
    display->setVisible(false);
}

void FullInterface::modulationChanged() {
  if (modulation_matrix_)
    modulation_matrix_->updateModulations();
  if (modulation_interface_)
    modulation_interface_->checkNumShown();
  if (modulation_manager_)
    modulation_manager_->reset();
}

void FullInterface::modulationValueChanged(int index) {
  if (modulation_matrix_)
    modulation_matrix_->updateModulationValue(index);
  if (modulation_manager_)
    modulation_manager_->setModulationAmounts();
}

void FullInterface::toggleOscillatorZoom(int index) {
  if (full_screen_section_)
    showFullScreenSection(nullptr);
  else
    showFullScreenSection(synthesis_interface_->getOscillatorSection(index));
}

void FullInterface::toggleFilter1Zoom() {
  if (full_screen_section_)
    showFullScreenSection(nullptr);
  else
    showFullScreenSection(synthesis_interface_->getFilterSection1());
}

void FullInterface::toggleFilter2Zoom() {
  if (full_screen_section_)
    showFullScreenSection(nullptr);
  else
    showFullScreenSection(synthesis_interface_->getFilterSection2());
}

String FullInterface::getCompletionPhrase() {
    static const char *phrases[] = {
        "Dialed it in.", "Cooked it up.", "Tuned it up.", "Locked it in.", 
        "Sculpted it.", "Tweaked it.", "Shaped it.", "Mixed it down.",
        "Spliced it.", "Warped it.", "Patched it.", "Wired it up.",
        "Sauced it up.", "Baked it in.", "Juiced it up.", "Done and dusted.",
        "Crunched it.", "Nailed it.", "Cranked it.", "Punched it in.",
        "Tightened it up.", "Spiced it up.", "Whipped it up."
    };
    int count = sizeof(phrases) / sizeof(phrases[0]);
    return phrases[Random::getSystemRandom().nextInt(count)];
}

void FullInterface::mergeJson(json& target, const json& patch) {
  static const std::string kPlaceholder = "(base64 data removed)";
  for (auto it = patch.begin(); it != patch.end(); ++it) {
    // Skip fields where the AI returned our placeholder instead of real base64 data
    if (it.value().is_string() && it.value().get<std::string>() == kPlaceholder)
      continue;

    if (it.value().is_object() && target.count(it.key()) && target[it.key()].is_object()) {
      mergeJson(target[it.key()], it.value());
    } else if (it.value().is_array() && target.count(it.key()) && target[it.key()].is_array()) {
      // For arrays (e.g. wavetables), merge element-by-element; null means keep original
      auto& target_arr = target[it.key()];
      const auto& patch_arr = it.value();
      for (size_t i = 0; i < patch_arr.size() && i < target_arr.size(); ++i) {
        if (patch_arr[i].is_null())
          continue;
        if (patch_arr[i].is_object() && target_arr[i].is_object())
          mergeJson(target_arr[i], patch_arr[i]);
        else
          target_arr[i] = patch_arr[i];
      }
    } else {
      target[it.key()] = it.value();
    }
  }
}

void FullInterface::stripBase64DataForLLM(json& state) {
  if (!state.count("settings"))
    return;

  auto& settings = state["settings"];

  // Strip sample base64 data
  if (settings.count("sample")) {
    auto& sample = settings["sample"];
    if (sample.count("samples"))
      sample["samples"] = "(base64 data removed)";
    if (sample.count("samples_stereo"))
      sample["samples_stereo"] = "(base64 data removed)";
  }

  // Strip Wave Source base64 wave_data from wavetables
  if (settings.count("wavetables") && settings["wavetables"].is_array()) {
    for (auto& wavetable : settings["wavetables"]) {
      if (wavetable.count("groups") && wavetable["groups"].is_array()) {
        for (auto& group : wavetable["groups"]) {
          if (group.count("components") && group["components"].is_array()) {
            for (auto& component : group["components"]) {
              if (component.count("keyframes") && component["keyframes"].is_array()) {
                for (auto& keyframe : component["keyframes"]) {
                  if (keyframe.count("wave_data"))
                    keyframe["wave_data"] = "(base64 data removed)";
                }
              }
            }
          }
        }
      }
    }
  }
}

void FullInterface::sidePanelMessageSubmitted(const String& message) {
  if (api_request_in_flight_) {
    queued_messages_.add(message);
    return;
  }

  api_request_in_flight_ = true;

  VitalSidePanel* panel = side_panel_.get();
  if (panel) {
    panel->addMessage("Thinking...", ChatMessage::kSystem);

    File checkpoint = saveAutosaveCheckpoint();
    if (checkpoint.exists()) {
      int user_msg_idx = panel->getMessageCount() - 2;
      int api_size = ClaudeApiClient::instance().getHistorySize();
      panel->addCheckpoint(user_msg_idx, api_size, checkpoint);
    }
  }

  routeAndExecute(message);
}

void FullInterface::routeAndExecute(const String& message) {
  VitalSidePanel* panel = side_panel_.get();

  int gen = api_request_generation_;
  ClaudeApiClient::instance().routeMessage(message, [this, panel, message, gen](
      const StringArray& actions, bool sound_design_required, bool save_required, const String& preset_name, bool success, const String& error) {
    if (!panel || gen != api_request_generation_) {
      api_request_in_flight_ = false;
      is_sound_design_reroute_ = false;
      queued_messages_.clear();
      return;
    }

    if (!success) {
      // Router failed — fall back to sending the original message directly
      DBG("Router failed (" + error + "), falling back to direct send");
      is_sound_design_reroute_ = false;
      StringArray messages;
      messages.add(message);
      sendApiRequest(messages);
      return;
    }

    // Store save state from first routing pass only (not from re-routed translations)
    if (!is_sound_design_reroute_) {
      pending_save_required_ = save_required;
      pending_preset_name_ = preset_name;
    }

    if (sound_design_required && !is_sound_design_reroute_) {
      // Sound design path — translate non-technical description into technical instructions
      // Replace "Thinking..." with permanent "Designing sound..." message
      panel->updateStatusMessage("Designing sound...");

      // Get fresh preset JSON for the translation call
      String preset_json;
      SynthGuiInterface* gui_interface = findParentComponentOfClass<SynthGuiInterface>();
      if (gui_interface && gui_interface->getSynth()) {
        json state = gui_interface->getSynth()->getStateAsJson();
        stripBase64DataForLLM(state);
        preset_json = String(state.dump());
      }

      ClaudeApiClient::instance().sendSoundDesignTranslation(message,
        [this, panel, message, gen](const String& translation, bool translationSuccess) {
          if (!panel || gen != api_request_generation_) {
            api_request_in_flight_ = false;
            is_sound_design_reroute_ = false;
            queued_messages_.clear();
            return;
          }

          if (!translationSuccess) {
            // Fallback: send original message directly
            DBG("Sound design translation failed, falling back to direct send");
            is_sound_design_reroute_ = false;
            StringArray messages;
            messages.add(message);
            sendApiRequest(messages);
            return;
          }

          // Don't show translation in chat — it's an internal intermediate step
          // Add a new "Thinking..." below the persistent "Designing sound..." message
          panel->addMessage("Thinking...", ChatMessage::kSystem);

          // Store original user message in history before re-routing translation
          ClaudeApiClient::instance().addToHistory("user", message);
          is_sound_design_reroute_ = true;
          routeAndExecute(translation);
        }, preset_json);
      return;
    }

    // Capture whether this came from sound design before resetting
    bool was_sound_design_reroute = is_sound_design_reroute_;
    is_sound_design_reroute_ = false;

    if (actions.isEmpty() && pending_save_required_) {
      // Save-only request — no actions to execute, just save immediately
      savePresetToSoundDesigner(pending_preset_name_);
      panel->addResponseMessage("Saved preset as " + pending_preset_name_);
      pending_save_required_ = false;
      pending_preset_name_ = String();
      api_request_in_flight_ = false;
      if (!queued_messages_.isEmpty()) {
        String next = queued_messages_[0];
        queued_messages_.remove(0);
        api_request_in_flight_ = true;
        panel->addMessage("Thinking...", ChatMessage::kSystem);
        routeAndExecute(next);
      }
      return;
    }

    if (actions.isEmpty()) {
      // No actions and not sound design — fall back to sending the original message
      StringArray messages;
      messages.add(message);
      sendApiRequest(messages);
      return;
    }

    if (actions.size() == 1) {
      // Single action — pass through directly with original message
      StringArray messages;
      messages.add(message);
      sendApiRequest(messages);
      return;
    }

    // Multiple actions — execute sequentially (don't store full message to avoid one-shotting)
    pending_actions_ = actions;
    total_actions_ = actions.size();
    current_action_index_ = 0;
    is_sound_design_multi_action_ = was_sound_design_reroute;

    if (!is_sound_design_multi_action_) {
      panel->updateStatusMessage("Breaking it down...");
      panel->addMessage("Thinking...", ChatMessage::kSystem);
    }
    executeNextAction();
  });
}

void FullInterface::executeNextAction() {
  VitalSidePanel* panel = side_panel_.get();
  if (!panel || current_action_index_ >= pending_actions_.size()) {
    // All actions done
    pending_actions_.clear();
    total_actions_ = 0;
    current_action_index_ = 0;
    is_sound_design_multi_action_ = false;
    api_request_in_flight_ = false;

    // Check queued messages
    if (!queued_messages_.isEmpty()) {
      String next = queued_messages_[0];
      queued_messages_.remove(0);
      api_request_in_flight_ = true;
      panel->addMessage("Thinking...", ChatMessage::kSystem);
      routeAndExecute(next);
    }
    return;
  }

  String action = pending_actions_[current_action_index_];
  int stepNum = current_action_index_ + 1;
  String truncated = action;
  if (action.length() > 50) {
    int cutoff = action.substring(0, 50).lastIndexOfChar(' ');
    truncated = action.substring(0, cutoff > 0 ? cutoff : 50) + "...";
  }
  String stepMsg = "Working on step " + String(stepNum) + " of " + String(total_actions_) + ": " + truncated;
  panel->updateStatusMessage(stepMsg, ChatMessage::kStep);

  current_action_index_++;

  StringArray messages;
  messages.add(action);
  sendApiRequest(messages);
}

void FullInterface::sendApiRequest(const StringArray& messages) {
  VitalSidePanel* panel = side_panel_.get();

  // Get fresh preset state as JSON to provide context to Claude
  String preset_json;
  SynthGuiInterface* gui_interface = findParentComponentOfClass<SynthGuiInterface>();
  if (gui_interface && gui_interface->getSynth()) {
    json state = gui_interface->getSynth()->getStateAsJson();
    stripBase64DataForLLM(state);
    preset_json = String(state.dump());
  }

  int gen = api_request_generation_;
  ClaudeApiClient::instance().sendMessages(messages, [panel, this, gen](const String& response, bool success) {
    // This callback is already on the message thread (handled by ClaudeApiClient)
    if (!panel || gen != api_request_generation_) {
      api_request_in_flight_ = false;
      queued_messages_.clear();
      return;
    }

    bool is_multi_action = total_actions_ > 1;

    if (!is_multi_action)
      panel->clearThinkingMessage();

    if (!success) {
      if (is_multi_action) {
        if (is_sound_design_multi_action_)
          panel->removeStatusMessage("Designing sound...");
        else
          panel->removeStatusMessage("Breaking it down...");
        panel->updateStatusMessage("Error: " + response);
      } else
        panel->addResponseMessage(response);
      // On failure, clear multi-action state, queue, and stop
      pending_actions_.clear();
      total_actions_ = 0;
      current_action_index_ = 0;
      is_sound_design_multi_action_ = false;
      pending_save_required_ = false;
      pending_preset_name_ = String();
      api_request_in_flight_ = false;
      queued_messages_.clear();
      return;
    }

    // Split response into text and JSON portions
    String jsonBlock;
    String textMessage;
    ClaudeApiClient::splitResponseText(response, textMessage, jsonBlock);

    // Try to parse JSON (from code fence, or the whole response as fallback)
    String jsonToParse = jsonBlock.isNotEmpty() ? jsonBlock : response.trim();
    try {
      json patch = json::parse(jsonToParse.toStdString(), nullptr);

      if (patch.count("settings")) {
        SynthGuiInterface* gui = findParentComponentOfClass<SynthGuiInterface>();
        if (gui && gui->getSynth()) {
          json current = gui->getSynth()->getStateAsJson();
          FullInterface::mergeJson(current, patch);

          bool loaded = gui->getSynth()->loadStateFromJson(current);
          if (loaded) {
            gui->updateFullGui();
            gui->notifyFresh();

            if (is_multi_action) {
              if (current_action_index_ < pending_actions_.size()) {
                // More steps remaining — silently proceed to next step
                executeNextAction();
                return;
              }

              // Final step
              if (is_sound_design_multi_action_) {
                // Sound design — replace "Designing sound..." with result
                panel->removeStatusMessage("Designing sound...");
              } else {
                // Direct multi-action — remove "Breaking it down..."
                panel->removeStatusMessage("Breaking it down...");
              }
              String msg = textMessage.isNotEmpty() ? textMessage : getCompletionPhrase();
              panel->updateStatusMessage(msg);

              pending_actions_.clear();
              total_actions_ = 0;
              current_action_index_ = 0;
              is_sound_design_multi_action_ = false;
            } else {
              String msg = textMessage.isNotEmpty() ? textMessage : getCompletionPhrase();
              // Single action — show as normal response
              panel->addResponseMessage(msg);
            }

            // Save preset if requested by router
            if (pending_save_required_ && pending_preset_name_.isNotEmpty()) {
              savePresetToSoundDesigner(pending_preset_name_);
              panel->addMessage("Saved preset as " + pending_preset_name_, ChatMessage::kSystem);
              pending_save_required_ = false;
              pending_preset_name_ = String();
            }

            // Autosave checkpoint for the response
            {
              File cp = saveAutosaveCheckpoint();
              if (cp.exists())
                panel->addCheckpoint(panel->getMessageCount() - 1,
                                     ClaudeApiClient::instance().getHistorySize(), cp);
            }

            // Check queue after successful response
            if (!queued_messages_.isEmpty()) {
              String next = queued_messages_[0];
              queued_messages_.remove(0);
              panel->addMessage("Thinking...", ChatMessage::kSystem);
              routeAndExecute(next);
            } else {
              api_request_in_flight_ = false;
            }
            return;
          }
        }
        if (is_multi_action) {
          if (is_sound_design_multi_action_)
            panel->removeStatusMessage("Designing sound...");
          else
            panel->removeStatusMessage("Breaking it down...");
          panel->updateStatusMessage("Failed to load preset from response.");
        } else
          panel->addResponseMessage("Failed to load preset from response.");
        pending_actions_.clear();
        total_actions_ = 0;
        current_action_index_ = 0;
        is_sound_design_multi_action_ = false;
        pending_save_required_ = false;
        pending_preset_name_ = String();
        api_request_in_flight_ = false;
        queued_messages_.clear();
        return;
      }
    }
    catch (const json::exception&) {
      // Not valid JSON - fall through to show as text
    }

    // Text-only response
    String displayText = textMessage.isNotEmpty() ? textMessage : response;

    if (is_multi_action) {
      if (current_action_index_ < pending_actions_.size()) {
        // More steps remaining — silently proceed to next step
        executeNextAction();
        return;
      }

      // Final step
      if (is_sound_design_multi_action_)
        panel->removeStatusMessage("Designing sound...");
      else
        panel->removeStatusMessage("Breaking it down...");
      panel->updateStatusMessage(displayText);

      pending_actions_.clear();
      total_actions_ = 0;
      current_action_index_ = 0;
      is_sound_design_multi_action_ = false;
    } else {
      panel->addResponseMessage(response);
    }

    // Save preset if requested by router
    if (pending_save_required_ && pending_preset_name_.isNotEmpty()) {
      savePresetToSoundDesigner(pending_preset_name_);
      panel->addMessage("Saved preset as " + pending_preset_name_, ChatMessage::kSystem);
      pending_save_required_ = false;
      pending_preset_name_ = String();
    }

    // Autosave checkpoint for the text-only response
    {
      File cp = saveAutosaveCheckpoint();
      if (cp.exists())
        panel->addCheckpoint(panel->getMessageCount() - 1,
                             ClaudeApiClient::instance().getHistorySize(), cp);
    }

    // Check queue after text-only response too
    if (!queued_messages_.isEmpty()) {
      String next = queued_messages_[0];
      queued_messages_.remove(0);
      panel->addMessage("Thinking...", ChatMessage::kSystem);
      routeAndExecute(next);
    } else {
      api_request_in_flight_ = false;
    }
  }, preset_json);
}

void FullInterface::savePresetToSoundDesigner(const String& presetName) {
  SynthGuiInterface* gui = findParentComponentOfClass<SynthGuiInterface>();
  if (!gui || !gui->getSynth())
    return;

  File presetDir = LoadSave::getUserPresetDirectory().getChildFile("Sound Designer");
  if (!presetDir.exists())
    presetDir.createDirectory();

  String safeName = presetName.removeCharacters("\\/:*?\"<>|");
  if (safeName.isEmpty())
    safeName = "Untitled";

  File presetFile = presetDir.getChildFile(safeName + ".vital");
  gui->getSynth()->saveToFile(presetFile);
}

File FullInterface::saveAutosaveCheckpoint() {
  SynthGuiInterface* gui = findParentComponentOfClass<SynthGuiInterface>();
  if (!gui || !gui->getSynth())
    return File();

  File dir = LoadSave::getDataDirectory().getChildFile("autosaves");
  if (!dir.exists())
    dir.createDirectory();

  int64 now = Time::currentTimeMillis();
  File file = dir.getChildFile("checkpoint_" + String(now) + ".vital");

  json state = gui->getSynth()->getStateAsJson();
  file.replaceWithText(String(state.dump()));
  return file;
}

bool FullInterface::sidePanelRestoreRequested(int message_index) {
  VitalSidePanel* panel = side_panel_.get();
  if (!panel) return false;

  // Use the user message's own checkpoint (pre-response state)
  const ChatCheckpoint* cp = panel->getCheckpoint(message_index);
  if (!cp || !cp->autosave_file.exists()) return false;

  SynthGuiInterface* gui = findParentComponentOfClass<SynthGuiInterface>();
  if (!gui || !gui->getSynth()) return false;

  try {
    json state = json::parse(cp->autosave_file.loadFileAsString().toStdString());
    bool loaded = gui->getSynth()->loadStateFromJson(state);
    if (!loaded) {
      panel->addResponseMessage("Failed to restore checkpoint.");
      return false;
    }
    gui->updateFullGui();
    gui->notifyFresh();
  } catch (const json::exception&) {
    panel->addResponseMessage("Failed to restore checkpoint: corrupt file.");
    return false;
  }

  // Truncate UI messages — remove the user message itself and everything after
  panel->truncateMessagesTo(message_index);

  // Truncate API conversation history
  ClaudeApiClient::instance().truncateHistoryTo(cp->api_history_size);

  // Remove checkpoint entries from the vector but do NOT delete files from disk.
  // enterEditMode() saved a snapshot that references these files — they must remain
  // intact so cancelEditMode() can restore them. Files are cleaned up by
  // exitEditMode() when the edit is committed (submit) or discarded (clear).
  panel->removeCheckpointsAfter(message_index - 1, false);

  // Cancel any in-flight API requests and multi-action state
  ++api_request_generation_;
  api_request_in_flight_ = false;
  queued_messages_.clear();
  pending_actions_.clear();
  total_actions_ = 0;
  current_action_index_ = 0;
  is_sound_design_multi_action_ = false;

  return true;
}

std::vector<ClaudeApiClient::HistoryEntry> FullInterface::sidePanelGetApiHistorySnapshot() {
  return ClaudeApiClient::instance().getHistorySnapshot();
}

File FullInterface::sidePanelSaveCheckpoint() {
  return saveAutosaveCheckpoint();
}

void FullInterface::sidePanelCancelEditRequested(const File& checkpoint, const std::vector<ClaudeApiClient::HistoryEntry>& history_snapshot) {
  if (!checkpoint.exists()) return;

  SynthGuiInterface* gui = findParentComponentOfClass<SynthGuiInterface>();
  if (!gui || !gui->getSynth()) return;

  try {
    json state = json::parse(checkpoint.loadFileAsString().toStdString());
    bool loaded = gui->getSynth()->loadStateFromJson(state);
    if (loaded) {
      gui->updateFullGui();
      gui->notifyFresh();
    }
  } catch (const json::exception&) {
    // Silently fail — state will remain as-is
  }

  // Restore full API conversation history from snapshot
  ClaudeApiClient::instance().restoreHistory(history_snapshot);

  // Cancel any in-flight API requests and multi-action state
  ++api_request_generation_;
  api_request_in_flight_ = false;
  queued_messages_.clear();
  pending_actions_.clear();
  total_actions_ = 0;
  current_action_index_ = 0;
  is_sound_design_multi_action_ = false;

}

void FullInterface::sidePanelClearRequested() {
  ++api_request_generation_;
  api_request_in_flight_ = false;
  queued_messages_.clear();
  pending_actions_.clear();
  total_actions_ = 0;
  current_action_index_ = 0;
  is_sound_design_multi_action_ = false;
  pending_save_required_ = false;
  pending_preset_name_ = String();
}
