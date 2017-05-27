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
    struct Do {
      uint id           = 0;
      bool switchTracks = true;
      bool tapeOps      = true;
      bool playAudio    = true;
      bool easeIn       = true;
      bool startRec     = true;
      bool spool        = true;
      bool loop         = true;

      bool operator == (const Do &other) const {return id == other.id; }
      bool operator != (const Do &other) const {return id != other.id; }
    };

    Do DO;

    bool readyToRec = false;
    bool recLast    = false;
    float playSpeed = 0;
    float nextSpeed = 0;
    uint track = 1;
    bool looping = false;

    Do &operator = (const Do &newState) { DO = newState; return DO; }
    bool operator == (const Do &other) const { return DO == other; }
    bool operator != (const Do &other) const { return DO != other; }

    template<class T>
    T forPlayDir(std::function<T ()> forward, std::function<T ()> reverse) {
      if (playSpeed > 0) { return forward(); }
      if (playSpeed < 0) { return reverse(); }
    }

    bool recording() const;
    bool playing() const;
    bool spooling() const;
    bool stopped() const;

  } state;

  struct States {
    const static State::Do STOPPED;
    const static State::Do SPOOLING;
    const static State::Do PLAYING;
  };

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
