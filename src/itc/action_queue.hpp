#pragma once


#include <deque>
#include <queue>
#include <tuple>

#include "action.hpp"
#include "util/spin_lock.hpp"
#include "util/type_traits.hpp"
#include "util/utility.hpp"

namespace otto::itc {

  /// A queue one can push actionData/receiver pairs to to have the receiver called on another thread
  ///
  /// @TODO Implement as a lock-free thread safe queue
  /// @TODO Implement using a fixed size std::function alternative.
  struct ActionQueue {
    using value_type = std::function<void()>;

    ActionQueue() = default;

    int size() const noexcept
    {
      return queue_.size();
    }

    bool empty() const noexcept
    {
      return queue_.empty();
    }

    /// Push a function to the queue
    ///
    /// This is completely separate from actions, and just allows you to run any old function on the other thread
    void push(const value_type& v) noexcept
    {
      lock_.lock();
      queue_.push(v);
      lock_.unlock();
      if (on_available_) on_available_();
    }

    /// Pop a function off the queue and return it
    value_type pop() noexcept
    {
      lock_.lock();
      auto res = queue_.front();
      queue_.pop();
      lock_.unlock();
      return res;
    }

    /// Pop a function off the queue and call it
    void pop_call() noexcept
    {
      pop()();
    }

    /// Pop all functions off the queue and call them
    void pop_call_all() noexcept
    {
      lock_.lock();
      while (queue_.size() > 0) {
        queue_.front()();
        queue_.pop();
      }
      lock_.unlock();
    }

    void on_available(std::function<void()> handler) noexcept
    {
      on_available_ = handler;
    }

  private:
    std::function<void()> on_available_;

    util::spin_lock lock_;
    std::queue<value_type, std::deque<value_type>> queue_;
  };
} // namespace otto::itc
