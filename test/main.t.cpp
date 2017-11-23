#define CATCH_CONFIG_RUNNER
#include "testing.t.hpp"

#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>

int main( int argc, char* argv[] )
{
  using namespace otto;
  static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::info, (test::dir / "test-log.txt").c_str()).addAppender(&consoleAppender);

  fs::remove_all(test::dir);
  fs::create_directories(test::dir);

  int result = Catch::Session().run( argc, argv );

  fs::remove_all(test::dir);

  return ( result < 0xff ? result : 0xff );
}

