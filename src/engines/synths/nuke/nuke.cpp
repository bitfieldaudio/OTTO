#include "nuke.hpp"

#include "core/globals.hpp"
#include "core/ui/vector_graphics.hpp"

#include "nuke.faust.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  /*
   * Declarations
   */

  struct NukeSynthScreen : EngineScreen<NukeSynth> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<NukeSynth>::EngineScreen;

    void draw_static(Canvas& ctx);
    void draw_power(Canvas& ctx);
    void draw_key(Canvas& ctx);
    void draw_dots(Canvas& ctx);
    void draw_bars(Canvas& ctx);
    void draw_aux(Canvas& ctx);
    void draw_Q(Canvas& ctx);
    void draw_sights(Canvas& ctx);
  };

  // NukeSynth ////////////////////////////////////////////////////////////////

  NukeSynth::NukeSynth()
    : SynthEngine("Nuke", props, std::make_unique<NukeSynthScreen>(this)),
      voice_mgr_(props),
      faust_(std::make_unique<FAUSTCLASS>(), props)
  {}

  audio::ProcessData<1> NukeSynth::process(audio::ProcessData<0> data)
  {
    voice_mgr_.process_before(data);
    auto res = faust_.process(data);
    voice_mgr_.process_after(data);
    return res;
  }

  /*
   * NukeSynthScreen
   */

  bool NukeSynthScreen::keypress(Key key)
  {
    return false;
  }

  void NukeSynthScreen::rotary(RotaryEvent e)
  {
    switch (e.rotary) {
    case Rotary::Blue:
      engine.props.wave.step(e.clicks);
      break;
    case Rotary::Green:
      engine.props.aux.step(e.clicks);
      break;
    case Rotary::White:
      engine.props.relation.step(e.clicks);
      break;
    case Rotary::Red:
      engine.props.filter.step(e.clicks);
      break;
    }
  }

  using namespace ui::vg;

  void NukeSynthScreen::draw(Canvas& ctx)
  {
    draw_static(ctx);
    draw_power(ctx);
    draw_key(ctx);
    draw_dots(ctx);
    draw_bars(ctx);
    draw_aux(ctx);
    draw_Q(ctx);
    draw_sights(ctx);
  }

  void NukeSynthScreen::draw_power(Canvas& ctx)
  {
    float rotation = engine.props.relation.normalize() * M_PI;
    // NUKE/powerdial

    // NUKE/powerdial/dial
    ctx.save();
    ctx.rotateAround(rotation, {170.0, 186.9});
    ctx.beginPath();
    ctx.moveTo(155.7, 186.9);
    ctx.lineTo(170.3, 186.9);
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(250, 184, 10));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();
    ctx.restore();

    // NUKE/powerdial/dot
    ctx.beginPath();
    ctx.moveTo(172.2, 186.9);
    ctx.bezierCurveTo(172.2, 188.2, 171.1, 189.4, 169.7, 189.4);
    ctx.bezierCurveTo(168.3, 189.4, 167.2, 188.2, 167.2, 186.9);
    ctx.bezierCurveTo(167.2, 185.5, 168.3, 184.4, 169.7, 184.4);
    ctx.bezierCurveTo(171.1, 184.4, 172.2, 185.5, 172.2, 186.9);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(250, 184, 10));
    ctx.fill();
  }

  void NukeSynthScreen::draw_key(Canvas& ctx)
  {
    // NUKE/key

    // NUKE/key/key
    ctx.beginPath();

    // NUKE/key/key/Pad
    ctx.moveTo(267.0, 169.2);
    ctx.bezierCurveTo(269.6, 169.1, 271.6, 167.0, 271.6, 164.4);
    ctx.bezierCurveTo(271.6, 161.8, 269.6, 159.7, 267.0, 159.6);
    ctx.lineTo(260.5, 159.7);
    ctx.bezierCurveTo(257.9, 159.7, 255.9, 161.8, 255.9, 164.4);
    ctx.bezierCurveTo(255.9, 167.0, 257.9, 169.1, 260.5, 169.2);
    ctx.lineTo(261.6, 169.2);
    ctx.lineTo(261.6, 204.8);
    ctx.bezierCurveTo(261.6, 205.3, 262.1, 205.7, 262.6, 205.7);
    ctx.lineTo(264.7, 205.7);
    ctx.bezierCurveTo(265.2, 205.7, 265.7, 205.3, 265.7, 204.8);
    ctx.lineTo(265.7, 201.3);
    ctx.bezierCurveTo(265.7, 200.7, 266.2, 200.2, 266.8, 200.2);
    ctx.lineTo(270.2, 200.2);
    ctx.lineTo(270.2, 196.8);
    ctx.lineTo(267.9, 196.8);
    ctx.lineTo(267.9, 193.8);
    ctx.lineTo(270.2, 193.8);
    ctx.lineTo(270.2, 190.4);
    ctx.lineTo(266.8, 190.4);
    ctx.bezierCurveTo(266.2, 190.4, 265.7, 189.9, 265.7, 189.3);
    ctx.lineTo(265.7, 169.2);
    ctx.lineTo(267.0, 169.2);
    ctx.closePath();

    // NUKE/key/key/Pad
    ctx.moveTo(259.7, 164.4);
    ctx.lineTo(259.7, 164.4);
    ctx.bezierCurveTo(259.7, 163.5, 260.4, 162.8, 261.3, 162.8);
    ctx.lineTo(266.2, 162.8);
    ctx.bezierCurveTo(267.1, 162.8, 267.8, 163.5, 267.8, 164.4);
    ctx.lineTo(267.8, 164.4);
    ctx.bezierCurveTo(267.8, 165.2, 267.1, 165.9, 266.2, 165.9);
    ctx.lineTo(261.3, 165.9);
    ctx.bezierCurveTo(260.4, 165.9, 259.7, 165.2, 259.7, 164.4);
    ctx.closePath();
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(234, 164, 200));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();
  }

  void NukeSynthScreen::draw_dots(Canvas& ctx)
  {
    // NUKE/graphEQ

    // NUKE/graphEQ/4
    ctx.beginPath();
    ctx.moveTo(128.2, 177.0);
    ctx.bezierCurveTo(128.2, 178.6, 126.9, 179.9, 125.3, 179.9);
    ctx.bezierCurveTo(123.7, 179.9, 122.4, 178.6, 122.4, 177.0);
    ctx.bezierCurveTo(122.4, 175.3, 123.7, 174.0, 125.3, 174.0);
    ctx.bezierCurveTo(126.9, 174.0, 128.2, 175.3, 128.2, 177.0);
    ctx.closePath();
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(40, 44, 95));
    ctx.stroke();

    // NUKE/graphEQ/3
    ctx.beginPath();
    ctx.moveTo(128.2, 187.4);
    ctx.bezierCurveTo(128.2, 189.1, 126.9, 190.4, 125.3, 190.4);
    ctx.bezierCurveTo(123.7, 190.4, 122.4, 189.1, 122.4, 187.4);
    ctx.bezierCurveTo(122.4, 185.8, 123.7, 184.5, 125.3, 184.5);
    ctx.bezierCurveTo(126.9, 184.5, 128.2, 185.8, 128.2, 187.4);
    ctx.closePath();
    ctx.stroke();

    // NUKE/graphEQ/6
    ctx.beginPath();
    ctx.moveTo(128.2, 155.7);
    ctx.bezierCurveTo(128.2, 157.3, 126.9, 158.7, 125.3, 158.7);
    ctx.bezierCurveTo(123.7, 158.7, 122.4, 157.3, 122.4, 155.7);
    ctx.bezierCurveTo(122.4, 154.1, 123.7, 152.8, 125.3, 152.8);
    ctx.bezierCurveTo(126.9, 152.8, 128.2, 154.1, 128.2, 155.7);
    ctx.closePath();
    ctx.stroke();

    // NUKE/graphEQ/5
    ctx.beginPath();
    ctx.moveTo(128.2, 166.2);
    ctx.bezierCurveTo(128.2, 167.8, 126.9, 169.1, 125.3, 169.1);
    ctx.bezierCurveTo(123.7, 169.1, 122.4, 167.8, 122.4, 166.2);
    ctx.bezierCurveTo(122.4, 164.6, 123.7, 163.3, 125.3, 163.3);
    ctx.bezierCurveTo(126.9, 163.3, 128.2, 164.6, 128.2, 166.2);
    ctx.closePath();
    ctx.stroke();

    // NUKE/graphEQ/2
    ctx.beginPath();
    ctx.moveTo(128.2, 197.9);
    ctx.bezierCurveTo(128.2, 199.5, 126.9, 200.9, 125.3, 200.9);
    ctx.bezierCurveTo(123.7, 200.9, 122.4, 199.6, 122.4, 197.9);
    ctx.bezierCurveTo(122.4, 196.3, 123.7, 195.0, 125.3, 195.0);
    ctx.bezierCurveTo(126.9, 195.0, 128.2, 196.3, 128.2, 197.9);
    ctx.closePath();
    ctx.strokeStyle(Colour::bytes(23, 156, 216));
    ctx.stroke();

    // NUKE/graphEQ/1
    ctx.beginPath();
    ctx.moveTo(128.2, 208.4);
    ctx.bezierCurveTo(128.2, 210.0, 126.9, 211.4, 125.3, 211.4);
    ctx.bezierCurveTo(123.7, 211.4, 122.4, 210.0, 122.4, 208.4);
    ctx.bezierCurveTo(122.4, 206.8, 123.7, 205.5, 125.3, 205.5);
    ctx.bezierCurveTo(126.9, 205.5, 128.2, 206.8, 128.2, 208.4);
    ctx.closePath();
    ctx.stroke();
  }

  void NukeSynthScreen::draw_bars(Canvas& ctx)
  {
    // NUKE/bars
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(231, 63, 99));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);

    // NUKE/bars/1
    ctx.beginPath();
    ctx.moveTo(125.8, 39.3);
    ctx.lineTo(160.3, 39.3);
    ctx.stroke();

    // NUKE/bars/2
    ctx.beginPath();
    ctx.moveTo(168.5, 39.3);
    ctx.lineTo(203.0, 39.3);
    ctx.stroke();

    // NUKE/bars/3
    ctx.beginPath();
    ctx.moveTo(211.2, 39.3);
    ctx.lineTo(245.7, 39.3);
    ctx.stroke();

    // NUKE/bars/4
    ctx.beginPath();
    ctx.moveTo(254.0, 39.3);
    ctx.lineTo(288.5, 39.3);
    ctx.stroke();
  }

  void NukeSynthScreen::draw_aux(Canvas& ctx)
  {
    float rotation = engine.props.aux.normalize() * 1.25 * M_PI;
    // NUKE/aux

    // NUKE/aux/dial
    ctx.save();
    ctx.rotateAround(rotation, {66.9, 187.1});
    ctx.beginPath();
    ctx.moveTo(57.0, 197.1);
    ctx.lineTo(67.4, 187.1);
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(147, 192, 31));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();
    ctx.restore();

    // NUKE/aux/dot
    ctx.beginPath();
    ctx.moveTo(69.4, 187.1);
    ctx.bezierCurveTo(69.4, 188.4, 68.3, 189.6, 66.9, 189.6);
    ctx.bezierCurveTo(65.5, 189.6, 64.4, 188.4, 64.4, 187.1);
    ctx.bezierCurveTo(64.4, 185.7, 65.5, 184.6, 66.9, 184.6);
    ctx.bezierCurveTo(68.3, 184.6, 69.4, 185.7, 69.4, 187.1);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(147, 192, 31));
    ctx.fill();

    // NUKE/aux/number
    ctx.font(Fonts::Bold, 16.0);
    ctx.fillStyle(Colour::bytes(231, 63, 99));
    ctx.textAlign(TextAlign::Center, TextAlign::Baseline);
    ctx.fillText("+4", 90.0, 210.3);
  }

  void NukeSynthScreen::draw_Q(Canvas& ctx)
  {
    float rotation = engine.props.filter.normalize() * M_PI;
    // NUKE/Q

    // NUKE/Q/dial
    ctx.save();
    ctx.rotateAround(rotation, {244.997, 111.064});
    ctx.beginPath();
    ctx.moveTo(219.6, 111.1);
    ctx.lineTo(245.2, 111.1);
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(23, 156, 216));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();
    ctx.restore();

    // NUKE/Q/dot
    ctx.beginPath();
    ctx.moveTo(247.5, 111.1);
    ctx.bezierCurveTo(247.5, 112.4, 246.4, 113.6, 245.0, 113.6);
    ctx.bezierCurveTo(243.6, 113.6, 242.5, 112.4, 242.5, 111.1);
    ctx.bezierCurveTo(242.5, 109.7, 243.6, 108.6, 245.0, 108.6);
    ctx.bezierCurveTo(246.4, 108.6, 247.5, 109.7, 247.5, 111.1);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(23, 156, 216));
    ctx.fill();
  }

  void NukeSynthScreen::draw_sights(Canvas& ctx)
  {
    // NUKE/sights

    // NUKE/sights/box
    ctx.beginPath();
    ctx.moveTo(127.5, 105.6);
    ctx.lineTo(114.0, 105.6);
    ctx.lineTo(114.0, 97.4);
    ctx.lineTo(127.5, 97.4);
    ctx.lineTo(127.5, 105.6);
    ctx.closePath();
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(255, 255, 255));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // NUKE/sights/right line
    ctx.beginPath();
    ctx.moveTo(127.5, 101.5);
    ctx.lineTo(132.5, 101.5);
    ctx.stroke();

    // NUKE/sights/left line
    ctx.beginPath();
    ctx.moveTo(109.0, 101.5);
    ctx.lineTo(114.0, 101.5);
    ctx.stroke();

    // NUKE/sights/top line
    ctx.beginPath();
    ctx.moveTo(120.7, 97.4);
    ctx.lineTo(120.7, 92.4);
    ctx.stroke();

    // NUKE/sights/bottom line
    ctx.beginPath();
    ctx.moveTo(120.7, 110.6);
    ctx.lineTo(120.7, 105.6);
    ctx.stroke();
  }

  /// Called from draw_static
  static void draw_grid(Canvas& ctx);
  void NukeSynthScreen::draw_static(Canvas& ctx)
  {
    // NUKE/bg
    ctx.save();

    // NUKE/border
    ctx.beginPath();
    ctx.moveTo(100.5, 219.2);
    ctx.lineTo(135.4, 219.2);
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(23, 156, 216));
    ctx.stroke();

    // NUKE/border
    ctx.beginPath();
    ctx.moveTo(114.4, 150.5);
    ctx.lineTo(114.4, 219.2);
    ctx.stroke();

    // NUKE/border
    ctx.beginPath();
    ctx.moveTo(203.0, 219.2);
    ctx.lineTo(211.3, 219.2);
    ctx.lineTo(214.8, 219.2);
    ctx.bezierCurveTo(219.9, 219.2, 224.0, 215.0, 224.0, 210.0);
    ctx.lineTo(224.0, 202.3);
    ctx.bezierCurveTo(224.0, 200.5, 222.5, 198.9, 220.6, 198.9);
    ctx.lineTo(217.6, 198.9);
    ctx.bezierCurveTo(214.9, 198.9, 212.9, 196.3, 214.1, 193.5);
    ctx.bezierCurveTo(214.7, 192.1, 216.1, 191.3, 217.5, 191.3);
    ctx.lineTo(220.6, 191.3);
    ctx.bezierCurveTo(222.5, 191.3, 224.0, 189.8, 224.0, 187.9);
    ctx.lineTo(224.0, 167.4);
    ctx.bezierCurveTo(224.0, 165.6, 222.5, 164.0, 220.6, 164.0);
    ctx.lineTo(217.5, 164.0);
    ctx.bezierCurveTo(216.1, 164.0, 214.7, 163.2, 214.1, 161.9);
    ctx.bezierCurveTo(212.9, 159.1, 214.9, 156.4, 217.6, 156.4);
    ctx.lineTo(220.6, 156.4);
    ctx.bezierCurveTo(222.5, 156.4, 224.0, 154.9, 224.0, 153.0);
    ctx.lineTo(224.0, 151.4);
    ctx.bezierCurveTo(224.0, 146.3, 219.9, 142.2, 214.8, 142.2);
    ctx.lineTo(28.6, 142.2);
    ctx.bezierCurveTo(23.6, 142.2, 19.5, 146.3, 19.5, 151.4);
    ctx.lineTo(19.5, 210.0);
    ctx.bezierCurveTo(19.5, 215.0, 23.6, 219.2, 28.6, 219.2);
    ctx.lineTo(39.3, 219.2);
    ctx.stroke();

    // NUKE/powerdial

    // NUKE/powerdial/diallines
    ctx.save();

    // NUKE/powerdial/diallines/1
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(141.4, 186.9);
    ctx.lineTo(135.3, 186.9);
    ctx.strokeStyle(Colour::bytes(48, 55, 57));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // NUKE/powerdial/diallines/4
    ctx.beginPath();
    ctx.moveTo(198.2, 186.9);
    ctx.lineTo(204.4, 186.9);
    ctx.stroke();

    // NUKE/powerdial/diallines/2
    ctx.beginPath();
    ctx.moveTo(155.0, 162.7);
    ctx.lineTo(152.0, 157.3);
    ctx.stroke();

    // NUKE/powerdial/diallines/3
    ctx.beginPath();
    ctx.moveTo(184.3, 162.3);
    ctx.lineTo(187.4, 157.1);
    ctx.stroke();

    // NUKE/powerdial/dot
    ctx.restore();
    ctx.beginPath();
    ctx.moveTo(169.9, 186.9);
    ctx.bezierCurveTo(169.9, 187.0, 169.8, 187.1, 169.7, 187.1);
    ctx.bezierCurveTo(169.6, 187.1, 169.4, 187.0, 169.4, 186.9);
    ctx.bezierCurveTo(169.4, 186.7, 169.6, 186.6, 169.7, 186.6);
    ctx.bezierCurveTo(169.8, 186.6, 169.9, 186.7, 169.9, 186.9);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(250, 184, 10));
    ctx.fill();

    // NUKE/key
    ctx.restore();

    // NUKE/key/border2
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(271.2, 220.6);
    ctx.lineTo(257.4, 220.6);
    ctx.bezierCurveTo(248.2, 220.6, 240.7, 213.2, 240.7, 204.0);
    ctx.lineTo(240.7, 161.3);
    ctx.bezierCurveTo(240.7, 152.1, 248.2, 144.7, 257.4, 144.7);
    ctx.lineTo(271.2, 144.7);
    ctx.bezierCurveTo(280.4, 144.7, 287.9, 152.1, 287.9, 161.3);
    ctx.lineTo(287.9, 204.0);
    ctx.bezierCurveTo(287.9, 213.2, 280.4, 220.6, 271.2, 220.6);
    ctx.closePath();
    ctx.strokeStyle(Colour::bytes(40, 44, 95));
    ctx.stroke();

    // NUKE/key/border1
    ctx.beginPath();
    ctx.moveTo(271.9, 213.9);
    ctx.lineTo(256.7, 213.9);
    ctx.bezierCurveTo(251.3, 213.9, 246.9, 209.5, 246.9, 204.1);
    ctx.lineTo(246.9, 161.2);
    ctx.bezierCurveTo(246.9, 155.8, 251.3, 151.4, 256.7, 151.4);
    ctx.lineTo(271.9, 151.4);
    ctx.bezierCurveTo(277.3, 151.4, 281.7, 155.8, 281.7, 161.2);
    ctx.lineTo(281.7, 204.1);
    ctx.bezierCurveTo(281.7, 209.5, 277.3, 213.9, 271.9, 213.9);
    ctx.closePath();
    ctx.strokeStyle(Colour::bytes(23, 156, 216));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // NUKE/key/screws

    // NUKE/key/screws/4
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(240.1, 143.0);
    ctx.bezierCurveTo(240.1, 144.6, 238.7, 146.0, 237.0, 146.0);
    ctx.bezierCurveTo(235.4, 146.0, 234.0, 144.6, 234.0, 143.0);
    ctx.bezierCurveTo(234.0, 141.3, 235.4, 139.9, 237.0, 139.9);
    ctx.bezierCurveTo(238.7, 139.9, 240.1, 141.3, 240.1, 143.0);
    ctx.closePath();
    ctx.strokeStyle(Colour::bytes(40, 44, 95));
    ctx.lineCap(Canvas::LineCap::BUTT);
    ctx.lineJoin(Canvas::LineJoin::MITER);
    ctx.miterLimit(10.0);
    ctx.stroke();

    // NUKE/key/screws/3
    ctx.beginPath();
    ctx.moveTo(294.6, 143.0);
    ctx.bezierCurveTo(294.6, 144.6, 293.2, 146.0, 291.6, 146.0);
    ctx.bezierCurveTo(289.9, 146.0, 288.5, 144.6, 288.5, 143.0);
    ctx.bezierCurveTo(288.5, 141.3, 289.9, 139.9, 291.6, 139.9);
    ctx.bezierCurveTo(293.2, 139.9, 294.6, 141.3, 294.6, 143.0);
    ctx.closePath();
    ctx.stroke();

    // NUKE/key/screws/2
    ctx.beginPath();
    ctx.moveTo(288.5, 222.4);
    ctx.bezierCurveTo(288.5, 220.7, 289.9, 219.3, 291.6, 219.3);
    ctx.bezierCurveTo(293.2, 219.3, 294.6, 220.7, 294.6, 222.4);
    ctx.bezierCurveTo(294.6, 224.0, 293.2, 225.4, 291.6, 225.4);
    ctx.bezierCurveTo(289.9, 225.4, 288.5, 224.0, 288.5, 222.4);
    ctx.closePath();
    ctx.stroke();

    // NUKE/key/screws/1
    ctx.beginPath();
    ctx.moveTo(234.0, 222.4);
    ctx.bezierCurveTo(234.0, 220.7, 235.4, 219.3, 237.0, 219.3);
    ctx.bezierCurveTo(238.7, 219.3, 240.1, 220.7, 240.1, 222.4);
    ctx.bezierCurveTo(240.1, 224.0, 238.7, 225.4, 237.0, 225.4);
    ctx.bezierCurveTo(235.4, 225.4, 234.0, 224.0, 234.0, 222.4);
    ctx.closePath();
    ctx.stroke();

    // NUKE/screw
    ctx.restore();
    ctx.restore();
    ctx.beginPath();
    ctx.moveTo(220.7, 161.0);
    ctx.bezierCurveTo(220.7, 162.7, 219.4, 164.0, 217.7, 164.0);
    ctx.bezierCurveTo(216.0, 164.0, 214.6, 162.7, 214.6, 161.0);
    ctx.bezierCurveTo(214.6, 159.3, 216.0, 158.0, 217.7, 158.0);
    ctx.bezierCurveTo(219.4, 158.0, 220.7, 159.3, 220.7, 161.0);
    ctx.closePath();

    // NUKE/screw
    ctx.beginPath();
    ctx.moveTo(220.7, 195.7);
    ctx.bezierCurveTo(220.7, 197.4, 219.4, 198.8, 217.7, 198.8);
    ctx.bezierCurveTo(216.0, 198.8, 214.6, 197.4, 214.6, 195.7);
    ctx.bezierCurveTo(214.6, 194.0, 216.0, 192.7, 217.7, 192.7);
    ctx.bezierCurveTo(219.4, 192.7, 220.7, 194.0, 220.7, 195.7);
    ctx.closePath();
    ctx.stroke();

    // NUKE/screw
    ctx.beginPath();
    ctx.moveTo(32.6, 152.4);
    ctx.bezierCurveTo(32.6, 154.0, 31.3, 155.4, 29.6, 155.4);
    ctx.bezierCurveTo(27.9, 155.4, 26.6, 154.0, 26.6, 152.4);
    ctx.bezierCurveTo(26.6, 150.7, 27.9, 149.3, 29.6, 149.3);
    ctx.bezierCurveTo(31.3, 149.3, 32.6, 150.7, 32.6, 152.4);
    ctx.closePath();
    ctx.strokeStyle(Colour::bytes(40, 44, 95));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // NUKE/screw
    ctx.beginPath();
    ctx.moveTo(32.6, 208.4);
    ctx.bezierCurveTo(32.6, 210.1, 31.3, 211.5, 29.6, 211.5);
    ctx.bezierCurveTo(27.9, 211.5, 26.6, 210.1, 26.6, 208.4);
    ctx.bezierCurveTo(26.6, 206.8, 27.9, 205.4, 29.6, 205.4);
    ctx.bezierCurveTo(31.3, 205.4, 32.6, 206.8, 32.6, 208.4);
    ctx.closePath();
    ctx.stroke();

    // NUKE/screw
    ctx.beginPath();
    ctx.moveTo(32.6, 64.4);
    ctx.bezierCurveTo(32.6, 66.0, 31.3, 67.4, 29.6, 67.4);
    ctx.bezierCurveTo(27.9, 67.4, 26.6, 66.0, 26.6, 64.4);
    ctx.bezierCurveTo(26.6, 62.7, 27.9, 61.3, 29.6, 61.3);
    ctx.bezierCurveTo(31.3, 61.3, 32.6, 62.7, 32.6, 64.4);
    ctx.closePath();
    ctx.stroke();

    // NUKE/screw
    ctx.beginPath();
    ctx.moveTo(32.6, 123.4);
    ctx.bezierCurveTo(32.6, 125.1, 31.3, 126.5, 29.6, 126.5);
    ctx.bezierCurveTo(27.9, 126.5, 26.6, 125.1, 26.6, 123.4);
    ctx.bezierCurveTo(26.6, 121.8, 27.9, 120.4, 29.6, 120.4);
    ctx.bezierCurveTo(31.3, 120.4, 32.6, 121.8, 32.6, 123.4);
    ctx.closePath();
    ctx.stroke();

    // NUKE/border
    ctx.beginPath();
    ctx.moveTo(294.5, 45.9);
    ctx.lineTo(119.9, 45.9);
    ctx.bezierCurveTo(116.9, 45.9, 114.4, 43.4, 114.4, 40.4);
    ctx.lineTo(114.4, 23.4);
    ctx.bezierCurveTo(114.4, 20.4, 116.9, 17.9, 119.9, 17.9);
    ctx.lineTo(294.5, 17.9);
    ctx.bezierCurveTo(297.5, 17.9, 300.0, 20.4, 300.0, 23.4);
    ctx.lineTo(300.0, 40.4);
    ctx.bezierCurveTo(300.0, 43.4, 297.5, 45.9, 294.5, 45.9);
    ctx.closePath();
    ctx.stroke();

    // NUKE/border
    ctx.beginPath();
    ctx.moveTo(100.5, 45.9);
    ctx.lineTo(24.9, 45.9);
    ctx.bezierCurveTo(21.9, 45.9, 19.4, 43.4, 19.4, 40.4);
    ctx.lineTo(19.4, 23.4);
    ctx.bezierCurveTo(19.4, 20.4, 21.9, 17.9, 24.9, 17.9);
    ctx.lineTo(100.5, 17.9);
    ctx.bezierCurveTo(103.5, 17.9, 106.0, 20.4, 106.0, 23.4);
    ctx.lineTo(106.0, 40.4);
    ctx.bezierCurveTo(106.0, 43.4, 103.5, 45.9, 100.5, 45.9);
    ctx.closePath();
    ctx.stroke();

    // NUKE/Qborder
    ctx.beginPath();
    ctx.moveTo(209.2, 53.6);
    ctx.lineTo(295.5, 53.6);
    ctx.bezierCurveTo(298.0, 53.6, 300.0, 55.6, 300.0, 58.1);
    ctx.lineTo(300.0, 128.9);
    ctx.bezierCurveTo(300.0, 131.4, 298.0, 133.4, 295.5, 133.4);
    ctx.lineTo(194.2, 133.4);
    ctx.bezierCurveTo(191.8, 133.4, 189.7, 131.4, 189.7, 128.9);
    ctx.lineTo(189.7, 75.3);
    ctx.lineTo(189.7, 57.1);
    ctx.bezierCurveTo(189.7, 55.2, 191.3, 53.6, 193.3, 53.6);
    ctx.lineTo(209.2, 53.6);
    ctx.closePath();
    ctx.stroke();

    // NUKE/aux

    // NUKE/aux/1
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(38.6, 187.1);
    ctx.lineTo(32.4, 187.1);
    ctx.strokeStyle(Colour::bytes(234, 164, 200));
    ctx.stroke();

    // NUKE/aux/3
    ctx.beginPath();
    ctx.moveTo(66.9, 158.7);
    ctx.lineTo(66.9, 152.6);
    ctx.stroke();

    // NUKE/aux/5
    ctx.beginPath();
    ctx.moveTo(95.4, 187.1);
    ctx.lineTo(101.5, 187.1);
    ctx.stroke();

    // NUKE/aux/2
    ctx.beginPath();
    ctx.moveTo(46.9, 167.0);
    ctx.lineTo(42.5, 162.7);
    ctx.strokeStyle(Colour::bytes(48, 55, 57));
    ctx.stroke();

    // NUKE/aux/4
    ctx.beginPath();
    ctx.moveTo(87.1, 166.9);
    ctx.lineTo(91.4, 162.6);
    ctx.stroke();

    // NUKE/aux/2
    ctx.beginPath();
    ctx.moveTo(46.9, 207.2);
    ctx.lineTo(44.8, 209.3);
    ctx.strokeStyle(Colour::bytes(231, 63, 99));
    ctx.stroke();

    // NUKE/aux/1
    ctx.beginPath();
    ctx.moveTo(40.7, 197.8);
    ctx.lineTo(37.8, 199.0);
    ctx.stroke();

    // NUKE/aux/dot
    ctx.beginPath();
    ctx.moveTo(67.1, 187.1);
    ctx.bezierCurveTo(67.1, 187.2, 67.0, 187.3, 66.9, 187.3);
    ctx.bezierCurveTo(66.8, 187.3, 66.6, 187.2, 66.6, 187.1);
    ctx.bezierCurveTo(66.6, 186.9, 66.8, 186.8, 66.9, 186.8);
    ctx.bezierCurveTo(67.0, 186.8, 67.1, 186.9, 67.1, 187.1);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(147, 192, 31));
    ctx.fill();

    // NUKE/POWER
    ctx.restore();
    ctx.font(Fonts::Bold, 21.0);
    ctx.fillStyle(Colour::bytes(231, 63, 99));
    ctx.textAlign(TextAlign::Center, TextAlign::Baseline);
    ctx.fillText("POWER", 169.6, 225.0);

    // NUKE/AUX
    ctx.fillText("AUX", 67.0, 225.0);

    // NUKE/screw
    ctx.beginPath();
    ctx.moveTo(299.6, 64.4);
    ctx.bezierCurveTo(299.6, 66.0, 298.3, 67.4, 296.6, 67.4);
    ctx.bezierCurveTo(294.9, 67.4, 293.6, 66.0, 293.6, 64.4);
    ctx.bezierCurveTo(293.6, 62.7, 294.9, 61.3, 296.6, 61.3);
    ctx.bezierCurveTo(298.3, 61.3, 299.6, 62.7, 299.6, 64.4);
    ctx.closePath();
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(40, 44, 95));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // NUKE/screw
    ctx.beginPath();
    ctx.moveTo(195.6, 64.4);
    ctx.bezierCurveTo(195.6, 66.0, 194.3, 67.4, 192.6, 67.4);
    ctx.bezierCurveTo(190.9, 67.4, 189.6, 66.0, 189.6, 64.4);
    ctx.bezierCurveTo(189.6, 62.7, 190.9, 61.3, 192.6, 61.3);
    ctx.bezierCurveTo(194.3, 61.3, 195.6, 62.7, 195.6, 64.4);
    ctx.closePath();
    ctx.stroke();

    // NUKE/screw
    ctx.beginPath();
    ctx.moveTo(299.6, 123.4);
    ctx.bezierCurveTo(299.6, 125.1, 298.3, 126.5, 296.6, 126.5);
    ctx.bezierCurveTo(294.9, 126.5, 293.6, 125.1, 293.6, 123.4);
    ctx.bezierCurveTo(293.6, 121.8, 294.9, 120.4, 296.6, 120.4);
    ctx.bezierCurveTo(298.3, 120.4, 299.6, 121.8, 299.6, 123.4);
    ctx.closePath();
    ctx.stroke();

    // NUKE/screw
    ctx.beginPath();
    ctx.moveTo(195.6, 123.4);
    ctx.bezierCurveTo(195.6, 125.1, 194.3, 126.5, 192.6, 126.5);
    ctx.bezierCurveTo(190.9, 126.5, 189.6, 125.1, 189.6, 123.4);
    ctx.bezierCurveTo(189.6, 121.8, 190.9, 120.4, 192.6, 120.4);
    ctx.bezierCurveTo(194.3, 120.4, 195.6, 121.8, 195.6, 123.4);
    ctx.closePath();
    ctx.stroke();

    // NUKE/Q

    // NUKE/Q/LO
    ctx.save();
    ctx.font(Fonts::Bold, 18.0);
    ctx.textAlign(TextAlign::Center, TextAlign::Baseline);
    ctx.fillText("LO", 209, 117.4);

    // NUKE/Q/HI
    ctx.fillText("HI", 281, 117.4);

    // NUKE/Q/Q
    ctx.fillStyle(Colour::bytes(40, 44, 95));
    ctx.fillText("Q", 245.0, 80.3);

    // NUKE/Q/dot
    ctx.beginPath();
    ctx.moveTo(245.2, 111.1);
    ctx.bezierCurveTo(245.2, 111.2, 245.1, 111.3, 245.0, 111.3);
    ctx.bezierCurveTo(244.9, 111.3, 244.7, 111.2, 244.7, 111.1);
    ctx.bezierCurveTo(244.7, 110.9, 244.9, 110.8, 245.0, 110.8);
    ctx.bezierCurveTo(245.1, 110.8, 245.2, 110.9, 245.2, 111.1);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(23, 156, 216));
    ctx.fill();

    // NUKE/Q/arrow2

    // NUKE/Q/arrow2/line
    ctx.beginPath();
    ctx.moveTo(251.0, 72.9);
    ctx.bezierCurveTo(262.8, 74.7, 272.9, 81.9, 278.6, 92.0);
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(40, 44, 95));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // NUKE/Q/arrow2/head
    ctx.beginPath();
    ctx.moveTo(274.5, 92.7);
    ctx.lineTo(281.1, 97.1);
    ctx.lineTo(281.6, 89.2);
    ctx.lineTo(274.5, 92.7);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(40, 44, 95));
    ctx.fill();

    // NUKE/Q/arrow1

    // NUKE/Q/arrow1/line
    ctx.beginPath();
    ctx.moveTo(208.9, 97.1);
    ctx.bezierCurveTo(213.0, 86.5, 221.8, 78.1, 232.7, 74.4);
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(40, 44, 95));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // NUKE/Q/arrow1/head
    ctx.beginPath();
    ctx.moveTo(232.6, 78.6);
    ctx.lineTo(238.2, 73.0);
    ctx.lineTo(230.5, 70.9);
    ctx.lineTo(232.6, 78.6);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(40, 44, 95));
    ctx.fill();

    // NUKE/gridborder
    ctx.restore();
    ctx.beginPath();
    ctx.moveTo(177.4, 133.6);
    ctx.lineTo(24.9, 133.6);
    ctx.bezierCurveTo(21.9, 133.6, 19.4, 131.1, 19.4, 128.1);
    ctx.lineTo(19.4, 59.1);
    ctx.bezierCurveTo(19.4, 56.1, 21.9, 53.6, 24.9, 53.6);
    ctx.lineTo(177.4, 53.6);
    ctx.stroke();

    // NUKE/grid
    draw_grid(ctx);

    // NUKE/corner
    ctx.beginPath();
    ctx.moveTo(45.6, 70.1);
    ctx.lineTo(45.6, 64.0);
    ctx.lineTo(51.7, 64.0);
    ctx.strokeStyle(Colour::bytes(23, 156, 216));
    ctx.lineCap(Canvas::LineCap::BUTT);
    ctx.lineJoin(Canvas::LineJoin::MITER);
    ctx.miterLimit(10.0);
    ctx.stroke();

    // NUKE/corner
    ctx.beginPath();
    ctx.moveTo(51.7, 124.1);
    ctx.lineTo(45.6, 124.1);
    ctx.lineTo(45.6, 118.0);
    ctx.stroke();

    // NUKE/corner
    ctx.beginPath();
    ctx.moveTo(166.0, 118.0);
    ctx.lineTo(166.0, 124.1);
    ctx.lineTo(160.0, 124.1);
    ctx.stroke();

    // NUKE/corner
    ctx.beginPath();
    ctx.moveTo(160.0, 64.0);
    ctx.lineTo(166.0, 64.0);
    ctx.lineTo(166.0, 70.1);
    ctx.stroke();

    // NUKE/europe

    // NUKE/europe/DEN
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(124.5, 128.5);
    ctx.bezierCurveTo(124.0, 127.5, 124.8, 126.5, 126.3, 126.3);
    ctx.lineTo(130.6, 125.6);
    ctx.bezierCurveTo(131.3, 125.5, 131.9, 125.2, 132.3, 124.8);
    ctx.lineTo(138.3, 117.3);
    ctx.bezierCurveTo(139.1, 116.3, 141.2, 116.1, 142.5, 116.8);
    ctx.lineTo(144.5, 118.0);
    ctx.bezierCurveTo(145.5, 118.6, 147.1, 118.6, 148.1, 118.0);
    ctx.lineTo(154.9, 114.1);
    ctx.bezierCurveTo(155.4, 113.8, 155.7, 113.3, 155.7, 112.8);
    ctx.lineTo(155.7, 110.6);
    ctx.bezierCurveTo(155.7, 110.1, 155.3, 109.6, 154.6, 109.3);
    ctx.lineTo(140.5, 102.8);
    ctx.bezierCurveTo(140.1, 102.6, 139.8, 102.4, 139.6, 102.2);
    ctx.lineTo(132.3, 92.3);
    ctx.bezierCurveTo(131.9, 91.8, 132.0, 91.3, 132.3, 90.8);
    ctx.lineTo(132.3, 90.8);
    ctx.bezierCurveTo(133.6, 89.3, 131.1, 87.7, 128.8, 88.5);
    ctx.lineTo(124.0, 90.1);
    ctx.bezierCurveTo(123.7, 90.2, 123.4, 90.3, 123.2, 90.5);
    ctx.lineTo(119.3, 93.5);
    ctx.bezierCurveTo(119.0, 93.7, 118.9, 94.0, 118.8, 94.3);
    ctx.lineTo(117.8, 98.2);
    ctx.bezierCurveTo(117.6, 98.8, 117.0, 99.3, 116.2, 99.5);
    ctx.lineTo(108.8, 101.4);
    ctx.bezierCurveTo(108.2, 101.6, 107.5, 101.6, 106.8, 101.5);
    ctx.lineTo(104.6, 100.9);
    ctx.bezierCurveTo(102.5, 100.4, 102.3, 98.5, 104.3, 97.9);
    ctx.lineTo(107.2, 96.8);
    ctx.bezierCurveTo(107.6, 96.7, 108.0, 96.5, 108.2, 96.2);
    ctx.lineTo(114.7, 89.2);
    ctx.bezierCurveTo(115.3, 88.6, 115.1, 87.8, 114.3, 87.2);
    ctx.lineTo(109.5, 84.1);
    ctx.bezierCurveTo(108.5, 83.5, 108.5, 82.5, 109.3, 81.9);
    ctx.lineTo(114.5, 77.6);
    ctx.lineTo(118.8, 74.2);
    ctx.bezierCurveTo(120.3, 72.9, 123.5, 73.6, 123.5, 75.2);
    ctx.lineTo(123.5, 80.5);
    ctx.lineTo(123.5, 84.3);
    ctx.bezierCurveTo(123.5, 85.3, 124.7, 86.0, 126.2, 86.0);
    ctx.lineTo(134.4, 86.0);
    ctx.bezierCurveTo(135.5, 86.0, 136.5, 85.5, 136.9, 84.8);
    ctx.lineTo(139.7, 79.2);
    ctx.bezierCurveTo(139.9, 78.9, 139.9, 78.6, 139.8, 78.4);
    ctx.lineTo(135.7, 66.2);
    ctx.bezierCurveTo(135.7, 66.1, 135.6, 66.0, 135.6, 65.9);
    ctx.lineTo(135.6, 60.7);
    ctx.strokeStyle(Colour::bytes(40, 44, 95));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // NUKE/europe/IT
    ctx.beginPath();
    ctx.moveTo(109.7, 127.3);
    ctx.bezierCurveTo(111.0, 126.8, 111.3, 125.6, 110.4, 124.8);
    ctx.lineTo(102.1, 118.3);
    ctx.lineTo(108.2, 118.9);
    ctx.bezierCurveTo(109.0, 119.0, 109.7, 119.4, 110.1, 119.9);
    ctx.lineTo(116.7, 129.1);
    ctx.stroke();

    // NUKE/europe/SP
    ctx.beginPath();
    ctx.moveTo(75.6, 128.8);
    ctx.lineTo(77.7, 127.8);
    ctx.bezierCurveTo(77.9, 127.6, 78.1, 127.5, 78.3, 127.4);
    ctx.lineTo(84.2, 121.8);
    ctx.bezierCurveTo(84.5, 121.4, 85.1, 121.2, 85.7, 121.1);
    ctx.lineTo(93.8, 119.8);
    ctx.bezierCurveTo(94.8, 119.6, 95.9, 119.8, 96.5, 120.3);
    ctx.lineTo(103.5, 125.7);
    ctx.bezierCurveTo(104.3, 126.3, 104.3, 127.2, 103.6, 127.8);
    ctx.stroke();

    // NUKE/europe/NL
    ctx.beginPath();
    ctx.moveTo(116.1, 60.7);
    ctx.lineTo(90.9, 81.3);
    ctx.bezierCurveTo(90.5, 81.6, 90.3, 82.0, 90.3, 82.3);
    ctx.lineTo(90.3, 89.1);
    ctx.bezierCurveTo(90.3, 90.3, 92.2, 91.1, 93.9, 90.7);
    ctx.lineTo(95.7, 90.2);
    ctx.bezierCurveTo(97.5, 89.8, 99.3, 90.7, 99.3, 91.8);
    ctx.lineTo(99.3, 92.8);
    ctx.bezierCurveTo(99.3, 93.6, 98.5, 94.2, 97.4, 94.4);
    ctx.lineTo(92.2, 95.4);
    ctx.bezierCurveTo(91.1, 95.6, 90.3, 96.3, 90.3, 97.0);
    ctx.lineTo(90.3, 100.2);
    ctx.bezierCurveTo(90.3, 100.6, 90.1, 101.0, 89.7, 101.3);
    ctx.lineTo(78.5, 109.4);
    ctx.bezierCurveTo(78.2, 109.6, 77.8, 109.8, 77.4, 109.9);
    ctx.lineTo(71.7, 111.1);
    ctx.bezierCurveTo(69.9, 111.5, 69.3, 112.9, 70.5, 113.8);
    ctx.lineTo(73.6, 116.1);
    ctx.bezierCurveTo(74.6, 116.8, 74.4, 117.9, 73.3, 118.5);
    ctx.lineTo(68.7, 120.8);
    ctx.bezierCurveTo(68.2, 121.1, 67.7, 121.2, 67.0, 121.2);
    ctx.lineTo(62.6, 121.2);
    ctx.bezierCurveTo(61.1, 121.2, 60.0, 122.0, 60.0, 122.9);
    ctx.lineTo(60.0, 128.6);
    ctx.stroke();

    // NUKE/europe/UK
    ctx.beginPath();
    ctx.moveTo(72.9, 88.3);
    ctx.lineTo(69.8, 92.5);
    ctx.lineTo(75.6, 92.5);
    ctx.lineTo(72.7, 96.8);
    ctx.lineTo(75.6, 101.6);
    ctx.lineTo(72.7, 105.2);
    ctx.lineTo(65.3, 107.5);
    ctx.lineTo(68.0, 103.5);
    ctx.lineTo(67.6, 99.2);
    ctx.bezierCurveTo(67.6, 98.9, 67.5, 98.6, 67.3, 98.3);
    ctx.lineTo(63.1, 92.0);
    ctx.lineTo(72.9, 88.3);
    ctx.closePath();
    ctx.stroke();

    // NUKE/europe/ireland
    ctx.beginPath();
    ctx.moveTo(53.8, 101.3);
    ctx.lineTo(53.8, 101.3);
    ctx.lineTo(60.0, 105.2);
    ctx.lineTo(60.0, 103.4);
    ctx.bezierCurveTo(60.0, 101.4, 56.5, 100.2, 53.8, 101.3);
    ctx.closePath();
    ctx.stroke();
    ctx.restore();

    // NUKE/keyhole
    ctx.beginPath();
    ctx.moveTo(33.1, 91.2);
    ctx.bezierCurveTo(33.1, 89.3, 30.9, 87.8, 28.5, 88.2);
    ctx.bezierCurveTo(27.2, 88.5, 26.1, 89.4, 25.8, 90.5);
    ctx.bezierCurveTo(25.4, 91.7, 26.0, 92.8, 26.9, 93.5);
    ctx.bezierCurveTo(27.4, 93.8, 27.7, 94.2, 27.7, 94.7);
    ctx.lineTo(27.7, 99.6);
    ctx.lineTo(31.1, 99.6);
    ctx.lineTo(31.1, 94.8);
    ctx.bezierCurveTo(31.1, 94.3, 31.3, 93.8, 31.7, 93.5);
    ctx.bezierCurveTo(32.6, 93.0, 33.1, 92.1, 33.1, 91.2);
    ctx.closePath();
    ctx.strokeStyle(Colour::bytes(40, 44, 95));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();
    ctx.restore();
  }

  void draw_grid(Canvas& ctx)
  {
    // NUKE/bg
    ctx.beginPath();

    // NUKE/grid/vertical/1/Samengesteld pad/Pad
    ctx.moveTo(44.6, 126.3);
    ctx.bezierCurveTo(44.6, 125.8, 45.0, 125.3, 45.6, 125.3);
    ctx.lineTo(45.6, 125.3);
    ctx.bezierCurveTo(46.2, 125.3, 46.6, 125.8, 46.6, 126.3);
    ctx.lineTo(46.6, 126.3);
    ctx.bezierCurveTo(46.6, 126.9, 46.2, 127.3, 45.6, 127.3);
    ctx.lineTo(45.6, 127.3);
    ctx.bezierCurveTo(45.0, 127.3, 44.6, 126.9, 44.6, 126.3);
    ctx.closePath();

    // NUKE/grid/vertical/1/Samengesteld pad/Pad
    ctx.moveTo(44.6, 121.3);
    ctx.bezierCurveTo(44.6, 120.8, 45.0, 120.3, 45.6, 120.3);
    ctx.lineTo(45.6, 120.3);
    ctx.bezierCurveTo(46.2, 120.3, 46.6, 120.8, 46.6, 121.3);
    ctx.lineTo(46.6, 121.3);
    ctx.bezierCurveTo(46.6, 121.9, 46.2, 122.3, 45.6, 122.3);
    ctx.lineTo(45.6, 122.3);
    ctx.bezierCurveTo(45.0, 122.3, 44.6, 121.9, 44.6, 121.3);
    ctx.closePath();

    // NUKE/grid/vertical/1/Samengesteld pad/Pad
    ctx.moveTo(44.6, 116.3);
    ctx.bezierCurveTo(44.6, 115.8, 45.0, 115.3, 45.6, 115.3);
    ctx.lineTo(45.6, 115.3);
    ctx.bezierCurveTo(46.2, 115.3, 46.6, 115.8, 46.6, 116.3);
    ctx.lineTo(46.6, 116.3);
    ctx.bezierCurveTo(46.6, 116.9, 46.2, 117.3, 45.6, 117.3);
    ctx.lineTo(45.6, 117.3);
    ctx.bezierCurveTo(45.0, 117.3, 44.6, 116.9, 44.6, 116.3);
    ctx.closePath();

    // NUKE/grid/vertical/1/Samengesteld pad/Pad
    ctx.moveTo(44.6, 111.3);
    ctx.bezierCurveTo(44.6, 110.8, 45.0, 110.3, 45.6, 110.3);
    ctx.lineTo(45.6, 110.3);
    ctx.bezierCurveTo(46.2, 110.3, 46.6, 110.8, 46.6, 111.3);
    ctx.lineTo(46.6, 111.3);
    ctx.bezierCurveTo(46.6, 111.9, 46.2, 112.3, 45.6, 112.3);
    ctx.lineTo(45.6, 112.3);
    ctx.bezierCurveTo(45.0, 112.3, 44.6, 111.9, 44.6, 111.3);
    ctx.closePath();

    // NUKE/grid/vertical/1/Samengesteld pad/Pad
    ctx.moveTo(44.6, 106.3);
    ctx.bezierCurveTo(44.6, 105.8, 45.0, 105.3, 45.6, 105.3);
    ctx.lineTo(45.6, 105.3);
    ctx.bezierCurveTo(46.2, 105.3, 46.6, 105.8, 46.6, 106.3);
    ctx.lineTo(46.6, 106.3);
    ctx.bezierCurveTo(46.6, 106.9, 46.2, 107.3, 45.6, 107.3);
    ctx.lineTo(45.6, 107.3);
    ctx.bezierCurveTo(45.0, 107.3, 44.6, 106.9, 44.6, 106.3);
    ctx.closePath();

    // NUKE/grid/vertical/1/Samengesteld pad/Pad
    ctx.moveTo(44.6, 101.3);
    ctx.bezierCurveTo(44.6, 100.8, 45.0, 100.3, 45.6, 100.3);
    ctx.lineTo(45.6, 100.3);
    ctx.bezierCurveTo(46.2, 100.3, 46.6, 100.8, 46.6, 101.3);
    ctx.lineTo(46.6, 101.3);
    ctx.bezierCurveTo(46.6, 101.9, 46.2, 102.3, 45.6, 102.3);
    ctx.lineTo(45.6, 102.3);
    ctx.bezierCurveTo(45.0, 102.3, 44.6, 101.9, 44.6, 101.3);
    ctx.closePath();

    // NUKE/grid/vertical/1/Samengesteld pad/Pad
    ctx.moveTo(44.6, 96.3);
    ctx.bezierCurveTo(44.6, 95.8, 45.0, 95.3, 45.6, 95.3);
    ctx.lineTo(45.6, 95.3);
    ctx.bezierCurveTo(46.2, 95.3, 46.6, 95.8, 46.6, 96.3);
    ctx.lineTo(46.6, 96.3);
    ctx.bezierCurveTo(46.6, 96.9, 46.2, 97.3, 45.6, 97.3);
    ctx.lineTo(45.6, 97.3);
    ctx.bezierCurveTo(45.0, 97.3, 44.6, 96.9, 44.6, 96.3);
    ctx.closePath();

    // NUKE/grid/vertical/1/Samengesteld pad/Pad
    ctx.moveTo(44.6, 91.3);
    ctx.bezierCurveTo(44.6, 90.8, 45.0, 90.3, 45.6, 90.3);
    ctx.lineTo(45.6, 90.3);
    ctx.bezierCurveTo(46.2, 90.3, 46.6, 90.8, 46.6, 91.3);
    ctx.lineTo(46.6, 91.3);
    ctx.bezierCurveTo(46.6, 91.9, 46.2, 92.3, 45.6, 92.3);
    ctx.lineTo(45.6, 92.3);
    ctx.bezierCurveTo(45.0, 92.3, 44.6, 91.9, 44.6, 91.3);
    ctx.closePath();

    // NUKE/grid/vertical/1/Samengesteld pad/Pad
    ctx.moveTo(44.6, 86.3);
    ctx.bezierCurveTo(44.6, 85.8, 45.0, 85.3, 45.6, 85.3);
    ctx.lineTo(45.6, 85.3);
    ctx.bezierCurveTo(46.2, 85.3, 46.6, 85.8, 46.6, 86.3);
    ctx.lineTo(46.6, 86.3);
    ctx.bezierCurveTo(46.6, 86.9, 46.2, 87.3, 45.6, 87.3);
    ctx.lineTo(45.6, 87.3);
    ctx.bezierCurveTo(45.0, 87.3, 44.6, 86.9, 44.6, 86.3);
    ctx.closePath();

    // NUKE/grid/vertical/1/Samengesteld pad/Pad
    ctx.moveTo(44.6, 81.3);
    ctx.bezierCurveTo(44.6, 80.8, 45.0, 80.3, 45.6, 80.3);
    ctx.lineTo(45.6, 80.3);
    ctx.bezierCurveTo(46.2, 80.3, 46.6, 80.8, 46.6, 81.3);
    ctx.lineTo(46.6, 81.3);
    ctx.bezierCurveTo(46.6, 81.9, 46.2, 82.3, 45.6, 82.3);
    ctx.lineTo(45.6, 82.3);
    ctx.bezierCurveTo(45.0, 82.3, 44.6, 81.9, 44.6, 81.3);
    ctx.closePath();

    // NUKE/grid/vertical/1/Samengesteld pad/Pad
    ctx.moveTo(44.6, 76.3);
    ctx.bezierCurveTo(44.6, 75.8, 45.0, 75.3, 45.6, 75.3);
    ctx.lineTo(45.6, 75.3);
    ctx.bezierCurveTo(46.2, 75.3, 46.6, 75.8, 46.6, 76.3);
    ctx.lineTo(46.6, 76.3);
    ctx.bezierCurveTo(46.6, 76.9, 46.2, 77.3, 45.6, 77.3);
    ctx.lineTo(45.6, 77.3);
    ctx.bezierCurveTo(45.0, 77.3, 44.6, 76.9, 44.6, 76.3);
    ctx.closePath();

    // NUKE/grid/vertical/1/Samengesteld pad/Pad
    ctx.moveTo(44.6, 71.3);
    ctx.bezierCurveTo(44.6, 70.8, 45.0, 70.3, 45.6, 70.3);
    ctx.lineTo(45.6, 70.3);
    ctx.bezierCurveTo(46.2, 70.3, 46.6, 70.8, 46.6, 71.3);
    ctx.lineTo(46.6, 71.3);
    ctx.bezierCurveTo(46.6, 71.9, 46.2, 72.3, 45.6, 72.3);
    ctx.lineTo(45.6, 72.3);
    ctx.bezierCurveTo(45.0, 72.3, 44.6, 71.9, 44.6, 71.3);
    ctx.closePath();

    // NUKE/grid/vertical/1/Samengesteld pad/Pad
    ctx.moveTo(44.6, 66.3);
    ctx.bezierCurveTo(44.6, 65.8, 45.0, 65.3, 45.6, 65.3);
    ctx.lineTo(45.6, 65.3);
    ctx.bezierCurveTo(46.2, 65.3, 46.6, 65.8, 46.6, 66.3);
    ctx.lineTo(46.6, 66.3);
    ctx.bezierCurveTo(46.6, 66.9, 46.2, 67.3, 45.6, 67.3);
    ctx.lineTo(45.6, 67.3);
    ctx.bezierCurveTo(45.0, 67.3, 44.6, 66.9, 44.6, 66.3);
    ctx.closePath();

    // NUKE/grid/vertical/1/Samengesteld pad/Pad
    ctx.moveTo(44.6, 61.3);
    ctx.bezierCurveTo(44.6, 60.8, 45.0, 60.3, 45.6, 60.3);
    ctx.lineTo(45.6, 60.3);
    ctx.bezierCurveTo(46.2, 60.3, 46.6, 60.8, 46.6, 61.3);
    ctx.lineTo(46.6, 61.3);
    ctx.bezierCurveTo(46.6, 61.9, 46.2, 62.3, 45.6, 62.3);
    ctx.lineTo(45.6, 62.3);
    ctx.bezierCurveTo(45.0, 62.3, 44.6, 61.9, 44.6, 61.3);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(40, 44, 95));
    ctx.fill();

    // NUKE/grid/vertical/2

    // NUKE/grid/vertical/2/Samengesteld pad
    ctx.beginPath();

    // NUKE/grid/vertical/2/Samengesteld pad/Pad
    ctx.moveTo(64.6, 126.3);
    ctx.bezierCurveTo(64.6, 125.8, 65.1, 125.3, 65.6, 125.3);
    ctx.lineTo(65.6, 125.3);
    ctx.bezierCurveTo(66.2, 125.3, 66.6, 125.8, 66.6, 126.3);
    ctx.lineTo(66.6, 126.3);
    ctx.bezierCurveTo(66.6, 126.9, 66.2, 127.3, 65.6, 127.3);
    ctx.lineTo(65.6, 127.3);
    ctx.bezierCurveTo(65.1, 127.3, 64.6, 126.9, 64.6, 126.3);
    ctx.closePath();

    // NUKE/grid/vertical/2/Samengesteld pad/Pad
    ctx.moveTo(64.6, 121.3);
    ctx.bezierCurveTo(64.6, 120.8, 65.1, 120.3, 65.6, 120.3);
    ctx.lineTo(65.6, 120.3);
    ctx.bezierCurveTo(66.2, 120.3, 66.6, 120.8, 66.6, 121.3);
    ctx.lineTo(66.6, 121.3);
    ctx.bezierCurveTo(66.6, 121.9, 66.2, 122.3, 65.6, 122.3);
    ctx.lineTo(65.6, 122.3);
    ctx.bezierCurveTo(65.1, 122.3, 64.6, 121.9, 64.6, 121.3);
    ctx.closePath();

    // NUKE/grid/vertical/2/Samengesteld pad/Pad
    ctx.moveTo(64.6, 116.3);
    ctx.bezierCurveTo(64.6, 115.8, 65.1, 115.3, 65.6, 115.3);
    ctx.lineTo(65.6, 115.3);
    ctx.bezierCurveTo(66.2, 115.3, 66.6, 115.8, 66.6, 116.3);
    ctx.lineTo(66.6, 116.3);
    ctx.bezierCurveTo(66.6, 116.9, 66.2, 117.3, 65.6, 117.3);
    ctx.lineTo(65.6, 117.3);
    ctx.bezierCurveTo(65.1, 117.3, 64.6, 116.9, 64.6, 116.3);
    ctx.closePath();

    // NUKE/grid/vertical/2/Samengesteld pad/Pad
    ctx.moveTo(64.6, 111.3);
    ctx.bezierCurveTo(64.6, 110.8, 65.1, 110.3, 65.6, 110.3);
    ctx.lineTo(65.6, 110.3);
    ctx.bezierCurveTo(66.2, 110.3, 66.6, 110.8, 66.6, 111.3);
    ctx.lineTo(66.6, 111.3);
    ctx.bezierCurveTo(66.6, 111.9, 66.2, 112.3, 65.6, 112.3);
    ctx.lineTo(65.6, 112.3);
    ctx.bezierCurveTo(65.1, 112.3, 64.6, 111.9, 64.6, 111.3);
    ctx.closePath();

    // NUKE/grid/vertical/2/Samengesteld pad/Pad
    ctx.moveTo(64.6, 106.3);
    ctx.bezierCurveTo(64.6, 105.8, 65.1, 105.3, 65.6, 105.3);
    ctx.lineTo(65.6, 105.3);
    ctx.bezierCurveTo(66.2, 105.3, 66.6, 105.8, 66.6, 106.3);
    ctx.lineTo(66.6, 106.3);
    ctx.bezierCurveTo(66.6, 106.9, 66.2, 107.3, 65.6, 107.3);
    ctx.lineTo(65.6, 107.3);
    ctx.bezierCurveTo(65.1, 107.3, 64.6, 106.9, 64.6, 106.3);
    ctx.closePath();

    // NUKE/grid/vertical/2/Samengesteld pad/Pad
    ctx.moveTo(64.6, 101.3);
    ctx.bezierCurveTo(64.6, 100.8, 65.1, 100.3, 65.6, 100.3);
    ctx.lineTo(65.6, 100.3);
    ctx.bezierCurveTo(66.2, 100.3, 66.6, 100.8, 66.6, 101.3);
    ctx.lineTo(66.6, 101.3);
    ctx.bezierCurveTo(66.6, 101.9, 66.2, 102.3, 65.6, 102.3);
    ctx.lineTo(65.6, 102.3);
    ctx.bezierCurveTo(65.1, 102.3, 64.6, 101.9, 64.6, 101.3);
    ctx.closePath();

    // NUKE/grid/vertical/2/Samengesteld pad/Pad
    ctx.moveTo(64.6, 96.3);
    ctx.bezierCurveTo(64.6, 95.8, 65.1, 95.3, 65.6, 95.3);
    ctx.lineTo(65.6, 95.3);
    ctx.bezierCurveTo(66.2, 95.3, 66.6, 95.8, 66.6, 96.3);
    ctx.lineTo(66.6, 96.3);
    ctx.bezierCurveTo(66.6, 96.9, 66.2, 97.3, 65.6, 97.3);
    ctx.lineTo(65.6, 97.3);
    ctx.bezierCurveTo(65.1, 97.3, 64.6, 96.9, 64.6, 96.3);
    ctx.closePath();

    // NUKE/grid/vertical/2/Samengesteld pad/Pad
    ctx.moveTo(64.6, 91.3);
    ctx.bezierCurveTo(64.6, 90.8, 65.1, 90.3, 65.6, 90.3);
    ctx.lineTo(65.6, 90.3);
    ctx.bezierCurveTo(66.2, 90.3, 66.6, 90.8, 66.6, 91.3);
    ctx.lineTo(66.6, 91.3);
    ctx.bezierCurveTo(66.6, 91.9, 66.2, 92.3, 65.6, 92.3);
    ctx.lineTo(65.6, 92.3);
    ctx.bezierCurveTo(65.1, 92.3, 64.6, 91.9, 64.6, 91.3);
    ctx.closePath();

    // NUKE/grid/vertical/2/Samengesteld pad/Pad
    ctx.moveTo(64.6, 86.3);
    ctx.bezierCurveTo(64.6, 85.8, 65.1, 85.3, 65.6, 85.3);
    ctx.lineTo(65.6, 85.3);
    ctx.bezierCurveTo(66.2, 85.3, 66.6, 85.8, 66.6, 86.3);
    ctx.lineTo(66.6, 86.3);
    ctx.bezierCurveTo(66.6, 86.9, 66.2, 87.3, 65.6, 87.3);
    ctx.lineTo(65.6, 87.3);
    ctx.bezierCurveTo(65.1, 87.3, 64.6, 86.9, 64.6, 86.3);
    ctx.closePath();

    // NUKE/grid/vertical/2/Samengesteld pad/Pad
    ctx.moveTo(64.6, 81.3);
    ctx.bezierCurveTo(64.6, 80.8, 65.1, 80.3, 65.6, 80.3);
    ctx.lineTo(65.6, 80.3);
    ctx.bezierCurveTo(66.2, 80.3, 66.6, 80.8, 66.6, 81.3);
    ctx.lineTo(66.6, 81.3);
    ctx.bezierCurveTo(66.6, 81.9, 66.2, 82.3, 65.6, 82.3);
    ctx.lineTo(65.6, 82.3);
    ctx.bezierCurveTo(65.1, 82.3, 64.6, 81.9, 64.6, 81.3);
    ctx.closePath();

    // NUKE/grid/vertical/2/Samengesteld pad/Pad
    ctx.moveTo(64.6, 76.3);
    ctx.bezierCurveTo(64.6, 75.8, 65.1, 75.3, 65.6, 75.3);
    ctx.lineTo(65.6, 75.3);
    ctx.bezierCurveTo(66.2, 75.3, 66.6, 75.8, 66.6, 76.3);
    ctx.lineTo(66.6, 76.3);
    ctx.bezierCurveTo(66.6, 76.9, 66.2, 77.3, 65.6, 77.3);
    ctx.lineTo(65.6, 77.3);
    ctx.bezierCurveTo(65.1, 77.3, 64.6, 76.9, 64.6, 76.3);
    ctx.closePath();

    // NUKE/grid/vertical/2/Samengesteld pad/Pad
    ctx.moveTo(64.6, 71.3);
    ctx.bezierCurveTo(64.6, 70.8, 65.1, 70.3, 65.6, 70.3);
    ctx.lineTo(65.6, 70.3);
    ctx.bezierCurveTo(66.2, 70.3, 66.6, 70.8, 66.6, 71.3);
    ctx.lineTo(66.6, 71.3);
    ctx.bezierCurveTo(66.6, 71.9, 66.2, 72.3, 65.6, 72.3);
    ctx.lineTo(65.6, 72.3);
    ctx.bezierCurveTo(65.1, 72.3, 64.6, 71.9, 64.6, 71.3);
    ctx.closePath();

    // NUKE/grid/vertical/2/Samengesteld pad/Pad
    ctx.moveTo(64.6, 66.3);
    ctx.bezierCurveTo(64.6, 65.8, 65.1, 65.3, 65.6, 65.3);
    ctx.lineTo(65.6, 65.3);
    ctx.bezierCurveTo(66.2, 65.3, 66.6, 65.8, 66.6, 66.3);
    ctx.lineTo(66.6, 66.3);
    ctx.bezierCurveTo(66.6, 66.9, 66.2, 67.3, 65.6, 67.3);
    ctx.lineTo(65.6, 67.3);
    ctx.bezierCurveTo(65.1, 67.3, 64.6, 66.9, 64.6, 66.3);
    ctx.closePath();

    // NUKE/grid/vertical/2/Samengesteld pad/Pad
    ctx.moveTo(64.6, 61.3);
    ctx.bezierCurveTo(64.6, 60.8, 65.1, 60.3, 65.6, 60.3);
    ctx.lineTo(65.6, 60.3);
    ctx.bezierCurveTo(66.2, 60.3, 66.6, 60.8, 66.6, 61.3);
    ctx.lineTo(66.6, 61.3);
    ctx.bezierCurveTo(66.6, 61.9, 66.2, 62.3, 65.6, 62.3);
    ctx.lineTo(65.6, 62.3);
    ctx.bezierCurveTo(65.1, 62.3, 64.6, 61.9, 64.6, 61.3);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(40, 44, 95));
    ctx.fill();

    // NUKE/grid/vertical/3

    // NUKE/grid/vertical/3/Samengesteld pad
    ctx.beginPath();

    // NUKE/grid/vertical/3/Samengesteld pad/Pad
    ctx.moveTo(84.6, 126.3);
    ctx.bezierCurveTo(84.6, 125.8, 85.0, 125.3, 85.6, 125.3);
    ctx.lineTo(85.6, 125.3);
    ctx.bezierCurveTo(86.2, 125.3, 86.6, 125.8, 86.6, 126.3);
    ctx.lineTo(86.6, 126.3);
    ctx.bezierCurveTo(86.6, 126.9, 86.2, 127.3, 85.6, 127.3);
    ctx.lineTo(85.6, 127.3);
    ctx.bezierCurveTo(85.0, 127.3, 84.6, 126.9, 84.6, 126.3);
    ctx.closePath();

    // NUKE/grid/vertical/3/Samengesteld pad/Pad
    ctx.moveTo(84.6, 121.3);
    ctx.bezierCurveTo(84.6, 120.8, 85.0, 120.3, 85.6, 120.3);
    ctx.lineTo(85.6, 120.3);
    ctx.bezierCurveTo(86.2, 120.3, 86.6, 120.8, 86.6, 121.3);
    ctx.lineTo(86.6, 121.3);
    ctx.bezierCurveTo(86.6, 121.9, 86.2, 122.3, 85.6, 122.3);
    ctx.lineTo(85.6, 122.3);
    ctx.bezierCurveTo(85.0, 122.3, 84.6, 121.9, 84.6, 121.3);
    ctx.closePath();

    // NUKE/grid/vertical/3/Samengesteld pad/Pad
    ctx.moveTo(84.6, 116.3);
    ctx.bezierCurveTo(84.6, 115.8, 85.0, 115.3, 85.6, 115.3);
    ctx.lineTo(85.6, 115.3);
    ctx.bezierCurveTo(86.2, 115.3, 86.6, 115.8, 86.6, 116.3);
    ctx.lineTo(86.6, 116.3);
    ctx.bezierCurveTo(86.6, 116.9, 86.2, 117.3, 85.6, 117.3);
    ctx.lineTo(85.6, 117.3);
    ctx.bezierCurveTo(85.0, 117.3, 84.6, 116.9, 84.6, 116.3);
    ctx.closePath();

    // NUKE/grid/vertical/3/Samengesteld pad/Pad
    ctx.moveTo(84.6, 111.3);
    ctx.bezierCurveTo(84.6, 110.8, 85.0, 110.3, 85.6, 110.3);
    ctx.lineTo(85.6, 110.3);
    ctx.bezierCurveTo(86.2, 110.3, 86.6, 110.8, 86.6, 111.3);
    ctx.lineTo(86.6, 111.3);
    ctx.bezierCurveTo(86.6, 111.9, 86.2, 112.3, 85.6, 112.3);
    ctx.lineTo(85.6, 112.3);
    ctx.bezierCurveTo(85.0, 112.3, 84.6, 111.9, 84.6, 111.3);
    ctx.closePath();

    // NUKE/grid/vertical/3/Samengesteld pad/Pad
    ctx.moveTo(84.6, 106.3);
    ctx.bezierCurveTo(84.6, 105.8, 85.0, 105.3, 85.6, 105.3);
    ctx.lineTo(85.6, 105.3);
    ctx.bezierCurveTo(86.2, 105.3, 86.6, 105.8, 86.6, 106.3);
    ctx.lineTo(86.6, 106.3);
    ctx.bezierCurveTo(86.6, 106.9, 86.2, 107.3, 85.6, 107.3);
    ctx.lineTo(85.6, 107.3);
    ctx.bezierCurveTo(85.0, 107.3, 84.6, 106.9, 84.6, 106.3);
    ctx.closePath();

    // NUKE/grid/vertical/3/Samengesteld pad/Pad
    ctx.moveTo(84.6, 101.3);
    ctx.bezierCurveTo(84.6, 100.8, 85.0, 100.3, 85.6, 100.3);
    ctx.lineTo(85.6, 100.3);
    ctx.bezierCurveTo(86.2, 100.3, 86.6, 100.8, 86.6, 101.3);
    ctx.lineTo(86.6, 101.3);
    ctx.bezierCurveTo(86.6, 101.9, 86.2, 102.3, 85.6, 102.3);
    ctx.lineTo(85.6, 102.3);
    ctx.bezierCurveTo(85.0, 102.3, 84.6, 101.9, 84.6, 101.3);
    ctx.closePath();

    // NUKE/grid/vertical/3/Samengesteld pad/Pad
    ctx.moveTo(84.6, 96.3);
    ctx.bezierCurveTo(84.6, 95.8, 85.0, 95.3, 85.6, 95.3);
    ctx.lineTo(85.6, 95.3);
    ctx.bezierCurveTo(86.2, 95.3, 86.6, 95.8, 86.6, 96.3);
    ctx.lineTo(86.6, 96.3);
    ctx.bezierCurveTo(86.6, 96.9, 86.2, 97.3, 85.6, 97.3);
    ctx.lineTo(85.6, 97.3);
    ctx.bezierCurveTo(85.0, 97.3, 84.6, 96.9, 84.6, 96.3);
    ctx.closePath();

    // NUKE/grid/vertical/3/Samengesteld pad/Pad
    ctx.moveTo(84.6, 91.3);
    ctx.bezierCurveTo(84.6, 90.8, 85.0, 90.3, 85.6, 90.3);
    ctx.lineTo(85.6, 90.3);
    ctx.bezierCurveTo(86.2, 90.3, 86.6, 90.8, 86.6, 91.3);
    ctx.lineTo(86.6, 91.3);
    ctx.bezierCurveTo(86.6, 91.9, 86.2, 92.3, 85.6, 92.3);
    ctx.lineTo(85.6, 92.3);
    ctx.bezierCurveTo(85.0, 92.3, 84.6, 91.9, 84.6, 91.3);
    ctx.closePath();

    // NUKE/grid/vertical/3/Samengesteld pad/Pad
    ctx.moveTo(84.6, 86.3);
    ctx.bezierCurveTo(84.6, 85.8, 85.0, 85.3, 85.6, 85.3);
    ctx.lineTo(85.6, 85.3);
    ctx.bezierCurveTo(86.2, 85.3, 86.6, 85.8, 86.6, 86.3);
    ctx.lineTo(86.6, 86.3);
    ctx.bezierCurveTo(86.6, 86.9, 86.2, 87.3, 85.6, 87.3);
    ctx.lineTo(85.6, 87.3);
    ctx.bezierCurveTo(85.0, 87.3, 84.6, 86.9, 84.6, 86.3);
    ctx.closePath();

    // NUKE/grid/vertical/3/Samengesteld pad/Pad
    ctx.moveTo(84.6, 81.3);
    ctx.bezierCurveTo(84.6, 80.8, 85.0, 80.3, 85.6, 80.3);
    ctx.lineTo(85.6, 80.3);
    ctx.bezierCurveTo(86.2, 80.3, 86.6, 80.8, 86.6, 81.3);
    ctx.lineTo(86.6, 81.3);
    ctx.bezierCurveTo(86.6, 81.9, 86.2, 82.3, 85.6, 82.3);
    ctx.lineTo(85.6, 82.3);
    ctx.bezierCurveTo(85.0, 82.3, 84.6, 81.9, 84.6, 81.3);
    ctx.closePath();

    // NUKE/grid/vertical/3/Samengesteld pad/Pad
    ctx.moveTo(84.6, 76.3);
    ctx.bezierCurveTo(84.6, 75.8, 85.0, 75.3, 85.6, 75.3);
    ctx.lineTo(85.6, 75.3);
    ctx.bezierCurveTo(86.2, 75.3, 86.6, 75.8, 86.6, 76.3);
    ctx.lineTo(86.6, 76.3);
    ctx.bezierCurveTo(86.6, 76.9, 86.2, 77.3, 85.6, 77.3);
    ctx.lineTo(85.6, 77.3);
    ctx.bezierCurveTo(85.0, 77.3, 84.6, 76.9, 84.6, 76.3);
    ctx.closePath();

    // NUKE/grid/vertical/3/Samengesteld pad/Pad
    ctx.moveTo(84.6, 71.3);
    ctx.bezierCurveTo(84.6, 70.8, 85.0, 70.3, 85.6, 70.3);
    ctx.lineTo(85.6, 70.3);
    ctx.bezierCurveTo(86.2, 70.3, 86.6, 70.8, 86.6, 71.3);
    ctx.lineTo(86.6, 71.3);
    ctx.bezierCurveTo(86.6, 71.9, 86.2, 72.3, 85.6, 72.3);
    ctx.lineTo(85.6, 72.3);
    ctx.bezierCurveTo(85.0, 72.3, 84.6, 71.9, 84.6, 71.3);
    ctx.closePath();

    // NUKE/grid/vertical/3/Samengesteld pad/Pad
    ctx.moveTo(84.6, 66.3);
    ctx.bezierCurveTo(84.6, 65.8, 85.0, 65.3, 85.6, 65.3);
    ctx.lineTo(85.6, 65.3);
    ctx.bezierCurveTo(86.2, 65.3, 86.6, 65.8, 86.6, 66.3);
    ctx.lineTo(86.6, 66.3);
    ctx.bezierCurveTo(86.6, 66.9, 86.2, 67.3, 85.6, 67.3);
    ctx.lineTo(85.6, 67.3);
    ctx.bezierCurveTo(85.0, 67.3, 84.6, 66.9, 84.6, 66.3);
    ctx.closePath();

    // NUKE/grid/vertical/3/Samengesteld pad/Pad
    ctx.moveTo(84.6, 61.3);
    ctx.bezierCurveTo(84.6, 60.8, 85.0, 60.3, 85.6, 60.3);
    ctx.lineTo(85.6, 60.3);
    ctx.bezierCurveTo(86.2, 60.3, 86.6, 60.8, 86.6, 61.3);
    ctx.lineTo(86.6, 61.3);
    ctx.bezierCurveTo(86.6, 61.9, 86.2, 62.3, 85.6, 62.3);
    ctx.lineTo(85.6, 62.3);
    ctx.bezierCurveTo(85.0, 62.3, 84.6, 61.9, 84.6, 61.3);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(40, 44, 95));
    ctx.fill();

    // NUKE/grid/vertical/4

    // NUKE/grid/vertical/4/Samengesteld pad
    ctx.beginPath();

    // NUKE/grid/vertical/4/Samengesteld pad/Pad
    ctx.moveTo(104.6, 126.3);
    ctx.bezierCurveTo(104.6, 125.8, 105.1, 125.3, 105.6, 125.3);
    ctx.lineTo(105.6, 125.3);
    ctx.bezierCurveTo(106.2, 125.3, 106.6, 125.8, 106.6, 126.3);
    ctx.lineTo(106.6, 126.3);
    ctx.bezierCurveTo(106.6, 126.9, 106.2, 127.3, 105.6, 127.3);
    ctx.lineTo(105.6, 127.3);
    ctx.bezierCurveTo(105.1, 127.3, 104.6, 126.9, 104.6, 126.3);
    ctx.closePath();

    // NUKE/grid/vertical/4/Samengesteld pad/Pad
    ctx.moveTo(104.6, 121.3);
    ctx.bezierCurveTo(104.6, 120.8, 105.1, 120.3, 105.6, 120.3);
    ctx.lineTo(105.6, 120.3);
    ctx.bezierCurveTo(106.2, 120.3, 106.6, 120.8, 106.6, 121.3);
    ctx.lineTo(106.6, 121.3);
    ctx.bezierCurveTo(106.6, 121.9, 106.2, 122.3, 105.6, 122.3);
    ctx.lineTo(105.6, 122.3);
    ctx.bezierCurveTo(105.1, 122.3, 104.6, 121.9, 104.6, 121.3);
    ctx.closePath();

    // NUKE/grid/vertical/4/Samengesteld pad/Pad
    ctx.moveTo(104.6, 116.3);
    ctx.bezierCurveTo(104.6, 115.8, 105.1, 115.3, 105.6, 115.3);
    ctx.lineTo(105.6, 115.3);
    ctx.bezierCurveTo(106.2, 115.3, 106.6, 115.8, 106.6, 116.3);
    ctx.lineTo(106.6, 116.3);
    ctx.bezierCurveTo(106.6, 116.9, 106.2, 117.3, 105.6, 117.3);
    ctx.lineTo(105.6, 117.3);
    ctx.bezierCurveTo(105.1, 117.3, 104.6, 116.9, 104.6, 116.3);
    ctx.closePath();

    // NUKE/grid/vertical/4/Samengesteld pad/Pad
    ctx.moveTo(104.6, 111.3);
    ctx.bezierCurveTo(104.6, 110.8, 105.1, 110.3, 105.6, 110.3);
    ctx.lineTo(105.6, 110.3);
    ctx.bezierCurveTo(106.2, 110.3, 106.6, 110.8, 106.6, 111.3);
    ctx.lineTo(106.6, 111.3);
    ctx.bezierCurveTo(106.6, 111.9, 106.2, 112.3, 105.6, 112.3);
    ctx.lineTo(105.6, 112.3);
    ctx.bezierCurveTo(105.1, 112.3, 104.6, 111.9, 104.6, 111.3);
    ctx.closePath();

    // NUKE/grid/vertical/4/Samengesteld pad/Pad
    ctx.moveTo(104.6, 106.3);
    ctx.bezierCurveTo(104.6, 105.8, 105.1, 105.3, 105.6, 105.3);
    ctx.lineTo(105.6, 105.3);
    ctx.bezierCurveTo(106.2, 105.3, 106.6, 105.8, 106.6, 106.3);
    ctx.lineTo(106.6, 106.3);
    ctx.bezierCurveTo(106.6, 106.9, 106.2, 107.3, 105.6, 107.3);
    ctx.lineTo(105.6, 107.3);
    ctx.bezierCurveTo(105.1, 107.3, 104.6, 106.9, 104.6, 106.3);
    ctx.closePath();

    // NUKE/grid/vertical/4/Samengesteld pad/Pad
    ctx.moveTo(104.6, 101.3);
    ctx.bezierCurveTo(104.6, 100.8, 105.1, 100.3, 105.6, 100.3);
    ctx.lineTo(105.6, 100.3);
    ctx.bezierCurveTo(106.2, 100.3, 106.6, 100.8, 106.6, 101.3);
    ctx.lineTo(106.6, 101.3);
    ctx.bezierCurveTo(106.6, 101.9, 106.2, 102.3, 105.6, 102.3);
    ctx.lineTo(105.6, 102.3);
    ctx.bezierCurveTo(105.1, 102.3, 104.6, 101.9, 104.6, 101.3);
    ctx.closePath();

    // NUKE/grid/vertical/4/Samengesteld pad/Pad
    ctx.moveTo(104.6, 96.3);
    ctx.bezierCurveTo(104.6, 95.8, 105.1, 95.3, 105.6, 95.3);
    ctx.lineTo(105.6, 95.3);
    ctx.bezierCurveTo(106.2, 95.3, 106.6, 95.8, 106.6, 96.3);
    ctx.lineTo(106.6, 96.3);
    ctx.bezierCurveTo(106.6, 96.9, 106.2, 97.3, 105.6, 97.3);
    ctx.lineTo(105.6, 97.3);
    ctx.bezierCurveTo(105.1, 97.3, 104.6, 96.9, 104.6, 96.3);
    ctx.closePath();

    // NUKE/grid/vertical/4/Samengesteld pad/Pad
    ctx.moveTo(104.6, 91.3);
    ctx.bezierCurveTo(104.6, 90.8, 105.1, 90.3, 105.6, 90.3);
    ctx.lineTo(105.6, 90.3);
    ctx.bezierCurveTo(106.2, 90.3, 106.6, 90.8, 106.6, 91.3);
    ctx.lineTo(106.6, 91.3);
    ctx.bezierCurveTo(106.6, 91.9, 106.2, 92.3, 105.6, 92.3);
    ctx.lineTo(105.6, 92.3);
    ctx.bezierCurveTo(105.1, 92.3, 104.6, 91.9, 104.6, 91.3);
    ctx.closePath();

    // NUKE/grid/vertical/4/Samengesteld pad/Pad
    ctx.moveTo(104.6, 86.3);
    ctx.bezierCurveTo(104.6, 85.8, 105.1, 85.3, 105.6, 85.3);
    ctx.lineTo(105.6, 85.3);
    ctx.bezierCurveTo(106.2, 85.3, 106.6, 85.8, 106.6, 86.3);
    ctx.lineTo(106.6, 86.3);
    ctx.bezierCurveTo(106.6, 86.9, 106.2, 87.3, 105.6, 87.3);
    ctx.lineTo(105.6, 87.3);
    ctx.bezierCurveTo(105.1, 87.3, 104.6, 86.9, 104.6, 86.3);
    ctx.closePath();

    // NUKE/grid/vertical/4/Samengesteld pad/Pad
    ctx.moveTo(104.6, 81.3);
    ctx.bezierCurveTo(104.6, 80.8, 105.1, 80.3, 105.6, 80.3);
    ctx.lineTo(105.6, 80.3);
    ctx.bezierCurveTo(106.2, 80.3, 106.6, 80.8, 106.6, 81.3);
    ctx.lineTo(106.6, 81.3);
    ctx.bezierCurveTo(106.6, 81.9, 106.2, 82.3, 105.6, 82.3);
    ctx.lineTo(105.6, 82.3);
    ctx.bezierCurveTo(105.1, 82.3, 104.6, 81.9, 104.6, 81.3);
    ctx.closePath();

    // NUKE/grid/vertical/4/Samengesteld pad/Pad
    ctx.moveTo(104.6, 76.3);
    ctx.bezierCurveTo(104.6, 75.8, 105.1, 75.3, 105.6, 75.3);
    ctx.lineTo(105.6, 75.3);
    ctx.bezierCurveTo(106.2, 75.3, 106.6, 75.8, 106.6, 76.3);
    ctx.lineTo(106.6, 76.3);
    ctx.bezierCurveTo(106.6, 76.9, 106.2, 77.3, 105.6, 77.3);
    ctx.lineTo(105.6, 77.3);
    ctx.bezierCurveTo(105.1, 77.3, 104.6, 76.9, 104.6, 76.3);
    ctx.closePath();

    // NUKE/grid/vertical/4/Samengesteld pad/Pad
    ctx.moveTo(104.6, 71.3);
    ctx.bezierCurveTo(104.6, 70.8, 105.1, 70.3, 105.6, 70.3);
    ctx.lineTo(105.6, 70.3);
    ctx.bezierCurveTo(106.2, 70.3, 106.6, 70.8, 106.6, 71.3);
    ctx.lineTo(106.6, 71.3);
    ctx.bezierCurveTo(106.6, 71.9, 106.2, 72.3, 105.6, 72.3);
    ctx.lineTo(105.6, 72.3);
    ctx.bezierCurveTo(105.1, 72.3, 104.6, 71.9, 104.6, 71.3);
    ctx.closePath();

    // NUKE/grid/vertical/4/Samengesteld pad/Pad
    ctx.moveTo(104.6, 66.3);
    ctx.bezierCurveTo(104.6, 65.8, 105.1, 65.3, 105.6, 65.3);
    ctx.lineTo(105.6, 65.3);
    ctx.bezierCurveTo(106.2, 65.3, 106.6, 65.8, 106.6, 66.3);
    ctx.lineTo(106.6, 66.3);
    ctx.bezierCurveTo(106.6, 66.9, 106.2, 67.3, 105.6, 67.3);
    ctx.lineTo(105.6, 67.3);
    ctx.bezierCurveTo(105.1, 67.3, 104.6, 66.9, 104.6, 66.3);
    ctx.closePath();

    // NUKE/grid/vertical/4/Samengesteld pad/Pad
    ctx.moveTo(104.6, 61.3);
    ctx.bezierCurveTo(104.6, 60.8, 105.1, 60.3, 105.6, 60.3);
    ctx.lineTo(105.6, 60.3);
    ctx.bezierCurveTo(106.2, 60.3, 106.6, 60.8, 106.6, 61.3);
    ctx.lineTo(106.6, 61.3);
    ctx.bezierCurveTo(106.6, 61.9, 106.2, 62.3, 105.6, 62.3);
    ctx.lineTo(105.6, 62.3);
    ctx.bezierCurveTo(105.1, 62.3, 104.6, 61.9, 104.6, 61.3);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(40, 44, 95));
    ctx.fill();

    // NUKE/grid/vertical/5

    // NUKE/grid/vertical/5/Samengesteld pad
    ctx.beginPath();

    // NUKE/grid/vertical/5/Samengesteld pad/Pad
    ctx.moveTo(124.6, 126.3);
    ctx.bezierCurveTo(124.6, 125.8, 125.0, 125.3, 125.6, 125.3);
    ctx.lineTo(125.6, 125.3);
    ctx.bezierCurveTo(126.2, 125.3, 126.6, 125.8, 126.6, 126.3);
    ctx.lineTo(126.6, 126.3);
    ctx.bezierCurveTo(126.6, 126.9, 126.2, 127.3, 125.6, 127.3);
    ctx.lineTo(125.6, 127.3);
    ctx.bezierCurveTo(125.0, 127.3, 124.6, 126.9, 124.6, 126.3);
    ctx.closePath();

    // NUKE/grid/vertical/5/Samengesteld pad/Pad
    ctx.moveTo(124.6, 121.3);
    ctx.bezierCurveTo(124.6, 120.8, 125.0, 120.3, 125.6, 120.3);
    ctx.lineTo(125.6, 120.3);
    ctx.bezierCurveTo(126.2, 120.3, 126.6, 120.8, 126.6, 121.3);
    ctx.lineTo(126.6, 121.3);
    ctx.bezierCurveTo(126.6, 121.9, 126.2, 122.3, 125.6, 122.3);
    ctx.lineTo(125.6, 122.3);
    ctx.bezierCurveTo(125.0, 122.3, 124.6, 121.9, 124.6, 121.3);
    ctx.closePath();

    // NUKE/grid/vertical/5/Samengesteld pad/Pad
    ctx.moveTo(124.6, 116.3);
    ctx.bezierCurveTo(124.6, 115.8, 125.0, 115.3, 125.6, 115.3);
    ctx.lineTo(125.6, 115.3);
    ctx.bezierCurveTo(126.2, 115.3, 126.6, 115.8, 126.6, 116.3);
    ctx.lineTo(126.6, 116.3);
    ctx.bezierCurveTo(126.6, 116.9, 126.2, 117.3, 125.6, 117.3);
    ctx.lineTo(125.6, 117.3);
    ctx.bezierCurveTo(125.0, 117.3, 124.6, 116.9, 124.6, 116.3);
    ctx.closePath();

    // NUKE/grid/vertical/5/Samengesteld pad/Pad
    ctx.moveTo(124.6, 111.3);
    ctx.bezierCurveTo(124.6, 110.8, 125.0, 110.3, 125.6, 110.3);
    ctx.lineTo(125.6, 110.3);
    ctx.bezierCurveTo(126.2, 110.3, 126.6, 110.8, 126.6, 111.3);
    ctx.lineTo(126.6, 111.3);
    ctx.bezierCurveTo(126.6, 111.9, 126.2, 112.3, 125.6, 112.3);
    ctx.lineTo(125.6, 112.3);
    ctx.bezierCurveTo(125.0, 112.3, 124.6, 111.9, 124.6, 111.3);
    ctx.closePath();

    // NUKE/grid/vertical/5/Samengesteld pad/Pad
    ctx.moveTo(124.6, 106.3);
    ctx.bezierCurveTo(124.6, 105.8, 125.0, 105.3, 125.6, 105.3);
    ctx.lineTo(125.6, 105.3);
    ctx.bezierCurveTo(126.2, 105.3, 126.6, 105.8, 126.6, 106.3);
    ctx.lineTo(126.6, 106.3);
    ctx.bezierCurveTo(126.6, 106.9, 126.2, 107.3, 125.6, 107.3);
    ctx.lineTo(125.6, 107.3);
    ctx.bezierCurveTo(125.0, 107.3, 124.6, 106.9, 124.6, 106.3);
    ctx.closePath();

    // NUKE/grid/vertical/5/Samengesteld pad/Pad
    ctx.moveTo(124.6, 101.3);
    ctx.bezierCurveTo(124.6, 100.8, 125.0, 100.3, 125.6, 100.3);
    ctx.lineTo(125.6, 100.3);
    ctx.bezierCurveTo(126.2, 100.3, 126.6, 100.8, 126.6, 101.3);
    ctx.lineTo(126.6, 101.3);
    ctx.bezierCurveTo(126.6, 101.9, 126.2, 102.3, 125.6, 102.3);
    ctx.lineTo(125.6, 102.3);
    ctx.bezierCurveTo(125.0, 102.3, 124.6, 101.9, 124.6, 101.3);
    ctx.closePath();

    // NUKE/grid/vertical/5/Samengesteld pad/Pad
    ctx.moveTo(124.6, 96.3);
    ctx.bezierCurveTo(124.6, 95.8, 125.0, 95.3, 125.6, 95.3);
    ctx.lineTo(125.6, 95.3);
    ctx.bezierCurveTo(126.2, 95.3, 126.6, 95.8, 126.6, 96.3);
    ctx.lineTo(126.6, 96.3);
    ctx.bezierCurveTo(126.6, 96.9, 126.2, 97.3, 125.6, 97.3);
    ctx.lineTo(125.6, 97.3);
    ctx.bezierCurveTo(125.0, 97.3, 124.6, 96.9, 124.6, 96.3);
    ctx.closePath();

    // NUKE/grid/vertical/5/Samengesteld pad/Pad
    ctx.moveTo(124.6, 91.3);
    ctx.bezierCurveTo(124.6, 90.8, 125.0, 90.3, 125.6, 90.3);
    ctx.lineTo(125.6, 90.3);
    ctx.bezierCurveTo(126.2, 90.3, 126.6, 90.8, 126.6, 91.3);
    ctx.lineTo(126.6, 91.3);
    ctx.bezierCurveTo(126.6, 91.9, 126.2, 92.3, 125.6, 92.3);
    ctx.lineTo(125.6, 92.3);
    ctx.bezierCurveTo(125.0, 92.3, 124.6, 91.9, 124.6, 91.3);
    ctx.closePath();

    // NUKE/grid/vertical/5/Samengesteld pad/Pad
    ctx.moveTo(124.6, 86.3);
    ctx.bezierCurveTo(124.6, 85.8, 125.0, 85.3, 125.6, 85.3);
    ctx.lineTo(125.6, 85.3);
    ctx.bezierCurveTo(126.2, 85.3, 126.6, 85.8, 126.6, 86.3);
    ctx.lineTo(126.6, 86.3);
    ctx.bezierCurveTo(126.6, 86.9, 126.2, 87.3, 125.6, 87.3);
    ctx.lineTo(125.6, 87.3);
    ctx.bezierCurveTo(125.0, 87.3, 124.6, 86.9, 124.6, 86.3);
    ctx.closePath();

    // NUKE/grid/vertical/5/Samengesteld pad/Pad
    ctx.moveTo(124.6, 81.3);
    ctx.bezierCurveTo(124.6, 80.8, 125.0, 80.3, 125.6, 80.3);
    ctx.lineTo(125.6, 80.3);
    ctx.bezierCurveTo(126.2, 80.3, 126.6, 80.8, 126.6, 81.3);
    ctx.lineTo(126.6, 81.3);
    ctx.bezierCurveTo(126.6, 81.9, 126.2, 82.3, 125.6, 82.3);
    ctx.lineTo(125.6, 82.3);
    ctx.bezierCurveTo(125.0, 82.3, 124.6, 81.9, 124.6, 81.3);
    ctx.closePath();

    // NUKE/grid/vertical/5/Samengesteld pad/Pad
    ctx.moveTo(124.6, 76.3);
    ctx.bezierCurveTo(124.6, 75.8, 125.0, 75.3, 125.6, 75.3);
    ctx.lineTo(125.6, 75.3);
    ctx.bezierCurveTo(126.2, 75.3, 126.6, 75.8, 126.6, 76.3);
    ctx.lineTo(126.6, 76.3);
    ctx.bezierCurveTo(126.6, 76.9, 126.2, 77.3, 125.6, 77.3);
    ctx.lineTo(125.6, 77.3);
    ctx.bezierCurveTo(125.0, 77.3, 124.6, 76.9, 124.6, 76.3);
    ctx.closePath();

    // NUKE/grid/vertical/5/Samengesteld pad/Pad
    ctx.moveTo(124.6, 71.3);
    ctx.bezierCurveTo(124.6, 70.8, 125.0, 70.3, 125.6, 70.3);
    ctx.lineTo(125.6, 70.3);
    ctx.bezierCurveTo(126.2, 70.3, 126.6, 70.8, 126.6, 71.3);
    ctx.lineTo(126.6, 71.3);
    ctx.bezierCurveTo(126.6, 71.9, 126.2, 72.3, 125.6, 72.3);
    ctx.lineTo(125.6, 72.3);
    ctx.bezierCurveTo(125.0, 72.3, 124.6, 71.9, 124.6, 71.3);
    ctx.closePath();

    // NUKE/grid/vertical/5/Samengesteld pad/Pad
    ctx.moveTo(124.6, 66.3);
    ctx.bezierCurveTo(124.6, 65.8, 125.0, 65.3, 125.6, 65.3);
    ctx.lineTo(125.6, 65.3);
    ctx.bezierCurveTo(126.2, 65.3, 126.6, 65.8, 126.6, 66.3);
    ctx.lineTo(126.6, 66.3);
    ctx.bezierCurveTo(126.6, 66.9, 126.2, 67.3, 125.6, 67.3);
    ctx.lineTo(125.6, 67.3);
    ctx.bezierCurveTo(125.0, 67.3, 124.6, 66.9, 124.6, 66.3);
    ctx.closePath();

    // NUKE/grid/vertical/5/Samengesteld pad/Pad
    ctx.moveTo(124.6, 61.3);
    ctx.bezierCurveTo(124.6, 60.8, 125.0, 60.3, 125.6, 60.3);
    ctx.lineTo(125.6, 60.3);
    ctx.bezierCurveTo(126.2, 60.3, 126.6, 60.8, 126.6, 61.3);
    ctx.lineTo(126.6, 61.3);
    ctx.bezierCurveTo(126.6, 61.9, 126.2, 62.3, 125.6, 62.3);
    ctx.lineTo(125.6, 62.3);
    ctx.bezierCurveTo(125.0, 62.3, 124.6, 61.9, 124.6, 61.3);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(40, 44, 95));
    ctx.fill();

    // NUKE/grid/vertical/6

    // NUKE/grid/vertical/6/Samengesteld pad
    ctx.beginPath();

    // NUKE/grid/vertical/6/Samengesteld pad/Pad
    ctx.moveTo(144.6, 126.3);
    ctx.bezierCurveTo(144.6, 125.8, 145.1, 125.3, 145.6, 125.3);
    ctx.lineTo(145.6, 125.3);
    ctx.bezierCurveTo(146.2, 125.3, 146.6, 125.8, 146.6, 126.3);
    ctx.lineTo(146.6, 126.3);
    ctx.bezierCurveTo(146.6, 126.9, 146.2, 127.3, 145.6, 127.3);
    ctx.lineTo(145.6, 127.3);
    ctx.bezierCurveTo(145.1, 127.3, 144.6, 126.9, 144.6, 126.3);
    ctx.closePath();

    // NUKE/grid/vertical/6/Samengesteld pad/Pad
    ctx.moveTo(144.6, 121.3);
    ctx.bezierCurveTo(144.6, 120.8, 145.1, 120.3, 145.6, 120.3);
    ctx.lineTo(145.6, 120.3);
    ctx.bezierCurveTo(146.2, 120.3, 146.6, 120.8, 146.6, 121.3);
    ctx.lineTo(146.6, 121.3);
    ctx.bezierCurveTo(146.6, 121.9, 146.2, 122.3, 145.6, 122.3);
    ctx.lineTo(145.6, 122.3);
    ctx.bezierCurveTo(145.1, 122.3, 144.6, 121.9, 144.6, 121.3);
    ctx.closePath();

    // NUKE/grid/vertical/6/Samengesteld pad/Pad
    ctx.moveTo(144.6, 116.3);
    ctx.bezierCurveTo(144.6, 115.8, 145.1, 115.3, 145.6, 115.3);
    ctx.lineTo(145.6, 115.3);
    ctx.bezierCurveTo(146.2, 115.3, 146.6, 115.8, 146.6, 116.3);
    ctx.lineTo(146.6, 116.3);
    ctx.bezierCurveTo(146.6, 116.9, 146.2, 117.3, 145.6, 117.3);
    ctx.lineTo(145.6, 117.3);
    ctx.bezierCurveTo(145.1, 117.3, 144.6, 116.9, 144.6, 116.3);
    ctx.closePath();

    // NUKE/grid/vertical/6/Samengesteld pad/Pad
    ctx.moveTo(144.6, 111.3);
    ctx.bezierCurveTo(144.6, 110.8, 145.1, 110.3, 145.6, 110.3);
    ctx.lineTo(145.6, 110.3);
    ctx.bezierCurveTo(146.2, 110.3, 146.6, 110.8, 146.6, 111.3);
    ctx.lineTo(146.6, 111.3);
    ctx.bezierCurveTo(146.6, 111.9, 146.2, 112.3, 145.6, 112.3);
    ctx.lineTo(145.6, 112.3);
    ctx.bezierCurveTo(145.1, 112.3, 144.6, 111.9, 144.6, 111.3);
    ctx.closePath();

    // NUKE/grid/vertical/6/Samengesteld pad/Pad
    ctx.moveTo(144.6, 106.3);
    ctx.bezierCurveTo(144.6, 105.8, 145.1, 105.3, 145.6, 105.3);
    ctx.lineTo(145.6, 105.3);
    ctx.bezierCurveTo(146.2, 105.3, 146.6, 105.8, 146.6, 106.3);
    ctx.lineTo(146.6, 106.3);
    ctx.bezierCurveTo(146.6, 106.9, 146.2, 107.3, 145.6, 107.3);
    ctx.lineTo(145.6, 107.3);
    ctx.bezierCurveTo(145.1, 107.3, 144.6, 106.9, 144.6, 106.3);
    ctx.closePath();

    // NUKE/grid/vertical/6/Samengesteld pad/Pad
    ctx.moveTo(144.6, 101.3);
    ctx.bezierCurveTo(144.6, 100.8, 145.1, 100.3, 145.6, 100.3);
    ctx.lineTo(145.6, 100.3);
    ctx.bezierCurveTo(146.2, 100.3, 146.6, 100.8, 146.6, 101.3);
    ctx.lineTo(146.6, 101.3);
    ctx.bezierCurveTo(146.6, 101.9, 146.2, 102.3, 145.6, 102.3);
    ctx.lineTo(145.6, 102.3);
    ctx.bezierCurveTo(145.1, 102.3, 144.6, 101.9, 144.6, 101.3);
    ctx.closePath();

    // NUKE/grid/vertical/6/Samengesteld pad/Pad
    ctx.moveTo(144.6, 96.3);
    ctx.bezierCurveTo(144.6, 95.8, 145.1, 95.3, 145.6, 95.3);
    ctx.lineTo(145.6, 95.3);
    ctx.bezierCurveTo(146.2, 95.3, 146.6, 95.8, 146.6, 96.3);
    ctx.lineTo(146.6, 96.3);
    ctx.bezierCurveTo(146.6, 96.9, 146.2, 97.3, 145.6, 97.3);
    ctx.lineTo(145.6, 97.3);
    ctx.bezierCurveTo(145.1, 97.3, 144.6, 96.9, 144.6, 96.3);
    ctx.closePath();

    // NUKE/grid/vertical/6/Samengesteld pad/Pad
    ctx.moveTo(144.6, 91.3);
    ctx.bezierCurveTo(144.6, 90.8, 145.1, 90.3, 145.6, 90.3);
    ctx.lineTo(145.6, 90.3);
    ctx.bezierCurveTo(146.2, 90.3, 146.6, 90.8, 146.6, 91.3);
    ctx.lineTo(146.6, 91.3);
    ctx.bezierCurveTo(146.6, 91.9, 146.2, 92.3, 145.6, 92.3);
    ctx.lineTo(145.6, 92.3);
    ctx.bezierCurveTo(145.1, 92.3, 144.6, 91.9, 144.6, 91.3);
    ctx.closePath();

    // NUKE/grid/vertical/6/Samengesteld pad/Pad
    ctx.moveTo(144.6, 86.3);
    ctx.bezierCurveTo(144.6, 85.8, 145.1, 85.3, 145.6, 85.3);
    ctx.lineTo(145.6, 85.3);
    ctx.bezierCurveTo(146.2, 85.3, 146.6, 85.8, 146.6, 86.3);
    ctx.lineTo(146.6, 86.3);
    ctx.bezierCurveTo(146.6, 86.9, 146.2, 87.3, 145.6, 87.3);
    ctx.lineTo(145.6, 87.3);
    ctx.bezierCurveTo(145.1, 87.3, 144.6, 86.9, 144.6, 86.3);
    ctx.closePath();

    // NUKE/grid/vertical/6/Samengesteld pad/Pad
    ctx.moveTo(144.6, 81.3);
    ctx.bezierCurveTo(144.6, 80.8, 145.1, 80.3, 145.6, 80.3);
    ctx.lineTo(145.6, 80.3);
    ctx.bezierCurveTo(146.2, 80.3, 146.6, 80.8, 146.6, 81.3);
    ctx.lineTo(146.6, 81.3);
    ctx.bezierCurveTo(146.6, 81.9, 146.2, 82.3, 145.6, 82.3);
    ctx.lineTo(145.6, 82.3);
    ctx.bezierCurveTo(145.1, 82.3, 144.6, 81.9, 144.6, 81.3);
    ctx.closePath();

    // NUKE/grid/vertical/6/Samengesteld pad/Pad
    ctx.moveTo(144.6, 76.3);
    ctx.bezierCurveTo(144.6, 75.8, 145.1, 75.3, 145.6, 75.3);
    ctx.lineTo(145.6, 75.3);
    ctx.bezierCurveTo(146.2, 75.3, 146.6, 75.8, 146.6, 76.3);
    ctx.lineTo(146.6, 76.3);
    ctx.bezierCurveTo(146.6, 76.9, 146.2, 77.3, 145.6, 77.3);
    ctx.lineTo(145.6, 77.3);
    ctx.bezierCurveTo(145.1, 77.3, 144.6, 76.9, 144.6, 76.3);
    ctx.closePath();

    // NUKE/grid/vertical/6/Samengesteld pad/Pad
    ctx.moveTo(144.6, 71.3);
    ctx.bezierCurveTo(144.6, 70.8, 145.1, 70.3, 145.6, 70.3);
    ctx.lineTo(145.6, 70.3);
    ctx.bezierCurveTo(146.2, 70.3, 146.6, 70.8, 146.6, 71.3);
    ctx.lineTo(146.6, 71.3);
    ctx.bezierCurveTo(146.6, 71.9, 146.2, 72.3, 145.6, 72.3);
    ctx.lineTo(145.6, 72.3);
    ctx.bezierCurveTo(145.1, 72.3, 144.6, 71.9, 144.6, 71.3);
    ctx.closePath();

    // NUKE/grid/vertical/6/Samengesteld pad/Pad
    ctx.moveTo(144.6, 66.3);
    ctx.bezierCurveTo(144.6, 65.8, 145.1, 65.3, 145.6, 65.3);
    ctx.lineTo(145.6, 65.3);
    ctx.bezierCurveTo(146.2, 65.3, 146.6, 65.8, 146.6, 66.3);
    ctx.lineTo(146.6, 66.3);
    ctx.bezierCurveTo(146.6, 66.9, 146.2, 67.3, 145.6, 67.3);
    ctx.lineTo(145.6, 67.3);
    ctx.bezierCurveTo(145.1, 67.3, 144.6, 66.9, 144.6, 66.3);
    ctx.closePath();

    // NUKE/grid/vertical/6/Samengesteld pad/Pad
    ctx.moveTo(144.6, 61.3);
    ctx.bezierCurveTo(144.6, 60.8, 145.1, 60.3, 145.6, 60.3);
    ctx.lineTo(145.6, 60.3);
    ctx.bezierCurveTo(146.2, 60.3, 146.6, 60.8, 146.6, 61.3);
    ctx.lineTo(146.6, 61.3);
    ctx.bezierCurveTo(146.6, 61.9, 146.2, 62.3, 145.6, 62.3);
    ctx.lineTo(145.6, 62.3);
    ctx.bezierCurveTo(145.1, 62.3, 144.6, 61.9, 144.6, 61.3);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(40, 44, 95));
    ctx.fill();

    // NUKE/grid/vertical/7

    // NUKE/grid/vertical/7/Samengesteld pad
    ctx.beginPath();

    // NUKE/grid/vertical/7/Samengesteld pad/Pad
    ctx.moveTo(164.6, 126.3);
    ctx.bezierCurveTo(164.6, 125.8, 165.0, 125.3, 165.6, 125.3);
    ctx.lineTo(165.6, 125.3);
    ctx.bezierCurveTo(166.2, 125.3, 166.6, 125.8, 166.6, 126.3);
    ctx.lineTo(166.6, 126.3);
    ctx.bezierCurveTo(166.6, 126.9, 166.2, 127.3, 165.6, 127.3);
    ctx.lineTo(165.6, 127.3);
    ctx.bezierCurveTo(165.0, 127.3, 164.6, 126.9, 164.6, 126.3);
    ctx.closePath();

    // NUKE/grid/vertical/7/Samengesteld pad/Pad
    ctx.moveTo(164.6, 121.3);
    ctx.bezierCurveTo(164.6, 120.8, 165.0, 120.3, 165.6, 120.3);
    ctx.lineTo(165.6, 120.3);
    ctx.bezierCurveTo(166.2, 120.3, 166.6, 120.8, 166.6, 121.3);
    ctx.lineTo(166.6, 121.3);
    ctx.bezierCurveTo(166.6, 121.9, 166.2, 122.3, 165.6, 122.3);
    ctx.lineTo(165.6, 122.3);
    ctx.bezierCurveTo(165.0, 122.3, 164.6, 121.9, 164.6, 121.3);
    ctx.closePath();

    // NUKE/grid/vertical/7/Samengesteld pad/Pad
    ctx.moveTo(164.6, 116.3);
    ctx.bezierCurveTo(164.6, 115.8, 165.0, 115.3, 165.6, 115.3);
    ctx.lineTo(165.6, 115.3);
    ctx.bezierCurveTo(166.2, 115.3, 166.6, 115.8, 166.6, 116.3);
    ctx.lineTo(166.6, 116.3);
    ctx.bezierCurveTo(166.6, 116.9, 166.2, 117.3, 165.6, 117.3);
    ctx.lineTo(165.6, 117.3);
    ctx.bezierCurveTo(165.0, 117.3, 164.6, 116.9, 164.6, 116.3);
    ctx.closePath();

    // NUKE/grid/vertical/7/Samengesteld pad/Pad
    ctx.moveTo(164.6, 111.3);
    ctx.bezierCurveTo(164.6, 110.8, 165.0, 110.3, 165.6, 110.3);
    ctx.lineTo(165.6, 110.3);
    ctx.bezierCurveTo(166.2, 110.3, 166.6, 110.8, 166.6, 111.3);
    ctx.lineTo(166.6, 111.3);
    ctx.bezierCurveTo(166.6, 111.9, 166.2, 112.3, 165.6, 112.3);
    ctx.lineTo(165.6, 112.3);
    ctx.bezierCurveTo(165.0, 112.3, 164.6, 111.9, 164.6, 111.3);
    ctx.closePath();

    // NUKE/grid/vertical/7/Samengesteld pad/Pad
    ctx.moveTo(164.6, 106.3);
    ctx.bezierCurveTo(164.6, 105.8, 165.0, 105.3, 165.6, 105.3);
    ctx.lineTo(165.6, 105.3);
    ctx.bezierCurveTo(166.2, 105.3, 166.6, 105.8, 166.6, 106.3);
    ctx.lineTo(166.6, 106.3);
    ctx.bezierCurveTo(166.6, 106.9, 166.2, 107.3, 165.6, 107.3);
    ctx.lineTo(165.6, 107.3);
    ctx.bezierCurveTo(165.0, 107.3, 164.6, 106.9, 164.6, 106.3);
    ctx.closePath();

    // NUKE/grid/vertical/7/Samengesteld pad/Pad
    ctx.moveTo(164.6, 101.3);
    ctx.bezierCurveTo(164.6, 100.8, 165.0, 100.3, 165.6, 100.3);
    ctx.lineTo(165.6, 100.3);
    ctx.bezierCurveTo(166.2, 100.3, 166.6, 100.8, 166.6, 101.3);
    ctx.lineTo(166.6, 101.3);
    ctx.bezierCurveTo(166.6, 101.9, 166.2, 102.3, 165.6, 102.3);
    ctx.lineTo(165.6, 102.3);
    ctx.bezierCurveTo(165.0, 102.3, 164.6, 101.9, 164.6, 101.3);
    ctx.closePath();

    // NUKE/grid/vertical/7/Samengesteld pad/Pad
    ctx.moveTo(164.6, 96.3);
    ctx.bezierCurveTo(164.6, 95.8, 165.0, 95.3, 165.6, 95.3);
    ctx.lineTo(165.6, 95.3);
    ctx.bezierCurveTo(166.2, 95.3, 166.6, 95.8, 166.6, 96.3);
    ctx.lineTo(166.6, 96.3);
    ctx.bezierCurveTo(166.6, 96.9, 166.2, 97.3, 165.6, 97.3);
    ctx.lineTo(165.6, 97.3);
    ctx.bezierCurveTo(165.0, 97.3, 164.6, 96.9, 164.6, 96.3);
    ctx.closePath();

    // NUKE/grid/vertical/7/Samengesteld pad/Pad
    ctx.moveTo(164.6, 91.3);
    ctx.bezierCurveTo(164.6, 90.8, 165.0, 90.3, 165.6, 90.3);
    ctx.lineTo(165.6, 90.3);
    ctx.bezierCurveTo(166.2, 90.3, 166.6, 90.8, 166.6, 91.3);
    ctx.lineTo(166.6, 91.3);
    ctx.bezierCurveTo(166.6, 91.9, 166.2, 92.3, 165.6, 92.3);
    ctx.lineTo(165.6, 92.3);
    ctx.bezierCurveTo(165.0, 92.3, 164.6, 91.9, 164.6, 91.3);
    ctx.closePath();

    // NUKE/grid/vertical/7/Samengesteld pad/Pad
    ctx.moveTo(164.6, 86.3);
    ctx.bezierCurveTo(164.6, 85.8, 165.0, 85.3, 165.6, 85.3);
    ctx.lineTo(165.6, 85.3);
    ctx.bezierCurveTo(166.2, 85.3, 166.6, 85.8, 166.6, 86.3);
    ctx.lineTo(166.6, 86.3);
    ctx.bezierCurveTo(166.6, 86.9, 166.2, 87.3, 165.6, 87.3);
    ctx.lineTo(165.6, 87.3);
    ctx.bezierCurveTo(165.0, 87.3, 164.6, 86.9, 164.6, 86.3);
    ctx.closePath();

    // NUKE/grid/vertical/7/Samengesteld pad/Pad
    ctx.moveTo(164.6, 81.3);
    ctx.bezierCurveTo(164.6, 80.8, 165.0, 80.3, 165.6, 80.3);
    ctx.lineTo(165.6, 80.3);
    ctx.bezierCurveTo(166.2, 80.3, 166.6, 80.8, 166.6, 81.3);
    ctx.lineTo(166.6, 81.3);
    ctx.bezierCurveTo(166.6, 81.9, 166.2, 82.3, 165.6, 82.3);
    ctx.lineTo(165.6, 82.3);
    ctx.bezierCurveTo(165.0, 82.3, 164.6, 81.9, 164.6, 81.3);
    ctx.closePath();

    // NUKE/grid/vertical/7/Samengesteld pad/Pad
    ctx.moveTo(164.6, 76.3);
    ctx.bezierCurveTo(164.6, 75.8, 165.0, 75.3, 165.6, 75.3);
    ctx.lineTo(165.6, 75.3);
    ctx.bezierCurveTo(166.2, 75.3, 166.6, 75.8, 166.6, 76.3);
    ctx.lineTo(166.6, 76.3);
    ctx.bezierCurveTo(166.6, 76.9, 166.2, 77.3, 165.6, 77.3);
    ctx.lineTo(165.6, 77.3);
    ctx.bezierCurveTo(165.0, 77.3, 164.6, 76.9, 164.6, 76.3);
    ctx.closePath();

    // NUKE/grid/vertical/7/Samengesteld pad/Pad
    ctx.moveTo(164.6, 71.3);
    ctx.bezierCurveTo(164.6, 70.8, 165.0, 70.3, 165.6, 70.3);
    ctx.lineTo(165.6, 70.3);
    ctx.bezierCurveTo(166.2, 70.3, 166.6, 70.8, 166.6, 71.3);
    ctx.lineTo(166.6, 71.3);
    ctx.bezierCurveTo(166.6, 71.9, 166.2, 72.3, 165.6, 72.3);
    ctx.lineTo(165.6, 72.3);
    ctx.bezierCurveTo(165.0, 72.3, 164.6, 71.9, 164.6, 71.3);
    ctx.closePath();

    // NUKE/grid/vertical/7/Samengesteld pad/Pad
    ctx.moveTo(164.6, 66.3);
    ctx.bezierCurveTo(164.6, 65.8, 165.0, 65.3, 165.6, 65.3);
    ctx.lineTo(165.6, 65.3);
    ctx.bezierCurveTo(166.2, 65.3, 166.6, 65.8, 166.6, 66.3);
    ctx.lineTo(166.6, 66.3);
    ctx.bezierCurveTo(166.6, 66.9, 166.2, 67.3, 165.6, 67.3);
    ctx.lineTo(165.6, 67.3);
    ctx.bezierCurveTo(165.0, 67.3, 164.6, 66.9, 164.6, 66.3);
    ctx.closePath();

    // NUKE/grid/vertical/7/Samengesteld pad/Pad
    ctx.moveTo(164.6, 61.3);
    ctx.bezierCurveTo(164.6, 60.8, 165.0, 60.3, 165.6, 60.3);
    ctx.lineTo(165.6, 60.3);
    ctx.bezierCurveTo(166.2, 60.3, 166.6, 60.8, 166.6, 61.3);
    ctx.lineTo(166.6, 61.3);
    ctx.bezierCurveTo(166.6, 61.9, 166.2, 62.3, 165.6, 62.3);
    ctx.lineTo(165.6, 62.3);
    ctx.bezierCurveTo(165.0, 62.3, 164.6, 61.9, 164.6, 61.3);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(40, 44, 95));
    ctx.fill();

    // NUKE/grid/horizontal

    // NUKE/grid/horizontal/1

    // NUKE/grid/horizontal/1/Samengesteld pad
    ctx.beginPath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(167.6, 64.0);
    ctx.bezierCurveTo(167.6, 63.5, 168.0, 63.0, 168.6, 63.0);
    ctx.lineTo(168.6, 63.0);
    ctx.bezierCurveTo(169.2, 63.0, 169.6, 63.5, 169.6, 64.0);
    ctx.lineTo(169.6, 64.0);
    ctx.bezierCurveTo(169.6, 64.6, 169.2, 65.0, 168.6, 65.0);
    ctx.lineTo(168.6, 65.0);
    ctx.bezierCurveTo(168.0, 65.0, 167.6, 64.6, 167.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(162.6, 64.0);
    ctx.bezierCurveTo(162.6, 63.5, 163.0, 63.0, 163.6, 63.0);
    ctx.lineTo(163.6, 63.0);
    ctx.bezierCurveTo(164.2, 63.0, 164.6, 63.5, 164.6, 64.0);
    ctx.lineTo(164.6, 64.0);
    ctx.bezierCurveTo(164.6, 64.6, 164.2, 65.0, 163.6, 65.0);
    ctx.lineTo(163.6, 65.0);
    ctx.bezierCurveTo(163.0, 65.0, 162.6, 64.6, 162.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(157.6, 64.0);
    ctx.bezierCurveTo(157.6, 63.5, 158.0, 63.0, 158.6, 63.0);
    ctx.lineTo(158.6, 63.0);
    ctx.bezierCurveTo(159.2, 63.0, 159.6, 63.5, 159.6, 64.0);
    ctx.lineTo(159.6, 64.0);
    ctx.bezierCurveTo(159.6, 64.6, 159.2, 65.0, 158.6, 65.0);
    ctx.lineTo(158.6, 65.0);
    ctx.bezierCurveTo(158.0, 65.0, 157.6, 64.6, 157.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(152.6, 64.0);
    ctx.bezierCurveTo(152.6, 63.5, 153.0, 63.0, 153.6, 63.0);
    ctx.lineTo(153.6, 63.0);
    ctx.bezierCurveTo(154.2, 63.0, 154.6, 63.5, 154.6, 64.0);
    ctx.lineTo(154.6, 64.0);
    ctx.bezierCurveTo(154.6, 64.6, 154.2, 65.0, 153.6, 65.0);
    ctx.lineTo(153.6, 65.0);
    ctx.bezierCurveTo(153.0, 65.0, 152.6, 64.6, 152.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(147.6, 64.0);
    ctx.bezierCurveTo(147.6, 63.5, 148.1, 63.0, 148.6, 63.0);
    ctx.lineTo(148.6, 63.0);
    ctx.bezierCurveTo(149.2, 63.0, 149.6, 63.5, 149.6, 64.0);
    ctx.lineTo(149.6, 64.0);
    ctx.bezierCurveTo(149.6, 64.6, 149.2, 65.0, 148.6, 65.0);
    ctx.lineTo(148.6, 65.0);
    ctx.bezierCurveTo(148.1, 65.0, 147.6, 64.6, 147.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(142.6, 64.0);
    ctx.bezierCurveTo(142.6, 63.5, 143.0, 63.0, 143.6, 63.0);
    ctx.lineTo(143.6, 63.0);
    ctx.bezierCurveTo(144.2, 63.0, 144.6, 63.5, 144.6, 64.0);
    ctx.lineTo(144.6, 64.0);
    ctx.bezierCurveTo(144.6, 64.6, 144.2, 65.0, 143.6, 65.0);
    ctx.lineTo(143.6, 65.0);
    ctx.bezierCurveTo(143.0, 65.0, 142.6, 64.6, 142.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(137.6, 64.0);
    ctx.bezierCurveTo(137.6, 63.5, 138.1, 63.0, 138.6, 63.0);
    ctx.lineTo(138.6, 63.0);
    ctx.bezierCurveTo(139.2, 63.0, 139.6, 63.5, 139.6, 64.0);
    ctx.lineTo(139.6, 64.0);
    ctx.bezierCurveTo(139.6, 64.6, 139.2, 65.0, 138.6, 65.0);
    ctx.lineTo(138.6, 65.0);
    ctx.bezierCurveTo(138.1, 65.0, 137.6, 64.6, 137.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(132.6, 64.0);
    ctx.bezierCurveTo(132.6, 63.5, 133.0, 63.0, 133.6, 63.0);
    ctx.lineTo(133.6, 63.0);
    ctx.bezierCurveTo(134.2, 63.0, 134.6, 63.5, 134.6, 64.0);
    ctx.lineTo(134.6, 64.0);
    ctx.bezierCurveTo(134.6, 64.6, 134.2, 65.0, 133.6, 65.0);
    ctx.lineTo(133.6, 65.0);
    ctx.bezierCurveTo(133.0, 65.0, 132.6, 64.6, 132.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(127.6, 64.0);
    ctx.bezierCurveTo(127.6, 63.5, 128.1, 63.0, 128.6, 63.0);
    ctx.lineTo(128.6, 63.0);
    ctx.bezierCurveTo(129.2, 63.0, 129.6, 63.5, 129.6, 64.0);
    ctx.lineTo(129.6, 64.0);
    ctx.bezierCurveTo(129.6, 64.6, 129.2, 65.0, 128.6, 65.0);
    ctx.lineTo(128.6, 65.0);
    ctx.bezierCurveTo(128.1, 65.0, 127.6, 64.6, 127.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(122.6, 64.0);
    ctx.bezierCurveTo(122.6, 63.5, 123.0, 63.0, 123.6, 63.0);
    ctx.lineTo(123.6, 63.0);
    ctx.bezierCurveTo(124.2, 63.0, 124.6, 63.5, 124.6, 64.0);
    ctx.lineTo(124.6, 64.0);
    ctx.bezierCurveTo(124.6, 64.6, 124.2, 65.0, 123.6, 65.0);
    ctx.lineTo(123.6, 65.0);
    ctx.bezierCurveTo(123.0, 65.0, 122.6, 64.6, 122.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(117.6, 64.0);
    ctx.bezierCurveTo(117.6, 63.5, 118.0, 63.0, 118.6, 63.0);
    ctx.lineTo(118.6, 63.0);
    ctx.bezierCurveTo(119.2, 63.0, 119.6, 63.5, 119.6, 64.0);
    ctx.lineTo(119.6, 64.0);
    ctx.bezierCurveTo(119.6, 64.6, 119.2, 65.0, 118.6, 65.0);
    ctx.lineTo(118.6, 65.0);
    ctx.bezierCurveTo(118.0, 65.0, 117.6, 64.6, 117.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(112.6, 64.0);
    ctx.bezierCurveTo(112.6, 63.5, 113.0, 63.0, 113.6, 63.0);
    ctx.lineTo(113.6, 63.0);
    ctx.bezierCurveTo(114.2, 63.0, 114.6, 63.5, 114.6, 64.0);
    ctx.lineTo(114.6, 64.0);
    ctx.bezierCurveTo(114.6, 64.6, 114.2, 65.0, 113.6, 65.0);
    ctx.lineTo(113.6, 65.0);
    ctx.bezierCurveTo(113.0, 65.0, 112.6, 64.6, 112.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(107.6, 64.0);
    ctx.bezierCurveTo(107.6, 63.5, 108.0, 63.0, 108.6, 63.0);
    ctx.lineTo(108.6, 63.0);
    ctx.bezierCurveTo(109.2, 63.0, 109.6, 63.5, 109.6, 64.0);
    ctx.lineTo(109.6, 64.0);
    ctx.bezierCurveTo(109.6, 64.6, 109.2, 65.0, 108.6, 65.0);
    ctx.lineTo(108.6, 65.0);
    ctx.bezierCurveTo(108.0, 65.0, 107.6, 64.6, 107.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(102.6, 64.0);
    ctx.bezierCurveTo(102.6, 63.5, 103.1, 63.0, 103.6, 63.0);
    ctx.lineTo(103.6, 63.0);
    ctx.bezierCurveTo(104.2, 63.0, 104.6, 63.5, 104.6, 64.0);
    ctx.lineTo(104.6, 64.0);
    ctx.bezierCurveTo(104.6, 64.6, 104.2, 65.0, 103.6, 65.0);
    ctx.lineTo(103.6, 65.0);
    ctx.bezierCurveTo(103.1, 65.0, 102.6, 64.6, 102.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(97.6, 64.0);
    ctx.bezierCurveTo(97.6, 63.5, 98.0, 63.0, 98.6, 63.0);
    ctx.lineTo(98.6, 63.0);
    ctx.bezierCurveTo(99.2, 63.0, 99.6, 63.5, 99.6, 64.0);
    ctx.lineTo(99.6, 64.0);
    ctx.bezierCurveTo(99.6, 64.6, 99.2, 65.0, 98.6, 65.0);
    ctx.lineTo(98.6, 65.0);
    ctx.bezierCurveTo(98.0, 65.0, 97.6, 64.6, 97.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(92.6, 64.0);
    ctx.bezierCurveTo(92.6, 63.5, 93.1, 63.0, 93.6, 63.0);
    ctx.lineTo(93.6, 63.0);
    ctx.bezierCurveTo(94.2, 63.0, 94.6, 63.5, 94.6, 64.0);
    ctx.lineTo(94.6, 64.0);
    ctx.bezierCurveTo(94.6, 64.6, 94.2, 65.0, 93.6, 65.0);
    ctx.lineTo(93.6, 65.0);
    ctx.bezierCurveTo(93.1, 65.0, 92.6, 64.6, 92.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(87.6, 64.0);
    ctx.bezierCurveTo(87.6, 63.5, 88.0, 63.0, 88.6, 63.0);
    ctx.lineTo(88.6, 63.0);
    ctx.bezierCurveTo(89.2, 63.0, 89.6, 63.5, 89.6, 64.0);
    ctx.lineTo(89.6, 64.0);
    ctx.bezierCurveTo(89.6, 64.6, 89.2, 65.0, 88.6, 65.0);
    ctx.lineTo(88.6, 65.0);
    ctx.bezierCurveTo(88.0, 65.0, 87.6, 64.6, 87.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(82.6, 64.0);
    ctx.bezierCurveTo(82.6, 63.5, 83.1, 63.0, 83.6, 63.0);
    ctx.lineTo(83.6, 63.0);
    ctx.bezierCurveTo(84.2, 63.0, 84.6, 63.5, 84.6, 64.0);
    ctx.lineTo(84.6, 64.0);
    ctx.bezierCurveTo(84.6, 64.6, 84.2, 65.0, 83.6, 65.0);
    ctx.lineTo(83.6, 65.0);
    ctx.bezierCurveTo(83.1, 65.0, 82.6, 64.6, 82.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(77.6, 64.0);
    ctx.bezierCurveTo(77.6, 63.5, 78.0, 63.0, 78.6, 63.0);
    ctx.lineTo(78.6, 63.0);
    ctx.bezierCurveTo(79.2, 63.0, 79.6, 63.5, 79.6, 64.0);
    ctx.lineTo(79.6, 64.0);
    ctx.bezierCurveTo(79.6, 64.6, 79.2, 65.0, 78.6, 65.0);
    ctx.lineTo(78.6, 65.0);
    ctx.bezierCurveTo(78.0, 65.0, 77.6, 64.6, 77.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(72.6, 64.0);
    ctx.bezierCurveTo(72.6, 63.5, 73.0, 63.0, 73.6, 63.0);
    ctx.lineTo(73.6, 63.0);
    ctx.bezierCurveTo(74.2, 63.0, 74.6, 63.5, 74.6, 64.0);
    ctx.lineTo(74.6, 64.0);
    ctx.bezierCurveTo(74.6, 64.6, 74.2, 65.0, 73.6, 65.0);
    ctx.lineTo(73.6, 65.0);
    ctx.bezierCurveTo(73.0, 65.0, 72.6, 64.6, 72.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(67.6, 64.0);
    ctx.bezierCurveTo(67.6, 63.5, 68.0, 63.0, 68.6, 63.0);
    ctx.lineTo(68.6, 63.0);
    ctx.bezierCurveTo(69.2, 63.0, 69.6, 63.5, 69.6, 64.0);
    ctx.lineTo(69.6, 64.0);
    ctx.bezierCurveTo(69.6, 64.6, 69.2, 65.0, 68.6, 65.0);
    ctx.lineTo(68.6, 65.0);
    ctx.bezierCurveTo(68.0, 65.0, 67.6, 64.6, 67.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(62.6, 64.0);
    ctx.bezierCurveTo(62.6, 63.5, 63.0, 63.0, 63.6, 63.0);
    ctx.lineTo(63.6, 63.0);
    ctx.bezierCurveTo(64.2, 63.0, 64.6, 63.5, 64.6, 64.0);
    ctx.lineTo(64.6, 64.0);
    ctx.bezierCurveTo(64.6, 64.6, 64.2, 65.0, 63.6, 65.0);
    ctx.lineTo(63.6, 65.0);
    ctx.bezierCurveTo(63.0, 65.0, 62.6, 64.6, 62.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(57.6, 64.0);
    ctx.bezierCurveTo(57.6, 63.5, 58.0, 63.0, 58.6, 63.0);
    ctx.lineTo(58.6, 63.0);
    ctx.bezierCurveTo(59.2, 63.0, 59.6, 63.5, 59.6, 64.0);
    ctx.lineTo(59.6, 64.0);
    ctx.bezierCurveTo(59.6, 64.6, 59.2, 65.0, 58.6, 65.0);
    ctx.lineTo(58.6, 65.0);
    ctx.bezierCurveTo(58.0, 65.0, 57.6, 64.6, 57.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(52.6, 64.0);
    ctx.bezierCurveTo(52.6, 63.5, 53.0, 63.0, 53.6, 63.0);
    ctx.lineTo(53.6, 63.0);
    ctx.bezierCurveTo(54.2, 63.0, 54.6, 63.5, 54.6, 64.0);
    ctx.lineTo(54.6, 64.0);
    ctx.bezierCurveTo(54.6, 64.6, 54.2, 65.0, 53.6, 65.0);
    ctx.lineTo(53.6, 65.0);
    ctx.bezierCurveTo(53.0, 65.0, 52.6, 64.6, 52.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(47.6, 64.0);
    ctx.bezierCurveTo(47.6, 63.5, 48.1, 63.0, 48.6, 63.0);
    ctx.lineTo(48.6, 63.0);
    ctx.bezierCurveTo(49.2, 63.0, 49.6, 63.5, 49.6, 64.0);
    ctx.lineTo(49.6, 64.0);
    ctx.bezierCurveTo(49.6, 64.6, 49.2, 65.0, 48.6, 65.0);
    ctx.lineTo(48.6, 65.0);
    ctx.bezierCurveTo(48.1, 65.0, 47.6, 64.6, 47.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(42.6, 64.0);
    ctx.bezierCurveTo(42.6, 63.5, 43.0, 63.0, 43.6, 63.0);
    ctx.lineTo(43.6, 63.0);
    ctx.bezierCurveTo(44.2, 63.0, 44.6, 63.5, 44.6, 64.0);
    ctx.lineTo(44.6, 64.0);
    ctx.bezierCurveTo(44.6, 64.6, 44.2, 65.0, 43.6, 65.0);
    ctx.lineTo(43.6, 65.0);
    ctx.bezierCurveTo(43.0, 65.0, 42.6, 64.6, 42.6, 64.0);
    ctx.closePath();

    // NUKE/grid/horizontal/1/Samengesteld pad/Pad
    ctx.moveTo(37.6, 64.0);
    ctx.bezierCurveTo(37.6, 63.5, 38.1, 63.0, 38.6, 63.0);
    ctx.lineTo(38.6, 63.0);
    ctx.bezierCurveTo(39.2, 63.0, 39.6, 63.5, 39.6, 64.0);
    ctx.lineTo(39.6, 64.0);
    ctx.bezierCurveTo(39.6, 64.6, 39.2, 65.0, 38.6, 65.0);
    ctx.lineTo(38.6, 65.0);
    ctx.bezierCurveTo(38.1, 65.0, 37.6, 64.6, 37.6, 64.0);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(40, 44, 95));
    ctx.fill();

    // NUKE/grid/horizontal/2

    // NUKE/grid/horizontal/2/Samengesteld pad
    ctx.beginPath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(167.6, 84.0);
    ctx.bezierCurveTo(167.6, 83.5, 168.0, 83.0, 168.6, 83.0);
    ctx.lineTo(168.6, 83.0);
    ctx.bezierCurveTo(169.2, 83.0, 169.6, 83.5, 169.6, 84.0);
    ctx.lineTo(169.6, 84.0);
    ctx.bezierCurveTo(169.6, 84.6, 169.2, 85.0, 168.6, 85.0);
    ctx.lineTo(168.6, 85.0);
    ctx.bezierCurveTo(168.0, 85.0, 167.6, 84.6, 167.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(162.6, 84.0);
    ctx.bezierCurveTo(162.6, 83.5, 163.0, 83.0, 163.6, 83.0);
    ctx.lineTo(163.6, 83.0);
    ctx.bezierCurveTo(164.2, 83.0, 164.6, 83.5, 164.6, 84.0);
    ctx.lineTo(164.6, 84.0);
    ctx.bezierCurveTo(164.6, 84.6, 164.2, 85.0, 163.6, 85.0);
    ctx.lineTo(163.6, 85.0);
    ctx.bezierCurveTo(163.0, 85.0, 162.6, 84.6, 162.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(157.6, 84.0);
    ctx.bezierCurveTo(157.6, 83.5, 158.0, 83.0, 158.6, 83.0);
    ctx.lineTo(158.6, 83.0);
    ctx.bezierCurveTo(159.2, 83.0, 159.6, 83.5, 159.6, 84.0);
    ctx.lineTo(159.6, 84.0);
    ctx.bezierCurveTo(159.6, 84.6, 159.2, 85.0, 158.6, 85.0);
    ctx.lineTo(158.6, 85.0);
    ctx.bezierCurveTo(158.0, 85.0, 157.6, 84.6, 157.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(152.6, 84.0);
    ctx.bezierCurveTo(152.6, 83.5, 153.0, 83.0, 153.6, 83.0);
    ctx.lineTo(153.6, 83.0);
    ctx.bezierCurveTo(154.2, 83.0, 154.6, 83.5, 154.6, 84.0);
    ctx.lineTo(154.6, 84.0);
    ctx.bezierCurveTo(154.6, 84.6, 154.2, 85.0, 153.6, 85.0);
    ctx.lineTo(153.6, 85.0);
    ctx.bezierCurveTo(153.0, 85.0, 152.6, 84.6, 152.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(147.6, 84.0);
    ctx.bezierCurveTo(147.6, 83.5, 148.1, 83.0, 148.6, 83.0);
    ctx.lineTo(148.6, 83.0);
    ctx.bezierCurveTo(149.2, 83.0, 149.6, 83.5, 149.6, 84.0);
    ctx.lineTo(149.6, 84.0);
    ctx.bezierCurveTo(149.6, 84.6, 149.2, 85.0, 148.6, 85.0);
    ctx.lineTo(148.6, 85.0);
    ctx.bezierCurveTo(148.1, 85.0, 147.6, 84.6, 147.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(142.6, 84.0);
    ctx.bezierCurveTo(142.6, 83.5, 143.0, 83.0, 143.6, 83.0);
    ctx.lineTo(143.6, 83.0);
    ctx.bezierCurveTo(144.2, 83.0, 144.6, 83.5, 144.6, 84.0);
    ctx.lineTo(144.6, 84.0);
    ctx.bezierCurveTo(144.6, 84.6, 144.2, 85.0, 143.6, 85.0);
    ctx.lineTo(143.6, 85.0);
    ctx.bezierCurveTo(143.0, 85.0, 142.6, 84.6, 142.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(137.6, 84.0);
    ctx.bezierCurveTo(137.6, 83.5, 138.1, 83.0, 138.6, 83.0);
    ctx.lineTo(138.6, 83.0);
    ctx.bezierCurveTo(139.2, 83.0, 139.6, 83.5, 139.6, 84.0);
    ctx.lineTo(139.6, 84.0);
    ctx.bezierCurveTo(139.6, 84.6, 139.2, 85.0, 138.6, 85.0);
    ctx.lineTo(138.6, 85.0);
    ctx.bezierCurveTo(138.1, 85.0, 137.6, 84.6, 137.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(132.6, 84.0);
    ctx.bezierCurveTo(132.6, 83.5, 133.0, 83.0, 133.6, 83.0);
    ctx.lineTo(133.6, 83.0);
    ctx.bezierCurveTo(134.2, 83.0, 134.6, 83.5, 134.6, 84.0);
    ctx.lineTo(134.6, 84.0);
    ctx.bezierCurveTo(134.6, 84.6, 134.2, 85.0, 133.6, 85.0);
    ctx.lineTo(133.6, 85.0);
    ctx.bezierCurveTo(133.0, 85.0, 132.6, 84.6, 132.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(127.6, 84.0);
    ctx.bezierCurveTo(127.6, 83.5, 128.1, 83.0, 128.6, 83.0);
    ctx.lineTo(128.6, 83.0);
    ctx.bezierCurveTo(129.2, 83.0, 129.6, 83.5, 129.6, 84.0);
    ctx.lineTo(129.6, 84.0);
    ctx.bezierCurveTo(129.6, 84.6, 129.2, 85.0, 128.6, 85.0);
    ctx.lineTo(128.6, 85.0);
    ctx.bezierCurveTo(128.1, 85.0, 127.6, 84.6, 127.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(122.6, 84.0);
    ctx.bezierCurveTo(122.6, 83.5, 123.0, 83.0, 123.6, 83.0);
    ctx.lineTo(123.6, 83.0);
    ctx.bezierCurveTo(124.2, 83.0, 124.6, 83.5, 124.6, 84.0);
    ctx.lineTo(124.6, 84.0);
    ctx.bezierCurveTo(124.6, 84.6, 124.2, 85.0, 123.6, 85.0);
    ctx.lineTo(123.6, 85.0);
    ctx.bezierCurveTo(123.0, 85.0, 122.6, 84.6, 122.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(117.6, 84.0);
    ctx.bezierCurveTo(117.6, 83.5, 118.0, 83.0, 118.6, 83.0);
    ctx.lineTo(118.6, 83.0);
    ctx.bezierCurveTo(119.2, 83.0, 119.6, 83.5, 119.6, 84.0);
    ctx.lineTo(119.6, 84.0);
    ctx.bezierCurveTo(119.6, 84.6, 119.2, 85.0, 118.6, 85.0);
    ctx.lineTo(118.6, 85.0);
    ctx.bezierCurveTo(118.0, 85.0, 117.6, 84.6, 117.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(112.6, 84.0);
    ctx.bezierCurveTo(112.6, 83.5, 113.0, 83.0, 113.6, 83.0);
    ctx.lineTo(113.6, 83.0);
    ctx.bezierCurveTo(114.2, 83.0, 114.6, 83.5, 114.6, 84.0);
    ctx.lineTo(114.6, 84.0);
    ctx.bezierCurveTo(114.6, 84.6, 114.2, 85.0, 113.6, 85.0);
    ctx.lineTo(113.6, 85.0);
    ctx.bezierCurveTo(113.0, 85.0, 112.6, 84.6, 112.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(107.6, 84.0);
    ctx.bezierCurveTo(107.6, 83.5, 108.0, 83.0, 108.6, 83.0);
    ctx.lineTo(108.6, 83.0);
    ctx.bezierCurveTo(109.2, 83.0, 109.6, 83.5, 109.6, 84.0);
    ctx.lineTo(109.6, 84.0);
    ctx.bezierCurveTo(109.6, 84.6, 109.2, 85.0, 108.6, 85.0);
    ctx.lineTo(108.6, 85.0);
    ctx.bezierCurveTo(108.0, 85.0, 107.6, 84.6, 107.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(102.6, 84.0);
    ctx.bezierCurveTo(102.6, 83.5, 103.1, 83.0, 103.6, 83.0);
    ctx.lineTo(103.6, 83.0);
    ctx.bezierCurveTo(104.2, 83.0, 104.6, 83.5, 104.6, 84.0);
    ctx.lineTo(104.6, 84.0);
    ctx.bezierCurveTo(104.6, 84.6, 104.2, 85.0, 103.6, 85.0);
    ctx.lineTo(103.6, 85.0);
    ctx.bezierCurveTo(103.1, 85.0, 102.6, 84.6, 102.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(97.6, 84.0);
    ctx.bezierCurveTo(97.6, 83.5, 98.0, 83.0, 98.6, 83.0);
    ctx.lineTo(98.6, 83.0);
    ctx.bezierCurveTo(99.2, 83.0, 99.6, 83.5, 99.6, 84.0);
    ctx.lineTo(99.6, 84.0);
    ctx.bezierCurveTo(99.6, 84.6, 99.2, 85.0, 98.6, 85.0);
    ctx.lineTo(98.6, 85.0);
    ctx.bezierCurveTo(98.0, 85.0, 97.6, 84.6, 97.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(92.6, 84.0);
    ctx.bezierCurveTo(92.6, 83.5, 93.1, 83.0, 93.6, 83.0);
    ctx.lineTo(93.6, 83.0);
    ctx.bezierCurveTo(94.2, 83.0, 94.6, 83.5, 94.6, 84.0);
    ctx.lineTo(94.6, 84.0);
    ctx.bezierCurveTo(94.6, 84.6, 94.2, 85.0, 93.6, 85.0);
    ctx.lineTo(93.6, 85.0);
    ctx.bezierCurveTo(93.1, 85.0, 92.6, 84.6, 92.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(87.6, 84.0);
    ctx.bezierCurveTo(87.6, 83.5, 88.0, 83.0, 88.6, 83.0);
    ctx.lineTo(88.6, 83.0);
    ctx.bezierCurveTo(89.2, 83.0, 89.6, 83.5, 89.6, 84.0);
    ctx.lineTo(89.6, 84.0);
    ctx.bezierCurveTo(89.6, 84.6, 89.2, 85.0, 88.6, 85.0);
    ctx.lineTo(88.6, 85.0);
    ctx.bezierCurveTo(88.0, 85.0, 87.6, 84.6, 87.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(82.6, 84.0);
    ctx.bezierCurveTo(82.6, 83.5, 83.1, 83.0, 83.6, 83.0);
    ctx.lineTo(83.6, 83.0);
    ctx.bezierCurveTo(84.2, 83.0, 84.6, 83.5, 84.6, 84.0);
    ctx.lineTo(84.6, 84.0);
    ctx.bezierCurveTo(84.6, 84.6, 84.2, 85.0, 83.6, 85.0);
    ctx.lineTo(83.6, 85.0);
    ctx.bezierCurveTo(83.1, 85.0, 82.6, 84.6, 82.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(77.6, 84.0);
    ctx.bezierCurveTo(77.6, 83.5, 78.0, 83.0, 78.6, 83.0);
    ctx.lineTo(78.6, 83.0);
    ctx.bezierCurveTo(79.2, 83.0, 79.6, 83.5, 79.6, 84.0);
    ctx.lineTo(79.6, 84.0);
    ctx.bezierCurveTo(79.6, 84.6, 79.2, 85.0, 78.6, 85.0);
    ctx.lineTo(78.6, 85.0);
    ctx.bezierCurveTo(78.0, 85.0, 77.6, 84.6, 77.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(72.6, 84.0);
    ctx.bezierCurveTo(72.6, 83.5, 73.0, 83.0, 73.6, 83.0);
    ctx.lineTo(73.6, 83.0);
    ctx.bezierCurveTo(74.2, 83.0, 74.6, 83.5, 74.6, 84.0);
    ctx.lineTo(74.6, 84.0);
    ctx.bezierCurveTo(74.6, 84.6, 74.2, 85.0, 73.6, 85.0);
    ctx.lineTo(73.6, 85.0);
    ctx.bezierCurveTo(73.0, 85.0, 72.6, 84.6, 72.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(67.6, 84.0);
    ctx.bezierCurveTo(67.6, 83.5, 68.0, 83.0, 68.6, 83.0);
    ctx.lineTo(68.6, 83.0);
    ctx.bezierCurveTo(69.2, 83.0, 69.6, 83.5, 69.6, 84.0);
    ctx.lineTo(69.6, 84.0);
    ctx.bezierCurveTo(69.6, 84.6, 69.2, 85.0, 68.6, 85.0);
    ctx.lineTo(68.6, 85.0);
    ctx.bezierCurveTo(68.0, 85.0, 67.6, 84.6, 67.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(62.6, 84.0);
    ctx.bezierCurveTo(62.6, 83.5, 63.0, 83.0, 63.6, 83.0);
    ctx.lineTo(63.6, 83.0);
    ctx.bezierCurveTo(64.2, 83.0, 64.6, 83.5, 64.6, 84.0);
    ctx.lineTo(64.6, 84.0);
    ctx.bezierCurveTo(64.6, 84.6, 64.2, 85.0, 63.6, 85.0);
    ctx.lineTo(63.6, 85.0);
    ctx.bezierCurveTo(63.0, 85.0, 62.6, 84.6, 62.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(57.6, 84.0);
    ctx.bezierCurveTo(57.6, 83.5, 58.0, 83.0, 58.6, 83.0);
    ctx.lineTo(58.6, 83.0);
    ctx.bezierCurveTo(59.2, 83.0, 59.6, 83.5, 59.6, 84.0);
    ctx.lineTo(59.6, 84.0);
    ctx.bezierCurveTo(59.6, 84.6, 59.2, 85.0, 58.6, 85.0);
    ctx.lineTo(58.6, 85.0);
    ctx.bezierCurveTo(58.0, 85.0, 57.6, 84.6, 57.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(52.6, 84.0);
    ctx.bezierCurveTo(52.6, 83.5, 53.0, 83.0, 53.6, 83.0);
    ctx.lineTo(53.6, 83.0);
    ctx.bezierCurveTo(54.2, 83.0, 54.6, 83.5, 54.6, 84.0);
    ctx.lineTo(54.6, 84.0);
    ctx.bezierCurveTo(54.6, 84.6, 54.2, 85.0, 53.6, 85.0);
    ctx.lineTo(53.6, 85.0);
    ctx.bezierCurveTo(53.0, 85.0, 52.6, 84.6, 52.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(47.6, 84.0);
    ctx.bezierCurveTo(47.6, 83.5, 48.1, 83.0, 48.6, 83.0);
    ctx.lineTo(48.6, 83.0);
    ctx.bezierCurveTo(49.2, 83.0, 49.6, 83.5, 49.6, 84.0);
    ctx.lineTo(49.6, 84.0);
    ctx.bezierCurveTo(49.6, 84.6, 49.2, 85.0, 48.6, 85.0);
    ctx.lineTo(48.6, 85.0);
    ctx.bezierCurveTo(48.1, 85.0, 47.6, 84.6, 47.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(42.6, 84.0);
    ctx.bezierCurveTo(42.6, 83.5, 43.0, 83.0, 43.6, 83.0);
    ctx.lineTo(43.6, 83.0);
    ctx.bezierCurveTo(44.2, 83.0, 44.6, 83.5, 44.6, 84.0);
    ctx.lineTo(44.6, 84.0);
    ctx.bezierCurveTo(44.6, 84.6, 44.2, 85.0, 43.6, 85.0);
    ctx.lineTo(43.6, 85.0);
    ctx.bezierCurveTo(43.0, 85.0, 42.6, 84.6, 42.6, 84.0);
    ctx.closePath();

    // NUKE/grid/horizontal/2/Samengesteld pad/Pad
    ctx.moveTo(37.6, 84.0);
    ctx.bezierCurveTo(37.6, 83.5, 38.1, 83.0, 38.6, 83.0);
    ctx.lineTo(38.6, 83.0);
    ctx.bezierCurveTo(39.2, 83.0, 39.6, 83.5, 39.6, 84.0);
    ctx.lineTo(39.6, 84.0);
    ctx.bezierCurveTo(39.6, 84.6, 39.2, 85.0, 38.6, 85.0);
    ctx.lineTo(38.6, 85.0);
    ctx.bezierCurveTo(38.1, 85.0, 37.6, 84.6, 37.6, 84.0);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(40, 44, 95));
    ctx.fill();

    // NUKE/grid/horizontal/3

    // NUKE/grid/horizontal/3/Samengesteld pad
    ctx.beginPath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(167.6, 104.0);
    ctx.bezierCurveTo(167.6, 103.5, 168.0, 103.0, 168.6, 103.0);
    ctx.lineTo(168.6, 103.0);
    ctx.bezierCurveTo(169.2, 103.0, 169.6, 103.5, 169.6, 104.0);
    ctx.lineTo(169.6, 104.0);
    ctx.bezierCurveTo(169.6, 104.6, 169.2, 105.0, 168.6, 105.0);
    ctx.lineTo(168.6, 105.0);
    ctx.bezierCurveTo(168.0, 105.0, 167.6, 104.6, 167.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(162.6, 104.0);
    ctx.bezierCurveTo(162.6, 103.5, 163.0, 103.0, 163.6, 103.0);
    ctx.lineTo(163.6, 103.0);
    ctx.bezierCurveTo(164.2, 103.0, 164.6, 103.5, 164.6, 104.0);
    ctx.lineTo(164.6, 104.0);
    ctx.bezierCurveTo(164.6, 104.6, 164.2, 105.0, 163.6, 105.0);
    ctx.lineTo(163.6, 105.0);
    ctx.bezierCurveTo(163.0, 105.0, 162.6, 104.6, 162.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(157.6, 104.0);
    ctx.bezierCurveTo(157.6, 103.5, 158.0, 103.0, 158.6, 103.0);
    ctx.lineTo(158.6, 103.0);
    ctx.bezierCurveTo(159.2, 103.0, 159.6, 103.5, 159.6, 104.0);
    ctx.lineTo(159.6, 104.0);
    ctx.bezierCurveTo(159.6, 104.6, 159.2, 105.0, 158.6, 105.0);
    ctx.lineTo(158.6, 105.0);
    ctx.bezierCurveTo(158.0, 105.0, 157.6, 104.6, 157.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(152.6, 104.0);
    ctx.bezierCurveTo(152.6, 103.5, 153.0, 103.0, 153.6, 103.0);
    ctx.lineTo(153.6, 103.0);
    ctx.bezierCurveTo(154.2, 103.0, 154.6, 103.5, 154.6, 104.0);
    ctx.lineTo(154.6, 104.0);
    ctx.bezierCurveTo(154.6, 104.6, 154.2, 105.0, 153.6, 105.0);
    ctx.lineTo(153.6, 105.0);
    ctx.bezierCurveTo(153.0, 105.0, 152.6, 104.6, 152.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(147.6, 104.0);
    ctx.bezierCurveTo(147.6, 103.5, 148.1, 103.0, 148.6, 103.0);
    ctx.lineTo(148.6, 103.0);
    ctx.bezierCurveTo(149.2, 103.0, 149.6, 103.5, 149.6, 104.0);
    ctx.lineTo(149.6, 104.0);
    ctx.bezierCurveTo(149.6, 104.6, 149.2, 105.0, 148.6, 105.0);
    ctx.lineTo(148.6, 105.0);
    ctx.bezierCurveTo(148.1, 105.0, 147.6, 104.6, 147.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(142.6, 104.0);
    ctx.bezierCurveTo(142.6, 103.5, 143.0, 103.0, 143.6, 103.0);
    ctx.lineTo(143.6, 103.0);
    ctx.bezierCurveTo(144.2, 103.0, 144.6, 103.5, 144.6, 104.0);
    ctx.lineTo(144.6, 104.0);
    ctx.bezierCurveTo(144.6, 104.6, 144.2, 105.0, 143.6, 105.0);
    ctx.lineTo(143.6, 105.0);
    ctx.bezierCurveTo(143.0, 105.0, 142.6, 104.6, 142.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(137.6, 104.0);
    ctx.bezierCurveTo(137.6, 103.5, 138.1, 103.0, 138.6, 103.0);
    ctx.lineTo(138.6, 103.0);
    ctx.bezierCurveTo(139.2, 103.0, 139.6, 103.5, 139.6, 104.0);
    ctx.lineTo(139.6, 104.0);
    ctx.bezierCurveTo(139.6, 104.6, 139.2, 105.0, 138.6, 105.0);
    ctx.lineTo(138.6, 105.0);
    ctx.bezierCurveTo(138.1, 105.0, 137.6, 104.6, 137.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(132.6, 104.0);
    ctx.bezierCurveTo(132.6, 103.5, 133.0, 103.0, 133.6, 103.0);
    ctx.lineTo(133.6, 103.0);
    ctx.bezierCurveTo(134.2, 103.0, 134.6, 103.5, 134.6, 104.0);
    ctx.lineTo(134.6, 104.0);
    ctx.bezierCurveTo(134.6, 104.6, 134.2, 105.0, 133.6, 105.0);
    ctx.lineTo(133.6, 105.0);
    ctx.bezierCurveTo(133.0, 105.0, 132.6, 104.6, 132.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(127.6, 104.0);
    ctx.bezierCurveTo(127.6, 103.5, 128.1, 103.0, 128.6, 103.0);
    ctx.lineTo(128.6, 103.0);
    ctx.bezierCurveTo(129.2, 103.0, 129.6, 103.5, 129.6, 104.0);
    ctx.lineTo(129.6, 104.0);
    ctx.bezierCurveTo(129.6, 104.6, 129.2, 105.0, 128.6, 105.0);
    ctx.lineTo(128.6, 105.0);
    ctx.bezierCurveTo(128.1, 105.0, 127.6, 104.6, 127.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(122.6, 104.0);
    ctx.bezierCurveTo(122.6, 103.5, 123.0, 103.0, 123.6, 103.0);
    ctx.lineTo(123.6, 103.0);
    ctx.bezierCurveTo(124.2, 103.0, 124.6, 103.5, 124.6, 104.0);
    ctx.lineTo(124.6, 104.0);
    ctx.bezierCurveTo(124.6, 104.6, 124.2, 105.0, 123.6, 105.0);
    ctx.lineTo(123.6, 105.0);
    ctx.bezierCurveTo(123.0, 105.0, 122.6, 104.6, 122.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(117.6, 104.0);
    ctx.bezierCurveTo(117.6, 103.5, 118.0, 103.0, 118.6, 103.0);
    ctx.lineTo(118.6, 103.0);
    ctx.bezierCurveTo(119.2, 103.0, 119.6, 103.5, 119.6, 104.0);
    ctx.lineTo(119.6, 104.0);
    ctx.bezierCurveTo(119.6, 104.6, 119.2, 105.0, 118.6, 105.0);
    ctx.lineTo(118.6, 105.0);
    ctx.bezierCurveTo(118.0, 105.0, 117.6, 104.6, 117.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(112.6, 104.0);
    ctx.bezierCurveTo(112.6, 103.5, 113.0, 103.0, 113.6, 103.0);
    ctx.lineTo(113.6, 103.0);
    ctx.bezierCurveTo(114.2, 103.0, 114.6, 103.5, 114.6, 104.0);
    ctx.lineTo(114.6, 104.0);
    ctx.bezierCurveTo(114.6, 104.6, 114.2, 105.0, 113.6, 105.0);
    ctx.lineTo(113.6, 105.0);
    ctx.bezierCurveTo(113.0, 105.0, 112.6, 104.6, 112.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(107.6, 104.0);
    ctx.bezierCurveTo(107.6, 103.5, 108.0, 103.0, 108.6, 103.0);
    ctx.lineTo(108.6, 103.0);
    ctx.bezierCurveTo(109.2, 103.0, 109.6, 103.5, 109.6, 104.0);
    ctx.lineTo(109.6, 104.0);
    ctx.bezierCurveTo(109.6, 104.6, 109.2, 105.0, 108.6, 105.0);
    ctx.lineTo(108.6, 105.0);
    ctx.bezierCurveTo(108.0, 105.0, 107.6, 104.6, 107.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(102.6, 104.0);
    ctx.bezierCurveTo(102.6, 103.5, 103.1, 103.0, 103.6, 103.0);
    ctx.lineTo(103.6, 103.0);
    ctx.bezierCurveTo(104.2, 103.0, 104.6, 103.5, 104.6, 104.0);
    ctx.lineTo(104.6, 104.0);
    ctx.bezierCurveTo(104.6, 104.6, 104.2, 105.0, 103.6, 105.0);
    ctx.lineTo(103.6, 105.0);
    ctx.bezierCurveTo(103.1, 105.0, 102.6, 104.6, 102.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(97.6, 104.0);
    ctx.bezierCurveTo(97.6, 103.5, 98.0, 103.0, 98.6, 103.0);
    ctx.lineTo(98.6, 103.0);
    ctx.bezierCurveTo(99.2, 103.0, 99.6, 103.5, 99.6, 104.0);
    ctx.lineTo(99.6, 104.0);
    ctx.bezierCurveTo(99.6, 104.6, 99.2, 105.0, 98.6, 105.0);
    ctx.lineTo(98.6, 105.0);
    ctx.bezierCurveTo(98.0, 105.0, 97.6, 104.6, 97.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(92.6, 104.0);
    ctx.bezierCurveTo(92.6, 103.5, 93.1, 103.0, 93.6, 103.0);
    ctx.lineTo(93.6, 103.0);
    ctx.bezierCurveTo(94.2, 103.0, 94.6, 103.5, 94.6, 104.0);
    ctx.lineTo(94.6, 104.0);
    ctx.bezierCurveTo(94.6, 104.6, 94.2, 105.0, 93.6, 105.0);
    ctx.lineTo(93.6, 105.0);
    ctx.bezierCurveTo(93.1, 105.0, 92.6, 104.6, 92.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(87.6, 104.0);
    ctx.bezierCurveTo(87.6, 103.5, 88.0, 103.0, 88.6, 103.0);
    ctx.lineTo(88.6, 103.0);
    ctx.bezierCurveTo(89.2, 103.0, 89.6, 103.5, 89.6, 104.0);
    ctx.lineTo(89.6, 104.0);
    ctx.bezierCurveTo(89.6, 104.6, 89.2, 105.0, 88.6, 105.0);
    ctx.lineTo(88.6, 105.0);
    ctx.bezierCurveTo(88.0, 105.0, 87.6, 104.6, 87.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(82.6, 104.0);
    ctx.bezierCurveTo(82.6, 103.5, 83.1, 103.0, 83.6, 103.0);
    ctx.lineTo(83.6, 103.0);
    ctx.bezierCurveTo(84.2, 103.0, 84.6, 103.5, 84.6, 104.0);
    ctx.lineTo(84.6, 104.0);
    ctx.bezierCurveTo(84.6, 104.6, 84.2, 105.0, 83.6, 105.0);
    ctx.lineTo(83.6, 105.0);
    ctx.bezierCurveTo(83.1, 105.0, 82.6, 104.6, 82.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(77.6, 104.0);
    ctx.bezierCurveTo(77.6, 103.5, 78.0, 103.0, 78.6, 103.0);
    ctx.lineTo(78.6, 103.0);
    ctx.bezierCurveTo(79.2, 103.0, 79.6, 103.5, 79.6, 104.0);
    ctx.lineTo(79.6, 104.0);
    ctx.bezierCurveTo(79.6, 104.6, 79.2, 105.0, 78.6, 105.0);
    ctx.lineTo(78.6, 105.0);
    ctx.bezierCurveTo(78.0, 105.0, 77.6, 104.6, 77.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(72.6, 104.0);
    ctx.bezierCurveTo(72.6, 103.5, 73.0, 103.0, 73.6, 103.0);
    ctx.lineTo(73.6, 103.0);
    ctx.bezierCurveTo(74.2, 103.0, 74.6, 103.5, 74.6, 104.0);
    ctx.lineTo(74.6, 104.0);
    ctx.bezierCurveTo(74.6, 104.6, 74.2, 105.0, 73.6, 105.0);
    ctx.lineTo(73.6, 105.0);
    ctx.bezierCurveTo(73.0, 105.0, 72.6, 104.6, 72.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(67.6, 104.0);
    ctx.bezierCurveTo(67.6, 103.5, 68.0, 103.0, 68.6, 103.0);
    ctx.lineTo(68.6, 103.0);
    ctx.bezierCurveTo(69.2, 103.0, 69.6, 103.5, 69.6, 104.0);
    ctx.lineTo(69.6, 104.0);
    ctx.bezierCurveTo(69.6, 104.6, 69.2, 105.0, 68.6, 105.0);
    ctx.lineTo(68.6, 105.0);
    ctx.bezierCurveTo(68.0, 105.0, 67.6, 104.6, 67.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(62.6, 104.0);
    ctx.bezierCurveTo(62.6, 103.5, 63.0, 103.0, 63.6, 103.0);
    ctx.lineTo(63.6, 103.0);
    ctx.bezierCurveTo(64.2, 103.0, 64.6, 103.5, 64.6, 104.0);
    ctx.lineTo(64.6, 104.0);
    ctx.bezierCurveTo(64.6, 104.6, 64.2, 105.0, 63.6, 105.0);
    ctx.lineTo(63.6, 105.0);
    ctx.bezierCurveTo(63.0, 105.0, 62.6, 104.6, 62.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(57.6, 104.0);
    ctx.bezierCurveTo(57.6, 103.5, 58.0, 103.0, 58.6, 103.0);
    ctx.lineTo(58.6, 103.0);
    ctx.bezierCurveTo(59.2, 103.0, 59.6, 103.5, 59.6, 104.0);
    ctx.lineTo(59.6, 104.0);
    ctx.bezierCurveTo(59.6, 104.6, 59.2, 105.0, 58.6, 105.0);
    ctx.lineTo(58.6, 105.0);
    ctx.bezierCurveTo(58.0, 105.0, 57.6, 104.6, 57.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(52.6, 104.0);
    ctx.bezierCurveTo(52.6, 103.5, 53.0, 103.0, 53.6, 103.0);
    ctx.lineTo(53.6, 103.0);
    ctx.bezierCurveTo(54.2, 103.0, 54.6, 103.5, 54.6, 104.0);
    ctx.lineTo(54.6, 104.0);
    ctx.bezierCurveTo(54.6, 104.6, 54.2, 105.0, 53.6, 105.0);
    ctx.lineTo(53.6, 105.0);
    ctx.bezierCurveTo(53.0, 105.0, 52.6, 104.6, 52.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(47.6, 104.0);
    ctx.bezierCurveTo(47.6, 103.5, 48.1, 103.0, 48.6, 103.0);
    ctx.lineTo(48.6, 103.0);
    ctx.bezierCurveTo(49.2, 103.0, 49.6, 103.5, 49.6, 104.0);
    ctx.lineTo(49.6, 104.0);
    ctx.bezierCurveTo(49.6, 104.6, 49.2, 105.0, 48.6, 105.0);
    ctx.lineTo(48.6, 105.0);
    ctx.bezierCurveTo(48.1, 105.0, 47.6, 104.6, 47.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(42.6, 104.0);
    ctx.bezierCurveTo(42.6, 103.5, 43.0, 103.0, 43.6, 103.0);
    ctx.lineTo(43.6, 103.0);
    ctx.bezierCurveTo(44.2, 103.0, 44.6, 103.5, 44.6, 104.0);
    ctx.lineTo(44.6, 104.0);
    ctx.bezierCurveTo(44.6, 104.6, 44.2, 105.0, 43.6, 105.0);
    ctx.lineTo(43.6, 105.0);
    ctx.bezierCurveTo(43.0, 105.0, 42.6, 104.6, 42.6, 104.0);
    ctx.closePath();

    // NUKE/grid/horizontal/3/Samengesteld pad/Pad
    ctx.moveTo(37.6, 104.0);
    ctx.bezierCurveTo(37.6, 103.5, 38.1, 103.0, 38.6, 103.0);
    ctx.lineTo(38.6, 103.0);
    ctx.bezierCurveTo(39.2, 103.0, 39.6, 103.5, 39.6, 104.0);
    ctx.lineTo(39.6, 104.0);
    ctx.bezierCurveTo(39.6, 104.6, 39.2, 105.0, 38.6, 105.0);
    ctx.lineTo(38.6, 105.0);
    ctx.bezierCurveTo(38.1, 105.0, 37.6, 104.6, 37.6, 104.0);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(40, 44, 95));
    ctx.fill();

    // NUKE/grid/horizontal/4

    // NUKE/grid/horizontal/4/Samengesteld pad
    ctx.beginPath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(167.6, 124.0);
    ctx.bezierCurveTo(167.6, 123.5, 168.0, 123.0, 168.6, 123.0);
    ctx.lineTo(168.6, 123.0);
    ctx.bezierCurveTo(169.2, 123.0, 169.6, 123.5, 169.6, 124.0);
    ctx.lineTo(169.6, 124.0);
    ctx.bezierCurveTo(169.6, 124.6, 169.2, 125.0, 168.6, 125.0);
    ctx.lineTo(168.6, 125.0);
    ctx.bezierCurveTo(168.0, 125.0, 167.6, 124.6, 167.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(162.6, 124.0);
    ctx.bezierCurveTo(162.6, 123.5, 163.0, 123.0, 163.6, 123.0);
    ctx.lineTo(163.6, 123.0);
    ctx.bezierCurveTo(164.2, 123.0, 164.6, 123.5, 164.6, 124.0);
    ctx.lineTo(164.6, 124.0);
    ctx.bezierCurveTo(164.6, 124.6, 164.2, 125.0, 163.6, 125.0);
    ctx.lineTo(163.6, 125.0);
    ctx.bezierCurveTo(163.0, 125.0, 162.6, 124.6, 162.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(157.6, 124.0);
    ctx.bezierCurveTo(157.6, 123.5, 158.0, 123.0, 158.6, 123.0);
    ctx.lineTo(158.6, 123.0);
    ctx.bezierCurveTo(159.2, 123.0, 159.6, 123.5, 159.6, 124.0);
    ctx.lineTo(159.6, 124.0);
    ctx.bezierCurveTo(159.6, 124.6, 159.2, 125.0, 158.6, 125.0);
    ctx.lineTo(158.6, 125.0);
    ctx.bezierCurveTo(158.0, 125.0, 157.6, 124.6, 157.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(152.6, 124.0);
    ctx.bezierCurveTo(152.6, 123.5, 153.0, 123.0, 153.6, 123.0);
    ctx.lineTo(153.6, 123.0);
    ctx.bezierCurveTo(154.2, 123.0, 154.6, 123.5, 154.6, 124.0);
    ctx.lineTo(154.6, 124.0);
    ctx.bezierCurveTo(154.6, 124.6, 154.2, 125.0, 153.6, 125.0);
    ctx.lineTo(153.6, 125.0);
    ctx.bezierCurveTo(153.0, 125.0, 152.6, 124.6, 152.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(147.6, 124.0);
    ctx.bezierCurveTo(147.6, 123.5, 148.1, 123.0, 148.6, 123.0);
    ctx.lineTo(148.6, 123.0);
    ctx.bezierCurveTo(149.2, 123.0, 149.6, 123.5, 149.6, 124.0);
    ctx.lineTo(149.6, 124.0);
    ctx.bezierCurveTo(149.6, 124.6, 149.2, 125.0, 148.6, 125.0);
    ctx.lineTo(148.6, 125.0);
    ctx.bezierCurveTo(148.1, 125.0, 147.6, 124.6, 147.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(142.6, 124.0);
    ctx.bezierCurveTo(142.6, 123.5, 143.0, 123.0, 143.6, 123.0);
    ctx.lineTo(143.6, 123.0);
    ctx.bezierCurveTo(144.2, 123.0, 144.6, 123.5, 144.6, 124.0);
    ctx.lineTo(144.6, 124.0);
    ctx.bezierCurveTo(144.6, 124.6, 144.2, 125.0, 143.6, 125.0);
    ctx.lineTo(143.6, 125.0);
    ctx.bezierCurveTo(143.0, 125.0, 142.6, 124.6, 142.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(137.6, 124.0);
    ctx.bezierCurveTo(137.6, 123.5, 138.1, 123.0, 138.6, 123.0);
    ctx.lineTo(138.6, 123.0);
    ctx.bezierCurveTo(139.2, 123.0, 139.6, 123.5, 139.6, 124.0);
    ctx.lineTo(139.6, 124.0);
    ctx.bezierCurveTo(139.6, 124.6, 139.2, 125.0, 138.6, 125.0);
    ctx.lineTo(138.6, 125.0);
    ctx.bezierCurveTo(138.1, 125.0, 137.6, 124.6, 137.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(132.6, 124.0);
    ctx.bezierCurveTo(132.6, 123.5, 133.0, 123.0, 133.6, 123.0);
    ctx.lineTo(133.6, 123.0);
    ctx.bezierCurveTo(134.2, 123.0, 134.6, 123.5, 134.6, 124.0);
    ctx.lineTo(134.6, 124.0);
    ctx.bezierCurveTo(134.6, 124.6, 134.2, 125.0, 133.6, 125.0);
    ctx.lineTo(133.6, 125.0);
    ctx.bezierCurveTo(133.0, 125.0, 132.6, 124.6, 132.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(127.6, 124.0);
    ctx.bezierCurveTo(127.6, 123.5, 128.1, 123.0, 128.6, 123.0);
    ctx.lineTo(128.6, 123.0);
    ctx.bezierCurveTo(129.2, 123.0, 129.6, 123.5, 129.6, 124.0);
    ctx.lineTo(129.6, 124.0);
    ctx.bezierCurveTo(129.6, 124.6, 129.2, 125.0, 128.6, 125.0);
    ctx.lineTo(128.6, 125.0);
    ctx.bezierCurveTo(128.1, 125.0, 127.6, 124.6, 127.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(122.6, 124.0);
    ctx.bezierCurveTo(122.6, 123.5, 123.0, 123.0, 123.6, 123.0);
    ctx.lineTo(123.6, 123.0);
    ctx.bezierCurveTo(124.2, 123.0, 124.6, 123.5, 124.6, 124.0);
    ctx.lineTo(124.6, 124.0);
    ctx.bezierCurveTo(124.6, 124.6, 124.2, 125.0, 123.6, 125.0);
    ctx.lineTo(123.6, 125.0);
    ctx.bezierCurveTo(123.0, 125.0, 122.6, 124.6, 122.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(117.6, 124.0);
    ctx.bezierCurveTo(117.6, 123.5, 118.0, 123.0, 118.6, 123.0);
    ctx.lineTo(118.6, 123.0);
    ctx.bezierCurveTo(119.2, 123.0, 119.6, 123.5, 119.6, 124.0);
    ctx.lineTo(119.6, 124.0);
    ctx.bezierCurveTo(119.6, 124.6, 119.2, 125.0, 118.6, 125.0);
    ctx.lineTo(118.6, 125.0);
    ctx.bezierCurveTo(118.0, 125.0, 117.6, 124.6, 117.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(112.6, 124.0);
    ctx.bezierCurveTo(112.6, 123.5, 113.0, 123.0, 113.6, 123.0);
    ctx.lineTo(113.6, 123.0);
    ctx.bezierCurveTo(114.2, 123.0, 114.6, 123.5, 114.6, 124.0);
    ctx.lineTo(114.6, 124.0);
    ctx.bezierCurveTo(114.6, 124.6, 114.2, 125.0, 113.6, 125.0);
    ctx.lineTo(113.6, 125.0);
    ctx.bezierCurveTo(113.0, 125.0, 112.6, 124.6, 112.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(107.6, 124.0);
    ctx.bezierCurveTo(107.6, 123.5, 108.0, 123.0, 108.6, 123.0);
    ctx.lineTo(108.6, 123.0);
    ctx.bezierCurveTo(109.2, 123.0, 109.6, 123.5, 109.6, 124.0);
    ctx.lineTo(109.6, 124.0);
    ctx.bezierCurveTo(109.6, 124.6, 109.2, 125.0, 108.6, 125.0);
    ctx.lineTo(108.6, 125.0);
    ctx.bezierCurveTo(108.0, 125.0, 107.6, 124.6, 107.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(102.6, 124.0);
    ctx.bezierCurveTo(102.6, 123.5, 103.1, 123.0, 103.6, 123.0);
    ctx.lineTo(103.6, 123.0);
    ctx.bezierCurveTo(104.2, 123.0, 104.6, 123.5, 104.6, 124.0);
    ctx.lineTo(104.6, 124.0);
    ctx.bezierCurveTo(104.6, 124.6, 104.2, 125.0, 103.6, 125.0);
    ctx.lineTo(103.6, 125.0);
    ctx.bezierCurveTo(103.1, 125.0, 102.6, 124.6, 102.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(97.6, 124.0);
    ctx.bezierCurveTo(97.6, 123.5, 98.0, 123.0, 98.6, 123.0);
    ctx.lineTo(98.6, 123.0);
    ctx.bezierCurveTo(99.2, 123.0, 99.6, 123.5, 99.6, 124.0);
    ctx.lineTo(99.6, 124.0);
    ctx.bezierCurveTo(99.6, 124.6, 99.2, 125.0, 98.6, 125.0);
    ctx.lineTo(98.6, 125.0);
    ctx.bezierCurveTo(98.0, 125.0, 97.6, 124.6, 97.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(92.6, 124.0);
    ctx.bezierCurveTo(92.6, 123.5, 93.1, 123.0, 93.6, 123.0);
    ctx.lineTo(93.6, 123.0);
    ctx.bezierCurveTo(94.2, 123.0, 94.6, 123.5, 94.6, 124.0);
    ctx.lineTo(94.6, 124.0);
    ctx.bezierCurveTo(94.6, 124.6, 94.2, 125.0, 93.6, 125.0);
    ctx.lineTo(93.6, 125.0);
    ctx.bezierCurveTo(93.1, 125.0, 92.6, 124.6, 92.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(87.6, 124.0);
    ctx.bezierCurveTo(87.6, 123.5, 88.0, 123.0, 88.6, 123.0);
    ctx.lineTo(88.6, 123.0);
    ctx.bezierCurveTo(89.2, 123.0, 89.6, 123.5, 89.6, 124.0);
    ctx.lineTo(89.6, 124.0);
    ctx.bezierCurveTo(89.6, 124.6, 89.2, 125.0, 88.6, 125.0);
    ctx.lineTo(88.6, 125.0);
    ctx.bezierCurveTo(88.0, 125.0, 87.6, 124.6, 87.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(82.6, 124.0);
    ctx.bezierCurveTo(82.6, 123.5, 83.1, 123.0, 83.6, 123.0);
    ctx.lineTo(83.6, 123.0);
    ctx.bezierCurveTo(84.2, 123.0, 84.6, 123.5, 84.6, 124.0);
    ctx.lineTo(84.6, 124.0);
    ctx.bezierCurveTo(84.6, 124.6, 84.2, 125.0, 83.6, 125.0);
    ctx.lineTo(83.6, 125.0);
    ctx.bezierCurveTo(83.1, 125.0, 82.6, 124.6, 82.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(77.6, 124.0);
    ctx.bezierCurveTo(77.6, 123.5, 78.0, 123.0, 78.6, 123.0);
    ctx.lineTo(78.6, 123.0);
    ctx.bezierCurveTo(79.2, 123.0, 79.6, 123.5, 79.6, 124.0);
    ctx.lineTo(79.6, 124.0);
    ctx.bezierCurveTo(79.6, 124.6, 79.2, 125.0, 78.6, 125.0);
    ctx.lineTo(78.6, 125.0);
    ctx.bezierCurveTo(78.0, 125.0, 77.6, 124.6, 77.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(72.6, 124.0);
    ctx.bezierCurveTo(72.6, 123.5, 73.0, 123.0, 73.6, 123.0);
    ctx.lineTo(73.6, 123.0);
    ctx.bezierCurveTo(74.2, 123.0, 74.6, 123.5, 74.6, 124.0);
    ctx.lineTo(74.6, 124.0);
    ctx.bezierCurveTo(74.6, 124.6, 74.2, 125.0, 73.6, 125.0);
    ctx.lineTo(73.6, 125.0);
    ctx.bezierCurveTo(73.0, 125.0, 72.6, 124.6, 72.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(67.6, 124.0);
    ctx.bezierCurveTo(67.6, 123.5, 68.0, 123.0, 68.6, 123.0);
    ctx.lineTo(68.6, 123.0);
    ctx.bezierCurveTo(69.2, 123.0, 69.6, 123.5, 69.6, 124.0);
    ctx.lineTo(69.6, 124.0);
    ctx.bezierCurveTo(69.6, 124.6, 69.2, 125.0, 68.6, 125.0);
    ctx.lineTo(68.6, 125.0);
    ctx.bezierCurveTo(68.0, 125.0, 67.6, 124.6, 67.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(62.6, 124.0);
    ctx.bezierCurveTo(62.6, 123.5, 63.0, 123.0, 63.6, 123.0);
    ctx.lineTo(63.6, 123.0);
    ctx.bezierCurveTo(64.2, 123.0, 64.6, 123.5, 64.6, 124.0);
    ctx.lineTo(64.6, 124.0);
    ctx.bezierCurveTo(64.6, 124.6, 64.2, 125.0, 63.6, 125.0);
    ctx.lineTo(63.6, 125.0);
    ctx.bezierCurveTo(63.0, 125.0, 62.6, 124.6, 62.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(57.6, 124.0);
    ctx.bezierCurveTo(57.6, 123.5, 58.0, 123.0, 58.6, 123.0);
    ctx.lineTo(58.6, 123.0);
    ctx.bezierCurveTo(59.2, 123.0, 59.6, 123.5, 59.6, 124.0);
    ctx.lineTo(59.6, 124.0);
    ctx.bezierCurveTo(59.6, 124.6, 59.2, 125.0, 58.6, 125.0);
    ctx.lineTo(58.6, 125.0);
    ctx.bezierCurveTo(58.0, 125.0, 57.6, 124.6, 57.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(52.6, 124.0);
    ctx.bezierCurveTo(52.6, 123.5, 53.0, 123.0, 53.6, 123.0);
    ctx.lineTo(53.6, 123.0);
    ctx.bezierCurveTo(54.2, 123.0, 54.6, 123.5, 54.6, 124.0);
    ctx.lineTo(54.6, 124.0);
    ctx.bezierCurveTo(54.6, 124.6, 54.2, 125.0, 53.6, 125.0);
    ctx.lineTo(53.6, 125.0);
    ctx.bezierCurveTo(53.0, 125.0, 52.6, 124.6, 52.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(47.6, 124.0);
    ctx.bezierCurveTo(47.6, 123.5, 48.1, 123.0, 48.6, 123.0);
    ctx.lineTo(48.6, 123.0);
    ctx.bezierCurveTo(49.2, 123.0, 49.6, 123.5, 49.6, 124.0);
    ctx.lineTo(49.6, 124.0);
    ctx.bezierCurveTo(49.6, 124.6, 49.2, 125.0, 48.6, 125.0);
    ctx.lineTo(48.6, 125.0);
    ctx.bezierCurveTo(48.1, 125.0, 47.6, 124.6, 47.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(42.6, 124.0);
    ctx.bezierCurveTo(42.6, 123.5, 43.0, 123.0, 43.6, 123.0);
    ctx.lineTo(43.6, 123.0);
    ctx.bezierCurveTo(44.2, 123.0, 44.6, 123.5, 44.6, 124.0);
    ctx.lineTo(44.6, 124.0);
    ctx.bezierCurveTo(44.6, 124.6, 44.2, 125.0, 43.6, 125.0);
    ctx.lineTo(43.6, 125.0);
    ctx.bezierCurveTo(43.0, 125.0, 42.6, 124.6, 42.6, 124.0);
    ctx.closePath();

    // NUKE/grid/horizontal/4/Samengesteld pad/Pad
    ctx.moveTo(37.6, 124.0);
    ctx.bezierCurveTo(37.6, 123.5, 38.1, 123.0, 38.6, 123.0);
    ctx.lineTo(38.6, 123.0);
    ctx.bezierCurveTo(39.2, 123.0, 39.6, 123.5, 39.6, 124.0);
    ctx.bezierCurveTo(39.6, 124.6, 39.2, 125.0, 38.6, 125.0);
    ctx.lineTo(38.6, 125.0);
    ctx.bezierCurveTo(38.1, 125.0, 37.6, 124.6, 37.6, 124.0);
    ctx.closePath();
    ctx.fillStyle(Colour::bytes(40, 44, 95));
    ctx.fill();
  }
} // namespace otto::engines
