#pragma once

#include <functional>
#include <tuple>

#include "util/macros.hpp"

namespace otto::itc {

  /// A tagged tuple of an actions arguments
  template<typename Action>
  struct ActionData {
    using args_tuple = typename Action::args_tuple;
    args_tuple args;
  };

  /// An Action is a statically-dispatched signal to one or more recievers.
  template<typename Tag, typename... Args>
  struct Action {
    using args_tuple = std::tuple<Args...>;
    /// Construct an @ref ActionData object  for this action
    static auto data(Args... args)
    {
      return ActionData<Action<Tag, Args...>>{args_tuple(args...)};
    }
  };

  /// Concept: `ActionReciever::is<AR, Action>` is true if `AR` has a reciever for `Action`.
  ///
  /// I.e. `call_reciever(AR, Action)` is valid, i.e. `AR` implements an `action(Action, Args...)` member function
  struct ActionReciever {
  private:
    static constexpr auto _is(...) -> std::false_type;
    template<
      typename T,
      typename Tag,
      typename... Args,
      typename = std::void_t<decltype(std::declval<T>().action(Action<Tag, Args...>(), std::declval<Args>()...))>>
    static constexpr auto _is(T&&, Action<Tag, Args...>) -> std::true_type;

  public:
    template<typename T, typename Action>
    static constexpr bool is = decltype(_is(std::declval<T>(), std::declval<Action>()))::value;
  };

  /// Calls the correct `action` function in an `ActionReciever` with the given `action_data`
  ///
  /// Does not compile if `AR` has no reciever for the given action
  template<typename AR, typename Tag, typename... Args>
  auto call_reciever(AR&& ar, ActionData<Action<Tag, Args...>> action_data)
    -> std::enable_if_t<ActionReciever::is<AR, Action<Tag, Args...>>>
  {
    static_assert(ActionReciever::is<AR, Action<Tag, Args...>>);
    std::apply([](auto&& ar, auto&&... args) { FWD(ar).action(FWD(args)...); },
               std::tuple_cat(std::forward_as_tuple<AR>(ar), std::tuple<Action<Tag, Args...>>(), action_data.args));
  }

  /// Calls the correct `action` function in an `ActionReciever` with the given `action_data`, if such a function exists
  ///
  /// @return `true` if `AR` has a reciever for the action and that action has been called. `false` otherwise.
  template<typename AR, typename Tag, typename... Args>
  bool try_call_reciever(AR&& ar, ActionData<Action<Tag, Args...>> action_data)
  {
    if constexpr (ActionReciever::is<AR, Action<Tag, Args...>>) {
      std::apply([](auto&& ar, auto&&... args) { FWD(ar).action(FWD(args)...); },
                 std::tuple_cat(std::forward_as_tuple<AR>(ar), std::tuple<Action<Tag, Args...>>(), action_data.args));
      return true;
    }
    return false;
  }

} // namespace otto::itc
