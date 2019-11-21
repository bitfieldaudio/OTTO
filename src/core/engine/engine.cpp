#include "engine.hpp"

#include "services/preset_manager.hpp"

namespace otto::core::engine {

  // IEngine ////////////////////////////////////////////////////////////////

  IEngine::IEngine() noexcept
  {}

  int IEngine::current_preset() const noexcept
  {
    return _current_preset;
  }

  int IEngine::current_preset(int new_val) noexcept
  {
    return _current_preset = new_val;
  }

} // namespace otto::core::engine
