#include <sys/types.h>
#include <cmath>

#include "core/globals.hpp"
#include "core/ui/vector_graphics.hpp"
#include "tapedeck.hpp"
#include "tapescreen.hpp"
#include "util/algorithm.hpp"
#include "util/timer.hpp"
#include "services/audio.hpp"
#include "services/engines.hpp"

namespace otto::engines {

  using service::engines::BeatPos;
  using service::engines::TapeTime;

  namespace metronome_state = service::engines::metronome_state;

  // TapeDeck::State ///////////////////////////////////////////////////////////

  bool Tapedeck::State::doSwitchTracks() const
  {
    return !recording();
  }
  bool Tapedeck::State::doTapeOps() const
  {
    return stopped();
  }
  bool Tapedeck::State::doPlayAudio() const
  {
    return playSpeed != 0;
  }
  bool Tapedeck::State::doEaseIn() const
  {
    return !recording();
  }
  bool Tapedeck::State::doStartRec() const
  {
    return !spooling() && !recording();
  }
  bool Tapedeck::State::doStartSpool() const
  {
    return !recording();
  }
  bool Tapedeck::State::doLoop() const
  {
    return playing();
  }
  bool Tapedeck::State::doJumps() const
  {
    return stopped();
  }

  bool Tapedeck::State::fwd() const
  {
    return playSpeed > 0;
  }
  bool Tapedeck::State::bwd() const
  {
    return playSpeed < 0;
  }


  bool Tapedeck::State::playing() const
  {
    return playType == PLAYING;
  }
  bool Tapedeck::State::spooling() const
  {
    return playType == SPOOLING;
  }
  bool Tapedeck::State::stopped() const
  {
    return playType == STOPPED;
  }
  bool Tapedeck::State::recording() const
  {
    return readyToRec && playing();
  }

  // Playback control

  void Tapedeck::State::play(float speed)
  {
    playType  = PLAYING;
    nextSpeed = speed;
  }

  void Tapedeck::State::spool(float speed)
  {
    if (!doStartSpool()) return;
    playType  = SPOOLING;
    nextSpeed = speed;
  }

  void Tapedeck::State::stop()
  {
    stopRecord();
    playType  = STOPPED;
    nextSpeed = 0;
  }

  void Tapedeck::State::startRecord()
  {
    if (!doStartRec()) return;
    readyToRec = true;
  }

  void Tapedeck::State::stopRecord()
  {
    readyToRec = false;
  }

  // Tapedeck //////////////////////////////////////////////////////////////////

  Tapedeck::Tapedeck()
    : Engine("TapeDeck", props, std::make_unique<TapeScreen>(this))
  {}

  void Tapedeck::on_enable()
  {
    tapeBuffer = std::make_unique<tape_buffer>();
  }

  void Tapedeck::on_disable()
  {
    tapeBuffer.reset();
  }

  // Looping

  void Tapedeck::loopInHere()
  {
    loopSect.in = tapeBuffer->position();
    if (loopSect.in == loopSect.out) {
      loopSect.in  = -1;
      loopSect.out = -1;
    }
    if (loopSect.in > loopSect.out) {
      loopSect.out = loopSect.in;
    }
  }

  void Tapedeck::loopOutHere()
  {
    loopSect.out = tapeBuffer->position();
    if (loopSect.in == loopSect.out) {
      loopSect.in  = -1;
      loopSect.out = -1;
    }
    if (loopSect.in > loopSect.out) {
      loopSect.in = loopSect.out;
    }
    if (loopSect.in == -1) {
      loopSect.in = loopSect.out;
    }
  }

  void Tapedeck::goToLoopIn()
  {
    if (state.recording()) return;
    if (loopSect.in == -1) return;
    tapeBuffer->jump_to(loopSect.in);
  }

  void Tapedeck::goToLoopOut()
  {
    if (state.recording()) return;
    if (loopSect.out == -1) return;
    tapeBuffer->jump_to(loopSect.out);
  }


  void Tapedeck::goToBar(BeatPos bar)
  {
    if (state.doJumps()) {
      tapeBuffer->jump_to(metronome_state::bar_time(bar));
    }
  }

  void Tapedeck::goToBarRel(BeatPos bars)
  {
    if (state.doJumps())
      tapeBuffer->jump_to(metronome_state::bar_time_rel(bars));
  }

  int Tapedeck::timeUntil(int tt)
  {
    return 0;
    auto ttUntil = state.fwd() ? tt - position() : position() - tt;
    if (state.doLoop() && state.looping) {
      TapeTime leftTillOut =
        state.fwd() ? loopSect.out - position() : position() - loopSect.in;
      if (leftTillOut < ttUntil) {
        return (leftTillOut +
                 (state.fwd() ? (tt - loopSect.out) : loopSect.in - tt)) /
               state.playSpeed;
      }
    }
    return ttUntil / state.playSpeed;
  }

  /*
   * Audio Processing
   */

  audio::ProcessData<4> Tapedeck::process_playback(audio::ProcessData<0> data)
  {
    TIME_SCOPE("Tapedeck::process_playback");

    // Animate the tape speed
    {
      constexpr int time = 200;  // animation time from 0 to 1 in ms
      static int x;
      static float nextSpeedLast = state.nextSpeed;
      if (nextSpeedLast != state.nextSpeed) {
        state.prevSpeed = state.playSpeed;
        x               = 0;
      }
      nextSpeedLast    = state.nextSpeed;
      const float diff = state.nextSpeed - state.playSpeed;
      if (diff != 0) {
        if (state.doEaseIn()) {
          if (std::abs(diff) < 0.01f) {
            state.playSpeed = state.nextSpeed;
            x               = 0;
          } else {
            if (tapeBuffer->position() == 0 && state.nextSpeed < 0) {
              // Stop tape
              state.playSpeed = state.nextSpeed;
              x               = 0;
            } else {
              float adjTime =
                time * (0.001 + std::abs(state.nextSpeed - state.prevSpeed));
              state.playSpeed =
                state.prevSpeed +
                (state.nextSpeed - state.prevSpeed) *
                (1 - std::cos((x / float(service::audio::samplerate()) * 1000 /
                                  (adjTime)) *
                                M_PI)) *
                  0.5;
              x += data.nframes;
            }
          }
        } else {
          state.playSpeed = state.nextSpeed;
          x               = 0;
        }
      }
    }

    // Start recording by pressing a key
    if (!state.recording() && state.doStartRec() && state.readyToRec) {
      for (auto&& e : data.midi) {
        if (mpark::holds_alternative<midi::NoteOnEvent>(e)) state.play();
      }
    }

    float realSpeed = props.baseSpeed * state.playSpeed;

    proc_buf.clear();

    // Read audio
    if (state.doPlayAudio()) {
      if (state.looping) {
        auto jmp = realSpeed > 0 ? loopSect.out : loopSect.in;
        long n   = tapeBuffer->read_until(
          jmp, realSpeed, std::begin(proc_buf), data.nframes);
        if (n < data.nframes) {
          tapeBuffer->jump_to(realSpeed > 0 ? loopSect.in : loopSect.out);
          tapeBuffer->read_n(data.nframes - n, realSpeed, std::begin(proc_buf));
        }
      } else {
        tapeBuffer->read_n(data.nframes, realSpeed, std::begin(proc_buf));
      }
    }

    return data.redirect(proc_buf);
  }

  audio::ProcessData<0> Tapedeck::process_record(audio::ProcessData<1> data)
  {
    TIME_SCOPE("Tapedeck::process_record");
    float realSpeed = props.baseSpeed * state.playSpeed;
    auto pos        = position();

    // Just started recording
    if (state.recording() && !state.recLast) {
      recSect = {pos, pos};
    }

    if (state.recording()) {
      // Write audio
      auto sect = tapeBuffer->write_n(std::begin(data.audio), data.nframes,
        realSpeed, [&, track = state.track] (auto&& src, auto& dst) {
          dst[track] += src[0] * props.gain;
        });
      recSect += sect;
    }

    // Just stopped recording
    if (!state.recording() && state.recLast) {
      tapeBuffer->slices[state.track].add(recSect);
      recSect = {-1, -2};
    }

    // Save recording state
    state.recLast = state.recording();

    // Graph

    procGraph.clear();
    for (auto&& smpl : data.audio) {
      procGraph.add(smpl[0] * props.gain);
    }

    return data.midi_only();
  }
}  // namespace otto::engines
