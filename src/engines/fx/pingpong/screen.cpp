#include "screen.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::engines::pingpong {

  using namespace core::ui;
  using namespace core::ui::vg;

  Screen::Screen() noexcept {}

  void Screen::action(itc::prop_change<&Props::timetype>, bool t) noexcept 
  {
    timetype_ = t;
  }
  void Screen::action(itc::prop_change<&Props::subdivision>, SubdivisionEnum s) noexcept
  {
    subdivision_ = s;
  }
  void Screen::action(itc::prop_change<&Props::delaytime>, float dt) noexcept
  {
    delaytime_ = dt;
  }
  void Screen::action(itc::prop_change<&Props::filter>, float f) noexcept
  {
    filter_ = f;
  }
  void Screen::action(itc::prop_change<&Props::stereo>, float s) noexcept
  {
    stereo_ = s;
  }
  void Screen::action(itc::prop_change<&Props::stereo_invert>, bool i) noexcept
  {
    stereo_invert_ = i;
  }
  void Screen::action(itc::prop_change<&Props::feedback>, float f) noexcept
  {
    feedback_ = f;
  }

  void Screen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 45;
    constexpr float spacing = 10;

    // Time
    ctx.fillStyle(Colours::White);
    ctx.beginPath();
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Top);
    ctx.fillText("TIME", {x_pad, height - y_pad});

    if (timetype_)
    {
      // draw subdivision
    } else {
      ctx.beginPath();
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Bottom);
      ctx.fillStyle(Colours::Blue);
      ctx.fillText(fmt::format("{}ms", delaytime_ * 1000), {x_pad, height - y_pad - spacing});
    }

    // Filter
    ctx.beginPath();
    ctx.fillStyle(Colours::White);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Top);
    ctx.fillText("FILTER", {width - x_pad, height - y_pad});

    // Green line
    constexpr Point line_start = {x_pad, height / 3};
    ctx.beginPath();
    ctx.circle(line_start, 6.f);
    ctx.fill(Colours::Green);

    float length = (width - 2 * x_pad) * feedback_; 
    ctx.beginPath();
    ctx.moveTo(line_start);
    ctx.lineTo(line_start.x + length, line_start.y);
    ctx.stroke(Colours::Green);


  }

} // namespace otto::engines::pingpong
