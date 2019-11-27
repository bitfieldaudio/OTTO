#pragma once

#include "core/engine/engine.hpp"
#include "core/ui/screen.hpp"
#include "core/voices/voice_manager.hpp"
#include "core/voices/voices_ui.hpp"
#include "itc/prop.hpp"
#include "util/reflection.hpp"

namespace otto::engines::goss {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct GossScreen;
  struct Audio;
  using Sender = EngineSender<Audio, GossScreen, voices::SettingsScreen, voices::EnvelopeScreen>;

  struct Actions {
    /// Publish the rotation variable, which is shared between the audio and screen
    using rotation_variable = itc::Action<struct rotation_variable_tag, std::atomic<float>&>;
  };

  struct Props : voices::SynthPropsBase<Sender> {
    Sender::Prop<struct model_tag, int> model = {sender, 0, limits(0, 2)};
    Sender::Prop<struct drawbar2_tag, float> drawbar2 = {sender, 0.5, limits(0, 1), step_size(0.01)};
    Sender::Prop<struct click_tag, float> click = {sender, 0.5, limits(0, 1), step_size(0.01)};
    Sender::Prop<struct leslie_tag, float> leslie = {sender, 0.3, limits(0, 1), step_size(0.01)};

    DECL_REFLECTION(Props, envelope, settings, model, drawbar2, click, leslie);
  };

  struct GossEngine : core::engine::SynthEngine<GossEngine> {
    static constexpr auto name = "Goss";
    using Audio = Audio;
    using Screen = GossScreen;
    using Props = Props;

    GossEngine();

    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput screen() override;
    core::ui::ScreenAndInput envelope_screen() override;
    core::ui::ScreenAndInput voices_screen() override;

    const std::unique_ptr<Audio> audio;

    DECL_REFLECTION(GossEngine, props);

  private:
    const std::unique_ptr<GossScreen> screen_;
    voices::SettingsScreen voice_screen_;
    voices::EnvelopeScreen env_screen_;

    Sender sender_ = {*audio, *screen_, voice_screen_, env_screen_};
    Props props{sender_};

    std::atomic<float> rotation_ = 0;
  };
} // namespace otto::engines::goss
