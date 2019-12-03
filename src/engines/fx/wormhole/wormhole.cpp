#include "wormhole.hpp"

#include "audio.hpp"
#include "screen.hpp"

namespace otto::engines::wormhole {

  Wormhole::Wormhole() : audio(std::make_unique<Audio>()), screen_(std::make_unique<Screen>()), props{{*audio, *screen_}} {}

  using namespace core::input;

  void Wormhole::encoder(EncoderEvent ev)
  {
    switch (ev.encoder) {
      case Encoder::blue: props.filter.step(ev.steps); break;
      case Encoder::green: props.length.step(ev.steps); break;
      case Encoder::yellow: props.shimmer.step(ev.steps); break;
      case Encoder::red: props.damping.step(ev.steps); break;
    }
  }

  core::ui::ScreenAndInput Wormhole::screen()
  {
    return {*screen_, *this};
  }

} // namespace otto::engines::wormhole
