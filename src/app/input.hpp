#pragma once

#include <fmt/format.h>
#include <bitset>
#include <compare>
#include <cstdint>

#include "lib/util/enum.hpp"

#include "lib/itc/reducer.hpp"

namespace otto {

  enum struct Key : std::uint8_t {
    channel0 = 1,
    channel1 = 2,
    channel2 = 3,
    channel3 = 4,
    channel4 = 5,
    channel5 = 6,
    channel6 = 7,
    channel7 = 8,
    channel8 = 9,
    channel9 = 10,
    seq0 = 11,
    seq1 = 12,
    seq2 = 13,
    seq3 = 14,
    seq4 = 15,
    seq5 = 16,
    seq6 = 17,
    seq7 = 18,
    seq8 = 19,
    seq9 = 20,
    seq10 = 21,
    seq11 = 22,
    seq12 = 23,
    seq13 = 24,
    seq14 = 25,
    seq15 = 26,
    blue_enc_click = 27,
    green_enc_click = 28,
    yellow_enc_click = 29,
    red_enc_click = 30,
    shift = 31,
    sends = 32,
    plus = 33,
    routing = 34,
    minus = 35,
    fx1 = 36,
    fx2 = 37,
    master = 38,
    play = 39,
    record = 40,
    arp = 41,
    slots = 42,
    twist1 = 43,
    twist2 = 44,
    looper = 45,
    external = 46,
    sampler = 47,
    envelope = 48,
    voices = 49,
    settings = 50,
    sequencer = 51,
    synth = 52,
    unassigned_a = 53,
    unassigned_b = 54,
    unassigned_c = 55,
    unassigned_d = 56,
    unassigned_e = 57,
    unassigned_f = 58,
  };

  struct KeyEvent {
    Key key = {};
    auto operator<=>(const KeyEvent&) const = default;
  };

  struct KeyPress : KeyEvent {
    auto operator<=>(const KeyPress&) const = default;
  };
  struct KeyRelease : KeyEvent {
    auto operator<=>(const KeyRelease&) const = default;
  };

  enum struct Encoder : std::uint8_t {
    blue,
    green,
    yellow,
    red,
  };

  struct EncoderEvent {
    Encoder encoder = {};
    int steps = 0;
    auto operator<=>(const EncoderEvent&) const = default;
  };

  using InputHandler = itc::IEventHandler<KeyPress, KeyRelease, EncoderEvent>;


  inline std::ostream& operator<<(std::ostream& os, const KeyPress& k)
  {
    return os << fmt::format("KeyPress({})", util::enum_name(k.key));
  }

  inline std::ostream& operator<<(std::ostream& os, const KeyRelease& k)
  {
    return os << fmt::format("KeyRelease({})", util::enum_name(k.key));
  }

  inline std::ostream& operator<<(std::ostream& os, const EncoderEvent& e)
  {
    return os << fmt::format("EncoderEvent({}, {})", util::enum_name(e.encoder), e.steps);
  }

} // namespace otto
