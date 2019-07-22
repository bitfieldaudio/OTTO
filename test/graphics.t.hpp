#pragma once

#include <functional>
#include <tuple>

#include "core/ui/vector_graphics.hpp"

namespace otto::test {

  void show_gui(core::ui::vg::Size size, std::function<void(core::ui::vg::Canvas& ctx)> draw);

  inline void show_gui(std::function<void(core::ui::vg::Canvas& ctx)> draw)
  {
    show_gui({core::ui::vg::width, core::ui::vg::height}, std::move(draw));
  }

} // namespace otto::test
