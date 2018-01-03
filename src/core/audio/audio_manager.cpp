#include "audio_manager.hpp"
#include "jack_audio_driver.hpp"
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
    };

    DebugInfo* pDebugInfo;
  } // namespace

  AudioManager& AudioManager::get()
  {
    static AudioManager* pInstance;

    if (!pInstance) {
      pInstance  = new AudioManager();
      pDebugInfo = new DebugInfo();
    }

    return *pInstance;
  }

  void AudioManager::init()
  {
    pre_init.fire();

    midi::generateFreqTable(440);
    AudioDriver::get().init();
  }

  void AudioManager::start()
  {
    _running = true;
  }

  void AudioManager::shutdown()
  {
    AudioDriver::get().shutdown();
  }

  bool AudioManager::running()
  {
    return _running;
  }

  void AudioManager::processAudioOutput(ProcessData<2> audio_output)
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
        pDebugInfo->buffers_lost++;
      }
      pDebugInfo->audio_graph.push(max / 2.f);
#endif
  }
} // namespace otto::audio
