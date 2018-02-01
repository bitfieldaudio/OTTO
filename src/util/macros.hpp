#pragma once
#include <type_traits>

/// Define bitwise operators for scoped enums.
///
/// This is especially useful for enums used for flags
#define MAKE_ENUM_OPERATORS(Enum)                                       \
  static_assert(std::is_enum_v<Enum>,                                   \
    "MAKE_ENUM_OPERATORS should only be instantiated for enumerators"); \
  inline constexpr Enum operator & (Enum lhs, Enum rhs)                 \
  {                                                                     \
    return Enum{std::underlying_type_t<Enum>(lhs) &                     \
        std::underlying_type_t<Enum>(rhs)};                             \
  }                                                                     \
  inline constexpr Enum operator | (Enum lhs, Enum rhs)                 \
  {                                                                     \
    return Enum{std::underlying_type_t<Enum>(lhs) |                     \
        std::underlying_type_t<Enum>(rhs)};                             \
  }                                                                     \
  inline constexpr Enum operator &= (Enum lhs, Enum rhs)                \
  {                                                                     \
    return lhs = (lhs & rhs);                                           \
  }                                                                     \
  inline constexpr Enum operator |= (Enum lhs, Enum rhs)                \
  {                                                                     \
    return lhs = (lhs | rhs);                                           \
  }


// Overload macros based on argument count
#define GET_MACRO_1(_1,NAME) NAME
#define GET_MACRO_2(_1,_2,NAME,...) NAME
#define GET_MACRO_3(_1,_2,_3,NAME,...) NAME
#define GET_MACRO_4(_1,_2,_3,_4,NAME,...) NAME
#define GET_MACRO_5(_1,_2,_3,_4,_5,NAME,...) NAME
#define GET_MACRO_6(_1,_2,_3,_4,_5,_6,NAME,...) NAME
#define GET_MACRO_7(_1,_2,_3,_4,_5,_6,_7,NAME,...) NAME
#define GET_MACRO_8(_1,_2,_3,_4,_5,_6,_7,_8,NAME,...) NAME
#define GET_MACRO_9(_1,_2,_3,_4,_5,_6,_7,_8,_9,NAME,...) NAME
#define GET_MACRO_10(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,NAME,...) NAME
#define GET_MACRO_11(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,NAME,...) NAME
#define GET_MACRO_12(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,NAME,...) NAME
#define GET_MACRO_13(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,NAME,...) NAME
#define GET_MACRO_14(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,NAME,...) NAME
#define GET_MACRO_15(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,NAME,...) NAME

// a FOREACH macro
#define FE_1(WHAT, X) WHAT(X) 
#define FE_2(WHAT, X, ...) WHAT(X)FE_1(WHAT, __VA_ARGS__)
#define FE_3(WHAT, X, ...) WHAT(X)FE_2(WHAT, __VA_ARGS__)
#define FE_4(WHAT, X, ...) WHAT(X)FE_3(WHAT, __VA_ARGS__)
#define FE_5(WHAT, X, ...) WHAT(X)FE_4(WHAT, __VA_ARGS__)
#define FE_6(WHAT, X, ...) WHAT(X)FE_5(WHAT, __VA_ARGS__)
#define FE_7(WHAT, X, ...) WHAT(X)FE_6(WHAT, __VA_ARGS__)
#define FE_8(WHAT, X, ...) WHAT(X)FE_7(WHAT, __VA_ARGS__)
#define FE_9(WHAT, X, ...) WHAT(X)FE_8(WHAT, __VA_ARGS__)
#define FE_10(WHAT, X, ...) WHAT(X)FE_9(WHAT, __VA_ARGS__)
#define FE_11(WHAT, X, ...) WHAT(X)FE_10(WHAT, __VA_ARGS__)
#define FE_12(WHAT, X, ...) WHAT(X)FE_11(WHAT, __VA_ARGS__)
#define FE_13(WHAT, X, ...) WHAT(X)FE_12(WHAT, __VA_ARGS__)
#define FE_14(WHAT, X, ...) WHAT(X)FE_13(WHAT, __VA_ARGS__)
#define FE_15(WHAT, X, ...) WHAT(X)FE_14(WHAT, __VA_ARGS__)

#define FOR_EACH(action, ...)                                                  \
  GET_MACRO_15(__VA_ARGS__, FE_15, FE_14, FE_13, FE_12, FE_11, FE_10, FE_9,    \
               FE_8, FE_7, FE_6, FE_5, FE_4, FE_3, FE_2, FE_1, NONE)           \
  (action, __VA_ARGS__)

# define EMPTY(...)
# define DEFER(...) __VA_ARGS__ EMPTY()
# define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()
# define EXPAND(...) __VA_ARGS__
