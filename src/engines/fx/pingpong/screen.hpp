#pragma once

#include "core/ui/nvg/Canvas.hpp"
#include "core/ui/vector_graphics.hpp"
#include "pingpong.hpp"

namespace otto::engines::pingpong {

  using namespace core;

  struct Screen : ui::Screen {
    Screen() noexcept;

    void action(itc::prop_change<&Props::timetype>, bool t) noexcept;
    void action(itc::prop_change<&Props::subdivision>, SubdivisionEnum s) noexcept;
    void action(itc::prop_change<&Props::delaytime>, float dt) noexcept;
    void action(itc::prop_change<&Props::filter>, float f) noexcept;
    void action(itc::prop_change<&Props::stereo>, float s) noexcept;
    void action(itc::prop_change<&Props::stereo_invert>, bool i) noexcept;
    void action(itc::prop_change<&Props::feedback>, float f) noexcept;

    void draw(nvg::Canvas& ctx) override;
    void draw_filter(nvg::Canvas& ctx, float val, nvg::Point pos, nvg::Size size);
    void draw_arc(nvg::Canvas& ctx, nvg::Point position, float size, float spread, float rotation);
    void draw_subdivision(nvg::Canvas& ctx, nvg::Point position, float size, SubdivisionEnum sd);

  private:
    bool timetype_ = false;
    SubdivisionEnum subdivision_ = SubdivisionEnum::quarter;
    float delaytime_ = 0;
    float filter_ = 0.5;
    float stereo_ = 0.5;
    bool stereo_invert_ = false;
    float feedback_ = 0.5;
  };

} // namespace otto::engines::pingpong
