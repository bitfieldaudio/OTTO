#pragma once

#include <filesystem>

#include <nlohmann/json.hpp>

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
} // namespace otto::json
