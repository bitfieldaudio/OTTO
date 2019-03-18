#pragma once

#include "util/reflect/reflect.hpp"
#include "util/macros.hpp"

#define _REFLECT_STRUCT_ARGS1(Type, Name) ::otto::reflect::member<Type>(#Name, &Type::Name)
#define _REFLECT_STRUCT_ADD_TYPE(Type, Name) &Type::Name
#define _REFLECT_STRUCT_ARGS2(Type, NameString, ...)                                               \
  ::otto::reflect::member<Type>(NameString, __VA_ARGS__)

#define _REFLECT_STRUCT_ARGS_DISPATCH(Type, ...)                                                   \
  GET_MACRO_4(__VA_ARGS__, _REFLECT_STRUCT_ARGS2, _REFLECT_STRUCT_ARGS2, _REFLECT_STRUCT_ARGS2,    \
              _REFLECT_STRUCT_ARGS1, NOTHING)                                                      \
  (Type, __VA_ARGS__)
#define _REFLECT_STRUCT_ARGS(Type, Args) _REFLECT_STRUCT_ARGS_DISPATCH(Type, UNPAREN(Args))

#define DECL_REFLECTION_OUTSIDE(Type, ...)                                                         \
  namespace otto::reflect {                                                                        \
    template<>                                                                                     \
    constexpr auto register_members<Type>()                                                        \
    {                                                                                              \
      return ::otto::reflect::members(                                                             \
        FOR_EACH_LAST_SEP(_REFLECT_STRUCT_ARGS, (Type), __VA_ARGS__));                             \
    }                                                                                              \
    template<>                                                                                     \
    constexpr std::string_view register_name<Type>()                                               \
    {                                                                                              \
      return #Type                                                                                 \
    }                                                                                              \
  }

#define DECL_REFLECTION(Type, ...)                                                                 \
  static constexpr auto reflect_members()                                                          \
  {                                                                                                \
    return ::otto::reflect::members(FOR_EACH_LAST_SEP(_REFLECT_STRUCT_ARGS, (Type), __VA_ARGS__)); \
  }                                                                                                \
  static constexpr std::string_view reflect_name()                                                 \
  {                                                                                                \
    return #Type;                                                                                  \
  }

#define DECL_REFLECTION_EMPTY(Type)                                                                \
  static constexpr auto reflect_members()                                                          \
  {                                                                                                \
    return ::otto::reflect::members();                                                             \
  }                                                                                                \
  static constexpr std::string_view reflect_name()                                                 \
  {                                                                                                \
    return #Type;                                                                                  \
  }

namespace otto::reflect {} // namespace otto::reflect
