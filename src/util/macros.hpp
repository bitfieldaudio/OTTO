#pragma once
#include <type_traits>

/// Define bitwise operators for scoped enums.
///
/// This is especially useful for enums used for flags
#define MAKE_ENUM_OPERATORS(Enum)                                                                                      \
  static_assert(std::is_enum_v<Enum>, "MAKE_ENUM_OPERATORS should only be instantiated for enumerators");              \
  inline constexpr Enum operator&(Enum lhs, Enum rhs)                                                                  \
  {                                                                                                                    \
    return Enum{std::underlying_type_t<Enum>(lhs) & std::underlying_type_t<Enum>(rhs)};                                \
  }                                                                                                                    \
  inline constexpr Enum operator|(Enum lhs, Enum rhs)                                                                  \
  {                                                                                                                    \
    return Enum{std::underlying_type_t<Enum>(lhs) | std::underlying_type_t<Enum>(rhs)};                                \
  }                                                                                                                    \
  inline constexpr Enum operator&=(Enum lhs, Enum rhs)                                                                 \
  {                                                                                                                    \
    return lhs = (lhs & rhs);                                                                                          \
  }                                                                                                                    \
  inline constexpr Enum operator|=(Enum lhs, Enum rhs)                                                                 \
  {                                                                                                                    \
    return lhs = (lhs | rhs);                                                                                          \
  }

#define FIELD_GETTER(name) [](auto&& obj) { return obj.name; }

/// Forward any expression through std::forward with the correct type
#define FWD(X) std::forward<decltype(X)>(X)

/// Used to wrap entire overload sets into a single callable lambda
#define CALLABLE(...) [](auto&&... args) -> decltype(auto) { return std::invoke(__VA_ARGS__, FWD(args)...); }
/// Used to wrap entire overload sets of member functions into a single callable lambda
#define MEMBER_CALLER(...) [](auto&& obj, auto&&... args) -> decltype(auto) { return obj.__VA_ARGS__(FWD(args)...); }
/// Make a lambda that captures `this` and calls the given member function with whatever is supplied
#define BIND_THIS(...) [this](auto&&... args) -> decltype(auto) { return this->__VA_ARGS__(FWD(args)...); }

// Overload macros based on argument count
#define GET_MACRO_1(_1, NAME, ...) NAME
#define GET_MACRO_2(_1, _2, NAME, ...) NAME
#define GET_MACRO_3(_1, _2, _3, NAME, ...) NAME
#define GET_MACRO_4(_1, _2, _3, _4, NAME, ...) NAME
#define GET_MACRO_5(_1, _2, _3, _4, _5, NAME, ...) NAME
#define GET_MACRO_6(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
#define GET_MACRO_7(_1, _2, _3, _4, _5, _6, _7, NAME, ...) NAME
#define GET_MACRO_8(_1, _2, _3, _4, _5, _6, _7, _8, NAME, ...) NAME
#define GET_MACRO_9(_1, _2, _3, _4, _5, _6, _7, _8, _9, NAME, ...) NAME
#define GET_MACRO_10(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME
#define GET_MACRO_11(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, NAME, ...) NAME
#define GET_MACRO_12(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, NAME, ...) NAME
#define GET_MACRO_13(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, NAME, ...) NAME
#define GET_MACRO_14(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, NAME, ...) NAME
#define GET_MACRO_15(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, NAME, ...) NAME

#define SWITCH_FOR_VARARGS_1(NO_VARARGS, VARARGS, ...)                                                                 \
  GET_MACRO_15(__VA_ARGS__, VARARGS, VARARGS, VARARGS, VARARGS, VARARGS, VARARGS, VARARGS, VARARGS, VARARGS, VARARGS,  \
               VARARGS, VARARGS, VARARGS, VARARGS, NO_VARARGS, NONE)(__VA_ARGS__)

// a FOREACH macro
#define FE_1(WHAT, X) WHAT(X)
#define FE_2(WHAT, X, ...) WHAT(X) FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT(X) FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT(X) FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT(X) FE_4(WHAT, __VA_ARGS__)
#define FE_6(WHAT, X, ...) WHAT(X) FE_5(WHAT, __VA_ARGS__)
#define FE_7(WHAT, X, ...) WHAT(X) FE_6(WHAT, __VA_ARGS__)
#define FE_8(WHAT, X, ...) WHAT(X) FE_7(WHAT, __VA_ARGS__)
#define FE_9(WHAT, X, ...) WHAT(X) FE_8(WHAT, __VA_ARGS__)
#define FE_10(WHAT, X, ...) WHAT(X) FE_9(WHAT, __VA_ARGS__)
#define FE_11(WHAT, X, ...) WHAT(X) FE_10(WHAT, __VA_ARGS__)
#define FE_12(WHAT, X, ...) WHAT(X) FE_11(WHAT, __VA_ARGS__)
#define FE_13(WHAT, X, ...) WHAT(X) FE_12(WHAT, __VA_ARGS__)
#define FE_14(WHAT, X, ...) WHAT(X) FE_13(WHAT, __VA_ARGS__)
#define FE_15(WHAT, X, ...) WHAT(X) FE_14(WHAT, __VA_ARGS__)

#define FOR_EACH(action, ...)                                                                                          \
  GET_MACRO_15(__VA_ARGS__, FE_15, FE_14, FE_13, FE_12, FE_11, FE_10, FE_9, FE_8, FE_7, FE_6, FE_5, FE_4, FE_3, FE_2,  \
               FE_1, NONE)                                                                                             \
  (action, __VA_ARGS__)

#define EMPTY(...)
#define DEFER(...) __VA_ARGS__ EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()
#define EXPAND(...) __VA_ARGS__
#define EXPAND1(...) __VA_ARGS__

// a FOREACH macro that puts the sequence element last in a macro call with
// other args
#define FEL_01(WHAT, ARGS, X) WHAT(EXPAND ARGS, X)
#define FEL_02(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X) FEL_01(WHAT, ARGS, __VA_ARGS__)
#define FEL_03(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X) FEL_02(WHAT, ARGS, __VA_ARGS__)
#define FEL_04(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X) FEL_03(WHAT, ARGS, __VA_ARGS__)
#define FEL_05(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X) FEL_04(WHAT, ARGS, __VA_ARGS__)
#define FEL_06(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X) FEL_05(WHAT, ARGS, __VA_ARGS__)
#define FEL_07(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X) FEL_06(WHAT, ARGS, __VA_ARGS__)
#define FEL_08(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X) FEL_07(WHAT, ARGS, __VA_ARGS__)
#define FEL_09(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X) FEL_08(WHAT, ARGS, __VA_ARGS__)
#define FEL_10(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X) FEL_09(WHAT, ARGS, __VA_ARGS__)
#define FEL_11(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X) FEL_10(WHAT, ARGS, __VA_ARGS__)
#define FEL_12(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X) FEL_11(WHAT, ARGS, __VA_ARGS__)
#define FEL_13(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X) FEL_12(WHAT, ARGS, __VA_ARGS__)
#define FEL_14(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X) FEL_13(WHAT, ARGS, __VA_ARGS__)
#define FEL_15(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X) FEL_14(WHAT, ARGS, __VA_ARGS__)

#define FOR_EACH_LAST(action, args, ...)                                                                               \
  GET_MACRO_15(__VA_ARGS__, FEL_15, FEL_14, FEL_13, FEL_12, FEL_11, FEL_10, FEL_09, FEL_08, FEL_07, FEL_06, FEL_05,    \
               FEL_04, FEL_03, FEL_02, FEL_01, NONE)                                                                   \
  (action, args, __VA_ARGS__)

// a FOREACH macro that puts the sequence element last in a macro call with
// other args, and places a comma separator in between the
#define FELS_01(WHAT, ARGS, X) WHAT(EXPAND ARGS, X)
#define FELS_02(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS_01(WHAT, ARGS, __VA_ARGS__)
#define FELS_03(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS_02(WHAT, ARGS, __VA_ARGS__)
#define FELS_04(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS_03(WHAT, ARGS, __VA_ARGS__)
#define FELS_05(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS_04(WHAT, ARGS, __VA_ARGS__)
#define FELS_06(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS_05(WHAT, ARGS, __VA_ARGS__)
#define FELS_07(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS_06(WHAT, ARGS, __VA_ARGS__)
#define FELS_08(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS_07(WHAT, ARGS, __VA_ARGS__)
#define FELS_09(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS_08(WHAT, ARGS, __VA_ARGS__)
#define FELS_10(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS_09(WHAT, ARGS, __VA_ARGS__)
#define FELS_11(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS_10(WHAT, ARGS, __VA_ARGS__)
#define FELS_12(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS_11(WHAT, ARGS, __VA_ARGS__)
#define FELS_13(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS_12(WHAT, ARGS, __VA_ARGS__)
#define FELS_14(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS_13(WHAT, ARGS, __VA_ARGS__)
#define FELS_15(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS_14(WHAT, ARGS, __VA_ARGS__)

#define FOR_EACH_LAST_SEP(action, args, ...)                                                                           \
  GET_MACRO_15(__VA_ARGS__, FELS_15, FELS_14, FELS_13, FELS_12, FELS_11, FELS_10, FELS_09, FELS_08, FELS_07, FELS_06,  \
               FELS_05, FELS_04, FELS_03, FELS_02, FELS_01, NONE)                                                      \
  (action, args, __VA_ARGS__)

// a FOREACH macro that puts the sequence element last in a macro call with
// other args, and places a comma separator in between the
#define FELS2_01(WHAT, ARGS, X) WHAT(EXPAND ARGS, X)
#define FELS2_02(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS2_01(WHAT, ARGS, __VA_ARGS__)
#define FELS2_03(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS2_02(WHAT, ARGS, __VA_ARGS__)
#define FELS2_04(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS2_03(WHAT, ARGS, __VA_ARGS__)
#define FELS2_05(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS2_04(WHAT, ARGS, __VA_ARGS__)
#define FELS2_06(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS2_05(WHAT, ARGS, __VA_ARGS__)
#define FELS2_07(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS2_06(WHAT, ARGS, __VA_ARGS__)
#define FELS2_08(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS2_07(WHAT, ARGS, __VA_ARGS__)
#define FELS2_09(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS2_08(WHAT, ARGS, __VA_ARGS__)
#define FELS2_10(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS2_09(WHAT, ARGS, __VA_ARGS__)
#define FELS2_11(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS2_10(WHAT, ARGS, __VA_ARGS__)
#define FELS2_12(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS2_11(WHAT, ARGS, __VA_ARGS__)
#define FELS2_13(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS2_12(WHAT, ARGS, __VA_ARGS__)
#define FELS2_14(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS2_13(WHAT, ARGS, __VA_ARGS__)
#define FELS2_15(WHAT, ARGS, X, ...) WHAT(EXPAND ARGS, X), FELS2_14(WHAT, ARGS, __VA_ARGS__)

#define FOR_EACH_LAST_SEP2(action, args, ...)                                                                          \
  GET_MACRO_15(__VA_ARGS__, FELS2_15, FELS2_14, FELS2_13, FELS2_12, FELS2_11, FELS2_10, FELS2_09, FELS2_08, FELS2_07,  \
               FELS2_06, FELS2_05, FELS2_04, FELS2_03, FELS2_02, FELS2_01, NONE)                                       \
  (action, args, __VA_ARGS__)


#define _FIRST_ARG(X, ...) X
#define FIRST_ARG(...) _FIRST_ARG(__VA_ARGS__, NONE)

// Remove parenthesis if they exist
#define EXTRACT(...) EXTRACT __VA_ARGS__
#define NOTHING_EXTRACT
#define PASTE(x, ...) x##__VA_ARGS__
#define EVALUATING_PASTE(x, ...) PASTE(x, __VA_ARGS__)
#define UNPAREN(x) EVALUATING_PASTE(NOTHING_, EXTRACT x)
