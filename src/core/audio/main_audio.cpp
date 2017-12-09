#include "main_audio.hpp"

#include "core/globals.hpp"
#include "engines/studio/input_selector/input_selector.hpp"
#include "util/algorithm.hpp"

namespace otto::audio {

  ProcessData<2> MainAudio::process(ProcessData<1> external_in)
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
        auto mtrnm_out = global::metronome.process(midi_in);
        for (auto && [ drm, snth, mtrn ] :
          util::zip(drums_out, synth_out, mtrnm_out)) {
          util::audio::add_all(drm, snth);
          util::audio::add_all(drm, mtrn);
        }
        return drums_out;
        //return global::effect->process(drums_out);
      }
      case Selection::External:
        return global::effect->process(external_in);
      case Selection::TrackFB:
        util::transform(playback_out, audiobuf1.begin(),
          [track = global::selector.props.track.get()](
            auto&& a) { return std::array<float, 1>{a[track]}; });
        return external_in.redirect(audiobuf1);
      case Selection::MasterFB:
        break;
      }
      return audio::ProcessData<1>{{nullptr}, {nullptr}};
    }();

    if (global::selector.props.input != Selection::MasterFB) {
      global::mixer.process_engine(record_in);
    }

    // mixer_out = Globals::master_fx.process(mixer_out);

    if (global::selector.props.input == Selection::MasterFB) {
      util::transform(mixer_out, audiobuf1.begin(),
        [](auto&& a) { return std::array<float, 1>{a[0] + a[1]}; });
      record_in = {{audiobuf1.data(), external_in.nframes}, external_in.midi};
    }

    global::tapedeck.process_record(record_in);

    IF_DEBUG({
      float max;
      for (auto& frm : mixer_out) {
        float sum = frm[0] + frm[1];
        if (std::abs(sum - max) > 0) {
          max = sum;
        }
      }
      if (max == 0) {
        dbg_info.buffers_lost++;
      }
      dbg_info.audio_graph.push(max / 2.f);
    });

    return mixer_out;
  }

  void MainAudio::DbgInfo::draw()
  {
    ImGui::Begin("Audio");
    audio_graph.plot("Audio graph", -1, 1);
    ImGui::Text("Buffers lost: %d", buffers_lost);
    ImGui::End();
  }
}
