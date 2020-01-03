#pragma once

#include "core/input.hpp"
#include "core/ui/nvg/Canvas.hpp"
#include "core/ui/screen.hpp"

namespace otto::engines::sequencer {

  using namespace core;

  struct Screen : ui::Screen {
    void draw(nvg::Canvas&);
    struct Input : input::InputHandler {
    } input;
  };

} // namespace otto::engines::sequencer
