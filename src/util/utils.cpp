#include "utils.h"
#include "globals.h"

namespace detail {

  template<typename Callable, typename>
  void registerAudioBufferResize(Callable) {
    GLOB.events.bufferSizeChanged.add(eh);
  }
}
