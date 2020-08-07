#include "testing.t.hpp"

#include <Gamma/Domain.h>
#include <filesystem>
#include <iostream>

#include "lib/logging.hpp"

// namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
  using namespace otto;
  // fs::remove_all(test::dir);
  // fs::create_directories(test::dir);
  logging::init();

  doctest::Context context;

  context.applyCommandLine(argc, argv);

  int result = context.run();

  // fs::remove_all(test::dir);

  return (result < 0xff ? result : 0xff);
}
