#pragma once

#include <tl/optional.hpp>
#include "core/input.hpp"

namespace otto::board::controller {

  using otto::core::input::Key;

  struct LEDMap {
    std::uint8_t string;
    std::uint8_t num;
  };

  template<int Rows, int Cols>
  using KeyMatrix = std::array<std::array<tl::optional<Key>, Cols>, Rows>;
  using LedSequence = util::enum_map<Key, LEDMap>;

  struct Proto1MCUHardwareMap {
    static constexpr auto n_rows = 8;
    static constexpr auto n_cols = 7;

    static constexpr KeyMatrix<n_rows, n_cols> keyCodes = {{
      {Key::C0, Key::C3, Key::C7, Key::shift, Key::sends, tl::nullopt, Key::blue_click},
      {Key::S1, Key::S6, Key::S11, Key::plus, Key::routing, Key::rec, Key::yellow_click},
      {Key::S2, Key::S7, Key::S12, Key::minus, Key::fx2, Key::master, tl::nullopt},
      {Key::C1, Key::C4, Key::C8, Key::S0, Key::fx1, Key::play, Key::red_click},
      {Key::S3, Key::S8, Key::S13, Key::S15, Key::arp, Key::slots, tl::nullopt},
      {Key::S4, Key::S9, Key::S14, Key::twist2, Key::looper, Key::twist1, tl::nullopt},
      {Key::C2, Key::C5, Key::C9, Key::external, Key::sampler, Key::envelope, Key::green_click},
      {Key::S5, Key::C6, Key::S10, Key::settings, Key::sequencer, Key::synth, tl::nullopt},
    }};

    static constexpr LedSequence led_map = {{
      {Key::C0, {1, 0}},
      {Key::C3, {1, 3}},
      {Key::C7, {1, 7}},
      {Key::shift, {0, 2}},
      {Key::sends, {0, 3}},
      {Key::blue_click, {0, 25}},
      {Key::S1, {2, 1}},
      {Key::S6, {2, 6}},
      {Key::S11, {2, 11}},
      {Key::plus, {0, 1}},
      {Key::routing, {0, 10}},
      {Key::rec, {0, 11}},
      {Key::yellow_click, {0, 25}},
      {Key::S2, {2, 2}},
      {Key::S7, {2, 7}},
      {Key::S12, {2, 12}},
      {Key::minus, {0, 0}},
      {Key::fx2, {0, 9}},
      {Key::master, {0, 13}},
      {Key::C1, {1, 1}},
      {Key::C4, {1, 4}},
      {Key::C8, {1, 8}},
      {Key::S0, {2, 0}},
      {Key::fx1, {0, 4}},
      {Key::play, {0, 12}},
      {Key::red_click, {0, 25}},
      {Key::S3, {2, 3}},
      {Key::S8, {2, 8}},
      {Key::S13, {2, 13}},
      {Key::S15, {2, 15}},
      {Key::arp, {0, 8}},
      {Key::slots, {0, 14}},
      {Key::S4, {2, 4}},
      {Key::S9, {2, 9}},
      {Key::S14, {2, 14}},
      {Key::twist2, {0, 16}},
      {Key::looper, {0, 5}},
      {Key::twist1, {0, 15}},
      {Key::C2, {1, 2}},
      {Key::C5, {1, 5}},
      {Key::C9, {1, 9}},
      {Key::external, {0, 17}},
      {Key::sampler, {0, 7}},
      {Key::envelope, {0, 18}},
      {Key::green_click, {0, 25}},
      {Key::S5, {2, 5}},
      {Key::C6, {1, 6}},
      {Key::S10, {2, 10}},
      {Key::settings, {0, 20}},
      {Key::sequencer, {0, 6}},
      {Key::synth, {0, 19}},
    }};
  };
} // namespace otto::board::controller
