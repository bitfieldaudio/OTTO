#pragma once

#include <functional>
#include <type_traits>
#include <utility>
#include "util/type_traits.hpp"

namespace otto::util {

  /* *********************************************************************** */
  /* Implementations of standard concepts                                    */
  /* *********************************************************************** */

  /// Core language concepts

  /// specifies that a type is the same as another type
  template<typename T, typename U>
  concept same_as = std::is_same_v<T, U>;
  /// specifies that a type is derived from another type
  template<typename T, typename U>
  concept derived_from = std::is_base_of_v<T, U>;
  /// specifies that a type is implicitly convertible to another type
  template<typename T, typename U>
  concept convertible_to = std::is_convertible_v<U, T>;
  // /// specifies that two types share a common reference type
  // template<class T, class U>
  // concept common_reference_with = same_as<std::common_reference_t<T, U>, std::common_reference_t<U, T>>&&
  //   convertible_to<T, std::common_reference_t<T, U>>&& convertible_to<U, std::common_reference_t<T, U>>;
  // /// specifies that two types share a common type
  // template<class T, class U>
  // concept common_with = same_as<std::common_type_t<T, U>, std::common_type_t<U, T>>&& requires
  // {
  //   static_cast<std::common_type_t<T, U>>(std::declval<T>());
  //   static_cast<std::common_type_t<T, U>>(std::declval<U>());
  // }
  // &&common_reference_with<std::add_lvalue_reference_t<const T>, std::add_lvalue_reference_t<const U>>&&
  //   common_reference_with<
  //     std::add_lvalue_reference_t<std::common_type_t<T, U>>,
  //     std::common_reference_t<std::add_lvalue_reference_t<const T>, std::add_lvalue_reference_t<const U>>>;

  /// specifies that a type is an integral type
  template<typename T>
  concept integral = std::is_integral_v<T>;
  /// specifies that a type is an integral type that is signed
  template<typename T>
  concept signed_integral = std::is_integral_v<T>&& std::is_signed_v<T>;
  /// specifies that a type is an integral type that is unsigned
  template<typename T>
  concept unsigned_integral = std::is_integral_v<T>&& std::is_unsigned_v<T>;
  /// specifies that a type is a floating-point type
  template<typename T>
  concept floating_point = std::is_floating_point_v<T>;
  /// specifies that a type is assignable from another type
  template<typename LHS, typename RHS>
  concept assignable_from = std::is_lvalue_reference_v<LHS>&& requires(LHS lhs, RHS&& rhs)
  {
    {
      lhs = std::forward<RHS>(rhs)
    }
    ->same_as<LHS>;
  };
  /// specifies that a type can be swapped or that two types can be swapped with each other
  template<typename T>
  concept swappable = std::is_swappable_v<T>;
  template<typename T>
  concept swappable_with = std::is_swappable_with_v<T>;
  /// specifies that an object of the type can be destroyed
  template<typename T>
  concept destructible = std::is_destructible_v<T>;
  /// specifies that a variable of the type can be constructed from or bound to a set of argument types
  template<typename T, typename... Args>
  concept constructible_from = destructible<T>&& std::is_constructible_v<T, Args...>;
  /// specifies that an object of a type can be default constructed
  template<typename T>
  concept default_initializable = constructible_from<T>&& requires
  {
    T{};
  }
  &&requires
  {
    ::new (static_cast<void*>(nullptr)) T;
  };
  /// specifies that an object of a type can be move constructed
  template<typename T>
  concept move_constructible = std::is_move_constructible_v<T>;
  /// specifies that an object of a type can be copy constructed and move constructed
  template<typename T>
  concept copy_constructible = std::is_copy_constructible_v<T>;

  template<typename T>
  concept boolean_testable = convertible_to<T, bool>&& requires(T&& b)
  {
    {
      !std::forward<T>(b)
    }
    ->convertible_to<bool>;
  };

  /// Comparison concepts

  /// specifies that operator == is an equivalence relation
  template<typename T, typename U>
  concept equality_comparable = requires(const std::remove_reference_t<T>& t, const std::remove_reference_t<U>& u)
  {
    {
      t == u
    }
    ->boolean_testable;
    {
      t != u
    }
    ->boolean_testable;
    {
      u == t
    }
    ->boolean_testable;
    {
      u != t
    }
    ->boolean_testable;
  };
  // template<typename T>
  // concept equality_comparable_with = std::is_equality_comparable_with_v<T>;
  /// specifies that the comparison operators on the type yield a total order
  // template<typename T>
  // concept totally_ordered = std::is_totally_ordered_v<T>;
  // template<typename T>
  // concept totally_ordered_with = std::is_totally_ordered_with_v<T>;

  /// Object concepts

  /// specifies that an object of a type can be moved and swapped
  template<typename T>
  concept movable = std::is_object_v<T>&& move_constructible<T>&& assignable_from<T&, T>&& swappable<T>;
  /// specifies that an object of a type can be copied, moved, and swapped
  template<typename T>
  concept copyable = copy_constructible<T>&& movable<T>&& assignable_from<T&, T&>&& assignable_from<T&, const T&>&&
    assignable_from<T&, const T>;
  /// specifies that an object of a type can be copied, moved, swapped, and default constructed
  template<typename T>
  concept semiregular = copyable<T>&& default_initializable<T>;
  /// specifies that a type is regular, that is, it is both semiregular and equality_comparable
  // template<typename T>
  // concept regular = std::is_regular_v<T>;

  /// Callable concepts

  /// specifies that a callable type can be invoked with a given set of argument types
  template<typename F, typename... Args>
  concept invocable = requires(F&& f, Args&&... args)
  {
    std::invoke(std::forward<F>(f), std::forward<Args>(args)...);
  };
  template<typename T, typename... Args>
  concept regular_invocable = invocable<T, Args...>;
  /// specifies that a callable type is a Boolean predicate
  template<typename T, typename... Args>
  concept predicate = regular_invocable<T, Args...>&& boolean_testable<std::invoke_result_t<T, Args...>>;

  /// specifies that a callable type is a binary relation
  template<typename R, typename T, typename U>
  concept relation = predicate<R, T, T>&& predicate<R, U, U>&& predicate<R, T, U>&& predicate<R, U, T>;
  /// specifies that a relation imposes an equivalence relation
  template<typename R, typename T, typename U>
  concept equivalence_relation = relation<R, T, U>;
  /// specifies that a relation imposes a strict weak ordering
  template<typename R, typename T, typename U>
  concept strict_weak_order = relation<R, T, U>;


  /* *********************************************************************** */
  /* Custom concepts                                                         */
  /* *********************************************************************** */

  /// Any arithmetic type except bool
  template<typename T>
  concept numeric = std::is_arithmetic_v<T> && !same_as<T, bool>;

  namespace detail {
    template<typename F, typename Shape>
    struct is_callable_impl;

    template<typename F, typename Ret, typename... Args>
    struct is_callable_impl<F, Ret(Args...)> : std::is_invocable_r<Ret, F, Args...> {};

    template<typename Shape>
    struct is_function_shape : std::false_type {};

    template<typename Ret, typename... Args>
    struct is_function_shape<Ret(Args...)> : std::true_type {};
  } // namespace detail

  template<typename T>
  concept function_shape = detail::is_function_shape<T>::value;

  template<typename F, typename Shape>
  concept callable = detail::is_callable_impl<F, Shape>::value;

  template<typename T, typename... Ts>
  concept one_of = is_one_of_v<T, Ts...>;

} // namespace otto::util
