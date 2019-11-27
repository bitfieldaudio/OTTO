#include "testing.t.hpp"

#include "core/engine/engine_selector_screen.hpp"

namespace otto {

  using namespace core::engine;

  TEST_CASE("EngineSelectorScreen", "[.graphics]") {

    EngineSelectorScreen screen;

    test::show_gui([&] (nvg::Canvas& ctx) {
      screen.draw(ctx);
    });
  }

}
