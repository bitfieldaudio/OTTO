#include "external.hpp"

#include "audio.hpp"
#include "screen.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines::external {

  using namespace services;
  using namespace core::input;

  External::External()
    : audio(std::make_unique<Audio>(*send_stereo.audio, *send_left.audio, *send_right.audio)),
      screen_(std::make_unique<Screen>())
  {
    set_children(props, audio, screen_);
    register_to(itc::ActionChannel::external);
    props.send_actions();
  }

  void External::encoder(EncoderEvent ev)
  {
    switch (ev.encoder) {
      case Encoder::blue: {
        if (props.mode == ModeEnum::stereo) {
          props.stereo_gain.step(ev.steps);
        } else if (props.mode == ModeEnum::dual_mono) {
          props.left_gain.step(ev.steps);
        }
        break;
      }
      case Encoder::green: {
        if (props.mode == ModeEnum::stereo) {
          props.stereo_balance.step(ev.steps);
        } else if (props.mode == ModeEnum::dual_mono) {
          props.right_gain.step(ev.steps);
        }
        break;
      }
      case Encoder::yellow: props.active_send.step(ev.steps); break;
      case Encoder::red: props.mode.step(ev.steps); break;
    }
  }

  services::ChannelEnum External::channel()
  {
    if (props.mode.get() == +ModeEnum::dual_mono && props.active_send.get() == 0)
      return ChannelEnum::external_left;
    else if (props.mode.get() == +ModeEnum::dual_mono && props.active_send.get() == 1)
      return ChannelEnum::external_right;
    else
      return ChannelEnum::external_stereo;
  }

  sends::Sends& External::active_send()
  {
    if (props.mode.get() == +ModeEnum::dual_mono && props.active_send.get() == 0)
      return send_left;
    else if (props.mode.get() == +ModeEnum::dual_mono && props.active_send.get() == 1)
      return send_right;
    else
      return send_stereo;
  }



  core::ui::ScreenAndInput External::screen()
  {
    return {*screen_, *this};
  }

} // namespace otto::engines::external
