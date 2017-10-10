#include "testing.t.hpp"

#include <thread>

#include "util/timer.hpp"

namespace top1::util::timer {

  int calcMargin() {
    Timer approxT;
    {
      auto volatile t = ScopeTimer(approxT);
      std::this_thread::sleep_for(Timer::Duration(1));
    }
    return approxT.times[0].count() * 3;
  }

  auto TimeApproximation(long int time) {
    return Approx(time).margin(calcMargin());
  }

  TEST_CASE("Timers", "[timer]") {

    TimerDispatcher dispatcher;

    SECTION("ScopeTimer") {
      Timer t;
      auto sleepTime = Timer::Duration(std::chrono::seconds(1));
      {
        auto volatile timer = ScopeTimer(t);
        std::this_thread::sleep_for(sleepTime);
      }
      CHECK(t.times[0].count() == TimeApproximation(sleepTime.count()));
    }
  }

}
