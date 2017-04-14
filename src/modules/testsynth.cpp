#include "testsynth.h"
#include "../globals.h"
#include "testsynth.faust.h"

static void process1(jack_nframes_t nframes, Module *arg) {
  auto *self = (TestSynth *) arg;
  self->faust.processAudio(nframes);
}

static void postInit(Module* arg) {
  auto &self = TestSynth::getInstance();
  self.faust = FaustWrapper(new testsynth(), {
    {"FREQ", &self.frequency}
  });
  *self.frequency = 400;
}

void TestSynth::init() {
  GLOB.events.postInit.add(&getInstance(), postInit);
  GLOB.events.process1.add(&getInstance(), process1);
}
