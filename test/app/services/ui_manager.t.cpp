#include "testing.t.hpp"

#include "app/services/audio.hpp"
#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/runtime.hpp"
#include "app/services/ui_manager.hpp"

using namespace otto;
using namespace services;

struct DummyAudioDriver final : AudioDriver {
  DummyAudioDriver()
  {
    buffers_.resize(buffer_size() * 4);
  }
  void set_callback(Callback&& cb) override
  {
    callback_ = std::move(cb);
  }
  void start() override
  {
    thread_ = std::jthread([this] {
      auto input_buf = util::stereo_audio_buffer(
        util::audio_buffer(std::span(buffers_.data() + 0 * buffer_size(), buffer_size()), nullptr),
        util::audio_buffer(std::span(buffers_.data() + 1 * buffer_size(), buffer_size()), nullptr));
      auto output_buf = util::stereo_audio_buffer(
        util::audio_buffer(std::span(buffers_.data() + 2 * buffer_size(), buffer_size()), nullptr),
        util::audio_buffer(std::span(buffers_.data() + 3 * buffer_size(), buffer_size()), nullptr));
      CallbackData cbd = {
        .input = input_buf,
        .output = output_buf,
      };
      while (runtime->should_run()) {
        callback_(cbd);
        std::this_thread::sleep_for(chrono::nanoseconds((1ns / 1s) * buffer_size() / sample_rate()));
      }
    });
  }
  std::size_t buffer_size() const override
  {
    return 64;
  }
  std::size_t sample_rate() const override
  {
    return 44100;
  }

private:
  std::vector<float> buffers_;
  [[no_unique_address]] core::ServiceAccessor<Runtime> runtime;
  Callback callback_;
  std::jthread thread_;
};

struct StubMidiHandler : midi::MidiHandler {
  void handle(midi::NoteOn e) noexcept override
  {
    events.emplace_back(e);
  }
  void handle(midi::NoteOff e) noexcept override
  {
    events.emplace_back(e);
  }
  std::vector<variant> events;
};

using Events = std::vector<midi::IMidiHandler::variant>;

TEST_CASE ("UIManager") {
  drivers::LocalMCUPort port;
  StubMidiHandler midi_handler;
  auto app =
    services::start_app(LogicThread::make(), ConfigManager::make(), Controller::make([&port] { return &port; }),
                        Audio::make(std::make_unique<DummyAudioDriver>), UIManager::make());
  app.service<Audio>().set_midi_handler(&midi_handler);
  SUBCASE ("Seq keys -> midi events") {
    port.handle(KeyPress{Key::seq0});
    port.handle(KeyPress{Key::seq1});
    port.handle(KeyPress{Key::channel0});
    port.handle(KeyPress{Key::seq2});
    port.handle(KeyPress{Key::channel1});
    port.handle(KeyPress{Key::seq3});
    port.handle(KeyPress{Key::seq4});
    port.handle(KeyPress{Key::channel2});
    port.handle(KeyPress{Key::seq5});
    port.handle(KeyPress{Key::channel3});
    port.handle(KeyPress{Key::seq6});
    port.handle(KeyPress{Key::channel4});
    port.handle(KeyPress{Key::seq7});
    port.handle(KeyPress{Key::seq8});
    port.handle(KeyPress{Key::channel5});
    port.handle(KeyPress{Key::seq9});
    port.handle(KeyPress{Key::channel6});
    port.handle(KeyPress{Key::seq10});
    port.handle(KeyPress{Key::seq11});
    port.handle(KeyPress{Key::channel7});
    port.handle(KeyPress{Key::seq12});
    port.handle(KeyPress{Key::channel8});
    port.handle(KeyPress{Key::seq13});
    port.handle(KeyPress{Key::channel9});
    port.handle(KeyPress{Key::seq14});
    port.handle(KeyPress{Key::seq15});
    port.handle(KeyRelease{Key::seq0});
    // No sync function for controller thread, sleep instead
    std::this_thread::sleep_for(5ms);
    app.service<Audio>().sync();
    app.service<LogicThread>().sync();
    REQUIRE(midi_handler.events == Events{
                                     midi::NoteOn{.note = 52, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 53, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 54, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 55, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 56, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 57, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 58, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 59, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 60, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 61, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 62, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 63, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 64, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 65, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 66, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 67, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 68, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 69, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 70, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 71, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 72, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 73, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 74, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 75, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 76, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 77, .velocity = 0x40, .channel = 0},
                                     midi::NoteOff{.note = 52, .velocity = 0x00, .channel = 0},
                                   });
  }
}
