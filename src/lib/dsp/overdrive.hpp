#pragma once

#include <math.h>

#include "lib/util/math.hpp"

namespace otto::dsp {

  /// Overdrive written for the Goss Hammond emulation. It consists of a pre-filter, a waveshaper, and a post-filter.
  /// TODO: The signal is upsampled before the waveshaper and downsampled after it
  struct HammondPreamp {
    float operator()(float in) noexcept
    {
      return postfilter(waveshaper(prefilter(in)));
    };


  private:
    float prefilter(float in) noexcept
    {
      // Bias
      sagZ_ = sagFb * sagZ_ + fabsf(in);
      bias_ = bias_base - sagZgb * sagZ_;
      norm_ = 1.0f - (1.0f / (1.0f + (bias_ * bias_)));

      // Skipping weird convolution shit for now.

      // Filter
      in -= (adwGfb * adwGfZ_);
      temp_ = in - adwZ_;
      adwZ_ = in + (adwZ_ * adwFb);
      return temp_;
    };

    float waveshaper(float in) noexcept
    {
      int sign_of_input = util::math::sgn(in);
      float x2 = in + sign_of_input * bias_;
      return sign_of_input * (1.0 - norm_ - (1.0 / (1.0 + (x2 * x2))));
    }

    float postfilter(float in) noexcept
    {
      temp_ = in + (adwFb2 * adwZ1_);
      float out = temp_ - adwZ1_;
      adwZ1_ = temp_;

      /* Global negative feedback */
      adwGfZ_ = out;

      return out;
    }

    float sagZ_ = 0.0f;
    float bias_ = 0.0f;
    float norm_ = 0.0f;
    float temp_ = 0.0f;
    float adwZ1_ = 0.0f;
    float adwGfZ_ = 0.0f;
    float adwZ_ = 0.0f;

    /// Params
    // filter coeff for sag
    float sagFb = 0.991f;
    // Base bias amount
    float bias_base = 0.5347f;
    // Amount that sag changes bias
    float sagZgb = 0.0094f;
    // Global feedback
    float adwGfb = -0.6214f;
    // Local feedback in prefilter
    float adwFb = 0.5821f;
    // Local feedback in postfilter
    float adwFb2 = 1.0f;
  };

} // namespace otto::dsp
