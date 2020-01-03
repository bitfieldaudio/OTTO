#include "screen.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::engines::saveslots {

  using namespace core::ui;
  using namespace core::ui::vg;

  void Screen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 20;
    constexpr float y_pad = 20;


    // Text
    ctx.font(Fonts::Norm, 35);
    ctx.fillStyle(Colours::White);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Top);
    ctx.fillText("Saveslots", x_pad, y_pad);

    ctx.font(Fonts::Norm, 20);
    ctx.fillText("Coming soon:", x_pad, 3 * y_pad);
    ctx.fillText("Used to save the state of OTTO", x_pad, 4 * y_pad);
    ctx.fillText("at a sound or project level.", x_pad, 5 * y_pad);
  }

} // namespace otto::engines::saveslots
