#include "testing.t.hpp"

#include <thread>

#include "util/timer.hpp"

namespace otto::util::timer {

  int calcMargin() {
    Timer approxT {"approx"};
    {
      start(approxT);
      std::this_thread::sleep_for(Timer::time_point::duration(1));
      stop();
    }
    return approxT.data.front().count() * 3;
  }

  auto TimeApproximation(long int time) {
    return Approx(time).margin(calcMargin());
  }

  TEST_CASE("Timers", "[timer]") {

    SECTION("ScopedTimer") {
      Timer t {"t"};
      auto sleepTime = Timer::time_point::duration(std::chrono::seconds(1));
      {
        auto timer = ScopedTimer(t);
        std::this_thread::sleep_for(sleepTime);
      }
      CHECK(t.data.front().count() == TimeApproximation(sleepTime.count()));
    }
  }

}
