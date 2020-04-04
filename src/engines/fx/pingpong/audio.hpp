#pragma once
#include "Gamma/Delay.h"
#include "util/dsp/dj_filter.hpp"
#include "pingpong.hpp"

namespace otto::engines::pingpong {

  using namespace core;

  struct Audio {
    Audio() noexcept;
    audio::ProcessData<2> process(audio::ProcessData<1>) noexcept;


    void action(itc::prop_change<&Props::filter>, float f) noexcept;
    //void action(itc::prop_change<&Props::stereo>, float s) noexcept;

    void action(itc::prop_change<&Props::delaytime>, float t) noexcept;

    void action(itc::prop_change<&Props::feedback>, float f) noexcept;

  private:
    /// Feeds into each other
    gam::Delay<> delay_line;
    /// Gets output of delay line 0. Used for stereo spread.
    gam::Delay<> output_delay;
    /// Filters
    DJFilter<gam::Biquad<>> input_filter;
    DJFilter<gam::OnePole<>> loop_filter{2000, 15000};

    float feedback_;
    
  };
} // namespace otto::engines::wormhole
