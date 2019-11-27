#pragma once

#include "core/ui/vector_graphics.hpp"

namespace otto::core::ui {

  struct IconData {
    nvg::Box square();

    nvg::Size size = {16, 16};
    nvg::Color color = ui::vg::Colors::White;
    float line_width = 6.f;
  };

  struct Icon : nvg::Drawable {
    using IconDrawer = std::function<void(IconData&, nvg::Canvas&)>;
    Icon(IconDrawer drawer, nvg::Size s = {16, 16}, nvg::Color c = ui::vg::Colors::White, float lw = 6.f);

    void draw(nvg::Canvas& ctx) override;

    void set_size(nvg::Size size);
    void set_color(nvg::Color color);
    void set_line_width(float width);
    void set_icon(IconDrawer drawer);

  private:
    IconDrawer drawer_;
    IconData data_;
  };

  namespace icons {
    void plus(IconData& i, nvg::Canvas& ctx);
    void plus_clockwise_circle_arrow(IconData& i, nvg::Canvas& ctx);
  } // namespace icons


} // namespace otto::core::ui
