#pragma once

#include <tl/optional.hpp>

#include "lib/util/enum.hpp"

#include "app/services/controller.hpp"

namespace otto::board::controller {

  using services::Key;

  struct HardwareMap {
    virtual ~HardwareMap() noexcept = default;
    virtual int row_count() const noexcept = 0;
    virtual int col_count() const noexcept = 0;
    virtual tl::optional<Key> key_at(std::uint8_t row, std::uint8_t col) const noexcept = 0;
    virtual std::uint8_t led_for(Key) const noexcept = 0;
  };

  template<int Rows, int Cols>
  using KeyMatrix = std::array<std::array<tl::optional<Key>, Cols>, Rows>;
  using LedSequence = util::enum_map<Key, std::uint8_t>;

} // namespace otto::board::controller
