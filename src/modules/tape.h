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

typedef int BarPos;

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

  std::atomic_bool recording;
  std::atomic<float> playing;
  std::atomic_bool looping;

  Section<TapeTime> loopSect;

  uint overruns = 0;

  void process(uint nframes);

  void play(float speed);
  void stop();

  TapeTime getBarTime(BarPos bar);
  TapeTime getBarTimeRel(BarPos bar);
  void goToBar(BarPos bar);
  void goToBarRel(BarPos bars);

  void loopInHere();
  void loopOutHere();
  void goToLoopIn();
  void goToLoopOut();

  BarPos closestBar(TapeTime time);

};

class TapeScreen : public ui::ModuleScreen<TapeModule> {
private:
  virtual void draw(NanoCanvas::Canvas& ctx) override;

  virtual bool keypress(ui::Key key, bool shift) override;
  virtual bool keyrelease(ui::Key key, bool shift) override;

public:

  TapeScreen(TapeModule *module) : ui::ModuleScreen<TapeModule>(module) {}
};
