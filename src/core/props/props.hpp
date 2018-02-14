#pragma once

#include <string>
#include <vector>

#include "internal/property.hpp"
#include "mixins/all.hpp"

namespace otto::core::props {

  template<typename ValueType>
  struct default_mixins {
    using type = tag_list<has_value, serializable>;
  };

  template<>
  struct default_mixins<int> {
    using type = tag_list<has_value, has_limits, steppable>;
  };

  template<>
  struct default_mixins<bool> {
    using type = tag_list<has_value, steppable>;
  };

  template<>
  struct default_mixins<float> {
    using type = tag_list<has_value, has_limits, steppable>;
  };

  template<>
  struct default_mixins<double> {
    using type = tag_list<has_value, has_limits, steppable>;
  };

  struct no_defaults {};

  template<typename Tag>
  struct no {};

  namespace detail {
    template<typename Tag>
    struct is_disabler {
      constexpr static bool value = false;
      using type = void;
    };

    template<typename Tag>
    struct is_disabler<no<Tag>> {
      constexpr static bool value = true;
      using type = Tag;
    };
  }

  template<typename TagList>
  struct remove_disabled_tags {
    using disablers = meta::filter_t<TagList, detail::is_disabler>;
    template<typename T>
    using is_disabled = meta::contains<disablers, no<T>>;
    using after_disable = meta::remove_if_t<TagList, is_disabled>;
    using type = meta::remove_if_t<after_disable, detail::is_disabler>;
  };

  template<typename ValueType, typename... Tags>
  struct get_tag_list {
    using defaults =
      std::conditional_t<meta::contains_v<tag_list<Tags...>, no_defaults>,
                         tag_list<>,
                         default_mixins<ValueType>>;
    using after_disable = meta::_t<remove_disabled_tags<meta::concat_t<defaults, tag_list<Tags...>>>>;
    using type = meta::_t<normalize_tags<
      meta::_t<add_required<after_disable>>>>;
  };

  template<typename ValueType, typename... Tags>
  using Property = PropertyImpl<ValueType, meta::_t<get_tag_list<ValueType, Tags...>>>;

  using no_serialize = no<serializable>;
}
