#pragma once

#include <functional>
#include <type_traits>
#include <valarray>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wunused-function"
#include <NanoCanvas.hpp>
#include <nanovg.h>
#pragma GCC diagnostic pop

#include "util/iterator.hpp"
#include "util/math.hpp"

namespace otto::core::ui::vg {

  using namespace NanoCanvas;
  using Colour = Color;

  struct MainColour : public Color {
    const Color dimmed;

    // cppcheck-suppress noExplicitConstructor
    MainColour(Colour basic) : Colour(basic), dimmed(basic.dim(0)) {}

    MainColour(Colour basic, Colour dimmed) : Colour(basic), dimmed(dimmed) {}

    // cppcheck-suppress noExplicitConstructor
    MainColour(std::uint32_t basic) : Colour(basic), dimmed(dim(0.1)) {}

    MainColour(std::uint32_t basic, std::uint32_t dimmed) : Colour(basic), dimmed(dimmed) {}
  };

} // namespace otto::core::ui::vg
