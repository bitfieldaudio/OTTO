#pragma once

#include <cstdlib>
#include <string>
#include <array>
#include <atomic>
#include <condition_variable>

#include "util/event.hpp"

#include "filesystem.hpp"
#include "core/datafile.hpp"
#include "core/audio/main_audio.hpp"
#include "core/ui/mainui.hpp"
#include "core/modules/module-dispatcher.hpp"

#include "modules/studio/input_selector/input_selector.hpp"
#include "modules/studio/tapedeck/tapedeck.hpp"
#include "modules/studio/mixer/mixer.hpp"
#include "modules/studio/metronome/metronome.hpp"


namespace otto {

  class Globals {
  private:
    static inline std::atomic_bool isRunning {true};
  public:

    static inline const filesystem::path data_dir {"data"};

    static inline struct {
      util::EventDispatcher<> preInit;
      util::EventDispatcher<> postInit;
      util::EventDispatcher<> preExit;
      util::EventDispatcher<> postExit;
      util::EventDispatcher<unsigned> bufferSizeChanged;
      util::EventDispatcher<unsigned> samplerateChanged;
    } events;

    static inline DataFile dataFile {data_dir / "modules.json"};
    static inline unsigned samplerate = 44100;

    static inline audio::MainAudio audio;
    static inline ui::MainUI ui;

    static inline modules::SynthModuleDispatcher synth;
    static inline modules::SynthModuleDispatcher drums;
    static inline modules::EffectModuleDispatcher effect;
    static inline modules::Tapedeck tapedeck;
    static inline modules::Mixer mixer;
    static inline modules::Metronome metronome;
    static inline modules::InputSelector selector;

    static inline void init() {
      dataFile.read();
      audio.init();
      tapedeck.init();
      mixer.init();
      synth.current().init();
      drums.current().init();
      ui.init();
    }

    // TODO: status codes etc
    static inline void exit() {
      isRunning = false;
    }

    static inline bool running() {
      return isRunning;
    }
  };

}
