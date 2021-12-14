#pragma once

#include "itc.hpp"

namespace otto {
  template<typename T>
  concept AnEvent = std::copyable<T>;

  template<typename... Events>
  requires(AnEvent<std::decay_t<Events>>&&...) //
    struct IEventHandler : virtual IEventHandler<Events>... {
    using IEventHandler<Events>::handle...;
    using variant = std::variant<std::decay_t<Events>...>;

    void handle(variant& evt) noexcept
    {
      std::visit([this](auto&& evt) { this->handle(evt); }, evt);
    }
    void handle(variant&& evt) noexcept
    {
      std::visit([this](auto&& evt) { this->handle(evt); }, std::move(evt));
    }
  };

  template<typename Event>
  requires(AnEvent<std::decay_t<Event>>) //
    struct IEventHandler<Event> {
    virtual ~IEventHandler() = default;
    /// Handle the event
    virtual void handle(Event) noexcept = 0;
  };


  /// CRTP Base class for event handler proxies
  /// ```cpp
  /// struct SomeProxy : EventHandlerProxy<KeyPress, KeyRelease>, IEventHandler {
  ///   IEventHandler<KeyPress, KeyRelease>& proxy_target() {
  ///     return /* the actual event handler */;
  ///   }
  /// };
  /// ```
  template<typename Derived, typename... Events>
  struct EventHandlerProxy : EventHandlerProxy<Derived, Events>... {
    using EventHandlerProxy<Derived, Events>::handle...;
  };

  template<typename Derived, typename Event>
  struct EventHandlerProxy<Derived, Event> : virtual IEventHandler<Event> {
    void handle(Event e) noexcept final
    {
      static_cast<Derived*>(this)->proxy_target().handle(e);
    }
  };

} // namespace otto

namespace otto::itc {

  namespace detail {
    template<typename Derived, AState State, AnEvent Event>
    struct ReducerImpl : virtual IEventHandler<Event> {
      virtual void reduce(Event, State&) noexcept = 0;
      void handle(Event e) noexcept final
      {
        auto* producer = static_cast<Producer<State>*>(static_cast<Derived*>(this));
        producer->commit([&](State& state) { reduce(e, state); });
      }
    };
  } // namespace detail

  /// An event handler with an internal producer.
  ///
  /// Instead of overriding `handle(Event)`, you override `reduce(Event, State&)`, and
  /// modify the state in there.
  ///
  /// The state will automatically be committed after each `reduce` call
  template<AState State, AnEvent... Events>
  struct Reducer : Producer<State>, detail::ReducerImpl<Reducer<State, Events...>, State, Events>... {
    using detail::ReducerImpl<Reducer, State, Events>::reduce...;
    using detail::ReducerImpl<Reducer, State, Events>::handle...;

    Reducer(itc::Context& ctx) noexcept : Producer<State>(ctx) {}
  };
} // namespace otto::itc
