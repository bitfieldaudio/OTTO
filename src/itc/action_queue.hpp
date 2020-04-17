#pragma once


#include <deque>
#include <queue>
#include <tuple>

#include "action.hpp"
#include "util/spin_lock.hpp"
#include "util/type_traits.hpp"
#include "util/utility.hpp"

namespace otto::itc {

  /// The push-only interface of an {@ref ActionQueue}.
  ///
  /// Queue-owners can expose a reference to this to make sure the internal pop functions aren't
  /// callable from the outside.
  ///
  /// @TODO Implement as a lock-free thread safe queue
  /// @TODO Implement using a fixed size std::function alternative.
  struct PushOnlyActionQueue {
    using value_type = std::function<void()>;

    virtual ~PushOnlyActionQueue() = default;

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
    ///
    /// @TODO Consider, should this be removed from the interface?
    void push(const value_type& v) noexcept
    {
      lock_.lock();
      queue_.push(v);
      lock_.unlock();
    }

  protected:
    PushOnlyActionQueue() = default;

    util::spin_lock lock_;
    std::queue<value_type, std::deque<value_type>> queue_;
  };

  /// A queue one can push actionData/receiver pairs to to have the receiver called on another thread
  struct ActionQueue : PushOnlyActionQueue {
    using value_type = PushOnlyActionQueue::value_type;

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
  };
} // namespace otto::itc
