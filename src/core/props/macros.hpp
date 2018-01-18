#pragma once

#include <boost/hana/string.hpp>

#include "util/macros.hpp"
#include "tag_list.hpp"

/// Declarations to place at the beginning of mixin decls.
#define OTTO_PROPS_MIXIN_DECLS(THIS_TYPE)                                      \
  using self_type  = THIS_TYPE##_;                                             \
  using value_type = ValueType;                                                \
  using tag_list_t = TagList;                                                  \
  using property_type =                                                        \
    ::otto::core::props::inherits_from_mixins_t<value_type, tag_list_t>;       \
  constexpr static tag_list_t tag_list;                                        \
                                                                               \
  template<typename Tag>                                                       \
  constexpr static bool is =                                                   \
    ::otto::core::props::contains_tag_v<tag_list_t, Tag>;                      \
                                                                               \
  template<typename Tag>                                                       \
  constexpr auto as()                                                          \
    ->::std::enable_if_t<self_type::is<Tag>, ::otto::core::props::tag_mixin_t< \
                                               Tag, value_type, tag_list_t>&>  \
  {                                                                            \
    auto* as_prop = static_cast<property_type*>(this);                         \
    return static_cast<                                                        \
      ::otto::core::props::tag_mixin_t<Tag, value_type, tag_list_t>&>(         \
      *as_prop);                                                               \
  }

/// \exclude
#define OTTO_PROPS_MIXIN_1(TAG_NAME)                                           \
  template<typename ValueType, typename TagList>                               \
  struct TAG_NAME##_;                                                          \
  struct TAG_NAME {                                                            \
    template<typename ValueType, typename TagList>                             \
    using implementation_type = TAG_NAME##_<ValueType, TagList>;               \
    using required_tags       = ::otto::core::props::tag_list<>;               \
    constexpr static ::boost::hana::string name =                              \
      BOOST_HANA_STRING(#TAG_NAME);                                            \
  };                                                                           \
  template<typename ValueType, typename TagList>                               \
  struct TAG_NAME##_

/// \exclude
#define OTTO_PROPS_MIXIN_2(TAG_NAME, ...)                                      \
  template<typename ValueType, typename TagList>                               \
  struct TAG_NAME##_;                                                          \
  struct TAG_NAME {                                                            \
    template<typename ValueType, typename TagList>                             \
    using implementation_type = TAG_NAME##_<ValueType, TagList>;               \
    using required_tags       = ::otto::core::props::tag_list<__VA_ARGS__>;    \
    constexpr static ::boost::hana::string name =                              \
      BOOST_HANA_STRING(#TAG_NAME);                                            \
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
///   OTTO_PROPS_MIXIN_DECLS(has_maximum);
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
