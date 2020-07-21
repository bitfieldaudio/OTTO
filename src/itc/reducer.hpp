#pragma once
#include "itc.hpp"

namespace otto::itc {

  template<typename T>
  concept AnEvent = true;

  namespace detail {
    template<AState State, AnEvent Event>
    struct ReducerImpl {
      virtual State reduce(State state, const Event& event) = 0;
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
  struct Reducer : private Producer<State>, detail::ReducerImpl<State, Events>... {
    using Producer<State>::Producer;

    /// Take the old state and an event and produce a new state
    using detail::ReducerImpl<State, Events>::reduce...;

    /// Handle an event, producing a new state if the state was changed.
    /// 
    /// Called externally
    void handle_event(const util::one_of<Events...> auto& event)
    {
      auto new_state = reduce(state_, event);
      if (new_state == state_) return;
      state_ = new_state;
      this->produce(state_);
    }

  private:
    State state_;
  };

} // namespace otto::itc
