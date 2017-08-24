#include "../../testing.h"

#include "core/modules/module-props.hpp"

namespace top1::modules {

  TEST_CASE ("Module Properties", "[modules]") {

    struct Props : public Properties {
      Property<float> fProp                  = {this, "fProp", 5.2f, {0.f, 10.f, 0.1f}};
      Property<float, modes::wrap> otherProp = {this, "otherProp", 16, {5, 32, 1}};
      Property<bool> toggle                  = {this, "toggle", false};

      struct SubProps : public Properties {
        Property<int> anInt                  = {this, "anInt", 42};
        using Properties::Properties;
      } subProps {this, "subProps"};

    } props;

    SECTION("Property modes") {

      REQUIRE(props.fProp.value == 5.2f);
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
      REQUIRE(props.otherProp.value == 13);
      props.otherProp.step(-10);
      REQUIRE(props.otherProp.value == 30);

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

    SECTION("Property to tree::Node conversions") {

      // REQUIRE(props[0].makeNode() == props.fProp.makeNode());
      REQUIRE(props.fProp.makeNode().match([](const tree::Float& f) {
            return f.value == 5.2f;
          }, [] (auto) {return false;}));

      tree::Map node = {{
          {"fProp", tree::Float{5.2f}},
          {"otherProp", tree::Float{16}},
          {"toggle", tree::Bool{false}},
          {"subProps", tree::Map{{
                {"anInt", tree::Int{42}}
              }}}
        }};
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
