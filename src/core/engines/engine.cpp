#include "engine.hpp"
#include "services/state.hpp"
#include "services/presets.hpp"

namespace otto::core::engines {

  // AnyEngine ////////////////////////////////////////////////////////////////

  AnyEngine::AnyEngine(std::string const& name,
    props::properties_base& props,
                       std::unique_ptr<ui::Screen> screen)
    : _props(props),
      _name(name),
      _screen(std::move(screen))
  {}

  /// The name of this module.
  const std::string& AnyEngine::name() const noexcept
  {
    return _name;
  }

  ui::Screen& AnyEngine::screen() noexcept
  {
    return *_screen;
  }

  ui::Screen const& AnyEngine::screen() const noexcept
  {
    return *_screen;
  }

  props::properties_base& AnyEngine::props() noexcept
  {
    return _props;
  }

  props::properties_base const& AnyEngine::props() const noexcept
  {
    return _props;
  }

  int AnyEngine::current_preset() const noexcept
  {
    return _current_preset;
  }

  int AnyEngine::current_preset(int new_val) noexcept
  {
    return _current_preset = new_val;
  }

  nlohmann::json AnyEngine::to_json() const
  {
    nlohmann::json j;
    if (props().is<props::serializable>()) {
      j["props"] = props().as<props::serializable>().to_json();
      try {
        j["preset"] = service::presets::name_of_idx(_name, _current_preset);
      } catch (service::presets::exception& e) {
        // no preset set, all is good
      }
    }
    return j;
  }

  void AnyEngine::from_json(const nlohmann::json& j)
  {
    if (j.is_object()) {
      auto iter = j.find("preset");
      if (iter != j.end()) {
        service::presets::apply_preset(*this, iter->get<std::string>(), true);
      }
      if (props().is<props::serializable>())
        props().as<props::serializable>().from_json(j["props"]);
    }
  }

} // namespace otto::core::engines
