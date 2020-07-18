#pragma once

#include <functional> // invoke

#include "util/type_traits.hpp"

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

    type _t() const noexcept;
  };

  /// First element of Pair
  template<typename Pair>
  using _first = typename Pair::first;

  /// Second element of Pair
  template<typename Pair>
  using _second = typename Pair::second;

  /// Metafunction to see if T1 and T2 are the same type
  template<typename T1, typename T2>
  struct equals;

  /// The default compare metafunction. Overload for user types.
  template<typename T1, typename T2>
  struct compare;

  /// Metafunction to get first element in a list.
  template<typename List>
  struct head;

  /// Metafunction to get everything but the first element in a list.
  template<typename List>
  struct tail;

  /// Metafunction to see if `List` contains `T`
  template<typename List, typename T>
  struct contains;

  /// Metafunction to see if `List` has an element matching `Predicate`
  ///
  /// Has a static constexpr bool member `value`
  template<typename List, template<typename T> typename Predicate>
  struct has_one;

  /// Metafunction to concattenate lists.
  template<typename... Lists>
  struct concat;

  /// Metafunction to flatten a list of lists.
  template<typename List>
  struct flatten;

  /// Metafunction to filter items by predicate
  template<typename List, template<typename T> typename Predicate>
  struct filter;

  /// Metafunction to remove items by predicate
  template<typename List, template<typename T> typename Predicate>
  struct remove_if;

  /// Metafunction to remove an item from a list
  template<typename List, typename T>
  struct remove;

  /// Metafunction to pop the last item from the list
  template<typename List>
  struct pop_back;

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

  /// Metafunction to see if T1 and T2 are the same type
  template<typename T1, typename T2>
  constexpr const bool equals_v = _v<equals<T1, T2>>;

  /// The default compare metafunction. Overload for user types.
  template<typename T1, typename T2>
  constexpr const bool compare_v = _v<compare<T1, T2>>;

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

  /// Metafunction to see if `List` has an element matching `Predicate`
  ///
  /// Has a static constexpr bool member `value`
  template<typename List, template<typename T> typename Predicate>
  constexpr const bool has_one_v = _v<has_one<List, Predicate>>;

  /// Metafunction to filter items by predicate
  template<typename List, template<typename T> typename Predicate>
  using filter_t = _t<filter<List, Predicate>>;

  /// Metafunction to remove items by predicate
  template<typename List, template<typename T> typename Predicate>
  using remove_if_t = _t<remove_if<List, Predicate>>;

  /// Metafunction to remove an item from a list
  template<typename List, typename T>
  using remove_t = _t<remove<List, T>>;

  /// Metafunction to pop the last item from a list
  template<typename List>
  using pop_back_t = _t<pop_back<List>>;

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

  template<typename T1, typename T2>
  struct equals {
    constexpr static const bool value = std::is_same_v<T1, T2>;
  };

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

  // has_one //

  template<template<typename T> typename P, typename... Types>
  struct has_one<list<Types...>, P> {
    static constexpr const bool value = (_v<P<Types>> || ...);
  };

  // contains //

  template<typename T, typename... Types>
  struct contains<list<Types...>, T> {
    static constexpr const bool value = (equals_v<T, Types> || ...);
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

  // filter //

  namespace detail {
    template<template<typename V> typename Predicate, typename... Types>
    struct filter_impl;

    template<template<typename V> typename Predicate, typename T, typename... Types>
    struct filter_impl<Predicate, T, Types...> {
      using type = _t<std::conditional_t<_v<Predicate<T>>,
                                         concat<list<T>, _t<filter<list<Types...>, Predicate>>>,
                                         filter<list<Types...>, Predicate>>>;
    };

    template<template<typename V> typename Predicate, typename T>
    struct filter_impl<Predicate, T> {
      using type = std::conditional_t<_v<Predicate<T>>, list<T>, list<>>;
    };

    template<template<typename V> typename Predicate>
    struct filter_impl<Predicate> {
      using type = list<>;
    };
  } // namespace detail

  template<template<typename T> typename Predicate, typename... Types>
  struct filter<list<Types...>, Predicate> {
    using type = _t<detail::filter_impl<Predicate, Types...>>;
  };

  // remove_if //
  template<template<typename T> typename Predicate, typename... Types>
  struct remove_if<list<Types...>, Predicate> {
  private:
    template<typename T>
    struct predicate {
      static constexpr const bool value = !_v<Predicate<T>>;
    };

  public:
    using type = _t<detail::filter_impl<predicate, Types...>>;
  };

  // remove //

  template<typename T, typename... Types>
  struct remove<list<Types...>, T> {
  private:
    template<typename T1>
    using predicate = equals<T, T1>;

  public:
    using type = _t<remove_if<list<Types...>, predicate>>;
  };

  // pop_back //

  namespace detail {
    template<typename... Types>
    struct pop_back_impl;

    template<typename T, typename... Types>
    struct pop_back_impl<T, Types...> {
      using type = _t<concat<list<T>, _t<pop_back<list<Types...>>>>>;
    };

    template<typename T>
    struct pop_back_impl<T> {
      using type = list<>;
    };

    template<>
    struct pop_back_impl<> {
      using type = list<>;
    };
  } // namespace detail

  template<typename... Types>
  struct pop_back<list<Types...>> {
  private:
  public:
    using type = _t<detail::pop_back_impl<list<Types...>>>;
  };

  // uniquify //

  namespace detail {
    template<typename... Types>
    struct uniquify_impl;

    template<typename T, typename... Types>
    struct uniquify_impl<T, Types...> {
      using type = _t<std::conditional_t<util::is_one_of_v<T, Types...>,
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
  } // namespace detail

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
    constexpr static auto impl()
    {
      if constexpr (sizeof...(Types) == 0) {
        return list<>{};
      } else {
        using TL = list<Types...>;
        using Pivot = _t<head<TL>>;
        using R = _t<partition<_t<tail<TL>>, Pivot, Compare>>;
        return _t<concat<_t<sort<_first<R>, Compare>>, list<Pivot>, _t<sort<_second<R>, Compare>>>>();
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
      static constexpr void apply(Callable&& cb)
      {
        std::invoke(cb, one<T>());
        for_each_impl<Types...>::apply(std::forward<Callable>(cb));
      }
    };

    template<>
    struct for_each_impl<> {
      template<typename Callable>
      static constexpr void apply(Callable&& cb)
      {}
    };

    template<typename List>
    struct for_each;

    template<typename... Types>
    struct for_each<list<Types...>> : for_each_impl<Types...> {};
  } // namespace impl

  template<typename List, typename Callable>
  constexpr void for_each(Callable&& cb)
  {
    impl::for_each<List>::apply(std::forward<Callable>(cb));
  }

  // transform_to_tuple //

  namespace impl {
    template<typename... Types>
    struct transform_to_tuple_impl;

    template<typename T, typename... Types>
    struct transform_to_tuple_impl<T, Types...> {
      template<typename Callable, typename Tuple>
      static constexpr auto apply(Callable&& cb, Tuple&& tuple)
      {
        auto t2 = std::tuple_cat(std::forward<Tuple>(tuple), std::make_tuple(cb(one<T>())));
        return transform_to_tuple_impl<Types...>::apply(std::forward<Callable>(cb), std::move(t2));
      }
    };

    template<>
    struct transform_to_tuple_impl<> {
      template<typename Callable, typename Tuple>
      static constexpr auto apply(Callable&& cb, Tuple&& tuple)
      {
        return tuple;
      }
    };

    template<typename List>
    struct transform_to_tuple;

    template<typename... Types>
    struct transform_to_tuple<list<Types...>> : transform_to_tuple_impl<Types...> {};
  } // namespace impl

  template<typename List, typename Callable>
  constexpr auto transform_to_tuple(Callable&& cb)
  {
    return impl::transform_to_tuple<List>::apply(std::forward<Callable>(cb), std::tuple<>());
  }

} // namespace otto::meta

#define OTTO_META_ASSERT_EQUAL(...) static_assert(std::is_same_v<__VA_ARGS__>)
