#pragma once


#include <deque>
#include <queue>
#include <tuple>

#include "util/type_traits.hpp"

#include "action.hpp"

namespace otto::core2 {

  /// A queue one can push actionData/reciever pairs to have the reciever called on another thread
  ///
  /// @TODO Implement as a lock-free thread safe queue
  /// @TODO Implement using a fixed size std::function alternative.
  struct ActionQueue {
    using value_type = std::function<void()>;

    int size() const noexcept
    {
      return queue_.size();
    }

    /// Push a call to `call_reciever` to the queue.
    template<typename AR, typename Tag, typename... Args>
    auto push(AR& ar, ActionData<Action<Tag, Args...>> action_data)
      -> std::enable_if_t<ActionReciever::is<AR, Action<Tag, Args...>>>
    {
      push([&ar, action_data] { call_reciever(ar, action_data); });
    }

    /// Push a call to `call_reciever` to the queue, if such a call is valid.
    ///
    /// Returns `true` if `AR` implements a reciever for the action, false otherwise
    template<typename AR, typename Tag, typename... Args>
    bool try_push(AR& ar, ActionData<Action<Tag, Args...>> action_data)
    {
      if constexpr (ActionReciever::is<AR, Action<Tag, Args...>>) {
        push([&ar, action_data] { call_reciever(ar, action_data); });
        return true;
      }
      return false;
    }

    /// Push a function to the queue
    ///
    /// This is completely separate from actions, and just allows you to run any old function on the other thread
    ///
    /// @TODO Consider, should this be removed from the interface?
    void push(const value_type& v)
    {
      queue_.push(v);
    }

    /// Pop a function off the queue and return it
    value_type pop() noexcept
    {
      auto res = queue_.front();
      queue_.pop();
      return res;
    }

    /// Pop a function off the queue and call it
    void pop_call()
    {
      pop()();
    }

    /// Pop all functions off the queue and call them
    void pop_call_all()
    {
      while (size() > 0) {
        pop_call();
      }
    }

  private:
    std::queue<value_type, std::deque<value_type>> queue_;
  };

  /// A class to help enqueue actions for a list of recievers
  ///
  /// Currently only supports one reciever of each type, which shouldn't be a problem.
  template<typename... Recievers>
  struct ActionQueueHelper {
    /// Does not own the queue, and does not own the recievers.
    ActionQueueHelper(ActionQueue& queue, Recievers&... r) : queue_(queue), recievers_(r...) {}

    /// Push an action to be recieved by all recievers that support it
    template<typename Tag, typename... Args>
    void push(ActionData<Action<Tag, Args...>> action_data)
    {
      (queue_.try_push(reciever<Recievers>(), action_data), ...);
    }

    /// Get a reciever of a specific type
    template<typename Reciever>
    auto reciever() noexcept -> std::enable_if_t<util::is_one_of_v<Reciever, Recievers...>, Reciever&>
    {
      return std::get<Reciever&>(recievers_);
    }

  private:
    ActionQueue& queue_;
    std::tuple<Recievers&...> recievers_;
  };

}
