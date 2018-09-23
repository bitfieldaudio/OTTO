#include "engines.hpp"

#include <map>

#include "core/globals.hpp"

#include "engines/seq/euclid/euclid.hpp"
#include "engines/synths/nuke/nuke.hpp"
#include "engines/fx/wormhole/wormhole.hpp"
#include "engines/misc/master/master.hpp"
#include "engines/synths/external/external.hpp"

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

    otto::engines::Master master;
  } // namespace

  void init()
  {
    engineGetters.try_emplace("Synth", [&]() { return dynamic_cast<AnyEngine*>(&*synth); });
    engineGetters.try_emplace("Effect", [&]() { return dynamic_cast<AnyEngine*>(&*effect); });
    engineGetters.try_emplace("Sequencer", [&]() { return dynamic_cast<AnyEngine*>(&*sequencer); });

    register_engine<otto::engines::Euclid>();
    register_engine<otto::engines::NukeSynth>();
    register_engine<otto::engines::Wormhole>();
    register_engine<otto::engines::External>();

    sequencer.init();
    synth.init();
    effect.init();

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

    service::ui::register_key_handler(core::ui::Key::voices, [](core::ui::Key k) {
      auto* owner = dynamic_cast<core::engines::EngineWithEnvelope*>(&synth.current());
      if (owner) {
        service::ui::display(owner->voices_screen());
      }
    });

    service::ui::register_key_handler(core::ui::Key::fx1, [](core::ui::Key k) {
      if (service::ui::is_pressed(core::ui::Key::shift)) {
        service::ui::display(effect.selector_screen());
      } else {
        service::ui::select_engine("Effect");
      }
    });

    static core::ui::Screen* master_last_screen = nullptr;

    service::ui::register_key_handler(core::ui::Key::master, [](core::ui::Key k) {
      master_last_screen = service::ui::current_screen();
      service::ui::display(master.screen());
    }, [] (core::ui::Key k) {
      if (master_last_screen) service::ui::display(*master_last_screen);
    });

    auto load = [&](nlohmann::json& data) {
      synth.from_json(data["Synth"]);
      effect.from_json(data["Effect"]);
      sequencer.from_json(data["Sequencer"]);
    };

    auto save = [&] {
      return nlohmann::json({{"Synth", synth.to_json()},
                             {"Effect", effect.to_json()},
                             {"Sequencer", sequencer.to_json()}});
    };

    service::state::attach("Engines", load, save);
  }

  void start()
  {
    sequencer.select(std::size_t(0));
    synth.select(std::size_t(0));
    effect.select(std::size_t(0));
  }

  void shutdown() {}

  core::audio::ProcessData<2> process(core::audio::ProcessData<1> external_in)
  {
    // Main processor function
    auto midi_in = external_in.midi_only();
    auto seq_out = sequencer->process(midi_in);
    auto synth_out = synth->process({external_in.audio, seq_out.midi, external_in.nframes});

    for (auto&& [snth, out] : util::zip(synth_out, audio_out)) {
      out[0] = snth[0];
      out[1] = snth[0];
    }
    auto fx_out = effect->process(synth_out.redirect(audio_out));

    return master.process(fx_out);;
  }

  AnyEngine* const by_name(const std::string& name) noexcept
  {
    auto getter = engineGetters.find(name);
    if (getter == engineGetters.end()) return nullptr;

    return getter->second();
  }

} // namespace otto::service::engines
