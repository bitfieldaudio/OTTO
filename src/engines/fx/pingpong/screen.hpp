#pragma once

#include "core/ui/vector_graphics.hpp"
#include "pingpong.hpp"

namespace otto::engines::pingpong {

  using namespace core;

  struct Screen : ui::Screen {
    Screen() noexcept;
    void draw(nvg::Canvas& ctx) override;


  private:
  };

} // namespace otto::engines::pingpong
