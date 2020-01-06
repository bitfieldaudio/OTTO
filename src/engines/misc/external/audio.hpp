#pragma once

#include "external.hpp"

namespace otto::engines::external {

  using namespace core;

  struct Audio {
    Audio() noexcept {};

    void recalculate()
    {
      // Temporary, to silence errors
      L_to_fx1 = 0.5;
      R_to_fx1 = 0.5;
      L_to_fx2 = 0.5;
      R_to_fx2 = 0.5;
      dryL = 0.5;
      dryR = 0.5;
    }

  void action(itc::prop_change<&Props::mode>, ModeEnum m) noexcept
  {
    mode_ = m;
    recalculate();
  }
  void action(itc::prop_change<&Props::stereo_gain>, float g) noexcept
  {
    stereo_gain_ = g;
  }
  void action(itc::prop_change<&Props::stereo_balance>, float b) noexcept
  {
    stereo_balance_ = b;
  }
  void action(itc::prop_change<&Props::left_gain>, float g) noexcept
  {
    left_gain_ = g;
  }
  void action(itc::prop_change<&Props::right_gain>, float g) noexcept
  {
    right_gain_ = g;
  }
  void action(itc::prop_change<&Props::active_send>, int a) noexcept
  {
    active_send_ = a;
  }

    /// Actual values used in the enginemanager
    float L_to_fx1 = 0.5;
    float R_to_fx1 = 0.5;
    float L_to_fx2 = 0.5;
    float R_to_fx2 = 0.5;
    float dryL = 0.5;
    float dryR = 0.5;

  private:
    float stereo_gain_ = 0.5;
    float stereo_balance_ = 0.5;
    float left_gain_ = 0.5;
    float right_gain_ = 0.5;
    int active_send_ = 0;
    ModeEnum mode_ = ModeEnum::stereo;
  };
} // namespace otto::engines::external