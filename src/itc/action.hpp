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
    using tag_type = Tag;
    using args_tuple = std::tuple<Args...>;
    /// Construct an @ref ActionData object  for this action
    static auto data(Args... args)
    {
      return ActionData<Action<Tag, Args...>>{args_tuple(args...)};
    }
  };

  template<typename... Actions>
  struct ActionReceiver;

  template<typename Tag, typename... Args>
  struct ActionReceiver<Action<Tag, Args...>> {
    using ActionList = meta::list<Action<Tag, Args...>>;
    virtual void action(Action<Tag, Args...>, Args... args) noexcept = 0;
  };

  template<typename... Actions>
  struct ActionReceiver : ActionReceiver<Actions>... {
    using ActionList = meta::concat_t<typename ActionReceiver<Actions>::ActionList...>;
  };

  template<typename... Types>
  struct ActionReceiver<meta::list<Types...>> : ActionReceiver<Types...> {
    using ActionList = typename ActionReceiver<Types...>::ActionList;
  };

  template<typename T, typename Action>
  constexpr bool is_action_receiver_v = std::is_base_of_v<ActionReceiver<Action>, std::decay_t<T>>;

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

} // namespace otto::itc
