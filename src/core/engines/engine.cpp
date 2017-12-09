#include "engine.hpp"

namespace otto::engines {

  // AnyEngine ////////////////////////////////////////////////////////////////

  AnyEngine::AnyEngine(std::string name,
                       Properties& props,
                       std::unique_ptr<ui::Screen> screen)
    : _name(std::move(name)), //
      _props(props),
      _screen(std::move(screen))
  {}

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

  // Free functions ///////////////////////////////////////////////////////////

  void to_json(nlohmann::json& j, const AnyEngine& e)
  {
    j = e.to_json();
  }

  void from_json(const nlohmann::json& j, AnyEngine& e)
  {
    e.from_json(j);
  }

}  // namespace otto::engines
