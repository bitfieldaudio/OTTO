#include "screen.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::engines::external {

  using namespace core::ui;
  using namespace core::ui::vg;

  void Screen::action(itc::prop_change<&Props::gain>, float g) noexcept
  {
    gain_ = g;
  }
  void Screen::action(itc::prop_change<&Props::enabled>, bool e) noexcept
  {
    enabled_ = e;
  }
  void Screen::action(itc::prop_change<&Props::stereo_routing>, int r) noexcept
  {
    routing_ = r;
  }
  void Screen::action(itc::prop_change<&Props::stereo_balance>, float b) noexcept
  {
    balance_ = b;
  }

  void Screen::draw(nvg::Canvas& ctx)
  {
    using namespace core::ui::vg;
    ctx.font(Fonts::Norm, 35);
  }

} // namespace otto::engines::external