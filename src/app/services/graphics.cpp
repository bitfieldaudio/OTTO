#include "graphics.hpp"

namespace otto::services {

  Graphics::Graphics(util::any_ptr<IGraphicsDriver>::factory&& make_driver)
    : driver_(make_driver()), thread_([this] {
        driver_->run(std::bind_front(&Graphics::loop_function, this));
        runtime->request_stop();
        exit_thread();
      })
  {}

  void Graphics::show(DrawFunc f)
  {
    draw_func_ = std::move(f);
  }

  bool Graphics::loop_function(SkCanvas& ctx)
  {
    if (draw_func_) draw_func_(ctx);
    executor().run_queued_functions();
    return runtime->should_run();
  }

  void Graphics::exit_thread()
  {
    // TODO: Propper exit syncing with ExecutorLock
    executor().run_queued_functions();
  }
} // namespace otto::services
