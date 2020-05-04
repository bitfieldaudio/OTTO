#pragma once

#include <better_enum.hpp>
#include <cstdint>

#include "core/audio/audio_buffer_pool.hpp"
#include "core/engine/engine.hpp"
#include "engines/misc/sends/sends.hpp"
#include "itc/itc.hpp"
#include "services/ui_manager.hpp"
#include "util/reflection.hpp"
#include "core/ui/icons.hpp"

namespace otto::engines::external {

  using namespace core::props;

  struct Screen;
  struct Audio;

  BETTER_ENUM(ModeEnum, std::int8_t, disabled, stereo, dual_mono);

  struct Props : core::props::Properties<Props>{
    /// Mode control
    itc::GAProp<struct mode_tag, ModeEnum> mode = {ModeEnum::disabled};
    /// Input gains
    /// Stereo mode
    itc::GAProp<struct stereo_gain_tag, float> stereo_gain = {0.5, limits(0, 1), step_size(0.01)};
    itc::GAProp<struct balance_tag, float> stereo_balance = {0.5, limits(0, 1), step_size(0.01)};
    /// Dual Mono mode
    itc::GAProp<struct left_gain_tag, float> left_gain = {0.5, limits(0, 1), step_size(0.01)};
    itc::GAProp<struct right_gain_tag, float> right_gain = {0.5, limits(0, 1), step_size(0.01)};
    /// TBD: Possible use is switching between active send
    itc::GAProp<struct active_send_tag, int> active_send = {0, limits(0, 1)};


    REFLECT_PROPS(Props, mode, stereo_gain, stereo_balance, left_gain, right_gain, active_send);
  };

  struct External : core::engine::MiscEngine<External>, itc::ActionReceiverOnBus<itc::LogicBus> {
    static constexpr util::string_ref name = "External";

    External();

    void encoder(core::input::EncoderEvent e) override;

    services::ChannelEnum channel();
    sends::Sends& active_send();

    core::ui::ScreenAndInput screen() override;

    core::ui::Icon line_icon = core::ui::Icon(core::ui::icons::line_in_icon);
    sends::Sends send_stereo = {itc::ActionChannel::ext_send_stereo, line_icon};
    sends::Sends send_left = {itc::ActionChannel::ext_send_left, line_icon};
    sends::Sends send_right = {itc::ActionChannel::ext_send_right, line_icon};

    DECL_REFLECTION(External, props, send_stereo, send_left, send_right);

    std::unique_ptr<Audio> audio;
  
  private:
    std::unique_ptr<Screen> screen_;

    Props props;
  };
} // namespace otto::engines::external
