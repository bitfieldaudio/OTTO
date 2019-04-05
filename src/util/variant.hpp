#pragma once

#include <mpark/variant.hpp>

/// @file
///
/// Declare a `variant` class in `otto::util`, because some compilers still don't completely
/// implement the C++17 variant. For now this uses mpark::variant, but in the future, std::variant
/// could be used instead.

namespace otto::util {
  using namespace mpark;
}
