#include "core/audio/faust.hpp"

#include "core/globals.hpp"
#include <exception>

namespace top1::audio {

  namespace detail {
    void register_faust_wrapper_events(dsp& _dsp, FaustOptions& opts) {
      Globals::events.preInit.add([&]() {
          _dsp.init(Globals::samplerate);
          _dsp.buildUserInterface(&opts);
        });
      Globals::events.samplerateChanged.add([&](int sr) {
          _dsp.instanceInit(sr);
          opts.props->updateFaust();
        });
    }
  }
} // top1::audio
