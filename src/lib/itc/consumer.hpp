#pragma once

#include "channel.hpp"
#include "executor.hpp"
#include "state.hpp"

namespace otto::itc {
  // Declarations
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
    /// Check if individual state variable have been changed using `diff`
    ///
    /// Override in subclass if needed
    virtual void on_state_change(Diff<State> diff) noexcept {}

  private:
    friend Channel<State>;

    /// Called from {@ref Channel::internal_produce}
    void internal_produce(AnAction<State> auto& func)
    {
      executor_.execute([this, func] { std::move(func)(tmp_state_); });
    }

    /// Called from {@ref Channel::internal_notify}
    void internal_notify(const BitSet<State>& changes)
    {
      executor_.execute([this, changes] {
        // Apply changes
        state_ = tmp_state_;
        on_state_change(Diff<State>(changes));
      });
    }

    State state_;
    IExecutor& executor_;
    Channel<State>* channel_;
    State tmp_state_;
  };

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

} // namespace otto::itc
