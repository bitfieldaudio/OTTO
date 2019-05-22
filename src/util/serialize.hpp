#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <json.hpp>

#include "util/reflection.hpp"
#include "util/string_conversions.hpp"

using json = nlohmann::json;

template<typename T>
void to_json(json& j, T&& t);

template<typename T>
void from_json(const json& j, T& t);

namespace otto::util {

  /////////////////// SERIALIZATION

  template<typename Class, typename = std::enable_if_t<reflect::is_registered<Class>()>>
  json serialize(const Class& obj);

  template<typename Class,
           typename = std::enable_if_t<!reflect::is_registered<Class>()>,
           typename = void>
  json serialize(const Class& obj);

  template<typename Class>
  json serialize_basic(const Class& obj);

  // specialization for std::array
  template<typename T, std::size_t N>
  json serialize_basic(const std::array<T, N>& obj);


  // specialization for std::vector
  template<typename T>
  json serialize_basic(const std::vector<T>& obj);

  // specialization for std::unodered_map
  template<typename K, typename V>
  json serialize_basic(const std::unordered_map<K, V>& obj);


  /////////////////// DESERIALIZATION

  template<typename Class, typename = std::enable_if_t<reflect::is_registered<Class>()>>
  void deserialize(Class& obj, const json& object);

  template<typename Class,
           typename = std::enable_if_t<!reflect::is_registered<Class>()>,
           typename = void>
  void deserialize(Class& obj, const json& object);

  // specialization for std::array
  template<typename T, std::size_t N>
  void deserialize(std::array<T, N>& obj, const json& object);

  // specialization for std::vector
  template<typename T>
  void deserialize(std::vector<T>& obj, const json& object);

  // specialization for std::unodered_map
  template<typename K, typename V>
  void deserialize(std::unordered_map<K, V>& obj, const json& object);

} // namespace otto::util

#include "serialize.inl"

// kak: other_file=serialize.inl
