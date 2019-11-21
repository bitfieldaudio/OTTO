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

  template<typename... AQHs>
  struct JoinedActionSender {
    template<typename Val, typename Tag, typename... Mixins>
    using Prop = ActionProp<JoinedActionSender<AQHs...>, Val, Tag, Mixins...>;

    JoinedActionSender(AQHs... sndrs) : sndrs_{std::forward<AQHs>(sndrs)...} {}

    template<typename Tag, typename... Args>
    void push(ActionData<Action<Tag, Args...>> action_data)
    {
      util::tuple_for_each(sndrs_, [&action_data](auto& sndr) { sndr.push(action_data); });
    }

  private:
    std::tuple<AQHs...> sndrs_;
  };

} // namespace otto::core::itc
