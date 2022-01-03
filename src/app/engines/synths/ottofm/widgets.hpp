#pragma once

#include "lib/skia/anim.hpp"
#include "lib/skia/skia.hpp"
#include "lib/widget.hpp"

#include "app/engines/synths/ottofm/state.hpp"

#include "ottofm.hpp"

namespace otto::engines::ottofm {

  struct Operators : graphics::Widget<Operators> {
    Operators(const std::array<float, 4>& a) : activity_levels(a) {}
    int algorithm_idx = 0, cur_op = 0;
    std::array<skia::Color, 4> operator_colours = {colors::red, colors::yellow, colors::green, colors::blue};

    const std::array<float, 4>& activity_levels;

    void do_draw(skia::Canvas& ctx);
  };

  // Should be resized when expanding and compressing
  struct FractionGraphic : graphics::Widget<FractionGraphic> {
    int numerator = 0;
    int denominator = 0;
    float expansion = 0;
    bool active = false;

    void do_draw(skia::Canvas& ctx);
  };

  struct DetuneGraphic : graphics::Widget<DetuneGraphic> {
    float value = 0;
    float expansion = 0;
    bool active = false;

    void do_draw(skia::Canvas& ctx);
  };

  struct LevelGraphic : graphics::Widget<LevelGraphic> {
    float value = 0;
    float expansion = 0;
    bool active = false;

    void do_draw(skia::Canvas& ctx);
  };

  // Should only be constructed once.
  struct WaveShapeGraphic : graphics::Widget<WaveShapeGraphic> {
    float value = 0, l_value = 0, r_value = 0;
    float expansion = 0;
    bool active = false;
    std::array<float, 30> sinewave = {};
    std::array<float, 30> right_harmonics = {};
    std::array<float, 30> left_harmonics = {};

    WaveShapeGraphic();

    void do_draw(skia::Canvas& ctx);
  };

} // namespace otto::engines::ottofm
