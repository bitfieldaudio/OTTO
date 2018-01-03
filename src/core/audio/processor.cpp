#include "processor.hpp"

#include "core/audio/audio_manager.hpp"

namespace otto::audio::detail {
  void registerAudioBufferResize(std::function<void(int)> eventHandler)
  {
    AudioManager::get().buffersize_change.subscribe(eventHandler);
  }
} // namespace otto::audio::detail
