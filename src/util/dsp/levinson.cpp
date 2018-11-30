//**************************************************************************
//
//	$file: main.c $
//	$author: Martin Fouilleul $
//	$date: 28/11/2018 $
//	$description: a simple Toeplitz system solver$
//
//**************************************************************************

#include<string.h> // memset()

namespace otto::dsp
{
//--------------------------------------------------------------------------
//
//	SolveSymmetricalToeplitz() is a simple implementation of the Levinson-Durbin algorithm for solving the Topelitz system Mx = y where M is symmetrical
//
//	arguments :
//		- size : the size of the Toeplitz matrix and of vectors x and y
//		- toeplitz : a buffer containing the first line of the symmetrical matrix.
//			     eg. if the matrix is :
//
//			     [T0 T1  ...   Tn-1]
//			     [T1 T0  ...   Tn-2]
//			     [...              ]
//			     [Tn-1   ...     T0]
//
//			     you should pass the vector [T0 T1 ... Tn-1] of length (size)
//
//		- y : the vector at the right-hand side of the equation, of length (size)
//		- x : result vector (that is, the x unknown at the left-hand side of the equation) of length (size)
//		- scratchBuffer : a block of memory used to hold intermediate computations. You must pass a buffer of size at least (2 * size * sizeof(float)).
//
//--------------------------------------------------------------------------

void SolveSymmetricalToeplitz(unsigned int size, const float* toeplitz, const float* y, float* x, char* scratchBuffer)
{
	//NOTE(martin): Clear and organize the scratch memory
	memset(x, 0, size*sizeof(float));
	memset(scratchBuffer, 0, 2*size*sizeof(float));

	float* backwardPrev = (float*)scratchBuffer; scratchBuffer += size*sizeof(float);
	float* backward = (float*)scratchBuffer; scratchBuffer += size*sizeof(float);

	//NOTE(martin): Initialize our first induction variables
	float inv = 1./toeplitz[0];
	backwardPrev[size-1] = inv;
	x[0] = y[0] * inv;

	int lastB = size-1;

	//NOTE(martin): Loop to compute our induction variables until we reach the appropriate vector size
	for(unsigned int n = 2; n <= size; n++)
	{
		//NOTE(martin): Compute forward and backward vectors from previous versions

		int firstB = size - n;
		float eb = 0;

		for(unsigned int i=1; i<n; i++)
		{
			eb += toeplitz[i] * backwardPrev[firstB+i];
		}

		float betaB = 1./(1 - eb*eb);
		float alphaB = -eb /(1 - eb*eb);

		for(unsigned int i=0; i<n; i++)
		{
			backward[firstB+i] = alphaB * backwardPrev[lastB-i] + betaB * backwardPrev[firstB+i];
		}

		//NOTE(martin): Compute x error and update x accordingly

		float ex = 0;
		unsigned int lastT = n-1;
		for(unsigned int i=0; i<n-1; i++)
		{
			ex += toeplitz[lastT-i] * x[i] ;
		}

		for(unsigned int i=0; i<n; i++)
		{
			x[i] = x[i] + (y[n-1] - ex) * backward[firstB+i];
		}

		//NOTE(martin): swap previous and current forward/backward vectors

		float* tmp = backward;
		backward = backwardPrev;
		backwardPrev = tmp;
	}
}

} // namespace otto::dsp;
