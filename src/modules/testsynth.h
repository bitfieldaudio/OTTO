#pragma once

#include "../module.h"
#include "../globals.h"
#include "../faust.h"
/**
 * Generates a square wave
 */
class TestSynth : public Module {
private:
  TestSynth() {
    frequency = (float *) malloc(sizeof(float*));
  };
  TestSynth(TestSynth &s) = delete;
public:

  float *frequency;

  FaustWrapper faust;

  int cur;

  static TestSynth &getInstance() {
    static TestSynth instance;
    return instance;
  };

  static void init();
};
