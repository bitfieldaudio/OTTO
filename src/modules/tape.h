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

class TapeModule : public module::Module {

  float nextSpeed = 0;

  ui::ModuleScreen<TapeModule> *tapeScreen;
public:

  std::array<AudioFrame, 256> trackBuffer;

  top1::TapeBuffer tapeBuffer;

  const static uint nTracks = top1::TapeBuffer::nTracks;

  TapeModule();
  TapeModule(TapeModule&) = delete;
  TapeModule(TapeModule&&) = delete;

  void init() override;
  void exit() override;

  std::atomic_uint track;

  std::atomic_bool recording;
  std::atomic<float> playing;
  std::atomic_bool looping;

  Section<top1::TapeTime> loopSect;

  uint overruns = 0;

  void preProcess(uint nframes);
  void postProcess(uint nframes);

  void play(float speed);
  void stop();
  void record();
  void stopRecord();

  top1::TapeTime getBarTime(BarPos bar);
  top1::TapeTime getBarTimeRel(BarPos bar);
  void goToBar(BarPos bar);
  void goToBarRel(BarPos bars);

  void loopInHere();
  void loopOutHere();
  void goToLoopIn();
  void goToLoopOut();

  BarPos closestBar(top1::TapeTime time);

  void display();
};

class TapeScreen : public ui::ModuleScreen<TapeModule> {
  bool stopRecOnRelease = true;
private:
  virtual void draw(NanoCanvas::Canvas& ctx) override;

  virtual bool keypress(ui::Key key) override;
  virtual bool keyrelease(ui::Key key) override;

public:

  TapeScreen(TapeModule *module) : ui::ModuleScreen<TapeModule>(module) {}
};
