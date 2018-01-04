#include "processor.hpp"

#include "services/audio_manager.hpp"

namespace otto::audio::detail {
  void registerAudioBufferResize(std::function<void(int)> eventHandler)
  {
    audio::events::buffersize_change().subscribe(eventHandler);
  }
} // namespace otto::audio::detail
