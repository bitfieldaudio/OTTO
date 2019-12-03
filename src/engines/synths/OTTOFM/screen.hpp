#pragma once

#include "core/ui/screen.hpp"
#include "ottofm.hpp"

#include "audio.hpp"

namespace otto::engines::ottofm {

  using namespace itc;

  struct OttofmScreen : ui::Screen {
    void draw(nvg::Canvas& ctx) override;


  };
} // namespace otto::engines::goss
