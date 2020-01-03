#pragma once

#include "core/input.hpp"
#include "core/ui/nvg/Canvas.hpp"
#include "core/ui/screen.hpp"

/// Note: This is not an engine. This is only a placeholder for convenience!
namespace otto::engines::saveslots {

  using namespace core;

  struct Screen : ui::Screen {
    void draw(nvg::Canvas&);
    struct Input : input::InputHandler {
    } input;
  };

} // namespace otto::engines::saveslots
