#pragma once

#include <catch.hpp>

#include <plog/Log.h>
#include <fmt/format.h>
#include <random.hpp>
#include <fstream>

#include <filesystem/path.h>

using Random = effolkronium::random_static;

namespace test {

  inline void truncateFile(const filesystem::path& p) {
    std::fstream fstream;
    fstream.open(p.str(), std::ios::trunc | std::ios::out | std::ios::binary);
    fstream.close();
  }

}
