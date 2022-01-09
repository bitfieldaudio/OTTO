#pragma once

#include <lunasvg.h>

#include "lib/util/enum.hpp"

#include "lib/graphics.hpp"
#include "lib/skia/point.hpp"
#include "lib/skia/skia.hpp"

#include "app/services/led_manager.hpp"

namespace otto::board {

  struct Emulator : IDrawable {
    enum struct ClickAction { down, up };

    Emulator(services::LedManager& led_manager);

    void draw(skia::Canvas& ctx) noexcept override
    {
      draw_bg(ctx);
      draw_leds(ctx);
      draw_frontpanel(ctx);
    };

    constexpr static skia::Vector size = {1617, 561};

  private:
    void draw_bg(skia::Canvas& ctx);
    void draw_leds(skia::Canvas& ctx);
    void draw_frontpanel(skia::Canvas& ctx);
    skia::Color get_led_color(Led);

    lunasvg::Bitmap svg_bitmap;
    skia::PixelRef pixref{0, 0, svg_bitmap.data(), 1};
    sk_sp<skia::PixelRef> pixrefptr;
    skia::Bitmap skia_bitmap;

    skia::ImageInfo image_info;
    sk_sp<skia::Image> image;
    services::LedManager& led_manager;
  };

} // namespace otto::board


// kak: other_file=../../src/emulator.cpp
