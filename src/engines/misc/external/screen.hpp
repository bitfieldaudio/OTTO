#pragma once

#include "core/ui/nvg/Canvas.hpp"
#include "core/ui/vector_graphics.hpp"
#include "external.hpp"

namespace otto::engines::external {

  using namespace core;
  using namespace core::input;

  struct Screen : ui::Screen {
    void draw(nvg::Canvas& ctx) override;
    void draw_jack(nvg::Canvas& ctx, bool active);
    void draw_pan(nvg::Canvas& ctx, float pan_float);
    void draw_levels(nvg::Canvas& ctx, ModeEnum mode);
    void draw_active_send(nvg::Canvas& ctx, int active_send);

    void action(itc::prop_change<&Props::mode>, ModeEnum m) noexcept;
    void action(itc::prop_change<&Props::stereo_gain>, float g) noexcept;
    void action(itc::prop_change<&Props::stereo_balance>, float b) noexcept;
    void action(itc::prop_change<&Props::left_gain>, float g) noexcept;
    void action(itc::prop_change<&Props::right_gain>, float g) noexcept;
    void action(itc::prop_change<&Props::active_send>, int a) noexcept;

  private:
    float stereo_gain_ = 0.5;
    float stereo_balance_ = 0.5;
    float left_gain_ = 0.5;
    float right_gain_ = 0.5;
    int active_send_ = 0;
    ModeEnum mode_ = ModeEnum::stereo;

    std::string mode_str;
    std::string active_send_str;
  };
} // namespace otto::engines::external