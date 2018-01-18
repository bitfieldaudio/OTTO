#pragma once

#include "tag_list.hpp"

namespace otto::core::props {

  // PropertyBase /////////////////////////////////////////////////////////////

  template<typename T, typename TagList>
  struct PropertyImpl : inherits_from_mixins_t<T, TagList> {

    using tag_list_t = TagList;
    constexpr static tag_list_t tag_list;

    template<typename Tag>
    using mixin = tag_mixin_t<Tag, T, tag_list_t>;

    /// Initialize the mixin of type `Tag` with args
    template<typename Tag, typename... Args>
    auto init(Args&&... args) -> std::enable_if_t<
      hana::contains(tag_list, hana::type_c<Tag>),
      decltype(mixin<Tag>::init(std::declval<Args>()...),
        std::declval<PropertyImpl&>())>
    {
      mixin<Tag>::init(std::forward<Args>(args)...);
      return *this;
    }


  };

  template<typename ValueType, typename... Tags>
  using Property = PropertyImpl<ValueType, make_tag_list_t<Tags...>>;

}
