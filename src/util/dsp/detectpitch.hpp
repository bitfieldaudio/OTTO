#pragma once
#include "services/audio_manager.hpp"
#include <gsl/span>
#include "acovb.hpp"

namespace otto::dsp {

    constexpr float pitch_threshold = 0.5;

    ///
    ///	\brief This is a simple pitch-detection algorithm using an autocovariance estimator.
    /// By convention, it returns 0 if the signal is aperiodic/unvoiced or if the
    /// detected period is out of the considered scope.
    ///
    ///	\param[in] gamma - a buffer containing the autocovariance of the audio frame.
    ///
    /// \param[minT] minT - the minimum period in samples to consider.
    ///
    /// \param[in] maxT - the maximum period in samples to consider.
    ///
    int detect_pitch(gsl::span<float> gamma, int minT, int maxT){
      int N = (int) gamma.size();
      for (auto&& c : gamma) c /= gamma[0];
      long int T = std::max_element(gamma.begin()+minT, gamma.end()) - gamma.begin();
      if (gamma[T]*N/(N-T) < pitch_threshold || T > maxT){
        T = 0;
      }
      return (int) T;
    }
} // namespace otto::dsp

