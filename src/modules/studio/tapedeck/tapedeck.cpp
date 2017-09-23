#include <bits/std_abs.h>
#include <plog/Log.h>
#include <sys/types.h>
#include <cmath>

#include "core/globals.hpp"
#include "core/ui/drawing.hpp"
#include "tapedeck.hpp"

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

  // Audio Processing
  void Tapedeck::preProcess(const audio::ProcessData& data) {

    {
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

    std::fill(std::begin(trackBuffer), std::end(trackBuffer), AudioFrame{0});

    auto playAudio = [this](uint at, uint nframes) {
      auto iter = tapeBuffer->citer(state.playSpeed);
      std::copy_n(iter, nframes, trackBuffer.begin() + at);
    };

    // Start recording by pressing a key
    if (!state.recording() && state.doStartRec() && state.readyToRec) {
      for (auto event : data.midi) {
        if (event.is<midi::NoteOnEvent>()) {
          state.play(1);
          break;
        }
      }
    }

    if (state.doPlayAudio()) {
      TapeTime pos = tapeBuffer->position();
      if (state.doLoop() && state.looping) {
        int leftTillOut =
          state.forPlayDir<int>([&] {return loopSect.out - pos;},
                                     [&] {return pos - loopSect.in;});
        if (leftTillOut >= 0 && leftTillOut < (int)data.nframes) {
          playAudio(0, leftTillOut);
          state.forPlayDir<void>(
            [&] {tapeBuffer->jump_to(loopSect.in);},
            [&] {tapeBuffer->jump_to(loopSect.out);});
          playAudio(leftTillOut, data.nframes - leftTillOut);
        } else {
          playAudio(0, data.nframes);
        }
      } else {
        playAudio(0, data.nframes);
      }
    }
  }

  void Tapedeck::postProcess(const audio::ProcessData& data) {
    // TapeTime pos = tapeBuffer.position();
    // if (!state.recording() && state.recLast) {
    //   recSect = {0,0};
    // }
    // auto recAudio = [&](uint from, uint recFrames) {
    //   std::vector<AudioFrame> buf;
    //   state.forPlayDir<void>([&] {
    //       uint writeSize = recFrames * state.playSpeed;
    //       for (uint i = 0; i < writeSize; i++) {
    //         buf.push_back(data.audio.proc[int(from + i / state.playSpeed)]);
    //       }
    //       tapeBuffer.writeFW(buf, (data.nframes - from) * state.playSpeed - writeSize,
    //                          [this](AudioFrame o, AudioFrame n) {
    //                            return o[state.track.idx] + n[state.track.idx];});
    //       if (recSect.size() < 1) {
    //         recSect.in = pos - (data.nframes - from) * state.playSpeed;
    //       }
    //       recSect.out = pos - (data.nframes - from) * state.playSpeed + writeSize;
    //     }, [&] {
    //       uint writeSize = recFrames * -state.playSpeed;
    //       for (uint i = 0; i < writeSize; i++) {
    //         buf.push_back(data.audio.proc[int(from + i / -state.playSpeed)]);
    //       }
    //       tapeBuffer.writeBW(buf, (data.nframes - from) * state.playSpeed - writeSize,
    //                          [this](AudioFrame o, AudioFrame n) {
    //                            return o[state.track.idx] + n[state.track.idx];});
    //       if (recSect.size() < 1) {
    //         recSect.out = pos + (data.nframes - from) * -state.playSpeed;
    //       }
    //       recSect.in = pos + (data.nframes - from) * state.playSpeed + writeSize;
    //     });
    //   tapeBuffer.trackSlices[state.track.idx].addSlice(recSect);
    // };

    // if (state.recording()) {
    //   if (state.doLoop() && state.looping) {
    //     TapeTime leftTillOut = state.forPlayDir<TapeTime>(
    //                                                       [&] {return loopSect.out - pos;},
    //                                                       [&] {return pos - loopSect.in;});
    //     if (leftTillOut >= 0 && leftTillOut < (int)data.nframes) {
    //       recAudio(0, leftTillOut);
    //       state.forPlayDir<void>(
    //                              [&] {tapeBuffer.goTo(loopSect.in);},
    //                              [&] {tapeBuffer.goTo(loopSect.out);});
    //       recSect = {0,0};
    //       recAudio(leftTillOut, data.nframes - leftTillOut);
    //     } else {
    //       recAudio(0, data.nframes);
    //     }
    //   } else {
    //     recAudio(0, data.nframes);
    //   }
    // }
    // state.recLast = state.recording();

    // for (uint i = 0; i < data.nframes; i++) {
    //   procGraph.add(data.audio.proc[i] * props.gain);
    // }
  }

  /************************************************/
  /* TapeScreen Implementation                    */
  /************************************************/

  bool TapeScreen::keypress(ui::Key key) {
    bool shift = Globals::ui.keys[ui::K_SHIFT];
    switch (key) {
    case ui::K_REC:
      module->state.startRecord();
      return true;
    case ui::K_PLAY:
      if (Globals::ui.keys[ui::K_REC]) {
        stopRecOnRelease = false;
      }
      return false;
    case ui::K_TRACK_1:
      module->state.track = 0;
      return true;
    case ui::K_TRACK_2:
      module->state.track = 1;
      return true;
    case ui::K_TRACK_3:
      module->state.track = 2;
      return true;
    case ui::K_TRACK_4:
      module->state.track = 3;
      return true;
    case ui::K_LEFT:
      if (shift) module->goToBarRel(-1);
      else module->state.spool(-5);
      return true;
    case ui::K_RIGHT:
      if (shift) module->goToBarRel(1);
      else module->state.spool(5);
      return true;
    case ui::K_LOOP:
      module->state.looping = !module->state.looping;
      return true;
    case ui::K_LOOP_IN:
      if (shift) module->loopInHere();
      else module->goToLoopIn();
      return true;
    case ui::K_LOOP_OUT:
      if (shift) module->loopOutHere();
      else module->goToLoopOut();
      return true;
    case ui::K_CUT:
      if (module->state.doTapeOps())
        // TODO:
        // module->tapeBuffer.trackSlices[module->state.track].cut(module->tapeBuffer.position());
      return true;
    case ui::K_LIFT:
      if (module->state.doTapeOps())
        // TODO:
        // module->tapeBuffer.lift(module->state.track);
      return true;
    case ui::K_DROP:
      if (module->state.doTapeOps())
        // TODO:
        // module->tapeBuffer.drop(module->state.track);
      return true;
    default:
      return false;
    }
  }

  void TapeScreen::rotary(ui::RotaryEvent e) {
    switch (e.rotary) {
    case ui::Rotary::Blue:
      break;
    case ui::Rotary::Green:
      break;
    case ui::Rotary::White:
      break;
    case ui::Rotary::Red:
      module->props.gain.step(e.clicks);
      break;
    }
  }

  bool TapeScreen::keyrelease(ui::Key key) {
    switch (key) {
    case ui::K_REC:
      if (stopRecOnRelease) {
        module->state.stopRecord();
        return true;
      } else {
        stopRecOnRelease = true;
        return true;
      }
    case ui::K_LEFT:
    case ui::K_RIGHT:
      module->state.stop();
      return true;
    default:
      return false;
    }
  }
} // top1::module

namespace top1::ui::drawing {
  namespace Colours {

    const Colour Tape = Colour(0.4, 0.4, 0.4);
    const Colour CurrentTrack = 0xFF4A4A;
    const Colour CurrentSlice = 0x4A4AFF;
    const Colour OtherTrack = 0x505050;
    const Colour LoopMarker = Green;
    const Colour BarMarker = Gray70;

  }
}

namespace top1::modules {

  std::string TapeScreen::timeStr() {
        double seconds = module->position()/(1.0 * Globals::samplerate);
        double minutes = seconds / 60.0;
        return fmt::format("{:0>2}:{:0>5.2f}", (int) minutes, fmod(seconds, 60.0));
    }

  static void drawReel(ui::drawing::Canvas& ctx, ui::drawing::Colour recColor) {
    using namespace ui::drawing;
    // #TapeReel
    ctx.save();
    ctx.transform(1.000000, 0.000000, 0.000000, 1.000000, -29.999796, -873.862160);

    ctx.beginPath();
    ctx.globalAlpha(1.0);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.strokeStyle(recColor);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.miterLimit(4);
    ctx.lineWidth(1.000000);
    ctx.fillStyle(Colours::Black);
    ctx.moveTo(82.500000, 874.864110);
    ctx.translate(82.499931, 926.362088);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 51.497978, -1.570795, -3.14159405, 1);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.499931, -926.362088);
    ctx.translate(82.499931, 926.362232);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 51.497978, -3.141591, -4.71239032, 1);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.499931, -926.362232);
    ctx.translate(82.500072, 926.362232);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 51.497978, 1.570798, -0.00000140, 1);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.500072, -926.362232);
    ctx.translate(82.500072, 926.362088);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 51.497978, 0.000001, -1.57079772, 1);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.500072, -926.362088);

    ctx.moveTo(82.500000, 881.479350);
    ctx.translate(82.314896, 926.362638);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 44.883670, -1.566672, -1.34174594, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.314896, -926.362638);
    ctx.translate(82.486916, 879.256055);
    ctx.rotate(0.000000);
    ctx.scale(0.432277, 1.000000);
    ctx.arc(0.000000, 0.000000, 23.424485, 0.145453, 1.56950419, 0);
    ctx.scale(2.313331, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.486916, -879.256055);
    ctx.translate(82.510263, 879.256047);
    ctx.rotate(0.000000);
    ctx.scale(0.432277, 1.000000);
    ctx.arc(0.000000, 0.000000, 23.424485, 1.571810, 2.99554928, 0);
    ctx.scale(2.313331, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.510263, -879.256047);
    ctx.translate(82.742780, 926.362363);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 44.883670, -1.801211, -1.57620546, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.742780, -926.362363);
    ctx.pathWinding(Canvas::Winding::CW);

    ctx.moveTo(82.500000, 909.243020);
    ctx.translate(82.501454, 926.362586);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 17.119566, -1.570881, -0.67002052, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.501454, -926.362586);
    ctx.translate(97.253964, 917.845616);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.500000, -2.133668, -2.10982770, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-97.253964, -917.845616);
    ctx.translate(97.219537, 917.865835);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.500000, -2.093857, -0.52346737, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-97.219537, -917.865835);
    ctx.translate(97.219517, 917.865801);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.500000, -0.523451, 1.04665029, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-97.219517, -917.865801);
    ctx.translate(97.323316, 917.809030);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.500000, 1.093979, 1.12018241, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-97.323316, -917.809030);
    ctx.translate(82.499580, 926.373816);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 17.119566, -0.377758, -0.00068084, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.499580, -926.373816);
    ctx.translate(82.499582, 926.347771);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 17.119566, 0.000841, 1.42433114, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.499582, -926.347771);
    ctx.translate(82.500172, 943.387082);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.500000, -0.041228, -0.00997684, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.500172, -943.387082);
    ctx.translate(82.500047, 943.362140);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.500000, -0.000000, 1.57079637, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.500047, -943.362140);
    ctx.translate(82.500047, 943.362140);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.500000, 1.570796, 3.14159265, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.500047, -943.362140);
    ctx.translate(82.499055, 943.432561);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.500000, -3.113421, -3.07902363, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.499055, -943.432561);
    ctx.translate(82.500456, 926.339682);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 17.119566, 1.717146, 3.14028085, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.500456, -926.339682);
    ctx.translate(82.500414, 926.406249);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 17.119566, -3.139016, -2.76228248, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.500414, -926.406249);
    ctx.translate(67.755867, 917.851671);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.500000, 2.052473, 2.08358559, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-67.755867, -917.851671);
    ctx.translate(67.780528, 917.865741);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.500000, 2.094942, 3.66504405, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-67.780528, -917.865741);
    ctx.translate(67.780508, 917.865775);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.500000, -2.618125, -1.04773538, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-67.780508, -917.865775);
    ctx.translate(67.703948, 917.819787);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.500000, -1.012009, -0.98036185, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-67.703948, -917.819787);
    ctx.translate(82.523511, 926.362590);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 17.119566, -2.472446, -1.57216673, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.523511, -926.362590);

    ctx.moveTo(82.500000, 912.758640);
    ctx.translate(82.499199, 926.361355);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 13.602715, -1.570737, -3.14165183, 1);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.499199, -926.361355);
    ctx.translate(82.499199, 926.362965);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 13.602715, -3.141533, -4.71244787, 1);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.499199, -926.362965);
    ctx.translate(82.500801, 926.362965);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 13.602715, 1.570855, -0.00005918, 1);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.500801, -926.362965);
    ctx.translate(82.500801, 926.361355);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 13.602715, 0.000059, -1.57085521, 1);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.500801, -926.361355);

    ctx.moveTo(82.500000, 923.916850);
    ctx.translate(82.499660, 926.362502);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.445652, -1.570657, -0.00013991, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.499660, -926.362502);
    ctx.translate(82.499660, 926.361818);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.445652, 0.000140, 1.57065727, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.499660, -926.361818);
    ctx.translate(82.500340, 926.361818);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.445652, 1.570935, 3.14145274, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.500340, -926.361818);
    ctx.translate(82.500340, 926.362502);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 2.445652, -3.141453, -1.57093538, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.500340, -926.362502);

    ctx.moveTo(109.830080, 935.285990);
    ctx.translate(123.269691, 949.915786);
    ctx.rotate(0.523599);
    ctx.scale(1.000000, 0.432277);
    ctx.arc(0.000000, 0.000000, 23.424483, -2.513502, -1.71357365, 0);
    ctx.scale(1.000000, 2.313331);
    ctx.rotate(-0.523599);
    ctx.translate(-123.269691, -949.915786);
    ctx.translate(82.532937, 926.248999);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 44.883670, 0.301310, 0.75104591, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.532937, -926.248999);
    ctx.translate(123.299800, 949.904177);
    ctx.rotate(0.523599);
    ctx.scale(1.000000, 0.432277);
    ctx.arc(0.000000, 0.000000, 23.424483, 1.716675, 3.14044579, 0);
    ctx.scale(1.000000, 2.313331);
    ctx.rotate(-0.523599);
    ctx.translate(-123.299800, -949.904177);
    ctx.translate(123.293116, 949.915785);
    ctx.rotate(0.523599);
    ctx.scale(1.000000, 0.432277);
    ctx.arc(0.000000, 0.000000, 23.424483, -3.141417, -2.54151478, 0);
    ctx.scale(1.000000, 2.313331);
    ctx.rotate(-0.523599);
    ctx.translate(-123.293116, -949.915785);
    ctx.translate(123.305322, 949.915294);
    ctx.rotate(0.523599);
    ctx.scale(1.000000, 0.432277);
    ctx.arc(0.000000, 0.000000, 23.424483, -2.542296, -2.51572870, 0);
    ctx.scale(1.000000, 2.313331);
    ctx.rotate(-0.523599);
    ctx.translate(-123.305322, -949.915294);
    ctx.pathWinding(Canvas::Winding::CW);

    ctx.moveTo(54.451172, 935.287990);
    ctx.translate(41.706709, 949.913586);
    ctx.rotate(1.047198);
    ctx.scale(0.432277, 1.000000);
    ctx.arc(0.000000, 0.000000, 23.424483, -2.241538, -1.57093822, 0);
    ctx.scale(2.313331, 1.000000);
    ctx.rotate(-1.047198);
    ctx.translate(-41.706709, -949.913586);
    ctx.translate(41.701831, 949.905121);
    ctx.rotate(1.047198);
    ctx.scale(0.432277, 1.000000);
    ctx.arc(0.000000, 0.000000, 23.424483, -1.569973, -0.14518859, 0);
    ctx.scale(2.313331, 1.000000);
    ctx.rotate(-1.047198);
    ctx.translate(-41.701831, -949.905121);
    ctx.translate(82.544941, 926.355072);
    ctx.rotate(0.000000);
    ctx.scale(1.000000, 1.000000);
    ctx.arc(0.000000, 0.000000, 44.883670, 2.393477, 2.84321061, 0);
    ctx.scale(1.000000, 1.000000);
    ctx.rotate(-0.000000);
    ctx.translate(-82.544941, -926.355072);
    ctx.translate(41.736106, 949.912836);
    ctx.rotate(1.047198);
    ctx.scale(0.432277, 1.000000);
    ctx.arc(0.000000, 0.000000, 23.424483, -2.997216, -2.24331013, 0);
    ctx.scale(2.313331, 1.000000);
    ctx.rotate(-1.047198);
    ctx.translate(-41.736106, -949.912836);
    ctx.pathWinding(Canvas::Winding::CW);
    ctx.fill();
    ctx.stroke();

    // #Circle
    ctx.beginPath();
    ctx.globalAlpha(1.0);
    ctx.strokeStyle(recColor);
    ctx.miterLimit(4);
    ctx.lineWidth(2.004047);
    ctx.arc(82.500000, 926.362180, 51.497978, 0.000000, 6.28318531, 1);
    ctx.stroke();
    ctx.restore();
  }

  void TapeScreen::draw(ui::drawing::Canvas& ctx) {
    using namespace ui::drawing;

    double rotation = (module->tapeBuffer->position()/double(Globals::samplerate));

    auto recColor = (module->state.readyToRec) ? Colours::Red : Colours::White;

    int timeLength = 5 * Globals::samplerate;

    audio::Section<int> inView;
    inView.in = module->tapeBuffer->position() - timeLength/2;
    inView.out = module->tapeBuffer->position() + timeLength/2;

    int startCoord = -5;
    int endCoord = 325;
    int coordWidth = endCoord - startCoord;

    float lengthRatio = (float)coordWidth/(float)timeLength;
    auto timeToCoord = [&](int time) -> float {
      if (inView.contains(time)){
        time -= inView.in;
        float coord = startCoord + time * lengthRatio;
        return coord;
      }
      return NAN;
    };

    ctx.save();

    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.miterLimit(4);
    ctx.lineWidth(2);

    int BPM = Globals::metronome.props.bpm;
    float FPB = float(Globals::samplerate) * 60.0/((float)BPM);

    // Bar Markers
    {
      int numFirst = std::max<int>(std::ceil(inView.in/FPB), 0);
      float x;
      for (int bn = numFirst; !std::isnan(x = timeToCoord(bn * FPB)); bn++) {
        float y = 190.0;
        ctx.beginPath();
        ctx.strokeStyle(Colours::BarMarker);
        ctx.lineWidth(1);
        ctx.moveTo(x, y);
        ctx.lineTo(x, 195);
        ctx.stroke();
      }
    }

    // Tracks
    // Track::foreach([&](Track t){
    //     auto slices = module->tapeBuffer.trackSlices[t.idx].slicesIn(inView);
    //     TapeBuffer::TapeSlice current;
    //     float lW = 3;
    //     for (auto slice : slices) {
    //       Colour col;
    //       if (t == module->state.track) {
    //         if (slice.contains(module->tapeBuffer.position())) {
    //           if (!current) {
    //             current = slice;
    //             continue;
    //           } else {
    //             LOGE << "TapeSlice overlap at current position";
    //           }
    //         } else {
    //           col = Colours::CurrentTrack;
    //         }
    //       } else {
    //         col = Colours::OtherTrack;
    //       }
    //       if (slice.size() >= 0 && slice.in >= 0 && slice.out >= 0) {
    //         if (inView.overlaps(slice)) {
    //           ctx.beginPath();
    //           ctx.strokeStyle(col);
    //           ctx.lineWidth(lW);
    //           ctx.moveTo(timeToCoord(std::max<float>(inView.in, slice.in)), 195 + 5*t.idx);
    //           ctx.lineTo(timeToCoord(std::min<float>(inView.out, slice.out)), 195 + 5*t.idx);
    //           ctx.stroke();
    //         }
    //       }
    //     }
    //     if (module->state.recording() && module->state.track == t) {
    //       current = module->recSect;
    //     }
    //     if (current) {
    //       if (inView.overlaps(current)) {
    //         ctx.beginPath();
    //         ctx.strokeStyle(Colours::CurrentSlice);
    //         ctx.lineWidth(lW);
    //         ctx.moveTo(timeToCoord(std::max<float>(inView.in, current.in)), 195 + 5*t.idx);
    //         ctx.lineTo(timeToCoord(std::min<float>(inView.out, current.out)), 195 + 5*t.idx);
    //         ctx.stroke();
    //       }
    //     }
    //   });

    // LoopArrow
    if (module->state.looping) {
      ctx.beginPath();
      ctx.globalAlpha(1.0);
      ctx.strokeStyle(Colours::White);
      ctx.lineCap(Canvas::LineCap::ROUND);
      ctx.lineJoin(Canvas::LineJoin::ROUND);
      ctx.miterLimit(2);
      ctx.lineWidth(1.4);
      ctx.moveTo(154.398460, 132.399290);
      ctx.lineTo(152.845290, 132.399290);
      ctx.bezierCurveTo(149.551640, 132.399290, 146.881700, 135.069220, 146.881700, 138.362860);
      ctx.bezierCurveTo(146.881700, 141.656510, 149.551640, 144.326460, 152.845290, 144.326460);
      ctx.lineTo(166.802650, 144.326460);
      ctx.bezierCurveTo(170.096300, 144.326460, 172.766230, 141.656510, 172.766230, 138.362860);
      ctx.bezierCurveTo(172.766230, 135.069220, 170.096300, 132.399290, 166.802650, 132.399290);
      ctx.lineTo(162.373100, 132.399290);
      ctx.stroke();

      ctx.beginPath();
      ctx.globalAlpha(1.0);
      ctx.strokeStyle(Colours::White);
      ctx.fillStyle(Colours::White);
      ctx.lineCap(Canvas::LineCap::ROUND);
      ctx.lineJoin(Canvas::LineJoin::ROUND);
      ctx.miterLimit(2);
      ctx.lineWidth(1);
      ctx.moveTo(162.373000, 132.399290);
      ctx.lineTo(162.373000, 134.399000);
      ctx.lineTo(158.373000, 132.399000);
      ctx.lineTo(162.373000, 130.399000);
      ctx.lineTo(162.373000, 132.399290);
      ctx.stroke();
      ctx.fill();
    }

    // StaticBackground
    {
      // #path4251
      ctx.beginPath();
      ctx.lineJoin(Canvas::LineJoin::ROUND);
      ctx.strokeStyle(Colours::Tape);
      ctx.lineCap(Canvas::LineCap::ROUND);
      ctx.miterLimit(4);
      ctx.lineWidth(2.000000);
      ctx.moveTo(265.000000, 121.000000);
      ctx.lineTo(230.000000, 174.000040);
      ctx.bezierCurveTo(228.654650, 176.065380, 226.599010, 176.839830, 224.958280, 176.563170);
      ctx.lineTo(189.000000, 170.500040);
      ctx.lineTo(160.000000, 170.500040);
      ctx.lineTo(131.000000, 170.500040);
      ctx.bezierCurveTo(131.000000, 170.500040, 95.606328, 176.609310, 94.157836, 176.563170);
      ctx.bezierCurveTo(92.709345, 176.517070, 91.091326, 176.867150, 89.000000, 174.500040);
      ctx.lineTo(53.748322, 134.478190);
      ctx.stroke();
  
      // #circle4383
      ctx.beginPath();
      ctx.globalAlpha(1.0);
      ctx.miterLimit(4);
      ctx.lineWidth(2.004047);
      ctx.fillStyle(Colours::Tape);
      ctx.arc(82.500000, 106.000000, 41.536888, 0.000000, 6.28318531, 1);
      ctx.fill();
  
      // #ellipse4367
      ctx.beginPath();
      ctx.globalAlpha(1.0);
      ctx.miterLimit(4);
      ctx.lineWidth(1.291101);
      ctx.fillStyle(Colours::Tape);
      ctx.arc(237.500000, 106.000020, 32.554844, 0.000000, 6.28318531, 1);
      ctx.fill();
  
      // #circle4376
      ctx.beginPath();
      ctx.globalAlpha(1.0);
      ctx.miterLimit(4);
      ctx.lineWidth(1.291101);
      ctx.fillStyle(Colours::Black);
      ctx.arc(237.500000, 106.000020, 20.726049, 0.000000, 6.28318531, 1);
      ctx.fill();
  
      // #path4243
      ctx.beginPath();
      ctx.globalAlpha(1.0);
      ctx.strokeStyle(recColor);
      ctx.miterLimit(4);
      ctx.lineWidth(1.000000);
      ctx.moveTo(93.500000, 166.954566);
      ctx.bezierCurveTo(96.010385, 166.954566, 98.045455, 168.989635, 98.045455, 171.500020);
      ctx.bezierCurveTo(98.045455, 174.010405, 96.010385, 176.045475, 93.500000, 176.045475);
      ctx.bezierCurveTo(90.989615, 176.045475, 88.954545, 174.010405, 88.954545, 171.500020);
      ctx.bezierCurveTo(88.954545, 168.989635, 90.989615, 166.954566, 93.500000, 166.954566);
      ctx.stroke();
  
      // #circle4245
      ctx.beginPath();
      ctx.globalAlpha(1.0);
      ctx.strokeStyle(recColor);
      ctx.miterLimit(4);
      ctx.lineWidth(1.000000);
      ctx.moveTo(225.500000, 166.954566);
      ctx.bezierCurveTo(228.010385, 166.954566, 230.045455, 168.989635, 230.045455, 171.500020);
      ctx.bezierCurveTo(230.045455, 174.010405, 228.010385, 176.045475, 225.500000, 176.045475);
      ctx.bezierCurveTo(222.989615, 176.045475, 220.954545, 174.010405, 220.954545, 171.500020);
      ctx.bezierCurveTo(220.954545, 168.989635, 222.989615, 166.954566, 225.500000, 166.954566);
      ctx.stroke();
  
      // #path4301
      ctx.beginPath();
      ctx.lineJoin(NanoCanvas::Canvas::LineJoin::ROUND);
      ctx.strokeStyle(recColor);
      ctx.lineCap(NanoCanvas::Canvas::LineCap::ROUND);
      ctx.miterLimit(4);
      ctx.lineWidth(1.703057);
      ctx.fillStyle(Colours::Black);
      ctx.moveTo(130.496090, 160.496090);
      ctx.lineTo(134.496090, 180.503940);
      ctx.lineTo(185.503910, 180.503940);
      ctx.lineTo(189.503910, 160.496090);
      ctx.closePath();
      ctx.moveTo(160.000000, 181.255840);
      ctx.lineTo(160.000000, 212.000040);
      ctx.fill();
      ctx.stroke();
  
      // #circle4410
      ctx.beginPath();
      ctx.globalAlpha(1.0);
      ctx.miterLimit(4);
      ctx.lineWidth(2.004047);
      ctx.fillStyle(Colours::Black);
      ctx.arc(82.500000, 106.000000, 24.104982, 0.000000, 6.28318531, 1);
      ctx.fill();
    }

    // Loop Marker
    {
      audio::Section<int> &loopSect = module->loopSect;
      if (loopSect.size() >= 0 && loopSect.in > 0 && loopSect.out > 0) {
        ctx.strokeStyle(Colours::LoopMarker);
        ctx.fillStyle(Colours::LoopMarker);

        if (inView.contains(loopSect.in)) {
          ctx.beginPath();
          ctx.circle(timeToCoord(loopSect.in), 190, 3);
          ctx.fill();
        }
        if (inView.contains(loopSect.out)) {
          ctx.beginPath();
          ctx.circle(timeToCoord(loopSect.out), 190, 3);
          ctx.fill();
        }
        if (inView.overlaps(loopSect)) {
          ctx.beginPath();
          ctx.strokeStyle(Colours::LoopMarker);
          ctx.lineWidth(3);
          ctx.moveTo(timeToCoord(std::max<float>(inView.in, loopSect.in)), 190);
          ctx.lineTo(timeToCoord(std::min<float>(inView.out, loopSect.out)), 190);
          ctx.stroke();
        }
      }
    }

    // Tape ends
    {
      ctx.fillStyle(Colours::Black);
      ctx.beginPath();
      ctx.rect(startCoord - 5, 185, 10, 40);
      ctx.rect(endCoord - 5, 185, 10, 40);
      ctx.fill();
    }

    // Proc Graph
    {
      float y = 240 - 81.5 - module->procGraph.clip() * 105;
      module->procGraph.clear();
      ctx.strokeStyle(Colours::Red.dimmed);
      ctx.lineCap(Canvas::LineCap::ROUND);
      ctx.beginPath();
      ctx.moveTo(305, 240 - 81.5 - 105);
      ctx.lineTo(305, y);
      ctx.stroke();
      ctx.strokeStyle(Colours::Red);
      ctx.beginPath();
      ctx.moveTo(305, y);
      ctx.lineTo(305, 240 - 81.5);
      ctx.stroke();
      ctx.fillStyle(Colours::Red);
      ctx.beginPath();
      ctx.circle(305, 240 - 81.5 - module->props.gain.mode.normalize() * 105, 3);
      ctx.fill();
    }

    ctx.restore();

    // #LeftReel
    ctx.save();

    ctx.transform(1.000000, 0.000000, 0.000000, 1.000000, 30, 240 - 105 - 81.5);

    ctx.translate(52.5, 52.5);
    ctx.rotate(rotation);
    ctx.translate(-52.5, -52.5);

    drawReel(ctx, recColor);

    ctx.restore();

    // #RightReel
    ctx.save();

    ctx.transform(1.000000, 0.000000, 0.000000, 1.000000, 185, 240 - 105 - 81.5);

    ctx.translate(52.5, 52.5);
    ctx.rotate(rotation);
    ctx.translate(-52.5, -52.5);

    drawReel(ctx, recColor);

    ctx.restore();

    // #text4304
    TextStyle style;
    style.size = 30;
    style.face = Fonts::Light.face;
    style.color = Colours::White;
    style.hAlign = HorizontalAlign::Center;
    style.vAlign = VerticalAlign::Middle;
    ctx.fillStyle(style);
    ctx.beginPath();
    ctx.fillText(timeStr(), 160, 30);

    // #rect4292
    ctx.beginPath();
    ctx.globalAlpha(1.0);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.strokeStyle(Colours::White);
    ctx.lineWidth(1.5);
    ctx.rect(15, 15, 30, 30);
    ctx.stroke();

    // #text4294
    ctx.fillStyle(style);
    ctx.font(36.0f);
    ctx.beginPath();
    ctx.fillText(std::to_string(module->state.track + 1), 30, 29);

  }

} // top1::module
