#pragma once

#include <string>
#include <vector>

#include "internal/property.hpp"
#include "mixins/all.hpp"
#include "util/serialize.hpp"

/// The property system
///
/// The property system is used for serialization, encoder-stepping and more
/// of variables, mainly on engines.
///
/// \warning The implementation of this relies on a lot of template metaprogramming and
/// generally complicated C++. You don't need to know how it works, but I'll try to explain how
/// to use it.
namespace otto::core::props {

  template<typename T, typename Enable>
  struct default_mixins {
    using type = std::conditional_t<std::is_enum_v<T> || util::BetterEnum::is<T>,
                                    tag_list<observable, has_limits, steppable>,
                                    tag_list<observable>>;
  };

  template<>
  struct default_mixins<int> {
    using type = tag_list<observable, has_limits, steppable>;
  };

  template<>
  struct default_mixins<bool> {
    using type = tag_list<observable, steppable>;
  };

  template<>
  struct default_mixins<float> {
    using type = tag_list<observable, has_limits, steppable>;
  };

  template<>
  struct default_mixins<double> {
    using type = tag_list<observable, has_limits, steppable>;
  };

  // Void is for branches
  template<>
  struct default_mixins<void> {
    using type = tag_list<>;
  };

  using no_observable = no<observable>;

  /// A property of type `ValueType` with mixins `Tags...`
  ///
  /// Properties
  template<typename ValueType, typename... Tags>
  using Property = PropertyImpl<ValueType, meta::_t<get_tag_list<ValueType, Tags...>>>;

  /// Serialize a property to json
  template<typename ValueType, typename TagList>
  inline nlohmann::json serialize(const PropertyImpl<ValueType, TagList>& prop)
  {
    using ::otto::util::serialize;
    return serialize(prop.get());
  }

  /// Deserialize a property from json
  template<typename ValueType, typename TagList>
  inline void deserialize(PropertyImpl<ValueType, TagList>& prop, const nlohmann::json& json)
  {
    using ::otto::util::deserialize;
    static_assert(std::is_default_constructible_v<ValueType>,
                  "A property type must be default constructible to be deserializable");
    ValueType v{};
    deserialize(v, json);
    prop.set(std::move(v));
  }


  template<typename ValueType, typename TagList>
  void to_json(nlohmann::json& j, PropertyImpl<ValueType, TagList>& t)
  {
    j = serialize(t);
  }

  template<typename ValueType, typename TagList>
  void to_json(nlohmann::json& j, const PropertyImpl<ValueType, TagList>& t)
  {
    j = serialize(t);
  }

  template<typename ValueType, typename TagList>
  void to_json(nlohmann::json& j, PropertyImpl<ValueType, TagList>&& t)
  {
    j = serialize(std::move(t));
  }

  template<typename ValueType, typename TagList>
  void from_json(const nlohmann::json& j, PropertyImpl<ValueType, TagList>& t)
  {
    deserialize(t, j);
  }
} // namespace otto::core::props
