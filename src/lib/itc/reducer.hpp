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
      virtual void reduce(Event, State&) noexcept = 0;
      void handle(Event e) noexcept final
      {
        auto& producer = *static_cast<Derived*>(this)->producer_;
        reduce(e, producer.state());
        producer.commit();
      }
    };
  } // namespace detail

  /// An event handler linked to a producer.
  ///
  /// Instead of overriding `handle(Event)`, you override `reduce(Event, State&)`, and
  /// modify the state in there.
  ///
  /// The state will automatically be committed after each `reduce` call
  template<AState State, AnEvent... Events>
  struct Reducer : detail::ReducerImpl<Reducer<State, Events...>, State, Events>... {
    using detail::ReducerImpl<Reducer, State, Events>::reduce...;
    using detail::ReducerImpl<Reducer, State, Events>::handle...;

    Reducer() noexcept = default;
    Reducer(Producer<State>& p) noexcept : producer_(&p) {}
    Reducer(itc::ChannelGroup& chan) noexcept : producer_(chan.get<State>().producer()) {}

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
