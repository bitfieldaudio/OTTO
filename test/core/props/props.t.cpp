#include "testing.t.hpp"

#include <functional>

#include "core/engines/props/props.hpp"

namespace otto::core::props {

  struct FaustLink {
    enum struct Type { Input, Output } const type;
    void refresh();

    std::string name;
  private:
    float* faust_var_;
    std::function<void(float)> set_;
  };

  struct JsonClient {
    std::function<void(const nlohmann::json&)> loader;
    std::function<nlohmann::json()> saver;
  };

  struct ValueHandler {
    std::function<void()> reset;
  };

  Property<float, steppable, has_limits, serializable> property = {
    steppable::init(0),
    has_limits::init(0, 10),
    serializable::init()
  };

  struct Props : Properties {
    Property<float, has_name, has_parent> prop1 = {
      0,
      has_name::init("prop1"),
      has_parent::init(this)
    };
    Property<float, has_name, has_parent> prop2 = {
      0,
      has_name::init("prop2"),
      has_parent::init(this)
    };
  } props;

  TEST_CASE("Property conversions", "") {
    auto& pb = static_cast<PropertyBase&>(property);
    REQUIRE(pb == property);

    const float& val = static_cast<const float&>(property);
    REQUIRE(&val == &property.value());
  }

  TEST_CASE("Property children", "") {
    REQUIRE(props.size() == 2);
    REQUIRE(props[0] == props.prop1);
    REQUIRE(props[1] == props.prop2)
  }
}
