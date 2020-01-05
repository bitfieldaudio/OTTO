#pragma once

#include "core/ui/vector_graphics.hpp"
#include "external_in.hpp"

namespace otto::engines::external {

  using namespace core;
  using namespace core::input;

  struct Screen : ui::Screen {
    void draw(nvg::Canvas& ctx) override;

    void action(itc::prop_change<&Props::mode>, int m) noexcept;
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
    int mode_ = 1;

    std::string mode_str;
    std::string gain_1;
    std::string gain_2;
    std::string active_send_str;
    float gain_1_val = 0;
    float gain_2_val = 0;
  };
} // namespace otto::engines::external