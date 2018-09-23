/// \file
///
/// Contains macros used to define mixins.
///
/// All of these macros are undefined in the file `undef_mixin_macros.hpp`, so
/// include that at the bottom of mixin files

#ifndef OTTO_PROPS_MIXIN__MACROS_DEFINED
#define OTTO_PROPS_MIXIN__MACROS_DEFINED

#include "util/macros.hpp"

/// Declarations to place at the beginning of mixin decls.
#define OTTO_PROPS_MIXIN_DECLS(TAG_NAME)                                                           \
  using value_type = ValueType;                                                                    \
  using tag_list = TagList;                                                                        \
  using self_type = leaf<TAG_NAME, value_type, tag_list>;                                          \
  using interface_type = ::otto::core::props::MixinTag::interface<TAG_NAME>;                       \
  using property_type = ::otto::core::props::PropertyImpl<value_type, tag_list>;                   \
                                                                                                   \
  template<typename Tag>                                                                           \
  constexpr static bool is()                                                                       \
  {                                                                                                \
    return ::otto::core::props::contains_tag_v<tag_list, Tag>;                                     \
  }                                                                                                \
                                                                                                   \
  template<typename Tag>                                                                           \
  constexpr auto as()                                                                              \
    ->::std::enable_if_t<self_type::is<Tag>(),                                                     \
                         ::otto::core::props::MixinTag::leaf<Tag, value_type, tag_list>&>          \
  {                                                                                                \
    auto* as_prop = static_cast<property_type*>(this);                                             \
    return static_cast<::otto::core::props::MixinTag::leaf<Tag, value_type, tag_list>&>(*as_prop); \
  }                                                                                                \
                                                                                                   \
  template<typename Tag>                                                                           \
  constexpr auto as() const->::std::enable_if_t<                                                   \
    self_type::is<Tag>(), const ::otto::core::props::MixinTag::leaf<Tag, value_type, tag_list>&>   \
  {                                                                                                \
    const auto& as_prop = static_cast<const property_type&>(*this);                                \
    return static_cast<const ::otto::core::props::MixinTag::leaf<Tag, value_type, tag_list>&>(     \
      as_prop);                                                                                    \
  }                                                                                                \
                                                                                                   \
  template<typename HT,                                                                            \
           ::otto::core::props::HookOrder HO = ::otto::core::props::HookOrder::Middle>             \
  using hook = HookTag::impl_t<HT, value_type, HO>;                                                \
                                                                                                   \
  template<typename HT, CONCEPT_REQUIRES_(::ranges::concepts::models<::otto::core::props::HookTag, \
                                                                     HT, value_type>())>           \
  typename hook<HT>::arg_type run_hook(const typename hook<HT>::arg_type& arg)                     \
  {                                                                                                \
    return ::otto::core::props::detail::run_hook<HT>(*this, arg);                                  \
  }                                                                                                \
                                                                                                   \
  template<typename HT>                                                                            \
  typename hook<HT>::arg_type run_hook(const typename hook<HT>::arg_type& arg) const               \
  {                                                                                                \
    return ::otto::core::props::detail::run_hook<HT>(*this, arg);                                  \
  }                                                                                                \
                                                                                                   \
  using hooks = ::otto::core::props::mixin::hooks<TAG_NAME>

#define OTTO_PROPS_MIXIN_REQUIRES(TAG_NAME, ...)                                                   \
  template<>                                                                                       \
  struct otto::core::props::mixin::required_tags<TAG_NAME> {                                       \
    using type = ::otto::core::props::tag_list<__VA_ARGS__>;                                       \
  }

#define OTTO_PROPS_MIXIN_INTERFACE(TAG_NAME)                                                       \
  template<>                                                                                       \
  struct otto::core::props::mixin::interface<TAG_NAME>

#define OTTO_PROPS_MIXIN_BRANCH(TAG_NAME)                                                          \
  template<>                                                                                       \
  struct otto::core::props::mixin::branch<TAG_NAME>                                                \
    : virtual otto::core::props::branch_base, otto::core::props::mixin::interface<TAG_NAME>

#define _OTTO_PROPS_MIXIN_HOOK_1(NAME)                                                             \
  struct NAME : ::otto::core::props::mixin::hook<void> {};

#define _OTTO_PROPS_MIXIN_HOOK_2(NAME, ...)                                                        \
  struct NAME : ::otto::core::props::mixin::hook<__VA_ARGS__> {};

#define _OTTO_PROPS_MIXIN_HOOK(...)                                                                \
  /* Call _OTTO_PROPS_MIXIN_HOOK_1 if 2 arguments was provided, and */                             \
  /* _OTTO_PROPS_MIXIN_HOOK_2 if 3 args were provided */                                           \
  GET_MACRO_15(__VA_ARGS__, _OTTO_PROPS_MIXIN_HOOK_2, _OTTO_PROPS_MIXIN_HOOK_2,                    \
               _OTTO_PROPS_MIXIN_HOOK_2, _OTTO_PROPS_MIXIN_HOOK_2, _OTTO_PROPS_MIXIN_HOOK_2,       \
               _OTTO_PROPS_MIXIN_HOOK_2, _OTTO_PROPS_MIXIN_HOOK_2, _OTTO_PROPS_MIXIN_HOOK_2,       \
               _OTTO_PROPS_MIXIN_HOOK_2, _OTTO_PROPS_MIXIN_HOOK_2, _OTTO_PROPS_MIXIN_HOOK_2,       \
               _OTTO_PROPS_MIXIN_HOOK_2, _OTTO_PROPS_MIXIN_HOOK_2, _OTTO_PROPS_MIXIN_HOOK_2,       \
               _OTTO_PROPS_MIXIN_HOOK_1, NONE)                                                     \
  (__VA_ARGS__)

/// Call _OTTO_PROPS_MIXIN_HOOK with ARGLIST, where ARGLIST is a set of
/// arguments wrapped in parens.
#define _OTTO_PROPS_MIXIN_HOOK_CALL(ARGLIST) _OTTO_PROPS_MIXIN_HOOK ARGLIST

/// Add hooks to a mixin.
/// This macro is used in OTTO_PROPS_MIXIN by the name HOOKS.
/// Arguments should be groups of parentheses of the form (HOOK_NAME, HOOK_TYPE)
#define OTTO_PROPS_MIXIN_HOOKS(TAG_NAME, ...)                                                      \
  template<>                                                                                       \
  struct otto::core::props::mixin::hooks<TAG_NAME> {                                               \
    FOR_EACH(_OTTO_PROPS_MIXIN_HOOK_CALL, __VA_ARGS__)                                             \
  }

#define OTTO_PROPS_MIXIN_TAG(TAG_NAME)                                                             \
  struct TAG_NAME {                                                                                \
    using tag_type = TAG_NAME;                                                                     \
    using hooks = ::otto::core::props::mixin::hooks<TAG_NAME>;                                     \
    constexpr static const char* name = #TAG_NAME;                                                 \
    template<typename... Args>                                                                     \
    static auto init(Args&&... args)                                                               \
    {                                                                                              \
      return ::otto::core::props::make_initializer<TAG_NAME>(std::forward<Args>(args)...);         \
    }                                                                                              \
  }

#define OTTO_PROPS_MIXIN_LEAF(TAG_NAME)                                                            \
  template<typename ValueType, typename TagList>                                                   \
  struct otto::core::props::mixin::leaf<TAG_NAME, ValueType, TagList>                              \
    : otto::core::props::mixin::interface<TAG_NAME>

#define OTTO_PROPS_MIXIN__NAME_REQUIRES(...) REQUIRES
#define OTTO_PROPS_MIXIN__ARGS_REQUIRES(...) __VA_ARGS__
#define OTTO_PROPS_MIXIN__NAME_HOOKS(...) HOOKS
#define OTTO_PROPS_MIXIN__ARGS_HOOKS(...) __VA_ARGS__
#define OTTO_PROPS_MIXIN__NAME_INTERFACE(...) INTERFACE
#define OTTO_PROPS_MIXIN__ARGS_INTERFACE(...) __VA_ARGS__
#define OTTO_PROPS_MIXIN__NAME_LEAF(...) LEAF
#define OTTO_PROPS_MIXIN__ARGS_LEAF(...) __VA_ARGS__
#define OTTO_PROPS_MIXIN__NAME_BRANCH(...) BRANCH
#define OTTO_PROPS_MIXIN__ARGS_BRANCH(...) __VA_ARGS__
#define OTTO_PROPS_MIXIN__NAME_TAG(...) TAG
#define OTTO_PROPS_MIXIN__ARGS_TAG(...) __VA_ARGS__

#define OTTO_PROPS_ADD_PREFIX(MACRO) OTTO_PROPS_MIXIN_##MACRO

#define OTTO_PROPS_MAKE_CALL(TAG_NAME, MACRO)                                                      \
  DEFER(OTTO_PROPS_ADD_PREFIX)                                                                     \
  (OTTO_PROPS_MIXIN__NAME_##MACRO(TAG_NAME, OTTO_PROPS_MIXIN__ARGS_##MACRO));

#define OTTO_PROPS_MIXIN_SCOPE(TAG_NAME, ...)                                                      \
  EXPAND(FOR_EACH_LAST(OTTO_PROPS_MAKE_CALL, (TAG_NAME), __VA_ARGS__))

/// \exclude
#define OTTO_PROPS_MIXIN_2(TAG_NAME, ...)                                                          \
  OTTO_PROPS_MIXIN_TAG(TAG_NAME);                                                                  \
  OTTO_PROPS_MIXIN_SCOPE(TAG_NAME, __VA_ARGS__)                                                    \
  inline char _##TAG_NAME##_do_not_warn_about_too_many_semicolons

/// \exclude
#define OTTO_PROPS_MIXIN_1(TAG_NAME) OTTO_PROPS_MIXIN_TAG(TAG_NAME)

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
#define OTTO_PROPS_MIXIN(...)                                                                      \
  /* Call OTTO_PROPS_MIXIN_1 if only 1 argument was provided, and */                               \
  /* OTTO_PROPS_MIXIN_2 if multiple args were provided */                                          \
  SWITCH_FOR_VARARGS_1(OTTO_PROPS_MIXIN_1, OTTO_PROPS_MIXIN_2, __VA_ARGS__)

#endif // OTTO_PROPS_MIXIN__MACROS_DEFINED
