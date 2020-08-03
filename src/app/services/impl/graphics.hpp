#pragma once

#include "lib/util/thread.hpp"

#include "app/services/graphics.hpp"

namespace otto::app::services {

  using namespace lib;

  struct GraphicsImpl : Graphics, core::ServiceAccessor<Runtime> {

    /// Open a window/display drawing the given draw function
    void show(std::function<void(SkCanvas&)> f) override;

    itc::IExecutor& executor() noexcept override;

  protected:
    /// The function to run in the main loop on the graphics thread.
    /// Draws the frame, executes the required functions, and returns
    /// whether to continue drawing frames.
    /// 
    /// When this function returns false, it must not be called again.
    bool loop_function(SkCanvas& ctx) {
      if (draw_func_) draw_func_(ctx);
      executor_.run_queued_functions();
      return service<Runtime>().should_run();
    }

    /// Make sure the queue is empty
    /// 
    /// Must be run at the end of the thread
    void exit_thread() {
      executor_.run_queued_functions();
    }

    std::function<void(SkCanvas&)> draw_func_ = nullptr;
    itc::QueueExecutor executor_;
  };

} // namespace otto::app::services
