#pragma once

#include "util/dsp/transpose.hpp"
#include "wormhole.hpp"

namespace otto::engines::wormhole {

  using namespace core;

  struct Audio {
    Audio() noexcept;
    audio::ProcessData<2> process(audio::ProcessData<1>) noexcept;

    void action(itc::prop_change<&Props::filter>, float f) noexcept;
    void action(itc::prop_change<&Props::shimmer>, float s) noexcept;
    void action(itc::prop_change<&Props::length>, float l) noexcept;
    void action(itc::prop_change<&Props::damping>, float d) noexcept;

  private:
    float last_sample = 0;
    float shimmer_amount = 0;
    gam::ReverbMS<> reverb;
    dsp::SimplePitchShift pitchshifter;
    std::array<gam::Delay<>, 2> output_delay;
    gam::Biquad<> shimmer_filter;
    gam::BlockDC<> dc_block;
    gam::Biquad<> pre_filter;
  };
} // namespace otto::engines::wormhole
