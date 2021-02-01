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

int main(int argc, char* argv[])
{
  using namespace otto;
  fs::remove_all(test::dir);
  fs::create_directories(test::dir);
  logging::init();

  auto result = Catch::Session().run(argc, argv);

  // fs::remove_all(test::dir);

  return result;
}
