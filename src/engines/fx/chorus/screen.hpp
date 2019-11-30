#pragma once


#include "core/ui/vector_graphics.hpp"
#include <Gamma/Envelope.h>
#include "chorus.hpp"



namespace otto::engines::chorus {

  using namespace core;

  struct Screen : ui::Screen {
    void draw(nvg::Canvas& ctx) override;
    void draw_front_head(nvg::Canvas&, nvg::Point, ui::vg::Color, float);
    void draw_background_head(nvg::Canvas&, nvg::Point, ui::vg::Color, float);

    float delay_ = 0.f;
    void action(itc::prop_change<&Props::delay>, float d) noexcept;
    float depth_ = 0.f;
    void action(itc::prop_change<&Props::depth>, float d) noexcept;
    float feedback_ = 0.f;
    void action(itc::prop_change<&Props::feedback>, float f) noexcept;
    float rate_ = 0.f;
    void action(itc::prop_change<&Props::rate>, float r) noexcept;
    std::atomic<float>* phase_ = nullptr;
    void action(Actions::phase_value, std::atomic<float>& v) noexcept;

    std::array<ui::vg::Color, 10> colour_list = {ui::vg::Colors::Blue,
                                                  ui::vg::Colors::Green,
                                                  ui::vg::Colors::Yellow,
                                                  ui::vg::Colors::Red,
                                                  ui::vg::Colors::Green,
                                                  ui::vg::Colors::Blue,
                                                  ui::vg::Colors::Red,
                                                  ui::vg::Colors::Green,
                                                  ui::vg::Colors::Yellow,
                                                  ui::vg::Colors::Red};

    float wave_height = 20;
    float intpart = 1;
    gam::AD<> env_blue{0.0005, 0.002, 1, 0};
    gam::AD<> env_green{0.0005, 0.002, 1, 0};
    gam::AD<> env_yellow{0.0005, 0.002, 1, 0};
    gam::AD<> env_red{0.0005, 0.002, 1, 0};
  };
 
} // namespace otto::engines::chorus
