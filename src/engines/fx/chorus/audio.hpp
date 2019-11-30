#pragma once

#include "chorus.hpp"

#include <Gamma/Filter.h>
#include <Gamma/Oscillator.h>
#include "core/voices/voice_manager.hpp"
#include "util/dsp/chorus.hpp"

namespace otto::engines::chorus {

  using namespace core;

  struct Audio {
    Audio() noexcept;
    float depth_ = 0.f;
    void action(itc::prop_change<&Props::delay>, float d) noexcept;
    void action(itc::prop_change<&Props::depth>, float d) noexcept;
    void action(itc::prop_change<&Props::feedback>, float f) noexcept;
    void action(itc::prop_change<&Props::rate>, float r) noexcept;
    void action(Actions::phase_value, std::atomic<float>& v) noexcept;

    audio::ProcessData<2> process(audio::ProcessData<1>) noexcept;
  private:
    ChorusEffect<> chorus;
    gam::AccumPhase<> phase;
    std::atomic<float>* shared_phase = nullptr;
  };
} // namespace otto::engines::chorus
