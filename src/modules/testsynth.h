#pragma once

#include "../module.h"
#include "../globals.h"

/**
 * Generates a square wave
 */
class TestSynth : public Module {
private:
  TestSynth() {};
public:

  int wavelength = 400;
  audio::AudioSample amplitude = 1;

  int cur;

  static TestSynth *getInstance() {
    static TestSynth instance;
    return &instance;
  };

  static void init();
};
