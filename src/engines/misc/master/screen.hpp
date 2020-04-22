#pragma once

#include "master.hpp"

namespace otto::engines::master {

  using namespace core;

  struct Screen final : ui::Screen,
                        itc::ActionReceiverOnBus<itc::GraphicsBus,
                                                 itc::prop_change<&Props::volume>,
                                                 itc::prop_change<&Props::tempo>> //
  {
    void draw(nvg::Canvas& ctx) override;
    void action(itc::prop_change<&Props::volume>, float v) noexcept final;
    void action(itc::prop_change<&Props::tempo>, float t) noexcept final;

    float volume_ = 0.f;
    float rotation = 0.f;
    float tempo_ = 120;
  };

} // namespace otto::engines::master
