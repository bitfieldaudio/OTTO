#pragma once

#include <functional>
#include <vector>

#include "lib/meta.hpp"
#include "lib/util/concepts.hpp"

#include "executor.hpp"

/// A State-based inter-thread communication library.
///
/// A single `Producer` can send a new `State` object to multiple `Channels`, which in
/// turn pass it on to multiple `Consumers` which receive the state on some `Executor`
///
/// State is intended to be little more than a simple `POD`-style struct, and it is up
/// to the individual consumers to determine which members have actually changed if they
/// require so.
namespace otto::itc {

  namespace detail {
    template<typename T>
    struct is_meta_list : std::false_type {};

    template<typename... Args>
    struct is_meta_list<meta::list<Args...>> : std::true_type {};
  } // namespace detail

  /// The concept that state types need to fulfill.
  template<typename T>
  concept AState = std::semiregular<T> && !detail::is_meta_list<T>::value;

  /// A function that modifies a state
  template<typename T, typename State>
  concept AnAction = util::callable<T, void(State&)>;

  // Forward Declarations

  /// A Channel through which a single Producer can send state to multiple consumers
  template<AState... States>
  struct Channel;

  /// Sends state to multiple Consumers through a Channel
  template<AState... States>
  struct Producer;

  /// Receives state from a single producer through a Channel
  template<AState... States>
  struct Consumer;

  // Declarations

  template<AState State>
  struct Channel<State> {
    Channel() noexcept {}
    Channel(const Channel&) = delete;
    ~Channel() noexcept
    {
      for (auto* c : consumers_) {
        c->channel_ = nullptr;
      }
      if (producer_) producer_->internal_remove_channel(*this);
    }

    const std::vector<Consumer<State>*>& consumers() const noexcept
    {
      return consumers_;
    }

    Producer<State>* producer() const noexcept
    {
      return producer_;
    }

    /// Set the producer for this channel
    ///
    /// Can be `nullptr` to clear the current producer
    void set_producer(Producer<State>* p) noexcept
    {
      producer_ = p;
      if (p) p->channels_.emplace_back(this);
    }

    /// Set the producer for this channel
    void set_producer(Producer<State>& p) noexcept
    {
      set_producer(&p);
    }

  protected:
  private:
    friend Producer<State>;
    friend Consumer<State>;

    /// Only called from Consumer constructor
    void internal_add_consumer(Consumer<State>* c)
    {
      consumers_.push_back(c);
    }

    /// Only called from {@ref Producer::produce}
    void internal_produce(AnAction<State> auto& action)
    {
      for (auto* cons : consumers_) cons->internal_produce(action);
    }

    std::vector<Consumer<State>*> consumers_;
    Producer<State>* producer_ = nullptr;
  };

  template<AState State>
  struct Producer<State> {
    Producer(Channel<State>& ch)
    {
      ch.set_producer(this);
    }

    ~Producer() noexcept
    {
      for (auto* ch : channels_) {
        ch->set_producer(nullptr);
      }
    }

    /// The channels this producer is currently linked to
    const std::vector<Channel<State>*>& channels() const noexcept
    {
      return channels_;
    }

    /// Produce one or more actions, and send them on the channel to be applied on all
    /// consumers.
    void produce(AnAction<State> auto&&... actions)
    {
      auto a = [actions...](State& s) { (actions(s), ...); };
      for (auto* chan : channels_) {
        chan->internal_produce(a);
      }
    }

    template<AState... States>
    friend auto produce_func(Producer<States...>& p);

  private:
    friend Channel<State>;

    /// Called only from set_producer in Channel
    void internal_add_channel(Channel<State>& ch)
    {
      channels_.push_back(ch);
    }

    /// Called only from Channel destructor
    void internal_remove_channel(Channel<State>& ch)
    {
      std::erase(channels_, &ch);
    }

    std::vector<Channel<State>*> channels_;
  };

  template<AState State>
  struct Consumer<State> {
    Consumer(Channel<State>& ch, IExecutor& executor) : executor_(executor), channel_(&ch)
    {
      ch.internal_add_consumer(this);
    }

    virtual ~Consumer() noexcept
    {
      if (channel_) std::erase(channel_->consumers_, this);
    }

    /// The channel this consumer is registered on
    Channel<State>* channel() const noexcept
    {
      return channel_;
    }

    /// Access the newest state available.
    const State& state() const noexcept
    {
      return state_;
    }

  protected:
    /// Hook called immediately after the state is updated.
    ///
    /// Gets the new state as a parameter, even though it is also available as
    ///
    /// if you consume multiple states.
    ///
    /// Override in subclass if needed
    virtual void on_state_change(const State& s) noexcept {}

  private:
    friend Channel<State>;

    /// Called from {@ref Channel::internal_produce}
    void internal_produce(AnAction<State> auto& action)
    {
      executor_.execute([this, action] {
        action(state_);
        on_state_change(state_);
      });
    }

    State state_;
    IExecutor& executor_;
    Channel<State>* channel_;
  };

  // Concepts

  /// Any type convertible to all of Channel<States>&...
  template<typename T, typename... States>
  concept AChannelFor = (AState<States> && ...) && (std::is_convertible_v<T&, Channel<States>&> && ...);

  // Definitions for multiple states

  template<AState... States>
  struct Channel : Channel<States>... {};

  template<AState... States>
  struct Consumer : Consumer<States>... {
    template<AChannelFor<States...> Ch>
    Consumer(Ch& channel, IExecutor& ex) : Consumer<States>(channel, ex)...
    {}

    template<util::one_of<States...> S>
    const S& state() const noexcept
    {
      return Consumer<S>::state();
    }
  };

  template<AState... States>
  struct Producer : Producer<States>... {
    template<AChannelFor<States...> Ch>
    Producer(Ch& channel) : Producer<States>(channel)...
    {}

    using Producer<States>::produce...;
  };

  template<AState... States>
  auto produce_func(Producer<States...>& p)
  {
    return [&p](auto&&... actions) { p.produce(FWD(actions)...); };
  }

  template<AState... States>
  using ProduceFunc = decltype(produce_func(std::declval<Producer<States...>&>()));

  // Actions //

  /// Create an action that replaces the entire state struct with new object
  template<AState State>
  auto replace(State s)
  {
    return [s = std::move(s)](State& ref) { ref = std::move(s); };
  }

  /// Create an action that sets a single member
  template<AState State, typename T>
  auto set(T State::*mem_ptr, T val)
  {
    return [val = std::move(val), mem_ptr](State& ref) { ref.*mem_ptr = std::move(val); };
  }

  /// Create an action that increments a member
  template<AState State, typename T, typename U>
  auto increment(T State::*mem_ptr, U val) requires requires(T& t)
  {
    t += val;
  }
  {
    return [val = std::move(val), mem_ptr](State& ref) { ref.*mem_ptr += std::move(val); };
  }

} // namespace otto::itc
