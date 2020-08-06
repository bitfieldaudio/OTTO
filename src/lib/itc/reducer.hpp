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

      void handle(const Event& event) noexcept final
      {
        // A more sane implementation would have ReducerImpl be a friend of Reducer,
        // and implement the actual function here. However, GCC 10.1 seems to have a bug
        // regarding constrained, templated friends.
        static_cast<Derived*>(this)->handle(event);
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

    void handle(const util::one_of<Events...> auto& event) noexcept
    {
      auto new_state = this->reduce(state_, event);
      if (new_state == state_) return;
      state_ = new_state;
      this->produce(state_);
    }

  private:
    State state_;
  };

} // namespace otto::lib::itc
