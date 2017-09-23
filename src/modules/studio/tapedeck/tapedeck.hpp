#pragma once

#include <thread>
#include <atomic>
#include <functional>

#include "core/modules/module.hpp"
#include "core/ui/canvas.hpp"
#include "core/ui/module-ui.hpp"

#include "tapebuffer.hpp"


namespace top1::modules {

  class Tapedeck final : public modules::Module {
    std::unique_ptr<ui::ModuleScreen<Tapedeck>> tapeScreen;
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
      int track       = 0;
      bool looping    = false;

      template<typename Ret, typename Callable1, typename Callable2>
      Ret forPlayDir(Callable1&& forward, Callable2&& reverse) {
        if (playSpeed > 0) {
          return std::invoke(forward);
        } else if (playSpeed < 0) {
          return std::invoke(reverse);
        } else {
          if constexpr (!std::is_void_v<Ret>) {
              return Ret();
            }
          }
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

    struct Props : Properties {
      Property<float> gain = {this, "PROC_GAIN", 0.5, {0, 1, 0.01}};
    } props;

    audio::Graph procGraph;

    using AudioFrame = audio::AudioFrame<4, float>;
    audio::RTBuffer<AudioFrame> trackBuffer;
    std::unique_ptr<tape_buffer> tapeBuffer;

    Tapedeck();
    Tapedeck(Tapedeck&) = delete;
    Tapedeck(Tapedeck&&) = delete;

    void init() override;
    void exit() override;

    audio::Section<int> loopSect;
    audio::Section<std::size_t> recSect;

    int overruns = 0;

    void preProcess(const audio::ProcessData&);
    void postProcess(const audio::ProcessData&); 
    void display() override;


    std::size_t position() const { return tapeBuffer->position(); }

    void loopInHere();
    void loopOutHere();
    void goToLoopIn();
    void goToLoopOut();

    void goToBar(int bar);
    void goToBarRel(int bars);

    int timeUntil(std::size_t tt);
  };

  class TapeScreen : public ui::ModuleScreen<Tapedeck> {
    bool stopRecOnRelease = true;
  private:
    void draw(ui::drawing::Canvas& ctx) override;

    bool keypress(ui::Key key) override;
    void rotary(ui::RotaryEvent) override;

    bool keyrelease(ui::Key key) override;

    std::string timeStr();
  public:
    using ui::ModuleScreen<Tapedeck>::ModuleScreen;
  };

} // top1::module
