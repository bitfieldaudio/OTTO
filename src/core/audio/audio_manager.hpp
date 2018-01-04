#pragma once

#include <memory>
#include <atomic>

#include "core/audio/processor.hpp"
#include "debug/ui.hpp"
#include "util/event.hpp"

namespace otto::audio {
  namespace events {
    util::Event<>& pre_init();
    util::Event<unsigned>& buffersize_change();
    util::Event<unsigned>& samplerate_change();
  }

  int samplerate();

  void processAudioOutput(ProcessData<2> audio_output);
  
  void init();
  void start();
  void shutdown();

  bool running();
}
