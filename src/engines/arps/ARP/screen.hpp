#pragma once

#include "arp.hpp"
#include "audio.hpp"

#include "core/ui/screen.hpp"

namespace otto::engines::arp {

  using namespace core;

  struct Screen : ui::Screen {
    void draw(nvg::Canvas& ctx) override;

  };

} // namespace otto::engines::arp
