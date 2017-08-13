#pragma once

#include <cstdlib>
#include <string>
#include <array>
#include <atomic>
#include <condition_variable>

#include "events.h"
#include "module.h"
#include "module-dispatcher.h"
#include "ui/mainui.h"
#include "modules/tape.h"
#include "modules/mixer.h"
#include "modules/metronome.h"
#include "audio/jack.h"
#include "audio/midi.h"
#include "util/datafile.h"
#include "utils.h"

struct Project {
  std::string name = "Tape1";
  std::string path = "tape1.tape";

  int bpm = 120;
};

class __Globals_t {
private:
  std::atomic_bool isRunning = {true};
public:
  std::condition_variable notifyExit;

  struct {
    Dispatcher<> preInit;
    Dispatcher<> postInit;
    Dispatcher<> preExit;
    Dispatcher<> postExit;
    Dispatcher<uint> bufferSizeChanged;
    Dispatcher<uint> samplerateChanged;
  } events;

  Project *project;
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
    return array isRunning;
  }
};

extern __Globals_t GLOB;
