#pragma once

#include "itc.hpp"

namespace otto {
  template<typename T>
  concept AnEvent = std::copyable<T>;

  template<AnEvent... Events>
  struct IEventHandler : IEventHandler<Events>... {
    using IEventHandler<Events>::handle...;
  };

  template<AnEvent Event>
  struct IEventHandler<Event> {
    virtual ~IEventHandler() = default;
    /// Handle the event
    virtual void handle(const Event&) noexcept = 0;
  };
} // namespace otto

namespace otto::itc {

  namespace detail {
    template<typename Derived, AState State, AnEvent Event>
    struct ReducerImpl : IEventHandler<Event> {
      void reduce(Event, ProduceFunc<State> produce) noexcept = 0;
      void handle(Event e) noexcept final
      {
        reduce(e, itc::produce_func(static_cast<Derived*>(this)->producer_));
      }
    };
  } // namespace detail

  template<AState State, AnEvent... Events>
  struct Reducer : detail::ReducerImpl<Reducer<State, Events...>, State, Events>... {
    using detail::ReducerImpl<Reducer, State, Events>::reduce...;
    using detail::ReducerImpl<Reducer, State, Events>::handle...;

    Reducer(Producer<State>& p) noexcept : producer_(p) {}

  private:
    template<typename Derived, AState, AnEvent>
    friend struct detail::ReducerImpl;
    Producer<State>& producer_;
  };

} // namespace otto::itc
