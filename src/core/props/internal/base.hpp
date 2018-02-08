#pragma once

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

  /// The base class of the type-erased interface for a branch of `Tag`
  ///
  /// Has a vector of pointers to child interfaces and pointers to other
  /// common branch data, such as the name. These can all be accessed through
  /// accessor functions.
  template<typename Tag>
  struct BaseBranchInterface; // defined in props.hpp

} // namespace otto::core::props
