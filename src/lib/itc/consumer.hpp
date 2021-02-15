#pragma once

#include "lib/util/concepts.hpp"
#include "lib/util/spin_lock.hpp"

#include "channel.hpp"
#include "domain.hpp"
#include "executor.hpp"
#include "state.hpp"

namespace otto::itc {
  // Declarations
  template<AState State>
  struct Consumer<State> : private virtual IDomain {
    Consumer(TypedChannel<State>& ch) : channel_(&ch)
    {
      ch.internal_add_consumer(this);
    }

    Consumer(ChannelGroup& channels) : Consumer(channels.get<State>()) {}

    Consumer(const Consumer&) = delete;
    Consumer& operator=(const Consumer&) = delete;

    virtual ~Consumer() noexcept
    {
      if (channel_) std::erase(channel_->consumers_, this);
      // Wait for queued functions to be executed
      // virtual functions dont exist at this point anymore,
      // so we have to do this weird caching of the executor
      // If it's still nullptr, internal_commit was never called
      // so no need to sync
      if (exec_ != nullptr) exec_->sync();
    }

    /// The channel this consumer is registered on
    TypedChannel<State>* channel() const noexcept
    {
      return channel_;
    }

    /// Access the newest state available.
    const State& state() const noexcept
    {
      return state_;
    }

    // FOR UNIFORMITY WITH Consumer<State...>

    /// Access the newest state available.
    template<std::same_as<State> S>
    const S& state() const noexcept
    {
      return state();
    }

  protected:
    /// Hook called immediately after the state is updated.
    ///
    /// The parameter is the same as `this->state()`
    ///
    /// Override in subclass if needed
    virtual void on_state_change(const State& state) noexcept {}

  private:
    friend TypedChannel<State>;

    /// Called from {@ref TypedChannel::internal_commit}
    void internal_commit(const State& state)
    {
      {
        std::scoped_lock l(lock_);
        tmp_state_ = state;
      }
      exec_ = &executor();
      exec_->execute([this] {
        // Apply changes
        {
          std::scoped_lock l(lock_);
          state_ = tmp_state_;
        }
        on_state_change(state_);
      });
    }

    IExecutor* exec_ = nullptr;
    util::spin_lock lock_;
    State state_;
    TypedChannel<State>* channel_;
    State tmp_state_;
  };

  template<AState... States>
  struct Consumer : Consumer<States>... {
    Consumer(ChannelGroup& channels) : Consumer<States>(channels)... {}

    template<util::one_of<States...> S>
    const S& state() const noexcept
    {
      return Consumer<S>::state();
    }
  };

} // namespace otto::itc
