#include "acovb.hpp"
#DEFIN THRESHOLD 0.5

unsigned detect_pitch(gsl::span<float> data, unsigned minT, unsigned maxT){
  const unsigned N = data.size();
  auto gamma = data.copy();
  acovb(gamma);
  for (auto&& c : gamma) c /= gamma[0];

  gamma = gamma.subspan(minT, gamma.end());
  float max_gamma = *std::max_element(gamma.begin(), gamma.end());
  unsigned T = std::find(gamma.begin(), gamma.end(), max_gamma);

  if (gamma(T)*N/(N-T) < THRESHOLD || T > maxT){
    T = 0;
  }
  return T;
}
