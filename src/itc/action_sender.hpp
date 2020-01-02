#pragma once

#include <nanorange.hpp>
#include "action_queue.hpp"

namespace otto::itc {

  // FORWARD DECLARATION
  template<typename Sndr, typename Tag, typename Val, typename... Mixins>
  struct ActionProp;

  /// A class to help enqueue actions for a list of receivers
  ///
  /// Currently only supports one receiver of each type, which shouldn't be a problem.
  template<typename... Receivers>
  struct ActionSender {
    template<typename Val, typename Tag, typename... Mixins>
    using Prop = ActionProp<ActionSender<Receivers...>, Val, Tag, Mixins...>;

    /// Does not own the queue, and does not own the receivers.
    ActionSender(PushOnlyActionQueue& queue, Receivers&... r) : queue_(queue), receivers_(r...) {}

    /// Push an action to be received by all receivers that support it
    template<typename Tag, typename... Args>
    void push(ActionData<Action<Tag, Args...>> action_data)
    {
      (queue_.try_push(receiver<Receivers>(), action_data), ...);
    }

    /// Get a receiver of a specific type
    template<typename Receiver>
    auto receiver() noexcept -> std::enable_if_t<util::is_one_of_v<Receiver, Receivers...>, Receiver&>
    {
      return std::get<Receiver&>(receivers_);
    }

  private:
    PushOnlyActionQueue& queue_;
    std::tuple<Receivers&...> receivers_;
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
  template<typename... Receivers>
  struct DirectActionSender {
    template<typename Val, typename Tag, typename... Mixins>
    using Prop = ActionProp<DirectActionSender<Receivers...>, Val, Tag, Mixins...>;

    DirectActionSender(Receivers&... r) : receivers_(r...) {}

    /// Push an action to be received by all receivers that support it
    template<typename Tag, typename... Args>
    void push(ActionData<Action<Tag, Args...>> action_data)
    {
      (try_call_receiver(receiver<Receivers>(), action_data), ...);
    }

    /// Get a receiver of a specific type
    template<typename Receiver>
    auto receiver() noexcept -> std::enable_if_t<util::is_one_of_v<Receiver, Receivers...>, Receiver&>
    {
      return std::get<Receiver&>(receivers_);
    }

  private:
    std::tuple<Receivers&...> receivers_;
  };

} // namespace otto::itc
