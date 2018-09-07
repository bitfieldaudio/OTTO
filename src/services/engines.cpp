#include "engines.hpp"

#include <map>

#include "core/globals.hpp"

#include "engines/seq/euclid/euclid.hpp"
#include "engines/synths/nuke/nuke.hpp"

#include "services/state.hpp"
#include "services/ui.hpp"

namespace otto::service::engines {

  using namespace core::engines;

  namespace {
    std::map<std::string, std::function<AnyEngine*()>> engineGetters;
    core::audio::ProcessBuffer<2> audio_out;

    EngineDispatcher<EngineType::sequencer> sequencer;
    EngineDispatcher<EngineType::synth> synth;
    EngineDispatcher<EngineType::effect> effect;
  } // namespace

  void init()
  {
    engineGetters.try_emplace("Synth", [&]() { return dynamic_cast<AnyEngine*>(&*synth); });
    engineGetters.try_emplace("Sequencer", [&]() { return dynamic_cast<AnyEngine*>(&*sequencer); });

    register_engine<otto::engines::NukeSynth>();
    register_engine<otto::engines::Euclid>();

    synth.init();
    sequencer.init();

    service::ui::register_key_handler(core::ui::Key::sequencer, [](core::ui::Key k) {
      if (service::ui::is_pressed(core::ui::Key::shift)) {
        service::ui::display(sequencer.selector_screen());
      } else {
        service::ui::select_engine("Sequencer");
        service::ui::display(sequencer->screen());
      }
    });

    service::ui::register_key_handler(core::ui::Key::synth, [](core::ui::Key k) {
      if (service::ui::is_pressed(core::ui::Key::shift)) {
        service::ui::display(synth.selector_screen());
      } else {
        service::ui::select_engine("Synth");
      }
    });

    service::ui::register_key_handler(core::ui::Key::envelope, [](core::ui::Key k) {
      auto* owner = dynamic_cast<core::engines::EngineWithEnvelope*>(&synth.current());
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
    };

    auto save = [&] {
      return nlohmann::json({{"Synth", synth.to_json()}, {"Sequencer", sequencer.to_json()}});
    };


    service::state::attach("Engines", load, save);
  }

  void start()
  {
    synth.select(std::size_t(0));
    sequencer.select(std::size_t(0));
  }

  void shutdown() {}

  core::audio::ProcessData<2> process(core::audio::ProcessData<1> external_in)
  {
    // Main processor function
    auto midi_in = external_in.midi_only();
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

} // namespace otto::service::engines
