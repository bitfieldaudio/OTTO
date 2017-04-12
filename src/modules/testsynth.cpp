#include "testsynth.h"
#include "../globals.h"
#include <math.h>

#ifndef M_PI
#define M_PI  (3.14159265)
#endif

#define TABLE_SIZE   (200)
float sine[TABLE_SIZE];
int phase;

static void process1(jack_nframes_t nframes, Module *arg) {
  for(uint i=0; i<nframes; i++ ) {
    GLOB.data.proc[i] = sine[phase];
    phase += 3;
    if( phase >= TABLE_SIZE ) phase -= TABLE_SIZE;
  }
}

void TestSynth::init() {

  for( uint i=0; i<TABLE_SIZE; i++ ) {
    sine[i] = 0.2 * (float) sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2. );
  }
  phase = 0;

  GLOB.events.process1.add(getInstance(), process1);
}
