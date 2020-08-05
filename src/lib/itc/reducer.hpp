#pragma once
#include "itc.hpp"

namespace otto::lib::itc {

  template<typename T>
  concept AnEvent = true;

  template<AnEvent... Events>
  struct IEventHandler : IEventHandler<Events>... {
    using IEventHandler<Events>::handle...;
  };

  template<AnEvent Event>
  struct IEventHandler<Event> {
    /// Handle the event
    virtual void handle(const Event&) noexcept = 0;
  };

  namespace detail {
    template<typename Derived, AState State, AnEvent Event>
    struct ReducerImpl : IEventHandler<Event> {
      virtual State reduce(State state, const Event& event) noexcept = 0;

      void handle(const Event& event) noexcept final {
        auto& derived = *static_cast<Derived*>(this);
        auto new_state = derived.reduce(derived.state_, event);
        if (new_state == derived.state_) return;
        derived.state_ = new_state;
        derived.produce(derived.state_);
      }
    };
  } // namespace detail

  /// A {@ref Producer} that handles events of multiple types and produces new state
  /// 
  /// This is a functional pattern used in many modern frameworks, most famously
  /// redux.
  /// 
  /// A class extends `Reducer`, and overrides `reduce` for each event type.
  /// `reduce` is the only way to produce  new states with this class.
  template<AState State, AnEvent... Events>
  struct Reducer : private Producer<State>, detail::ReducerImpl<Reducer<State, Events...>, State, Events>... {
    using Producer<State>::Producer;

    /// Take the old state and an event and produce a new state
    using detail::ReducerImpl<Reducer, State, Events>::reduce...;
    using detail::ReducerImpl<Reducer, State, Events>::handle...;

  private:
    template<typename D, AState S, AnEvent E>
    friend struct detail::ReducerImpl;
    State state_;
  };

} // namespace otto::itc
