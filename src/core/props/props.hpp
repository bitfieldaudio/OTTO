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
                                    tag_list<change_hook, has_limits, steppable>,
                                    tag_list<change_hook>>;
  };

  template<>
  struct default_mixins<int> {
    using type = tag_list<change_hook, has_limits, steppable>;
  };

  template<>
  struct default_mixins<bool> {
    using type = tag_list<change_hook, steppable>;
  };

  template<>
  struct default_mixins<float> {
    using type = tag_list<change_hook, has_limits, steppable>;
  };

  template<>
  struct default_mixins<double> {
    using type = tag_list<change_hook, has_limits, steppable>;
  };

  // Void is for branches
  template<>
  struct default_mixins<void> {
    using type = tag_list<>;
  };

  /// A property of type `ValueType` with mixins `Tags...`
  template<typename ValueType, typename... Tags>
  using Property = PropertyImpl<ValueType, meta::_t<get_tag_list<ValueType, Tags...>>>;
} // namespace otto::core::props

// reflect a property directly to its value type
// For serialization, this means you get { "property": 13 }
// instead of { "property": { "value": 13 } }

namespace otto::reflect {
  template<typename Class, typename ValueType, typename... Tags>
  constexpr auto member(util::string_ref name,
                        util::member_ptr<Class, core::props::Property<ValueType, Tags...>> memptr)
  {
    return member<Class>(
      name, [memptr](const Class& obj) -> const ValueType& { return (obj.*memptr).get(); },
      [memptr](Class& obj, const ValueType& val) { return (obj.*memptr).set(val); });
  }
} // namespace otto::reflect
