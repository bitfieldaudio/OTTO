#include "engine.hpp"
#include "services/state.hpp"

namespace otto::engines {

  // AnyEngine ////////////////////////////////////////////////////////////////

  AnyEngine::AnyEngine(std::string name,
                       Properties& props,
                       std::unique_ptr<ui::Screen> screen)
    : _name(std::move(name)), //
      _props(props),
      _screen(std::move(screen))
  {
    auto load = [&](auto json) { from_json(json); };
    auto save = [&]() { return to_json(); };
    services::state::attach(_name, load, save);
  }

  AnyEngine::~AnyEngine()
  {
    services::state::detach(_name);
  }

  /// The name of this module.
  const std::string& AnyEngine::name() const noexcept
  {
    return _name;
  }

  Properties& AnyEngine::props() noexcept
  {
    return _props;
  }

  const Properties& AnyEngine::props() const noexcept
  {
    return _props;
  }

  ui::Screen& AnyEngine::screen() noexcept
  {
    return *_screen;
  }

  const ui::Screen& AnyEngine::screen() const noexcept
  {
    return *_screen;
  }

  nlohmann::json AnyEngine::to_json() const
  {
    return _props.to_json();
  }

  void AnyEngine::from_json(const nlohmann::json& j)
  {
    _props.from_json(j);
  }
} // namespace otto::engines
