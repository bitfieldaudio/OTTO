#include "chorus.hpp"

#include "services/audio_manager.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines::chorus {

  Chorus::Chorus() : audio(std::make_unique<Audio>(shared_phase_)), screen_(std::make_unique<Screen>(shared_phase_)), props{{*audio, *screen_}}
  {
  }

  using namespace core::input;

  void Chorus::encoder(EncoderEvent ev)
  {
    switch (ev.encoder) {
      case Encoder::blue: props.delay.step(ev.steps); break;
      case Encoder::green: props.rate.step(ev.steps); break;
      case Encoder::yellow: props.feedback.step(ev.steps); break;
      case Encoder::red: props.depth.step(ev.steps); break;
    }
  }

  core::ui::ScreenAndInput Chorus::screen()
  {
    return {*screen_, *this};
  }

} // namespace otto::engines::chorus
