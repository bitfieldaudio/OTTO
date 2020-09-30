#pragma once

#include "lib/util/any_ptr.hpp"

#include "lib/core/service.hpp"
#include "lib/itc/executor.hpp"
#include "lib/itc/itc.hpp"

#include <SkCanvas.h>

#include "runtime.hpp"

namespace otto::services {

  struct IGraphicsDriver {
    virtual ~IGraphicsDriver() = default;
    virtual void run(std::function<bool(SkCanvas&)>) = 0;

    /// Construct the default graphics driver
    static std::unique_ptr<IGraphicsDriver> make_default();
  };

  struct Graphics : core::Service<Graphics> {
    Graphics(util::any_ptr<IGraphicsDriver> driver = IGraphicsDriver::make_default());

    /// An @ref itc::Consumer with the graphics executor hardcoded
    template<itc::AState State>
    struct Consumer;
    /// Open a window/display drawing the given draw function
    void show(std::function<void(SkCanvas&)> f);

    itc::IExecutor& executor() noexcept;

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
    std::function<void(SkCanvas&)> draw_func_ = nullptr;
    itc::QueueExecutor executor_;
    std::jthread thread_;
  };

  template<itc::AState State>
  struct Graphics::Consumer : itc::Consumer<State> {
    Consumer(itc::Channel<State>& c) : itc::Consumer<State>(c, graphics->executor()) {}

  private:
    core::ServiceAccessor<Graphics> graphics;
  };


} // namespace otto::services
