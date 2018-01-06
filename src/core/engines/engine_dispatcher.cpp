#include "engine_dispatcher.hpp"

#include "engine_selector_screen.hpp"

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
  std::vector<EnginePatch> EngineDispatcher<ET>::make_patches() const
  {
    std::vector<EnginePatch> res;
    res.reserve(_engines.size());
    util::transform(_engines, std::back_inserter(res),
                    [](auto&& eptr) { return eptr->make_patch(); });
    return res;
  }

  template<EngineType ET>
  Engine<ET>& EngineDispatcher<ET>::apply_patch(const EnginePatch& patch)
  {
    if (patch.type != type) {
      throw exception(ErrorCode::type_mismatch);
    }
    auto iter = util::find_if(
      _engines, [&patch](auto&& eptr) { return eptr->name() == patch.name; });
    if (iter == _engines.end()) {
      throw exception(ErrorCode::engine_not_found);
    }
    (*iter)->from_json(patch.data);
    return **iter;
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

  // Explicit instantiations
  // If you need an EngineDispatcher for any other engine type, add it here
  template struct EngineDispatcher<EngineType::synth>;
  template struct EngineDispatcher<EngineType::drums>;
  template struct EngineDispatcher<EngineType::effect>;

} // namespace otto::engines
