#pragma once

#include "core/engines/engine.hpp"
#include "core/engines/engine_dispatcher.hpp"

#include "engines/studio/input_selector/input_selector.hpp"
#include "engines/studio/metronome/metronome.hpp"
#include "engines/studio/mixer/mixer.hpp"
#include "engines/studio/tapedeck/tapedeck.hpp"

namespace otto::engines {
  struct EngineManager {
    static EngineManager& get();

    void init();
    void start();
    void shutdown();

    AnyEngine* getEngineByName(const std::string& name);

    EngineDispatcher<engines::EngineType::synth> synth;
    EngineDispatcher<engines::EngineType::drums> drums;
    EngineDispatcher<engines::EngineType::effect> effect;
    Tapedeck tapedeck;
    Mixer mixer;
    Metronome metronome;
    InputSelector selector;

  private:
    EngineManager()  = default;
    ~EngineManager() = default;
  };
} // namespace otto::engines