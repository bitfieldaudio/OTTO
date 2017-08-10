#pragma once

#include <cmath>

namespace top1 {

struct vec {
  const float x, y;

  vec() : vec(0, 0) {}
  vec(float x, float y) : x (x), y (y) {}

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
  float dir() const {return y / x;}

  vec hat() const {return {-y, x};}

  vec swapXY() const {return {y, x};}
  vec flipSignX() const {return {-x, y};}
  vec flipSignY() const {return {x, -y};}

  bool operator==(const vec& r) const {return x == r.x && y == r.y;}
  bool operator!=(const vec& r) const {return x != r.x && y != r.y;}
  vec operator-(const vec& r) const {return {x - r.x, y - r.y};}
  vec operator+(const vec& r) const {return {x + r.x, y + r.y};}
  vec operator*(float s) const {return {x * s, y * s};}
  vec operator/(float s) const {return {x / s, y / s};}
  vec operator-() const {return {-x, -y};}

  // Factory methods
  static vec angleAndLen(float a, float l) {
    return vec(std::cos(a), std::sin(a)) * l;
  }
};

}
