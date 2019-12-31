#include "arp.hpp"

#include "audio.hpp"
#include "screen.hpp"
#include "services/audio_manager.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines::arp {

  using namespace core::input;

  Arp::Arp() : audio(std::make_unique<Audio>()), screen_(std::make_unique<Screen>())
  {
    props.sender.push(Actions::graphics_outdated::data(graphics_outdated_));
  }

  void Arp::encoder(EncoderEvent ev)
  {
    switch (ev.encoder) {
      case Encoder::blue: props.playmode.step(util::math::sgn(ev.steps)); break;
      case Encoder::green: props.octavemode.step(util::math::sgn(ev.steps)); break;
      case Encoder::yellow: props.subdivision.step(util::math::sgn(ev.steps)); break;
      case Encoder::red: props.note_length.step(ev.steps); break;
    }
  }

  core::ui::ScreenAndInput Arp::screen()
  {
    return {*screen_, *this};
  }

} // namespace otto::engines::arp
