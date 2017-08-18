#pragma once

#include <cstdlib>
#include <string>
#include <array>
#include <atomic>
#include <condition_variable>

#include "util/event.hpp"

#include "core/datafile.hpp"
#include "core/audio/jack.hpp"
#include "core/audio/midi.hpp"
#include "core/ui/mainui.hpp"


namespace top1 {
  
class __Globals_t {
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

  JackAudio jackAudio;
  MainUI ui;

  std::vector<MidiEventPtr> midiEvents;

  module::SynthModuleDispatcher synth;
  module::SynthModuleDispatcher drums;
  module::EffectModuleDispatcher effect;
  TapeModule tapedeck;
  MixerModule mixer;
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

static inline __Globals_t GLOB;

void __Globals_t::init() {
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
