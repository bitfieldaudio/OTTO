#include "graphics.hpp"

namespace otto::services {

  Graphics::Graphics(util::any_ptr<IGraphicsDriver> driver)
    : driver_(std::move(driver)), thread_([this] {
        driver_->run(std::bind_front(&Graphics::loop_function, this));
        runtime->request_stop();
        exit_thread();
      })
  {}

  itc::IExecutor& Graphics::executor() noexcept
  {
    return executor_;
  }

  void Graphics::show(std::function<void(SkCanvas&)> f)
  {
    draw_func_ = f;
  }

  bool Graphics::loop_function(SkCanvas& ctx)
  {
    if (draw_func_) draw_func_(ctx);
    executor_.run_queued_functions();
    return runtime->should_run();
  }

  void Graphics::exit_thread()
  {
    executor_.run_queued_functions();
  }
} // namespace otto::services
