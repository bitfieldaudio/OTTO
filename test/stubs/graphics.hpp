#pragma once

#include <thread>

#include "lib/chrono.hpp"

#include "app/drivers/graphics_driver.hpp"
#include "app/services/runtime.hpp"

namespace otto::stubs {

  struct NoProcessGraphicsDriver : drivers::IGraphicsDriver {
    void run(std::function<bool(skia::Canvas&)>) override{

    };
  };

  struct DummyGraphicsDriver final : drivers::IGraphicsDriver {
    void run(std::function<bool(skia::Canvas&)> func) override
    {
      thread_ = std::jthread([func = std::move(func)](const std::stop_token& st) {
        auto pixels = std::vector<SkPMColor>(320 * 240);
        auto canvas = SkCanvas::MakeRasterDirectN32(320, 240, pixels.data(), 0);
        while (!st.stop_requested()) {
          func(*canvas);
          std::this_thread::sleep_for(1s / 30);
        }
      });
    }

  private:
    std::jthread thread_;
  };
} // namespace otto::stubs
