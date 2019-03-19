#include "engine.hpp"

#include "services/preset_manager.hpp"

namespace otto::core::engine {

  // IEngine ////////////////////////////////////////////////////////////////

  IEngine::IEngine(std::unique_ptr<ui::Screen> screen)
    : _screen(std::move(screen))
  {}

  ui::Screen& IEngine::screen() noexcept
  {
    return *_screen;
  }

  ui::Screen const& IEngine::screen() const noexcept
  {
    return *_screen;
  }

  int IEngine::current_preset() const noexcept
  {
    return _current_preset;
  }

  int IEngine::current_preset(int new_val) noexcept
  {
    return _current_preset = new_val;
  }

} // namespace otto::core::engine
