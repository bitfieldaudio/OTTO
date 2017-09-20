#pragma once

#include <cmath>

namespace top1::math {

  template<typename T>
  constexpr inline bool between(T min, T max, T el) {
    return (el <= max && el >= min);
  }

  constexpr inline float round(float f, int places) {
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

}
