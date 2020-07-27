#include "lib/core/service.hpp"
#include "testing.t.hpp"

using namespace otto::lib;
using namespace otto::lib::core;

TEST_CASE ("ServiceProvider / ServiceAccessor") {
  struct TestService : Service<TestService> {
    virtual int get_int() = 0;
  };
  static_assert(AService<TestService>);

  struct TSImpl : TestService {
    int get_int() override
    {
      // Chosen by fair dice roll, guaranteed to be random
      return 4;
    }
  };
  static_assert(AServiceImpl<TSImpl>);
  static_assert(!AService<TSImpl>);

  SUBCASE ("Register/unregister service manually") {
    TSImpl tsi;
    REQUIRE(core::detail::service_registry_<TestService> == nullptr);
    register_service(tsi);
    // NOT A PUBLIC API!
    REQUIRE(core::detail::service_registry_<TestService> == &tsi);
    unregister_service(tsi);
    // NOT A PUBLIC API!
    REQUIRE(core::detail::service_registry_<TestService> == nullptr);
  }

  SUBCASE ("Auto register/unregister service using ServiceProvider") {
    {
      auto prov = ServiceProvider(std::make_unique<TSImpl>());
      REQUIRE(core::detail::service_registry_<TestService> == &prov.service());
    }
    REQUIRE(core::detail::service_registry_<TestService> == nullptr);
  }

  struct TSAccessor : ServiceAccessor<TestService> {
    void test_4()
    {
      REQUIRE(service<TestService>().get_int() == 4);
    }
  };

  SUBCASE ("Access registered service through ServiceAccessor") {
    auto prov = ServiceProvider(std::make_unique<TSImpl>());
    TSAccessor a;
    a.test_4();
  }

  struct Service2 : Service<Service2> {
    virtual int get_bool() = 0;
  };

  struct S2Impl : Service2 {
    int get_bool() override
    {
      return true;
    }
  };

  struct ServiceFactory {
    virtual ~ServiceFactory() = default;
    virtual ServiceProvider<TestService> make(util::tag_t<TestService>) = 0;
    virtual ServiceProvider<Service2> make(util::tag_t<Service2>) = 0;
  };

  struct Fact1 : ServiceFactory {
    ServiceProvider<TestService> make(util::tag_t<TestService>) override
    {
      return std::make_unique<TSImpl>();
    }
    ServiceProvider<Service2> make(util::tag_t<Service2>) override
    {
      return std::make_unique<S2Impl>();
    }
  };

  SUBCASE ("ServiceFactory") {}
  SUBCASE ("Application") {
    struct Application {
      std::unique_ptr<ServiceFactory> factory;
      ServiceProvider<TestService> test_service = factory->make(util::tag<TestService>);
      ServiceProvider<Service2> service2 = factory->make(util::tag<Service2>);
    };

    Application app = {.factory = std::make_unique<Fact1>()};

    TSAccessor a;
    a.test_4();
  }
}
