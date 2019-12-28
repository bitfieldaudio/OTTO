#include "screen.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::engines::master {

  using namespace core::ui;
  using namespace core::ui::vg;

  void Screen::action(itc::prop_change<&Props::volume>, float v) noexcept
  {
    volume_ = v;
    rotation = -2.15 + volume_ * 4.3;
  }
  void Screen::action(itc::prop_change<&Props::tempo>, int t) noexcept
  {
    tempo_ = t;
  }


  void Screen::draw(ui::vg::Canvas& ctx)
  {
    using namespace nvg;
    using namespace ui::vg;

    // Text
    ctx.font(Fonts::Bold, 26);
    ctx.fillStyle(Color::bytes(255, 255, 255));
    ctx.fillText("master volume", 86.6, 189.9);

    // Dot
    ctx.save();
    ctx.beginPath();
    ctx.circle({160,110},4);
    ctx.fillStyle(Colours::Green);
    ctx.fill();
    ctx.lineWidth(6.0);
    ctx.strokeStyle(Color::bytes(147, 192, 34));
    ctx.lineCap(LineCap::ROUND);
    ctx.lineJoin(LineJoin::ROUND);
    ctx.stroke();

    ctx.save();
    ctx.rotateAround({160,110}, rotation);
    ctx.beginPath();
    ctx.moveTo(160.0, 110.8);
    ctx.lineTo(160.0, 73.4);
    ctx.stroke();
    ctx.restore();

    // Outer circle
    ctx.restore();
    ctx.beginPath();
    ctx.moveTo(109.4, 144.9);
    ctx.bezierCurveTo(102.8, 135.1, 99.0, 123.4, 99.0, 110.8);
    ctx.bezierCurveTo(99.0, 77.1, 126.3, 49.8, 160.0, 49.8);
    ctx.bezierCurveTo(193.7, 49.8, 221.0, 77.1, 221.0, 110.8);
    ctx.bezierCurveTo(221.0, 122.6, 217.6, 133.7, 211.8, 143.0);
    ctx.lineWidth(6.0);
    ctx.strokeStyle(Color::bytes(99, 99, 99));
    ctx.lineCap(LineCap::ROUND);
    ctx.lineJoin(LineJoin::ROUND);
    ctx.stroke();
    ctx.restore();

  }


} // namespace otto::engines::wormhole
