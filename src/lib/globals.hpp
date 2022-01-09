#pragma once

#include <filesystem>

namespace otto::globals {
  namespace init {
    void resource_dir(std::filesystem::path) noexcept;
    void data_dir(std::filesystem::path) noexcept;
  } // namespace init

  const std::filesystem::path& resource_dir() noexcept;
  const std::filesystem::path& data_dir() noexcept;
} // namespace otto::globals
