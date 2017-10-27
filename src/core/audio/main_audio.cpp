#include "main_audio.hpp"
#include "core/globals.hpp"
#include "util/algorithm.hpp"

namespace otto::audio {

  ProcessData<2> MainAudio::process(ProcessData<1> external_in)
  {
    using Selection = modules::InputSelector::Selection;

    // Main processor function
    auto midi_in = external_in.midi_only();
    auto playback_out = Globals::tapedeck.process_playback(midi_in);
    auto mixer_out = Globals::mixer.process_tracks(playback_out);

    auto record_in = [&] () {
      switch (Globals::selector.props.input.get()) {
      case Selection::Internal:
      {
        auto synth_out = Globals::synth.process(midi_in);
        auto drums_out = Globals::drums.process(midi_in);
        for (auto&& [dst, src] : util::zip(drums_out, synth_out)) {
          util::audio::add_all(src, dst);
        }
        return Globals::effect.process(drums_out);
      }
      case Selection::External:
        return Globals::effect.process(external_in);
      case Selection::TrackFB:
        util::transform(playback_out, audiobuf1.begin(),
          [track = Globals::selector.props.track.get()] (auto&& a) {
            return std::array{a[track]};
          });
        return external_in.redirect(audiobuf1);
      case Selection::MasterFB:
        break;
      }
      return audio::ProcessData<1>{{nullptr},{nullptr}};
    }();

    if (Globals::selector.props.input != Selection::MasterFB) {
      Globals::mixer.process_engine(record_in);
    }

    // mixer_out = Globals::master_fx.process(mixer_out);

    if (Globals::selector.props.input == Selection::MasterFB) {
      util::transform(mixer_out, audiobuf1.begin(),
        [] (auto&& a) { return std::array{a[0] + a[1]}; });
      record_in = {{audiobuf1.data(), external_in.nframes}, external_in.midi};
    }

    Globals::tapedeck.process_record(record_in);

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
