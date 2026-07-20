#include "graphics.hpp"

#include <chrono>
#include <thread>

namespace otto::services {

  Graphics::Graphics(RuntimeController& runtime, util::smart_ptr<IGraphicsDriver>&& driver)
    : ExecutorProvider("graphics"), driver_(std::move(driver))
  {
#if defined(__APPLE__)
    // AppKit/GLFW must create windows and poll events on the main thread.
    // Until run_until_stop() takes over, keep a pump thread so setup code that
    // syncs to the graphics executor (engine screens, etc.) does not deadlock.
    runtime_ = &runtime;
    pump_ = std::jthread([this](const std::stop_token& st) {
      log::set_thread_name("graphics-exec");
      using namespace std::chrono_literals;
      while (!st.stop_requested() && !takeover_.load()) {
        executor().run_queued_functions();
        std::this_thread::sleep_for(1ms);
      }
    });
#else
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
#endif
  }

  util::at_exit Graphics::show(DrawFunc f)
  {
#if defined(__APPLE__)
    draw_func_ = std::move(f);
    return util::at_exit([this] { draw_func_ = nullptr; });
#else
    executor().execute([this, f = std::move(f)]() mutable { draw_func_ = std::move(f); });
    executor().sync();
    return util::at_exit([this] {
      executor().execute([this] { draw_func_ = nullptr; });
      executor().sync();
    });
#endif
  }

#if defined(__APPLE__)
  void Graphics::run_until_stop()
  {
    takeover_ = true;
    if (pump_.joinable()) {
      pump_.request_stop();
      pump_.join();
    }
    log::set_thread_name("graphics");
    // Drain anything queued while the pump was shutting down before the
    // GLFW loop starts serving the graphics executor.
    executor().run_queued_functions();
    if (runtime_->should_run()) {
      driver_->run([this](SkCanvas& ctx) {
        loop_function(ctx);
        return runtime_->should_run();
      });
    }
    runtime_->request_stop();
  }
#endif

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
