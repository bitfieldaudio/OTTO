#pragma once
#include <gsl/span>

namespace otto::dsp {
  ///
  ///	\brief This is a simple solver for Yule-Walker equations using a specialized version of
  /// the Levinson-Durbin algorithm.
  ///
  ///	\param[in] acov - a buffer containing the covariance coefficents for indices 0 to (size-1).
  /// ie. [acov(0) acov(1) ... acov(n-1)] of length (size)
  ///
  /// \param[out] sigma_and_coeffs - result vector of length (size). The first element will be the
  /// variance of the signal, and the remaining elements will be the estimated coefficients of the
  /// autoregressive filter.
  ///
  /// \param[in] scratch_buffer - a block of memory used to hold intermediate computations. You must
  /// pass a buffer of size at least (2 * size * sizeof(float)).
  ///
  void solve_yule_walker(gsl::span<const float> acov,
                         gsl::span<float> sigma_and_coeffs,
                         gsl::span<float> scratch_buffer);

} // namespace otto::dsp
