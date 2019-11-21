#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <json.hpp>

#include "util/reflection.hpp"
#include "util/string_conversions.hpp"

template<typename T>
void to_json(nlohmann::json& j, T&& t);

template<typename T>
void from_json(const nlohmann::json& j, T& t);

namespace otto::util {

  /////////////////// SERIALIZATION

  template<typename Class, typename = std::enable_if_t<reflect::is_registered<Class>()>>
  nlohmann::json serialize(const Class& obj);

  template<typename Class,
           typename = std::enable_if_t<!reflect::is_registered<Class>()>,
           typename = void>
  nlohmann::json serialize(const Class& obj);

  template<typename Class>
  nlohmann::json serialize_basic(const Class& obj);

  // specialization for std::array
  template<typename T, std::size_t N>
  nlohmann::json serialize_basic(const std::array<T, N>& obj);


  // specialization for std::vector
  template<typename T>
  nlohmann::json serialize_basic(const std::vector<T>& obj);

  // specialization for std::unodered_map
  template<typename K, typename V>
  nlohmann::json serialize_basic(const std::unordered_map<K, V>& obj);


  /////////////////// DESERIALIZATION

  template<typename Class, typename = std::enable_if_t<reflect::is_registered<Class>()>>
  void deserialize(Class& obj, const nlohmann::json& object);

  template<typename Class,
           typename = std::enable_if_t<!reflect::is_registered<Class>()>,
           typename = void>
  void deserialize(Class& obj, const nlohmann::json& object);

  // specialization for std::array
  template<typename T, std::size_t N>
  void deserialize(std::array<T, N>& obj, const nlohmann::json& object);

  // specialization for std::vector
  template<typename T>
  void deserialize(std::vector<T>& obj, const nlohmann::json& object);

  // specialization for std::unodered_map
  template<typename K, typename V>
  void deserialize(std::unordered_map<K, V>& obj, const nlohmann::json& object);

} // namespace otto::util

#include "serialize.inl"

// kak: other_file=serialize.inl
