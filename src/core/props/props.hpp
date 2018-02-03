#pragma once

#include <string>
#include <vector>

#include "util/type_traits.hpp"

#include "base.hpp"
#include "macros.hpp"
#include "mixins.hpp"

namespace otto::core::props {

  struct Properties {
    // Accessors //

    std::size_t size() const noexcept;

    PropertyBase& operator[](std::size_t) noexcept;
    const PropertyBase& operator[](std::size_t) const noexcept;

    // Iterators //

    auto begin();
    auto end();
    auto begin() const;
    auto end() const;
    auto cbegin() const;
    auto cend() const;
  };

} // namespace otto::core::props
