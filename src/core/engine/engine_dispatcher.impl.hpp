#pragma once
#include "engine_dispatcher.hpp"

#include "core/engine/engine_selector_screen.hpp"
#include "engine_selector_screen.hpp"
#include "services/audio_manager.hpp"
#include "services/engine_manager.hpp"
#include "services/preset_manager.hpp"
#include "util/meta.hpp"
#include "util/string_conversions.hpp"

#include <thread>

namespace otto::core::engine {

  // EngineDispatcher Implementations /////////////////////////////////////////
  template<EngineType ET, typename... Egs>
  void EngineDispatcher<ET, Egs...>::init()
  {
    _selector_screen = std::make_unique<EngineSelectorScreen>(*this);
  }

  template<EngineType ET, typename... Egs>
  ITypedEngine<ET>& EngineDispatcher<ET, Egs...>::current() noexcept
  {
    return *_current;
  }

  template<EngineType ET, typename... Egs>
  int EngineDispatcher<ET, Egs...>::current_idx() const noexcept
  {
    if (_current == &_null_engine) return -1;
    return _engine_storage.index();
  }

  template<EngineType ET, typename... Egs>
  const ITypedEngine<ET>& EngineDispatcher<ET, Egs...>::current() const noexcept
  {
    return *_current;
  }


  template<EngineType ET, typename... Egs>
  ITypedEngine<ET>* EngineDispatcher<ET, Egs...>::operator->() noexcept
  {
    return _current;
  }

  template<EngineType ET, typename... Egs>
  const ITypedEngine<ET>* EngineDispatcher<ET, Egs...>::operator->() const noexcept
  {
    return _current;
  }

  template<EngineType ET, typename... Egs>
  ITypedEngine<ET>& EngineDispatcher<ET, Egs...>::select(std::string_view name)
  {
    _engine_data.insert_or_replace(_current->name(), _current->to_json());
    _current = &_null_engine;
    if (!allow_off || util::to_lowercase(name) != "off") {
      Application::current().audio_manager->wait_one();
      bool done = false;
      meta::for_each<meta::list<Egs...>>([&](auto m_type) -> void {
        using type = decltype(m_type._t());
        if (!done && name_of_engine_v<type> == name) {
          _engine_storage.template emplace<type>();
          if (auto found = _engine_data.try_lookup(_engine_storage->name()); found)
            _engine_storage.base()->from_json(*found);
          done = true;
        }
      });
      _current = _engine_storage.base();
      if (!done) throw util::exception("ITypedEngine '{}' not found", name);
    }
    return *_current;
  }

  template<EngineType ET, typename... Egs>
  ITypedEngine<ET>& EngineDispatcher<ET, Egs...>::select(int index)
  {
    _engine_data.insert_or_replace(_current->name(), _current->to_json());
    _current = &_null_engine;
    if (!allow_off || index >= 0) {
      Application::current().audio_manager->wait_one();
      bool done = false;
      meta::for_each<meta::list<Egs...>>([&, idx = 0](auto m_type) mutable {
        using type = decltype(m_type._t());
        if (!done && idx == index) {
          _engine_storage.template emplace<type>();
          if (auto found = _engine_data.try_lookup(_engine_storage->name()); found)
            _engine_storage.base()->from_json(*found);
          done = true;
        }
        idx++;
      });
      _current = _engine_storage.base();
      if (!done) throw util::exception("EngineDispatcher::select(): Idx {} out of bounds", index);
    }
    return *_current;
  }

  template<EngineType ET, typename... Egs>
  std::vector<std::string_view> EngineDispatcher<ET, Egs...>::make_name_list() const
  {
    std::vector<std::string_view> res;
    res.reserve(sizeof...(Egs));
    meta::for_each<meta::list<Egs...>>([&](auto m_type) {
      using type = decltype(m_type._t());
      res.emplace_back(name_of_engine_v<type>);
    });
    return res;
  }

  template<EngineType ET, typename... Egs>
  ui::Screen& EngineDispatcher<ET, Egs...>::selector_screen() noexcept
  {
    return *_selector_screen;
  }

  template<EngineType ET, typename... Egs>
  const foonathan::array::flat_map<std::string_view, nlohmann::json>&
  EngineDispatcher<ET, Egs...>::data_of_engines() const noexcept
  {
    return _engine_data;
  }

  template<EngineType ET, typename... Egs>
  nlohmann::json EngineDispatcher<ET, Egs...>::to_json() const
  {
    nlohmann::json j = nlohmann::json::object();
    j["current_engine"] = current().name();
    auto engines = nlohmann::json::object();
    for (auto&& [key, val] : _engine_data) {
      engines[std::string(key)] = val;
    }
    if (_current != &_null_engine) engines[std::string(_current->name())] = _current->to_json();
    j["engines"] = engines;
    return j;
  }

  template<EngineType ET, typename... Egs>
  void EngineDispatcher<ET, Egs...>::from_json(const nlohmann::json& j)
  {
    auto engines = j.find("engines");
    if (engines != j.end() && engines->is_object()) {
      for (auto&& [key, val] : (*engines).items()) {
        _engine_data.insert_or_replace(key, val);
      }
    }
    select(j["current_engine"].get<std::string_view>());
  }
} // namespace otto::core::engine

// kak: other_file=engine_dispatcher.hpp
