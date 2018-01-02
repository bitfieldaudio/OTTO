#include "audio_manager.hpp"
#include "core/globals.hpp"
#include "engines/studio/input_selector/input_selector.hpp"
#include "util/algorithm.hpp"
#include "jack_audio_driver.hpp"

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

  void AudioManager::init() {
    AudioDriver::get().init();
  }

  void AudioManager::start() {
    _running = true;
  }

  void AudioManager::shutdown() {
    AudioDriver::get().shutdown();
  }

  bool AudioManager::running()
  {
    return _running;
  }

  ProcessData<2> AudioManager::process(ProcessData<1> external_in)
  {
    using Selection = engines::InputSelector::Selection;

    // Main processor function
    auto midi_in      = external_in.midi_only();
    auto playback_out = global::tapedeck.process_playback(midi_in);
    auto mixer_out    = global::mixer.process_tracks(playback_out);

    auto record_in = [&]() {
      switch (global::selector.props.input.get()) {
      case Selection::Internal: {
        auto synth_out = global::synth->process(midi_in);
        auto drums_out = global::drums->process(midi_in);
        for (auto && [ drm, snth ] : util::zip(drums_out, synth_out)) {
          util::audio::add_all(drm, snth);
        }
        return drums_out;
      }
      case Selection::External: return global::effect->process(external_in);
      case Selection::TrackFB:
        util::transform(playback_out, _audiobuf1.begin(),
                        [track = global::selector.props.track.get()](auto&& a) {
                          return std::array<float, 1>{a[track]};
                        });
        return external_in.redirect(_audiobuf1);
      case Selection::MasterFB: break;
      }
      return audio::ProcessData<1>{{nullptr}, {nullptr}};
    }();

    if (global::selector.props.input != Selection::MasterFB) {
      global::mixer.process_engine(record_in);
    }

    if (global::selector.props.input == Selection::MasterFB) {
      util::transform(mixer_out, _audiobuf1.begin(), [](auto&& a) {
        return std::array<float, 1>{a[0] + a[1]};
      });
      record_in = {{_audiobuf1.data(), external_in.nframes}, external_in.midi};
    }

    global::tapedeck.process_record(record_in);

    auto mtrnm_out = global::metronome.process(midi_in);

    for (auto && [ mix, mtrn ] : util::zip(mixer_out, mtrnm_out)) {
      util::audio::add_all(mix, mtrn);
    }

#if OTTO_DEBUG_UI
    {
      float max;
      for (auto& frm : mixer_out) {
        float sum = frm[0] + frm[1];
        if (std::abs(sum - max) > 0) {
          max = sum;
        }
      }
      if (max == 0) {
        pDebugInfo->buffers_lost++;
      }
      pDebugInfo->audio_graph.push(max / 2.f);
    }
#endif

    return mixer_out;
  }
} // namespace otto::audio
