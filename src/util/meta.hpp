#pragma once

#include "util/type_traits.hpp"

#define OTTO_META_ASSERT_EQUAL(...) static_assert(std::is_same_v<__VA_ARGS__>)

/// OTTO Metaprogramming utilities
///
/// ## Metafunctions
/// A metafunction is a struct that takes template arguments, and its "return"
/// value is either a `static constexpr const` member variable named `value` or
/// a memeber type named `type`. These can be accessed using the
/// `meta::_t<Func>` or `meta::_v<Func>` shorthand metavariables.
///
/// ## Metavariables
/// Metavariables are either constexpr variables, or alias declarations, and
/// should be prefixed by an underscore, to indicate that they do not need to be
/// unwrapped using `_t` or `_v` like the metafunctions
///
/// ## Metatypes
/// The center of most metafunctions here is the `list` metatype. This is
/// simply a list of types that can be manipulated using metafunctions like
/// `sort`, `uniquify`, `flatten` etc.
/// There is also `pair` and `one`, which are useful mainly internally in
/// metafunctions
///
/// For more information, take a look at the test file
namespace otto::meta {

  /// Get return type from metafunction
  template<typename MetaFunc>
  using _t = typename MetaFunc::type;

  /// Get return value from metafunction
  template<typename MetaFunc>
  constexpr auto _v = MetaFunc::value;

  /// Get return value from the return type of a metafunction
  template<typename MetaFunc>
  constexpr auto _tv = _v<_t<MetaFunc>>;

  /// List of types. Base for most manipulations here
  template<typename... Args>
  struct list {};

  /// An integral constant value
  template<auto val>
  using c = std::integral_constant<decltype(val), val>;

  /// A list of integral constant values
  template<auto... vals>
  using c_list = list<c<vals>...>;

  /// Pair of types
  template<typename First, typename Second>
  struct pair {
    using first = First;
    using second = Second;
  };

  /// A single type
  ///
  /// Useful when using unevaluated functions to do type computations, to avoid
  /// issues with non-constructible types etc.
  template<typename Type>
  struct one {
    using type = Type;
  };

  /// First element of Pair
  template<typename Pair>
  using _first = typename Pair::first;

  /// Second element of Pair
  template<typename Pair>
  using _second = typename Pair::second;

  /// The default compare metafunction. Overload for user types.
  template<typename T1, typename T2>
  struct compare;

  /// Metafunction to get first element in a list.
  template<typename List>
  struct head;

  /// Metafunction to get everything but the first element in a list.
  template<typename List>
  struct tail;

  /// Metafunction to concattenate lists.
  template<typename... Lists>
  struct concat;

  /// Metafunction to flatten a list of lists.
  template<typename List>
  struct flatten;

  /// Metafunction to see if `List` contains `T`
  template<typename List, typename T>
  struct contains;

  /// Metafunction to make sure every type only exists once in the list.
  ///
  /// Only the first appearance of each type is kept.
  template<typename List>
  struct uniquify;

  /// Partition List around Pivot.
  ///
  /// \tparam List the list to partition
  /// \tparam Pivot the type to partition around.
  /// \tparam Compare a metafunction that compares two types and returns a bool
  /// \returns a pair of lists, where the first one contains all types T for
  /// which `Compare<T, Pivot>` returns true, and the second one where it
  /// returns false.
  template<typename List, typename Pivot, template<class T1, class T2> typename Compare = compare>
  struct partition;

  /// Quicksort a list using the metafunction `Compare`
  ///
  /// \tparam List the list to partition
  /// \tparam Compare a metafunction that compares two types and returns a bool
  template<typename List, template<class T1, class T2> typename Compare = compare>
  struct sort;

  // _t and _v aliases ////////////////////////////////////////////////////////

  /// The default compare metafunction. Overload for user types.
  template<typename T1, typename T2>
  using compare_t = _t<compare<T1, T2>>;

  /// Metafunction to get first element in a list.
  template<typename List>
  using head_t = _t<head<List>>;

  /// Metafunction to get everything but the first element in a list.
  template<typename List>
  using tail_t = _t<tail<List>>;

  /// Metafunction to concattenate lists.
  template<typename... Lists>
  using concat_t = _t<concat<Lists...>>;

  /// Metafunction to flatten a list of lists.
  template<typename List>
  using flatten_t = _t<flatten<List>>;

  /// Metafunction to see if `List` contains `T`
  template<typename List, typename T>
  constexpr const bool contains_v = _v<contains<List, T>>;

  /// Metafunction to make sure every type only exists once in the list.
  ///
  /// Only the first appearance of each type is kept.
  template<typename List>
  using uniquify_t = _t<uniquify<List>>;

  /// Partition List around Pivot.
  ///
  /// \tparam List the list to partition
  /// \tparam Pivot the type to partition around.
  /// \tparam Compare a metafunction that compares two types and returns a bool
  /// \returns a pair of lists, where the first one contains all types T for
  /// which `Compare<T, Pivot>` returns true, and the second one where it
  /// returns false.
  template<typename List, typename Pivot, template<class T1, class T2> typename Compare = compare>
  using partition_t = _t<partition<List, Pivot, Compare>>;

  /// Quicksort a list using the metafunction `Compare`
  ///
  /// \tparam List the list to partition
  /// \tparam Compare a metafunction that compares two types and returns a bool
  template<typename List, template<class T1, class T2> typename Compare = compare>
  using sort_t = _t<sort<List, Compare>>;

  // Normal functions to work with type lists at runtime ///////////////////////

  /// A normal function to call another normal function for each argument
  ///
  /// \param cb will be invoked as `cb(meta::one<T>{})` for each type in `List`
  template<typename List, typename Callable>
  constexpr void for_each(Callable&& cb);

  /// A normal function to call another normal function that transforms a list
  /// of types to a [std::tuple]()
  ///
  /// \param cb will be invoked as `cb(meta::one<T>{})` for each type in `List`,
  /// and its return value will be put in the returned tuple
  template<typename List, typename Callable>
  constexpr auto transform_to_tuple(Callable&& cb);

  // Implementations ////////////////////////////////////////////////////////

  // Compare //

  template<auto I1, auto I2>
  struct compare<c<I1>, c<I2>> {
    constexpr static const bool value = I1 < I2;
  };

  // head //

  template<typename T, typename... Types>
  struct head<list<T, Types...>> {
    using type = T;
  };

  // tail //

  template<typename T, typename... Types>
  struct tail<list<T, Types...>> {
    using type = list<Types...>;
  };

  // concat //

  template<typename TL1, typename... Lists>
  struct concat<TL1, Lists...> {
    using type = _t<concat<TL1, _t<concat<Lists...>>>>;
  };

  template<typename... Args1, typename... Args2>
  struct concat<list<Args1...>, list<Args2...>> {
    using type = list<Args1..., Args2...>;
  };

  template<typename TL>
  struct concat<TL> {
    using type = TL;
  };

  template<>
  struct concat<> {
    using type = list<>;
  };

  // contains //

  template<typename T, typename... Args>
  struct contains<list<Args...>, T> {
    static constexpr const bool value = util::is_one_of_v<T, Args...>;
  };

  // flatten //

  template<typename... Args>
  struct flatten<list<Args...>> {
    using type = _t<concat<_t<flatten<Args>>...>>;
  };

  template<typename NonListType>
  struct flatten {
    // Flattening a non-list type means sticking it in a list
    using type = list<NonListType>;
  };

  // uniquify //

  namespace detail {
    template<typename... Types>
    struct uniquify_impl;

    template<typename T, typename... Types>
    struct uniquify_impl<T, Types...> {
      using type = _t<std::conditional_t<
        util::is_one_of_v<T, Types...>,
        uniquify<list<Types...>>,
        concat<list<T>, _t<uniquify<list<Types...>>>>>>;
    };

    template<typename T>
    struct uniquify_impl<T> {
      using type = list<T>;
    };

    template<>
    struct uniquify_impl<> {
      using type = list<>;
    };
  }

  template<typename... Types>
  struct uniquify<list<Types...>> {
    using type = meta::_t<detail::uniquify_impl<Types...>>;
  };

  // partition //

  template<typename Pivot, template<class T1, class T2> typename Compare, typename... Types>
  struct partition<list<Types...>, Pivot, Compare> {
  private:
    constexpr static auto impl()
    {
      if constexpr (sizeof...(Types) == 0) {
        return pair<list<>, list<>>();
      } else {
        using List = list<Types...>;
        using H = _t<head<List>>;
        using R = _t<partition<_t<tail<List>>, Pivot, Compare>>;
        if constexpr (_v<Compare<H, Pivot>>) {
          return pair<_t<concat<list<H>, _first<R>>>, _second<R>>();
        } else {
          return pair<_first<R>, _t<concat<list<H>, _second<R>>>>();
        }
      }
    }
  public:
    using type = decltype(impl());
  };

  // sort //

  template<template<class T1, class T2> typename Compare, typename... Types>
  struct sort<list<Types...>, Compare> {
  private:
    constexpr static auto impl() {
      if constexpr (sizeof...(Types) == 0) {
        return list<>{};
      } else {
        using TL = list<Types...>;
        using Pivot = _t<head<TL>>;
        using R     = _t<partition<_t<tail<TL>>, Pivot, Compare>>;
        return _t<concat<_t<sort<_first<R>, Compare>>,
                    list<Pivot>,
                    _t<sort<_second<R>, Compare>>>>();
      }
    };

  public:
    using type = decltype(impl());
  };

  // for_each //

  namespace impl {
    template<typename... Types>
    struct for_each_impl;

    template<typename T, typename... Types>
    struct for_each_impl<T, Types...> {
      template<typename Callable>
      static constexpr void apply(Callable&& cb) {
        cb(one<T>());
        for_each_impl<Types...>::apply(std::forward<Callable>(cb));
      }
    };

    template<>
    struct for_each_impl<> {
      template<typename Callable>
      static constexpr void apply(Callable&& cb) {}
    };

    template<typename List>
    struct for_each;

    template<typename... Types>
    struct for_each<list<Types...>> : for_each_impl<Types...> {};
  }

  template<typename List, typename Callable>
  constexpr void for_each(Callable&& cb) {
    impl::for_each<List>::apply(std::forward<Callable>(cb));
  }

  // transform_to_tuple //

  namespace impl {
    template<typename... Types>
    struct transform_to_tuple_impl;

    template<typename T, typename... Types>
    struct transform_to_tuple_impl<T, Types...> {
      template<typename Callable, typename Tuple>
      static constexpr auto apply(Callable&& cb, Tuple&& tuple) {
        auto t2 = std::tuple_cat(std::forward<Tuple>(tuple), std::make_tuple(cb(one<T>())));
        return transform_to_tuple_impl<Types...>::apply(std::forward<Callable>(cb), std::move(t2));
      }
    };

    template<>
    struct transform_to_tuple_impl<> {
      template<typename Callable, typename Tuple>
      static constexpr auto apply(Callable&& cb, Tuple&& tuple) {
        return tuple;
      }
    };

    template<typename List>
    struct transform_to_tuple;

    template<typename... Types>
    struct transform_to_tuple<list<Types...>>
      : transform_to_tuple_impl<Types...> {};
  }

  template<typename List, typename Callable>
  constexpr auto transform_to_tuple(Callable&& cb) {
    return impl::transform_to_tuple<List>::apply(std::forward<Callable>(cb), std::tuple<>());
  }

}
