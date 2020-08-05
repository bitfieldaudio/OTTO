#pragma once

#include "lib/core/service.hpp"
#include "lib/itc/reducer.hpp"

namespace otto::app::services {

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
    rec,
    minus,
    fx1,
    fx2,
    master,
    play,
    arp,
    slots,
    twist1,
    twist2,
    looper,
    external,
    sampler,
    envelope,
    settings,
    sequencer,
    synth
  };

  struct KeyEvent {
    enum struct Type {
      press,
      release,
    };
    Key key = {};
  };

  struct KeyPress : KeyEvent {};
  struct KeyRelease : KeyEvent {};

  enum struct Encoder : std::uint8_t {
    blue,
    green,
    yellow,
    red,
  };

  struct EncoderEvent {
    Encoder encoder = {};
    int steps = 0;
  };

  using InputHandler = lib::itc::IEventHandler<KeyPress, KeyRelease, EncoderEvent>;

  struct Controller : lib::core::Service<Controller> {
    virtual void set_input_handler(InputHandler& handler) = 0;

    /// The board-specfic graphics service
    [[nodiscard]] static auto make_board();
  };

} // namespace otto::app::services

namespace otto::board {
  lib::core::ServiceHandle<app::services::Controller> make_controller();
}

namespace otto::app::services {
  inline auto Controller::make_board()
  {
    return board::make_controller();
  }
} // namespace otto::app::services
