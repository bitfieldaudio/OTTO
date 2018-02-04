#pragma once

#include <boost/hana/string.hpp>

#include "util/macros.hpp"
#include "tag_list.hpp"

/// Declarations to place at the beginning of mixin decls.
#define OTTO_PROPS_MIXIN_DECLS(THIS_TYPE)                                      \
  using self_type  = THIS_TYPE##_;                                             \
  using value_type = ValueType;                                                \
  using tag_list_t = TagList;                                                  \
  using hooks      = ::otto::core::props::detail::tag_hooks_t<THIS_TYPE>;      \
  using interface_type =                                                       \
    ::otto::core::props::MixinTag::leaf_interface<THIS_TYPE>;                  \
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
    ->::std::enable_if_t<                                                      \
      self_type::is<Tag>,                                                      \
      ::otto::core::props::MixinTag::mixin_t<Tag, value_type, tag_list_t>&>    \
  {                                                                            \
    auto* as_prop = static_cast<property_type*>(this);                         \
    return static_cast<                                                        \
      ::otto::core::props::MixinTag::mixin_t<Tag, value_type, tag_list_t>&>(   \
      *as_prop);                                                               \
  }                                                                            \
                                                                               \
  template<typename Tag>                                                       \
  constexpr auto as()                                                          \
    const->::std::enable_if_t<self_type::is<Tag>,                              \
                              const ::otto::core::props::MixinTag::mixin_t<    \
                                Tag, value_type, tag_list_t>&>                 \
  {                                                                            \
    const auto& as_prop = static_cast<const property_type&>(*this);            \
    return static_cast<const ::otto::core::props::MixinTag::mixin_t<           \
      Tag, value_type, tag_list_t>&>(as_prop);                                 \
  }                                                                            \
                                                                               \
  template<typename HT, ::otto::core::props::HookOrder HO =                    \
                          ::otto::core::props::HookOrder::Middle>              \
  using hook = HookTag::impl_t<HT, value_type, HO>;                            \
                                                                               \
  template<typename HT,                                                        \
           CONCEPT_REQUIRES_(::ranges::concepts::models<                       \
                             ::otto::core::props::HookTag, HT, value_type>())> \
  typename hook<HT>::arg_type run_hook(const typename hook<HT>::arg_type& arg) \
  {                                                                            \
    return ::otto::core::props::detail::run_hook<HT>(*this, arg);              \
  }                                                                            \
                                                                               \
  template<typename HT>                                                        \
  typename hook<HT>::arg_type run_hook(const typename hook<HT>::arg_type& arg) \
    const                                                                      \
  {                                                                            \
    return ::otto::core::props::detail::run_hook<HT>(*this, arg);              \
  }


#define _OTTO_PROPS_ADD_PREFIX(MACRO) OTTO_PROPS_MIXIN_##MACRO

#define OTTO_PROPS_MIXIN_REQUIRES(...)                                         \
  using required_tags = ::otto::core::props::tag_list<__VA_ARGS__>;

#define OTTO_PROPS_MIXIN_LEAF_INTERFACE(...)                                   \
  using leaf_interface = __VA_ARGS__;

#define OTTO_PROPS_MIXIN_BRANCH_INTERFACE(...)                                 \
  using branch_interface = __VA_ARGS__;

#define OTTO_PROPS_MIXIN_EXTEND_BRANCH_INTERFACE(...)                          \
  using branch_interface =                                                     \
    struct interface : ::otto::core::props::BaseBranchInterface<tag_type> __VA_ARGS__;

#define OTTO_PROPS_MIXIN_VALUE(...)                                            \
  template<typename ValueType, typename TagList>                               \
  using implementation_type = __VA_ARGS__;

#define _OTTO_PROPS_MIXIN_HOOK_1(NAME)                                         \
  struct NAME {                                                                \
    template<typename Val, ::otto::core::props::HookOrder HO>                  \
    struct type {                                                              \
      using value_type = Val;                                                  \
      using arg_type   = void;                                                 \
      template<::otto::core::props::HookOrder HO1>                             \
      type(type<Val, HO1>&& rhs)                                               \
      {}                                                                       \
    };                                                                         \
  };

#define _OTTO_PROPS_MIXIN_HOOK_2(NAME, ARG_TYPE)                               \
  struct NAME {                                                                \
    template<typename Val, ::otto::core::props::HookOrder HO>                  \
    struct type {                                                              \
      using value_type = Val;                                                  \
      using arg_type   = ARG_TYPE;                                             \
      type(const arg_type& a) : _arg(a) {}                                     \
      type(arg_type&& a) : _arg(std::move(a)) {}                               \
      template<::otto::core::props::HookOrder HO1>                             \
      type(type<Val, HO1>&& rhs) : _arg(std::move(rhs.value()))         \
      {}                                                                       \
      operator arg_type&()                                                     \
      {                                                                        \
        return _arg;                                                           \
      }                                                                        \
      arg_type& value()                                                        \
      {                                                                        \
        return _arg;                                                           \
      }                                                                        \
                                                                               \
    private:                                                                   \
      arg_type _arg;                                                           \
    };                                                                         \
  };

#define _OTTO_PROPS_MIXIN_HOOK(...)                                            \
/* Call _OTTO_PROPS_MIXIN_HOOK_1 if 2 arguments was provided, and */         \
/* _OTTO_PROPS_MIXIN_HOOK_2 if 3 args were provided */                       \
GET_MACRO_2(__VA_ARGS__, _OTTO_PROPS_MIXIN_HOOK_2,                    \
            _OTTO_PROPS_MIXIN_HOOK_1)                                        \
(__VA_ARGS__)

// Macro recursion is not allowed, so use this and the DEFER macro
// to invoke FOR_EACH recursively
#define _OTTO_PROPS_DEFERED_FOR_EACH() FOR_EACH

/// Call _OTTO_PROPS_MIXIN_HOOK with ARGLIST, where ARGLIST is a set of
/// arguments wrapped in parens.
#define _OTTO_PROPS_MIXIN_HOOK_CALL(ARGLIST) _OTTO_PROPS_MIXIN_HOOK ARGLIST

/// Add hooks to a mixin.
/// This macro is used in OTTO_PROPS_MIXIN by the name HOOKS.
/// Arguments should be groups of parentheses of the form (HOOK_NAME, HOOK_TYPE)
#define OTTO_PROPS_MIXIN_HOOKS(...)                                            \
  struct hooks {                                                               \
    /* The use of the DEFER macro is because this is called from within a      \
     * FOR_EACH call */                                                        \
    DEFER(_OTTO_PROPS_DEFERED_FOR_EACH)                                        \
    ()(_OTTO_PROPS_MIXIN_HOOK_CALL, __VA_ARGS__)                               \
  };

/// \exclude
#define OTTO_PROPS_MIXIN_1(TAG_NAME)                                           \
  template<typename ValueType, typename TagList>                               \
  struct TAG_NAME##_;                                                          \
  struct TAG_NAME {                                                            \
    using tag_type = TAG_NAME;                                                 \
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
    using tag_type = TAG_NAME;                                                 \
    template<typename ValueType, typename TagList>                             \
    using implementation_type = TAG_NAME##_<ValueType, TagList>;               \
    constexpr static ::boost::hana::string name =                              \
      BOOST_HANA_STRING(#TAG_NAME);                                            \
    EXPAND(EXPAND(EXPAND(FOR_EACH(_OTTO_PROPS_ADD_PREFIX, __VA_ARGS__))))      \
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
