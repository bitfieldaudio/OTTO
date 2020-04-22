#pragma once

#include "core/ui/icons.hpp"
#include "core/ui/vector_graphics.hpp"
#include "sends.hpp"

namespace otto::engines::sends {

  using namespace core;
  using namespace core::input;
  using namespace nvg;

  struct Screen final : ui::Screen,
                        itc::ActionReceiverOnBus<itc::GraphicsBus,
                                                 itc::prop_change<&Props::dry>,
                                                 itc::prop_change<&Props::fx1>,
                                                 itc::prop_change<&Props::fx2>,
                                                 itc::prop_change<&Props::pan>> //
  {
    Screen(core::ui::Icon i);

    void draw(Canvas& ctx) override;
    void draw_coloured_circle(Canvas& ctx, Point p, Color cl, float value);
    void draw_radial_lines(Canvas& ctx, float pan_float);
    void draw_background(Canvas& ctx);

    void action(itc::prop_change<&Props::dry>, float d) noexcept final;
    void action(itc::prop_change<&Props::fx1>, float fx1) noexcept final;
    void action(itc::prop_change<&Props::fx2>, float fx2) noexcept final;
    void action(itc::prop_change<&Props::pan>, float p) noexcept final;

  private:
    float dry_ = 1;
    float fx1_ = 0;
    float fx2_ = 0;
    float pan_ = 0.5;

    core::ui::Icon icon_;
  };



} // namespace otto::engines::sends
