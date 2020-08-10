#include "app/services/impl/runtime.hpp"
#include "testing.t.hpp"

#include "app/services/config.hpp"

using namespace otto;

struct TestConfig final : Config<TestConfig> {
  static constexpr util::string_ref name = "TestConfig";
  int option1 = 4;
  std::string option2 = "test";

  // void to_toml(toml::value& val) const override
  // {
  //   val["option1"] = option1;
  //   val["option2"] = option2;
  // }
  // void from_toml(const toml::value& val) override
  // {
  //   option1 = toml::find<decltype(option1)>(val, "option1");
  //   option2 = toml::find<decltype(option2)>(val, "option2");
  // }
  // 
  // Both of those will be implemented to something that looks basically like the above
  // by using DECL_VISIT:

  DECL_VISIT(option1, option2);
};
static_assert(util::AVisitable<TestConfig>);

TEST_CASE ("ConfigManager") {
  SUBCASE ("Registry") {
    auto app = services::start_app(core::make_handle<otto::services::ConfigManager>());
    core::ServiceAccessor<services::ConfigManager> confman;
    const TestConfig& tc1 = confman->register_config<TestConfig>();
    REQUIRE(tc1.option1 == 4);
    REQUIRE(&confman->get<TestConfig>() == &tc1);
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

  SUBCASE ("Service constructor") {
    using namespace otto::toml::literals;
    otto::toml::value config_data = R"(
      [TestConfig]
      option1 = 100
      option2 = "string"
    )"_toml;

    auto app = services::start_app(core::make_handle<services::ConfigManager>(config_data));
    core::ServiceAccessor<services::ConfigManager> confman;
    const TestConfig& tc1 = confman->register_config<TestConfig>();

    REQUIRE(tc1.option1 == 100);
    REQUIRE(tc1.option2 == "string");
  }
}
