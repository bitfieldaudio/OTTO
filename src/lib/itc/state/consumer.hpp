#pragma once

#include "lib/util/concepts.hpp"
#include "lib/util/spin_lock.hpp"

#include "../domain.hpp"
#include "../services/accessor.hpp"
#include "state.hpp"

namespace otto::itc {
  // Declarations
  template<AState State>
  struct Consumer<State> : private virtual IDomain, Accessor<state_service<State>> {
    Consumer(Context& ctx) : Accessor<state_service<State>>(ctx) {}

    Consumer(const Consumer&) = delete;
    Consumer& operator=(const Consumer&) = delete;

    virtual ~Consumer() noexcept
    {
      this->unregister();
      // Wait for queued functions to be executed
      // virtual functions dont exist at this point anymore,
      // so we have to do this weird caching of the executor
      // If it's still nullptr, internal_send was never called
      // so no need to sync
      if (exec_ != nullptr) exec_->sync();
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
    friend Producer<State>;

    /// Called from {@ref TypedChannelLeaf::internal_commit}
    void internal_commit(const State& state) noexcept
    {
      if (exec_ == nullptr) {
        exec_ = &executor();
      }
      {
        std::scoped_lock l(lock_);
        tmp_state_ = state;
      }
      exec_->execute([this] {
        // Apply changes
        {
          std::scoped_lock l(lock_);
          state_ = std::move(tmp_state_);
        }
        on_state_change(state_);
      });
    }

    util::spin_lock lock_;
    State state_;
    State tmp_state_;
    IExecutor* exec_ = nullptr;
  };

  template<AState... States>
  struct Consumer : Consumer<States>... {
    Consumer(Context& ctx) : Consumer<States>(ctx)... {}

    template<util::one_of<States...> S>
    const S& state() const noexcept
    {
      return Consumer<S>::state();
    }
  };

} // namespace otto::itc
