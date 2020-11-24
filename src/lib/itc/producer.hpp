#pragma once

#include "channel.hpp"
#include "state.hpp"

namespace otto::itc {

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

    /// Commit the current `state()`, notifying consumers
    void commit()
    {
      for (auto* chan : channels_) chan->internal_commit(state());
    }

    State& state() noexcept
    {
      return state_;
    }

    const State& state() const noexcept
    {
      return state_;
    }

    // FOR UNIFORMITY WITH Producer<State...>

    /// Access the stored state of the given type
    template<std::same_as<State> S>
    S& state() noexcept
    {
      return state();
    }

    /// Access the stored state of the given type
    template<std::same_as<State> S>
    const S& state() const noexcept
    {
      return state();
    }

    /// Commit the current states of the given types, notifying all consumers
    template<std::same_as<State> S>
    void commit() noexcept
    {
      commit();
    }

    void commit_all() noexcept
    {
      commit();
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
    State state_;
  };

  template<AState... States>
  struct Producer : Producer<States>... {
    template<AChannelFor<States...> Ch>
    Producer(Ch& channel) : Producer<States>(channel)...
    {}

    /// Access the stored state of the given type
    template<util::one_of<States...> S>
    S& state() noexcept
    {
      return Producer<S>::state();
    }

    /// Access the stored state of the given type
    template<util::one_of<States...> S>
    const S& state() const noexcept
    {
      return Producer<S>::state();
    }

    /// Commit the current states of the given types, notifying all consumers
    template<util::one_of<States...>... S>
    void commit() noexcept
    {
      (Producer<S>::commit(), ...);
    }

    void commit_all() noexcept
    {
      commit<States...>();
    }
  };

} // namespace otto::itc
