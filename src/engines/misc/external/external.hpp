#pragma once

#include <better_enum.hpp>
#include <cstdint>

#include "core/audio/audio_buffer_pool.hpp"
#include "core/engine/engine.hpp"
#include "engines/misc/sends/sends.hpp"
#include "itc/itc.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines::external {

  using namespace core::props;

  struct Screen;
  struct Audio;

  using Sender = core::engine::EngineSender<Audio, Screen>;

  BETTER_ENUM(ModeEnum, std::int8_t, disabled, stereo, dual_mono);

  struct Props {
    Sender sender;

    /// Mode control
    Sender::Prop<struct mode_tag, ModeEnum> mode = {sender, ModeEnum::disabled};
    /// Input gains
    /// Stereo mode
    Sender::Prop<struct stereo_gain_tag, float> stereo_gain = {sender, 0.5, limits(0, 1), step_size(0.01)};
    Sender::Prop<struct balance_tag, float> stereo_balance = {sender, 0.5, limits(0, 1), step_size(0.01)};
    /// Dual Mono mode
    Sender::Prop<struct left_gain_tag, float> left_gain = {sender, 0.5, limits(0, 1), step_size(0.01)};
    Sender::Prop<struct right_gain_tag, float> right_gain = {sender, 0.5, limits(0, 1), step_size(0.01)};
    /// TBD: Possible use is switching between active send
    Sender::Prop<struct active_send_tag, int> active_send = {sender, 0, limits(0, 1)};


    DECL_REFLECTION(Props, mode, stereo_gain, stereo_balance, left_gain, right_gain, active_send);
  };

  struct External : core::engine::MiscEngine<External> {
    static constexpr util::string_ref name = "External";

    External();

    void encoder(core::input::EncoderEvent e) override;

    services::ChannelEnum channel();
    sends::Sends& active_send();

    core::ui::ScreenAndInput screen() override;

    

    sends::Sends send_stereo;
    sends::Sends send_left;
    sends::Sends send_right;

    std::unique_ptr<Audio> audio;
    std::unique_ptr<Screen> screen_;

    Props props;
  };
} // namespace otto::engines::external

#include "audio.hpp"
#include "screen.hpp"