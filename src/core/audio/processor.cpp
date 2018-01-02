#include "processor.hpp"

#include "services/event_manager.hpp"

namespace otto::audio::detail {
  void registerAudioBufferResize(std::function<void(int)> eventHandler)
  {
    services::EventManager::get().buffersize_change.add(eventHandler);
  }
} // namespace otto::audio::detail
