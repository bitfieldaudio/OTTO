#pragma once

namespace otto::util {

  /// A helper for CRTP
  ///
  /// Exposes a {@ref derived()} function to the CRTP class only, not to
  /// types deriving from the CRTP type.
  /// 
  /// Usage:
  /// ```cpp
  /// template<typename Derived, typename SecondT>
  /// struct SomeBase : crtp<Derived, SomeBase<Derived, SecondT>> {}
  /// ```
  ///
  /// @tparam Derived the "real" derived type
  /// @tparam CrtpT the CRTP type
  template<typename Derived, typename CrtpT>
  struct crtp {
  private:
    friend CrtpT;

    /// Cast this to the derived type
    Derived& derived()
    {
      return static_cast<Derived&>(*this);
    }

    /// Cast this to the derived type
    Derived const& derived() const
    {
      return static_cast<Derived const&>(*this);
    }
  };

} // namespace otto::util
