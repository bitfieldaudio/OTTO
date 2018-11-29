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
//	SolveToeplitz() is a (somewhat naive) implementation of the Levinson-Durbin algorithm for solving the Topelitz system Mx = y
//
//	arguments :
//		- size : the size of the Toeplitz matrix and of vectors x and y
//		- toeplitz : a buffer containing the first column of the matrix from bottom to top, then the first line from left to right.
//			     eg. if the matrix is :
//
//			     [T0 T1   ...  Tn-1]
//			     [T-1 T0  ...  Tn-2]
//			     [...              ]
//			     [T-n+1   ...    T0]
//
//			     you should pass the vector [T-n+1 T-n+2 ... T0 T1 ... Tn-1] of length (size+size-1)
//
//		- y : the vector at the right-hand side of the equation
//		- x : result vector (that is, the x unknown at the left-hand side of the equation)
//		- scratchBuffer : a block of memory used to hold intermediate computations. You must pass a buffer of size at least 4*size*sizeof(float).
//
//--------------------------------------------------------------------------

void SolveToeplitz(unsigned int size, const float* toeplitz, const float* y, float* x, char* scratchBuffer)
{
	//NOTE(martin): Clear and organize the scratch memory
	memset(x, 0, size*sizeof(float));
	memset(scratchBuffer, 0, 4*size*sizeof(float));

	float* forwardPrev  = (float*)scratchBuffer; scratchBuffer += size*sizeof(float);
	float* backwardPrev = (float*)scratchBuffer; scratchBuffer += size*sizeof(float);
	float* forward  = (float*)scratchBuffer; scratchBuffer += size*sizeof(float);
	float* backward = (float*)scratchBuffer; scratchBuffer += size*sizeof(float);

	//NOTE(martin): Initialize our first induction variables
	float inv = 1./toeplitz[size-1];
	forwardPrev[0] = backwardPrev[size-1] = inv;
	x[0] = y[0] * inv;

	//NOTE(martin): Loop to compute our induction variables until we reach the appropriate vector size
	for(unsigned int n = 2; n <= size; n++)
	{
		//NOTE(martin): Compute forward and backward vectors from previous versions

		int firstB = size - n;
		float ef = 0;
		float eb = 0;

		for(unsigned int i=0; i< n-1; i++)
		{
			ef += toeplitz[firstB+i] * forwardPrev[i];
			eb += toeplitz[size+i] * backwardPrev[firstB+i+1];
		}

		float alphaF = 1./(1 - ef*eb);
		float betaF = -ef*alphaF;
		float alphaB =  -eb*alphaF;
		float betaB = alphaF;

		for(unsigned int i=0; i<n; i++)
		{
			forward[i] = alphaF * forwardPrev[i] + betaF * backwardPrev[firstB+i];
			backward[firstB+i] = alphaB * forwardPrev[i] + betaB * backwardPrev[firstB+i];
		}

		//NOTE(martin): Compute x error and update x accordingly

		float ex = 0;
		for(unsigned int i=0; i<n-1; i++)
		{
			ex += toeplitz[firstB+i] * x[i] ;
		}

		for(unsigned int i=0; i<n; i++)
		{
			x[i] = x[i] + (y[n-1] - ex) * backward[firstB+i];
		}

		//NOTE(martin): swap previous and current forward/backward vectors

		float* tmp = forward;
		forward = forwardPrev;
		forwardPrev = tmp;

		tmp = backward;
		backward = backwardPrev;
		backwardPrev = tmp;
	}
}

} // namespace otto::dsp;
