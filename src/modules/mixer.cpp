#include "mixer.h"
#include "../ui/utils.h"
#include "../utils.h"
#include "../globals.h"

/**************************************************/
/* MixerModule Implementation                     */
/**************************************************/

MixerModule::MixerModule() :
  screen (new MixerScreen(this))
{}

void MixerModule::display() {
  GLOB.ui.display(screen);
}

// Getters & Setters

bool MixerModule::trackMuted(int track) const {
  return trackInfo[track-1].muted;
}
bool MixerModule::trackMuted(int track, bool newVal) {
  return trackInfo[track-1].muted = newVal;
}

float MixerModule::trackPan(int track) const {
  return trackInfo[track-1].pan;
}
float MixerModule::trackPan(int track, float newVal) {
  return trackInfo[track-1].pan
    = top::withBounds(-0.9, 0.9, top::round(newVal, 1));
}

float MixerModule::trackLevel(int track) const {
  return trackInfo[track-1].level;
}
float MixerModule::trackLevel(int track, float newVal) {
  return trackInfo[track-1].level
    = top::withBounds(0, 0.99, top::round(newVal, 2));
}

// Mixing!

void MixerModule::process(uint nframes) {
  auto &trackBuffer = GLOB.tapedeck.trackBuffer;
  // TODO: Configurable and all that
  for (uint f = 0; f < nframes; f++) {
    float lMix = 0, rMix = 0;
    for (uint t = 0; t < 4 ; t++) {
      if (!trackInfo[t].muted) {
        lMix += trackBuffer[f][t] * trackInfo[t].level * (1-trackInfo[t].pan) / 2;
        rMix += trackBuffer[f][t] * trackInfo[t].level * (1+trackInfo[t].pan) / 2;
      }
    }
    GLOB.audioData.outL[f] = top::audio::mix(lMix, GLOB.audioData.proc[f]);
    GLOB.audioData.outR[f] = top::audio::mix(rMix, GLOB.audioData.proc[f]);
  }
}

/**************************************************/
/* MixerScreen Implementation                     */
/**************************************************/

using namespace drawing;

void MixerScreen::draw(NanoCanvas::Canvas& ctx) {

  drawMixerSegment(ctx, 1, 18, 32.5);
  drawMixerSegment(ctx, 2, 93, 32.5);
  drawMixerSegment(ctx, 3, 168, 32.5);
  drawMixerSegment(ctx, 4, 243, 32.5);

}

bool MixerScreen::keypress(ui::Key key) {
  using namespace ui;
  bool shift = GLOB.ui.keys[K_SHIFT];
  switch (key) {
  case K_RED_UP:
    if (shift) module->panRight(1);
    else module->levelUp(1);
    return true;
  case K_RED_DOWN:
    if (shift) module->panLeft(1);
    else module->levelDown(1);
    return true;
  case K_RED_CLICK: module->toggleMute(1); return true;

  case K_BLUE_UP:
    if (shift) module->panRight(2);
    else module->levelUp(2);
    return true;
  case K_BLUE_DOWN:
    if (shift) module->panLeft(2);
    else module->levelDown(2);
    return true;
  case K_BLUE_CLICK: module->toggleMute(2); return true;

  case K_WHITE_UP:
    if (shift) module->panRight(3);
    else module->levelUp(3);
    return true;
  case K_WHITE_DOWN:
    if (shift) module->panLeft(3);
    else module->levelDown(3);
    return true;
  case K_WHITE_CLICK: module->toggleMute(3); return true;

  case K_GREEN_UP:
    if (shift) module->panRight(4);
    else module->levelUp(4);
    return true;
  case K_GREEN_DOWN:
    if (shift) module->panLeft(4);
    else module->levelDown(4);
    return true;
  case K_GREEN_CLICK: module->toggleMute(4); return true;
  }
  return false;
}

bool MixerScreen::keyrelease(ui::Key key) {
  using namespace ui;
  return false;
}

void MixerScreen::drawMixerSegment(
  NanoCanvas::Canvas& ctx,
  int track,
  float x,
  float y) {

  Color trackCol;
  switch (track) {
  case 1: trackCol = COLOR_RED; break;
  case 2: trackCol = COLOR_BLUE; break;
  case 3: trackCol = COLOR_WHITE; break;
  case 4: trackCol = COLOR_GREEN; break;
  }
  Color muteCol = (module->trackMuted(track)) ? COLOR_RED : COLOR_GRAY60;
  float mix = module->trackLevel(track);
  float pan = module->trackPan(track);

  ctx.save();
  ctx.translate(x, y);
  ctx.lineJoin(Canvas::LineJoin::ROUND);
  ctx.lineCap(Canvas::LineCap::ROUND);

  // #DialBG
  ctx.beginPath();
  ctx.globalAlpha(1.0);
  ctx.strokeStyle(COLOR_GRAY60);
  ctx.lineWidth(2.000000);
  ctx.moveTo(59.033168, 35.301881);
  ctx.bezierCurveTo(59.027768, 19.486571, 46.045611, 6.668541, 30.033168, 6.668541);
  ctx.bezierCurveTo(14.020725, 6.668541, 1.038564, 19.486571, 1.033169, 35.301881);
  ctx.moveTo(30.033167, 6.168541);
  ctx.lineTo(30.033167, 1.137461);
  ctx.stroke();

  // #DialHand
  ctx.beginPath();
  ctx.fillStyle(COLOR_WHITE);
  ctx.circle(30, 35, 5);
  ctx.fill();

  float angle = (mix - 1) * M_PI;
  ctx.strokeStyle(COLOR_WHITE);
  ctx.lineWidth(2);
  ctx.beginPath();
  ctx.moveTo(30, 35);
  ctx.lineTo(30 + std::cos(angle) * 30, 35 + std::sin(angle) * 30);
  ctx.stroke();

  // #PanTxt
  ctx.lineWidth(1.000000);
  ctx.font(FONT_NORM);
  ctx.font(20);
  ctx.textAlign(TextAlign::Left, TextAlign::Baseline);
  ctx.fillText("L", 5, 120);
  ctx.textAlign(TextAlign::Right, TextAlign::Baseline);
  ctx.fillText("R", 55, 120);

  // #PanSep
  ctx.beginPath();
  ctx.strokeStyle(COLOR_GRAY60);
  ctx.lineWidth(2.000000);
  ctx.moveTo(30.000000, 120);
  ctx.lineTo(30.000000, 110);
  ctx.stroke();

  // #PanSliderBG
  ctx.beginPath();
  ctx.strokeStyle(COLOR_GRAY60);
  ctx.lineWidth(2);
  ctx.moveTo(02, 130);
  ctx.lineTo(58, 130);
  ctx.stroke();

  // #PanSlider
  ctx.beginPath();
  ctx.globalAlpha(1.0);
  ctx.strokeStyle(COLOR_WHITE);
  ctx.fillStyle(COLOR_GRAY60);
  ctx.lineWidth(2.000000);
  ctx.circle(30 + (28 * pan), 130, 3);
  ctx.fill();
  ctx.stroke();

  // #DialNum
  ctx.lineWidth(1);
  ctx.fillStyle(trackCol);
  ctx.font(FONT_LIGHT);
  ctx.font(60);
  ctx.textAlign(TextAlign::Right, TextAlign::Baseline);
  std::string txt;
  if (!GLOB.ui.keys[ui::K_SHIFT]) {
    txt = fmt::format("{:0>2.0f}", mix * 100);
  } else {
    if (int(pan * 10) == 0)
      txt = "C";
    else if (pan < 0)
      txt = fmt::format("{:.0f}L", -pan * 10);
    else if (pan > 0)
      txt = fmt::format("{:.0f}R", pan * 10);
  }
  ctx.fillText(txt, 60, 90);

  // #MuteBG
  ctx.beginPath();
  ctx.globalAlpha(1.0);
  ctx.strokeStyle(muteCol);
  ctx.lineWidth(2.000000);
  ctx.rect(1, 150, 58, 25);
  ctx.stroke();

  // #MuteTxt
  ctx.lineWidth(1.000000);
  ctx.fillStyle(muteCol);
  ctx.font(FONT_NORM);
  ctx.font(20);
  ctx.textAlign(TextAlign::Center, TextAlign::Middle);
  ctx.fillText("MUTE", 30, 162.5);

  ctx.restore();
}
