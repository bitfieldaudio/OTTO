#include "piano_key_layer.hpp"

namespace otto {
  constexpr std::array<Key, 26> piano_keys{{
    Key::seq0,     Key::seq1,  Key::channel0, Key::seq2,  Key::channel1, Key::seq3,     Key::seq4,
    Key::channel2, Key::seq5,  Key::channel3, Key::seq6,  Key::channel4, Key::seq7,     Key::seq8,
    Key::channel5, Key::seq9,  Key::channel6, Key::seq10, Key::seq11,    Key::channel7, Key::seq12,
    Key::channel8, Key::seq13, Key::channel9, Key::seq14, Key::seq15,
  }};

  constexpr std::array<LEDColor, 4> octave_colors = {{
    led_colors::blue,
    led_colors::green,
    led_colors::yellow,
    led_colors::red,
  }};

  namespace {
    constexpr int note_of(Key k, int octave = 0) noexcept
    {
      auto base = [&]() constexpr
      {
        int idx = static_cast<int>(stdr::find(piano_keys, k) - piano_keys.begin());
        if (idx > 26) return -1000;
        return 47 + idx;
      }
      ();
      return base + octave * 12;
    }

    constexpr std::pair<Key, int> key_and_octave_of(int note, int octave) noexcept
    {
      return {piano_keys[(note - (47 + octave * 12)) % 27], 0};
    }

  } // namespace

  void PianoKeyLayer::handle(KeyPress e) noexcept
  {
    if (e.key == Key::plus) {
      state_.octave++;
    } else if (e.key == Key::minus) {
      state_.octave--;
    } else if (int note = note_of(e.key, state_.octave); note > 0 && note < 128) {
      midi_.send_event(midi::NoteOn{.note = note, .velocity = 0x40, .channel = 0});
    }
  }
  void PianoKeyLayer::handle(KeyRelease e) noexcept
  {
    if (int note = note_of(e.key, state_.octave); note > 0 && note < 128) {
      midi_.send_event(midi::NoteOff{.note = note, .velocity = 0x00, .channel = 0});
    }
  }
  void PianoKeyLayer::leds(LEDColorSet& output) noexcept
  {
    for (int i = 0; i < 128; i++) {
      auto [k, oct] = key_and_octave_of(i, state_.octave);
      Led led = *led_from(k);
      if (midi_.key_states()[i]) {
        output[led] = led_colors::white;
      }
    }
    output[Led::plus] = led_colors::inactive;
    output[Led::minus] = led_colors::inactive;

    if (state_.octave > 0) {
      output[Led::plus] = octave_colors[state_.octave - 1];
    } else if (state_.octave < 0) {
      output[Led::minus] = octave_colors[-state_.octave - 1];
    }
  }
} // namespace otto
