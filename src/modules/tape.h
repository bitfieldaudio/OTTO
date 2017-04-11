#pragma once

#include <jack/jack.h>
#include <jack/ringbuffer.h>
#include <sndfile.hh>
#include <pthread.h>

#include "../audio/jack.h"
#include "../module.h"

class TapeModule : public Module {
private:
  TapeModule() {};
public:
  pthread_t thread;
  const static uint nTracks = 4;

  uint recording = 1; // 0: Not recording, !0: track number;
  bool monitor = 1; // 0: Not recording, !0: track number;

  jack_nframes_t rbSize = 16384;
  jack_ringbuffer_t *ringBuf;
  SndfileHandle sndfile;

  static TapeModule *getInstance() {
    static TapeModule instance;
    return &instance;
  };

  static void init();
};
