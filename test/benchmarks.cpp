#include "testing.t.hpp"

#include "dummy_services.hpp"

#include "engines/fx/chorus/chorus.hpp"
#include "engines/fx/wormhole/wormhole.hpp"
#include "engines/synths/OTTOFM/ottofm.hpp"

#include "benchmark_csv_reporter.hpp"

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

  template<typename Engine>
  void benchmark_fx(std::string name = "", int runs = 1)
  {
    Engine engine;
    auto buf = AudioManager::current().buffer_pool().allocate();
    BENCHMARK_ADVANCED(std::string(Engine::name) + "::process " + name)(Catch::Benchmark::Chronometer meter)
    {
      meter.divisor(buf.size() / runs);
      meter.measure([&] {
        for (int i = 0; i < runs; i++) engine.process({buf});
      });
    };
  }

  template<typename Engine>
  void benchmark_fx_pr_bs()
  {
    SECTION (std::string(Engine::name) + " at different buffer sizes") {
      DummyAudioManager::current().set_bs_sr(1, 44100);
      benchmark_fx<Engine>("buffer_size = 1");
      DummyAudioManager::current().set_bs_sr(2, 44100);
      benchmark_fx<Engine>("buffer_size = 2");
      DummyAudioManager::current().set_bs_sr(4, 44100);
      benchmark_fx<Engine>("buffer_size = 4");
      DummyAudioManager::current().set_bs_sr(8, 44100);
      benchmark_fx<Engine>("buffer_size = 8");
      DummyAudioManager::current().set_bs_sr(16, 44100);
      benchmark_fx<Engine>("buffer_size = 16");
      DummyAudioManager::current().set_bs_sr(32, 44100);
      benchmark_fx<Engine>("buffer_size = 32");
      DummyAudioManager::current().set_bs_sr(64, 44100);
      benchmark_fx<Engine>("buffer_size = 64");
      DummyAudioManager::current().set_bs_sr(128, 44100);
      benchmark_fx<Engine>("buffer_size = 128");
      DummyAudioManager::current().set_bs_sr(256, 44100);
      benchmark_fx<Engine>("buffer_size = 256");
      DummyAudioManager::current().set_bs_sr(1024, 44100);
      benchmark_fx<Engine>("buffer_size = 1024");
    }
  }

  TEST_CASE ("Engine benchmarks") {
    auto app = make_dummy_application();
    app.engine_manager->start();
    app.audio_manager->start();

    WARN("Benchmark times are per sample");
    benchmark_fx_pr_bs<Wormhole>();
    benchmark_fx_pr_bs<Chorus>();

    SECTION("Parameter changes") {

    }
  }
} // namespace otto::services::test
