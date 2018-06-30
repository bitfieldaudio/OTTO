#pragma once

#include <string>
#include <vector>

#include "internal/property.hpp"
#include "mixins/all.hpp"

namespace otto::core::props {

  template<typename ValueType>
  struct default_mixins {
    using type = tag_list<serializable>;
  };

  template<>
  struct default_mixins<int> {
    using type = tag_list<serializable, faust_link, has_limits, steppable>;
  };

  template<>
  struct default_mixins<bool> {
    using type = tag_list<serializable, faust_link, steppable>;
  };

  template<>
  struct default_mixins<float> {
    using type = tag_list<serializable, faust_link, has_limits, steppable>;
  };

  template<>
  struct default_mixins<double> {
    using type = tag_list<serializable, faust_link, has_limits, steppable>;
  };

  // Void is for branches
  template<>
  struct default_mixins<void> {
    using type = tag_list<serializable, faust_link>;
  };

  template<typename ValueType, typename... Tags>
  using Property = PropertyImpl<ValueType, meta::_t<get_tag_list<ValueType, Tags...>>>;
  
  using no_serialize = no<serializable>;
}
