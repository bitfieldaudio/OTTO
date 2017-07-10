#pragma once

#include <thread>
#include <atomic>
#include <functional>

#include "../audio/jack.h"
#include "../module.h"
#include "../ui/base.h"
#include "../util/tapebuffer.h"
#include "../utils.h"

#include "metronome.h"

class TapeModule : public module::Module {
  ui::ModuleScreen<TapeModule>::ptr tapeScreen;

  top1::TapeTime tapePosition; // Read from here instead of the tapebuffer
public:

  struct State {
    enum PlayType {
      STOPPED = 0,
      PLAYING,
      SPOOLING
    } playType;

    // whether these features are active in this state
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
    float prevSpeed = 0;
    top1::Track track = top1::Track::newName(1);
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

  struct Data : module::Data {
    module::Opt<float> procGain = {this, "PROC_GAIN", 0.5, 0, 1, 0.01};
  } data;

  top1::AudioAverage procGraph;

  AudioBuffer<AudioFrame> trackBuffer;

  top1::TapeBuffer tapeBuffer;

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
  void display() override;


  top1::TapeTime position() const { return tapePosition; }

  void loopInHere();
  void loopOutHere();
  void goToLoopIn();
  void goToLoopOut();

  void goToBar(BeatPos bar);
  void goToBarRel(BeatPos bars);

  int timeUntil(top1::TapeTime tt);
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
