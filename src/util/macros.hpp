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

