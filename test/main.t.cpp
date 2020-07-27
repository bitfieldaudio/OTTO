#include "testing.t.hpp"

#include <Gamma/Domain.h>
#include <iostream>
#include <filesystem>

#include "app/services/log_manager.hpp"

namespace fs = std::filesystem;

int main( int argc, char* argv[] )
{
  using namespace otto;
  using namespace otto::app;
  fs::remove_all(test::dir);
  fs::create_directories(test::dir);
  //service::logger::init(argc, argv, true, (test::dir / "test-log.txt").c_str());
  services::LogManager::init();

  doctest::Context context;

  context.applyCommandLine(argc, argv);

  int result = context.run();

  fs::remove_all(test::dir);

  return ( result < 0xff ? result : 0xff );
}

