#include "screen.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::engines::goss {

  using namespace itc;

  using namespace ui;
  using namespace ui::vg;

  void GossScreen::action(prop_change<&Props::drawbar1>, float d1) noexcept
  {
    drawbar1 = d1;
  }
  void GossScreen::action(prop_change<&Props::drawbar2>, float d2) noexcept
  {
    drawbar2 = d2;
  }
  void GossScreen::action(prop_change<&Props::click>, float c) noexcept
  {
    click = c;
  }
  void GossScreen::action(prop_change<&Props::leslie>, float l) noexcept
  {
    leslie = l;
  }
  void GossScreen::action(Actions::rotation_variable, std::atomic<float>& val) noexcept
  {
    rotation = &val;
  }

  void GossScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    ctx.font(Fonts::Norm, 35);

    // Gray Base Layers
    ctx.group([&] {
      // Ring 1 Base
      ctx.beginPath();
      ctx.circle({160, 120}, 55);
      ctx.lineWidth(6.0);
      ctx.strokeStyle(Colours::Gray50);
      ctx.lineCap(LineCap::ROUND);
      ctx.lineJoin(LineJoin::ROUND);
      ctx.stroke();

      // Ring 2 Base
      ctx.beginPath();
      ctx.circle({160, 120}, 75);
      ctx.stroke();

      // Ring 3 Base
      ctx.beginPath();
      ctx.circle({160, 120}, 95);
      ctx.stroke();
    });

    // Coloured Parameters
    ctx.group([&] {
      // Ring 1
      ctx.beginPath();
      ctx.rotateAround(55, {160, 120});
      ctx.arc(160, 120, 55, 0, (2 * M_PI * click), false);
      ctx.lineWidth(6.0);
      ctx.strokeStyle(Colours::Yellow);
      ctx.lineCap(LineCap::ROUND);
      ctx.lineJoin(LineJoin::ROUND);
      ctx.stroke();

      // Ring 2
      ctx.beginPath();
      ctx.arc(160, 120, 75, 0, (2 * M_PI * drawbar2), false);
      ctx.strokeStyle(Colours::Green);
      ctx.stroke();

      // Ring 3
      ctx.beginPath();
      ctx.arc(160, 120, 95, 0, (2 * M_PI * drawbar1), false);
      ctx.strokeStyle(Colours::Blue);
      ctx.stroke();
    });

    // middle red ring
    ctx.group([&] {
      // Ring Base
      ctx.beginPath();
      ctx.lineWidth(6.0);
      ctx.strokeStyle(Colours::Red);

      OTTO_ASSERT(rotation != nullptr);
      ctx.rotateAround(*rotation, {160, 120});
      ctx.circle({160, height / 2 + leslie * 25}, 12.5);
      ctx.stroke();

      ctx.circle({160, height / 2 + leslie * 25}, 12.5);
      ctx.stroke();
    });
    ///
  }
} // namespace otto::engines::goss
