#pragma once

#include "lib/core/service.hpp"
#include "lib/itc/executor.hpp"
#include "lib/itc/itc.hpp"

#include <SkCanvas.h>

#include "runtime.hpp"

namespace otto::services {

  struct Graphics : core::Service<Graphics> {
    /// An @ref itc::Consumer with the graphics executor hardcoded
    template<itc::AState State>
    struct Consumer;
    /// Open a window/display drawing the given draw function
    virtual void show(std::function<void(SkCanvas&)>) = 0;

    virtual itc::IExecutor& executor() noexcept = 0;

    /// The board-specfic graphics service
    [[nodiscard]] static core::ServiceHandle<services::Graphics> make_board();
  };

  template<itc::AState State>
  struct Graphics::Consumer : itc::Consumer<State> {
    Consumer(itc::Channel<State>& c) : itc::Consumer<State>(c, graphics->executor()) {}

  private:
    core::ServiceAccessor<Graphics> graphics;
  };

} // namespace otto::services

namespace otto::board {
  core::ServiceHandle<services::Graphics> make_graphics();
}

namespace otto::services {
  inline core::ServiceHandle<services::Graphics> Graphics::make_board()
  {
    return board::make_graphics();
  }
} // namespace otto::services
