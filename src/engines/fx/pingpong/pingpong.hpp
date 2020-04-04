#pragma once

#include "core/audio/clock.hpp"
#include "core/engine/engine.hpp"

#include "core/input.hpp"
#include "itc/itc.hpp"

namespace otto::engines::pingpong {

  using namespace core::props;

  struct Screen;
  struct Audio;

  using Sender = core::engine::EngineSender<Audio, Screen>;

  struct Props {
    Sender sender;

    /// Changes between free delay time and subdivisions
    Sender::Prop<struct timetype_tag, bool> timetype = {sender, false};
    /// Only changed when timetype is false. 
    Sender::Prop<struct free_time_tag, float> free_time = {sender, 0, limits(0, 1), step_size(0.01)};
    /// Only changed when timetype is true
    Sender::Prop<struct subdivision_tag, int> subdivision = {sender, 0, limits(0, 6)};
    /// Actual delaytime in ms. Sent to the audio thread
    // 6 seconds is the length of a measure at 40 bpm
    Sender::Prop<struct free_time_tag, float> delaytime = {sender, 500, limits(0, 6)};

    // 0.5 is neutral
    Sender::Prop<struct filter_tag, float> filter = {sender, 0.5, limits(0, 1), step_size(0.01)};
    
    // 0.5 is neutral
    Sender::Prop<struct stereo_tag, float> stereo = {sender, 0.5, limits(0, 1), step_size(0.01)};
    Sender::Prop<struct stereo_invert_tag, bool> stereo_invert = {sender, false};

    Sender::Prop<struct feedback_tag, float> feedback = {sender, 0.2, limits(0, 0.99), step_size(0.01)};

    DECL_REFLECTION(Props, free_time, delaytime, subdivision, timetype, filter, stereo, stereo_invert, feedback);
  };

  struct PingPong : core::engine::EffectEngine<PingPong> {
    static constexpr util::string_ref name = "PingPong";
    PingPong();

    float calculate_delaytime(bool type, float free, int sd);

    bool keypress(core::input::Key k) override;
    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput screen() override;

    std::unique_ptr<Audio> audio;
    std::unique_ptr<Screen> screen_;

    Props props;
  };

} // namespace otto::engines::wormhole

#include "audio.hpp"
#include "screen.hpp"
