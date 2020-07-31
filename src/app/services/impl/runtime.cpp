#include "runtime.hpp"

namespace otto::app::services {

  using Stage = Runtime::Stage;

  Stage RuntimeImpl::stage() const noexcept
  {
    return static_cast<Stage>(stage_.load());
  }

  bool RuntimeImpl::should_run() const noexcept
  {
    auto s = stage();
    return s == Stage::running || s == Stage::initializing;
  }

  void RuntimeImpl::set_stage(Stage s) noexcept {
    stage_.store(static_cast<std::underlying_type_t<Stage>>(s));
  }

} // namespace otto::app::services
