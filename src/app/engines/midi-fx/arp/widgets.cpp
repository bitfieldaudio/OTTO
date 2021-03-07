#include "widgets.hpp"

namespace otto::engines::arp {

  void NoteLength::do_draw(skia::Canvas& ctx)
  {
    // Box rounding
    float r = 5.f;
    // Status bar
    SkRect rect = SkRect::MakeXYWH(0, 0, bounding_box.width(), bounding_box.height());
    SkRRect rrect = SkRRect::MakeRectXY(rect, r, r);
    ctx.drawRRect(rrect, paints::fill(colors::red.mix(colors::black, fade_)));
    // Covering square
    SkRect black_rect =
      SkRect::MakeLTRB(bounding_box.width() * length_, 0, bounding_box.width(), bounding_box.height());
    ctx.drawRect(black_rect, paints::fill(colors::black));
    // Outline
    ctx.drawRRect(rrect, paints::stroke(colors::red.mix(colors::black, fade_), 3.f));
  }

  void Subdivision::do_draw(skia::Canvas& ctx)
  {
    float step_size = bounding_box.width() / 6;
    float height = bounding_box.height() / 2.f;
    for (int i = 0; i < num_dots_; i++) {
      ctx.drawCircle({i * step_size, height}, 5.f, paints::fill(colors::yellow.fade(fade_)));
    }
  }

} // namespace otto::engines::arp