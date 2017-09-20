#define CATCH_CONFIG_RUNNER
#include "testing.t.hpp"

#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>

namespace fs = std::experimental::filesystem;

int main( int argc, char* argv[] )
{
  static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::info, (test::dir / "test-log.txt").c_str()).addAppender(&consoleAppender);

  if (fs::exists(test::dir)) {
    fs::remove_all(test::dir);
  }

  fs::create_directories(test::dir);

  int result = Catch::Session().run( argc, argv );

  // global clean-up...

  return ( result < 0xff ? result : 0xff );
}

