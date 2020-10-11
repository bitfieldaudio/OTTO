#pragma once

#include "app/input.hpp"

namespace otto {

  /// InputHandler linked to a logic component
  template<typename Logic>
  struct LinkedInputHandler : InputHandler {
    LinkedInputHandler(Logic& l) : logic(l) {}

    auto produce(auto&&... actions) requires requires(Logic& l)
    {
      l.produce(FWD(actions)...);
    }
    {
      return logic.produce(FWD(actions)...);
    }

    auto update(auto&&... funcs) requires requires(Logic& l)
    {
      l.update(FWD(funcs)...);
    }
    {
      return logic.update(FWD(funcs)...);
    }

    auto& state() const noexcept //
      requires requires(Logic& l)
    {
      l.state();
    }
    {
      return logic.state();
    }

    template<typename T>
    auto& state() const noexcept //
      requires requires(Logic& l)
    {
      l.template state<T>();
    }
    {
      return logic.template state<T>();
    }

  protected:
    Logic& logic;
  };
} // namespace otto
