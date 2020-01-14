#pragma once

#include <any>
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

  namespace detail {
    template<typename Action>
    struct VirtualActionReceiverBase;
    template<typename Tag, typename... Args>
    struct VirtualActionReceiverBase<Action<Tag, Args...>> {
      virtual void action(Action<Tag, Args...>, Args...) = 0;
    };
  } // namespace detail

  /// Base class for receivers to type erase action handlers
  template<typename... Actions>
  struct VirtualActionReceiver : detail::VirtualActionReceiverBase<Actions>... {};

  namespace detail {
    template<typename Action>
    struct DynamicActionSenderBase;
    template<typename Tag, typename... Args>
    struct DynamicActionSenderBase<Action<Tag, Args...>> {
      template<typename Sender>
      DynamicActionSenderBase(Sender& sender)
      {
        caller = [](std::any* sender, ActionData<Action<Tag, Args...>>&& data) {
          std::any_cast<std::decay_t<Sender>>(sender)->push(std::move(data));
        };
      }

      util::function_ptr<void(std::any* sender, ActionData<Action<Tag, Args...>>&& data)> caller;
    };
  } // namespace detail


  /// Type erased sender of multiple actions
  template<typename... Actions>
  struct DynamicActionSender : private detail::DynamicActionSenderBase<Actions>... {
    template<typename Sender>
    DynamicActionSender(const Sender& s) : detail::DynamicActionSenderBase<Actions>(s)...
    {
      sender = std::make_any<Sender>(s);
    }

    template<typename Tag,
             typename... Args,
             typename = std::enable_if_t<util::is_one_of_v<Action<Tag, Args...>, Actions...>>>
    void push(ActionData<Action<Tag, Args...>> data)
    {
      detail::DynamicActionSenderBase<Action<Tag, Args...>>::caller(&sender, std::move(data));
    }

  private:
    std::any sender;
  };
} // namespace otto::itc
