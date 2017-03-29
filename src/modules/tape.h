#pragma once

#include <jack/jack.h>
#include <jack/ringbuffer.h>
#include <sndfile.h>
#include <pthread.h>

#include "../audio/jack.h"
#include "../module.h"

class TapeModule : public Module {
public:
  pthread_t thread;
  const static uint nTracks = 4;

  jack_nframes_t rbSize = 16384;
  jack_ringbuffer_t *ringBuf;
  SNDFILE *sndFile;

  void init();
};
