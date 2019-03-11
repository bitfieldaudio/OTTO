#include "engine.hpp"

#include "services/preset_manager.hpp"

namespace otto::core::engine {

  // AnyEngine ////////////////////////////////////////////////////////////////

  IEngine::IEngine(std::string_view name,
    props::properties_base& props,
                       std::unique_ptr<ui::Screen> screen)
    : _props(props),
      _name(name),
      _screen(std::move(screen))
  {}

  /// The name of this module.
  std::string_view IEngine::name() const noexcept
  {
    return _name;
  }

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

  nlohmann::json IEngine::to_json() const
  {
    nlohmann::json j;
    if (props().is<props::serializable>()) {
      j["props"] = props().as<props::serializable>().to_json();
      try {
        j["preset"] = Application::current().preset_manager->name_of_idx(_name, _current_preset);
      } catch (services::PresetManager::exception& e) {
        // no preset set, all is good
      }
    }
    return j;
  }

  void IEngine::from_json(const nlohmann::json& j)
  {
    if (j.is_object()) {
      auto iter = j.find("preset");
      if (iter != j.end()) {
        Application::current().preset_manager->apply_preset(*this, iter->get<std::string>(), true);
      }
      if (props().is<props::serializable>())
        props().as<props::serializable>().from_json(j["props"]);
    }
  }

} // namespace otto::core::engines
