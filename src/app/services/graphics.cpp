#include "graphics.hpp"

namespace otto::services {

  Graphics::Graphics(RuntimeController& runtime, util::smart_ptr<IGraphicsDriver>&& driver) : driver_(std::move(driver))
  {
    thread_ = std::jthread([this, &runtime](const std::stop_token& st) {
      driver_->run([this, &st](SkCanvas& ctx) {
        loop_function(ctx);
        return !st.stop_requested();
      });
      runtime.request_stop();
      exit_thread();
    });
  }

  void Graphics::show(DrawFunc f)
  {
    draw_func_ = std::move(f);
  }

  void Graphics::loop_function(SkCanvas& ctx)
  {
    auto now = chrono::clock::now();
    domain_.timeline().step(std::chrono::duration<choreograph::Time>((now - last_frame_)).count());
    last_frame_ = now;
    if (draw_func_) draw_func_(ctx);
    executor().run_queued_functions();
  }

  void Graphics::exit_thread()
  {
    // TODO: Propper exit syncing with ExecutorLock
    executor().run_queued_functions();
  }
} // namespace otto::services
