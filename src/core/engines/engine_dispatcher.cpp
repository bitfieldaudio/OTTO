#include "engine_dispatcher.hpp"

#include "engine_selector_screen.hpp"
#include "services/engines.hpp"
#include "services/presets.hpp"

namespace otto::core::engines {

  // EngineDispatcher Implementations /////////////////////////////////////////
  template<EngineType ET>
  void EngineDispatcher<ET>::init()
  {
    _engines = create_engines<ET>();
    if (_engines.empty()) {
      throw util::exception(
        "No engines registered. Can't construct EngineDispatcher");
    }
    for (auto&& engine : _engines) {
      // Apply default presets to all engines
      try {
        int idx = engine->current_preset();
        service::presets::apply_preset(*engine, std::max(idx, 0), true);
      } catch (service::presets::exception& e) {
        DLOGI(e.what());
      }
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
    if (_current == ptr && ptr != nullptr) return *_current;
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
      for (auto iter = j.begin(); iter != j.end(); iter++) {
        auto found = util::find_if(_engines, [name = iter.key()](auto&& eptr) {
          return eptr->name() == name;
        });
        if (found == _engines.end()) {
          throw exception(ErrorCode::engine_not_found);
        }
        (*found)->from_json(iter.value());
      }
    }
  }

  // Explicit instantiations
  // If you need an EngineDispatcher for any other engine type, add it here
  template struct EngineDispatcher<EngineType::synth>;
  template struct EngineDispatcher<EngineType::sequencer>;
  template struct EngineDispatcher<EngineType::effect>;

} // namespace otto::core::engines
