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

  std::array<AudioFrame, 256> buffer;
  ui::ModuleScreen<TapeModule> *tapeScreen;

  void mixOut(jack_nframes_t nframes);

  float nextSpeed;
public:

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
  virtual void draw(const ui::ContextPtr& cr) override;

  virtual bool keypress(ui::Key key) override;
  virtual bool keyrelease(ui::Key key) override;

public:

  TapeScreen(TapeModule *module) : ui::ModuleScreen<TapeModule>(module) {}
};
