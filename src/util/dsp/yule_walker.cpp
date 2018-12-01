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

void SolveYuleWalker(unsigned int size, const float* acov, float* sigmaAndCoeffs, char* scratchBuffer)
{
	//NOTE(martin): first we solve the system Mx = y, where M is the symmetrical Toeplitz matrix derived from the autocovariance acov and y = [1 0 ... 0]T
	//		Then we extract sigma as 1/x[0] and the filter coefficients as coeff[k] = - sigma * x[k+1].
	//		(note that the results are packed in sigmaAndCoeffs, so sigma = sigmaAndCoeff[0] and coeff[k] = sigmaAndCoeff[k+1] !)

	//NOTE(martin): Clear and organize the scratch memory
	memset(sigmaAndCoeffs, 0, size*sizeof(float));
	memset(scratchBuffer, 0, 2*size*sizeof(float));

	float* backwardPrev = (float*)scratchBuffer; scratchBuffer += size*sizeof(float);
	float* backward = (float*)scratchBuffer; scratchBuffer += size*sizeof(float);

	//NOTE(martin): Initialize our first induction variables
	float inv = 1./acov[0];
	sigmaAndCoeffs[0] = backwardPrev[size-1] = inv;

	int lastB = size-1;

	//NOTE(martin): Loop to compute our induction variables until we reach the appropriate vector size
	for(unsigned int n = 2; n <= size; n++)
	{
		//NOTE(martin): Compute forward and backward vectors from previous versions

		int firstB = size - n;
		float eb = 0;

		for(unsigned int i=1; i<n; i++)
		{
			eb += acov[i] * backwardPrev[firstB+i];
		}

		float beta = 1./(1 - eb*eb);
		float alpha = -eb /(1 - eb*eb);

		for(unsigned int i=0; i<n; i++)
		{
			backward[firstB+i] = alpha * backwardPrev[lastB-i] + beta * backwardPrev[firstB+i];
		}

		#if 0
		float check[1024];

		for(int i=0; i<n; i++)
		{
			check[i] = 0;
			for(int j=0; j<n; j++)
			{
				unsigned int index = abs(i-j);
				check[i] += acov[index] * backward[firstB+j];
			}
		}
		printf("\ncb[%i] = ", n);
		double mse = 0;
		for(int i=0; i<n; i++)
		{
			double diff = (double)check[i] - ((i==n-1) ? 1 : 0);

			mse += diff*diff;
			printf("\t%.3f", check[i]);
		}
		printf("\nmse = %e\n", mse/n);
		printf("\n");
		printf("\n\n");

		#endif

		//NOTE(martin): Compute x error and update x accordingly

		float ex = 0;
		unsigned int lastT = n-1;
		for(unsigned int i=0; i<n-1; i++)
		{
			ex += acov[lastT-i] * sigmaAndCoeffs[i] ;
		}

		for(unsigned int i=0; i<n; i++)
		{
			sigmaAndCoeffs[i] = sigmaAndCoeffs[i] - ex * backward[firstB+i];
		}

		//NOTE(martin): swap previous and current forward/backward vectors

		float* tmp = backward;
		backward = backwardPrev;
		backwardPrev = tmp;
	}
	//NOTE(martin): get sigma and renormalize filter coefficients

	float sigma = 1./sigmaAndCoeffs[0];
	for(unsigned int i=1; i<size; i++)
	{
		sigmaAndCoeffs[i] = - sigma * sigmaAndCoeffs[i];
	}
	sigmaAndCoeffs[0] = sigma;
}

} // namespace otto::dsp;
