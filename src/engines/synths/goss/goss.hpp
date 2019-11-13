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
  using GraphicsSndr = itc::ActionSender<GossScreen, voices::EnvelopeScreen, voices::SettingsScreen>;

  struct Audio;
  using AudioSndr = itc::ActionSender<Audio>;

  using Sndr = itc::JoinedActionSender<GraphicsSndr, AudioSndr>;

  struct Actions {
    /// Publish the rotation variable, which is shared between the audio and screen
    using rotation_variable = itc::Action<struct rotation_variable_tag, std::atomic<float>&>;
  };

  struct Props {
    Sndr* sndr;

    Sndr::Prop<struct model_tag, int> model = {sndr, 0, limits(0, 2)};
    Sndr::Prop<struct drawbar2_tag, float> drawbar2 = {sndr, 0.5, limits(0, 1), step_size(0.01)};
    Sndr::Prop<struct click_tag, float> click = {sndr, 0.5, limits(0, 1), step_size(0.01)};
    Sndr::Prop<struct leslie_tag, float> leslie = {sndr, 0.3, limits(0, 1), step_size(0.01)};

    DECL_REFLECTION(Props, model, drawbar2, click, leslie);
  };

  struct GossEngine : core::engine::SynthEngine<GossEngine> {
    static constexpr auto name = "Goss";
    using Audio = Audio;
    using Screen = GossScreen;
    using Props = Props;
    GossEngine();

    const std::unique_ptr<GossScreen> screen;
    const std::unique_ptr<Audio> audio;

    DECL_REFLECTION(GossEngine, props, voice_props_, envelope_props_);

    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput envelope_screen() override 
    {
      return {env_screen_, envelope_props_};
    }
    core::ui::ScreenAndInput voices_screen() override
    {
      return {voice_screen_, voice_props_};
    }

  private:
    GraphicsSndr graphics_sndr_;
    AudioSndr audio_sndr_;
    Sndr sndr_ = {graphics_sndr_, audio_sndr_};

    Props props{&sndr_};

    voices::SettingsProps<Sndr> voice_props_ {&sndr_};
    voices::EnvelopeProps<Sndr> envelope_props_ {&sndr_};
    voices::SettingsScreen voice_screen_;
    voices::EnvelopeScreen env_screen_;


    std::atomic<float> rotation_ = 0;
  };
} // namespace otto::engines::goss
