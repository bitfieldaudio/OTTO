#pragma once

#include "lib/util/visitor.hpp"

#include "lib/toml.hpp"

namespace otto::util {

  /// Used to implement serialization/deserialization functions for objects.
  ///
  /// Specialize this, and implement the following two functions
  /// ```cpp
  /// static void serialize_into(toml::value& toml, const T& value);
  /// static void deserialize_from(const toml::value& toml, T& value);
  /// ```
  template<typename T, unsigned order = 3>
  struct serialize_impl;

  template<typename T>
  concept ASerializable = requires(toml::value toml, T t)
  {
    serialize_impl<std::decay_t<T>>::serialize_into(toml, t);
    serialize_impl<std::decay_t<T>>::deserialize_from(toml, t);
  };

  void serialize_into(toml::value& toml, const ASerializable auto& obj)
  {
    serialize_impl<std::decay_t<decltype(obj)>>::serialize_into(toml, obj);
  }

  void deserialize_from(const toml::value& toml, ASerializable auto& obj)
  {
    serialize_impl<std::decay_t<decltype(obj)>>::deserialize_from(toml, obj);
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
    deserialize_from(toml, res);
    return res;
  }

  // Specializations

  template<typename T, unsigned Order>
  struct serialize_impl : serialize_impl<T, Order - 1> {};

  template<typename T>
  struct serialize_impl<T, 0> {};

  template<toml::ATomlSerializable T>
  struct serialize_impl<T, 0> {
    static void serialize_into(toml::value& toml, const T& value)
    {
      toml = value;
    }
    static void deserialize_from(const toml::value& toml, T& value)
    {
      value = toml::get<T>(toml);
    }
  };


  template<typename T>
  requires requires(const toml::value& ctoml, toml::value& toml, T& obj, const T& cobj)
  {
    cobj.serialize_into(toml);
    obj.deserialize_from(ctoml);
  } //
  struct serialize_impl<T, 2> {
    static void serialize_into(toml::value& toml, const T& value)
    {
      value.serialize_into(toml);
    }
    static void deserialize_from(const toml::value& toml, T& value)
    {
      value.deserialize_from(toml);
    }
  };

  template<AVisitable T>
  struct serialize_impl<T, 1> {
    static void serialize_into(toml::value& toml, const T& value)
    {
      if (toml.type() == toml::value_t::empty) toml = toml::table();
      value.visit([&](util::string_ref name, const auto& member) {
        util::serialize_into(toml.as_table()[name.c_str()], member);
      });
    }
    static void deserialize_from(const toml::value& toml, T& value)
    {
      value.visit(
        [&](util::string_ref name, auto& member) { util::deserialize_from(toml::find(toml, name.c_str()), member); });
    }
  };

} // namespace otto::util
