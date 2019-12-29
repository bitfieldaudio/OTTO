#pragma once

#include "master.hpp"

namespace otto::engines::master {

  using namespace core;

  struct Screen : ui::Screen {
    void draw(nvg::Canvas& ctx) override;
    void action(itc::prop_change<&Props::volume>, float v) noexcept;
    void action(itc::prop_change<&Props::tempo>, float t) noexcept;

    float volume_ = 0.f;
    float rotation = 0.f;
    float tempo_ = 120;
  };

} // namespace otto::engines::master
