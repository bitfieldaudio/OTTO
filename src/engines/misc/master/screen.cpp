#include "screen.hpp"

#include "core/ui/nvg/Text.hpp"
#include "core/ui/vector_graphics.hpp"

namespace otto::engines::master {

  using namespace core::ui;
  using namespace core::ui::vg;

  void Screen::action(itc::prop_change<&Props::volume>, float v) noexcept
  {
    volume_ = v;
    rotation = -2.15 + volume_ * 4.3;
  }
  void Screen::action(itc::prop_change<&Props::tempo>, float t) noexcept
  {
    tempo_ = t;
  }


  void Screen::draw(ui::vg::Canvas& ctx)
  {
    using namespace nvg;
    using namespace ui::vg;

    constexpr Point volume_center = {75, 110};

    // Text
    ctx.beginPath();
    ctx.font(Fonts::Bold, 26);
    ctx.fillStyle(Colours::White);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Bottom);
    ctx.fillText("VOLUME", volume_center.x, 189.9);

    // Dot
    ctx.beginPath();
    ctx.circle(volume_center,4);
    ctx.fillStyle(Colours::Green);
    ctx.fill();
    ctx.lineWidth(6.0);
    ctx.strokeStyle(Colours::Green);
    ctx.lineCap(LineCap::ROUND);
    ctx.lineJoin(LineJoin::ROUND);
    ctx.stroke(Colours::Green);

    ctx.group([&]{
      ctx.rotateAround(volume_center, rotation);
      ctx.beginPath();
      ctx.moveTo(volume_center);
      ctx.lineTo(volume_center.x, volume_center.y - 37);
      ctx.lineWidth(6.f);
      ctx.stroke(Colours::Green);
    });

    constexpr float radius = 55.f;
    constexpr float angle = M_PI * 0.7; 
    // Outer circle
    ctx.beginPath();
    ctx.arc(volume_center, radius, -angle - M_PI_2, angle - M_PI_2);
    ctx.lineWidth(6.0);
    ctx.strokeStyle(Colours::Gray50);
    ctx.lineCap(LineCap::ROUND);
    ctx.lineJoin(LineJoin::ROUND);
    ctx.stroke();

    // Tempo
    ctx.fillStyle(Colours::White);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Bottom);
    ctx.fillText("TEMPO", width - 25, 189.9);
    ctx.fillStyle(Colours::Red);
    ctx.font(Fonts::Bold, 40);
    ctx.fillText(fmt::format("{:.1f}", tempo_), {width - 25, 150});

  }


} // namespace otto::engines::master
