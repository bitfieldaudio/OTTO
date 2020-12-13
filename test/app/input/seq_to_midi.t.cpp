#include "testing.t.hpp"

#include "app/input/seq_to_midi.hpp"

#include "app/services/audio.hpp"
#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/runtime.hpp"
#include "app/services/ui_manager.hpp"

#include "stubs/audio.hpp"
#include "stubs/graphics.hpp"
#include "stubs/midi.hpp"

using namespace otto;
using namespace services;

using Events = std::vector<midi::IMidiHandler::variant>;

TEST_CASE ("KeyboardKeysHandler") {
  stubs::StubMidiHandler midi_handler;
  auto app = services::start_app(LogicThread::make(),   //
                                 ConfigManager::make(), //
                                 Audio::make(std::make_unique<stubs::DummyAudioDriver>));
  KeyboardKeysHandler handler;
  app.service<Audio>().set_midi_handler(&midi_handler);
  SECTION ("Seq keys -> midi events") {
    handler.handle(KeyPress{Key::seq0});
    handler.handle(KeyPress{Key::seq1});
    handler.handle(KeyPress{Key::channel0});
    handler.handle(KeyPress{Key::seq2});
    handler.handle(KeyPress{Key::channel1});
    handler.handle(KeyPress{Key::seq3});
    handler.handle(KeyPress{Key::seq4});
    handler.handle(KeyPress{Key::channel2});
    handler.handle(KeyPress{Key::seq5});
    handler.handle(KeyPress{Key::channel3});
    handler.handle(KeyPress{Key::seq6});
    handler.handle(KeyPress{Key::channel4});
    handler.handle(KeyPress{Key::seq7});
    handler.handle(KeyPress{Key::seq8});
    handler.handle(KeyPress{Key::channel5});
    handler.handle(KeyPress{Key::seq9});
    handler.handle(KeyPress{Key::channel6});
    handler.handle(KeyPress{Key::seq10});
    handler.handle(KeyPress{Key::seq11});
    handler.handle(KeyPress{Key::channel7});
    handler.handle(KeyPress{Key::seq12});
    handler.handle(KeyPress{Key::channel8});
    handler.handle(KeyPress{Key::seq13});
    handler.handle(KeyPress{Key::channel9});
    handler.handle(KeyPress{Key::seq14});
    handler.handle(KeyPress{Key::seq15});
    handler.handle(KeyRelease{Key::seq0});
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

    // TODO: Octaves & press, change octave, release
  }
}
