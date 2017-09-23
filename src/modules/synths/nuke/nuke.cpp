#include "nuke.hpp"

#include "core/globals.hpp"
#include "core/ui/drawing.hpp"

#include "nuke.faust.h"

namespace top1::modules {

  /*
   * Declarations
   */

  struct PointInRange {
    float min;
    float cur;
    float max;
  };

  struct Knob : ui::drawing::Drawable {

    ui::drawing::Colour colour;
    PointInRange rotation;

    Knob() = default;
    Knob(ui::drawing::Colour c, PointInRange r) : colour (c), rotation (r) {}

    void draw(ui::drawing::Canvas& ctx) override;

  };

  class NukeSynthScreen : public ui::ModuleScreen<NukeSynth> {

    std::array<Knob, 4> knobs = {{
        Knob{ui::drawing::Colours::Blue, {-1.13097, 0.5, M_PI}},
        Knob{ui::drawing::Colours::Green, {-0.376991, 0.5, 3.51858}},
        Knob{ui::drawing::Colours::White, {0, 0.5, M_PI}},
        Knob{ui::drawing::Colours::Red, {-0.565486, 0.5, 0.565486}},
      }};

    void draw_bg(ui::drawing::Canvas& ctx);
    void draw_text(ui::drawing::Canvas& ctx);
    void draw_key(ui::drawing::Canvas& ctx);
    void draw_level_dots(ui::drawing::Canvas& ctx);
    void draw_slider(ui::drawing::Canvas& ctx);
    void draw_knobs(ui::drawing::Canvas& ctx);

    void draw(ui::drawing::Canvas& ctx) override;
    bool keypress(ui::Key key) override;
    void rotary(ui::RotaryEvent e) override;

    public:
    using ui::ModuleScreen<NukeSynth>::ModuleScreen;
  };

  /*
   * NukeSynth
   */

  NukeSynth::NukeSynth() :
    FaustSynthModule (std::make_unique<FAUSTCLASS>(), &props),
      screen (new NukeSynthScreen(this)) {}

  void NukeSynth::display() {
    Globals::ui.display(*screen);
  }

  void NukeSynth::process(const audio::ProcessData& data) {}

  /*
   * NukeSynthScreen
   */

  bool NukeSynthScreen::keypress(ui::Key key) {
    Knob k;
    switch (key) {
    case ui::K_BLUE_CLICK:
      k = knobs[0]; break;
    case ui::K_GREEN_CLICK:
      k = knobs[1]; break;
    case ui::K_WHITE_CLICK:
      k = knobs[2]; break;
    case ui::K_RED_CLICK:
      k = knobs[3]; break;
    default: return false;
    }
    LOGD << "rotation: "
         << (k.rotation.min + ((k.rotation.max - k.rotation.min)
             * k.rotation.cur));
    return true;
  }

  void NukeSynthScreen::rotary(ui::RotaryEvent e) {
    PointInRange& r = [&]() -> PointInRange& {
      switch (e.rotary) {
      case ui::Rotary::Blue:
      return knobs[0].rotation;
      case ui::Rotary::Green:
      return knobs[1].rotation;
      case ui::Rotary::White:
      return knobs[2].rotation;
      case ui::Rotary::Red:
      return knobs[3].rotation;
      }
    }();
    r.cur = std::clamp(r.cur + 0.01f * e.clicks, 0.f, 1.f);
  }


  using namespace ui::drawing;

  void NukeSynthScreen::draw(Canvas &ctx) {
    draw_bg(ctx);
    draw_key(ctx);
    draw_text(ctx);
    draw_level_dots(ctx);
    draw_slider(ctx);
    draw_knobs(ctx);
  }

  void Knob::draw(Canvas& ctx) {
    ctx.rotate(rotation.min + ((rotation.max - rotation.min) * rotation.cur));
    ctx.save();
    ctx.translate(-28.9, -28.5);

    // kNOB/KNOBPOINTER
    ctx.beginPath();
    ctx.moveTo(7.4, 28.5);
    ctx.lineTo(28.9, 28.5);
    ctx.lineWidth(2.0);
    ctx.strokeStyle(colour);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // kNOB/KNOBOUTLINE
    ctx.beginPath();
    ctx.moveTo(44.1, 22.9);
    ctx.lineTo(43.1, 22.9);
    ctx.bezierCurveTo(42.6, 22.9, 42.1, 22.6, 41.9, 22.1);
    ctx.bezierCurveTo(39.5, 17.0, 34.3, 13.4, 28.2, 13.4);
    ctx.bezierCurveTo(22.2, 13.4, 16.9, 17.0, 14.5, 22.1);
    ctx.bezierCurveTo(14.3, 22.6, 13.9, 22.9, 13.4, 22.9);
    ctx.lineTo(13.4, 22.9);
    ctx.bezierCurveTo(13.0, 22.9, 12.6, 23.0, 12.4, 23.3);
    ctx.lineTo(7.4, 27.7);
    ctx.bezierCurveTo(7.0, 28.2, 7.0, 28.8, 7.4, 29.3);
    ctx.lineTo(12.4, 33.7);
    ctx.bezierCurveTo(12.6, 34.0, 13.0, 34.2, 13.4, 34.2);
    ctx.lineTo(13.4, 34.2);
    ctx.bezierCurveTo(13.9, 34.2, 14.3, 34.4, 14.5, 34.9);
    ctx.bezierCurveTo(16.9, 40.1, 22.2, 43.6, 28.2, 43.6);
    ctx.bezierCurveTo(34.3, 43.6, 39.5, 40.1, 41.9, 34.9);
    ctx.bezierCurveTo(42.1, 34.5, 42.6, 34.2, 43.1, 34.2);
    ctx.lineTo(44.1, 34.2);
    ctx.bezierCurveTo(44.8, 34.2, 45.4, 33.6, 45.4, 32.9);
    ctx.lineTo(45.4, 24.1);
    ctx.bezierCurveTo(45.4, 23.4, 44.8, 22.9, 44.1, 22.9);
    ctx.closePath();
    ctx.strokeStyle(Colour::bytes(255, 255, 255));
    ctx.lineCap(Canvas::LineCap::BUTT);
    ctx.lineJoin(Canvas::LineJoin::MITER);
    ctx.miterLimit(10.0);
    ctx.stroke();
    ctx.restore();
  }

  void NukeSynthScreen::draw_knobs(Canvas& ctx) {

    // Bass
    ctx.drawAt({60.8, 92.2}, knobs[0]);

    // Launch
    ctx.drawAt({60.8, 189.1}, knobs[1]);

    // Function
    ctx.drawAt({169.6, 189.1}, knobs[2]);

    // Init
    ctx.drawAt({280.4, 87.5}, knobs[3]);

  }

  void NukeSynthScreen::draw_slider(Canvas& ctx) {
    // mODESLIDER/CIRCLE
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(164.6, 64.0);
    ctx.bezierCurveTo(164.6, 67.2, 162.0, 69.9, 158.7, 69.9);
    ctx.bezierCurveTo(155.5, 69.9, 152.8, 67.2, 152.8, 64.0);
    ctx.bezierCurveTo(152.8, 60.7, 155.5, 58.1, 158.7, 58.1);
    ctx.bezierCurveTo(162.0, 58.1, 164.6, 60.7, 164.6, 64.0);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(255, 255, 255));
    ctx.fill();
    ctx.restore();
  }

  void NukeSynthScreen::draw_level_dots(Canvas& ctx) {
    // lEVELDOTS/6
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(125.8, 210.6);
    ctx.bezierCurveTo(125.8, 212.2, 124.4, 213.6, 122.8, 213.6);
    ctx.bezierCurveTo(121.2, 213.6, 119.9, 212.2, 119.9, 210.6);
    ctx.bezierCurveTo(119.9, 209.0, 121.2, 207.7, 122.8, 207.7);
    ctx.bezierCurveTo(124.4, 207.7, 125.8, 209.0, 125.8, 210.6);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(153, 153, 152));
    ctx.fill();

    // lEVELDOTS/5
    ctx.beginPath();
    ctx.moveTo(125.8, 200.1);
    ctx.bezierCurveTo(125.8, 201.8, 124.4, 203.1, 122.8, 203.1);
    ctx.bezierCurveTo(121.2, 203.1, 119.9, 201.8, 119.9, 200.1);
    ctx.bezierCurveTo(119.9, 198.5, 121.2, 197.2, 122.8, 197.2);
    ctx.bezierCurveTo(124.4, 197.2, 125.8, 198.5, 125.8, 200.1);
    ctx.closePath();
    ctx.fill();

    // lEVELDOTS/4
    ctx.beginPath();
    ctx.moveTo(125.8, 189.7);
    ctx.bezierCurveTo(125.8, 191.3, 124.4, 192.6, 122.8, 192.6);
    ctx.bezierCurveTo(121.2, 192.6, 119.9, 191.3, 119.9, 189.7);
    ctx.bezierCurveTo(119.9, 188.0, 121.2, 186.7, 122.8, 186.7);
    ctx.bezierCurveTo(124.4, 186.7, 125.8, 188.0, 125.8, 189.7);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(38, 43, 95));
    ctx.fill();

    // lEVELDOTS/3
    ctx.beginPath();
    ctx.moveTo(125.8, 179.2);
    ctx.bezierCurveTo(125.8, 180.8, 124.4, 182.1, 122.8, 182.1);
    ctx.bezierCurveTo(121.2, 182.1, 119.9, 180.8, 119.9, 179.2);
    ctx.bezierCurveTo(119.9, 177.5, 121.2, 176.2, 122.8, 176.2);
    ctx.bezierCurveTo(124.4, 176.2, 125.8, 177.5, 125.8, 179.2);
    ctx.closePath();
    ctx.fill();

    // lEVELDOTS/2
    ctx.beginPath();
    ctx.moveTo(125.8, 168.4);
    ctx.bezierCurveTo(125.8, 170.0, 124.4, 171.4, 122.8, 171.4);
    ctx.bezierCurveTo(121.2, 171.4, 119.9, 170.0, 119.9, 168.4);
    ctx.bezierCurveTo(119.9, 166.8, 121.2, 165.5, 122.8, 165.5);
    ctx.bezierCurveTo(124.4, 165.5, 125.8, 166.8, 125.8, 168.4);
    ctx.closePath();
    ctx.fill();

    // lEVELDOTS/1
    ctx.beginPath();
    ctx.moveTo(125.8, 157.9);
    ctx.bezierCurveTo(125.8, 159.5, 124.4, 160.9, 122.8, 160.9);
    ctx.bezierCurveTo(121.2, 160.9, 119.9, 159.6, 119.9, 157.9);
    ctx.bezierCurveTo(119.9, 156.3, 121.2, 155.0, 122.8, 155.0);
    ctx.bezierCurveTo(124.4, 155.0, 125.8, 156.3, 125.8, 157.9);
    ctx.closePath();
    ctx.fill();
    ctx.restore();
  }

  void NukeSynthScreen::draw_text(Canvas& ctx) {
    ctx.save();
    ctx.font(Fonts::Norm);
    ctx.font(16.f);
    ctx.textAlign(TextAlign::Center, TextAlign::Middle);

    // tXT/INIT
    ctx.fillStyle(Colour::bytes(255, 255, 255));
    ctx.fillText("INIT", 280.4, 50.8);

    // tXT/BASS
    ctx.fillStyle(Colours::White);
    ctx.fillText("BASS", 60.8, 39.0);

    // tXT/LNCH
    ctx.fillStyle(Colour::bytes(57, 111, 181));
    ctx.fillText("LAUNCH", 60.8, 221.4);

    // tXT/FNCT
    ctx.fillStyle(Colour::bytes(57, 111, 181));
    ctx.fillText("FUNCTION", 169.6, 221.4);

    // tXT/NUKE  POWER SYNTH
    ctx.font(Fonts::Bold);
    ctx.font(16.f);
    ctx.textAlign(TextAlign::Center, TextAlign::Middle);
    ctx.fillStyle(Colour::bytes(231, 54, 53));
    ctx.fillText("NUKE  ×  POWER SYNTH  ×  NUKE", 160, 17.0);

    ctx.font(Fonts::Bold);
    ctx.font(18.f);
    ctx.textAlign(TextAlign::Left, TextAlign::Baseline);

    // tXT/1
    ctx.fillStyle(Colour::bytes(255, 255, 255));
    ctx.fillText("1", 196.2, 68.6);

    // tXT/0
    ctx.fillStyle(Colour::bytes(231, 54, 53));
    ctx.fillText("0", 196.2, 94.2);

    // tXT/2
    ctx.fillStyle(Colour::bytes(255, 255, 255));
    ctx.fillText("2", 196.2, 118.8);
    ctx.restore();
  }

  void NukeSynthScreen::draw_key(Canvas& ctx) {
    // kEY/KEYOBJECT
    ctx.save();
    ctx.beginPath();

    // kEY/KEYOBJECT/Pad
    ctx.moveTo(285.5, 157.3);
    ctx.bezierCurveTo(288.3, 157.2, 290.5, 155.0, 290.5, 152.2);
    ctx.bezierCurveTo(290.5, 149.4, 288.3, 147.1, 285.5, 147.0);
    ctx.lineTo(278.5, 147.0);
    ctx.bezierCurveTo(275.7, 147.1, 273.5, 149.4, 273.5, 152.2);
    ctx.bezierCurveTo(273.5, 154.9, 275.7, 157.2, 278.5, 157.3);
    ctx.lineTo(279.8, 157.3);
    ctx.lineTo(279.8, 195.7);
    ctx.bezierCurveTo(279.8, 196.2, 280.2, 196.7, 280.8, 196.7);
    ctx.lineTo(283.1, 196.7);
    ctx.bezierCurveTo(283.6, 196.7, 284.1, 196.2, 284.1, 195.7);
    ctx.lineTo(284.1, 191.9);
    ctx.bezierCurveTo(284.1, 191.3, 284.6, 190.8, 285.3, 190.8);
    ctx.lineTo(288.9, 190.8);
    ctx.lineTo(288.9, 187.1);
    ctx.lineTo(286.5, 187.1);
    ctx.lineTo(286.5, 183.9);
    ctx.lineTo(288.9, 183.9);
    ctx.lineTo(288.9, 180.2);
    ctx.lineTo(285.3, 180.2);
    ctx.bezierCurveTo(284.6, 180.2, 284.1, 179.6, 284.1, 179.0);
    ctx.lineTo(284.1, 157.3);
    ctx.lineTo(285.5, 157.3);
    ctx.closePath();

    // kEY/KEYOBJECT/Pad
    ctx.moveTo(277.7, 152.1);
    ctx.lineTo(277.7, 152.1);
    ctx.bezierCurveTo(277.7, 151.2, 278.4, 150.4, 279.4, 150.4);
    ctx.lineTo(284.7, 150.4);
    ctx.bezierCurveTo(285.6, 150.4, 286.4, 151.2, 286.4, 152.1);
    ctx.lineTo(286.4, 152.1);
    ctx.bezierCurveTo(286.4, 153.1, 285.6, 153.8, 284.7, 153.8);
    ctx.lineTo(279.4, 153.8);
    ctx.bezierCurveTo(278.4, 153.8, 277.7, 153.1, 277.7, 152.1);
    ctx.closePath();
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(231, 54, 53));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();
    ctx.restore();
  }

  void NukeSynthScreen::draw_bg(Canvas &ctx) {
    // sTATICBG/left white border
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(14.4, 128.1);
    ctx.lineTo(14.4, 44.9);
    ctx.bezierCurveTo(14.4, 41.7, 17.0, 39.0, 20.2, 39.0);
    ctx.lineTo(21.8, 39.0);
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(255, 255, 255));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // sTATICBG/fnct key border
    ctx.beginPath();
    ctx.moveTo(231.0, 216.7);
    ctx.lineTo(233.5, 216.7);
    ctx.bezierCurveTo(237.4, 216.7, 240.6, 213.5, 240.6, 209.7);
    ctx.lineTo(240.6, 112.7);
    ctx.lineTo(246.0, 109.7);
    ctx.strokeStyle(Colour::bytes(38, 43, 95));
    ctx.stroke();

    // sTATICBG/top white border
    ctx.beginPath();
    ctx.moveTo(100.9, 39.0);
    ctx.lineTo(240.6, 39.0);
    ctx.lineTo(240.6, 62.5);
    ctx.lineTo(246.0, 65.5);
    ctx.strokeStyle(Colour::bytes(255, 255, 255));
    ctx.stroke();

    // sTATICBG/lnch fnct border
    ctx.beginPath();
    ctx.moveTo(210.8, 221.4);
    ctx.lineTo(214.2, 221.4);
    ctx.bezierCurveTo(219.3, 221.4, 223.5, 217.2, 223.5, 212.1);
    ctx.lineTo(223.5, 201.1);
    ctx.lineTo(217.1, 201.1);
    ctx.bezierCurveTo(214.7, 201.1, 212.9, 199.0, 213.4, 196.6);
    ctx.bezierCurveTo(213.7, 194.8, 215.4, 193.6, 217.2, 193.6);
    ctx.lineTo(223.5, 193.6);
    ctx.lineTo(223.5, 166.2);
    ctx.lineTo(217.2, 166.2);
    ctx.bezierCurveTo(215.4, 166.2, 213.7, 165.0, 213.4, 163.2);
    ctx.bezierCurveTo(212.9, 160.8, 214.7, 158.7, 217.1, 158.7);
    ctx.lineTo(223.5, 158.7);
    ctx.lineTo(223.5, 150.7);
    ctx.bezierCurveTo(223.5, 145.6, 219.3, 141.4, 214.2, 141.4);
    ctx.lineTo(20.3, 141.4);
    ctx.bezierCurveTo(15.1, 141.4, 11.0, 145.6, 11.0, 150.7);
    ctx.lineTo(11.0, 212.1);
    ctx.bezierCurveTo(11.0, 217.2, 15.1, 221.4, 20.3, 221.4);
    ctx.lineWidth(3.0);
    ctx.strokeStyle(Colour::bytes(38, 43, 95));
    ctx.stroke();

    // sTATICBG/divider line lnch fnct
    ctx.beginPath();
    ctx.moveTo(103.3, 221.4);
    ctx.lineTo(128.1, 221.4);
    ctx.stroke();

    // sTATICBG/lnch meters

    // sTATICBG/lnch meters/line 11
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(86.7, 200.2);
    ctx.lineTo(92.3, 202.7);
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(57, 111, 181));
    ctx.stroke();

    // sTATICBG/lnch meters/line 10
    ctx.beginPath();
    ctx.moveTo(88.9, 189.1);
    ctx.lineTo(95.0, 189.1);
    ctx.strokeStyle(Colour::bytes(38, 43, 95));
    ctx.stroke();

    // sTATICBG/lnch meters/line 9
    ctx.beginPath();
    ctx.moveTo(86.8, 178.0);
    ctx.lineTo(92.5, 175.7);
    ctx.strokeStyle(Colour::bytes(57, 111, 181));
    ctx.stroke();

    // sTATICBG/lnch meters/line 8
    ctx.beginPath();
    ctx.moveTo(80.6, 168.9);
    ctx.lineTo(84.9, 164.6);
    ctx.strokeStyle(Colour::bytes(38, 43, 95));
    ctx.stroke();

    // sTATICBG/lnch meters/line 7
    ctx.beginPath();
    ctx.moveTo(71.3, 162.7);
    ctx.lineTo(73.7, 157.1);
    ctx.strokeStyle(Colour::bytes(57, 111, 181));
    ctx.stroke();

    // sTATICBG/lnch meters/line 6
    ctx.beginPath();
    ctx.moveTo(60.4, 160.7);
    ctx.lineTo(60.4, 154.6);
    ctx.strokeStyle(Colour::bytes(38, 43, 95));
    ctx.stroke();

    // sTATICBG/lnch meters/line 5
    ctx.beginPath();
    ctx.moveTo(49.6, 162.7);
    ctx.lineTo(47.3, 157.1);
    ctx.strokeStyle(Colour::bytes(57, 111, 181));
    ctx.stroke();

    // sTATICBG/lnch meters/line 4
    ctx.beginPath();
    ctx.moveTo(40.4, 169.0);
    ctx.lineTo(36.0, 164.7);
    ctx.strokeStyle(Colour::bytes(38, 43, 95));
    ctx.stroke();

    // sTATICBG/lnch meters/line 3
    ctx.beginPath();
    ctx.moveTo(34.3, 178.0);
    ctx.lineTo(28.6, 175.7);
    ctx.strokeStyle(Colour::bytes(57, 111, 181));
    ctx.stroke();

    // sTATICBG/lnch meters/line 2
    ctx.beginPath();
    ctx.moveTo(32.1, 189.1);
    ctx.lineTo(25.9, 189.1);
    ctx.strokeStyle(Colour::bytes(38, 43, 95));
    ctx.stroke();

    // sTATICBG/lnch meters/line 1
    ctx.beginPath();
    ctx.moveTo(34.0, 199.7);
    ctx.lineTo(28.3, 202.0);
    ctx.strokeStyle(Colour::bytes(57, 111, 181));
    ctx.stroke();

    // sTATICBG/fnct meters
    ctx.restore();

    // sTATICBG/fnct meters/line 5
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(197.7, 189.1);
    ctx.lineTo(203.9, 189.1);
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(57, 111, 181));
    ctx.stroke();

    // sTATICBG/fnct meters/line 4
    ctx.beginPath();
    ctx.moveTo(189.4, 168.9);
    ctx.lineTo(193.7, 164.6);
    ctx.stroke();

    // sTATICBG/fnct meters/line 3
    ctx.beginPath();
    ctx.moveTo(169.2, 160.7);
    ctx.lineTo(169.2, 154.6);
    ctx.stroke();

    // sTATICBG/fnct meters/line 2
    ctx.beginPath();
    ctx.moveTo(149.2, 169.0);
    ctx.lineTo(144.9, 164.7);
    ctx.stroke();

    // sTATICBG/fnct meters/line 1
    ctx.beginPath();
    ctx.moveTo(140.9, 189.1);
    ctx.lineTo(134.8, 189.1);
    ctx.stroke();

    // sTATICBG/red cross
    ctx.restore();

    // sTATICBG/red cross/line 2
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(233.8, 80.3);
    ctx.lineTo(248.1, 94.6);
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(231, 54, 53));
    ctx.stroke();

    // sTATICBG/red cross/line 1
    ctx.beginPath();
    ctx.moveTo(248.1, 80.3);
    ctx.lineTo(233.8, 94.6);
    ctx.stroke();

    // sTATICBG/nuke border
    ctx.restore();
    ctx.beginPath();
    ctx.moveTo(304.4, 25.1);
    ctx.lineTo(15.5, 25.1);
    ctx.bezierCurveTo(14.3, 25.1, 13.3, 24.1, 13.3, 22.9);
    ctx.lineTo(13.3, 10.7);
    ctx.bezierCurveTo(13.3, 9.4, 14.3, 8.5, 15.5, 8.5);
    ctx.lineTo(304.4, 8.5);
    ctx.bezierCurveTo(305.6, 8.5, 306.6, 9.4, 306.6, 10.7);
    ctx.lineTo(306.6, 22.9);
    ctx.bezierCurveTo(306.6, 24.1, 305.6, 25.1, 304.4, 25.1);
    ctx.closePath();
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(231, 54, 53));
    ctx.lineCap(Canvas::LineCap::BUTT);
    ctx.lineJoin(Canvas::LineJoin::MITER);
    ctx.miterLimit(10.0);
    ctx.stroke();

    // sTATICBG/key border 2
    ctx.beginPath();
    ctx.moveTo(289.7, 218.9);
    ctx.lineTo(274.9, 218.9);
    ctx.bezierCurveTo(265.7, 218.9, 258.3, 211.4, 258.3, 202.2);
    ctx.lineTo(258.3, 141.5);
    ctx.bezierCurveTo(258.3, 132.3, 265.7, 124.9, 274.9, 124.9);
    ctx.lineTo(289.7, 124.9);
    ctx.bezierCurveTo(298.9, 124.9, 306.4, 132.3, 306.4, 141.5);
    ctx.lineTo(306.4, 202.2);
    ctx.bezierCurveTo(306.4, 211.4, 298.9, 218.9, 289.7, 218.9);
    ctx.closePath();
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(38, 43, 95));
    ctx.stroke();

    // sTATICBG/lnch fnt separator
    ctx.beginPath();
    ctx.moveTo(113.9, 152.7);
    ctx.lineTo(113.9, 221.4);
    ctx.lineWidth(3.0);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // sTATICBG/bass modes separator
    ctx.beginPath();
    ctx.moveTo(105.9, 54.9);
    ctx.lineTo(105.9, 123.5);
    ctx.lineWidth(2.0);
    ctx.stroke();

    // sTATICBG/key border 1
    ctx.beginPath();
    ctx.moveTo(290.4, 212.1);
    ctx.lineTo(274.2, 212.1);
    ctx.bezierCurveTo(268.8, 212.1, 264.4, 207.7, 264.4, 202.3);
    ctx.lineTo(264.4, 141.4);
    ctx.bezierCurveTo(264.4, 136.0, 268.8, 131.6, 274.2, 131.6);
    ctx.lineTo(290.4, 131.6);
    ctx.bezierCurveTo(295.8, 131.6, 300.2, 136.0, 300.2, 141.4);
    ctx.lineTo(300.2, 202.3);
    ctx.bezierCurveTo(300.2, 207.7, 295.8, 212.1, 290.4, 212.1);
    ctx.closePath();
    ctx.strokeStyle(Colour::bytes(57, 111, 181));
    ctx.lineCap(Canvas::LineCap::BUTT);
    ctx.lineJoin(Canvas::LineJoin::MITER);
    ctx.miterLimit(10.0);
    ctx.stroke();

    // sTATICBG/bass meters

    // sTATICBG/bass meters/line 4
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(88.9, 92.3);
    ctx.lineTo(95.0, 92.3);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // sTATICBG/bass meters/line 3
    ctx.beginPath();
    ctx.moveTo(80.6, 72.1);
    ctx.lineTo(84.9, 67.8);
    ctx.stroke();

    // sTATICBG/bass meters/line 2
    ctx.beginPath();
    ctx.moveTo(60.4, 63.9);
    ctx.lineTo(60.4, 57.8);
    ctx.stroke();

    // sTATICBG/bass meters/line 1
    ctx.beginPath();
    ctx.moveTo(40.4, 72.2);
    ctx.lineTo(36.0, 67.9);
    ctx.stroke();

    // sTATICBG/bass meters/line 0
    ctx.beginPath();
    ctx.moveTo(32.1, 92.3);
    ctx.lineTo(25.9, 92.3);
    ctx.strokeStyle(Colour::bytes(153, 153, 152));
    ctx.stroke();

    // sTATICBG/bass meters/line 1
    ctx.beginPath();
    ctx.moveTo(34.2, 103.1);
    ctx.lineTo(31.4, 104.2);
    ctx.stroke();

    // sTATICBG/bass meters/line 2
    ctx.beginPath();
    ctx.moveTo(40.4, 112.4);
    ctx.lineTo(38.3, 114.5);
    ctx.stroke();

    // sTATICBG/bass meters/line 3
    ctx.beginPath();
    ctx.moveTo(49.5, 118.5);
    ctx.lineTo(48.3, 121.3);
    ctx.stroke();

    // sTATICBG/key screws
    ctx.restore();

    // sTATICBG/key screws/screw
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(260.6, 123.2);
    ctx.bezierCurveTo(260.6, 124.8, 259.2, 126.2, 257.6, 126.2);
    ctx.bezierCurveTo(255.9, 126.2, 254.5, 124.8, 254.5, 123.2);
    ctx.bezierCurveTo(254.5, 121.5, 255.9, 120.1, 257.6, 120.1);
    ctx.bezierCurveTo(259.2, 120.1, 260.6, 121.5, 260.6, 123.2);
    ctx.closePath();
    ctx.strokeStyle(Colour::bytes(38, 43, 95));
    ctx.stroke();

    // sTATICBG/key screws/screw
    ctx.beginPath();
    ctx.moveTo(310.1, 123.2);
    ctx.bezierCurveTo(310.1, 124.8, 308.8, 126.2, 307.1, 126.2);
    ctx.bezierCurveTo(305.4, 126.2, 304.0, 124.8, 304.0, 123.2);
    ctx.bezierCurveTo(304.0, 121.5, 305.4, 120.1, 307.1, 120.1);
    ctx.bezierCurveTo(308.8, 120.1, 310.1, 121.5, 310.1, 123.2);
    ctx.closePath();
    ctx.stroke();

    // sTATICBG/key screws/screw
    ctx.beginPath();
    ctx.moveTo(304.0, 220.6);
    ctx.bezierCurveTo(304.0, 218.9, 305.4, 217.5, 307.1, 217.5);
    ctx.bezierCurveTo(308.8, 217.5, 310.1, 218.9, 310.1, 220.6);
    ctx.bezierCurveTo(310.1, 222.2, 308.8, 223.6, 307.1, 223.6);
    ctx.bezierCurveTo(305.4, 223.6, 304.0, 222.2, 304.0, 220.6);
    ctx.closePath();
    ctx.stroke();

    // sTATICBG/key screws/screw
    ctx.beginPath();
    ctx.moveTo(254.5, 220.6);
    ctx.bezierCurveTo(254.5, 218.9, 255.9, 217.5, 257.6, 217.5);
    ctx.bezierCurveTo(259.2, 217.5, 260.6, 218.9, 260.6, 220.6);
    ctx.bezierCurveTo(260.6, 222.2, 259.2, 223.6, 257.6, 223.6);
    ctx.bezierCurveTo(255.9, 223.6, 254.5, 222.2, 254.5, 220.6);
    ctx.closePath();
    ctx.stroke();

    // sTATICBG/screw
    ctx.restore();
    ctx.beginPath();
    ctx.moveTo(220.2, 163.2);
    ctx.bezierCurveTo(220.2, 164.9, 218.9, 166.2, 217.2, 166.2);
    ctx.bezierCurveTo(215.5, 166.2, 214.1, 164.9, 214.1, 163.2);
    ctx.bezierCurveTo(214.1, 161.5, 215.5, 160.2, 217.2, 160.2);
    ctx.bezierCurveTo(218.9, 160.2, 220.2, 161.5, 220.2, 163.2);
    ctx.closePath();
    ctx.stroke();

    // sTATICBG/screw
    ctx.beginPath();
    ctx.moveTo(220.2, 197.9);
    ctx.bezierCurveTo(220.2, 199.6, 218.9, 201.0, 217.2, 201.0);
    ctx.bezierCurveTo(215.5, 201.0, 214.1, 199.6, 214.1, 197.9);
    ctx.bezierCurveTo(214.1, 196.3, 215.5, 194.9, 217.2, 194.9);
    ctx.bezierCurveTo(218.9, 194.9, 220.2, 196.3, 220.2, 197.9);
    ctx.closePath();
    ctx.stroke();

    // sTATICBG/modes border
    ctx.beginPath();
    ctx.moveTo(158.7, 121.6);
    ctx.lineTo(158.7, 121.6);
    ctx.bezierCurveTo(153.0, 121.6, 148.4, 117.0, 148.4, 111.2);
    ctx.lineTo(148.4, 63.7);
    ctx.bezierCurveTo(148.4, 58.0, 153.0, 53.3, 158.7, 53.3);
    ctx.lineTo(158.7, 53.3);
    ctx.bezierCurveTo(164.5, 53.3, 169.1, 58.0, 169.1, 63.7);
    ctx.lineTo(169.1, 111.2);
    ctx.bezierCurveTo(169.1, 117.0, 164.5, 121.6, 158.7, 121.6);
    ctx.closePath();
    ctx.lineWidth(4.0);
    ctx.strokeStyle(Colour::bytes(38, 43, 95));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // sTATICBG/init white line
    ctx.beginPath();
    ctx.moveTo(240.6, 62.5);
    ctx.lineTo(217.2, 62.5);
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(255, 255, 255));
    ctx.stroke();

    // sTATICBG/init blue line
    ctx.beginPath();
    ctx.moveTo(240.6, 112.7);
    ctx.lineTo(217.2, 112.7);
    ctx.strokeStyle(Colour::bytes(38, 43, 95));
    ctx.stroke();

    // sTATICBG/init red line
    ctx.beginPath();
    ctx.moveTo(225.0, 87.5);
    ctx.lineTo(217.2, 87.5);
    ctx.strokeStyle(Colour::bytes(231, 54, 53));
    ctx.stroke();

    // sTATICBG/modes

    // sTATICBG/modes/square
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(134.6, 108.0);
    ctx.lineTo(134.6, 113.9);
    ctx.lineTo(128.7, 113.9);
    ctx.lineTo(128.7, 108.0);
    ctx.lineTo(122.8, 108.0);
    ctx.lineTo(122.8, 113.9);
    ctx.strokeStyle(Colour::bytes(110, 182, 66));
    ctx.stroke();

    // sTATICBG/modes/round
    ctx.beginPath();
    ctx.moveTo(134.6, 87.8);
    ctx.bezierCurveTo(134.6, 89.5, 133.3, 90.8, 131.7, 90.8);
    ctx.bezierCurveTo(131.7, 90.8, 128.7, 91.1, 128.7, 87.8);
    ctx.bezierCurveTo(128.7, 86.2, 127.4, 84.9, 125.8, 84.9);
    ctx.bezierCurveTo(124.1, 84.9, 122.8, 86.2, 122.8, 87.8);
    ctx.stroke();

    // sTATICBG/modes/tooth
    ctx.beginPath();
    ctx.moveTo(122.8, 66.2);
    ctx.lineTo(122.8, 60.2);
    ctx.lineTo(134.6, 66.2);
    ctx.stroke();

    // sTATICBG/INIT modes border
    ctx.restore();
    ctx.beginPath();
    ctx.moveTo(221.1, 121.0);
    ctx.bezierCurveTo(221.1, 124.9, 217.9, 128.1, 214.1, 128.1);
    ctx.lineTo(192.0, 128.1);
    ctx.bezierCurveTo(188.2, 128.1, 185.0, 124.9, 185.0, 121.0);
    ctx.lineTo(185.0, 53.8);
    ctx.bezierCurveTo(185.0, 49.9, 188.2, 46.8, 192.0, 46.8);
    ctx.lineTo(214.1, 46.8);
    ctx.bezierCurveTo(217.9, 46.8, 221.1, 49.9, 221.1, 53.8);
    ctx.strokeStyle(Colour::bytes(38, 43, 95));
    ctx.stroke();

    // sTATICBG/screw
    ctx.beginPath();
    ctx.moveTo(24.2, 151.6);
    ctx.bezierCurveTo(24.2, 153.2, 22.8, 154.6, 21.1, 154.6);
    ctx.bezierCurveTo(19.4, 154.6, 18.1, 153.2, 18.1, 151.6);
    ctx.bezierCurveTo(18.1, 149.9, 19.4, 148.5, 21.1, 148.5);
    ctx.bezierCurveTo(22.8, 148.5, 24.2, 149.9, 24.2, 151.6);
    ctx.closePath();
    ctx.lineCap(Canvas::LineCap::BUTT);
    ctx.lineJoin(Canvas::LineJoin::MITER);
    ctx.miterLimit(10.0);
    ctx.stroke();

    // sTATICBG/screw
    ctx.beginPath();
    ctx.moveTo(24.2, 210.7);
    ctx.bezierCurveTo(24.2, 212.3, 22.8, 213.7, 21.1, 213.7);
    ctx.bezierCurveTo(19.4, 213.7, 18.1, 212.3, 18.1, 210.7);
    ctx.bezierCurveTo(18.1, 209.0, 19.4, 207.6, 21.1, 207.6);
    ctx.bezierCurveTo(22.8, 207.6, 24.2, 209.0, 24.2, 210.7);
    ctx.closePath();
    ctx.stroke();
    ctx.restore();
  }
}
