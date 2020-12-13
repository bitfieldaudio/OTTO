#pragma once

#include <thread>

#include "app/drivers/graphics_driver.hpp"
#include "app/services/runtime.hpp"
#include "lib/chrono.hpp"
#include "lib/core/service.hpp"

namespace otto::stubs {

  struct NoProcessGraphicsDriver : drivers::IGraphicsDriver {
    void run(std::function<bool(skia::Canvas&)>) override{

    };
  };

  struct DummyGraphicsDriver final : drivers::IGraphicsDriver {
    DummyGraphicsDriver() = default;
    void run(std::function<bool(skia::Canvas&)> func) override
    {
      thread_ = std::jthread([this, func = std::move(func)] {
        auto pixels = std::vector<SkPMColor>(320 * 240);
        auto canvas = SkCanvas::MakeRasterDirectN32(320, 240, pixels.data(), 0);
        while (runtime->should_run()) {
          func(*canvas);
          std::this_thread::sleep_for(1s / 30);
        }
      });
    }

  private:
    [[no_unique_address]] core::ServiceAccessor<services::Runtime> runtime;
    std::jthread thread_;
  };
} // namespace otto::stubs
