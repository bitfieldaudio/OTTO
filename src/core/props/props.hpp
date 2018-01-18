#pragma once

#include <string>

#include "util/type_traits.hpp"

#include "macros.hpp"
#include "base.hpp"
#include "mixins.hpp"

namespace otto::core::props {

  // User facing classes

  /// Leaf property
  // template<typename T>
  // struct Leaf : PropertyBase<T> {};

  // /// Branch property. Can have branch/leaf children
  // template<typename T>
  // struct Branch : PropertyBase<T> {};

  /// Trunk property. Can have branch/leaf children
  struct Trunk {};

} // namespace otto::core::props
