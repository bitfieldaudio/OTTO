#include "core/audio/faust.hpp"

#include <exception>
#include "services/audio_manager.hpp"

namespace otto::core::audio::detail {
  void register_faust_wrapper_events(dsp& _dsp, FaustOptions& opts)
  {
    Application::current().events.post_init.subscribe([&]() {
      _dsp.init(Application::current().audio_manager->samplerate());
      _dsp.buildUserInterface(&opts);
      opts.client.refresh_links();
    });
  }
} // namespace otto::core::audio::detail
