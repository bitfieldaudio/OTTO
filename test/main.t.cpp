#define CATCH_CONFIG_RUNNER
#include "testing.t.hpp"
#include "filesystem.hpp"
#include "util/logger.hpp"

int main( int argc, char* argv[] )
{
  using namespace otto;
  fs::remove_all(test::dir);
  fs::create_directories(test::dir);
  util::logger::init(argc, argv, false, (test::dir / "test-log.txt").c_str());

  int result = Catch::Session().run( argc, argv );

  fs::remove_all(test::dir);

  return ( result < 0xff ? result : 0xff );
}

