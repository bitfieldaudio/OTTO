#pragma once

#include "core/engine/engine.hpp"
#include "core/ui/screen.hpp"
#include "core/voices/voice_manager.hpp"
#include "core/voices/voices_ui.hpp"
#include "itc/prop.hpp"
#include "util/reflection.hpp"

namespace otto::engines::goss {

  // Stuff needed for both audio and the screen
  constexpr int number_of_models = 11; // When changed, update model limits.
  constexpr int model_size = 9;
  using model_type = std::array<int, model_size>;
  // Only static data is shared. nothing during runtime
  /// Number of sine cycles for each drawbar. multiplied by 2.
  // Note: perhaps all could be divided by 2 but then we get a cusp for the second drawbar.
  constexpr model_type cycles = {1, 3, 2, 4, 6, 8, 10, 12, 16};
  /// The drawbar settings. correspond to typical hammond drawbars in ascending order.
  constexpr std::array<model_type, number_of_models> model_params = {{{8, 8, 8, 0, 0, 0, 0, 0, 0},
                                                                      {0, 0, 8, 5, 0, 0, 0, 0, 0},
                                                                      {8, 8, 8, 0, 0, 0, 0, 0, 2},
                                                                      {8, 4, 8, 0, 0, 0, 0, 0, 0},
                                                                      {8, 8, 8, 8, 8, 8, 8, 6, 4},
                                                                      {6, 6, 8, 8, 4, 8, 5, 8, 2},
                                                                      {8, 0, 0, 0, 0, 0, 6, 7, 6},
                                                                      {8, 3, 5, 3, 5, 8, 0, 7, 0},
                                                                      {8, 3, 0, 0, 0, 0, 3, 7, 6},
                                                                      {8, 0, 3, 6, 0, 0, 0, 0, 0},
                                                                      {2, 0, 8, 8, 0, 0, 0, 0, 3}}};

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct GossScreen;
  struct Audio;

  struct Props : core::props::Properties<Props> {
    // SettingsProps is mandatory for a synth. This gives it the necessary settings for the voice manager
    voices::SettingsProps settings;
    // EnvelopeProps gives settings for a standard ADSR envelope. It is optional if you would rather do something
    // different.
    voices::EnvelopeProps envelope;

    itc::GAProp<struct model_tag, int, wrap> model = {0, limits(0, number_of_models - 1)};
    itc::GAProp<struct drive_tag, float> drive = {0.5, limits(0, 1), step_size(0.01)};
    itc::GAProp<struct click_tag, float> click = {0.5, limits(0, 1), step_size(0.01)};
    itc::GAProp<struct leslie_tag, float> leslie = {0.3, limits(0, 1), step_size(0.01)};

    REFLECT_PROPS(Props, settings, envelope, model, drive, click, leslie);
  };

  struct GossEngine : core::engine::SynthEngine<GossEngine>, itc::ActionReceiverOnBus<itc::LogicBus> {
    static constexpr auto name = "Goss";

    GossEngine(itc::ActionChannel);

    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput screen() override;
    core::ui::ScreenAndInput envelope_screen() override;
    core::ui::ScreenAndInput voices_screen() override;

    const std::unique_ptr<Audio> audio;

    DECL_REFLECTION(GossEngine, props);

  private:
    itc::Shared<float>::Storage rotation_;
    const std::unique_ptr<GossScreen> screen_;
    voices::SettingsScreen voice_screen_;
    voices::EnvelopeScreen env_screen_;

  public:
    Props props;
  };

} // namespace otto::engines::goss
