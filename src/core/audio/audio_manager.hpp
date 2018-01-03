#pragma once

#include <memory>
#include <atomic>

#include "core/audio/processor.hpp"
#include "debug/ui.hpp"
#include "util/event.hpp"

namespace otto::audio {
  /// Class that interacts with OS audio/midi framework, and delegates
  /// processing to the engines.
  struct AudioManager {
    static AudioManager& get();

    std::atomic_int samplerate;

    void processAudioOutput(ProcessData<2> audio_output);
  
    void init();
    void start();
    void shutdown();

    bool running();

    util::Event<> pre_init;
    util::Event<unsigned> buffersize_change;
    util::Event<unsigned> samplerate_change;

  private:
    AudioManager() = default;
    ~AudioManager() = default;

    std::atomic_bool _running {false};
  };
}
