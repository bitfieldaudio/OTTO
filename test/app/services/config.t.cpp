#include "app/services/impl/runtime.hpp"
#include "testing.t.hpp"

#include "app/services/config.hpp"

using namespace otto;

struct TestConfig final : Config<TestConfig> {
  // Optional, uses util::qualified_name_of by default:
  // static constexpr util::string_ref name = "TestConfig";
  int option1 = 4;
  std::string option2 = "test";

  DECL_VISIT(option1, option2);
};

TEST_CASE ("ConfigManager") {
  SUBCASE ("Registry") {
    auto app = services::start_app(core::make_handle<otto::services::ConfigManager>());
    core::ServiceAccessor<services::ConfigManager> confman;
    TestConfig tc1 = confman->make_conf<TestConfig>();
    REQUIRE(tc1.option1 == 4);
  }
  TestConfig tc1;

  SUBCASE ("Serialization") {
    REQUIRE(tc1.get_name() == "TestConfig");
    otto::toml::value res;
    tc1.to_toml(res);
    REQUIRE(res == otto::toml::value{
                     {"option1", 4},
                     {"option2", "test"},
                   });
  }

  SUBCASE ("Deserialization") {
    tc1.from_toml(otto::toml::value{
      {"option1", 42},
      {"option2", "new value"},
    });
    REQUIRE(tc1.option1 == 42);
    REQUIRE(tc1.option2 == "new value");

    auto tc2 = otto::toml::get<TestConfig>(otto::toml::value{
      {"option1", 9},
      {"option2", "yo"},
    });
    REQUIRE(tc2.option1 == 9);
    REQUIRE(tc2.option2 == "yo");
  }

  using namespace otto::toml::literals;
  otto::toml::value config_data = R"(
      [TestConfig]
      option1 = 100
    )"_toml;

  SUBCASE ("Service constructor") {
    auto app = services::start_app(core::make_handle<services::ConfigManager>(config_data));
    core::ServiceAccessor<services::ConfigManager> confman;
    TestConfig tc1 = confman->make_conf<TestConfig>();

    REQUIRE(tc1.option1 == 100);
    REQUIRE(tc1.option2 == "test");
  }

  SUBCASE ("ConfHandle") {
    SUBCASE ("With no service") {
      TestConfig::Handle tc1 = TestConfig{.option1 = 42, .option2 = "yay"};
      REQUIRE(tc1->option1 == 42);
    }
    SUBCASE ("With service") {
      auto app = services::start_app(core::make_handle<services::ConfigManager>(config_data));
      core::ServiceAccessor<services::ConfigManager> confman;
      TestConfig::Handle tc1;
      REQUIRE(tc1->option1 == 100);
      REQUIRE(tc1->option2 == "test");

      auto data = confman->into_toml();
      std::cout << data;
      REQUIRE(otto::toml::find<std::string>(otto::toml::find(data, "TestConfig"), "option2") == "test");
    }
  }
}
