#pragma once

#include <cmath>
#include <array>
#include <algorithm>

namespace otto::util::math {

  template<typename T>
  constexpr inline bool between(T min, T max, T el) {
    return (el <= max && el >= min);
  }

  inline float round(float f, int places) {
    int i = std::pow(10, places);
    return std::round(f * i)/i;
  }

  /// Real modulo for negative `a` too
  template<typename T>
  constexpr inline T modulo(T a, T b) {
    const T result = std::fmod(a, b);
    return result >= 0 ? result : result + b;
  }

  struct vec {
    const float x, y;

    constexpr vec() : vec(0, 0) {}
    constexpr vec(float x, float y) : x (x), y (y) {}

    vec rotate(float angle) const {
      float s = std::sin(angle);
      float c = std::cos(angle);

      float nx = x * c - y * s;
      float ny = x * s + y * c;

      return {nx, ny};
    }

    float angle() const {
      return std::atan(y/x);
    }

    float len() const {return std::sqrt(x * x + y * y);}
    constexpr float dir() const {return y / x;}

    constexpr vec hat() const {return {-y, x};}

    constexpr vec swapXY() const {return {y, x};}
    constexpr vec flipSignX() const {return {-x, y};}
    constexpr vec flipSignY() const {return {x, -y};}

    constexpr bool operator==(const vec& r) const {return x == r.x && y == r.y;}
    constexpr bool operator!=(const vec& r) const {return x != r.x && y != r.y;}
    constexpr vec operator-(const vec& r) const {return {x - r.x, y - r.y};}
    constexpr vec operator+(const vec& r) const {return {x + r.x, y + r.y};}
    constexpr vec operator*(float s) const {return {x * s, y * s};}
    constexpr vec operator/(float s) const {return {x / s, y / s};}
    constexpr vec operator-() const {return {-x, -y};}

    // Factory methods
    static vec angleAndLen(float a, float l) {
      return vec(std::cos(a), std::sin(a)) * l;
    }
  };

  /// Split a number into `N` values between 0 and 1, each representing a Nth
  /// part of the range `[min,max]`
  ///
  /// This is useful for UI especially, when you want to display a range of
  /// values by fading colours between N fixed points. See `draw_pitch` in
  /// `drum_sampler.cpp` for an example
  template<int N>
  constexpr std::array<float, N> split_values(float f, float min, float max)
  {
    std::array<float, N> res {{0}};
    // f scaled to [0, N]
    float f1 = (N - 1) * (f - min) / (max - min);
    for (int i = 0; i < N; i++) {
      res[i] = 1 - std::clamp(std::abs(i - f1), 0.f, 1.f);
    }
    return res;
  }

}
