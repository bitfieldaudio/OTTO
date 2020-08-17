#pragma once

#include "lib/util/enum.hpp"

#include "lib/core/service.hpp"
#include "lib/itc/reducer.hpp"

namespace otto::services {

  enum struct Key : std::uint8_t {
    channel0,
    channel1,
    channel2,
    channel3,
    channel4,
    channel5,
    channel6,
    channel7,
    channel8,
    channel9,
    seq0,
    seq1,
    seq2,
    seq3,
    seq4,
    seq5,
    seq6,
    seq7,
    seq8,
    seq9,
    seq10,
    seq11,
    seq12,
    seq13,
    seq14,
    seq15,
    blue_enc_click,
    green_enc_click,
    yellow_enc_click,
    red_enc_click,
    shift,
    sends,
    plus,
    routing,
    minus,
    fx1,
    fx2,
    master,
    play,
    record,
    arp,
    slots,
    twist1,
    twist2,
    looper,
    external,
    sampler,
    envelope,
    voices,
    settings,
    sequencer,
    synth,
    unassigned_a,
    unassigned_b,
    unassigned_c,
    unassigned_d,
    unassigned_e,
    unassigned_f,
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

  struct Controller : core::Service<Controller> {
    virtual void set_input_handler(InputHandler& handler) = 0;

    /// The board-specfic graphics service
    [[nodiscard]] static auto make_board();
  };

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
} // namespace otto::services

namespace otto::board {
  core::ServiceHandle<services::Controller> make_controller();
}

namespace otto::services {
  inline auto Controller::make_board()
  {
    return board::make_controller();
  }
} // namespace otto::services
