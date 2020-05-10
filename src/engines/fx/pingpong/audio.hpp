#pragma once

#include "Gamma/Delay.h"
#include "pingpong.hpp"
#include "services/application.hpp"
#include "util/dsp/dj_filter.hpp"

namespace otto::engines::pingpong {

  using namespace core;

  struct Audio {
    Audio() noexcept;
    audio::ProcessData<2> process(audio::ProcessData<1>) noexcept;


    void action(itc::prop_change<&Props::filter>, float f) noexcept;

    void action(itc::prop_change<&Props::stereo>, float s) noexcept;
    void action(itc::prop_change<&Props::stereo_invert>, bool inv) noexcept;

    void action(itc::prop_change<&Props::delaytime>, float t) noexcept;

    void action(itc::prop_change<&Props::feedback>, float f) noexcept;

  private:
    /// Feeds into each other
    std::array<gam::Delay<>, 2> delay_line;
    /// Gets output of delay line 0. Used for stereo spread.
    gam::Delay<> output_delay;
    /// Filters
    DJFilter<gam::Biquad<>> input_filter{400, 10000};
    std::array<DJFilter<gam::OnePole<>>, 2> loop_filter = {{{300, 15000}, {300, 15000}}};


    float feedback_ = 0.5;
    float pingpong_ = 0;
    float spread_ = 0;
    const float spread_max = 0.100f;
    const float spread_max_samples = spread_max * gam::sampleRate() - 2.f;
    bool invert_ = false;
  };
} // namespace otto::engines::pingpong
