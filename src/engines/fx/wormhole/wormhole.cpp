#include "wormhole.hpp"

#include "audio.hpp"
#include "screen.hpp"
#include "services/audio_manager.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines::wormhole {

  Wormhole::Wormhole()
    : screen(std::make_unique<Screen>()), //
      audio(std::make_unique<Audio>()),
      graphics_sndr_(services::UIManager::current().make_sndr(*screen)),
      audio_sndr_(services::AudioManager::current().make_sndr(*audio))
  {}

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

} // namespace otto::engines::wormhole
