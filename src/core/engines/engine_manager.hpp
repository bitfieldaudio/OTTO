#pragma once

#include "core/engines/engine.hpp"
#include "core/engines/engine_dispatcher.hpp"

#include "engines/studio/input_selector/input_selector.hpp"
#include "engines/studio/metronome/metronome.hpp"
#include "engines/studio/mixer/mixer.hpp"
#include "engines/studio/tapedeck/tapedeck.hpp"
#include "core/audio/processor.hpp"

namespace otto::engines {
  using TapeTime = unsigned;

  namespace tapeState {
    int position();
    float playSpeed();
    bool playing();
  }

  namespace metronomeState {
    TapeTime getBarTime(BeatPos bar);
    TapeTime getBarTimeRel(BeatPos bar);
    float bar_for_time(std::size_t time);
    std::size_t time_for_bar(float time);
  }

  void init();
  void start();
  void shutdown();

  audio::ProcessData<2> processAudio(audio::ProcessData<1> external_in);

  AnyEngine* getEngineByName(const std::string& name);
} // namespace otto::engines