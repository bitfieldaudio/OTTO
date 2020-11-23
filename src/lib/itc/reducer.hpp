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

} // namespace otto

namespace otto::itc {

  namespace detail {
    template<typename Derived, AState State, AnEvent Event>
    struct ReducerImpl : virtual IEventHandler<Event> {
      virtual void reduce(Event, Updater<State> updater) noexcept = 0;
      void handle(Event e) noexcept final
      {
        auto& producer = *static_cast<Derived*>(this)->producer_;
        Updater<State> updater = {producer.state()};
        reduce(e, updater);
        producer.produce(updater.bitset());
      }
    };
  } // namespace detail

  template<AState State, AnEvent... Events>
  struct Reducer : detail::ReducerImpl<Reducer<State, Events...>, State, Events>... {
    using detail::ReducerImpl<Reducer, State, Events>::reduce...;
    using detail::ReducerImpl<Reducer, State, Events>::handle...;

    Reducer() noexcept = default;
    Reducer(Producer<State>& p) noexcept : producer_(&p) {}

  private:
    template<AState S, AnEvent... Es>
    friend void set_producer(Reducer<S, Es...>& r, Producer<S>& p);

    template<typename Derived, AState, AnEvent>
    friend struct detail::ReducerImpl;
    Producer<State>* producer_ = nullptr;
  };

  template<AState State, AnEvent... Events>
  void set_producer(Reducer<State, Events...>& r, Producer<State>& p)
  {
    r.producer_ = &p;
  }

} // namespace otto::itc
