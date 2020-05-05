#include "screen.hpp"

#include <cmath>

#include "core/ui/nvg/Text.hpp"
#include "core/ui/vector_graphics.hpp"
#include "engines/fx/pingpong/pingpong.hpp"

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

    constexpr float x_pad = 30;
    constexpr float y_pad = 45;

    if (timetype_) {
      draw_subdivision(ctx, {x_pad + 10, height - 2 * y_pad}, 80, subdivision_);
    } else {
      // Time label
      /*
    ctx.fillStyle(Colours::White);
    ctx.beginPath();
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Top);
    ctx.fillText("TIME", {x_pad, height - y_pad});
    */
      ctx.beginPath();
      ctx.font(Fonts::Norm, 55);
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Bottom);
      ctx.fillStyle(Colours::Blue);
      ctx.fillText(fmt::format("{0:04d}", (int) (delaytime_ * 1000.f)), {x_pad - 4, height - 11});
    }

    // Filter
    /*
    ctx.beginPath();
    ctx.font(Fonts::Norm, 35);
    ctx.fillStyle(Colours::White);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Top);
    ctx.fillText("FILTER", {width - x_pad, height - y_pad});
    */
    constexpr nvg::Size filter_size = {125, 42};
    draw_filter(ctx, filter_, {width - x_pad - filter_size.w, height - 22 - filter_size.h}, filter_size);

    // Green line
    constexpr Point line_start = {x_pad, height / 3 + 3};
    ctx.beginPath();
    ctx.circle(line_start, 6.f);
    ctx.fill(Colours::Green);

    float length = (width - 2 * x_pad) * feedback_;
    ctx.beginPath();
    ctx.moveTo(line_start);
    ctx.lineTo(line_start.x + length, line_start.y);
    ctx.stroke(Colours::Green);

    // infinity symbol
    ctx.group([&](){
      ctx.save();
      ctx.font(Fonts::Norm, 45);
      ctx.fillStyle(Colours::Gray50.mix(Colours::Green, 10.f * std::clamp(feedback_ - 0.8f, 0.f, 0.1f)));
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Top);
      ctx.fillText("\u221E", {x_pad - 8, 15});
      ctx.restore();
    });

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
      ctx.group([&] {
        float rotation = pingpong_amount * (i % 2 == 0 ? 1 : -1);
        // ctx.rotateAround(line_start, 0.15 * rotation * M_PI_4);
        draw_arc(ctx, {line_start.x + arc_pad + (cur_step_size + i) * arc_step, line_start.y},
                 10 + 8 * (cur_step_size + i), spread_amount, rotation, stereo_invert_);
      });
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


  void Screen::draw_arc(nvg::Canvas& ctx, nvg::Point position, float size, float spread, float rotation, bool invert)
  {
    constexpr float angle = M_PI_4 * 1.4;
    float spread_px = 10;
    rotation *= angle;
    // rotation = 0;

    if (invert) {
      spread_px = -spread_px;
      rotation = -rotation;
    }

    float top_angle = rotation > 0 ? -angle + rotation : -angle;
    float bot_angle = rotation > 0 ? angle : angle + rotation;

    
    // First half, not gonna lie
    nvg::Point center = {position.x - size + spread_px * spread, position.y};
    ctx.lineWidth(12.f);
    ctx.beginPath();
    ctx.arc(center, size, top_angle, 0);
    ctx.stroke(Colours::Black);

    // Second half
    center = {position.x - size - spread_px * spread, position.y};
    ctx.lineWidth(12.f);
    ctx.beginPath();
    ctx.arc(center, size, 0, bot_angle);
    ctx.stroke(Colours::Black);

    ctx.lineWidth(6.f);
    ctx.beginPath();
    ctx.arc(center, size, 0, bot_angle);
    ctx.stroke(Colours::Red);

    // First half again
    center = {position.x - size + spread_px * spread, position.y};
    ctx.lineWidth(6.f);
    ctx.beginPath();
    ctx.arc(center, size, top_angle, 0);
    ctx.stroke(Colours::Red);
  }

  void Screen::draw_subdivision(nvg::Canvas& ctx, nvg::Point position, float size, SubdivisionEnum sd)
  {
    ctx.save();
    nvg::Point center = {position.x + size / 2.f, position.y + size / 2.f};
    nvg::Point foot = {center.x - size * 0.07f, center.y + size * 0.25f};
    float foot_size = size * 0.1;
    float line_length = size * 0.5;

    ctx.strokeStyle(Colours::Blue);
    ctx.fillStyle(Colours::Blue);
    if (sd == +SubdivisionEnum::whole) {
      float x_len = size * 0.3f;
      float y_len = size * 0.18f;
      constexpr float y_shift = 4.f;
      ctx.beginPath();
      ctx.circle({center.x, center.y + y_shift}, y_len * 0.7);
      ctx.stroke();
      /*
      ctx.beginPath();
      ctx.moveTo(center.x - x_len, center.y - y_len + y_shift);
      ctx.lineTo(center.x + x_len, center.y - y_len + y_shift);
      ctx.stroke();
      */
      ctx.beginPath();
      ctx.moveTo(center.x - x_len, center.y + y_len + y_shift);
      ctx.lineTo(center.x + x_len, center.y + y_len + y_shift);
      ctx.stroke();
    } else {
      // Normal note
      // Draw outline
      ctx.beginPath();
      ctx.circle(foot, foot_size);
      ctx.stroke();

      if (sd == +SubdivisionEnum::half || sd == +SubdivisionEnum::halftriplet || sd == +SubdivisionEnum::dothalf)
        ctx.fill();

      ctx.beginPath();
      ctx.moveTo(foot.x + foot_size, foot.y);
      ctx.lineTo(foot.x + foot_size, foot.y - line_length);
      ctx.stroke();

      // TRIPLETNUMBER
      if (sd == +SubdivisionEnum::halftriplet || sd == +SubdivisionEnum::quartertriplet ||
          sd == +SubdivisionEnum::eighthtriplet) {
        ctx.save();
        ctx.transform(1.000000, 0.000000, 0.000000, 1.000000, -168.131000, -140.436000);
        ctx.transform(1.0, 0.0, 0.0, 1.0, position.x + size * 0.2, position.y + size * 0.3);

        // #path787
        ctx.lineWidth(4.f);
        ctx.beginPath();
        ctx.moveTo(169.131060, 145.936280);
        ctx.moveTo(170.646930, 154.273550);
        ctx.bezierCurveTo(170.646930, 157.066160, 172.898630, 159.305280, 175.678660, 159.305280);
        ctx.bezierCurveTo(178.456180, 159.305280, 180.710400, 157.041000, 180.710400, 154.273550);
        ctx.bezierCurveTo(180.710400, 151.480940, 178.458690, 149.241810, 175.678660, 149.241810);
        ctx.lineTo(180.710400, 142.952150);
        ctx.lineTo(170.646930, 142.952150);
        ctx.stroke();
        ctx.restore();
        ctx.lineWidth(6.f);
      }

      // DOT
      if (sd == +SubdivisionEnum::doteighth || sd == +SubdivisionEnum::dothalf || sd == +SubdivisionEnum::dotquarter) {
        ctx.beginPath();
        ctx.circle({center.x + 2 * foot_size, foot.y}, size * 0.03);
        ctx.stroke();
      }

      // FLAGS
      float flag_len = size * 0.1;
      float flag_spacing = size * 0.12;
      float raise = flag_len * 0.5;
      if (sd == +SubdivisionEnum::eighth || sd == +SubdivisionEnum::doteighth ||
          sd == +SubdivisionEnum::eighthtriplet) {
        ctx.beginPath();
        ctx.moveTo(foot.x + foot_size, foot.y - line_length);
        ctx.lineTo(center.x + 2 * foot_size, foot.y - line_length - raise);
        ctx.stroke();
      }
      if (sd == +SubdivisionEnum::sixteenth) {
        ctx.beginPath();
        ctx.moveTo(foot.x + foot_size, foot.y - line_length);
        ctx.lineTo(center.x + 2 * foot_size, foot.y - line_length - raise);
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(foot.x + foot_size, foot.y - line_length + flag_spacing);
        ctx.lineTo(center.x + 2 * foot_size, foot.y - line_length - raise + flag_spacing);
        ctx.stroke();
      }
      if (sd == +SubdivisionEnum::thirtysecondth) {
        ctx.beginPath();
        ctx.moveTo(foot.x + foot_size, foot.y - line_length);
        ctx.lineTo(center.x + 2 * foot_size, foot.y - line_length - raise);
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(foot.x + foot_size, foot.y - line_length + flag_spacing);
        ctx.lineTo(center.x + 2 * foot_size, foot.y - line_length - raise + flag_spacing);
        ctx.stroke();

        ctx.beginPath();
        ctx.moveTo(foot.x + foot_size, foot.y - line_length + 2 * flag_spacing);
        ctx.lineTo(center.x + 2 * foot_size, foot.y - line_length - raise + 2 * flag_spacing);
        ctx.stroke();
      }
    }
    ctx.restore();
  }

} // namespace otto::engines::pingpong
