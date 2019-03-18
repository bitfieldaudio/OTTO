#include "engine.hpp"

#include "services/preset_manager.hpp"

namespace otto::core::engine {

  // IEngine ////////////////////////////////////////////////////////////////

  IEngine::IEngine(props::properties_base& props, std::unique_ptr<ui::Screen> screen)
    : _props(props), _screen(std::move(screen))
  {}

  ui::Screen& IEngine::screen() noexcept
  {
    return *_screen;
  }

  ui::Screen const& IEngine::screen() const noexcept
  {
    return *_screen;
  }

  props::properties_base& IEngine::props() noexcept
  {
    return _props;
  }

  props::properties_base const& IEngine::props() const noexcept
  {
    return _props;
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
