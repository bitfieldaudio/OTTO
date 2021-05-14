#pragma once

#include "lib/skia/anim.hpp"
#include "lib/skia/skia.hpp"
#include "lib/widget.hpp"

#include "app/engines/synths/nuke/state.hpp"

#include "nuke.hpp"

namespace otto::engines::nuke {

  struct FourParams : graphics::Widget<FourParams> {
    std::string title;

    float a = 0;
    float b = 0;
    float c = 0;
    float d = 0;

    FourParams(std::string t) : title(t){};

    void set(const std::array<float, 4>& t);

    void do_draw(skia::Canvas& ctx);
  };


} // namespace otto::engines::nuke
