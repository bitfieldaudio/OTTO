#pragma once

#include "lib/core/service.hpp"
#include "lib/itc/executor.hpp"

#include <SkCanvas.h>

#include "runtime.hpp"

namespace otto::app::services {

  struct Graphics : lib::core::Service<Graphics>, lib::core::ServiceAccessor<Runtime> {
    /// Open a window/display drawing the given draw function
    virtual void show(std::function<void(SkCanvas&)>) = 0;

    ///
    virtual lib::itc::IExecutor& executor() const noexcept = 0;

    /// Run the board-specfic graphics service
    [[nodiscard]] static auto make_board();
  };

} // namespace otto::app::services

namespace otto::board {
  lib::core::ServiceHandle<app::services::Graphics> make_graphics_service();
}

namespace otto::app::services {
  inline auto Graphics::make_board()
  {
    return board::make_graphics_service();
  }
} // namespace otto::app::services
