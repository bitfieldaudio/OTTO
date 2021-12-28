#include "board/emulator.hpp"

#include <SkImageInfo.h>

namespace otto::board {

  Emulator::Emulator()
  {
    auto document = lunasvg::Document::loadFromFile("data/emulator_front.svg");
    svg_bitmap = document->renderToBitmap(size.x(), size.y(), 0x00000000);

    image_info = skia::ImageInfo::Make(size.x(), size.y(), kRGBA_8888_SkColorType, kUnpremul_SkAlphaType);

    pixmap = skia::Pixmap(image_info, svg_bitmap.data(), size.x() * 4);

    // pixrefptr = sk_sp<skia::PixelRef>(&pixref_test);
    // skia_bitmap.setPixelRef(pixrefptr, 0, 0);
  }

  void Emulator::draw_bg(skia::Canvas& ctx)
  {
    ctx.drawRect(skia::Rect::MakeXYWH(0, 0, size.x(), size.y()), otto::paints::fill(colors::black));
  }

  void Emulator::draw_leds(skia::Canvas& ctx)
  {
    // Func Group 1
    skia::Point origin = {1116, 65};
    float side_length = 66;
    for (auto x = 0; x < 5; x++) {
      for (auto y = 0; y < 4; y++) {
        ctx.drawCircle({origin.x() + x * side_length, origin.y() + y * side_length}, 20,
                       otto::paints::fill(colors::blue));
      }
    }
    // Func Group 2
    origin = {1480, 65};
    for (auto x = 0; x < 2; x++) {
      for (auto y = 0; y < 4; y++) {
        ctx.drawCircle({origin.x() + x * side_length, origin.y() + y * side_length}, 20,
                       otto::paints::fill(colors::blue));
      }
    }
    // Channel
    origin = {190, 344};
    side_length = 99;
    std::array<int, 10> the_black_keys = {0, 1, 3, 4, 5, 7, 8, 10, 11, 12};
    for (auto x : the_black_keys) {
      ctx.drawRect(skia::Rect::MakeXYWH(origin.x() + x * side_length, origin.y(), 50, 15),
                   otto::paints::fill(colors::blue));
    }
    // Seq
    origin = {43, 428};
    for (auto x = 0; x < 16; x++) {
      ctx.drawRect(skia::Rect::MakeXYWH(origin.x() + x * side_length, origin.y(), 50, 15),
                   otto::paints::fill(colors::blue));
    }
  }

  void Emulator::draw_frontpanel(skia::Canvas& ctx)
  {
    // ctx.drawImage(skia::Image::MakeFromBitmap(skia_bitmap), 0, 0);
    ctx.drawImage(skia::Image::MakeRasterCopy(pixmap), 0, 0);
  }

} // namespace otto::board

// kak: other_file=../include/board/emulator.hpp
