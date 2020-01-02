#pragma once

#include "sends.hpp"

namespace otto::engines::sends {

  using namespace core;

  struct Audio {
    Audio() noexcept {};

    void recalculate() 
    {
      dryL = volume_ * (1 - pan_) * (1 - mix_);
      dryR = volume_ * pan_ * (1 - mix_);
      to_fx1 = volume_ * (1 - sendAB_) * mix_;
      to_fx2 = volume_ * (1 - sendAB_) * mix_;
    }

    void action(itc::prop_change<&Props::mix>, float m) noexcept 
    {
      mix_ = m;
      recalculate();
    };
    void action(itc::prop_change<&Props::volume>, float v) noexcept
    {
      volume_ = v;
      recalculate();
    }
    void action(itc::prop_change<&Props::sendAB>, float s) noexcept
    {
      sendAB_ = s;
      recalculate();
    };
    void action(itc::prop_change<&Props::pan>, float p) noexcept
    {
      pan_ = p;
      recalculate();
    };

  private:
    float mix_ = 0;
    float volume_ = 1;
    float sendAB_ = 0.5;
    float pan_ = 0.5;

    /// Actual values used in the enginemanager
    float dryL = 0.5;
    float dryR = 0.5;
    float to_fx1 = 0;
    float to_fx2 = 0;
  };
} // namespace otto::engines::wormhole