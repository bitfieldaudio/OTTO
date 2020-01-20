#pragma once

#include "core/ui/vector_graphics.hpp"
#include "core/ui/icons.hpp"
#include "sends.hpp"

namespace otto::engines::sends {

  using namespace core;
  using namespace core::input;
  using namespace nvg;

  struct Screen : ui::Screen {

    Screen(core::ui::Icon i);
    
    void draw(Canvas& ctx) override;
    void draw_coloured_circle(Canvas& ctx, Point p, Color cl, float value);
    void draw_radial_lines(Canvas& ctx, float pan_float);
    void draw_background(Canvas& ctx);
    
    void action(itc::prop_change<&Props::dry>, float d) noexcept;
    void action(itc::prop_change<&Props::fx1>, float fx1) noexcept;
    void action(itc::prop_change<&Props::fx2>, float fx2) noexcept;
    void action(itc::prop_change<&Props::pan>, float p) noexcept;

  private:
    float dry_ = 1;
    float fx1_ = 0;
    float fx2_ = 0;
    float pan_ = 0.5;

    core::ui::Icon icon_;
  };



}