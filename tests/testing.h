#pragma once

#include <catch.hpp>

#include <plog/Log.h>
#include <fmt/format.h>
#include <cstdlib>

namespace test {

// good for basic randomness
inline int rand(int min, int max) {
  return std::rand() % (max - min + 1) + min;
}

inline double fRand(double min, double max) {
  return (std::rand() / double(RAND_MAX)) * (max - min) + min;
}
}
