#include "tape.h"
#include "../audio/jack.h"
#include "../globals.h"
#include <plog/Log.h>
#include <sndfile.hh>
#include <thread>
#include <cmath>
#include <algorithm>
#include <mutex>
#include <condition_variable>

#include "../ui/mainui.h"
#include "../ui/utils.h"

using namespace audio;
using namespace audio::jack;

/************************************************/
/* TapeModule Implementation                    */
/************************************************/

TapeModule::TapeModule() :
  tapeScreen (new TapeScreen(this)),
  track (1),
  recording (false),
  playing (0)
{
  MainUI::getInstance().currentScreen = tapeScreen;
}

// Playback control

void TapeModule::play(float speed) {
  nextSpeed = speed;
  if (recording) {
    playing = speed;
  }
}

void TapeModule::stop() {
  recording = false;
  nextSpeed = 0;
}

void TapeModule::record() {
  recording = true;
  tapeBuffer.cutTape(track);
}

void TapeModule::stopRecord() {
  recording = false;
}

// Spooling and jumping
BarPos TapeModule::closestBar(TapeTime time) {
  double fpb = (GLOB.samplerate)*60/(double)GLOB.project->bpm;
  BarPos prevBar = time/fpb;
  TapeTime prevBarTime = getBarTime(prevBar);
  if (time - prevBarTime > fpb/2) {
    return prevBar + 1;
  }
  return prevBar;
}

TapeTime TapeModule::getBarTime(BarPos bar) {
  double fpb = (GLOB.samplerate)*60/(double)GLOB.project->bpm;
  return bar * fpb;
}

TapeTime TapeModule::getBarTimeRel(BarPos bar) {
  return getBarTime(closestBar(tapeBuffer.position()) + bar);
}

void TapeModule::goToBar(BarPos bar) {
  if (recording) return;
  tapeBuffer.goTo(getBarTime(bar));
}

void TapeModule::goToBarRel(BarPos bars) {
  if (recording) return;
  tapeBuffer.goTo(getBarTimeRel(bars));
}

// Looping

void TapeModule::loopInHere() {
  loopSect.in = tapeBuffer.position();
  if (loopSect.in == loopSect.out) {
    loopSect.in = -1;
    loopSect.out = -1;
  }
  if (loopSect.in > loopSect.out) {
    loopSect.out = loopSect.in;
  }
}

void TapeModule::loopOutHere() {
  loopSect.out = tapeBuffer.position();
  if (loopSect.in == loopSect.out) {
    loopSect.in = -1;
    loopSect.out = -1;
  }
  if (loopSect.in > loopSect.out) {
    loopSect.in = loopSect.out;
  }
  if (loopSect.in < 0) {
    loopSect.in = loopSect.out;
  }
}

void TapeModule::goToLoopIn() {
  if (recording) return;
  if (loopSect.in < 0) return;
  tapeBuffer.goTo(loopSect.in);
}

void TapeModule::goToLoopOut() {
  if (recording) return;
  if (loopSect.out < 0) return;
  tapeBuffer.goTo(loopSect.out);
}


// Audio Processing

void TapeModule::process(uint nframes) {
  // TODO: Linear speed changes are for pussies
  const float diff = nextSpeed - playing;
  if (diff > 0) {
    playing = playing + std::min(0.01f, diff);
  }
  if (diff < 0) {
    playing = playing - std::min(0.01f, -diff);
  }

  static bool recLast = false;
  TapeBuffer::TapeSlice slice;

  memset(trackBuffer.data(), 0, sizeof(AudioFrame) * trackBuffer.size());
  if (playing > 0) {
    int rframes = nframes * playing;
    auto data = tapeBuffer.readAllFW(rframes);
    TapeTime pos = tapeBuffer.position();
    int diff = loopSect.out - pos;
    if (looping) {
      //TODO: Probably has some one-off errors
      if (diff > 0 && diff <= rframes) {
        goToLoopIn();
        auto data2 = tapeBuffer.readAllFW(rframes - diff);
        for (uint i = 0; i < data2.size(); i++) {
          data[diff + i] = data2[i];
        }
      }
    }
    if (data.size() != 0) {
      if (data.size() < uint(rframes))
        LOGD << "tape too slow: " << data.size() << " of " << rframes;
      for (uint i = 0; i < nframes; i++) {
        trackBuffer[i] = data[(int)i * (float)data.size()/((float)nframes)];
      }
    }
    if (recording) {
      std::vector<float> buf;
      //TODO: Probably has some one-off errors
      if (looping && diff > 0 && diff <= rframes) {
        if (!recLast) {
          slice = {pos, pos + diff};
          tapeBuffer.addSlice(slice, track);
        } else {
          slice = tapeBuffer.currentSlice(track);
        }
        for (int i = 0; i < diff; i++) {
          buf.push_back(top::audio::mix(
            trackBuffer[i][track - 1], GLOB.data.in[0][i]));
        }
        tapeBuffer.writeFW(buf, track, slice);
        tapeBuffer.goTo(loopSect.in + (rframes - diff));
        buf.clear();
        if (!recLast) {
          slice = {loopSect.in, loopSect.in + rframes - diff};
          tapeBuffer.addSlice(slice, track);
        } else {
          slice = tapeBuffer.currentSlice(track);
        }
        for (uint i = 0; i < rframes - diff; i++) {
          buf.push_back(top::audio::mix(
            trackBuffer[i][track - 1], GLOB.data.in[0][diff + i]));
        }
        tapeBuffer.writeFW(buf, track, slice);
      } else {
        if (!recLast) {
          slice = {pos, pos + rframes};
          tapeBuffer.addSlice(slice, track);
        } else {
          slice = tapeBuffer.currentSlice(track);
        }
        for (uint i = 0; i < nframes; i++) {
          buf.push_back(top::audio::mix(
            trackBuffer[i][track - 1], GLOB.data.in[0][i]));
        }
        tapeBuffer.writeFW(buf, track, slice);
      }
    }
  }
  if (playing < 0) {
    float speed = -playing;
    auto data = tapeBuffer.readAllBW(nframes * speed);
    if (looping) {
      //TODO: Probably has some one-off errors
      TapeTime pos = tapeBuffer.position();
      int diff = pos - loopSect.in;
      if (diff > 0 && diff <= nframes * speed) {
        goToLoopOut();
        auto data2 = tapeBuffer.readAllBW(nframes * speed - diff);
        for (uint i = 0; i < data2.size(); i++) {
          data[diff + i] = data2[i];
        }
      }
    }
    if (data.size() != 0) {
      if (data.size() < uint (nframes * speed))
        LOGD << "tape too slow: " << data.size() << " of " << nframes * speed;
      for (uint i = 0; i < nframes; i++) {
        trackBuffer[i] = data[(int)i * (float)data.size()/((float)nframes)];
      }
    }
    if (recording) {
      std::vector<float> buf;
      //TODO: Probably has some one-off errors
      TapeTime pos = tapeBuffer.position();
      int diff = pos - loopSect.in;
      if (looping && diff > 0 && diff <= nframes * speed) {
        for (uint i = 0; i < diff; i++) {
          buf.push_back(top::audio::mix(
            trackBuffer[i][track - 1], GLOB.data.in[0][i]));
        }
        tapeBuffer.writeBW(buf, track, slice);
        tapeBuffer.goTo(loopSect.out - (nframes * speed - diff));
        buf.clear();
        for (uint i = 0; i < nframes * speed - diff; i++) {
          buf.push_back(top::audio::mix(
            trackBuffer[i][track - 1], GLOB.data.in[0][diff + i]));
        }
        tapeBuffer.writeBW(buf, track, slice);
      } else {
        for (uint i = 0; i < nframes; i++) {
          buf.push_back(top::audio::mix(
            trackBuffer[i][track - 1], GLOB.data.in[0][i]));
        }
        tapeBuffer.writeBW(buf, track, slice);
      }
    }
  }
  recLast = recording;
}

/************************************************/
/* TapeScreen Implementation                    */
/************************************************/

bool TapeScreen::keypress(ui::Key key, bool shift) {
  switch (key) {
  case ui::K_REC:
    module->record();
    return true;
  case ui::K_TRACK_1:
    module->track = 1;
    return true;
  case ui::K_TRACK_2:
    module->track = 2;
    return true;
  case ui::K_TRACK_3:
    module->track = 3;
    return true;
  case ui::K_TRACK_4:
    module->track = 4;
    return true;
  case ui::K_LEFT:
    if (shift) module->goToBarRel(-1);
    else module->play(-4);
    return true;
  case ui::K_RIGHT:
    if (shift) module->goToBarRel(1);
    else module->play(4);
    return true;
  case ui::K_LOOP:
    module->looping = !module->looping;
    return true;
  case ui::K_LOOP_IN:
    if (shift) module->loopInHere();
    else module->goToLoopIn();
    return true;
  case ui::K_LOOP_OUT:
    if (shift) module->loopOutHere();
    else module->goToLoopOut();
    return true;
  }
  return false;
}

bool TapeScreen::keyrelease(ui::Key key, bool shift) {
  switch (key) {
  case ui::K_REC:
    module->stopRecord();
    return true;
  case ui::K_LEFT:
  case ui::K_RIGHT:
    module->stop();
    return true;
  }
  return false;
}

auto COLOR_TAPE = NanoCanvas::Color(102, 102, 102);

static void drawReel(NanoCanvas::Canvas& ctx, NanoCanvas::Color& recColor) {
  using namespace drawing;
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
	ctx.fillStyle(COLOR_BLACK);
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

void TapeScreen::draw(NanoCanvas::Canvas& ctx) {
  using namespace drawing;
  using namespace NanoCanvas;

  double rotation = (module->tapeBuffer.position()/44100.0);

  auto recColor = (module->recording) ? COLOR_RED : COLOR_WHITE;

  int timeLength = 5 * 44100;

  Section<int> inView;
  inView.in = module->tapeBuffer.position() - timeLength/2;
  inView.out = module->tapeBuffer.position() + timeLength/2;

  int startCoord = 40;
  int endCoord = 280;
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

  // TODO: Real value
  int BPM = GLOB.project->bpm;
  float FPB = 44100.0 * 60.0/((float)BPM);

  // Bar Markers
  {
    int numFirst = std::max<int>(std::ceil(inView.in/FPB), 0);
    float x;
    for (int bn = numFirst; !std::isnan(x = timeToCoord(bn * FPB)); bn++) {
      float y = 190.0;
      ctx.beginPath();
      ctx.strokeStyle(COLOR_BAR_MARKER);
      ctx.moveTo(x, y);
      ctx.lineTo(x, 195);
      ctx.stroke();
    }
  }

  // Tracks
  for(uint t = 0; t < 4; t++) {
    auto slices = module->tapeBuffer.slicesIn(inView, t + 1);
    for (auto slice : slices) {
      Color col;
      if (t + 1 == module->track) {
        if (slice.contains(module->tapeBuffer.position()))
          col = COLOR_CURRENT_SLICE;
        else
          col = COLOR_CURRENT_TRACK;
      } else {
        col = COLOR_OTHER_TRACK;
      }
      if (slice.size() >= 0 && slice.in >= 0 && slice.out >= 0) {
        if (inView.overlaps(slice)) {
          ctx.beginPath();
          ctx.strokeStyle(col);
          ctx.moveTo(timeToCoord(std::max<float>(inView.in, slice.in)), 195 + 5*t);
          ctx.lineTo(timeToCoord(std::min<float>(inView.out, slice.out)), 195 + 5*t);
          ctx.stroke();
        }
      }
    }
  }

  // LoopArrow
  if (module->looping) {
    ctx.beginPath();
    ctx.globalAlpha(1.0);
    ctx.strokeStyle(COLOR_WHITE);
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
    ctx.strokeStyle(COLOR_WHITE);
    ctx.fillStyle(COLOR_WHITE);
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
    ctx.strokeStyle(COLOR_TAPE);
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
    ctx.fillStyle(COLOR_TAPE);
    ctx.arc(82.500000, 106.000000, 41.536888, 0.000000, 6.28318531, 1);
    ctx.fill();
  
    // #ellipse4367
    ctx.beginPath();
    ctx.globalAlpha(1.0);
    ctx.miterLimit(4);
    ctx.lineWidth(1.291101);
    ctx.fillStyle(COLOR_TAPE);
    ctx.arc(237.500000, 106.000020, 32.554844, 0.000000, 6.28318531, 1);
    ctx.fill();
  
    // #circle4376
    ctx.beginPath();
    ctx.globalAlpha(1.0);
    ctx.miterLimit(4);
    ctx.lineWidth(1.291101);
    ctx.fillStyle(COLOR_BLACK);
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
    ctx.fillStyle(COLOR_BLACK);
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
    ctx.fillStyle(COLOR_BLACK);
    ctx.arc(82.500000, 106.000000, 24.104982, 0.000000, 6.28318531, 1);
    ctx.fill();
  }

  // Loop Marker
  {
    Section<int> &loopSect = module->loopSect;
    if (loopSect.size() >= 0 && loopSect.in > 0 && loopSect.out > 0) {
      ctx.strokeStyle(COLOR_LOOP_MARKER);
      ctx.fillStyle(COLOR_LOOP_MARKER);

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
        ctx.strokeStyle(COLOR_LOOP_MARKER);
        ctx.lineWidth(3);
        ctx.moveTo(timeToCoord(std::max<float>(inView.in, loopSect.in)), 190);
        ctx.lineTo(timeToCoord(std::min<float>(inView.out, loopSect.out)), 190);
        ctx.stroke();
      }
    }
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
  style.face = FONT_LIGHT.face;
  style.color = COLOR_WHITE;
  style.hAlign = HorizontalAlign::Center;
  style.vAlign = VerticalAlign::Middle;
	ctx.fillStyle(style);
  ctx.beginPath();
	ctx.fillText(module->tapeBuffer.timeStr(), 160, 30);

  // #rect4292
	ctx.beginPath();
	ctx.globalAlpha(1.0);
	ctx.strokeStyle(recColor);
	ctx.miterLimit(4);
	ctx.lineWidth(2);
	ctx.rect(15, 15, 30, 30);
	ctx.stroke();
	
  // #text4294
	ctx.fillStyle(style);
  ctx.font(36.0f);
  ctx.beginPath();
  ctx.fillText(std::to_string(module->track), 30, 30);
	
}
