#pragma once

#include "core/engine/engine.hpp"
#include "itc/itc.hpp"

namespace otto::engines::external {

  using namespace core::props;

  struct Screen;
  struct Audio;

  using Sender = services::UISender<Audio, Screen>;

  struct Props {
    Sender sender;

    /// Mode control
    /// 0: off, 1: stereo, 2: dual mono
    Sender::Prop<struct mode_tag, int> mode = {sender, 1, limits(0, 2)};
    /// Input gains
    /// Stereo mode
    Sender::Prop<struct stereo_gain_tag, float> stereo_gain = {sender, 0.5, limits(0, 1), step_size(0.01)};
    Sender::Prop<struct balance_tag, float> stereo_balance = {sender, 0.5, limits(0, 1), step_size(0.01)};
    /// Dual Mono mode
    Sender::Prop<struct left_gain_tag, float> left_gain = {sender, 0.5, limits(0, 1), step_size(0.01)};
    Sender::Prop<struct right_gain_tag, float> right_gain = {sender, 0.5, limits(0, 1), step_size(0.01)};
    /// TBD: Possible use is swithing between active send
    Sender::Prop<struct active_send_tag, int> active_send = {sender, 0, limits(0, 1)};


    DECL_REFLECTION(Props, mode, stereo_gain, stereo_balance, left_gain, right_gain, active_send);
  };

  struct External : core::engine::MiscEngine<External> {
    static constexpr util::string_ref name = "External";

    External();

    void encoder(core::input::EncoderEvent e) override;

    core::ui::ScreenAndInput screen() override;

    std::unique_ptr<Audio> audio;
    std::unique_ptr<Screen> screen_;

    Props props;
  };
} // namespace otto::engines::external

#include "audio.hpp"
#include "screen.hpp"