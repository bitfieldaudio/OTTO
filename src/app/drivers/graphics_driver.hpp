#pragma once

#include "lib/graphics.hpp"

namespace otto::drivers {

  struct IGraphicsDriver {
    virtual ~IGraphicsDriver() = default;
    virtual void run(std::function<bool(skia::Canvas&)>) = 0;

    /// Construct the default graphics driver
    static std::unique_ptr<IGraphicsDriver> make_default();
  };
} // namespace otto::drivers
