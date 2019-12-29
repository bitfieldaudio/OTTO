#pragma once

#include "core/ui/vector_graphics.hpp"
#include "sends.hpp"

namespace otto::engines::sends {

  using namespace core;
  using namespace core::input;

  struct Screen : ui::Screen {
  
    void draw(nvg::Canvas& ctx) override;
    
    void action(itc::prop_change<&Props::mix>, float m) noexcept;
    void action(itc::prop_change<&Props::volume>, float v) noexcept;
    void action(itc::prop_change<&Props::sendAB>, float s) noexcept;
    void action(itc::prop_change<&Props::pan>, float p) noexcept;

  private:
    float mix_ = 0;
    float volume_ = 1;
    float sendAB_ = 0.5;
    float pan_ = 0.5;
  };



}