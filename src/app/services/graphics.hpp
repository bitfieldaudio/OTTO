#pragma once

#include <choreograph/Choreograph.h>

#include "lib/util/any_ptr.hpp"

#include "app/drivers/graphics_driver.hpp"
#include "lib/core/service.hpp"
#include "lib/itc/executor.hpp"
#include "lib/itc/executor_provider.hpp"
#include "lib/itc/itc.hpp"

#include "runtime.hpp"

namespace otto::services {

  namespace detail {
    struct graphics_domain_tag;
  }

  struct Graphics : core::Service<Graphics>, itc::ExecutorProvider<detail::graphics_domain_tag> {
    using IGraphicsDriver = drivers::IGraphicsDriver;
    Graphics(util::any_ptr<IGraphicsDriver>::factory&& driver = IGraphicsDriver::make_default);
    /// Open a window/display drawing the given draw function
    void show(DrawFunc f);

    choreograph::Timeline& timeline() noexcept;

  private:
    /// The function to run in the main loop on the graphics thread.
    /// Draws the frame, executes the required functions, and returns
    /// whether to continue drawing frames.
    ///
    /// When this function returns false, it must not be called again.
    bool loop_function(skia::Canvas& ctx);

    /// Make sure the queue is empty
    ///
    /// Must be run at the end of the thread
    void exit_thread();
    /// As a member instead of inheritance to easilly allow subclasses
    /// to add their own service accessors
    [[no_unique_address]] core::ServiceAccessor<Runtime> runtime;

    util::any_ptr<IGraphicsDriver> driver_;
    DrawFunc draw_func_ = nullptr;
    choreograph::Timeline timeline_;
    chrono::time_point last_frame_ = chrono::clock::now();
    std::jthread thread_;
  };

} // namespace otto::services

namespace otto {

  struct GraphicsDomain : itc::StaticDomain<services::detail::graphics_domain_tag> {};

} // namespace otto
