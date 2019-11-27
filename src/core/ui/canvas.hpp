#pragma once

#include <functional>
#include <type_traits>
#include <valarray>

#include "nvg/Canvas.hpp"

#include "choreograph/Choreograph.h"

#include "util/iterator.hpp"
#include "util/math.hpp"

namespace otto::core::ui::vg {

  using namespace otto::nvg;

  struct MainColor : public Color {
    const Color dimmed;

    // cppcheck-suppress noExplicitConstructor
    constexpr MainColor(Color basic) : Color(basic), dimmed(basic.dim(0)) {}

    constexpr MainColor(Color basic, Color dimmed) noexcept : Color(basic), dimmed(dimmed) {}

    // cppcheck-suppress noExplicitConstructor
    constexpr MainColor(std::uint32_t basic) : Color(basic), dimmed(dim(0.1)) {}

    constexpr MainColor(std::uint32_t basic, std::uint32_t dimmed) : Color(basic), dimmed(dimmed) {}
  };

} // namespace otto::core::ui::vg
