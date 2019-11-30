#pragma once

#include "core/engine/engine.hpp"

#include "itc/itc.hpp"

namespace otto::engines::chorus {

  using namespace core::props;

  struct Screen;
  struct Audio;

  using Sender = core::engine::EngineSender<Audio, Screen>;

  struct Actions {
    /// Publish the rotation variable, which is shared between the audio and screen
    using phase_value = itc::Action<struct phase_value_tag, std::atomic<float>&>;
  };

  struct Props {
    Sender sender;

    Sender::Prop<struct delay_tag, float> delay = {sender, 0.8, limits(0, 1), step_size(0.01)};
    Sender::Prop<struct depth_tag, float> depth = {sender, 0.5, limits(0, 1), step_size(0.01)};
    Sender::Prop<struct feedback_tag, float> feedback = {sender, 0, limits(-0.99, 0.99), step_size(0.01)};
    Sender::Prop<struct rate_tag, float> rate = {sender, 0, limits(0, 2), step_size(0.1)};
    DECL_REFLECTION(Props, delay, depth, feedback, rate);
  };

  struct Chorus : core::engine::EffectEngine<Chorus> {
    static constexpr util::string_ref name = "Chorus";
    Chorus();

    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput screen() override;
  
    std::unique_ptr<Audio> audio;
    std::unique_ptr<Screen> screen_;
    

    std::atomic<float> phase_ = 0;

    Sender sender_ = {*audio, *screen_};
    Props props;
  };

} // namespace otto::engines::chorus
