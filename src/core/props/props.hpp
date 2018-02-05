#pragma once

#include <string>
#include <vector>

#include "util/type_traits.hpp"

#include "base.hpp"
#include "macros.hpp"

namespace otto::core::props {

  // PropertyBase /////////////////////////////////////////////////////////////

  /// Base class of all properties
  struct PropertyBase {};

  /// Equality compare two PropertyBase's
  ///
  /// \returns `&lhs == &rhs`
  bool operator==(const PropertyBase& lhs, const PropertyBase& rhs)
  {
    return &lhs == &rhs;
  }

  /// Inequality compare two PropertyBase's
  ///
  /// \returns `&lhs != &rhs`
  bool operator!=(const PropertyBase& lhs, const PropertyBase& rhs)
  {
    return &lhs != &rhs;
  }

  // PropertyImpl /////////////////////////////////////////////////////////////

  template<typename T, typename TagList>
  struct PropertyImpl : PropertyBase, inherits_from_mixins_t<T, TagList> {
    using value_type = T;
    using tag_list_t = TagList;
    constexpr static tag_list_t tag_list;

    template<typename Tag>
    using mixin = MixinTag::mixin_t<Tag, T, tag_list_t>;

    using inherits_from_mixins_t<T, TagList>::inherits_from_mixins_t;
    using inherits_from_mixins_t<T, TagList>::operator=;

    /// Initialize the mixin of type `Tag` with args
    template<typename Tag, typename... Args>
    auto init(Args&&... args)
      -> std::enable_if_t<contains_tag_v<tag_list_t, Tag>,
                          decltype(mixin<Tag>::init(std::declval<Args>()...),
                                   std::declval<PropertyImpl&>())>
    {
      mixin<Tag>::init(std::forward<Args>(args)...);
      return *this;
    }

    template<typename Tag>
    constexpr static bool is =
      ::otto::core::props::contains_tag_v<tag_list_t, Tag>;

    template<typename Tag>
    constexpr auto as() -> ::std::enable_if_t<
      PropertyImpl::is<Tag>,
      MixinTag::mixin_t<Tag, value_type, tag_list_t>&>
    {
      return static_cast<
        MixinTag::mixin_t<Tag, value_type, tag_list_t>&>(*this);
    }

    template<typename Tag>
    constexpr auto as() const -> ::std::enable_if_t<
      PropertyImpl::is<Tag>,
      const MixinTag::mixin_t<Tag, value_type, tag_list_t>&>
    {
      return static_cast<const MixinTag::mixin_t<Tag, value_type, tag_list_t>&>(
        *this);
    }

    template<typename Hook>
    using hook = HookTag::impl_t<Hook, value_type>;

    template<typename Hook>
    typename hook<Hook>::arg_type run_hook(
      const typename hook<Hook>::arg_type& arg)
    {
      return ::otto::core::props::detail::run_hook<Hook>(*this, arg);
    }

    template<typename Hook>
    typename hook<Hook>::arg_type run_hook(
      const typename hook<Hook>::arg_type& arg) const
    {
      return ::otto::core::props::detail::run_hook<Hook>(*this, arg);
    }
  };

  template<typename ValueType, typename... Tags>
  using Property = PropertyImpl<ValueType, make_tag_list_t<Tags...>>;

  // Properties ////////////////////////////////////////////////////////////////

  template<typename... Tags>
  struct Properties {

    using tag_list_t = tag_list<Tags...>;
    using interface_storage_type = std::tuple<MixinTag::branch_interface<Tags>...>;

    // Initialization //

    template<typename... Fields>
    Properties(Fields&... fields) {
      // Fold expression with comma operator
      (init_field(fields), ...);
    }

    template<typename Field>
    void init_field(Field& f) {
      boost::hana::for_each(tag_list_t(), [&] (auto ttype) {
          using Tag = typename decltype(+ttype)::type;
          std::get<MixinTag::branch_interface<Tag>>(storage_).push_back(
            f.interface());
        });
    }

    template<typename Tag>
    MixinTag::branch_interface<Tag>& interface() {
      return std::get<MixinTag::branch_interface<Tag>>(storage_);
    }

  private:
    interface_storage_type storage_;
  };

} // namespace otto::core::props

#include "mixins.hpp"
