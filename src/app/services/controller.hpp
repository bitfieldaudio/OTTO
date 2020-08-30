#pragma once

#include "lib/core/service.hpp"
#include "lib/itc/reducer.hpp"

#include "app/input.hpp"
#include "app/leds.hpp"

namespace otto::services {
  struct Controller : core::Service<Controller> {
    virtual void set_input_handler(InputHandler& handler) = 0;
    virtual void set_led_color(LED led, LEDColor) = 0;

    /// The board-specfic controller service
    [[nodiscard]] static auto make_board();
  };
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
