#include "processor.hpp"

#include "core/globals.hpp"

namespace otto::audio {
namespace detail {

  void registerAudioBufferResize(std::function<void(int)> eventHandler) {
    global::event::buffersize_change.add(eventHandler);
  }

} // detail
} // otto::audio
