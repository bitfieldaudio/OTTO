#pragma once

#include "external_in.hpp"

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

    void action(itc::prop_change<&Props::gain>, float g) noexcept
    {
      gain_ = g;
      recalculate();
    };
    void action(itc::prop_change<&Props::enabled>, bool e) noexcept
    {
      enable_ = e;
      recalculate();
    }
    void action(itc::prop_change<&Props::stereo_balance>, float b) noexcept
    {
      balance_ = b;
      recalculate();
    };
    void action(itc::prop_change<&Props::stereo_routing>, int r) noexcept
    {
      routing_ = r;
      recalculate();
    };

    /// Actual values used in the enginemanager
    float L_to_fx1 = 0.5;
    float R_to_fx1 = 0.5;
    float L_to_fx2 = 0.5;
    float R_to_fx2 = 0.5;
    float dryL = 0.5;
    float dryR = 0.5;

  private:
    float gain_ = 0.5;
    bool enable_ = true;
    int routing_ = 0;
    float balance_ = 0.5;
  };
} // namespace otto::engines::external