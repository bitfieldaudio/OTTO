#include "engines.hpp"

#include <map>

#include "core/globals.hpp"

#include "engines/drums/drum-sampler/drum-sampler.hpp"
#include "engines/drums/simple-drums/simple-drums.hpp"
#include "engines/studio/input_selector/input_selector.hpp"
#include "engines/studio/metronome/metronome.hpp"
#include "engines/studio/mixer/mixer.hpp"
#include "engines/studio/tapedeck/tapedeck.hpp"
#include "engines/synths/nuke/nuke.hpp"

#include "services/state.hpp"
#include "services/ui.hpp"

namespace otto::service::engines {

  using namespace core::engines;

  enum struct SynthOrDrums { synth, drums };

  nlohmann::json to_json(SynthOrDrums sod)
  {
    return sod == SynthOrDrums::synth ? "Synth" : "Drums";
  }

  void from_json(const nlohmann::json& js, SynthOrDrums& sod)
  {
    if (js == "Synth") {
      sod = SynthOrDrums::synth;
    } else if (js == "Drums") {
      sod = SynthOrDrums::drums;
    }
  }

  namespace {
    std::map<std::string, std::function<AnyEngine*()>> engineGetters;
    core::audio::ProcessBuffer<1> _audiobuf1;

    EngineDispatcher<EngineType::synth> synth;
    EngineDispatcher<EngineType::drums> drums;
    EngineDispatcher<EngineType::effect> effect;
    otto::engines::Mixer mixer;
    otto::engines::Tapedeck tapedeck;
    otto::engines::Metronome metronome;
    otto::engines::InputSelector selector;

    SynthOrDrums current_sound_source = SynthOrDrums::synth;
  } // namespace

  void init()
  {
    engineGetters = {{"TapeDeck", [&]() { return (AnyEngine*) &tapedeck; }},
                     {"Mixer", [&]() { return (AnyEngine*) &mixer; }},
                     {"Synth", [&]() { return (AnyEngine*) &*synth; }},
                     {"Drums", [&]() { return (AnyEngine*) &*drums; }},
                     {"Metronome", [&]() { return (AnyEngine*) &metronome; }}};

    register_engine<otto::engines::DrumSampler>();
    register_engine<otto::engines::SimpleDrumsEngine>();
    register_engine<otto::engines::NukeSynth>();

    synth.init();
    drums.init();

    service::ui::register_key_handler(core::ui::Key::tape,
                             [](core::ui::Key k) { service::ui::select_engine(tapedeck); });
    service::ui::register_key_handler(core::ui::Key::mixer,
                             [](core::ui::Key k) { service::ui::select_engine(mixer); });
    service::ui::register_key_handler(core::ui::Key::metronome,
                             [](core::ui::Key k) { service::ui::select_engine(metronome); });
    service::ui::register_key_handler(core::ui::Key::synth, [](core::ui::Key k) {
      if (service::ui::is_pressed(core::ui::Key::shift)) {
        service::ui::display(synth.selector_screen());
      } else {
        service::ui::select_engine("Synth");
      }
      current_sound_source = SynthOrDrums::synth;
    });
    service::ui::register_key_handler(core::ui::Key::drums, [](core::ui::Key k) {
      if (service::ui::is_pressed(core::ui::Key::shift)) {
        service::ui::display(drums.selector_screen());
      } else {
        service::ui::select_engine("Drums");
      }
      current_sound_source = SynthOrDrums::drums;
    });

    service::ui::register_key_handler(core::ui::Key::envelope, [](core::ui::Key k) {
        auto* engine = by_name(service::ui::selected_engine_name());
        auto* owner = dynamic_cast<core::engines::EngineWithEnvelope*>(engine);
        if (owner) {
          if (service::ui::is_pressed(core::ui::Key::shift)) {
            service::ui::display(owner->voices_screen());
          } else {
            service::ui::display(owner->envelope_screen());
          }
        }
    });

    service::ui::register_key_handler(core::ui::Key::play, [](core::ui::Key key) {
      if (tapedeck.state.playing()) {
        tapedeck.state.stop();
      } else {
        tapedeck.state.play();
      }
    });


    auto load = [&](nlohmann::json& data) {
      tapedeck.from_json(data["TapeDeck"]);
      mixer.from_json(data["Mixer"]);
      synth.from_json(data["Synth"]);
      drums.from_json(data["Drums"]);
      metronome.from_json(data["Metronome"]);
      from_json(data["CurrentSoundSource"], current_sound_source);
    };

    auto save = [&] {
      return nlohmann::json({{"TapeDeck", tapedeck.to_json()},
                             {"Mixer", mixer.to_json()},
                             {"Synth", synth.to_json()},
                             {"Drums", drums.to_json()},
                             {"Metronome", metronome.to_json()},
                             {"CurrentSoundSource", to_json(current_sound_source)}});
    };

    service::state::attach("Engines", load, save);
  }

  void start()
  {
    tapedeck.on_enable();
    metronome.on_enable();
    mixer.on_enable();
    synth.select(std::size_t(0));
    drums.select(std::size_t(0));
  }

  void shutdown()
  {
    mixer.on_disable();
    tapedeck.on_disable();
  }

  core::audio::ProcessData<2> process(core::audio::ProcessData<1> external_in)
  {
    using Selection = otto::engines::InputSelector::Selection;

    // Main processor function
    auto midi_in      = external_in.midi_only();
    auto playback_out = tapedeck.process_playback(midi_in);
    auto mixer_out    = mixer.process_tracks(playback_out);

    auto record_in = [&]() {
      switch (Selection{selector.props.input.get()}) {
      case Selection::Internal: {
        if (current_sound_source == SynthOrDrums::synth) {
          return synth->process(midi_in);
        } else {
          return drums->process(midi_in);
        }
      }
      case Selection::External: return effect->process(external_in);
      case Selection::TrackFB:
        util::transform(playback_out, _audiobuf1.begin(),
                        [track = selector.props.track.get()](auto&& a) {
                          return std::array<float, 1>{{a[track]}};
                        });
        return external_in.redirect(_audiobuf1);
      case Selection::MasterFB: break;
      }
      return core::audio::ProcessData<1>{{nullptr}, {nullptr}};
    }();

    for (auto& frm : record_in) {
      for (auto& smpl : frm) {
        smpl *= tapedeck.props.gain;
      }
    }

    if (Selection{selector.props.input.get()} != Selection::MasterFB) {
      mixer.process_engine(record_in);
    }

    if (Selection{selector.props.input.get()} == Selection::MasterFB) {
      util::transform(mixer_out, _audiobuf1.begin(), [](auto&& a) {
          return std::array<float, 1>{{a[0] + a[1]}};
      });
      record_in = {{_audiobuf1.data(), external_in.nframes}, external_in.midi};
    }

    tapedeck.process_record(record_in);

    auto mtrnm_out = metronome.process(midi_in);

    for (auto&& [mix, mtrn] : util::zip(mixer_out, mtrnm_out)) {
      util::audio::add_all(mix, mtrn);
    }

    return mixer_out;
  }

  AnyEngine* const by_name(const std::string& name) noexcept
  {
    auto getter = engineGetters.find(name);
    if (getter == engineGetters.end()) return nullptr;

    return getter->second();
  }

  namespace tape_state {
    int position()
    {
      return tapedeck.position();
    }

    float playSpeed()
    {
      return tapedeck.state.playSpeed;
    }

    bool playing()
    {
      return tapedeck.state.playing();
    }
  } // namespace tape_state

  namespace metronome_state {
    TapeTime bar_time(BeatPos bar)
    {
      return metronome.getBarTime(bar);
    }

    TapeTime bar_time_rel(BeatPos bar)
    {
      return metronome.getBarTimeRel(bar);
    }

    float bar_for_time(std::size_t time)
    {
      return metronome.bar_for_time(time);
    }

    std::size_t time_for_bar(float bar)
    {
      return metronome.time_for_bar(bar);
    }
  } // namespace metronome_state
} // namespace otto::engines
