#include "../../testing.h"

#include "core/modules/module-props.hpp"

namespace top1::modules {

  TEST_CASE ("Module Properties", "[modules]") {

    struct Props : public Properties {
      Property<float> fProp = {"fProp", 5.2f, {0.f, 10.f, 0.1f}};
      Property<float, modes::wrap> otherProp = {"otherProp", 16, {5, 32, 1}};
      Property<bool> toggle = {"toggle", false};
    } props;

    // REQUIRE(props[0].name == "fProp");
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

    for (auto&& p : props) {
      // Can loop
    }

  }
}
