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

void TapeModule::play(float speed) {
  nextSpeed = speed;
}

void TapeModule::stop() {
  nextSpeed = 0;
}

/**
 * Mixes two signals.
 * @param A Signal A
 * @param B Signal B
 * @param ratio B:A, amount of B to mix into signal A.
 */
static inline AudioSample mix(AudioSample A, AudioSample B, float ratio = 0.5) {
  return A + (B - A) * ratio;
}

void TapeModule::process(uint nframes) {
  // TODO: Linear speed changes are for pussies
  const float diff = nextSpeed - playing;
  if (diff > 0) {
    playing = playing + std::min(0.01f, diff);
  }
  if (diff < 0) {
    playing = playing - std::min(0.01f, -diff);
  }

  memset(buffer.data(), 0, sizeof(AudioFrame) * buffer.size());
  if (playing > 0) {
    auto data = tapeBuffer.readAllFW(nframes * playing);
    if (data.size() != 0) {
      if (data.size() < nframes * playing)
        LOGD << "tape too slow";
      for (uint i = 0; i < nframes; i++) {
        buffer[i] = data[(int)i * (float)data.size()/((float)nframes)];
      }
    }
    if (recording) {
      std::vector<float> buf;
      for (uint i = 0; i < nframes; i++) {
        buf.push_back(mix(buffer[i][track - 1], GLOB.data.in[0][i]));
      }
      tapeBuffer.writeFW(buf, track);
    }
  }
  if (playing < 0) {
    float speed = -playing;
    auto data = tapeBuffer.readAllBW(nframes * speed);
    if (data.size() != 0) {
      if (data.size() < nframes * speed)
        LOGD << "tape too slow";
      for (uint i = 0; i < nframes; i++) {
        buffer[i] = data[(int)i * (float)data.size()/((float)nframes)];
      }
    }
    if (recording) {
      std::vector<float> buf;
      for (uint i = 0; i < nframes; i++) {
        buf.push_back(mix(buffer[i][track - 1], GLOB.data.in[0][i]));
      }
      tapeBuffer.writeBW(buf, track);
    }
  }

  mixOut(nframes);
}

void TapeModule::mixOut(jack_nframes_t nframes) {
  // TODO: Configurable and all that
  AudioSample mixed;
  for (uint f = 0; f < nframes; f++) {
    mixed = buffer[f][0];
    for (uint t = 1; t < nTracks ; t++) {
      mixed = mix(mixed, buffer[f][t]);
    }
    GLOB.data.outL[f] = GLOB.data.outR[f] = mixed;
  }
}

TapeModule::TapeModule() :
  tapeScreen (new TapeScreen(this)),
  track (1),
  recording (false),
  playing (0)
{
  MainUI::getInstance().currentScreen = tapeScreen;
}

bool TapeScreen::keypress(ui::Key key) {
  switch (key) {
  case ui::K_REC:
    module->recording = true;
    return true;
  case ui::K_PLAY:
    if (module->playing) {
      module->stop();
    } else {
      module->play(1);
    }
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
    module->play(-4);
    return true;
  case ui::K_RIGHT:
    LOGD << "start";
    module->play(4);
    return true;
  }
  return false;
}

bool TapeScreen::keyrelease(ui::Key key) {
  switch (key) {
  case ui::K_REC:
    module->recording = false;
    return true;
  case ui::K_LEFT:
  case ui::K_RIGHT:
    LOGD << "stop";
    module->stop();
    return true;
  }
  return false;
}

static inline void drawTapeReel(NVGcontext *context, NVGcolor recCol) {
  // Group start: LeftReel
  nvgBeginPath(context);
  nvgMoveTo(context, 82.5, 54.50195);
  nvgClosePath(context);
  nvgMoveTo(context, 82.5, 61.11719);
  nvgClosePath(context);
  nvgPathWinding(context, NVG_HOLE);
  nvgMoveTo(context, 82.5, 88.88086);
  nvgClosePath(context);
  nvgPathWinding(context, NVG_HOLE);
  nvgMoveTo(context, 82.5, 92.39648);
  nvgClosePath(context);
  nvgPathWinding(context, NVG_HOLE);
  nvgMoveTo(context, 82.5, 103.55469);
  nvgClosePath(context);
  nvgPathWinding(context, NVG_HOLE);
  nvgMoveTo(context, 109.83008, 114.92383);
  nvgClosePath(context);
  nvgPathWinding(context, NVG_HOLE);
  nvgMoveTo(context, 54.451172, 114.92583);
  nvgClosePath(context);
  nvgPathWinding(context, NVG_HOLE);
  nvgFillColor(context, nvgRGBA(0, 0, 0, 255));
  nvgFill(context);
  nvgStrokeColor(context, nvgRGBA(255, 255, 255, 255));
  nvgLineCap(context, NVG_ROUND);
  nvgLineJoin(context, NVG_ROUND);
  nvgMiterLimit(context, 4);
  nvgStrokeWidth(context, 1);
  nvgStroke(context);
  nvgBeginPath(context);
  nvgCircle(context, 116.07142, 148.43364, 51.497978);
  nvgStrokeColor(context, nvgRGBA(255, 255, 255, 255));
  nvgMiterLimit(context, 4);
  nvgStrokeWidth(context, 2.00404716);
  nvgStroke(context);
  // Group end: LeftReel
  // Group start: RightReel
  nvgBeginPath(context);
  nvgMoveTo(context, 237.5, 54.501953);
  nvgClosePath(context);
  nvgMoveTo(context, 237.5, 61.117188);
  nvgClosePath(context);
  nvgPathWinding(context, NVG_HOLE);
  nvgMoveTo(context, 237.5, 88.88086);
  nvgClosePath(context);
  nvgPathWinding(context, NVG_HOLE);
  nvgMoveTo(context, 237.5, 92.39648);
  nvgClosePath(context);
  nvgPathWinding(context, NVG_HOLE);
  nvgMoveTo(context, 237.5, 103.55469);
  nvgClosePath(context);
  nvgPathWinding(context, NVG_HOLE);
  nvgMoveTo(context, 264.83008, 114.92383);
  nvgClosePath(context);
  nvgPathWinding(context, NVG_HOLE);
  nvgMoveTo(context, 209.45117, 114.92583);
  nvgClosePath(context);
  nvgPathWinding(context, NVG_HOLE);
  nvgFillColor(context, nvgRGBA(0, 0, 0, 255));
  nvgFill(context);
  nvgStrokeColor(context, nvgRGBA(255, 255, 255, 255));
  nvgLineCap(context, NVG_ROUND);
  nvgLineJoin(context, NVG_ROUND);
  nvgMiterLimit(context, 4);
  nvgStrokeWidth(context, 1);
  nvgStroke(context);
  nvgBeginPath(context);
  nvgCircle(context, 237.5, 106.00002, 51.497978);
  nvgStrokeColor(context, nvgRGBA(255, 255, 255, 255));
  nvgMiterLimit(context, 4);
  nvgStrokeWidth(context, 2.00404716);
  nvgStroke(context);
  // Group end: RightReel
}

static void drawStaticBackground(NVGcontext *context, NVGcolor recCol) {
  nvgBeginPath(context);
  nvgMoveTo(context, 265.0, 121.0);
  nvgMoveTo(context, 230.0, 174.00004);
  nvgBezierTo(context, 228.65465, 176.06538, 226.59901, 176.83983, 224.95828, 176.56317);
  nvgLineTo(context, 189, 170.50004);
  nvgLineTo(context, 160.0, 170.50004);
  nvgLineTo(context, 131.0, 170.50004);
  nvgBezierTo(context, 131.0, 170.50004, 95.606328, 176.60931, 94.157836, 176.56317);
  nvgBezierTo(context, 92.709345, 176.51707, 91.091326, 176.86715, 89.0, 174.50004);
  nvgLineTo(context, 53.748322, 134.47819);
  nvgStrokeColor(context, nvgRGBA(102, 102, 102, 255));
  nvgLineCap(context, NVG_ROUND);
  nvgLineJoin(context, NVG_ROUND);
  nvgMiterLimit(context, 4);
  nvgStrokeWidth(context, 2);
  nvgStroke(context);
  nvgBeginPath(context);
  nvgCircle(context, 82.5, 106, 41.536888);
  nvgFillColor(context, nvgRGBA(102, 102, 102, 255));
  nvgFill(context);
  nvgBeginPath(context);
  nvgCircle(context, 237.5, 106.00002, 32.554844);
  nvgFillColor(context, nvgRGBA(102, 102, 102, 255));
  nvgFill(context);
  nvgBeginPath(context);
  nvgCircle(context, 237.5, 106.00002, 20.726049);
  nvgFillColor(context, nvgRGBA(0, 0, 0, 255));
  nvgFill(context);
  nvgBeginPath(context);
  nvgEllipse(context, 93.5, 171.50002, 4.545455, 4.5454545);
  nvgStrokeColor(context, nvgRGBA(255, 255, 255, 255));
  nvgMiterLimit(context, 4);
  nvgStrokeWidth(context, 1);
  nvgStroke(context);
  nvgBeginPath(context);
  nvgEllipse(context, 225.5, 171.50002, 4.545455, 4.5454545);
  nvgStrokeColor(context, nvgRGBA(255, 255, 255, 255));
  nvgMiterLimit(context, 4);
  nvgStrokeWidth(context, 1);
  nvgStroke(context);
  nvgBeginPath(context);
  nvgMoveTo(context, 130.49609, 160.49609);
  nvgMoveTo(context, 134.49609, 180.50394);
  nvgMoveTo(context, 185.50391, 180.50394);
  nvgMoveTo(context, 189.50391, 160.49609);
  nvgClosePath(context);
  nvgPathWinding(context, NVG_HOLE);
  nvgMoveTo(context, 160, 181.25584);
  nvgLineTo(context, 160.0, 212.00004);
  nvgClosePath(context);
  nvgPathWinding(context, NVG_HOLE);
  nvgFillColor(context, nvgRGBA(0, 0, 0, 255));
  nvgFill(context);
  nvgStrokeColor(context, nvgRGBA(255, 255, 255, 255));
  nvgLineCap(context, NVG_ROUND);
  nvgLineJoin(context, NVG_ROUND);
  nvgMiterLimit(context, 4);
  nvgStrokeWidth(context, 1.70305741);
  nvgStroke(context);
  nvgBeginPath(context);
  nvgCircle(context, 82.5, 106, 24.104982);
  nvgFillColor(context, nvgRGBA(0, 0, 0, 255));
  nvgFill(context);
  // Group end: StaticBackground
}

void TapeScreen::draw(NVGcontext *context) {
  using namespace drawing;

  double rotation = (module->tapeBuffer.position()/44100.0);

  auto recColor = (module->recording) ? COLOR_RED : COLOR_WHITE;

  drawStaticBackground(context, recColor);

  drawTapeReel(context, recColor);
}
