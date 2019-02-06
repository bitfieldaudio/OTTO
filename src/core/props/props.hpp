#pragma once

#include <string>
#include <vector>

#include "internal/property.hpp"
#include "mixins/all.hpp"

/// The property system
///
/// The property system is used for serialization, faust linking, encoder-stepping and more
/// of variables, mainly on engines.
///
/// \warning The implementation of this relies on a lot of template metaprogramming and
/// generally complicated C++. You don't need to know how it works, but I'll try to explain how
/// to use it.
namespace otto::core::props {

  template<typename T, typename Enable>
  struct default_mixins {
    using type = std::conditional_t<std::is_enum_v<T>,
                                    tag_list<serializable, change_hook, has_limits, steppable>,
                                    tag_list<serializable, change_hook>>;
  };

  template<>
  struct default_mixins<int> {
    using type = tag_list<serializable, faust_link, change_hook, has_limits, steppable>;
  };

  template<>
  struct default_mixins<bool> {
    using type = tag_list<serializable, faust_link, change_hook, steppable>;
  };

  template<>
  struct default_mixins<float> {
    using type = tag_list<serializable, faust_link, change_hook, has_limits, steppable>;
  };

  template<>
  struct default_mixins<double> {
    using type = tag_list<serializable, faust_link, change_hook, has_limits, steppable>;
  };

  // Void is for branches
  template<>
  struct default_mixins<void> {
    using type = tag_list<serializable, faust_link>;
  };

  /// A property of type `ValueType` with mixins `Tags...`
  template<typename ValueType, typename... Tags>
  using Property = PropertyImpl<ValueType, meta::_t<get_tag_list<ValueType, Tags...>>>;

  template<typename... Tags>
  struct Properties : meta::_t<detail::properties_for_list<meta::_t<get_tag_list<void, Tags...>>>> {
    /// \private
    using Super = meta::_t<detail::properties_for_list<meta::_t<get_tag_list<void, Tags...>>>>;

    using typename Super::tag_list;

    /// \private
    using Super::Super;
  };

  using no_serialize = no<serializable>;
} // namespace otto::core::props
