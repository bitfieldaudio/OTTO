#include "screen.hpp"

#include "core/ui/vector_graphics.hpp"
#include "util/string_conversions.hpp"

namespace otto::engines::goss {

  using namespace itc;

  using namespace ui;
  using namespace ui::vg;

  GossScreen::GossScreen(itc::Shared<float> rotation) noexcept : rotation(rotation) {}

  void GossScreen::action(prop_change<&Props::model>, int m) noexcept
  {
    model = m;
    // Get list of model parameters
    model_param = model_params[model];
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

  void GossScreen::draw_model(nvg::Canvas& ctx)
  {
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Bottom);
    for (auto&& [i, p] : util::view::indexed(model_param)) {
      ctx.beginPath();
      ctx.fillText(util::to_string(p), {float(40 + 20 * i), 50.f});
    }
  }

  void GossScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    ctx.font(Fonts::Norm, 35);

    constexpr Point ring_center = {160, 120};

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


      // Ring 3
      /* Deprecated
      ctx.beginPath();
      ctx.arc(ring_center.x, ring_center.y, 95, 0, (2 * M_PI * (model / 2.f)), false);
      ctx.strokeStyle(Colours::Blue);
      ctx.stroke();
      */
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

    draw_model(ctx);
  }
} // namespace otto::engines::goss
