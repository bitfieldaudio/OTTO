#include "app/services/impl/runtime.hpp"
#include "testing.t.hpp"

#include <refl.hpp>

#include "app/services/config.hpp"

using namespace otto::app;
using namespace otto::lib;

struct TestConfig : Config {
  int option1 = 4;
  std::string option2 = "test";
};

REFL_AUTO(type(TestConfig), field(option1), field(option2));

TEST_CASE ("Config service") {
  auto app = services::start_app(core::make_handle<otto::app::services::ConfigManager>());
  core::ServiceAccessor<services::ConfigManager> confman;
  //TestConfig& tc1 = confman->register_config<TestConfig>();
}
