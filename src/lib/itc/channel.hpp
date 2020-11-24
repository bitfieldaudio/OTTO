#pragma once

#include <vector>

#include "lib/util/concepts.hpp"

#include "state.hpp"

namespace otto::itc {

  /// Any type convertible to all of Channel<States>&...
  template<typename T, typename... States>
  concept AChannelFor = (AState<States> && ...) && (std::is_convertible_v<T&, Channel<States>&> && ...);

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

    void internal_commit(const State& state)
    {
      for (auto* cons : consumers_) cons->internal_commit(state);
    }

    std::vector<Consumer<State>*> consumers_;
    Producer<State>* producer_ = nullptr;
  };

  template<AState... States>
  struct Channel : Channel<States>... {};

} // namespace otto::itc
