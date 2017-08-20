#pragma once

#include <thread>
#include <atomic>
#include <functional>

#include "core/modules/module.hpp"
#include "core/ui/canvas.hpp"
#include "core/ui/module-ui.hpp"
#include "util/tapebuffer.hpp"


namespace top1::module {

  using BeatPos = int;

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
      top1::Track track = Track::makeName(1);
      bool looping = false;

      template<typename Ret, typename Callable1, typename Callable2,
               typename = std::enable_if_t<std::is_invocable_r_v<Ret, Callable1> &&
                                           std::is_invocable_r_v<Ret, Callable2>>>
      Ret forPlayDir(Callable1 forward, Callable2 reverse) {
        if (playSpeed > 0) return std::invoke(forward);
        else if (playSpeed < 0) return std::invoke(reverse);
        else return Ret();
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

    audio::Graph procGraph;

    using AudioFrame = audio::AudioFrame<4, float>;
    audio::RTBuffer<AudioFrame> trackBuffer;

    top1::TapeBuffer tapeBuffer;

    TapeModule();
    TapeModule(TapeModule&) = delete;
    TapeModule(TapeModule&&) = delete;

    void init() override;
    void exit() override;

    audio::Section<top1::TapeTime> loopSect;
    audio::Section<top1::TapeTime> recSect;

    uint overruns = 0;

    void preProcess(audio::ProcessData&);
    void postProcess(audio::ProcessData&); 
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
    virtual void draw(ui::drawing::Canvas& ctx) override;

    virtual bool keypress(ui::Key key) override;
    virtual bool keyrelease(ui::Key key) override;

  public:

    TapeScreen(TapeModule *module) : ui::ModuleScreen<TapeModule>(module) {}
  };

} // top1::module
