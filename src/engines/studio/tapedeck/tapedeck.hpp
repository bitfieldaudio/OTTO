#pragma once

#include <atomic>
#include <functional>
#include <thread>

#include "core/engines/engine.hpp"
#include "core/ui/canvas.hpp"
#include "core/ui/engine-ui.hpp"

#include "tapebuffer.hpp"

namespace otto::engines {

  struct Tapedeck final : Engine<EngineType::studio> {
    Tapedeck();
    Tapedeck(Tapedeck&)  = delete;
    Tapedeck(Tapedeck&&) = delete;

    void on_enable() override;
    void on_disable() override;

    util::audio::Section<int> loopSect;
    util::audio::Section<int> recSect;

    int overruns = 0;

    audio::ProcessData<4> process_playback(audio::ProcessData<0>);
    audio::ProcessData<0> process_record(audio::ProcessData<1>);

    int position() const
    {
      return tapeBuffer->position();
    }

    void loopInHere();
    void loopOutHere();
    void goToLoopIn();
    void goToLoopOut();

    void goToBar(int bar);
    void goToBarRel(int bars);

    int timeUntil(std::size_t tt);

    struct State {
      enum PlayType { STOPPED = 0, PLAYING, SPOOLING } playType;

      static constexpr float max_speed = 5;

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

      bool fwd() const;
      bool bwd() const;

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
      Property<float> gain      = {this, "PROC_GAIN", 0.5, {0, 1, 0.01}};
      Property<float> baseSpeed = {this, "Tape Speed", 1, {-2.f, 2.f, 0.01}};
    } props;

    util::audio::Graph procGraph;
    std::unique_ptr<tape_buffer> tapeBuffer;

  private:
    audio::ProcessBuffer<4> proc_buf;
  };

}  // namespace otto::engines
