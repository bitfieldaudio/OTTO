#pragma once

#include "base.hpp"
#include "tag_list.hpp"

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
    using tag_list = TagList;

    template<typename Tag>
    using mixin = MixinTag::mixin_t<Tag, T, tag_list>;

    using inherits_from_mixins_t<T, TagList>::inherits_from_mixins_t;
    using inherits_from_mixins_t<T, TagList>::operator=;

    template<typename... Args>
    PropertyImpl(Args&&... args)
    {
      if constexpr ((is_initializer_v<Args> && ...)) {
        // lambda and fold expression on comma operator
        ([](auto* obj, auto&& tuple) { obj->init_with_tuple(tuple); }(
           this, std::forward<Args>(args)),
         ...);
      } else {
        static_cast<inherits_from_mixins_t<T, TagList>&>(*this) = {
          std::forward<Args>(args)...};
      }
    }

    /// Initialize the mixin of type `Tag` with args
    template<typename Tag, typename... Args>
    auto init(Args&&... args)
      -> std::enable_if_t<contains_tag_v<tag_list, Tag>,
                          decltype(mixin<Tag>::init(std::declval<Args>()...),
                                   std::declval<PropertyImpl&>())>
    {
      mixin<Tag>::init(std::forward<Args>(args)...);
      return *this;
    }

    template<typename Tag, typename... Args>
    auto init_with_tuple(const TaggedTuple<Tag, Args...>& tt)
      -> std::enable_if_t<contains_tag_v<tag_list, Tag>,
                          decltype(mixin<Tag>::init(std::declval<Args>()...),
                                   std::declval<PropertyImpl&>())>
    {
      // Clang is bugged, and marks the `this` capture as unused
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-lambda-capture"
      std::apply([this](auto&&... init_args) {init<Tag>(init_args...);}, tt.args);
#pragma clang diagnostic pop
      return *this;
    }

    template<typename Tag>
    constexpr static bool is =
      ::otto::core::props::contains_tag_v<tag_list, Tag>;

    template<typename Tag>
    constexpr auto as() -> ::std::enable_if_t<
      PropertyImpl::is<Tag>,
      MixinTag::mixin_t<Tag, value_type, tag_list>&>
    {
      return static_cast<
        MixinTag::mixin_t<Tag, value_type, tag_list>&>(*this);
    }

    template<typename Tag>
    constexpr auto as() const -> ::std::enable_if_t<
      PropertyImpl::is<Tag>,
      const MixinTag::mixin_t<Tag, value_type, tag_list>&>
    {
      return static_cast<const MixinTag::mixin_t<Tag, value_type, tag_list>&>(
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

  // Properties ////////////////////////////////////////////////////////////////

  template<typename... Tags>
  struct Properties {

    using tag_list = props::tag_list<Tags...>;
    using interface_storage_type = std::tuple<MixinTag::branch_interface<Tags>...>;

    // Initialization //

    template<typename... Fields>
    Properties(Fields&... fields) {
      // Fold expression with comma operator
      (init_field(fields), ...);
    }

    template<typename Field>
    void init_field(Field& f) {
      meta::for_each<tag_list>([&] (auto ttype) {
          using Tag = meta::_t<decltype(ttype)>;
          std::get<MixinTag::branch_interface<Tag>>(storage_).push_back(
            f.interface());
        });
    }

    template<typename Tag>
    MixinTag::branch_interface<Tag>& interface() {
      return std::get<MixinTag::branch_interface<Tag>>(storage_);
    }

  private:
    std::string name_;
    interface_storage_type storage_{MixinTag::branch_interface<Tags>(name_)...};
  };

} // namespace otto::core::props
