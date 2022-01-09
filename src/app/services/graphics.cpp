#include "graphics.hpp"

namespace otto::services {

  Graphics::Graphics(RuntimeController& runtime, util::smart_ptr<IGraphicsDriver>&& driver)
    : ExecutorProvider("graphics"), driver_(std::move(driver))
  {
    thread_ = std::jthread([this, &runtime](const std::stop_token& st) {
      log::set_thread_name("graphics");
      while (draw_func_ == nullptr && !st.stop_requested()) {
        executor().run_queued_functions();
      }
      if (!st.stop_requested()) {
        driver_->run([this, &st](SkCanvas& ctx) {
          loop_function(ctx);
          return !st.stop_requested();
        });
      }
      runtime.request_stop();
      // Run until destructor
      while (!st.stop_requested()) {
        executor().run_queued_functions();
      }
    });
  }

  util::at_exit Graphics::show(DrawFunc f)
  {
    executor().execute([this, f = std::move(f)]() mutable { draw_func_ = std::move(f); });
    executor().sync();
    return util::at_exit([this] {
      executor().execute([this] { draw_func_ = nullptr; });
      executor().sync();
    });
  }

  void Graphics::loop_function(SkCanvas& ctx)
  {
    auto now = chrono::clock::now();
    domain_.timeline().step(std::chrono::duration<choreograph::Time>((now - last_frame_)).count());
    last_frame_ = now;
    if (draw_func_) draw_func_(ctx);
    executor().run_queued_functions();
  }

  Graphics::IGraphicsDriver& Graphics::driver() noexcept
  {
    return *driver_;
  }
} // namespace otto::services
