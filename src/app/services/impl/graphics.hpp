#pragma once

#include "lib/util/thread.hpp"

#include "app/services/graphics.hpp"
#include "app/services/runtime.hpp"

namespace otto::services {

  struct GraphicsImpl : Graphics {
    /// Open a window/display drawing the given draw function
    void show(std::function<void(SkCanvas&)> f) override;

    itc::IExecutor& executor() noexcept override;

  protected:
    /// The function to run in the main loop on the graphics thread.
    /// Draws the frame, executes the required functions, and returns
    /// whether to continue drawing frames.
    ///
    /// When this function returns false, it must not be called again.
    bool loop_function(SkCanvas& ctx);

    /// Make sure the queue is empty
    ///
    /// Must be run at the end of the thread
    void exit_thread();

  private:
    /// As a member instead of inheritance to easilly allow subclasses
    /// to add their own service accessors
    [[no_unique_address]] core::ServiceAccessor<Runtime> runtime;

  protected:
    std::function<void(SkCanvas&)> draw_func_ = nullptr;
    itc::QueueExecutor executor_;
  };

} // namespace otto::services
