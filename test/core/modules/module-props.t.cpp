#include "testing.t.hpp"

#include <algorithm>

#include "core/modules/module-props.hpp"

namespace otto::modules {

  TEST_CASE ("Module Properties", "[modules]") {

    struct Props : public Properties {
      Property<float> fProp           = {this, "fProp", 5.2f, {0.f, 10.f, 0.1f}};
      Property<float, wrap> otherProp = {this, "otherProp", 16, {5, 32, 1}};
      Property<bool> toggle           = {this, "toggle", false};

      struct SubProps : public Properties {
        Property<int> anInt           = {this, "anInt", 42};
        using Properties::Properties;
      } subProps {this, "subProps"};

    } props;

    SECTION("Property modes") {

      REQUIRE(props.fProp.get() == 5.2f);
      props.fProp.step(300);
      REQUIRE(props.fProp == 10.f);
      props.fProp.step(-20);
      REQUIRE(props.fProp == 8.f);
      props.fProp.step(-84.f);
      REQUIRE(props.fProp == 0.f);
      props.fProp.set(4);
      REQUIRE(props.fProp == 4);

      REQUIRE(props.otherProp == 16);
      props.otherProp.step(9);
      REQUIRE(props.otherProp == 25);
      props.otherProp.step(15);
      REQUIRE(props.otherProp.get() == 13);
      props.otherProp.step(-10);
      REQUIRE(props.otherProp.get() == 30);

      REQUIRE(props.toggle == false);
      props.toggle.step();
      REQUIRE(props.toggle == true);
      props.toggle.step(-5);
      REQUIRE(props.toggle == false);
      props.toggle.step(-1);
      REQUIRE(props.toggle == true);
      props.toggle.set(true);
      REQUIRE(props.toggle == true);

    }

    SECTION("Properties are added to the vector correctly") {

      REQUIRE(props[0].name == "fProp");
      REQUIRE(props.size() == 4);
      REQUIRE(&props[2] == &props.toggle);

      REQUIRE(props.subProps.size() == 1);
      REQUIRE(&props.subProps[0] == &props.subProps.anInt);
      REQUIRE(&props[3] == &props.subProps);

    }

    using nlohmann::json;

    SECTION("Property to json conversions") {

      REQUIRE(props.fProp.to_json() == 5.2f);

      json node = {
          {"fProp", 5.2f},
          {"otherProp", 16},
          {"toggle", false},
          {"subProps", {
                {"anInt", 42}
              }
          }
        };

      auto propsNode = props.to_json();
      REQUIRE(propsNode == node);

    }

    SECTION("json to Property conversions") {

      props.fProp.from_json({8.f});
      REQUIRE(props.fProp == 8.f);

      json node = {
          {"fProp", 2.f},
          {"otherProp", 31},
          {"toggle", true},
          {"subProps", {
                {"anInt", 9}
              }
          }
        };

      props.from_json(node);
      REQUIRE(props.fProp == 2.f);

      REQUIRE(props.to_json() == node);
    }

    SECTION("Properties work with range-based for loops") {
      int n = 0;
      for (auto&& p : props) {
        n++;
      }

      REQUIRE(n == props.size());
      REQUIRE(props.size() == 4);
    }

  }
}
