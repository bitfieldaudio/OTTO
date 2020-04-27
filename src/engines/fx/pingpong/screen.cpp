#include "screen.hpp"

#include <cmath>

#include "core/ui/nvg/Text.hpp"
#include "core/ui/vector_graphics.hpp"

namespace otto::engines::pingpong {

  std::string to_string(SubdivisionEnum sd)
  {
    switch (sd) {
        case SubdivisionEnum::sixteenths: return "16THS";
        case SubdivisionEnum::eighthtriplets: return "D.16THS";
        case SubdivisionEnum::eights: return "8THS";
        case SubdivisionEnum::quartertriplets: return "D.8THS";
        case SubdivisionEnum::quarter: return "QUARTER";
        case SubdivisionEnum::half: return "HALF";
        case SubdivisionEnum::whole: return "WHOLE";
        default: OTTO_UNREACHABLE;
      }
  }

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

    if (timetype_) {
      // draw subdivision
      // TODO: draw actual note icons
      ctx.font(Fonts::Bold, 25);
      ctx.beginPath();
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Bottom);
      ctx.fillStyle(Colours::Blue);
      ctx.fillText(to_string(subdivision_), {x_pad, height - y_pad - spacing});
    } else {
      ctx.beginPath();
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Bottom);
      ctx.fillStyle(Colours::Blue);
      ctx.fillText(fmt::format("{0:d}ms", (int) (delaytime_ * 1000.f)), {x_pad, height - y_pad - spacing});
    }

    // Filter
    ctx.beginPath();
    ctx.font(Fonts::Norm, 35);
    ctx.fillStyle(Colours::White);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Top);
    ctx.fillText("FILTER", {width - x_pad, height - y_pad});
    constexpr nvg::Size filter_size = {100, 30};
    draw_filter(ctx, filter_, {width - x_pad - filter_size.w, height - y_pad - spacing - filter_size.h}, filter_size);

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

    // Red Arcs
    float pingpong_amount = std::clamp(stereo_ * 2 - 1, 0.f, 1.f);
    float spread_amount = std::clamp(-stereo_ * 2 + 1, 0.f, 1.f);
    constexpr float arc_pad = -10.f;
    constexpr float arc_step = 40.f;
    // Math detour: Since the the length of a chord in a circle is proportional to radius, distance and radius should
    // scale by the same factor between steps
    constexpr float step_scale = 1.2;
    float cur_step_size = 1;
    for (int i = 0; i < 5; i++) {
      cur_step_size = powf(step_scale, (float) i);
      ctx.group([&]{
        float rotation = i % 2 == 1 ? M_PI_4 * pingpong_amount : -M_PI_4 * pingpong_amount; 
        ctx.rotateAround(line_start, 0.15 * rotation);
        draw_arc(ctx, {line_start.x + arc_pad + (cur_step_size + i) * arc_step, line_start.y},
               10 + 8 * (cur_step_size + i), spread_amount);
    
      });
    }
    if (stereo_invert_) {
      ctx.beginPath();
      ctx.fillStyle(Colours::Red);
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Top);
      ctx.fillText("X", {x_pad, x_pad / 2.f});
    }

  }

  void Screen::draw_filter(nvg::Canvas& ctx, float val, nvg::Point pos, nvg::Size size)
  {
    // Drawn as 3 beziers
    // lo_x and hi_x are also control points for beginning- and endpoints.
    constexpr float min_pad = 0.07;
    constexpr float max_pad = 0.2;
    float lo_val = std::clamp(2 * val - 1, 0.f, 1.f);
    float hi_val = std::clamp(2 * val, 0.f, 1.f);
    float adj_lo_val = lo_val * (1 - max_pad - min_pad) + min_pad;
    float adj_hi_val = hi_val * (1 - max_pad - min_pad) + max_pad;
    float lo_x = pos.x + size.w * adj_lo_val;
    float hi_x = pos.x + size.w * adj_hi_val;

    ctx.beginPath();
    ctx.moveTo(pos.x, pos.y + size.h);
    ctx.bezierCurveTo({lo_x, pos.y + size.h}, {lo_x - min_pad * size.w, pos.y}, {lo_x, pos.y});
    ctx.bezierCurveTo({lo_x, pos.y}, {hi_x, pos.y}, {hi_x, pos.y});
    ctx.bezierCurveTo({hi_x + min_pad * size.w, pos.y}, {hi_x, pos.y + size.h}, {pos.x + size.w, pos.y + size.h});
    ctx.stroke(Colours::Yellow);
  }


  void Screen::draw_arc(nvg::Canvas& ctx, nvg::Point position, float size, float spread)
  {
    constexpr float angle = M_PI_4 * 1.4;
    constexpr float spread_px = 10;
    // First half, not gonna lie
    nvg::Point center = {position.x - size + spread_px * spread, position.y};
    ctx.lineWidth(12.f);
    ctx.beginPath();
    ctx.arc(center, size, -angle, 0);
    ctx.stroke(Colours::Black);

    // Second half
    center = {position.x - size - spread_px * spread, position.y};
    ctx.lineWidth(12.f);
    ctx.beginPath();
    ctx.arc(center, size, 0, angle);
    ctx.stroke(Colours::Black);

    ctx.lineWidth(6.f);
    ctx.beginPath();
    ctx.arc(center, size, 0, angle);
    ctx.stroke(Colours::Red);

    // First half again
    center = {position.x - size + spread_px * spread, position.y};
    ctx.lineWidth(6.f);
    ctx.beginPath();
    ctx.arc(center, size, -angle, 0);
    ctx.stroke(Colours::Red);
  }

} // namespace otto::engines::pingpong
