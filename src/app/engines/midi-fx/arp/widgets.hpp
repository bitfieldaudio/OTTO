#pragma once

#include "lib/skia/anim.hpp"
#include "lib/skia/skia.hpp"
#include "lib/widget.hpp"

#include "arp.hpp"

namespace otto::engines::arp {

  struct NoteLength : graphics::Widget<NoteLength> {
    float length_ = 0;
    float fade_ = 0;
    void do_draw(skia::Canvas& ctx);
  };

  struct Subdivision : graphics::Widget<Subdivision> {
    int num_dots_ = 1;
    float fade_ = 0;
    void do_draw(skia::Canvas& ctx);
  };
} // namespace otto::engines::arp