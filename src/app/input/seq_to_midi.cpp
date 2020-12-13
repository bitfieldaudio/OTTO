#include "seq_to_midi.hpp"

namespace otto {
  namespace {
    constexpr int note_of(Key k, int octave = 0) noexcept
    {
      auto base = [&] {
        switch (k) {
          case Key::seq0: return 52;
          case Key::seq1: return 53;
          case Key::channel0: return 54;
          case Key::seq2: return 55;
          case Key::channel1: return 56;
          case Key::seq3: return 57;
          case Key::seq4: return 58;
          case Key::channel2: return 59;
          case Key::seq5: return 60;
          case Key::channel3: return 61;
          case Key::seq6: return 62;
          case Key::channel4: return 63;
          case Key::seq7: return 64;
          case Key::seq8: return 65;
          case Key::channel5: return 66;
          case Key::seq9: return 67;
          case Key::channel6: return 68;
          case Key::seq10: return 69;
          case Key::seq11: return 70;
          case Key::channel7: return 71;
          case Key::seq12: return 72;
          case Key::channel8: return 73;
          case Key::seq13: return 74;
          case Key::channel9: return 75;
          case Key::seq14: return 76;
          case Key::seq15: return 77;
          default: return -1;
        }
      }();
      return base + octave * 12;
    }

  } // namespace

  void KeyboardKeysHandler::handle(KeyPress e) noexcept
  {
    if (int note = note_of(e.key, state_->octave); note > 0 && note < 256) {
      service<services::Audio>().enqueue_midi(midi::NoteOn{.note = note, .velocity = 0x40, .channel = 0});
    }
  }
  void KeyboardKeysHandler::handle(KeyRelease e) noexcept
  {
    if (int note = note_of(e.key, state_->octave); note > 0 && note < 256) {
      service<services::Audio>().enqueue_midi(midi::NoteOff{.note = note, .velocity = 0x00, .channel = 0});
    }
  }
} // namespace otto
