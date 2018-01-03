#include "core/audio/faust.hpp"

#include <exception>
#include "core/audio/audio_manager.hpp"
#include "core/globals.hpp"

namespace otto::audio::detail {
  void register_faust_wrapper_events(dsp& _dsp, FaustOptions& opts)
  {
    auto& audioManager = audio::AudioManager::get();

    audioManager.pre_init.subscribe([&]() {
      _dsp.init(audioManager.samplerate);
      _dsp.buildUserInterface(&opts);
    });

    audioManager.samplerate_change.subscribe([&](int sr) {
      _dsp.instanceInit(sr);
      opts.props->updateFaust();
    });
  }
} // namespace otto::audio::detail
