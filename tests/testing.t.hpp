#pragma once

#include <catch.hpp>

#include <plog/Log.h>
#include <fmt/format.h>
#include <random.hpp>
#include <fstream>
#include <filesystem.hpp>

using Random = effolkronium::random_static;
namespace fs = filesystem;

namespace test {

  inline fs::path dir = fs::current_path() / "testdir";

  inline void truncateFile(const filesystem::path& p) {
    std::fstream fstream;
    fstream.open(p, std::ios::trunc | std::ios::out | std::ios::binary);
    fstream.close();
  }

}
