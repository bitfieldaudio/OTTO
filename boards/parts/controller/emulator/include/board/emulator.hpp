#pragma once

#include <lunasvg.h>

#include "lib/util/enum.hpp"

#include "lib/graphics.hpp"
#include "lib/skia/point.hpp"
#include "lib/skia/skia.hpp"

#include "app/services/led_manager.hpp"

#include "board/ui/glfw_ui.hpp"

namespace otto::board {

  struct Emulator : drivers::IGraphicsDriver {
    enum struct ClickAction { down, up };

    Emulator();

    void draw(skia::Canvas& ctx) noexcept
    {
      draw_bg(ctx);
      draw_leds(ctx);
      draw_frontpanel(ctx);
    };

    void run(std::function<bool(skia::Canvas&)>) override;

    constexpr static skia::Vector size = {1617, 561};

  private:
    void draw_bg(skia::Canvas& ctx);
    void draw_leds(skia::Canvas& ctx);
    void draw_frontpanel(skia::Canvas& ctx);
    skia::Color get_led_color(Led);

    void handle_click(glfw::Button, glfw::Action, glfw::Modifiers);
    void handle_scroll(double x, double y);

    lunasvg::Bitmap svg_bitmap;
    skia::PixelRef pixref{0, 0, svg_bitmap.data(), 1};
    sk_sp<skia::PixelRef> pixrefptr;
    skia::Bitmap skia_bitmap;

    skia::ImageInfo image_info;
    sk_sp<skia::Image> image;

    drivers::GlfwGraphicsDriver glfw_;
  };

} // namespace otto::board


// kak: other_file=../../src/emulator.cpp
