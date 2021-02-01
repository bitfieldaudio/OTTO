#include "testing.t.hpp"

#include "app/services/config.hpp"

#include "app/application.hpp"
#include "app/services/runtime.hpp"

using namespace otto;

struct TestConfig final : Config<TestConfig> {
  // Optional, uses util::qualified_name_of by default:
  // static constexpr util::string_ref name = "TestConfig";
  int option1 = 4;
  std::string option2 = "test";

  DECL_VISIT(option1, option2);
};

TEST_CASE ("ConfigManager") {
  SECTION ("Registry") {
    auto app = start_app(core::make_handle<otto::services::ConfigManager>());
    core::ServiceAccessor<services::ConfigManager> confman;
    auto tc1 = confman->make_conf<TestConfig>();
    REQUIRE(tc1.option1 == 4);
  }
  TestConfig tc1;

  json::value config_data = {{"TestConfig", {{"option1", 100}}}};

  SECTION ("Service constructor") {
    auto app = start_app(core::make_handle<services::ConfigManager>(config_data));
    core::ServiceAccessor<services::ConfigManager> confman;
    auto tc1 = confman->make_conf<TestConfig>();

    REQUIRE(tc1.option1 == 100);
    REQUIRE(tc1.option2 == "test");
  }

  SECTION ("ConfHandle") {
    SECTION ("With no service") {
      TestConfig::Handle tc1 = TestConfig{.option1 = 42, .option2 = "yay"};
      REQUIRE(tc1->option1 == 42);
    }
    SECTION ("With service") {
      auto app = start_app(core::make_handle<services::ConfigManager>(config_data));
      core::ServiceAccessor<services::ConfigManager> confman;
      TestConfig::Handle tc1;
      REQUIRE(tc1->option1 == 100);
      REQUIRE(tc1->option2 == "test");

      auto data = confman->into_json();
      std::cout << data;
      REQUIRE(data["TestConfig"]["option2"] == "test");
    }
  }
}
