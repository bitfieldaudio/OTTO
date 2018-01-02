#include "core/audio/faust.hpp"

#include <exception>
#include "core/audio/audio_manager.hpp"
#include "services/event_manager.hpp"
#include "core/globals.hpp"

namespace otto::audio::detail {
  void register_faust_wrapper_events(dsp& _dsp, FaustOptions& opts)
  {
    services::EventManager::get().pre_init.add([&]() {
      _dsp.init(audio::AudioManager::get().samplerate);
      _dsp.buildUserInterface(&opts);
    });

    services::EventManager::get().samplerate_change.add([&](int sr) {
      _dsp.instanceInit(sr);
      opts.props->updateFaust();
    });
  }
} // namespace otto::audio::detail
