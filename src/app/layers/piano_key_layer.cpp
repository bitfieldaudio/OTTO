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
    constexpr tl::optional<int> index_of(Key k)
    {
      const auto* found = stdr::find(piano_keys, k);
      if (found == piano_keys.end()) return tl::nullopt;
      return found - piano_keys.begin();
    }

    constexpr tl::optional<int> note_of(Key k, int octave = 0) noexcept
    {
      return index_of(k)                                  //
        .map([&](int i) { return 47 + i + octave * 12; }) //
        .and_then([](int i) -> tl::optional<int> {
          if (i < 128 && i > 0) return i;
          return tl::nullopt;
        });
    }

    constexpr std::pair<Key, int> key_and_octave_of(int note, int octave) noexcept
    {
      return {piano_keys[math::modulo(note - (47 + octave * 12), 26)], 0};
    }

  } // namespace

  void PianoKeyLayer::handle(KeyPress e) noexcept
  {
    if (e.key == Key::plus) {
      state_.octave++;
    } else if (e.key == Key::minus) {
      state_.octave--;
    } else if (auto note = note_of(e.key, state_.octave)) {
      key_notes_[index_of(e.key).value()] = *note;
      midi_.send_event(midi::NoteOn{.note = static_cast<uint8_t>(*note), .velocity = 0x40, .channel = 0});
    }
  }
  void PianoKeyLayer::handle(KeyRelease e) noexcept
  {
    if (auto idx = index_of(e.key)) {
      midi_.send_event(midi::NoteOff{.note = key_notes_[*idx], .velocity = 0x00, .channel = 0});
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
