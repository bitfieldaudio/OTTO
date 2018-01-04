#include "audio_manager.hpp"
#include "audio/jack_audio_driver.hpp"
#include "util/algorithm.hpp"

namespace otto::audio {
  using AudioDriver = JackAudioDriver;

  namespace {
    struct DebugInfo : debug::Info {
      debug::graph<1 << 10> audio_graph;
      int buffers_lost = 0;
      int lost_pos     = 0;

      void draw() override
      {
        ImGui::Begin("Audio");
        audio_graph.plot("Audio graph", -1, 1);
        ImGui::Text("Buffers lost: %d", buffers_lost);
        ImGui::End();
      }
    } debugInfo;

    std::atomic_bool _running {false};
  } // namespace

  namespace events {
    util::Event<>& pre_init() {
      static util::Event<> instance;
      return instance;
    }

    util::Event<unsigned>& buffersize_change() {
      static util::Event<unsigned> instance;
      return instance;
    }

    util::Event<unsigned>& samplerate_change() {
      static util::Event<unsigned> instance;
      return instance;
    }
  }

  int samplerate() noexcept {
    return AudioDriver::get().samplerate;
  }

  void init()
  {
    events::pre_init().fire();

    midi::generateFreqTable(440);
    AudioDriver::get().init();
  }

  void start() noexcept
  {
    _running = true;
  }

  void shutdown()
  {
    AudioDriver::get().shutdown();
  }

  bool running() noexcept
  {
    return _running;
  }

  void process_audio_output(ProcessData<2> audio_output)
  {
#if OTTO_DEBUG_UI
      float max;
      for (auto& frm : audio_output) {
        float sum = frm[0] + frm[1];
        if (std::abs(sum - max) > 0) {
          max = sum;
        }
      }
      if (max == 0) {
        debugInfo.buffers_lost++;
      }
      
      debugInfo.audio_graph.push(max / 2.f);
#endif
  }
} // namespace otto::audio
