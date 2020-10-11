#pragma once

#include "lib/util/any_ptr.hpp"

#include "app/drivers/graphics_driver.hpp"
#include "lib/core/service.hpp"
#include "lib/itc/executor.hpp"
#include "lib/itc/executor_provider.hpp"
#include "lib/itc/itc.hpp"

#include "runtime.hpp"

namespace otto::services {

  struct Graphics : core::Service<Graphics>, itc::ExecutorProvider {
    using IGraphicsDriver = drivers::IGraphicsDriver;
    Graphics(util::any_ptr<IGraphicsDriver>::factory&& driver = IGraphicsDriver::make_default);

    /// An @ref itc::Consumer with the graphics executor hardcoded
    template<itc::AState State>
    struct Consumer;
    /// Open a window/display drawing the given draw function
    void show(DrawFunc f);

  private:
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
    /// As a member instead of inheritance to easilly allow subclasses
    /// to add their own service accessors
    [[no_unique_address]] core::ServiceAccessor<Runtime> runtime;

  protected:
    util::any_ptr<IGraphicsDriver> driver_;
    DrawFunc draw_func_ = nullptr;
    std::jthread thread_;
  };

  template<itc::AState State>
  struct Graphics::Consumer : itc::Consumer<State> {
    Consumer(itc::Channel<State>& c) : itc::Consumer<State>(c, graphics->executor()) {}

  private:
    core::ServiceAccessor<Graphics> graphics;
  };


} // namespace otto::services
