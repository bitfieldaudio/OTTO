#include "processor.hpp"

#include "services/audio.hpp"

namespace otto::core::audio::detail {
  void registerAudioBufferResize(std::function<void(int)> eventHandler)
  {
    service::audio::events::buffersize_change().subscribe(eventHandler);
  }
} // namespace otto::core::audio::detail
