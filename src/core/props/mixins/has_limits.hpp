#pragma once

#include "services/logger.hpp"

#include "../internal/mixin_macros.hpp"
#include "../internal/property.hpp"

namespace otto::core::props {

  OTTO_PROPS_MIXIN(has_limits);

  template<>
  struct mixin::hooks<has_limits> {
    struct on_exceeded {
      template<typename Val, HookOrder HO>
      struct type : hook<value_type>::type<Val, HO> {};
    };
  };

  OTTO_PROPS_MIXIN_LEAF (has_limits) {
    using value_type     = ValueType;
    using tag_list       = TagList;
    using self_type      = leaf<has_limits, value_type, tag_list>;
    using interface_type = ::otto::core::props::MixinTag::interface<has_limits>;
    using property_type =
      ::otto::core::props::PropertyImpl<value_type, tag_list>;

    template<typename Tag>
    constexpr static bool is =
      ::otto::core::props::contains_tag_v<tag_list, Tag>;

    template<typename Tag>
    constexpr auto as()
      ->::std::enable_if_t<
        self_type::is<Tag>,
        ::otto::core::props::MixinTag::leaf<Tag, value_type, tag_list>&>
    {
      auto* as_prop = static_cast<property_type*>(this);
      return static_cast<
        ::otto::core::props::MixinTag::leaf<Tag, value_type, tag_list>&>(
        *as_prop);
    }

    template<typename Tag>
    constexpr auto as() const->::std::enable_if_t<
      self_type::is<Tag>,
      const ::otto::core::props::MixinTag::leaf<Tag, value_type, tag_list>&>
    {
      const auto& as_prop = static_cast<const property_type&>(*this);
      return static_cast<
        const ::otto::core::props::MixinTag::leaf<Tag, value_type, tag_list>&>(
        as_prop);
    }

    template<typename HT, ::otto::core::props::HookOrder HO =
                            ::otto::core::props::HookOrder::Middle>
    using hook = HookTag::impl_t<HT, value_type, HO>;

    template<typename HT,
             CONCEPT_REQUIRES_(::ranges::concepts::models<
                               ::otto::core::props::HookTag, HT, value_type>())>
    typename hook<HT>::arg_type run_hook(const typename hook<HT>::arg_type& arg)
    {
      return ::otto::core::props::detail::run_hook<HT>(*this, arg);
    }

    template<typename HT>
    typename hook<HT>::arg_type run_hook(const typename hook<HT>::arg_type& arg)
      const
    {
      return ::otto::core::props::detail::run_hook<HT>(*this, arg);
    }

    using hooks = ::otto::core::props::mixin::hooks<has_limits>;

    void init(const value_type& pmin, const value_type& pmax)
    {
      min = pmin;
      max = pmax;
    }

    void on_hook(hook<common::hooks::on_set, HookOrder::Early> & hook)
    {
      auto& val = hook.value();
      if (val < min) {
        auto hv      = run_hook<hooks::on_exceeded>(val);
        hook.value() = hv == val ? min : hv;
      } else if (val > max) {
        auto hv      = run_hook<hooks::on_exceeded>(val);
        hook.value() = hv == val ? max : hv;
      }
    }

    value_type normalize() const
    {
      auto& prop = dynamic_cast<property_type const&>(*this);
      return (prop.get() - min) / (max - min);
    }

    value_type min;
    value_type max;
  };

} // namespace otto::core::props
