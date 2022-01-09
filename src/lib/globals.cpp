#include "globals.hpp"

namespace otto::globals {
  namespace {
    std::filesystem::path resource_dir_ = "./resources";
    std::filesystem::path data_dir_ = "./data";
  } // namespace

  const std::filesystem::path& resource_dir() noexcept
  {
    return resource_dir_;
  }
  const std::filesystem::path& data_dir() noexcept
  {
    return data_dir_;
  }
  namespace init {
    void data_dir(std::filesystem::path d) noexcept
    {
      data_dir_ = std::move(d);
    }
    void resource_dir(std::filesystem::path d) noexcept
    {
      resource_dir_ = std::move(d);
    }
  } // namespace init
} // namespace otto::globals
