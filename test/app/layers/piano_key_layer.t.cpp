#include "testing.t.hpp"

#include "app/layers/piano_key_layer.hpp"

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

TEST_CASE ("PianoKeyLayer") {
  stubs::StubMidiHandler midi_handler;
  drivers::MidiDriver midi_driver;
  PianoKeyLayer piano = {midi_driver.controller()};
  midi_driver.set_handler(&midi_handler);
  SECTION ("Seq keys -> midi events") {
    piano.handle(KeyPress{Key::seq0});
    piano.handle(KeyPress{Key::seq1});
    piano.handle(KeyPress{Key::channel0});
    piano.handle(KeyPress{Key::seq2});
    piano.handle(KeyPress{Key::channel1});
    piano.handle(KeyPress{Key::seq3});
    piano.handle(KeyPress{Key::seq4});
    piano.handle(KeyPress{Key::channel2});
    piano.handle(KeyPress{Key::seq5});
    piano.handle(KeyPress{Key::channel3});
    piano.handle(KeyPress{Key::seq6});
    piano.handle(KeyPress{Key::channel4});
    piano.handle(KeyPress{Key::seq7});
    piano.handle(KeyPress{Key::seq8});
    piano.handle(KeyPress{Key::channel5});
    piano.handle(KeyPress{Key::seq9});
    piano.handle(KeyPress{Key::channel6});
    piano.handle(KeyPress{Key::seq10});
    piano.handle(KeyPress{Key::seq11});
    piano.handle(KeyPress{Key::channel7});
    piano.handle(KeyPress{Key::seq12});
    piano.handle(KeyPress{Key::channel8});
    piano.handle(KeyPress{Key::seq13});
    piano.handle(KeyPress{Key::channel9});
    piano.handle(KeyPress{Key::seq14});
    piano.handle(KeyPress{Key::seq15});
    piano.handle(KeyRelease{Key::seq0});
    midi_driver.process_events();
    REQUIRE(midi_handler.events == Events{
                                     midi::NoteOn{.note = 47, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 48, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 49, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 50, .velocity = 0x40, .channel = 0},
                                     midi::NoteOn{.note = 51, .velocity = 0x40, .channel = 0},
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
                                     midi::NoteOff{.note = 47, .velocity = 0x00, .channel = 0},
                                   });
  }

  // TODO: Octaves & press, change octave, release
  SECTION ("Octaves") {
    piano.handle(KeyPress{Key::plus});
    piano.handle(KeyRelease{Key::plus});
    piano.handle(KeyPress{Key::seq0});
    midi_driver.process_events();
    REQUIRE(midi_handler.events == Events{midi::NoteOn{.note = 47 + 12, .velocity = 0x40, .channel = 0}});
  }

  SECTION ("Release after switching octaves") {
    piano.handle(KeyPress{Key::seq0});
    piano.handle(KeyPress{Key::plus});
    piano.handle(KeyRelease{Key::plus});
    midi_driver.process_events();
    REQUIRE(midi_handler.events == Events{midi::NoteOn{.note = 47, .velocity = 0x40, .channel = 0}});
    piano.handle(KeyRelease{Key::seq0});
    midi_driver.process_events();
    REQUIRE(midi_handler.events == Events{midi::NoteOn{.note = 47, .velocity = 0x40, .channel = 0},
                                          midi::NoteOff{.note = 47, .velocity = 0x00, .channel = 0}});
  }
}
