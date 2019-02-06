#include "engine_dispatcher.hpp"

#include "engine_selector_screen.hpp"
#include "services/engine_manager.hpp"
#include "services/preset_manager.hpp"

#include <thread>

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
  int EngineDispatcher<ET>::current_idx() const noexcept {
    return _current_factory - &*_factories.begin();
  }

  template<EngineType ET>
  Engine<ET>& EngineDispatcher<ET>::select(const EngineFactory& fact)
  {
    auto save_it = _current;
    _current = fact.construct();
    _current_factory = &fact;
    _current->from_json(fact.data);
    // TODO:
    // So sorry about this hack, its awful.
    // If we dont wait to destruct the old engine, the audio thread might still be using it.
    // This obviously needs to be done with some signaling.
    if (save_it != nullptr) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      if (auto found =
            util::find_if(_factories, [&](auto& fc) { return fc.name == save_it->name(); });
          found != _factories.end()) {
        found->data = save_it->to_json();
      }
    }
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
    auto engines = nlohmann::json::object();
    for (auto& f : _factories) {
      if (_current != nullptr && f.name == _current->name()) {
        engines[f.name] = _current->to_json();
      } else {
        engines[f.name] = f.data;
      }
    }
    j["engines"] = engines;
    return j;
  }

  template<EngineType ET>
  void EngineDispatcher<ET>::from_json(const nlohmann::json& j)
  {
    auto engines = j.find("engines");
    if (engines != j.end() && engines->is_object()) {
      for (auto& f : _factories) {
        try {
          auto found = engines->find(f.name);
          if (found != engines->end() && found->is_object()) {
            f.data = *found;
          }
        } catch (nlohmann::json::exception& e) {
          LOGE(e.what());
        }
      }
    }
    const auto found =
      util::find_if(_factories, [name = j["current_engine"].get<std::string>()](
                                  EngineFactory& fact) { return fact.name == name; });
    if (found == _factories.end()) {
      throw exception(ErrorCode::engine_not_found);
    }
    select(*found);
  }

  // Explicit instantiations
  // If you need an EngineDispatcher for any other engine type, add it here
  template struct EngineDispatcher<EngineType::synth>;
  template struct EngineDispatcher<EngineType::arpeggiator>;
  template struct EngineDispatcher<EngineType::effect>;

} // namespace otto::core::engine
