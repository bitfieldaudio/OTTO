#pragma once


#include <deque>
#include <queue>
#include <tuple>

#include "util/type_traits.hpp"
#include "util/utility.hpp"

#include "action.hpp"

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

  protected:
    PushOnlyActionQueue() = default;

    std::queue<value_type, std::deque<value_type>> queue_;
  };

  /// A queue one can push actionData/reciever pairs to to have the reciever called on another thread
  struct ActionQueue : PushOnlyActionQueue {
    using value_type = PushOnlyActionQueue::value_type;

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
  };

  // FORWARD DECLARATION
  template<typename Aqh, typename Tag, typename Val, typename... Mixins>
  struct ActionProp;

  /// A class to help enqueue actions for a list of recievers
  ///
  /// Currently only supports one reciever of each type, which shouldn't be a problem.
  template<typename... Recievers>
  struct ActionQueueHelper {
    template<typename Val, typename Tag, typename... Mixins>
    using Prop = ActionProp<ActionQueueHelper<Recievers...>, Val, Tag, Mixins...>;

    /// Does not own the queue, and does not own the recievers.
    ActionQueueHelper(PushOnlyActionQueue& queue, Recievers&... r) : queue_(queue), recievers_(r...) {}

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
    PushOnlyActionQueue& queue_;
    std::tuple<Recievers&...> recievers_;
  };

  template<typename... AQHs>
  struct JoinedActionQueueHelper {
    template<typename Val, typename Tag, typename... Mixins>
    using Prop = ActionProp<JoinedActionQueueHelper<AQHs...>, Val, Tag, Mixins...>;

    JoinedActionQueueHelper(AQHs... aqhs) : aqhs_{std::forward<AQHs>(aqhs)...} {}

    template<typename Tag, typename... Args>
    void push(ActionData<Action<Tag, Args...>> action_data)
    {
      util::tuple_for_each(aqhs_, [this, &action_data](auto& aqh) { aqh.push(action_data); });
    }

  private:
    std::tuple<AQHs...> aqhs_;
  };

} // namespace otto::itc
