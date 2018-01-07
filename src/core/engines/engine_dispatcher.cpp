#include "engine_dispatcher.hpp"

#include "engine_selector_screen.hpp"
#include "services/engine_manager.hpp"

namespace otto::engines {

  // EngineDispatcher Implementations /////////////////////////////////////////
  template<EngineType ET>
  void EngineDispatcher<ET>::init()
  {
    _engines = create_engines<ET>();
    if (_engines.empty()) {
      throw util::exception(
        "No engines registered. Can't construct EngineDispatcher");
    }
    _selector_screen = std::make_unique<EngineSelectorScreen>(*this);
  }

  template<EngineType ET>
  Engine<ET>& EngineDispatcher<ET>::current() noexcept
  {
    return *_current;
  }

  template<EngineType ET>
  const Engine<ET>& EngineDispatcher<ET>::current() const noexcept
  {
    return *_current;
  }

  template<EngineType ET>
  Engine<ET>& EngineDispatcher<ET>::operator*() noexcept
  {
    return *_current;
  }

  template<EngineType ET>
  const Engine<ET>& EngineDispatcher<ET>::operator*() const noexcept
  {
    return *_current;
  }

  template<EngineType ET>
  Engine<ET>* EngineDispatcher<ET>::operator->() noexcept
  {
    return _current;
  }

  template<EngineType ET>
  const Engine<ET>* EngineDispatcher<ET>::operator->() const noexcept
  {
    return _current;
  }

  template<EngineType ET>
  Engine<ET>& EngineDispatcher<ET>::select(const std::string& name)
  {
    auto iter = util::find_if(
      _engines, [&name](auto&& eg) { return eg->name() == name; });
    if (iter != _engines.end()) {
      select((*iter).get());
    } else {
      throw util::exception("Engine '{}' not found", name);
    }
    return *_current;
  }

  template<EngineType ET>
  Engine<ET>& EngineDispatcher<ET>::select(Engine<ET>* ptr)
  {
    if (_current != nullptr) _current->on_disable();
    _current = ptr;
    _current->on_enable();
    return *_current;
  }

  template<EngineType ET>
  Engine<ET>& EngineDispatcher<ET>::select(Engine<ET>& ref)
  {
    return select(&ref);
  }

  template<EngineType ET>
  Engine<ET>& EngineDispatcher<ET>::select(std::size_t idx)
  {
    return select((_engines.begin().base() + idx)->get());
  }

  template<EngineType ET>
  ui::Screen& EngineDispatcher<ET>::selector_screen() noexcept
  {
    return *_selector_screen;
  }

  template<EngineType ET>
  const std::vector<std::unique_ptr<Engine<ET>>>&
  EngineDispatcher<ET>::engines() const noexcept
  {
    return _engines;
  }

  template<EngineType ET>
  nlohmann::json EngineDispatcher<ET>::to_json() const
  {
    nlohmann::json j = nlohmann::json::object();
    for (auto&& engine : _engines) {
      j[engine->name()] = engine->to_json();
    }
    return j;
  }

  template<EngineType ET>
  void EngineDispatcher<ET>::from_json(const nlohmann::json& j)
  {
    if (j.is_object()) {
      auto& engine_name = j["engine"];
      auto& preset_name = j["preset"];
      auto& data = j["data"];
      if (!engine_name.is_string() || !preset_name.is_string() || data.is_null()) {
        DLOGE("Got json: {}", j);
        throw util::JsonFile::exception(util::JsonFile::ErrorCode::invalid_data,
          "Unexpected json structure");
      }
      auto found = util::find_if(
        _engines, [name = engine_name.get<std::string>()](auto&& eptr) {
          return eptr->name() == name;
        });
      if (found == _engines.end()) {
        throw exception(ErrorCode::engine_not_found);
      }
      engines::apply_preset(**found, preset_name.get<std::string>());
      (*found)->from_json(data);
    }
  }

  // Explicit instantiations
  // If you need an EngineDispatcher for any other engine type, add it here
  template struct EngineDispatcher<EngineType::synth>;
  template struct EngineDispatcher<EngineType::drums>;
  template struct EngineDispatcher<EngineType::effect>;

} // namespace otto::engines
