#include "screen.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::engines::sequencer {

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
    ctx.fillText("Sequencer", x_pad, y_pad);

    ctx.font(Fonts::Norm, 20);
    ctx.fillText("Coming Soon:", x_pad, 3 * y_pad);
    ctx.fillText("Sequence midi output", x_pad, 4 * y_pad);
    ctx.fillText("or internal audio samples!", x_pad, 5 * y_pad);
  }

} // namespace otto::engines::sequencer
