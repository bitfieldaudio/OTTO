#include "core/audio/faust.hpp"

#include <exception>
#include "services/audio.hpp"
#include "core/globals.hpp"

namespace otto::core::audio::detail {
  void register_faust_wrapper_events(dsp& _dsp, FaustOptions& opts)
  {
    service::audio::events::pre_init().subscribe([&]() {
        _dsp.init(service::audio::samplerate());
      _dsp.buildUserInterface(&opts);
    });

    service::audio::events::samplerate_change().subscribe([&](int samplerate) {
      _dsp.instanceInit(samplerate);
      opts.props->updateFaust();
    });
  }
} // namespace otto::core::audio::detail
