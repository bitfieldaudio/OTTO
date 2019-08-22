#pragma once

#include "Gamma/Gamma.h"
#include "Gamma/FFT.h"
using namespace gam;
#include <gsl/span>


void acovb(gsl::span<float> data){
    const int N = (int) data.size();
    const int M = 2*(N - 1); // FFT order

    // FFT is in-place and we need more space, so we first copy the data to a buffer, and zero-pad
    // TODO: not this
    static std::vector<float> buf = [M] () {
        std::vector<float> vec;
        std::fill_n(std::back_inserter(vec), M, 0);
        return vec;
    }();

    for(int i=0; i<N; ++i) buf[i] = data[i];
    for(int i=N; i<M; ++i) buf[i] = 0;

    // remove the mean
    const float mean = arr::mean(buf.data(), N);
    for (auto&& x : buf) x -= mean;

    // compute the periodogram
    RFFT<float> fft(M); // Real-to-complex FFT
    float invN = 1.0f / N;
  	int numBins = N;
    fft.forward(buf.data());
    // The complex sequence format for forward and inverse transforms is
    // [r0, r1, i1, ... , r(n/2-1), i(n/2-1), r(n/2)]
    // Transform each complex number c to its square norm over N, i.e. |c|²/N:
    for(int i=0; i<numBins; ++i){
    		if (0 == i){
          buf[0] = buf[0] * buf[0] * invN;
        }else if	(N-1 == i){
          buf[M-1] = buf[M-1] * buf[M-1] * invN;
        }
    		else{
          Complex<float> c;
          c(buf[i*2-1], buf[i*2]);
          buf[i*2-1] = c.normSqr() * invN;
        }
    }
    // do the ifft to get the autocovariance estimator
    fft.inverse(buf.data());

    // Crop the autocovariance estimator to the first N values, and copy to the output
    for(int i=0; i<N; ++i) data[i] = buf[i];
}
