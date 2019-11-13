#pragma once

#include "core/ui/screen.hpp"
#include "goss.hpp"

namespace otto::engines::goss {

  using namespace itc;

  struct GossScreen : ui::Screen {
    void draw(nvg::Canvas& ctx) override;

    void action(itc::prop_change<&Props::model>, int m) noexcept;
    void action(itc::prop_change<&Props::drawbar2>, float d2) noexcept;
    void action(itc::prop_change<&Props::click>, float c) noexcept;
    void action(itc::prop_change<&Props::leslie>, float l) noexcept;
    void action(Actions::rotation_variable, std::atomic<float>& v) noexcept;

    int model = 0;
    float drawbar2 = 0;
    float click = 0;
    float leslie = 0;
    std::atomic<float>* rotation = nullptr;
  };
} // namespace otto::engines::goss
