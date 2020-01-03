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
      case Encoder::blue: props.gain.step(ev.steps); break;
      case Encoder::green: props.enabled.set(!props.enabled.get()); break;
      case Encoder::yellow: props.stereo_balance.step(ev.steps); break;
      case Encoder::red: props.stereo_routing.step(ev.steps); break;
    }
  }

  core::ui::ScreenAndInput External::screen()
  {
    return {*screen_, *this};
  }

} // namespace otto::engines::external