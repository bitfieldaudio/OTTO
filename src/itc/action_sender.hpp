#pragma once

#include "action_queue.hpp"

namespace otto::itc {

  // FORWARD DECLARATION
  template<typename Sndr, typename Tag, typename Val, typename... Mixins>
  struct ActionProp;

  /// A class to help enqueue actions for a list of recievers
  ///
  /// Currently only supports one reciever of each type, which shouldn't be a problem.
  template<typename... Recievers>
  struct ActionSender {
    template<typename Val, typename Tag, typename... Mixins>
    using Prop = ActionProp<ActionSender<Recievers...>, Val, Tag, Mixins...>;

    /// Does not own the queue, and does not own the recievers.
    ActionSender(PushOnlyActionQueue& queue, Recievers&... r) : queue_(queue), recievers_(r...) {}

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

  template<typename... ActionSenders>
  struct JoinedActionSender {
    template<typename Val, typename Tag, typename... Mixins>
    using Prop = ActionProp<JoinedActionSender<ActionSenders...>, Val, Tag, Mixins...>;

    JoinedActionSender(ActionSenders... sndrs) : sndrs_{std::forward<ActionSenders>(sndrs)...} {}

    template<typename Tag, typename... Args>
    void push(ActionData<Action<Tag, Args...>> action_data)
    {
      util::for_each(sndrs_, [&action_data](auto& sndr) { sndr.push(action_data); });
    }

  private:
    std::tuple<ActionSenders...> sndrs_;
  };


  /// Directly-invoking action sender
  /// 
  /// Calls the action handler directly instead of pushing to a queue.
  /// 
  /// @note mainly used for single-threaded testing
  template<typename... Recievers>
  struct DirectActionSender {
    template<typename Val, typename Tag, typename... Mixins>
    using Prop = ActionProp<DirectActionSender<Recievers...>, Val, Tag, Mixins...>;

    DirectActionSender(Recievers&... r) : recievers_(r...) {}

    /// Push an action to be recieved by all recievers that support it
    template<typename Tag, typename... Args>
    void push(ActionData<Action<Tag, Args...>> action_data)
    {
      (try_call_reciever(reciever<Recievers>(), action_data), ...);
    }

    /// Get a reciever of a specific type
    template<typename Reciever>
    auto reciever() noexcept -> std::enable_if_t<util::is_one_of_v<Reciever, Recievers...>, Reciever&>
    {
      return std::get<Reciever&>(recievers_);
    }

  private:
    std::tuple<Recievers&...> recievers_;
  };

} // namespace otto::itc
