#pragma once

#include "util/concepts.hpp"
#include "util/meta.hpp"

#include "services/log_manager.hpp"

namespace otto::core {

  /// Base class of all services. Don't extend this directly, use `Service` instead
  ///
  /// Only ensures a virtual constructor, otherwise its just used for identifying types.
  struct IService {
    virtual ~IService() = default;
  };

  /// CRTP Base class for services. All services should extend this class.
  ///
  /// It is used to help detect the difference between the `AService` and `AServiceImpl` concepts.
  ///
  /// CRTP = Curiously Recurring Template Pattern. It's a C++ pattern for static
  /// polymorphism. All you need to know is, this is how you use this class:
  ///
  /// ```cpp
  /// struct SomeService : Service<SomeService> {
  ///   // ...
  /// };
  /// ```
  ///
  /// So, you extend it, templated on the derived class you are defining.
  template<typename Derived>
  struct Service : IService {
    using ServiceType = Derived;

    Derived& service()
    {
      return static_cast<Derived&>(*this);
    }
  };

  template<typename S>
  concept AService = std::is_base_of_v<IService, S>&& std::is_same_v<typename S::ServiceType, S>;

  template<typename S>
  concept AServiceImpl =
    !std::is_abstract_v<S> && std::is_base_of_v<IService, S> && !std::is_same_v<typename S::ServiceType, S>;

  namespace detail {
    template<AService S>
    S* service_registry_ = nullptr;
  }

  template<AService S>
  void register_service(S& s)
  {
    OTTO_ASSERT(detail::service_registry_<S> == nullptr, "Registering a service, when another is already registered");
    detail::service_registry_<S> = &s;
  }

  template<AService S>
  void unregister_service(S& s)
  {
    OTTO_ASSERT(detail::service_registry_<S> == &s, "Unregistering a service different from the one registered");
    detail::service_registry_<S> = nullptr;
  }

  void register_service(AServiceImpl auto& s)
  {
    register_service(s.service());
  }
  void unregister_service(AServiceImpl auto& s)
  {
    unregister_service(s.service());
  }

  template<AService Service>
  struct ServiceProvider {
    ServiceProvider(std::unique_ptr<Service> s) noexcept : service_(std::move(s))
    {
      register_service(*service_);
    }

    template<AServiceImpl SI>
    ServiceProvider(std::unique_ptr<SI> s) noexcept
      : ServiceProvider(static_cast<std::unique_ptr<Service>>(std::move(s)))
    {}

    ~ServiceProvider() noexcept
    {
      unregister_service(*service_);
    }

    Service& service() noexcept
    {
      return *service_;
    }

  private:
    std::unique_ptr<Service> service_;
  };

  template<AServiceImpl SI>
  ServiceProvider(std::unique_ptr<SI> s) -> ServiceProvider<typename SI::ServiceType>;

  template<AService... Services>
  struct ServiceAccessor {
  protected:
    template<util::one_of<Services...> S>
    S& service() const noexcept
    {
      OTTO_ASSERT(detail::service_registry_<S> != nullptr, "Tried to access service with none registered");
      return *detail::service_registry_<S>;
    }
  };
} // namespace otto::core
