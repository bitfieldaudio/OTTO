#pragma once

#include <cstdlib>
#include <string>
#include <array>
#include <atomic>
#include <condition_variable>

#include "util/event.hpp"

#include "core/datafile.hpp"
#include "core/audio/jack.hpp"
#include "core/ui/mainui.hpp"
#include "core/modules/module-dispatcher.hpp"

#include "modules/tapedeck.hpp"
#include "modules/mixer.hpp"
#include "modules/metronome.hpp"


namespace top1 {

  class Globals {
  private:
    static inline std::atomic_bool isRunning = {true};
  public:
    static inline std::condition_variable notifyExit;

    static inline struct {
      top1::EventDispatcher<> preInit;
      top1::EventDispatcher<> postInit;
      top1::EventDispatcher<> preExit;
      top1::EventDispatcher<> postExit;
      top1::EventDispatcher<uint> bufferSizeChanged;
      top1::EventDispatcher<uint> samplerateChanged;
    } events;

    static inline DataFile dataFile;
    static inline uint samplerate = 44100;

    static inline audio::JackAudio jackAudio;
    static inline ui::MainUI ui;

    static inline modules::SynthModuleDispatcher synth;
    static inline modules::SynthModuleDispatcher drums;
    static inline modules::EffectModuleDispatcher effect;
    static inline modules::TapeModule tapedeck;
    static inline modules::MixerModule mixer;
    static inline modules::Metronome metronome;

    static inline void init() {
      dataFile.path = "data.json";
      dataFile.read();
      jackAudio.init();
      tapedeck.init();
      mixer.init();
      synth.current().init();
      drums.current().init();
      ui.init();
    }

    //TODO: status codes etc
    static inline void exit() {
      isRunning = false;
      notifyExit.notify_all();
    }

    static inline bool running() {
      return isRunning;
    }
  };

}
