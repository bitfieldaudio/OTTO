#pragma once

#include "wormhole.hpp"

namespace otto::engines::wormhole {

  using namespace core;

  struct Screen final : ui::Screen,
                        itc::ActionReceiverOnBus<itc::GraphicsBus,
                                                 itc::prop_change<&Props::filter>,
                                                 itc::prop_change<&Props::shimmer>,
                                                 itc::prop_change<&Props::length>,
                                                 itc::prop_change<&Props::damping>> //
  {
    void draw(nvg::Canvas& ctx) override;

    void action(itc::prop_change<&Props::filter>, float f) noexcept final;
    void action(itc::prop_change<&Props::shimmer>, float s) noexcept final;
    void action(itc::prop_change<&Props::length>, float l) noexcept final;
    void action(itc::prop_change<&Props::damping>, float d) noexcept final;

    float filter_ = 0.f;
    float shimmer_ = 0.f;
    float length_ = 0.f;
    float damping_ = 0.f;
  };

} // namespace otto::engines::wormhole
