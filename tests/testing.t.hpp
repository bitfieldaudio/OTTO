#pragma once

#include <catch.hpp>

#include <plog/Log.h>
#include <fmt/format.h>
#include <cstdlib>
#include <fstream>

#include <filesystem/path.h>

namespace test {

  // good for basic randomness
  inline int rand(int min, int max) {
    return std::rand() % (max - min + 1) + min;
  }

  inline double fRand(double min, double max) {
    return (std::rand() / double(RAND_MAX)) * (max - min) + min;
  }

  inline void truncateFile(const filesystem::path& p) {
    std::fstream fstream;
    fstream.open(p.str(), std::ios::trunc | std::ios::out | std::ios::binary);
    fstream.close();
  }

}
