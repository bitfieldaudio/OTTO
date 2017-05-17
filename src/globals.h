#pragma once

#include <cstdlib>
#include <string>
#include <array>
#include <atomic>

#include "events.h"
#include "module.h"
#include "ui/mainui.h"
#include "modules/tape.h"
#include "modules/mixer.h"
#include "audio/jack.h"
#include "audio/midi.h"

struct Project {
  std::string name = "Tape1";
  std::string path = "tape1.tape";

  int bpm = 120;
};

struct __Globals_t {

  struct {
    Dispatcher<> preInit;
    Dispatcher<> postInit;
    Dispatcher<> preExit;
    Dispatcher<> postExit;
  } events;

  Project *project;
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

  volatile bool doProcess;
  volatile int status;

  std::atomic_bool running;

  module::SynthModuleDispatcher synth;
  module::EffectModuleDispatcher effect1;
  module::EffectModuleDispatcher effect2;
  module::EffectModuleDispatcher effect3;
  module::EffectModuleDispatcher effect4;
  TapeModule tapedeck;
  MixerModule mixer;
};

extern __Globals_t GLOB;
