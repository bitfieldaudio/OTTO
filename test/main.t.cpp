#define CATCH_CONFIG_RUNNER
#include "testing.t.hpp"
#include "util/filesystem.hpp"

int main( int argc, char* argv[] )
{
  using namespace otto;
  fs::remove_all(test::dir);
  fs::create_directories(test::dir);
  service::logger::init(argc, argv, true, (test::dir / "test-log.txt").c_str());

  int result = Catch::Session().run( argc, argv );

  fs::remove_all(test::dir);

  return ( result < 0xff ? result : 0xff );
}

