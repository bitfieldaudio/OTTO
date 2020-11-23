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

    /// Produce one or more actions, and send them on the channel to be applied on all
    /// consumers.
    ///
    /// When producing multiple actions, they will be aggregated into one, and applied atomically.
    void produce(BitSet<State> changes)
    {
      for_each_changed(state(), changes, [this](auto member) {
        auto f = [val = reflect::get(member, state())](State& s) {
          reflect::get(decltype(member)(), s) = std::move(val);
        };
        for (auto* chan : channels_) chan->internal_produce(f);
      });
      for (auto* chan : channels_) chan->internal_notify(changes);
    }

    void produce(reflect::AMember auto&&... members)
    {
      BitSet<State> bitset;
      (bitset.set(reflect::flat_idx(members)), ...);
      produce(bitset);
    }

    void produce(Updater<State>&& u)
    {
      produce(u.bitset());
    }

    void produce(Updater<State>& u)
    {
      produce(u.bitset());
      u.bitset().reset();
    }

    State& state() noexcept
    {
      return state_;
    }

    State& state() const noexcept
    {
      return state_;
    }

    Updater<State> make_updater() noexcept
    {
      return {state()};
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

    template<util::one_of<States...> S>
    S& state() noexcept
    {
      return Producer<S>::state();
    }

    template<util::one_of<States...> S>
    const S& state() const noexcept
    {
      return Producer<S>::state();
    }

    template<util::one_of<States...> S>
    auto make_updater() noexcept
    {
      return Producer<S>::make_updater();
    }

    using Producer<States>::produce...;
  };

} // namespace otto::itc
