#pragma once

#include "app/services/audio.hpp"
#include "app/services/controller.hpp"
#include "lib/core/service.hpp"
#include "lib/graphics.hpp"

#include "app/input.hpp"
#include "lib/midi.hpp"

namespace otto::services {

  struct UIManager : core::Service<UIManager>, InputHandler, core::ServiceAccessor<Audio, Controller> {
    UIManager()
    {
      service<Controller>().set_input_handler(*this);
    }
    IInputHandler& input_handler() noexcept;
    IDrawable& drawable() noexcept;

    void handle(KeyPress e) noexcept override;
    void handle(KeyRelease) noexcept override;
    void handle(EncoderEvent) noexcept override {}
  };

} // namespace otto::services
