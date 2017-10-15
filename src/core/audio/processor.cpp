#include "processor.hpp"

#include "core/globals.hpp"

namespace otto::audio {
namespace detail {

  void registerAudioBufferResize(std::function<void(int)> eventHandler) {
    Globals::events.bufferSizeChanged.add(eventHandler);
  }

} // detail
} // otto::audio
