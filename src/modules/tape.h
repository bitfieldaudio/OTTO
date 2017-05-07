#pragma once

#include <jack/jack.h>
#include <jack/ringbuffer.h>
#include <sndfile.hh>
#include <thread>
#include <atomic>

#include "../audio/jack.h"
#include "../module.h"
#include "../ui/base.h"
#include "../util/tapebuffer.h"

class TapeModule : public Module {

  void mixOut(jack_nframes_t nframes);

  float nextSpeed = 0;
public:

  std::array<AudioFrame, 256> trackBuffer;

  ui::ModuleScreen<TapeModule> *tapeScreen;

  TapeBuffer tapeBuffer;

  const static uint nTracks = TapeBuffer::nTracks;

  TapeModule();

  std::atomic_uint track;

  std::atomic_bool recording; // 0: Not recording, !0: track number;
  std::atomic<float> playing;

  uint overruns = 0;

  void process(uint nframes);

  void play(float speed);
  void stop();
};

class TapeScreen : public ui::ModuleScreen<TapeModule> {
private:
  virtual void draw(NanoCanvas::Canvas& ctx) override;

  virtual bool keypress(ui::Key key, bool shift) override;
  virtual bool keyrelease(ui::Key key, bool shift) override;

public:

  TapeScreen(TapeModule *module) : ui::ModuleScreen<TapeModule>(module) {}
};
