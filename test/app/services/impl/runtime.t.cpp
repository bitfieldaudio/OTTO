#include "testing.t.hpp"

#include "app/services/impl/runtime.hpp"

using namespace otto::app;
using namespace otto::lib;
using namespace otto::app::services;

using Stage = RuntimeImpl::Stage;

TEST_CASE ("Runtime service") {
  SUBCASE ("Manual start/stop") {
    RuntimeImpl rt;
    REQUIRE(rt.stage() == Stage::initializing);
    REQUIRE(rt.should_run());
    rt.set_stage(Stage::running);
    REQUIRE(rt.stage() == Stage::running);
    REQUIRE(rt.should_run());
    rt.set_stage(Stage::stopping);
    REQUIRE(rt.stage() == Stage::stopping);
    REQUIRE(!rt.should_run());
  }

  struct S1 : core::Service<S1> {};
  struct S2 : core::Service<S2> {};
  struct S3 : core::Service<S3> {};

  static std::vector<int> construction_order;
  construction_order.clear();

  struct SI1 : S1, core::ServiceAccessor<Runtime> {
    SI1()
    {
      REQUIRE(service<Runtime>().stage() == Stage::initializing);
      construction_order.push_back(1);
    }

    ~SI1()
    {
      REQUIRE(service<Runtime>().stage() == Stage::stopping);
      construction_order.push_back(1);
    }
  };
  struct SI2 : S2 {
    SI2()
    {
      construction_order.push_back(2);
    }
    ~SI2()
    {
      construction_order.push_back(2);
    }
  };
  struct SI3 : S3 {
    SI3()
    {
      construction_order.push_back(3);
    }
    ~SI3()
    {
      construction_order.push_back(3);
    }
  };

  SUBCASE ("start_app") {
    SUBCASE ("Scoped") {
      {
        auto app = start_app(core::make_handle<SI1>(), //
                             core::make_handle<SI2>(), //
                             core::make_handle<SI3>());
        REQUIRE(app.service<Runtime>().stage() == Stage::running);
        REQUIRE(construction_order == std::vector{1, 2, 3});
        REQUIRE(core::unsafe_get_active_service<S1>() != nullptr);
        REQUIRE(core::unsafe_get_active_service<S2>() != nullptr);
        REQUIRE(core::unsafe_get_active_service<S3>() != nullptr);
      }
      // Check unregistration and destruction order
      REQUIRE(core::unsafe_get_active_service<S1>() == nullptr);
      REQUIRE(core::unsafe_get_active_service<S2>() == nullptr);
      REQUIRE(core::unsafe_get_active_service<S3>() == nullptr);
      REQUIRE(construction_order == std::vector{1, 2, 3, 3, 2, 1});
    }

    SUBCASE (".stop") {
      auto app = start_app(core::make_handle<SI1>(), //
                           core::make_handle<SI2>(), //
                           core::make_handle<SI3>());
      REQUIRE(app.service<Runtime>().stage() == Stage::running);
      REQUIRE(construction_order == std::vector{1, 2, 3});
      REQUIRE(core::unsafe_get_active_service<S1>() != nullptr);
      REQUIRE(core::unsafe_get_active_service<S2>() != nullptr);
      REQUIRE(core::unsafe_get_active_service<S3>() != nullptr);
      app.stop();
      // Check unregistration and destruction order
      REQUIRE(core::unsafe_get_active_service<S1>() == nullptr);
      REQUIRE(core::unsafe_get_active_service<S2>() == nullptr);
      REQUIRE(core::unsafe_get_active_service<S3>() == nullptr);
      REQUIRE(construction_order == std::vector{1, 2, 3, 3, 2, 1});
    }
  }
}
