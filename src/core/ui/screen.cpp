#include "screen.hpp"

#include "core/ui/vector_graphics.hpp"

#include "core/ui/animation.hpp"

namespace otto::core::ui {

  inline auto Position::Relative::absolute(vg::Size size) const noexcept -> Absolute
  {
    switch (alignment) {
    case Alignment::top_left: return {0 + padding.horizontal, 0 + padding.vertical};
    case Alignment::top_center: return {(vg::width - size.w) / 2.f, 0 + padding.vertical};
    case Alignment::top_right:
      return {vg::width - size.w - padding.horizontal, 0 + padding.vertical};

    case Alignment::center_left: return {0 + padding.horizontal, (vg::height - size.h) / 2.f};
    case Alignment::center: return {(vg::width - size.w) / 2.f, (vg::height - size.h) / 2.f};
    case Alignment::center_right:
      return {(vg::width - size.w) - padding.horizontal, (vg::height - size.h) / 2.f};

    case Alignment::bottom_left:
      return {0 + padding.horizontal, vg::height - size.h - padding.vertical};
    case Alignment::bottom_center:
      return {(vg::width - size.w) / 2.f, vg::height - size.h - padding.vertical};
    case Alignment::bottom_right:
      return {(vg::width - size.w) - padding.horizontal, vg::height - size.h - padding.vertical};
    }
  }

} // namespace otto::core::ui
