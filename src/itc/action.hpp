#pragma once

#include <functional>
#include <tuple>

#include "services/log_manager.hpp"
#include "testing.t.hpp"
#include "util/macros.hpp"
#include "util/meta.hpp"
#include "util/type_traits.hpp"

namespace otto::itc {

  /// A tagged tuple of an actions arguments
  template<typename Action>
  struct ActionData {
    using args_tuple = typename Action::args_tuple;
    args_tuple args;
  };

  /// An Action is a statically-dispatched signal to one or more receivers.
  template<typename Tag, typename... Args>
  struct Action {
    using args_tuple = std::tuple<Args...>;
    /// Construct an @ref ActionData object  for this action
    static auto data(Args... args)
    {
      return ActionData<Action<Tag, Args...>>{args_tuple(args...)};
    }
  };

  namespace detail {
    template<typename T, bool HasDirectConversion = std::is_reference_v<T>>
    struct no_implicits {
      template<typename T2, typename = std::enable_if_t<std::is_same_v<T, T2>>>
      operator T2();
    };
    template<typename T>
    struct no_implicits<T, true> {
      operator T();
    };
  } // namespace detail

  /// Concept: `ActionReceiver::is<AR, Action>` is true if `AR` has a receiver for
  /// `Action`.
  ///
  /// I.e. `call_receiver(AR, Action)` is valid, i.e. `AR` implements an
  /// `action(Action, Args...)` member function
  class ActionReceiver {
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

  namespace detail {
    template<size_t>
    struct arbitrary_t {
      // this type casts implicitly to anything,
      // thus, it can represent an arbitrary type.
      template<typename T>
      operator T&&();

      template<typename T>
      operator T&();
    };

    template<typename T,
             typename Action,
             size_t... Is,
             typename = std::void_t<decltype(std::declval<T>().action(Action(), arbitrary_t<Is>()...))>>
    auto check_action_with_n_args(std::index_sequence<Is...>) -> std::true_type
    {
      return {};
    }

    template<typename T, typename Action, size_t I, typename = std::enable_if_t<(I >= 0)>>
    auto iar_impl(int) -> decltype(check_action_with_n_args<T, Action>(std::make_index_sequence<I>()))
    {
      return {};
    }

    template<typename T, typename Action, size_t I>
    auto iar_impl(...)
    {
      if constexpr (I > 0) {
        return iar_impl<T, Action, I - 1>(0);
      } else {
        return std::false_type();
      }
    }

  } // namespace detail
  template<typename Tag>
  constexpr std::string_view get_type_name()
  {
    std::string_view func_name = __PRETTY_FUNCTION__;
#ifdef __clang__
    std::string_view prefix = "[Tag = ";
    std::string_view end_chars = "]";
#elif defined(__GNUC__) && __GNUC__ >= 9
    std::string_view prefix = "[with Tag = ";
    std::string_view end_chars = ";]";
#else
#warning cannot get action name on this compiler
#endif
    // Do this manually since std::string_view::find() is not constexpr with clang + libstdc++
    for (int i = 0; i < func_name.size() - prefix.size(); i++) {
      if (func_name.substr(i, prefix.size()) == prefix) {
        func_name = func_name.substr(i + prefix.size());
        break;
      }
    }
    for (int i = 0; i < func_name.size(); i++) {
      for (auto& c : end_chars) {
        if (func_name[i] == c) {
          func_name = func_name.substr(0, i);
        }
      }
    }
    return func_name;
  }

  // Test get_type_name
  static_assert(get_type_name<int>() == "int",
                "get_type_name works using some compiler hacks, and appears to not work on this compiler");

  /// Concept: `InvalidActionReceiver::is<AR, Action>` is true if `AR` has an
  /// invalid receiver for `Action`.
  ///
  /// An invalid receiver is a function called `action`, which takes `Action` as
  /// the first parameter, but not the correct arguments afterwards.
  class InvalidActionReceiver {
    template<typename T, typename Tag, typename... Args>
    static constexpr auto _is(T&&, Action<Tag, Args...>)
    {
      return detail::iar_impl<T, Action<Tag, Args...>, 2>(0);
    }

  public:
    template<typename T, typename Action>
    static constexpr bool is = !ActionReceiver::is<T, Action> &&
                               decltype(InvalidActionReceiver::_is(std::declval<T>(), std::declval<Action>()))::value;
  };

  /// Calls the correct `action` function in an `ActionReceiver` with the given
  /// `action_data`
  ///
  /// Does not compile if `AR` has no receiver for the given action
  template<typename AR, typename Tag, typename... Args>
  auto call_receiver(AR&& ar, ActionData<Action<Tag, Args...>> action_data)
    -> std::enable_if_t<ActionReceiver::is<AR, Action<Tag, Args...>>>
  {
    DLOGI("Action {} received by {}, args: {}", get_type_name<Tag>(), get_type_name<std::decay_t<AR>>(),
          doctest::StringMaker<std::tuple<Args...>>::convert(action_data.args).c_str());
    static_assert(ActionReceiver::is<AR, Action<Tag, Args...>>);
    std::apply([](auto&& ar, auto&&... args) { FWD(ar).action(FWD(args)...); },
               std::tuple_cat(std::forward_as_tuple<AR>(ar), std::tuple<Action<Tag, Args...>>(), action_data.args));
  }

  /// Calls the correct `action` function in an `ActionReceiver` with the given
  /// `action_data`, if such a function exists
  ///
  /// @return `true` if `AR` has a receiver for the action and that action has
  /// been called. `false` otherwise.
  template<typename AR, typename Tag, typename... Args>
  bool try_call_receiver(AR&& ar, ActionData<Action<Tag, Args...>> action_data)
  {
    static_assert(!InvalidActionReceiver::is<AR, Action<Tag, Args...>>,
                  "The ActionReceiver (AR) has an invalid action receiver for "
                  "the given action");
    if constexpr (ActionReceiver::is<AR, Action<Tag, Args...>>) {
      DLOGI("Action {} received by {}, args: {}", get_type_name<Tag>(), get_type_name<std::decay_t<AR>>(),
            doctest::StringMaker<std::tuple<Args...>>::convert(action_data.args).c_str());
      std::apply([](auto&& ar, auto&&... args) { FWD(ar).action(FWD(args)...); },
                 std::tuple_cat(std::forward_as_tuple<AR>(ar), std::tuple<Action<Tag, Args...>>(), action_data.args));
      return true;
    }
    return false;
  }

} // namespace otto::itc
