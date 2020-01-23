#pragma once

#include "master.hpp"

namespace otto::engines::master {

  using namespace core;

  struct Audio {
    Audio() noexcept;
    audio::ProcessData<2> process(audio::ProcessData<2>) noexcept;

    void action(itc::prop_change<&Props::volume>, float v) noexcept;
    void action(itc::prop_change<&Props::tempo>, float t) noexcept;

  private:
    float tempo_ = 120;
  };
} // namespace otto::engines::master
