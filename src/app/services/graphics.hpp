#pragma once

#include <choreograph/Choreograph.h>

#include "lib/util/at_exit.hpp"
#include "lib/util/smart_ptr.hpp"

#include "lib/itc/executor.hpp"
#include "lib/itc/executor_provider.hpp"
#include "lib/itc/itc.hpp"

#include "app/domains/graphics.hpp"
#include "app/drivers/graphics_driver.hpp"

#include "runtime.hpp"

namespace otto::services {

  struct Graphics : itc::ExecutorProvider<GraphicsDomain::domain_tag_t> {
    using IGraphicsDriver = drivers::IGraphicsDriver;
    Graphics(RuntimeController& runtime, util::smart_ptr<IGraphicsDriver>&& driver = IGraphicsDriver::make_default());
    /// Open a window/display drawing the given draw function
    util::at_exit show(DrawFunc f);

    IGraphicsDriver& driver() noexcept;

  private:
    /// The function to run in the main loop on the graphics thread.
    /// Draws the frame, executes the required functions, and returns
    /// whether to continue drawing frames.
    void loop_function(skia::Canvas& ctx);

    GraphicsDomain domain_;
    util::smart_ptr<IGraphicsDriver> driver_;
    DrawFunc draw_func_ = nullptr;
    chrono::time_point last_frame_ = chrono::clock::now();
    std::jthread thread_;
  };

} // namespace otto::services

// TODO: move
namespace otto {

  /// Base class for screens.
  ///
  /// - Extends GraphicsDomain
  /// - Overrides LED functions to not handle any LEDs (these can obviously be overridden
  ///   in the derived class)
  struct ScreenBase : IScreen, GraphicsDomain {
    [[nodiscard]] LedSet led_mask() const noexcept override
    {
      return {};
    }
    void leds(LEDColorSet& colors) noexcept override {}
  };

  /// Base class for overlays.
  ///
  /// Extends IOverlay instead, which overrides is_overlay()
  struct OverlayBase : IOverlay, GraphicsDomain {
    [[nodiscard]] LedSet led_mask() const noexcept override
    {
      return {};
    }
    void leds(LEDColorSet& colors) noexcept override {}
  };


} // namespace otto
