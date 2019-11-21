#define CATCH_CONFIG_RUNNER
#include "testing.t.hpp"
#include "util/filesystem.hpp"

#include "core/audio/midi.hpp"

#include <Gamma/Domain.h>

int main( int argc, char* argv[] )
{
  using namespace otto;
  fs::remove_all(test::dir);
  fs::create_directories(test::dir);
  //service::logger::init(argc, argv, true, (test::dir / "test-log.txt").c_str());

  core::midi::generateFreqTable();

  int result = Catch::Session().run( argc, argv );

  fs::remove_all(test::dir);

  return ( result < 0xff ? result : 0xff );
}

