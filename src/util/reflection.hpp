#pragma once

#include <MetaStuff/Meta.h>
#include "util/macros.hpp"

#define _REFLECT_STRUCT_ARGS1(Type, Name) ::metastuff::member(#Name, &Type::Name)
#define _REFLECT_STRUCT_ADD_TYPE(Type, Name) &Type::Name
#define _REFLECT_STRUCT_ARGS2(Type, NameString, ...)                                               \
  ::metastuff::member(NameString, FOR_EACH_LAST_SEP2(_REFLECT_STRUCT_ADD_TYPE, (Type), __VA_ARGS__))
#define _REFLECT_STRUCT_ARGS_DISPATCH(Type, ...)                                                   \
  GET_MACRO_4(__VA_ARGS__, _REFLECT_STRUCT_ARGS2, _REFLECT_STRUCT_ARGS2, _REFLECT_STRUCT_ARGS2,    \
              _REFLECT_STRUCT_ARGS1, NOTHING)                                                      \
  (Type, __VA_ARGS__)
#define _REFLECT_STRUCT_ARGS(Type, Args) _REFLECT_STRUCT_ARGS_DISPATCH(Type, UNPAREN(Args))

#define DECL_REFLECTION_OUTSIDE(Type, ...)                                                         \
  namespace metastuff {                                                                            \
    template<>                                                                                     \
    inline auto registerMembers<Type>()                                                            \
    {                                                                                              \
      return ::metastuff::members(FOR_EACH_LAST_SEP(_REFLECT_STRUCT_ARGS, (Type), __VA_ARGS__));   \
    }                                                                                              \
    template<>                                                                                     \
    inline auto registerName<Type>()                                                               \
    {                                                                                              \
      return #Type                                                                                 \
    }                                                                                              \
  }

#define DECL_REFLECTION(Type, ...)                                                                 \
  friend auto metastuff::registerMembers<Type>();                                                  \
  static auto reflect_members()                                                                    \
  {                                                                                                \
    return ::metastuff::members(FOR_EACH_LAST_SEP(_REFLECT_STRUCT_ARGS, (Type), __VA_ARGS__));     \
  }                                                                                                \
  friend constexpr auto ::metastuff::registerName<Type>();                                         \
  static constexpr auto reflect_name()                                                             \
  {                                                                                                \
    return #Type;                                                                                  \
  }

namespace metastuff {
  // function used for registration of classes by user
  template<typename Class>
  inline auto registerMembers()
  {
    return Class::reflect_members();
  }

  // function used for registration of class name by user
  template<typename Class>
  constexpr auto registerName()
  {
    return Class::reflect_name();
  }
} // namespace metastuff

namespace otto {
  namespace reflect = ::metastuff;
}
