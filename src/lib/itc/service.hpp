#pragma once

namespace otto::itc {

  template<typename T>
  concept AService = requires
  {
    typename T::provider_t;
    typename T::accessor_t;
  };

  template<AService S>
  using provider_t = typename S::provider_t;
  template<AService S>
  using accessor_t = typename S::accessor_t;

  template<AService...>
  struct Provider;
  template<AService...>
  struct Accessor;

  namespace detail {
    struct ProviderBase {
      virtual ~ProviderBase() = default;
    };
    struct AccessorBase {
      virtual ~AccessorBase() = default;
    };
  } // namespace detail
} // namespace otto::itc
