#pragma once

#include <filesystem>

#include <nlohmann/json.hpp>

namespace otto::json {

  using value = nlohmann::json;
  using array = nlohmann::json::array_t;
  using object = nlohmann::json::object_t;
  using string = nlohmann::json::string_t;

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
