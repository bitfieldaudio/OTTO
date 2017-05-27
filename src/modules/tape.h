#pragma once

#include <thread>
#include <atomic>
#include <functional>

#include "../audio/jack.h"
#include "../module.h"
#include "../ui/base.h"
#include "../util/tapebuffer.h"

typedef int BarPos;

class TapeModule : public module::Module {
  ui::ModuleScreen<TapeModule> *tapeScreen;
public:

  struct State {
    enum PlayType {
      STOPPED = 0,
      PLAYING,
      SPOOLING
    } playType;

    bool doSwitchTracks() const;
    bool doTapeOps() const;
    bool doPlayAudio() const;
    bool doEaseIn() const;
    bool doStartRec() const;
    bool doStartSpool() const;
    bool doLoop() const;
    bool doJumps() const;

    bool readyToRec = false;
    bool recLast    = false;
    float playSpeed = 0;
    float nextSpeed = 0;
    uint track = 1;
    bool looping = false;

    template<class T>
    T forPlayDir(std::function<T ()> forward, std::function<T ()> reverse) {
      if (playSpeed > 0) { return forward(); }
      if (playSpeed < 0) { return reverse(); }
    }

    bool recording() const;
    bool playing() const;
    bool spooling() const;
    bool stopped() const;

    void play(float speed = 1);
    void spool(float speed = 5);
    void stop();
    void startRecord();
    void stopRecord();

  } state;

  std::array<AudioFrame, 256> trackBuffer;

  top1::TapeBuffer tapeBuffer;

  const static uint nTracks = top1::TapeBuffer::nTracks;

  TapeModule();
  TapeModule(TapeModule&) = delete;
  TapeModule(TapeModule&&) = delete;

  void init() override;
  void exit() override;

  Section<top1::TapeTime> loopSect;
  Section<top1::TapeTime> recSect;

  uint overruns = 0;

  void preProcess(uint nframes);
  void postProcess(uint nframes);

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
