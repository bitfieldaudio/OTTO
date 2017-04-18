#pragma once

#include <jack/jack.h>
#include <jack/ringbuffer.h>
#include <sndfile.hh>
#include <thread>
#include <atomic>

#include "../audio/jack.h"
#include "../module.h"

class TapeModule : public Module {
  static void diskRoutine(TapeModule *self);
  static void initThread(Module *arg);
  static void exitThread(Module *arg);

  uint bufferSize;
  audio::AudioSample *buffer;

  void mixOut(jack_nframes_t nframes);
public:

  TapeModule();

  std::thread diskThread;
  const static uint nTracks = 4;

  std::atomic_uint recording; // 0: Not recording, !0: track number;
  std::atomic_bool playing;

  const static jack_nframes_t rbSize = 16384 * 4;
  jack_ringbuffer_t *recBuf;
  jack_ringbuffer_t *playBuf;
  SndfileHandle sndfile;

  uint overruns = 0;

  void process(uint nframes);
};
