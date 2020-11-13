#pragma once

#include <array>

#include <Gamma/Delay.h>
#include <Gamma/Envelope.h>
#include <Gamma/Filter.h>
#include <Gamma/Oscillator.h>
#include <Gamma/Spatial.h>
#include <Gamma/Types.h>
#include <Gamma/scl.h>

namespace otto::dsp {

  /// Simple Pitch shifter
  struct SimplePitchShift {
    SimplePitchShift();

    float operator()(float) noexcept;

    // Sets crossfade in seconds
    void crossfade(int);

    // Sets maximum delay in seconds
    void maxdelay(int);

  private:
    std::array<gam::Delay<>, 2> delay;
    std::array<gam::ADSR<>, 2> amp;
    std::array<gam::LFO<>, 2> lfo_delay;

    int _maxdelay = 10000;
    int _crossfade = 300;
    float _frac = 0.2;

    std::array<int, 2> delay_amount = {_maxdelay + _crossfade, 0};
    std::array<float, 2> amp_amount = {1.f, 0.f};
  };

} // namespace otto::dsp
