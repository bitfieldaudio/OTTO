#include "dummy_services.hpp"
#include "engines/synths/OTTOFM/audio.hpp"
#include "testing.t.hpp"

namespace otto::engines::ottofm {

  using namespace services;

  TEST_CASE ("[.benchmarks] FM Benchmarks") {
    std::array<itc::Shared<float>::Storage, 4> activities;
    Audio audio{{
      activities[0],
      activities[1],
      activities[2],
      activities[3],
    }};
    Voice& v = audio.voice_mgr_.voices()[0];
    auto app = test::make_dummy_application();
    audio.voice_mgr_.handle_midi(midi::NoteOnEvent(60));
    auto buf = AudioManager::current().buffer_pool().allocate_clear();

    // TODO: BENCHMARK ("Voice operator() inner switch lambda") {
    // TODO:   v.process({buf});
    // TODO: };
  }

} // namespace otto::engines::ottofm
