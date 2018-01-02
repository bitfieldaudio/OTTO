#include "core/audio/faust.hpp"

#include "core/globals.hpp"
#include "core/audio/audio_manager.hpp"
#include <exception>

namespace otto::audio {

  namespace detail {
    void register_faust_wrapper_events(dsp& _dsp, FaustOptions& opts) {
      global::event::pre_init.add([&]() {
          _dsp.init(audio::AudioManager::get().samplerate);
          _dsp.buildUserInterface(&opts);
        });
      global::event::samplerate_change.add([&](int sr) {
          _dsp.instanceInit(sr);
          opts.props->updateFaust();
        });
    }
  }
} // otto::audio
