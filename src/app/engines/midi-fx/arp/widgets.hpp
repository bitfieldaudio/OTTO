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

  struct VisualDots : graphics::Widget<VisualDots> {
    using Dots = util::local_vector<NoteVector, 24>;
    using DotCoords = util::local_vector<std::pair<skia::Point, bool>, 48>;
    PlayModeFunc playmode_func_ = play_modes::up;
    OctaveModeFunc octavemode_func_ = octave_modes::standard;
    ArpeggiatorState dummy_state;
    NoteArray notes;
    Dots dots;
    DotCoords dots_coords;

    void update_dots() noexcept;

    void do_draw(skia::Canvas& ctx);
  };

} // namespace otto::engines::arp