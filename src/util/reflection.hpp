#pragma once

#include "util/macros.hpp"
#include "util/reflect/reflect.hpp"

/// @if hidden
#define _REFLECT_STRUCT_ARGS1(Type, Name) ::otto::reflect::member<Type>(#Name, &Type::Name)
#define _REFLECT_STRUCT_ADD_TYPE(Type, Name) &Type::Name
#define _REFLECT_STRUCT_ARGS2(Type, NameString, ...)                                               \
  ::otto::reflect::member<Type>(NameString, __VA_ARGS__)

#define _REFLECT_STRUCT_ARGS_DISPATCH(Type, ...)                                                   \
  GET_MACRO_4(__VA_ARGS__, _REFLECT_STRUCT_ARGS2, _REFLECT_STRUCT_ARGS2, _REFLECT_STRUCT_ARGS2,    \
              _REFLECT_STRUCT_ARGS1, NOTHING)                                                      \
  (Type, __VA_ARGS__)
#define _REFLECT_STRUCT_ARGS(Type, Args) _REFLECT_STRUCT_ARGS_DISPATCH(Type, UNPAREN(Args))
/// @endif

/// @ingroup reflection
#define DECL_REFLECTION_OUTSIDE(Type, ...)                                                         \
  namespace otto::reflect {                                                                        \
    template<>                                                                                     \
    constexpr auto register_members<Type>()                                                        \
    {                                                                                              \
      return ::otto::reflect::members(                                                             \
        FOR_EACH_LAST_SEP(_REFLECT_STRUCT_ARGS, (Type), __VA_ARGS__));                             \
    }                                                                                              \
    template<>                                                                                     \
    constexpr ::otto::util::string_ref register_name<Type>()                                                \
    {                                                                                              \
      return #Type                                                                                 \
    }                                                                                              \
  }

/// @ingroup reflection
/// Used inside a class to register its members
#define DECL_REFLECTION(Type, ...)                                                                 \
  static constexpr auto reflect_members()                                                          \
  {                                                                                                \
    return ::otto::reflect::members(FOR_EACH_LAST_SEP(_REFLECT_STRUCT_ARGS, (Type), __VA_ARGS__)); \
  }                                                                                                \
  static constexpr ::otto::util::string_ref reflect_name()                                                  \
  {                                                                                                \
    return #Type;                                                                                  \
  }

/// @ingroup reflection
#define DECL_REFLECTION_EMPTY(Type)                                                                \
  static constexpr auto reflect_members()                                                          \
  {                                                                                                \
    return ::otto::reflect::members();                                                             \
  }                                                                                                \
  static constexpr ::otto::util::string_ref reflect_name()                                                  \
  {                                                                                                \
    return #Type;                                                                                  \
  }

/// @defgroup reflection
///
/// The OTTO reflection library is based on [MetaStuff](https://github.com/eliasdaler/MetaStuff) by
/// Elias daler.
///
/// You register classes for reflection using the macros @ref DECL_REFLECTION or
/// @ref DECL_REFLECTION_OUTSIDE, or by manually declaring the static constexpr member `reflect_members` or
/// nonmember @ref register_members, along with `reflect_name` and @ref register_name
///
/// Reflection is mainly used for serialization, using @ref otto::util::serialize and
/// @ref otto::util::deserialize, but can be used for other purposes as well. The main function is
/// @ref reflect::for_all_members, which can be used to iterate over members of a struct.
namespace otto::reflect {} // namespace otto::reflect
