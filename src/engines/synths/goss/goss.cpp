#include "goss.hpp"

#include "screen.hpp"
#include "audio.hpp"

#include "services/audio_manager.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines::goss {

  GossEngine::GossEngine()
    : screen(std::make_unique<GossScreen>()), //
      audio(std::make_unique<Audio>()),
      graphics_sndr_(services::UIManager::current().make_sndr(*screen)),
      audio_sndr_(services::AudioManager::current().make_sndr(*audio))
  {
    sndr_.push(Actions::rotation_variable::data(rotation_));
  }

} // namespace otto::engines::goss
