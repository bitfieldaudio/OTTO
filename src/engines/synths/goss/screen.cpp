#include "screen.hpp"

#include <cmath>

#include "core/ui/vector_graphics.hpp"
#include "util/math.hpp"
#include "util/string_conversions.hpp"

namespace otto::engines::goss {

  using namespace itc;

  using namespace ui;
  using namespace ui::vg;

  GossScreen::GossScreen(itc::Shared<float> rotation) noexcept : rotation(rotation) {}

  void GossScreen::action(prop_change<&Props::model>, int m) noexcept
  {
    model = m;
    // Update list of model parameters
    prev_model_param = model_param;
    model_param = model_params[model];
    model_interp = 0;
    ui::vg::timeline().apply(&model_interp).then<ch::RampTo>(1.f, 350, ch::EaseOutExpo());
  }
  void GossScreen::action(prop_change<&Props::click>, float c) noexcept
  {
    click = c;
  }
  void GossScreen::action(prop_change<&Props::drive>, float d) noexcept
  {
    drive = d;
  }
  void GossScreen::action(prop_change<&Props::leslie>, float l) noexcept
  {
    leslie = l;
  }

  void GossScreen::draw_model(nvg::Canvas& ctx, float interpolation_value)
  {
    constexpr float left_pad = 40.f;
    constexpr float step_size = 20.f;
    constexpr float y_pos = 35.f;
    // Lines
    constexpr float y_pad = 5.f;
    constexpr float min_length = 5.f;
    constexpr float length_step = 5.f;

    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Bottom);
    for (auto&& [i, p] : util::view::indexed(model_param)) {
      float x = left_pad + step_size * i;
      ctx.beginPath();
      ctx.fillText(util::to_string(p), {x, y_pos});
      // Line
      float prev_p = prev_model_param[i];
      float effective_p = p * interpolation_value + prev_p * (1 - interpolation_value);
      ctx.beginPath();
      ctx.lineWidth(6.f);
      ctx.moveTo({x, y_pos + y_pad});
      ctx.lineTo({x, y_pos + y_pad + min_length + effective_p * length_step});
      ctx.stroke(Colours::Blue);
    }
  }

  void GossScreen::draw_horn(nvg::Canvas& ctx, float phase)
  {
    constexpr Point real_center = {120, 150};
    constexpr float shift = 5.f;
    // On axis isometric length
    constexpr float side = 20;
    float side_long = side * std::sqrt(2.f);
    float side_short = side_long / 2.f;
    ctx.lineWidth(6.f);

    // Brightnesses
    float nw = util::math::trianglewrap(rotation, 0.25f, 0.3f, 1.f);
    float ne = util::math::trianglewrap(rotation, 0.5f, 0.3f, 1.f);
    float se = util::math::trianglewrap(rotation, 0.75f, 0.3f, 1.f);
    float sw = util::math::trianglewrap(rotation, 1.0f, 0.3f, 1.f);

    Point center = {real_center.x - shift, real_center.y - shift};
    
    // North-west
    ctx.beginPath();
    ctx.moveTo(center);
    ctx.lineTo({center.x - side_long, center.y});
    ctx.lineTo({center.x - side_long, center.y - side});
    ctx.lineTo({center.x - side_long + side_short, center.y - 1.5f * side});
    ctx.lineTo(center);
    ctx.lineTo({center.x - side_long, center.y - side});
    ctx.stroke(Colours::Red.dim(1 - nw));
    
    center = {real_center.x + shift, real_center.y - shift};
    
    // North-east
    ctx.beginPath();
    ctx.moveTo(center);
    ctx.lineTo({center.x + side_long, center.y});
    ctx.lineTo({center.x + side_long, center.y - side});
    ctx.lineTo({center.x + side_long - side_short, center.y - 1.5f * side});
    ctx.lineTo(center);
    ctx.lineTo({center.x + side_long, center.y - side});
    ctx.stroke(Colours::Red.dim(1 - ne));
    
    center = {real_center.x - shift, real_center.y + shift};
    
    // South-west
    ctx.beginPath();
    ctx.moveTo(center);
    ctx.lineTo({center.x - side_long, center.y});
    ctx.lineTo({center.x - side_long, center.y + side});
    ctx.lineTo({center.x - side_long + side_short, center.y + 1.5f * side});
    ctx.lineTo(center);
    ctx.lineTo({center.x - side_short, center.y + 0.5 * side});
    ctx.lineTo({center.x - side_long + side_short, center.y + 1.5f * side});
    ctx.moveTo({center.x - side_short, center.y + 0.5 * side});
    ctx.lineTo({center.x - side_long, center.y});
    ctx.stroke(Colours::Red.dim(1 - sw));
    
    center = {real_center.x + shift, real_center.y + shift};
    
    // South-east
    ctx.beginPath();
    ctx.moveTo(center);
    ctx.lineTo({center.x + side_long, center.y});
    ctx.lineTo({center.x + side_long, center.y + side});
    ctx.lineTo({center.x + side_long - side_short, center.y + 1.5f * side});
    ctx.lineTo(center);
    ctx.lineTo({center.x + side_short, center.y + 0.5 * side});
    ctx.lineTo({center.x + side_long - side_short, center.y + 1.5f * side});
    ctx.moveTo({center.x + side_short, center.y + 0.5 * side});
    ctx.lineTo({center.x + side_long, center.y});
    ctx.stroke(Colours::Red.dim(1 - se));
    
  }

  void GossScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    ctx.font(Fonts::Norm, 35);

    constexpr Point ring_center = {160, 120};
    /*
    // Gray Base Layers
    ctx.group([&] {
      // Ring 1 Base
      ctx.beginPath();
      ctx.circle(ring_center, 55);
      ctx.lineWidth(6.0);
      ctx.strokeStyle(Colours::Gray50);
      ctx.lineCap(LineCap::ROUND);
      ctx.lineJoin(LineJoin::ROUND);
      ctx.stroke();

      // Ring 2 Base
      ctx.beginPath();
      ctx.circle(ring_center, 75);
      ctx.stroke();

      // Ring 3 Base
      ctx.beginPath();
      ctx.circle(ring_center, 95);
      ctx.stroke();
    });

    // Coloured Parameters
    ctx.group([&] {
      // Ring 1
      ctx.beginPath();
      ctx.rotateAround(ring_center, 55);
      ctx.arc(ring_center.x, ring_center.y, 55, 0, (2 * M_PI * click), false);
      ctx.lineWidth(6.0);
      ctx.strokeStyle(Colours::Yellow);
      ctx.lineCap(LineCap::ROUND);
      ctx.lineJoin(LineJoin::ROUND);
      ctx.stroke();

      // Ring 2
      ctx.beginPath();
      ctx.arc(160, 120, 75, 0, (2 * M_PI * drive), false);
      ctx.strokeStyle(Colours::Green);
      ctx.stroke();
    });

    // middle red ring
    ctx.group([&] {
      constexpr Point ring_center = {160, 120};
      // Ring Base
      ctx.beginPath();
      ctx.lineWidth(6.0);
      ctx.strokeStyle(Colours::Red);

      ctx.rotateAround(ring_center, rotation);
      ctx.circle({ring_center.x, height / 2 + leslie * 25}, 12.5);
      ctx.stroke();

      ctx.circle({ring_center.x, height / 2 + leslie * 25}, 12.5);
      ctx.stroke();
    });

    */
    draw_model(ctx, model_interp);
    draw_horn(ctx, rotation);
  }
} // namespace otto::engines::goss
