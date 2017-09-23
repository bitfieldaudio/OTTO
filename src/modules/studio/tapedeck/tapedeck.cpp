#include <bits/std_abs.h>
#include <plog/Log.h>
#include <sys/types.h>
#include <cmath>

#include "core/globals.hpp"
#include "core/ui/drawing.hpp"
#include "tapedeck.hpp"
#include "tapescreen.hpp"

namespace top1::modules {

  using TapeTime = std::size_t;

  /************************************************/
  /* Tapedeck::State Implementation             */
  /************************************************/

  bool Tapedeck::State::doSwitchTracks() const {
    return !recording();
  }
  bool Tapedeck::State::doTapeOps() const {
    return stopped();
  }
  bool Tapedeck::State::doPlayAudio() const {
    return playSpeed != 0;
  }
  bool Tapedeck::State::doEaseIn() const {
    return !recording();
  }
  bool Tapedeck::State::doStartRec() const {
    return !spooling() && !recording();
  }
  bool Tapedeck::State::doStartSpool() const {
    return !recording();
  }
  bool Tapedeck::State::doLoop() const {
    return playing();
  }
  bool Tapedeck::State::doJumps() const {
    return stopped();
  }

  bool Tapedeck::State::playing() const {
    return playType == PLAYING;
  }
  bool Tapedeck::State::spooling() const {
    return playType == SPOOLING;
  }
  bool Tapedeck::State::stopped() const {
    return playType == STOPPED;
  }
  bool Tapedeck::State::recording() const {
    return readyToRec && playing();
  }

  // Playback control

  void Tapedeck::State::play(float speed) {
    playType = PLAYING;
    nextSpeed = speed;
  }

  void Tapedeck::State::spool(float speed) {
    if (!doStartSpool()) return;
    playType = SPOOLING;
    nextSpeed = speed;
  }

  void Tapedeck::State::stop() {
    stopRecord();
    playType = STOPPED;
    nextSpeed = 0;
  }

  void Tapedeck::State::startRecord() {
    if (!doStartRec()) return;
    readyToRec = true;
  }

  void Tapedeck::State::stopRecord() {
    readyToRec = false;
  }

  /************************************************/
  /* Tapedeck Implementation                    */
  /************************************************/

  Tapedeck::Tapedeck() :
    Module(&props),
    tapeScreen (new TapeScreen(this)) {}

  void Tapedeck::init() {
    tapeBuffer = std::make_unique<tape_buffer>();
    display();
  }

  void Tapedeck::exit() {
    tapeBuffer.reset();
  }

  void Tapedeck::display() {
    Globals::ui.display(*tapeScreen);
  }

  // Looping

  void Tapedeck::loopInHere() {
    loopSect.in = tapeBuffer->position();
    if (loopSect.in == loopSect.out) {
      loopSect.in = -1;
      loopSect.out = -1;
    }
    if (loopSect.in > loopSect.out) {
      loopSect.out = loopSect.in;
    }
  }

  void Tapedeck::loopOutHere() {
    loopSect.out = tapeBuffer->position();
    if (loopSect.in == loopSect.out) {
      loopSect.in = -1;
      loopSect.out = -1;
    }
    if (loopSect.in > loopSect.out) {
      loopSect.in = loopSect.out;
    }
    if (loopSect.in == -1) {
      loopSect.in = loopSect.out;
    }
  }

  void Tapedeck::goToLoopIn() {
    if (state.recording()) return;
    if (loopSect.in == -1) return;
    tapeBuffer->jump_to(loopSect.in);
  }

  void Tapedeck::goToLoopOut() {
    if (state.recording()) return;
    if (loopSect.out == -1) return;
    tapeBuffer->jump_to(loopSect.out);
  }


  void Tapedeck::goToBar(BeatPos bar) {
    if (state.doJumps()) tapeBuffer->jump_to(Globals::metronome.getBarTime(bar));
  }

  void Tapedeck::goToBarRel(BeatPos bars) {
    if (state.doJumps()) tapeBuffer->jump_to(Globals::metronome.getBarTimeRel(bars));
  }

  int Tapedeck::timeUntil(std::size_t tt) {
    return 0;
    TapeTime ttUntil = state.forPlayDir<TapeTime>([&] {return tt - position();},
                                                  [&] {return position() - tt;});
    if (state.doLoop() && state.looping) {
      TapeTime leftTillOut = state.forPlayDir<TapeTime>([&] {return loopSect.out - position();},
                                                        [&] {return position() - loopSect.in;});
      if (leftTillOut != -1 && leftTillOut < ttUntil) {
        return state.forPlayDir<int>([&] { return (leftTillOut + (tt - loopSect.out)) ;},
                                     [&] { return (leftTillOut + (loopSect.in - tt)) ;})/state.playSpeed;
      } else {
        return ttUntil/state.playSpeed;
      }
    } else {
      return ttUntil/state.playSpeed;
    }
  }

  /*
   * Audio Processing
   */

  void Tapedeck::process(const audio::ProcessData& data) {

    { // Animate the tape speed
      constexpr int time = 200; // animation time from 0 to 1 in ms
      static int x;
      static float nextSpeedLast = state.nextSpeed;
      if (nextSpeedLast != state.nextSpeed) {
        state.prevSpeed = state.playSpeed;
        x = 0;
      }
      nextSpeedLast = state.nextSpeed;
      const float diff = state.nextSpeed - state.playSpeed;
      if (diff != 0) {
        if (state.doEaseIn()) {
          if (std::abs(diff) < 0.01f) {
            state.playSpeed = state.nextSpeed;
            x = 0;
          } else {
            if (tapeBuffer->position() == 0 && state.nextSpeed < 0) {
              // Stop tape
              state.playSpeed = state.nextSpeed;
              x = 0;
            } else {
              float adjTime = time * (0.001 + std::abs(state.nextSpeed - state.prevSpeed));
              state.playSpeed = state.prevSpeed + (state.nextSpeed - state.prevSpeed) *
                (1 - std::cos((x / float(Globals::samplerate) * 1000/(adjTime)) * M_PI)) * 0.5;
              x += data.nframes;
            }
          }
        } else {
          state.playSpeed = state.nextSpeed;
          x = 0;
        }
      }
    }

    std::fill(std::begin(trackBuffer), std::end(trackBuffer), AudioFrame{0,0,0,0});

    // Start recording by pressing a key
    if (!state.recording() && state.doStartRec() && state.readyToRec) {
      if (std::any_of(std::begin(data.midi), std::end(data.midi),
          [] (auto&& e) {return e.template is<midi::NoteOnEvent>();})) {
        state.play(1);
      }
    }

    // Read audio
    if (state.doPlayAudio()) {
      auto trkbf = std::begin(trackBuffer);
      auto tape = tapeBuffer->read(state.playSpeed);
      std::copy_n(std::move(tape), data.nframes, std::move(trkbf));
    }

    // Write audio
    if (state.recording()) {
      auto proc = std::begin(data.audio.proc);
      tapeBuffer->write_frames(data.nframes, state.playSpeed,
        [&proc, track = state.track] (auto&& trk) {
          trk[track] += *proc;
          return trk;
        } );
    }
  }

} // top1::module
