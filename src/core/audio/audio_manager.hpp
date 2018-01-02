#pragma once

#include <memory>
#include <atomic>

#include "core/audio/processor.hpp"
#include "debug/ui.hpp"

namespace otto::audio {
  /// Class that interacts with OS audio/midi framework, and delegates
  /// processing to the engines.
  struct AudioManager {
    static AudioManager& get();

    std::atomic_int samplerate;

    // Input channel is external audio in. Also should hold MIDI from system
    ProcessData<2> process(ProcessData<1>);

    void init();
    void start();
    void shutdown();

    bool running();

  private:
    AudioManager() = default;
    ~AudioManager() = default;

    ProcessBuffer<1> _audiobuf1;
    std::atomic_bool _running {false};
  };
}
