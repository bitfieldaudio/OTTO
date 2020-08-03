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
} // namespace otto::app::services
