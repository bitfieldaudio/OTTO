#pragma once

#include <functional>
#include <tuple>

#include "core/ui/vector_graphics.hpp"
#include "core/input.hpp"

namespace otto::test {

  void show_gui(core::ui::vg::Size size, std::function<void(core::ui::vg::Canvas& ctx)> draw, core::input::InputHandler*);

  inline void show_gui(std::function<void(core::ui::vg::Canvas& ctx)> draw, core::input::InputHandler* input = nullptr)
  {
    show_gui({core::ui::vg::width, core::ui::vg::height}, std::move(draw), input);
  }

  inline void show_gui(nvg::Drawable& drawable, core::input::InputHandler* input = nullptr)
  {
    show_gui({core::ui::vg::width, core::ui::vg::height}, [&drawable] (auto& ctx) { drawable.draw(ctx); }, input);
  }

} // namespace otto::test
