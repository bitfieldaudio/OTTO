#include "testing.t.hpp"

#include "dummy_services.hpp"

#include "engines/fx/chorus/chorus.hpp"
#include "engines/fx/wormhole/wormhole.hpp"

namespace otto::services::test {

  using namespace otto::engines;

  TEST_CASE ("Application benchmarks") {
    auto app = make_dummy_application_default_engines();

    app.engine_manager->start();
    app.audio_manager->start();

    SECTION ("AudioManager::process()") {
      DummyAudioManager::current().set_bs_sr(16, 44100);
      BENCHMARK("AudioManager::process, bs = 16")
      {
        return DummyAudioManager::current().process();
      };

      DummyAudioManager::current().set_bs_sr(256, 44100);
      BENCHMARK("AudioManager::process, bs = 256")
      {
        return DummyAudioManager::current().process();
      };

      DummyAudioManager::current().set_bs_sr(1024, 44100);
      BENCHMARK("AudioManager::process, bs = 1024")
      {
        return DummyAudioManager::current().process();
      };
    }
  }

  TEST_CASE ("Engine benchmarks") {
    auto app = make_dummy_application();
    app.engine_manager->start();
    app.audio_manager->start();

    SECTION ("Wormhole") {
      Wormhole wormhole;
      auto buf = AudioManager::current().buffer_pool().allocate();
      BENCHMARK("Wormhole::process")
      {
        return wormhole.process({buf});
      };
    }

    SECTION ("Chorus") {
      Chorus chorus;
      auto buf = AudioManager::current().buffer_pool().allocate();
      BENCHMARK("Chorus::process")
      {
        return chorus.process({buf});
      };
    }
  }

} // namespace otto::services::test
