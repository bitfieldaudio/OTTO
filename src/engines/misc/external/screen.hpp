#pragma once

#include "core/ui/vector_graphics.hpp"
#include "external_in.hpp"

namespace otto::engines::external {

  using namespace core;
  using namespace core::input;

  struct Screen : ui::Screen {
    void draw(nvg::Canvas& ctx) override;

    void action(itc::prop_change<&Props::gain>, float g) noexcept;
    void action(itc::prop_change<&Props::enabled>, bool e) noexcept;
    void action(itc::prop_change<&Props::stereo_routing>, int s) noexcept;
    void action(itc::prop_change<&Props::stereo_balance>, float s) noexcept;

  private:
    float gain_ = 0.5;
    bool enabled_ = true;
    int routing_ = 0;
    float balance_ = 0.5;
  };
} // namespace otto::engines::external