#pragma once

#include <lunasvg.h>

#include "lib/util/enum.hpp"

#include "lib/graphics.hpp"
#include "lib/skia/point.hpp"
#include "lib/skia/skia.hpp"

namespace otto::board {

  struct Emulator : IDrawable {
    enum struct ClickAction { down, up };

    Emulator();

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

    lunasvg::Bitmap svg_bitmap;
    skia::PixelRef pixref{0, 0, svg_bitmap.data(), 1};
    sk_sp<skia::PixelRef> pixrefptr;
    skia::Bitmap skia_bitmap;

    skia::ImageInfo image_info;
    skia::Pixmap pixmap;
  };

} // namespace otto::board


// kak: other_file=../../src/emulator.cpp
