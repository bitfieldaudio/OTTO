#include "testing.t.hpp"

#include "app/services/config.hpp"

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
    services::RuntimeController rt;
    services::ConfigManager confman;
    auto tc1 = confman.make_conf<TestConfig>();
    REQUIRE(tc1.option1 == 4);
  }
  TestConfig tc1;

  json::value config_data = {{"TestConfig", {{"option1", 100}}}};

  SECTION ("Service constructor") {
    services::RuntimeController rt;
    services::ConfigManager confman(config_data);
    auto tc1 = confman.make_conf<TestConfig>();

    REQUIRE(tc1.option1 == 100);
    REQUIRE(tc1.option2 == "test");
  }
}
