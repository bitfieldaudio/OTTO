#include "engines.hpp"

#include <map>

#include "core/globals.hpp"

#include "engines/synths/nuke/nuke.hpp"
#include "engines/seq/euclid/euclid.hpp"

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
    core::audio::ProcessBuffer<2> audio_out;

    EngineDispatcher<EngineType::sequencer> sequencer;
    EngineDispatcher<EngineType::synth> synth;
    EngineDispatcher<EngineType::effect> effect;

    SynthOrDrums current_sound_source = SynthOrDrums::synth;
  } // namespace

  void init()
  {
    engineGetters.try_emplace("Synth", [&]() { return (AnyEngine*) &*synth; });

    register_engine<otto::engines::NukeSynth>();
    register_engine<otto::engines::Euclid>();

    synth.init();
    sequencer.init();
    sequencer.select(std::size_t(0));

    service::ui::register_key_handler(core::ui::Key::sequencer, [](core::ui::Key k) {
      if (service::ui::is_pressed(core::ui::Key::shift)) {
        service::ui::display(sequencer.selector_screen());
      } else {
        service::ui::select_engine("Sequencer");
      }
      service::ui::display(sequencer->screen());
    });

    service::ui::register_key_handler(core::ui::Key::synth, [](core::ui::Key k) {
      if (service::ui::is_pressed(core::ui::Key::shift)) {
        service::ui::display(synth.selector_screen());
      } else {
        service::ui::select_engine("Synth");
      }
      current_sound_source = SynthOrDrums::synth;
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

    auto load = [&](nlohmann::json& data) {
      synth.from_json(data["Synth"]);
      sequencer.from_json(data["Sequencer"]);
      from_json(data["CurrentSoundSource"], current_sound_source);
    };

    auto save = [&] {
      return nlohmann::json({{"Synth", synth.to_json()},
                             {"Sequencer", sequencer.to_json()},
                             {"CurrentSoundSource", to_json(current_sound_source)}});
    };

    service::state::attach("Engines", load, save);
  }

  void start()
  {
    synth.select(std::size_t(0));
  }

  void shutdown()
  {
  }

  core::audio::ProcessData<2> process(core::audio::ProcessData<1> external_in)
  {
    // Main processor function
    auto midi_in      = external_in.midi_only();
    auto seq_out = sequencer->process(midi_in);
    auto synth_out = synth->process(seq_out);

    for (auto&& [snth, out] : util::zip(synth_out, audio_out)) {
      out[0] = snth[0];
      out[1] = snth[0];
    }
    return midi_in.redirect(audio_out);
  }

  AnyEngine* const by_name(const std::string& name) noexcept
  {
    auto getter = engineGetters.find(name);
    if (getter == engineGetters.end()) return nullptr;

    return getter->second();
  }

} // namespace otto::engines
