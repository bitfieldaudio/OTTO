#include "testsynth.h"
#include "../globals.h"

static void process1(jack_nframes_t nframes, Module *arg) {
  auto *self = (TestSynth *) arg;

  for (uint f = 0; f < nframes; f++) {
    if (self->cur >= 0) {
      if (self->cur >= self->wavelength) {
        self->cur = -self->wavelength;
      }
      GLOB.data.proc[f] = self->amplitude;
    } else {
      GLOB.data.proc[f] = -self->amplitude;
    }
    self->cur++;
  }
}

void TestSynth::init() {
  GLOB.events.process1.add(getInstance(), process1);
}
