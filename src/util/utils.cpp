#include "utils.h"
#include "globals.h"

namespace detail {

void registerAudioBufferResize(std::function<void(uint)> eh) {
  GLOB.events.bufferSizeChanged.add(eh);
}
}
