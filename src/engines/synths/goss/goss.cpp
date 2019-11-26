#include "goss.hpp"

#include "audio.hpp"
#include "screen.hpp"
#include "services/audio_manager.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines::goss {

  using namespace core::input;

  GossEngine::GossEngine()
    : screen(std::make_unique<GossScreen>()), //
      audio(std::make_unique<Audio>()),
      graphics_sndr_(services::UIManager::current().make_sndr(*screen, env_screen_, voice_screen_)),
      audio_sndr_(services::AudioManager::current().make_sndr(*audio))
  {
    sndr_.push(Actions::rotation_variable::data(rotation_));
  }

  void GossEngine::encoder(EncoderEvent e)
  {
    switch (e.encoder) {
      case Encoder::blue: props.model.step(e.steps); break;
      case Encoder::green: break;
      case Encoder::yellow: props.click.step(e.steps); break;
      case Encoder::red: props.leslie.step(e.steps); break;
    }
  }

} // namespace otto::engines::goss
