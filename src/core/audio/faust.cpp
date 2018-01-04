#include "core/audio/faust.hpp"

#include <exception>
#include "services/audio_manager.hpp"
#include "core/globals.hpp"

namespace otto::audio::detail {
  void register_faust_wrapper_events(dsp& _dsp, FaustOptions& opts)
  {
    audio::events::pre_init().subscribe([&]() {
      _dsp.init(audio::samplerate());
      _dsp.buildUserInterface(&opts);
    });

    audio::events::samplerate_change().subscribe([&](int samplerate) {
      _dsp.instanceInit(samplerate);
      opts.props->updateFaust();
    });
  }
} // namespace otto::audio::detail
