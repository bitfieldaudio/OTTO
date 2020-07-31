#pragma once

#include "app/services/graphics.hpp"

namespace otto::app::services {

  struct GraphicsImpl : Graphics {
    /// Open a window/display drawing the given draw function
    virtual void show(std::function<void(SkCanvas&)>) override = 0;

    lib::itc::IExecutor& executor() const noexcept override;

  protected:
  };

} // namespace otto::app::services
