#pragma once

#include "lib/graphics.hpp"
#include "lib/skia/skia.hpp"

namespace otto::drivers {

  struct IGraphicsDriver {
    virtual ~IGraphicsDriver() = default;
    /// Request window size, if the driver supports it.
    /// Will default to @ref otto::skia::screen_size.
    virtual void request_size(skia::Vector){};
    /// Show the graphics, using the given draw function.
    /// If the draw function returns false, the window is closed
    virtual void run(std::function<bool(skia::Canvas&)>) = 0;

    /// Construct the default graphics driver
    static std::unique_ptr<IGraphicsDriver> make_default();
  };
} // namespace otto::drivers
