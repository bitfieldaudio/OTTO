#pragma once
#include <algorithm>

#include "Gamma/Filter.h"
/// DJ-filter. Takes a filter type (One-pole, biquad, etc) and makes a pair of low- and highpass filters to be
/// controlled by a single center-neutral control.
/// \tparam Filter  Filter type. Must accept Low- and High-pass types
template<class Filter>
struct DJFilter {
  DJFilter(float lower = 300.f, float upper = 15000.f) : lower_freq_(lower), upper_freq_(upper)
  {
    lowpass.type(gam::LOW_PASS);
    highpass.type(gam::HIGH_PASS);
  }

  void calculate_freqs()
  {
    calculate_freqs(position_);
  }

  void calculate_freqs(float pos)
  {
    if (pos > 0.5f) {
      lowpass.freq(20000.f);
      auto ppp = powf(2.f * pos - 1.f, 3.f);
      highpass.freq(20 * (1.f - ppp) + upper_freq_ * ppp);
    } else {
      auto pp = powf(2.f * pos, 3.f);
      lowpass.freq(lower_freq_ * (1 - pp) + 20000 * pp);
      highpass.freq(20.f);
    }
  }

  void set_upper_freq(float u)
  {
    upper_freq_ = u;
    calculate_freqs();
  }
  void set_lower_freq(float l)
  {
    lower_freq_ = l;
    calculate_freqs();
  }

  void set_position(float p)
  {
    position_ = std::clamp(p, 0.f, 1.f);
    calculate_freqs(position_);
  }

  float operator()(float in)
  {
    return highpass(lowpass(in));
  }

  float get_lo_freq()
  {
    return lowpass.freq();
  }

  float get_hi_freq()
  {
    return highpass.freq();
  }

private:
  Filter lowpass;
  Filter highpass;
  float position_ = 0.5f;

  /// Play with these to get correct response
  float lower_freq_ = 300.f;
  float upper_freq_ = 15000.f;
};