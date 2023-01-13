#include "testing.t.hpp"

#include "app/services/audio.hpp"

#include <Gamma/Oscillator.h>

#include "app/application.hpp"
#include "app/services/config.hpp"
#include "app/services/runtime.hpp"

using namespace otto;
using namespace otto::services;
using namespace std::literals;

TEST_CASE ("audio_loopback", "[.interactive]") {
  RuntimeController rt;
  ConfigManager confman;
  Audio audio(drivers::IAudioDriver::make_default(confman));
  auto stop = audio.set_process_callback([](Audio::CallbackData data) { data.output = data.input; });
  rt.wait_for_stop(10s);
}

TEST_CASE ("audio_sine", "[.interactive]") {
  RuntimeController rt;
  ConfigManager confman;
  Audio audio(drivers::IAudioDriver::make_default(confman));
  gam::Sine<> osc = {440};
  auto stop = audio.set_process_callback([&](Audio::CallbackData data) {
    std::ranges::generate(data.output.left, std::ref(osc));
    std::ranges::copy(data.output.left, data.output.right.begin());
  });
  rt.wait_for_stop(10s);
}

TEST_CASE ("midi queue") {
  struct Handler : midi::MidiHandler {
    void handle(midi::NoteOn e) noexcept override
    {
      note += e.note;
    }
    int note = 0;
  } handler;

  {
    RuntimeController rt;
    ConfigManager confman;
    Audio audio(drivers::IAudioDriver::make_default(confman));
    auto stop_midi = audio.set_midi_handler(&handler);
    audio.midi().send_event(midi::NoteOn{5});
    auto stop_process = audio.set_process_callback([&](Audio::CallbackData) {
      if (handler.note != 0) rt.request_stop();
    });
    rt.wait_for_stop(1s);
  }
  REQUIRE(handler.note == 5);
}
