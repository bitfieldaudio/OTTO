#pragma once

#include <type_traits>

namespace otto::util {
  
  /// Any arithmetic type except bool
  template<typename T>
  concept numeric = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>; 
  
  // Quick test
  static_assert(numeric<int>);
  static_assert(numeric<float>);
  static_assert(!numeric<bool>);

}

