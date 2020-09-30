#include "app/services/config.hpp"
#include "testing.t.hpp"

#include <Gamma/Oscillator.h>

#include "app/services/audio.hpp"
#include "app/services/runtime.hpp"

using namespace otto;
using namespace otto::services;
using namespace std::literals;

TEST_CASE (test::interactive() * "audio_loopback") {
  auto app = start_app(ConfigManager::make_default(), Audio::make());
  app.service<Audio>().set_process_callback([](Audio::CallbackData data) { data.output = data.input; });
  app.wait_for_stop(10s);
}

TEST_CASE (test::interactive() * "audio_sine") {
  auto app = start_app(ConfigManager::make_default(), Audio::make());
  gam::Sine<> osc = {440};
  app.service<Audio>().set_process_callback([&](Audio::CallbackData data) {
    std::ranges::generate(data.output.left, osc);
    std::ranges::copy(data.output.left, data.output.right.begin());
  });
  app.wait_for_stop(10s);
}

TEST_CASE ("midi queue") {
  struct Handler : midi::MidiHandler {
    void handle(midi::NoteOn e) noexcept override
    {
      note += e.note;
    }
    int note = 0;
  } handler;

  auto app = start_app(ConfigManager::make_default(), Audio::make());
  app.service<Audio>().set_midi_handler(&handler);
  app.service<Audio>().enqueue_midi(midi::NoteOn{.channel = 0, .note = 5});
  app.service<Audio>().set_process_callback([&](Audio::CallbackData) {
    if (handler.note != 0) app.service<Runtime>().request_stop();
  });
  app.wait_for_stop(1s);
  REQUIRE(handler.note == 5);
}
