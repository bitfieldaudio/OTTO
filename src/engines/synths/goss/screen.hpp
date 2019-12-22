#pragma once

#include "core/ui/screen.hpp"
#include "goss.hpp"

#include "audio.hpp"

namespace otto::engines::goss {

  using namespace itc;

  struct GossScreen : ui::Screen {
    GossScreen(itc::Shared<float>) noexcept;
    void draw(nvg::Canvas& ctx) override;
    void draw_model(nvg::Canvas& ctx);

    void action(itc::prop_change<&Props::model>, int m) noexcept;
    void action(itc::prop_change<&Props::click>, float c) noexcept;
    void action(itc::prop_change<&Props::drive>, float d) noexcept;
    void action(itc::prop_change<&Props::leslie>, float l) noexcept;

    itc::Shared<float> rotation;
    int model = 0;
    float drive = 0;
    float click = 0;
    float leslie = 0;

    model_type model_param;
  };
} // namespace otto::engines::goss
