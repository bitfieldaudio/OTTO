#pragma once

#include "wormhole.hpp"

namespace otto::engines::wormhole {

  using namespace core;

  struct Screen : ui::Screen {
    void draw(nvg::Canvas& ctx) override;

    float filter_ = 0.f;
    void action(itc::prop_change<&Props::filter>, float f) noexcept;
    float shimmer_ = 0.f;
    void action(itc::prop_change<&Props::shimmer>, float s) noexcept;
    float length_ = 0.f;
    void action(itc::prop_change<&Props::length>, float l) noexcept;
    float damping_ = 0.f;
    void action(itc::prop_change<&Props::damping>, float d) noexcept;
  };

} // namespace otto::engines::wormhole
