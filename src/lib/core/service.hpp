#pragma once

#include <memory>

#include <function2/function2.hpp>

#include "lib/meta.hpp"
#include "lib/util/concepts.hpp"
#include "lib/util/name_of.hpp"

#include "lib/logging.hpp"

namespace otto::core {

  /// Base class of all services. Don't extend this directly, use `Service` instead
  ///
  /// Only ensures a virtual constructor, otherwise its just used for identifying types.
  struct IService {
    IService() = default;
    IService(const IService&) = delete;
    IService(IService&&) = delete;
    virtual ~IService() = default;
    virtual std::string_view name() const noexcept = 0;
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
    static constexpr util::string_ref service_name = util::name_of<Derived>;

    std::string_view name() const noexcept override
    {
      return service_name;
    }
  };

  template<typename S>
  concept AService = std::is_base_of_v<IService, S>&& std::is_same_v<typename S::ServiceType, S>;

  template<typename SI>
  concept AServiceImpl = !std::is_abstract_v<SI> && std::is_base_of_v<IService, SI>;

  template<typename SSI>
  concept AServiceOrImpl = (AService<SSI> || AServiceImpl<SSI>);

  template<typename SI, typename S>
  concept AServiceImplOf = AServiceImpl<SI>&& AService<S>&& std::is_same_v<typename SI::ServiceType, S>;

  /// Statically get the name of the service from either the service itself, or an implementation
  template<AServiceOrImpl S>
  constexpr util::string_ref service_name() noexcept
  {
    return S::service_name;
  }

  namespace detail {
    template<AService S>
    S* active_service_ = nullptr;
  }

  template<AService S>
  void set_active_service(S& s)
  {
    OTTO_ASSERT(detail::active_service_<S> == nullptr, "Registering a service, when another is already registered");
    detail::active_service_<S> = &s;
  }

  template<AService S>
  void unset_active_service(S& s)
  {
    OTTO_ASSERT(detail::active_service_<S> == &s, "Unregistering a service different from the one registered");
    detail::active_service_<S> = nullptr;
  }

  template<AServiceImpl S>
  void set_active_service(S& s) requires(!AService<S>)
  {
    set_active_service(static_cast<typename S::ServiceType&>(s));
  }
  template<AServiceImpl S>
  void unset_active_service(S& s) requires(!AService<S>)
  {
    unset_active_service(static_cast<typename S::ServiceType&>(s));
  }

  /// DO NOT USE!
  ///
  /// Only available for testing and library code!
  ///
  /// Returns a pointer to the currently active service of type `S`
  template<AService S>
  S* unsafe_get_active_service()
  {
    return detail::active_service_<S>;
  }

  template<typename Service>
  struct [[nodiscard]] ServiceHandle
  {
    using Constructor = fu2::unique_function<std::unique_ptr<Service>()>;

    ServiceHandle(Constructor c) noexcept : constructor_(std::move(c)) {}

    ServiceHandle(ServiceHandle &&) = default;

    ~ServiceHandle() noexcept
    {
      if (started()) stop();
    }

    Service& service() const noexcept
    {
      return *service_;
    }

    Service* operator->() const noexcept
    {
      return service_.get();
    }

    ServiceHandle& start()& noexcept
    {
      service_ = constructor_();
      set_active_service(*service_);
      return *this;
    }

    ServiceHandle&& start()&& noexcept
    {
      start();
      return std::move(*this);
    }

    void stop() noexcept
    {
      unset_active_service(*service_);
      service_ = nullptr;
    }

    bool started() const noexcept
    {
      return service_ != nullptr;
    }

  private:
    Constructor constructor_;
    std::unique_ptr<Service> service_;
  };

  template<AServiceImpl SI, typename... Args>
  requires(std::is_constructible_v<SI, Args...>)
    [[nodiscard("The returned handle manages the lifetime of the service")]] auto make_handle(Args&&... args)
  {
    return ServiceHandle<typename SI::ServiceType>( //
      [... as = FWD(args)]() mutable {              //
        return std::make_unique<SI>(FWD(as)...);
      });
  }


  /// Gain access to the running instance of a service
  ///
  /// This class is only a wrapper to make sure service access is declared in the header of a
  /// component. It asserts that a service implementation is registered for each required service
  /// **in the constructor!**. This means any component using this to access a service must be
  /// constructed _after_ the given service. For a version that does not have this requirement,
  /// see {@ref UnsafeServiceAccessor}.
  ///
  /// There are two main ways to use it:
  ///
  ///   1. By inheriting from `private ServiceAccessor<Runtime, Graphics, Controller>`.
  ///      This method is prefered for `final` classes, since it clearly declares the needed services
  ///      at the top of the class definition.
  ///      Services can be accessed using `service<Runtime>()`
  ///      Make sure to use `private` inheritance for maximum effect!
  ///
  ///   2. By declaring members of the form `[[no_unique_address]] ServiceAccessor<Runtime> runtime`.
  ///      This method is prefered whenever the class is intended to be inherited from, to avoid
  ///      ambiguities when multiple points of the inheritance hierarchy inherit from `ServiceAccessor`.
  ///      When using this method, make a separate member for each service, and use their `operator->()`
  ///      to access the service.
  ///      We recommend marking the member as `private` and `[[no_unique_address]]`. The latter makes
  ///      sure the member doesn't take up space in your class.
  ///
  /// In theory, either method could be used either with single or multiple template argumets, but they
  /// lend themselves best to the aproaches described above.
  template<AServiceOrImpl... Services>
  requires(sizeof...(Services) > 0) //
    struct ServiceAccessor {
    ServiceAccessor()
    {
      (check_service<Services>(), ...);
    }

    template<util::one_of<Services...> S>
    S& service() const& noexcept
    {
      S* res = dynamic_cast<S*>(detail::active_service_<typename S::ServiceType>);
      OTTO_ASSERT(res != nullptr, "Tried to access service '{}' with none registered", util::name_of<S>);
      return *res;
    }

    auto* operator->() const& noexcept requires(sizeof...(Services) == 1)
    {
      return &service<Services...>();
    }


    // Do not allow service access from temporary
    template<util::one_of<Services...> S>
    S& service() && = delete;
    // Do not allow service access from temporary
    auto* operator->() && = delete;

  private:
    template<util::one_of<Services...> S>
    void check_service()
    {
      if (detail::active_service_<typename S::ServiceType> == nullptr) {
        LOGF("ServiceAccessor constructed with no service {} available", util::name_of<S>);
      }
      if constexpr (AServiceImpl<S>) {
        if (dynamic_cast<S*>(detail::active_service_<typename S::ServiceType>) == nullptr) {
          LOGF("ServiceAccessor<{}> constructed with the wrong service {} available", util::name_of<S>,
               util::name_of<typename S::ServiceType>);
        }
      }
    }
  };

  /// Require access to a service from a type that might be constructed before the service.
  template<AService... Services>
  struct UnsafeServiceAccessor {
    template<util::one_of<Services...> S>
    S* service_unsafe() const noexcept
    {
      return unsafe_get_active_service<S>;
    }

    auto* operator->() const noexcept requires(sizeof...(Services) == 1)
    {
      return service_unsafe<Services...>();
    }

    bool is_active() const noexcept requires(sizeof...(Services) == 1)
    {
      return (operator->()) != nullptr;
    }
  };
} // namespace otto::core
