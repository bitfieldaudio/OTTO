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
    ctx.drawCircle({765, 190}, 30, otto::paints::fill(colors::blue));
  }

  void Emulator::draw_frontpanel(skia::Canvas& ctx)
  {
    // ctx.drawImage(skia::Image::MakeFromBitmap(skia_bitmap), 0, 0);
    ctx.drawImage(skia::Image::MakeRasterCopy(pixmap), 0, 0);
  }

} // namespace otto::board

// kak: other_file=../include/board/emulator.hpp
