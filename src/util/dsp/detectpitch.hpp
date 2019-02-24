#pragma once
#include <gsl/span>
#include "acovb.hpp"
#define THRESHOLD 0.5

namespace otto::dsp {
    ///
    ///	\brief This is a simple pitch-detection algorithm using an autocovariance estimator.
    /// By convention, it returns 0 if the signal is aperiodic/unvoiced or if the
    /// detected period is out of the considered scope.
    ///
    ///	\param[in] data - a buffer containing the audio.
    ///
    /// \param[minT] minT - the minimum period in samples to consider.
    ///
    /// \param[in] maxT - the maximum period in samples to consider.
    ///
    int detect_pitch(gsl::span<float> data, int minT, int maxT){
      const long int N = data.size();
      float gamma_arr[N];
      auto gamma = gsl::span(gamma_arr, N);
      for(int i=0; i<N; ++i) gamma[i] = data[i];
      acovb(gamma);
      for (auto&& c : gamma) c /= gamma[0];

      int T = std::max_element(gamma.begin()+minT, gamma.end()) - gamma.begin();

      if (gamma[T]*N/(N-T) < THRESHOLD || T > maxT){
        T = 0;
      }
      return T;
    }
} // namespace otto::dsp

