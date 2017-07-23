#include "mixer.h"
#include "../ui/utils.h"
#include "../utils.h"
#include "../globals.h"

/**************************************************/
/* MixerModule Implementation                     */
/**************************************************/

MixerModule::MixerModule() :
  Module(&data),
  screen (new MixerScreen(this))
{
}

void MixerModule::display() {
  GLOB.ui.display(screen);
}

// Mixing!

void MixerModule::process(uint nframes) {
  auto &trackBuffer = GLOB.tapedeck.trackBuffer;
  float level[4] = {data.track[0].level, data.track[1].level,
                    data.track[2].level, data.track[3].level};
  float pan[4] = {data.track[0].pan, data.track[1].level,
                  data.track[2].pan, data.track[3].pan};
  for (uint f = 0; f < nframes; f++) {
    float lMix = 0, rMix = 0;
    for (uint t = 0; t < 4 ; t++) {
      if (!data.track[t].muted) {
        lMix += trackBuffer[f][t] * level[t] * (1-pan[t]);
        rMix += trackBuffer[f][t] * level[t] * (1+pan[t]);
      }
      trackGraph[t].add(trackBuffer[f][t] * level[t]);
    }
    GLOB.audioData.outL[f] =
      lMix + GLOB.audioData.proc[f] * GLOB.tapedeck.data.procGain;
    GLOB.audioData.outR[f] =
      rMix + GLOB.audioData.proc[f] * GLOB.tapedeck.data.procGain;
  }
}

/**************************************************/
/* MixerScreen Implementation                     */
/**************************************************/

using namespace drawing;

void MixerScreen::draw(drawing::Canvas& ctx) {

  drawMixerSegment(ctx, 1, 18, 32.5);
  drawMixerSegment(ctx, 2, 93, 32.5);
  drawMixerSegment(ctx, 3, 168, 32.5);
  drawMixerSegment(ctx, 4, 243, 32.5);

}

bool MixerScreen::keypress(ui::Key key) {
  using namespace ui;
  bool shift = GLOB.ui.keys[K_SHIFT];
  switch (key) {
  case K_BLUE_UP:
    if (shift) module->data.track[0].pan++;
    else module->data.track[0].level++;
    return true;
  case K_BLUE_DOWN:
    if (shift) module->data.track[0].pan--;
    else module->data.track[0].level--;
    return true;
  case K_BLUE_CLICK:
    module->data.track[0].muted.toggle();
    return true;
  case K_GREEN_UP:
    if (shift) module->data.track[1].pan++;
    else module->data.track[1].level++;
    return true;
  case K_GREEN_DOWN:
    if (shift) module->data.track[1].pan--;
    else module->data.track[1].level--;
    return true;
  case K_GREEN_CLICK:
    module->data.track[1].muted.toggle();
    return true;
  case K_WHITE_UP:
    if (shift) module->data.track[2].pan++;
    else module->data.track[2].level++;
    return true;
  case K_WHITE_DOWN:
    if (shift) module->data.track[2].pan--;
    else module->data.track[2].level--;
    return true;
  case K_WHITE_CLICK:
    module->data.track[2].muted.toggle();
    return true;
  case K_RED_UP:
    if (shift) module->data.track[3].pan++;
    else module->data.track[3].level++;
    return true;
  case K_RED_DOWN:
    if (shift) module->data.track[3].pan--;
    else module->data.track[3].level--;
    return true;
  case K_RED_CLICK:
    module->data.track[3].muted.toggle();
    return true;
  }
  return false;
}

bool MixerScreen::keyrelease(ui::Key key) {
  using namespace ui;
  return false;
}

void MixerScreen::drawMixerSegment(
  drawing::Canvas& ctx,
  int track,
  float x,
  float y) {

  Colour trackCol;
  switch (track) {
  case 1: trackCol = Colours::Blue; break;
  case 2: trackCol = Colours::Green; break;
  case 3: trackCol = Colours::White; break;
  case 4: trackCol = Colours::Red; break;
  }
  Colour muteCol = (module->data.track[track-1].muted) ? Colours::Red : Colours::Gray60;
  float mix = module->data.track[track-1].level;
  float graph = module->trackGraph[track-1].clip();
  module->trackGraph[track-1].clear();
  float pan = module->data.track[track-1].pan;

  ctx.save();
  ctx.translate(x, y);
  ctx.lineJoin(Canvas::LineJoin::ROUND);
  ctx.lineCap(Canvas::LineCap::ROUND);

  // #DialBG
  ctx.beginPath();
  ctx.globalAlpha(1.0);
  ctx.strokeStyle(Colours::Gray60);
  ctx.lineWidth(2.000000);
  ctx.moveTo(59.033168, 35.301881);
  ctx.bezierCurveTo(59.027768, 19.486571, 46.045611, 6.668541, 30.033168, 6.668541);
  ctx.bezierCurveTo(14.020725, 6.668541, 1.038564, 19.486571, 1.033169, 35.301881);
  ctx.moveTo(30.033167, 6.168541);
  ctx.lineTo(30.033167, 1.137461);
  ctx.stroke();

  // #DialHand
  ctx.beginPath();
  ctx.fillStyle(Colours::White);
  ctx.circle(30, 35, 5);
  ctx.fill();

  float angle = (graph - 1) * M_PI;
  ctx.strokeStyle(Colours::White);
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
  ctx.strokeStyle(Colours::Gray60);
  ctx.lineWidth(2.000000);
  ctx.moveTo(30.000000, 120);
  ctx.lineTo(30.000000, 110);
  ctx.stroke();

  // #PanSliderBG
  ctx.beginPath();
  ctx.strokeStyle(Colours::Gray60);
  ctx.lineWidth(2);
  ctx.moveTo(02, 130);
  ctx.lineTo(58, 130);
  ctx.stroke();

  // #PanSlider
  ctx.beginPath();
  ctx.globalAlpha(1.0);
  ctx.strokeStyle(Colours::White);
  ctx.fillStyle(Colours::Gray60);
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
