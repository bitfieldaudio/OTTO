#pragma once

#include <memory>
#include <atomic>

#include "core/audio/processor.hpp"
#include "debug/ui.hpp"

namespace top1::audio {

  /// Class that interacts with OS audio/midi framework, and delegates
  /// processing to the modules.
  class MainAudio {

    // PIMPL - define in individual implementation files
    class Impl;
    std::unique_ptr<Impl> impl;
    std::atomic_bool do_process {false};

    struct DbgInfo : debug::Info {
      util::ringbuffer<float, 1 << 12> audio_graph;

      void draw() override;
    };

    IF_DEBUG(DbgInfo dbg_info);

  public:

    // A unique_ptr pimpl requires externally defined ctors and dtors
    MainAudio();
    ~MainAudio();

    // Input channel is external audio in. Also should hold MIDI from system
    ProcessData<2> process(ProcessData<1>);

    void init();
    void exit();
    void start_processing() { do_process = true; }

  private:
    ProcessBuffer<1> audiobuf1;
  };
}
