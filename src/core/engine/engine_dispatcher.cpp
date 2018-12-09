#include "engine_dispatcher.hpp"

#include "engine_selector_screen.hpp"
#include "services/engine_manager.hpp"
#include "services/preset_manager.hpp"

namespace otto::core::engine {

  // EngineDispatcher Implementations /////////////////////////////////////////
  template<EngineType ET>
  void EngineDispatcher<ET>::init()
  {
    _selector_screen = std::make_unique<EngineSelectorScreen>(*this);
  }

  template<EngineType ET>
  Engine<ET>* EngineDispatcher<ET>::current() noexcept
  {
    return _current.get();
  }

  template<EngineType ET>
  const Engine<ET>* EngineDispatcher<ET>::current() const noexcept
  {
    return _current.get();
  }

  template<EngineType ET>
  Engine<ET>* EngineDispatcher<ET>::operator->() noexcept
  {
    return _current.get();
  }

  template<EngineType ET>
  const Engine<ET>* EngineDispatcher<ET>::operator->() const noexcept
  {
    return _current.get();
  }

  template<EngineType ET>
  Engine<ET>& EngineDispatcher<ET>::select(const EngineFactory& fact)
  {
    _current = fact.construct();
    return *_current;
  }

  template<EngineType ET>
  Engine<ET>& EngineDispatcher<ET>::select(const std::string& name)
  {
    auto iter = util::find_if(_factories, [&name](auto&& f) { return f.name == name; });
    if (iter != _factories.end()) {
      select(*iter);
    } else {
      throw util::exception("Engine '{}' not found", name);
    }
    return *_current;
  }

  template<EngineType ET>
  Engine<ET>& EngineDispatcher<ET>::select(std::size_t idx)
  {
    return select(_factories.at(idx));
  }

  template<EngineType ET>
  ui::Screen& EngineDispatcher<ET>::selector_screen() noexcept
  {
    return *_selector_screen;
  }

  template<EngineType ET>
  auto EngineDispatcher<ET>::engine_factories() const noexcept -> const std::vector<EngineFactory>&
  {
    return _factories;
  }

  template<EngineType Et>
  void EngineDispatcher<Et>::register_factory(EngineFactory fact)
  {
    _factories.push_back(std::move(fact));
  }

  template<EngineType ET>
  nlohmann::json EngineDispatcher<ET>::to_json() const
  {
    nlohmann::json j = nlohmann::json::object();
    j["current_engine"] = current()->name();
    j["props"] = current()->to_json();
    return j;
  }

  template<EngineType ET>
  void EngineDispatcher<ET>::from_json(const nlohmann::json& j)
  {
    const auto found =
      util::find_if(_factories, [name = j["current_engine"].get<std::string>()](
                                  EngineFactory& fact) { return fact.name == name; });
    if (found == _factories.end()) {
      throw exception(ErrorCode::engine_not_found);
    }
    select(*found);
    current()->from_json(j["props"]);
  }

  // Explicit instantiations
  // If you need an EngineDispatcher for any other engine type, add it here
  template struct EngineDispatcher<EngineType::synth>;
  template struct EngineDispatcher<EngineType::sequencer>;
  template struct EngineDispatcher<EngineType::effect>;

} // namespace otto::core::engine
