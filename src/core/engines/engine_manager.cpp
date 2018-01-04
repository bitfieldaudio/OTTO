#include "engine_manager.hpp"

#include "core/ui/mainui.hpp"
#include "engines/drums/drum-sampler/drum-sampler.hpp"
#include "engines/drums/simple-drums/simple-drums.hpp"
#include "engines/synths/nuke/nuke.hpp"
#include "services/state.hpp"

namespace otto::engines {
  namespace {
    std::map<std::string, std::function<AnyEngine*()>> engineGetters;
    audio::ProcessBuffer<1> _audiobuf1;

    EngineDispatcher<engines::EngineType::synth> synth;
    EngineDispatcher<engines::EngineType::drums> drums;
    EngineDispatcher<engines::EngineType::effect> effect;
    Tapedeck tapedeck;
    Mixer mixer;
    Metronome metronome;
    InputSelector selector;
  } // namespace

  void init()
  {
    engineGetters = {{"TapeDeck", [&]() { return (AnyEngine*) &tapedeck; }},
                     {"Mixer", [&]() { return (AnyEngine*) &mixer; }},
                     {"Synth", [&]() { return (AnyEngine*) &*synth; }},
                     {"Drums", [&]() { return (AnyEngine*) &*drums; }},
                     {"Metronome", [&]() { return (AnyEngine*) &metronome; }}};

    register_engine<DrumSampler>();
    register_engine<SimpleDrumsEngine>();
    register_engine<NukeSynth>();

    synth.init();
    drums.init();

    ui::registerKeyHandler(ui::Key::play, [](ui::Key key) {
      if (tapedeck.state.playing()) {
        tapedeck.state.stop();
      } else {
        tapedeck.state.play();
      }
    });

    auto load = [&](nlohmann::json& data) {
      from_json(data["TapeDeck"], tapedeck);
      from_json(data["Mixer"], mixer);
      from_json(data["Synth"], synth);
      from_json(data["Drums"], drums);
      from_json(data["Metronome"], metronome);
    };

    auto save = [&]() {
      return nlohmann::json({{"TapeDeck", tapedeck},
                             {"Mixer", mixer},
                             {"Synth", synth},
                             {"Drums", drums},
                             {"Metronome", metronome}});
    };

    services::state::attach("Engines", load, save);
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

  audio::ProcessData<2> processAudio(
    audio::ProcessData<1> external_in)
  {
    using Selection = InputSelector::Selection;

    // Main processor function
    auto midi_in      = external_in.midi_only();
    auto playback_out = tapedeck.process_playback(midi_in);
    auto mixer_out    = mixer.process_tracks(playback_out);

    auto record_in = [&]() {
      switch (selector.props.input.get()) {
      case Selection::Internal: {
        auto synth_out = synth->process(midi_in);
        auto drums_out = drums->process(midi_in);
        for (auto && [ drm, snth ] : util::zip(drums_out, synth_out)) {
          util::audio::add_all(drm, snth);
        }
        return drums_out;
      }
      case Selection::External: return effect->process(external_in);
      case Selection::TrackFB:
        util::transform(
          playback_out,
          _audiobuf1.begin(), [track = selector.props.track.get()](auto&& a) {
            return std::array<float, 1>{a[track]};
          });
        return external_in.redirect(_audiobuf1);
      case Selection::MasterFB: break;
      }
      return audio::ProcessData<1>{{nullptr}, {nullptr}};
    }();

    if (selector.props.input != Selection::MasterFB) {
      mixer.process_engine(record_in);
    }

    if (selector.props.input == Selection::MasterFB) {
      util::transform(mixer_out, _audiobuf1.begin(), [](auto&& a) {
        return std::array<float, 1>{a[0] + a[1]};
      });
      record_in = {{_audiobuf1.data(), external_in.nframes}, external_in.midi};
    }

    tapedeck.process_record(record_in);

    auto mtrnm_out = metronome.process(midi_in);

    for (auto && [ mix, mtrn ] : util::zip(mixer_out, mtrnm_out)) {
      util::audio::add_all(mix, mtrn);
    }

    return mixer_out;
  }

  AnyEngine* getEngineByName(const std::string& name)
  {
    auto getter = engineGetters[name];
    if (!getter) {
      return nullptr;
    }

    return getter();
  }

  namespace tapeState {
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
  } // namespace tapeState

  namespace metronomeState {
    TapeTime getBarTime(BeatPos bar) {
      return metronome.getBarTime(bar);
    }

    TapeTime getBarTimeRel(BeatPos bar) {
      return metronome.getBarTimeRel(bar);
    }

    float bar_for_time(std::size_t time) {
      return metronome.bar_for_time(time);
    }

    std::size_t time_for_bar(float bar) {
      return metronome.time_for_bar(bar);
    }
  }
} // namespace otto::engines