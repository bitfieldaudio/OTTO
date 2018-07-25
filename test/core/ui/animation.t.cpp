#include "testing.t.hpp"

#include "core/ui/animation.hpp"

namespace otto::core::ui::animation {

  using namespace std::chrono_literals;

  TEST_CASE("Animations", "[util]")
  {
    Timeline<> timeline;

    SECTION("Basic tests")
    {
      // timeline.start();

      float value;
      // auto animation = timeline.push(value)
      //                    .then(procs::set(0))
      //                    .then(procs::wait(5s))
      //                    .then(procs::set(10))
      //                    .then(ramp_to(100, 10s, ease_in_out));
    }
  }
} // namespace otto::core::ui::animation

