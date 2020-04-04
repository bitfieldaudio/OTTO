#include "screen.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::engines::pingpong {

  using namespace core::ui;
  using namespace core::ui::vg;

  Screen::Screen() noexcept {}

  void Screen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    ctx.font(Fonts::Norm, 35);
  }

} // namespace otto::engines::pingpong
