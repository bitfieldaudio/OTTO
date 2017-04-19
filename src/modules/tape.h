#pragma once

#include <jack/jack.h>
#include <jack/ringbuffer.h>
#include <sndfile.hh>
#include <thread>
#include <atomic>

#include "../audio/jack.h"
#include "../module.h"
#include "../ui/base.h"

class TapeModule : public Module {

  uint bufferSize;
  audio::AudioSample *buffer;
  ui::ModuleScreen<TapeModule> *tapeScreen;

  static void diskRoutine(TapeModule *self);
  static void initThread(Module *arg);
  static void exitThread(Module *arg);

  void mixOut(jack_nframes_t nframes);
public:

  TapeModule();

  std::thread diskThread;
  const static uint nTracks = 4;

  std::atomic_uint track;

  std::atomic_bool recording; // 0: Not recording, !0: track number;
  std::atomic_bool playing;

  const static jack_nframes_t rbSize = 16384 * 4;
  jack_ringbuffer_t *recBuf;
  jack_ringbuffer_t *playBuf;
  SndfileHandle sndfile;

  uint overruns = 0;

  void process(uint nframes);
};

class TapeScreen : public ui::ModuleScreen<TapeModule> {
private:
  virtual void draw(const ui::ContextPtr& cr) override;

  virtual bool keypress(ui::Key key) override;

public:

  TapeScreen(TapeModule *module) : ui::ModuleScreen<TapeModule>(module) {}
};
