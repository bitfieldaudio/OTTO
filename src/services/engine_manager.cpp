#include "engine_manager.hpp"

#include "engines/fx/wormhole/wormhole.hpp"
#include "engines/misc/master/master.hpp"
#include "engines/seq/arp/arp.hpp"
#include "engines/seq/euclid/euclid.hpp"
#include "engines/synths/DX7/dxotto.hpp"
#include "engines/synths/OTTOFM/ottofm.hpp"
#include "engines/synths/external/external.hpp"
#include "engines/synths/hammond/hammond.hpp"
#include "engines/synths/nuke/nuke.hpp"
#include "engines/synths/vocoder/vocoder.hpp"

#include "services/application.hpp"

namespace otto::services {

  using namespace core;
  using namespace core::engine;

  struct DefaultEngineManager final : EngineManager {
    DefaultEngineManager();

    void start() override;
    audio::ProcessData<2> process(audio::ProcessData<1> external_in) override;
    AnyEngine* by_name(const std::string& name) noexcept override;

  private:
    std::unordered_map<std::string, std::function<AnyEngine*()>> engineGetters;

    EngineDispatcher<EngineType::sequencer> sequencer;
    EngineDispatcher<EngineType::synth> synth;
    EngineDispatcher<EngineType::effect> effect;

    engines::Master master;
  };

  std::unique_ptr<EngineManager> EngineManager::create_default()
  {
    return std::make_unique<DefaultEngineManager>();
  }

  DefaultEngineManager::DefaultEngineManager()
  {
    auto& ui_manager = *Application::current().ui_manager;
    auto& state_manager = *Application::current().state_manager;

    engineGetters.try_emplace("Synth", [&]() { return dynamic_cast<AnyEngine*>(&*synth); });
    engineGetters.try_emplace("Effect", [&]() { return dynamic_cast<AnyEngine*>(&*effect); });
    engineGetters.try_emplace("Sequencer", [&]() { return dynamic_cast<AnyEngine*>(&*sequencer); });

    register_engine<engines::Arp>();
    register_engine<engines::DXOTTOSynth>();
    register_engine<engines::Euclid>();
    register_engine<engines::External>();
    register_engine<engines::HammondSynth>();
    register_engine<engines::NukeSynth>();
    register_engine<engines::OTTOFMSynth>();
    register_engine<engines::VocoderSynth>();
    register_engine<engines::Wormhole>();

    sequencer.init();
    synth.init();
    effect.init();

    ui_manager.register_key_handler(ui::Key::sequencer, [&](ui::Key k) {
      if (ui_manager.is_pressed(ui::Key::shift)) {
        ui_manager.display(sequencer.selector_screen());
      } else {
        ui_manager.select_engine("Sequencer");
        ui_manager.display(sequencer->screen());
      }
    });

    ui_manager.register_key_handler(ui::Key::synth, [&](ui::Key k) {
      if (ui_manager.is_pressed(ui::Key::shift)) {
        ui_manager.display(synth.selector_screen());
      } else {
        ui_manager.select_engine("Synth");
      }
    });

    ui_manager.register_key_handler(ui::Key::envelope, [&](ui::Key k) {
      auto* owner = dynamic_cast<engines::EngineWithEnvelope*>(&synth.current());
      if (owner) {
        if (ui_manager.is_pressed(ui::Key::shift)) {
          ui_manager.display(owner->voices_screen());
        } else {
          ui_manager.display(owner->envelope_screen());
        }
      }
    });

    ui_manager.register_key_handler(ui::Key::voices, [&](ui::Key k) {
      auto* owner = dynamic_cast<engines::EngineWithEnvelope*>(&synth.current());
      if (owner) {
        ui_manager.display(owner->voices_screen());
      }
    });

    ui_manager.register_key_handler(ui::Key::fx1, [&](ui::Key k) {
      if (ui_manager.is_pressed(ui::Key::shift)) {
        ui_manager.display(effect.selector_screen());
      } else {
        ui_manager.select_engine("Effect");
      }
    });

    static ui::Screen* master_last_screen = nullptr;

    ui_manager.register_key_handler(ui::Key::master,
                                    [&](ui::Key k) {
                                      master_last_screen = ui_manager.current_screen();
                                      ui_manager.display(master.screen());
                                    },
                                    [&](ui::Key k) {
                                      if (master_last_screen)
                                        ui_manager.display(*master_last_screen);
                                    });

    auto load = [&](nlohmann::json& data) {
      synth.from_json(data["Synth"]);
      effect.from_json(data["Effect"]);
      master.from_json(data["Master"]);
      sequencer.from_json(data["Sequencer"]);
    };

    auto save = [&] {
      return nlohmann::json({{"Synth", synth.to_json()},
                             {"Effect", effect.to_json()},
                             {"Master", master.to_json()},
                             {"Sequencer", sequencer.to_json()}});
    };

    state_manager.attach("Engines", load, save);

    sequencer.select(std::size_t(0));
    synth.select(std::size_t(0));
    effect.select(std::size_t(0));
  }

  void DefaultEngineManager::start() {}

  audio::ProcessData<2> DefaultEngineManager::process(audio::ProcessData<1> external_in)
  {
    // Main processor function
    auto midi_in = external_in.midi_only();
    auto seq_out = sequencer->process(midi_in);
    auto audio_out = Application::current().audio_manager->buffer_pool().allocate_multi<2>();
    auto synth_out = synth->process({external_in.audio, seq_out.midi, external_in.nframes});

    for (auto&& [snth, out] : util::zip(synth_out, audio_out)) {
      std::get<0>(out) = std::get<0>(snth);
      std::get<1>(out) = std::get<0>(snth);
    }
    synth_out.audio.release();
    auto fx_out = effect->process(seq_out.redirect(audio_out));
    audio_out.release();

    return master.process(std::move(fx_out));
  }

  AnyEngine* DefaultEngineManager::by_name(const std::string& name) noexcept
  {
    auto getter = engineGetters.find(name);
    if (getter == engineGetters.end()) return nullptr;

    return getter->second();
  }

} // namespace otto::services
