#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <valarray>

namespace otto::util::math {

  template<typename T>
  constexpr inline bool between(T el, T min, T max)
  {
    return (el <= max && el >= min);
  }

  inline float round(float f, int places)
  {
    int i = std::pow(10, places);
    return std::round(f * i) / i;
  }

  template<typename T>
  int sgn(T val)
  {
    return (T(0) < val) - (val < T(0));
  }

  /// Real modulo for negative `a` too
  template<typename T>
  constexpr inline T modulo(T a, T b)
  {
    const T result = std::fmod(a, b);
    return result >= 0 ? result : result + b;
  }

  /// Real modulo for negative `a` too
  inline int modulo(int i, int n)
  {
    return (i % n + n) % n;
  }

  /// Split a number into `N` values between 0 and 1, each representing a Nth
  /// part of the range `[min,max]`
  ///
  /// This is useful for UI especially, when you want to display a range of
  /// values by fading colours between N fixed points. See `draw_pitch` in
  /// `drum_sampler.cpp` for an example
  template<int N>
  constexpr std::array<float, N> split_values(float f, float min, float max)
  {
    std::array<float, N> res{{0}};
    // f scaled to [0, N]
    float f1 = (N - 1) * (f - min) / (max - min);
    for (int i = 0; i < N; i++) {
      res[i] = 1 - std::clamp(std::abs(i - f1), 0.f, 1.f);
    }
    return res;
  }

  inline double vox_fasttanh2(const double x)
  {
    const double ax = fabs(x);
    const double x2 = x * x;

    return (x * (2.45550750702956 + 2.45550750702956 * ax + (0.893229853513558 + 0.821226666969744 * ax) * x2) /
            (2.44506634652299 + (2.44506634652299 + x2) * fabs(x + 0.814642734961073 * x * ax)));
  }

  inline float fasttanh3(const float x)
  {
    const float x2 = x * x;
    const float ax = (((x2 + 378.f) * x2 + 17325.f) * x2 + 135135) * x;
    const float bx = ((28 * x2 + 3150.f) * x2 + 62370) * x2 + 135135;
    return ax / bx;
  }

  inline float fastatan( const float x)
  {
    const float a1 = (M_PI / 4.f) * x;
    const float a2 = 0.273f * x * (1.f - std::abs(x));
    return a1 + a2;
  }
}// namespace otto::util::math
