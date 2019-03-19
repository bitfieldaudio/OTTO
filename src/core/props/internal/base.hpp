#pragma once

#include <vector>
#include <string>
#include <functional>

namespace otto::core::props {

  /// Order of hook handlers.
  ///
  /// This is the second template argument to hook implementations, and is used
  /// to sort handlers.
  enum struct HookOrder {
    /// Should only read hook values
    Before,
    /// Change values early
    Early,
    /// Change values in the middle. Default
    Middle,
    /// Change values late
    Late,
    /// Should only read hook values
    After,
  };

} // namespace otto::core::props
