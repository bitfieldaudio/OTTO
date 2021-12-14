#include "testing.t.hpp"

#include <filesystem>
#include <iostream>

#include <Gamma/Domain.h>
#include <catch2/catch_session.hpp>
#include <catch2/internal/catch_compiler_capabilities.hpp>
#include <catch2/internal/catch_leak_detector.hpp>
#include <catch2/internal/catch_platform.hpp>

#include "lib/logging.hpp"

namespace Catch {
  CATCH_INTERNAL_START_WARNINGS_SUPPRESSION
  CATCH_INTERNAL_SUPPRESS_GLOBALS_WARNINGS
  LeakDetector leakDetector; // NOLINT
  CATCH_INTERNAL_STOP_WARNINGS_SUPPRESSION
} // namespace Catch

namespace {
  fs::path dir; // NOLINT
}

namespace otto::test {
  fs::path temp_file(std::string_view name)
  {
    auto path = dir / name;
    fs::remove_all(path);
    return path;
  }
} // namespace otto::test


int main(int argc, char* argv[])
{
  using namespace otto;
  try {
    dir = fs::temp_directory_path() / "otto-tests";
  } catch (std::filesystem::filesystem_error& e) {
    dir = "/tmp/otto-tests";
  }
  fs::remove_all(dir);
  fs::create_directories(dir);
  log::init();
  log::set_level(log::level::trace);

  auto result = Catch::Session().run(argc, argv);

  // fs::remove_all(test::dir);

  return result;
}
