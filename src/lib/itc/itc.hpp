#pragma once

#include <functional>
#include <vector>

#include "lib/util/concepts.hpp"
#include "lib/meta.hpp"

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
  concept AState = std::regular<T> && !detail::is_meta_list<T>::value;

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
    void internal_produce(const State& s)
    {
      for (auto* cons : consumers_) cons->internal_produce(s);
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

  protected:
    /// Produce a new state
    /// 
    /// Sends the state to all attached channels, to be sent to all consumers
    /// registered on said channels.
    void produce(const State& s)
    {
      for (auto* chan : channels_) {
        chan->internal_produce(s);
      }
    }

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
    Consumer(IExecutor& executor, Channel<State>& ch) : executor_(executor), channel_(&ch)
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
    /// Hook called with the new state right before the state is updated
    ///
    /// In this hook, the old state is available through the {@ref state()} member function
    /// Override in subclass if needed
    virtual void on_new_state(const State& s) {}

  private:
    friend Channel<State>;

    /// Called from {@ref Channel::internal_produce}
    void internal_produce(const State& s)
    {
      executor_.execute([this, s] {
        on_new_state(s);
        state_ = std::move(s);
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
    Consumer(IExecutor& ex, Ch& channel) : Consumer<States>(ex, channel)...
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

} // namespace otto::itc
