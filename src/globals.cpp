#include "globals.h"

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

__Globals_t GLOB;

