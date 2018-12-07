//**************************************************************************
//
//	$file: yule_walker.cpp $
//	$author: Martin Fouilleul $
//	$date: 28/11/2018 $
//	$description: a simple Yule-Walker system solver$
//
//**************************************************************************

#include "util/algorithm.hpp"
#include "yule_walker.hpp"

namespace otto::dsp {
  void solve_yule_walker(gsl::span<const float> acov,
                         gsl::span<float> sigma_and_coeffs,
                         gsl::span<float> scratch_buffer)
  {
    // First we solve the system Mx = y, where M is the symmetrical
    // Toeplitz matrix derived from the autocovariance acov and y = [1 0 ... 0]T
    //
    // Then we extract sigma as 1/x[0] and the filter coefficients as
    // coeff[k] = - sigma * x[k+1].
    //
    // Please note that the results are packed in sigma_and_coeffs, so:
    // sigma = sigma_and_coeffs[0]
    // coeff[k] = sigma_and_coeffs[k+1]

    util::fill(sigma_and_coeffs, 0.f);

    // Clear and organize the scratch memory
    util::fill(scratch_buffer, 0.f);
    gsl::span<float> backward_prev = scratch_buffer.subspan(0, acov.size());
    gsl::span<float> backward = scratch_buffer.subspan(acov.size(), acov.size());

    // Initialize our first induction variables
    float inv = 1. / acov[0];
    sigma_and_coeffs[0] = backward_prev[acov.size() - 1] = inv;

    int lastB = acov.size() - 1;

    // Loop to compute our induction variables until we reach the
    // appropriate vector size
    for (int n = 2; n <= acov.size(); n++) {
      // Compute backward vector from previous versions
      int firstB = acov.size() - n;
      float eb = 0;

      for (int i = 1; i < n; i++) {
        eb += acov[i] * backward_prev[firstB + i];
      }

      float beta = 1. / (1 - eb * eb);
      float alpha = -eb / (1 - eb * eb);

      for (int i = 0; i < n; i++) {
        backward[firstB + i] = alpha * backward_prev[lastB - i] + beta * backward_prev[firstB + i];
      }

      // Compute x error and update x accordingly

      float ex = 0;
      unsigned int lastT = n - 1;
      for (int i = 0; i < n - 1; i++) {
        ex += acov[lastT - i] * sigma_and_coeffs[i];
      }

      for (int i = 0; i < n; i++) {
        sigma_and_coeffs[i] = sigma_and_coeffs[i] - ex * backward[firstB + i];
      }

      // Swap previous and current forward/backward vectors
      auto tmp = backward;
      backward = backward_prev;
      backward_prev = tmp;
    }
    // Get sigma and renormalize filter coefficients

    float sigma = 1. / sigma_and_coeffs[0];
    for (int i = 1; i < acov.size(); i++) {
      sigma_and_coeffs[i] = -sigma * sigma_and_coeffs[i];
    }
    sigma_and_coeffs[0] = sigma;
  }

} // namespace otto::dsp
