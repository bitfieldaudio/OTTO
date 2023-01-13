#pragma once

#include <filesystem>

#include <nlohmann/json.hpp>
#include <tl/optional.hpp>

namespace otto::json {

  using value = nlohmann::json;
  using array = value::array_t;
  using object = value::object_t;
  using string = value::string_t;
  using type = value::value_t;
  using pointer = value::json_pointer;

  const value null = nullptr;

  template<typename T>
  concept AJsonSerializable = requires(value& j, T& t)
  {
    j.get<T>();
    j = t;
  };

  value parse_file(const std::filesystem::path& path);
  void write_to_file(const value& v, const std::filesystem::path& path);

  /// Get a json value by key, or, if it does not exist or the object is null, return null
  inline const value& get_or_null(const value& json, std::string_view key)
  {
    static const value null = value();

    if (json.is_null()) return null;
    if (json.count(key) == 0) return null;
    return json[key];
  }

  /// Get a json value by key, or, if it does not exist or the object is null, return null
  inline const value& get_or_null(const value& json, std::size_t key)
  {
    static const value null = value();

    if (json.is_null()) return null;
    if (json.size() >= key) return null;
    return json[key];
  }
} // namespace otto::json
