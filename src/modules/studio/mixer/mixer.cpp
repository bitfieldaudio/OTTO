#include "mixer.hpp"
#include "core/ui/drawing.hpp"
#include "core/globals.hpp"
#include "util/timer.hpp"

namespace top1::modules {

  /**************************************************/
  /* MixerModule Implementation                     */
  /**************************************************/

  Mixer::Mixer() :
    Module(&props),
    screen (new MixerScreen(this)) {}

  void Mixer::display() {
    Globals::ui.display(*screen);
  }

  // Mixing!

  void Mixer::process(const audio::ProcessData& data) {
    TIME_SCOPE("Mixer::Process");
    auto &trackBuffer = Globals::tapedeck.trackBuffer;
    auto level = generate_sequence<4>([this] (int n) { return props.tracks[n].level.get(); });
    auto pan = generate_sequence<4>([this] (int n) { return props.tracks[n].pan.get(); });
    // Iterators
    auto outL = std::begin(data.audio.outL);
    auto outR = std::begin(data.audio.outR);
    auto proc = std::begin(data.audio.proc);
    auto trb = std::begin(trackBuffer);
    for (int f = 0; f < data.nframes; ++f, ++outL, ++outR, ++proc, ++trb) {
      float lMix = 0, rMix = 0;
      for (uint t = 0; t < 4 ; t++) {
        if (!props.tracks[t].muted) {
          lMix += (*trb)[t] * level[t] * (1-pan[t]);
          rMix += (*trb)[t] * level[t] * (1+pan[t]);
        }
        graphs[t].add((*trb)[t] * level[t]);
      }
      *outL = lMix + *proc * Globals::tapedeck.props.gain;
      *outR = rMix + *proc * Globals::tapedeck.props.gain;
    }
  }

  /**************************************************/
  /* MixerScreen Implementation                     */
  /**************************************************/

  using namespace ui::drawing;

  void MixerScreen::draw(ui::drawing::Canvas& ctx) {

    drawMixerSegment(ctx, 1, 18, 32.5);
    drawMixerSegment(ctx, 2, 93, 32.5);
    drawMixerSegment(ctx, 3, 168, 32.5);
    drawMixerSegment(ctx, 4, 243, 32.5);

  }

  bool MixerScreen::keypress(ui::Key key) {
    using namespace ui;
    switch (key) {
    case K_BLUE_CLICK:
      module->props.tracks[0].muted.step();
      return true;
    case K_GREEN_CLICK:
      module->props.tracks[1].muted.step();
      return true;
    case K_WHITE_CLICK:
      module->props.tracks[2].muted.step();
      return true;
    case K_RED_CLICK:
      module->props.tracks[3].muted.step();
      return true;
    default:
      return false;
    }
  }

  bool MixerScreen::keyrelease(ui::Key key) {
    using namespace ui;
    return false;
  }

  void MixerScreen::rotary(ui::RotaryEvent e) {
    if (Globals::ui.keys[ui::K_SHIFT]) {
      module->props.tracks[static_cast<int>(e.rotary)].pan.step(e.clicks);
    } else {
      module->props.tracks[static_cast<int>(e.rotary)].level.step(e.clicks);
    }
  }

  void MixerScreen::drawMixerSegment(ui::drawing::Canvas& ctx,
                                     int track, float x, float y) {

    Colour trackCol;
    switch (track) {
    case 1: trackCol = Colours::Blue; break;
    case 2: trackCol = Colours::Green; break;
    case 3: trackCol = Colours::White; break;
    case 4: trackCol = Colours::Red; break;
    }
    Colour muteCol = (module->props.tracks[track-1].muted) ? Colours::Red : Colours::Gray60;
    float mix = module->props.tracks[track-1].level;
    float graph = module->graphs[track-1].clip();
    module->graphs[track-1].clear();
    float pan = module->props.tracks[track-1].pan;

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
      ctx.font(Fonts::Norm);
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
      ctx.moveTo( 2, 130);
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
      ctx.font(Fonts::Light);
      ctx.font(60);
      ctx.textAlign(TextAlign::Center, TextAlign::Baseline);
      std::string txt;
      if (!Globals::ui.keys[ui::K_SHIFT]) {
        txt = fmt::format("{:0>2.0f}", mix * 100);
      } else {
        if (int(pan * 10) == 0)
          txt = "C";
        else if (pan < 0)
          txt = fmt::format("{:.0f}L", -pan * 10);
        else if (pan > 0)
          txt = fmt::format("{:.0f}R", pan * 10);
      }
      ctx.fillText(txt, 30, 90);

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
      ctx.font(Fonts::Norm);
      ctx.font(20);
      ctx.textAlign(TextAlign::Center, TextAlign::Middle);
      ctx.fillText("MUTE", 30, 162.5);

      ctx.restore();
    }

}
