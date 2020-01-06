#pragma once

#include "external.hpp"
#include "services/log_manager.hpp"

namespace otto::engines::external {

  using namespace core;

  struct Audio {
    Audio() noexcept {};

    void recalculate()
    {
      switch (mode_) {
        case ModeEnum::disabled: {
          gainL = 0;
          gainR = 0;
          break;
        }
        case ModeEnum::stereo: {
          gainL = stereo_gain_ * (1 - stereo_balance_);
          gainR = stereo_gain_ * stereo_balance_;
          break;
        }
        case ModeEnum::dual_mono: {
          gainL = left_gain_;
          gainR = right_gain_;
          break;
        }
          OTTO_UNREACHABLE;
      }
    }

    void action(itc::prop_change<&Props::mode>, ModeEnum m) noexcept
    {
      mode_ = m;
      recalculate();
    }
    void action(itc::prop_change<&Props::stereo_gain>, float g) noexcept
    {
      stereo_gain_ = g;
      recalculate();
    }
    void action(itc::prop_change<&Props::stereo_balance>, float b) noexcept
    {
      stereo_balance_ = b;
      recalculate();
    }
    void action(itc::prop_change<&Props::left_gain>, float g) noexcept
    {
      left_gain_ = g;
      recalculate();
    }
    void action(itc::prop_change<&Props::right_gain>, float g) noexcept
    {
      right_gain_ = g;
      recalculate();
    }
    void action(itc::prop_change<&Props::active_send>, int a) noexcept
    {
      active_send_ = a;
    }

    /// Actual values used in the enginemanager
    float gainL = 1;
    float gainR = 1;

    ModeEnum mode_ = ModeEnum::stereo;

  private:
    float stereo_gain_ = 0.5;
    float stereo_balance_ = 0.5;
    float left_gain_ = 0.5;
    float right_gain_ = 0.5;
    int active_send_ = 0;
  };
} // namespace otto::engines::external