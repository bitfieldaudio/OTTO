//**************************************************************************
//
//	$file: yule_walker.c $
//	$author: Martin Fouilleul $
//	$date: 28/11/2018 $
//	$description: a simple Yule-Walker system solver$
//
//**************************************************************************

#include<string.h> // memset()

namespace otto::dsp
{
//--------------------------------------------------------------------------
//
//	SolveYuleWalker() is a simple solver for Yule-Walker equations using a specialized version of the Levinson-Durbin algorithm.
//
//	arguments :
//		- size : the size of the Toeplitz matrix and of result vector sigmaAndCoeffs
//		- acov : a buffer containing the covariance coefficents for indices 0 to (size-1).
//			     ie. [acov(0) acov(1) ... acov(n-1)] of length (size)
//
//		- sigmaAndCoeffs : result vector of length (size). The first element will be the variance of the signal, and the remaining elements will be the estimated coefficients of the autoregressive filter.
//		- scratchBuffer : a block of memory used to hold intermediate computations. You must pass a buffer of size at least (2 * size * sizeof(float)).
//
//--------------------------------------------------------------------------

void solve_yule_walker(gsl::span<const float> acov, gsl::span<float> sigma_and_coeffs, gsl::span<float> scratch_buffer)
{
	//NOTE(martin): first we solve the system Mx = y, where M is the symmetrical Toeplitz matrix derived from the autocovariance acov and y = [1 0 ... 0]T
	//		Then we extract sigma as 1/x[0] and the filter coefficients as coeff[k] = - sigma * x[k+1].
	//		(note that the results are packed in sigmaAndCoeffs, so sigma = sigmaAndCoeff[0] and coeff[k] = sigmaAndCoeff[k+1] !)

	//NOTE(martin): Clear and organize the scratch memory
	util::fill(sigma_and_coeffs, 0.f);
	util::fill(scratch_buffer, 0.f);

	gsl::span<float> backward_prev = {scratch_buffer.begin(), scratch_buffer.begin() + acov.size()};
	gsl::span<float> backward = {scratch_buffer.begin() + acov.size(), scratch_buffer.end()};

	//NOTE(martin): Initialize our first induction variables
	float inv = 1./acov[0];
	sigma_and_coeffs[0] = backward_prev[acov.size() - 1] = inv;

	int lastB = acov.size() - 1;

	//NOTE(martin): Loop to compute our induction variables until we reach the appropriate vector size
	for(int n = 2; n <= acov.size(); n++)
	{
		//NOTE(martin): Compute forward and backward vectors from previous versions

		int firstB = acov.size() - n;
		float eb = 0;

		for(int i=1; i<n; i++)
		{
			eb += acov[i] * backward_prev[firstB+i];
		}

		float beta = 1./(1 - eb*eb);
		float alpha = -eb /(1 - eb*eb);

		for(int i=0; i<n; i++)
		{
			backward[firstB+i] = alpha * backward_prev[lastB-i] + beta * backward_prev[firstB+i];
		}

		//NOTE(martin): Compute x error and update x accordingly

		float ex = 0;
		unsigned int lastT = n-1;
		for(int i=0; i<n-1; i++)
		{
			ex += acov[lastT-i] * sigma_and_coeffs[i] ;
		}

		for(int i=0; i<n; i++)
		{
			sigma_and_coeffs[i] = sigma_and_coeffs[i] - ex * backward[firstB+i];
		}

		//NOTE(martin): swap previous and current forward/backward vectors

		auto tmp = backward;
		backward = backward_prev;
		backward_prev = tmp;
	}
	//NOTE(martin): get sigma and renormalize filter coefficients

	float sigma = 1./sigma_and_coeffs[0];
	for(int i=1; i<size; i++)
	{
		sigma_and_coeffs[i] = - sigma * sigma_and_coeffs[i];
	}
	sigma_and_coeffs[0] = sigma;
}

} // namespace otto::dsp;
