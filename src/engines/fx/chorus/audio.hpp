#pragma once

#include "chorus.hpp"

#include <Gamma/Filter.h>
#include <Gamma/Oscillator.h>
#include "core/voices/voice_manager.hpp"
#include "util/dsp/chorus.hpp"

namespace otto::engines::chorus {

  using namespace core;

  struct Audio {
    Audio(itc::Shared<float> phase) noexcept;
    void action(itc::prop_change<&Props::delay>, float d) noexcept;
    void action(itc::prop_change<&Props::depth>, float d) noexcept;
    void action(itc::prop_change<&Props::feedback>, float f) noexcept;
    void action(itc::prop_change<&Props::rate>, float r) noexcept;

    audio::ProcessData<2> process(audio::ProcessData<1>) noexcept;
  private:
    ChorusEffect<> chorus;
    float depth_ = 0.f;
    gam::AccumPhase<> phase;
    itc::Shared<float> shared_phase;
  };
} // namespace otto::engines::chorus
