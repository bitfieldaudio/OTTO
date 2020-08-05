#include "graphics.hpp"

namespace otto::app::services {

  lib::itc::IExecutor& GraphicsImpl::executor() noexcept
  {
    return executor_;
  }

  void GraphicsImpl::show(std::function<void(SkCanvas&)> f)
  {
    draw_func_ = f;
  }

  bool GraphicsImpl::loop_function(SkCanvas& ctx)
  {
    if (draw_func_) draw_func_(ctx);
    executor_.run_queued_functions();
    return runtime->should_run();
  }

  void GraphicsImpl::exit_thread()
  {
    executor_.run_queued_functions();
  }
} // namespace otto::app::services
