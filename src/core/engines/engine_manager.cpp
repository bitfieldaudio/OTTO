#include "engine_manager.hpp"

#include "engines/drums/drum-sampler/drum-sampler.hpp"
#include "engines/drums/simple-drums/simple-drums.hpp"
#include "engines/synths/nuke/nuke.hpp"
#include "services/state.hpp"

namespace otto::engines {
  namespace {
    std::map<std::string, std::function<AnyEngine*()>> engineGetters;
  }

  EngineManager& EngineManager::get()
  {
    static EngineManager* pInstance;

    if (!pInstance) {
      pInstance = new EngineManager();
    }

    return *pInstance;
  }

  void EngineManager::init()
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

  void EngineManager::start()
  {
    tapedeck.on_enable();
    metronome.on_enable();
    mixer.on_enable();
    synth.select(std::size_t(0));
    drums.select(std::size_t(0));
  }

  void EngineManager::shutdown()
  {
    mixer.on_disable();
    tapedeck.on_disable();
  }

  AnyEngine* EngineManager::getEngineByName(const std::string& name)
  {
    auto getter = engineGetters[name];
    if (!getter) {
      return nullptr;
    }

    return getter();
  }
} // namespace otto::engines