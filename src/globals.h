#pragma once

#include <cstdlib>
#include <string>
#include <array>
#include <atomic>
#include <condition_variable>

#include "events.h"
#include "module.h"
#include "ui/mainui.h"
#include "modules/tape.h"
#include "modules/mixer.h"
#include "audio/jack.h"
#include "audio/midi.h"
#include "util/datafile.h"

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
  } events;

  Project *project;
  DataFile dataFile;
  uint samplerate = 44100;

  JackAudio jackAudio;
  MainUI ui;

  struct {
    float *outL;
    float *outR;
    float *input;
    // The sound that is passed between modules
    float *proc;
  } audioData;

  std::vector<MidiEvent*> midiEvents;

  module::SynthModuleDispatcher synth;
  module::EffectModuleDispatcher effect;
  TapeModule tapedeck;
  MixerModule mixer;

  //TODO: status codes etc
  void exit() {
    isRunning = false;
    notifyExit.notify_all();
  }

  bool running() const {
    return isRunning;
  }
};

extern __Globals_t GLOB;
