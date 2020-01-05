#include "external_in.hpp"

#include "audio.hpp"
#include "screen.hpp"

namespace otto::engines::external {

  using namespace services;
  using namespace core::input;

  External::External()
    : audio(std::make_unique<Audio>()), screen_(std::make_unique<Screen>()), props({{*audio, *screen_}})
  {}

  void External::encoder(EncoderEvent ev)
  {
    switch (ev.encoder) {
      case Encoder::blue: {
        if (props.mode == 1) props.stereo_gain.step(ev.steps); 
        else if (props.mode == 2) props.left_gain.step(ev.steps);
        break;
      }
      case Encoder::green:  {
        if (props.mode == 1) props.stereo_balance.step(ev.steps); 
        else if (props.mode == 2) props.right_gain.step(ev.steps);
        break;
      }
      case Encoder::yellow: props.active_send.step(ev.steps); break;
      case Encoder::red: props.mode.step(ev.steps); break;
    }
  }

  core::ui::ScreenAndInput External::screen()
  {
    return {*screen_, *this};
  }

} // namespace otto::engines::external