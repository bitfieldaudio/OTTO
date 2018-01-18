#pragma once

#include <boost/hana/string.hpp>

#include "util/macros.hpp"
#include "tag_list.hpp"

/// \exclude
#define OTTO_PROPS_MIXIN_1(TAG_NAME)                                           \
  template<typename value_type, typename tag_list>                             \
  struct TAG_NAME##_;                                                          \
  struct TAG_NAME {                                                            \
    template<typename value_type, typename tag_list>                           \
    using implementation_type = TAG_NAME##_<value_type, tag_list>;             \
    using required_tags       = ::otto::core::props::black_magic::tag_list<>;  \
    constexpr static hana::string name = BOOST_HANA_STRING(#TAG_NAME);         \
  };                                                                           \
  template<typename ValueType, typename TagList>                               \
  struct TAG_NAME##_

/// \exclude
#define OTTO_PROPS_MIXIN_2(TAG_NAME, ...)                                      \
  template<typename value_type, typename tag_list>                             \
  struct TAG_NAME##_;                                                          \
  struct TAG_NAME {                                                            \
    template<typename value_type, typename tag_list>                           \
    using implementation_type = TAG_NAME##_<value_type, tag_list>;             \
    using required_tags =                                                      \
      ::otto::core::props::black_magic::tag_list<__VA_ARGS__>;                 \
    constexpr static hana::string name = BOOST_HANA_STRING(#TAG_NAME);         \
  };                                                                           \
  template<typename ValueType, typename TagList>                               \
  struct TAG_NAME##_

/// Start a mixin declaration.
///
/// First argument is the mixin tag name, the rest (maximum 14) are other mixins
/// to inherit from.
///
/// Usage:
/// ```cpp
/// OTTO_PROPS_MIXIN(has_maximum, has_value)
/// {
///   static_assert(util::is_number_v<T>, "property mixin 'has_maximum' requires
///                 a numeric type");
///   T maximum() const;
/// };
/// ```
/// This defines the tag type `has_name`, and the type template
/// `has_name_impl<T>`, which inherits virtually from
/// [otto::props::PropertyBase<T>]() and `has_value`. Applying this mixin will
/// make the member function `maximum` avaliable to the user, along with any
/// `has_value` members.
#define OTTO_PROPS_MIXIN(...)                                                  \
  /* Call OTTO_PROPS_MIXIN_1 if only 1 argument was provided, and */           \
  /* OTTO_PROPS_MIXIN_2 if multiple args were provided */                      \
  GET_MACRO_15(__VA_ARGS__, OTTO_PROPS_MIXIN_2, OTTO_PROPS_MIXIN_2,            \
               OTTO_PROPS_MIXIN_2, OTTO_PROPS_MIXIN_2, OTTO_PROPS_MIXIN_2,     \
               OTTO_PROPS_MIXIN_2, OTTO_PROPS_MIXIN_2, OTTO_PROPS_MIXIN_2,     \
               OTTO_PROPS_MIXIN_2, OTTO_PROPS_MIXIN_2, OTTO_PROPS_MIXIN_2,     \
               OTTO_PROPS_MIXIN_2, OTTO_PROPS_MIXIN_2, OTTO_PROPS_MIXIN_2,     \
               OTTO_PROPS_MIXIN_1, NONE)                                       \
  (__VA_ARGS__)

/// Declarations to place at the beginning of mixin decls.
#define OTTO_PROPS_MIXIN_DECLS(THIS_TYPE)                                      \
  using self_type  = THIS_TYPE##_;                                             \
  using value_type = ValueType;                                                \
  using tag_list_t = TagList;                                                  \
  constexpr static tag_list_t tag_list;\
