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
    std::atomic_bool isRunning = {true};
  public:
    std::condition_variable notifyExit;

    struct {
      top1::EventDispatcher<> preInit;
      top1::EventDispatcher<> postInit;
      top1::EventDispatcher<> preExit;
      top1::EventDispatcher<> postExit;
      top1::EventDispatcher<uint> bufferSizeChanged;
      top1::EventDispatcher<uint> samplerateChanged;
    } events;

    DataFile dataFile;
    uint samplerate = 44100;

    audio::JackAudio jackAudio;
    ui::MainUI ui;

    module::SynthModuleDispatcher synth;
    module::SynthModuleDispatcher drums;
    module::EffectModuleDispatcher effect;
    module::TapeModule tapedeck;
    module::MixerModule mixer;
    module::Metronome metronome;

    void init();

    //TODO: status codes etc
    void exit() {
      isRunning = false;
      notifyExit.notify_all();
    }

    bool running() const {
      return isRunning;
    }
  };

  extern Globals GLOB;

  inline void Globals::init() {
    dataFile.path = "data.json";
    dataFile.read();
    jackAudio.init();
    tapedeck.init();
    mixer.init();
    synth.current()->init();
    drums.current()->init();
    ui.init();
  }

}
