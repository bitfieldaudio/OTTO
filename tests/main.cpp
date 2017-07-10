#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>

int main( int argc, char* argv[] )
{
  static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::debug, "test-log.txt").addAppender(&consoleAppender);

  int result = Catch::Session().run( argc, argv );

  // global clean-up...

  return ( result < 0xff ? result : 0xff );
}

