#pragma once

#include "core/ui/vector_graphics.hpp"
#include <Gamma/Envelope.h>
#include "chorus.hpp"

namespace otto::engines::chorus {

  using namespace core;

  struct Screen : ui::Screen {
    Screen(itc::Shared<float> phase) noexcept;
    void draw(nvg::Canvas& ctx) override;
    void draw_front_head(nvg::Canvas&, nvg::Point, ui::vg::Color, float);
    void draw_background_head(nvg::Canvas&, nvg::Point, ui::vg::Color, float);
    
    void action(itc::prop_change<&Props::delay>, float d) noexcept;
    void action(itc::prop_change<&Props::rate>, float r) noexcept;
    void action(itc::prop_change<&Props::feedback>, float f) noexcept;
    void action(itc::prop_change<&Props::depth>, float d) noexcept;

  private:
    float delay_ = 0.f;
    float rate_ = 0.f;
    float feedback_ = 0.f;
    float depth_ = 0.f;
    float wave_height = 20;

    itc::Shared<float> phase_;

    // Individual brightness for the heads. Depends on feedback
    std::array<float, 10> brightness;

    ch::Output<float> env_blue_ = 0;
    ch::Output<float> env_green_ = 0;
    ch::Output<float> env_yellow_ = 0;
    ch::Output<float> env_red_ = 0;
  };
 
} // namespace otto::engines::chorus
