#pragma once

#include "sends.hpp"

namespace otto::engines::sends {

  using namespace core;

  struct Audio final : itc::ActionReceiverOnBus<itc::AudioBus,
                                                itc::prop_change<&Props::dry>,
                                                itc::prop_change<&Props::fx1>,
                                                itc::prop_change<&Props::fx2>,
                                                itc::prop_change<&Props::pan>> //
  {
    Audio() noexcept {};

    void recalculate_dry()
    {
      // TODO: Use real panning object
      dryL = (1 - pan_) * dry_;
      dryR = pan_ * dry_;
    }

    void action(itc::prop_change<&Props::dry>, float d) noexcept final
    {
      dry_ = d;
      recalculate_dry();
    };
    void action(itc::prop_change<&Props::fx1>, float fx1) noexcept final
    {
      to_fx1 = fx1;
    };
    void action(itc::prop_change<&Props::fx2>, float fx2) noexcept final
    {
      to_fx2 = fx2;
    };
    void action(itc::prop_change<&Props::pan>, float p) noexcept final
    {
      pan_ = p;
      recalculate_dry();
    };

    /// Actual values used in the enginemanager
    float dryL = 0.5;
    float dryR = 0.5;
    float to_fx1 = 0;
    float to_fx2 = 0;

  private:
    float dry_ = 1;
    float pan_ = 0.5;
  };
} // namespace otto::engines::sends
