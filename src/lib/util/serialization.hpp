#pragma once

#include "lib/util/visitor.hpp"

#include "lib/toml.hpp"

namespace otto::util {

  /// Used to implement serialization/deserialization functions for objects.
  ///
  /// Specialize this, and implement the following two functions
  /// ```cpp
  /// static void serialize(toml::value& toml, const T& value);
  /// static void deserialize(const toml::value& toml, T& value);
  /// ```
  template<typename T>
  struct serialize_impl;

  template<typename T>
  concept ASerializable = requires(toml::value toml, T t)
  {
    serialize_impl<std::decay_t<T>>::serialize(toml, t);
    serialize_impl<std::decay_t<T>>::deserialize(toml, t);
  };

  void serialize_into(toml::value& toml, const ASerializable auto& obj)
  {
    serialize_impl<std::decay_t<decltype(obj)>>::serialize(toml, obj);
  }

  void deserialize_into(const toml::value& toml, ASerializable auto& obj)
  {
    serialize_impl<std::decay_t<decltype(obj)>>::deserialize(toml, obj);
  }

  toml::value serialize(const ASerializable auto& obj)
  {
    toml::value res;
    serialize_into(res, obj);
    return res;
  }

  template<ASerializable T>
  requires(std::is_default_constructible_v<T>) //
    T deserialize(const toml::value& toml)
  {
    T res = {};
    deserialize_into(toml, res);
    return res;
  }

  // Specializations

  template<toml::ATomlSerializable T>
  struct serialize_impl<T> {
    static void serialize(toml::value& toml, const T& value)
    {
      toml = value;
    }
    static void deserialize(const toml::value& toml, T& value)
    {
      value = toml::get<T>(toml);
    }
  };

  template<AVisitable T>
  requires(!toml::ATomlSerializable<T>) struct serialize_impl<T> {
    static void serialize(toml::value& toml, const T& value)
    {
      if (toml.type() == toml::value_t::empty) toml = toml::table();
      value.visit(
        [&](util::string_ref name, const auto& member) { serialize_into(toml.as_table()[name.c_str()], member); });
    }
    static void deserialize(const toml::value& toml, T& value)
    {
      value.visit(
        [&](util::string_ref name, auto& member) { deserialize_into(toml::find(toml, name.c_str()), member); });
    }
  };

} // namespace otto::util
