#include "itc/executor.hpp"
#include "testing.t.hpp"

#include <thread>

using namespace otto;
using namespace otto::itc;

TEST_CASE ("QueueExecutor") {
  SUBCASE ("queued functions are executed on run_queued_functions") {
    int i = 0;
    QueueExecutor e;
    e.execute([&] { i++; });
    REQUIRE(i == 0);
    e.run_queued_functions();
    REQUIRE(i == 1);
    e.run_queued_functions();
    REQUIRE(i == 1);
  }

  SUBCASE ("Multithreading") {
    QueueExecutor e;
    /// The loop condition for the application
    std::atomic_bool run = true;
    /// Synchronization of destruction. See below
    std::atomic_int active_producers = 0;
    auto consumer = std::thread([&] {
      while (run) {
        e.run_queued_functions();
        std::this_thread::sleep_for(std::chrono::nanoseconds(4));
      }
      while (active_producers != 0) {
        e.run_queued_functions();
      }
      e.run_queued_functions();
    });

    int count = 0;
    std::atomic_int expected_count = 0;

    std::array<std::thread, 10> producers;
    for (auto& p : producers) {
      p = std::thread([&] {
        active_producers++;
        while (run) {
          int i = expected_count++;
          e.execute([&count] { count++; });
          std::this_thread::sleep_for(std::chrono::nanoseconds(i % 8));
        }
        active_producers--;
      });
    }
    // Let the threads run for 100ns
    std::this_thread::sleep_for(std::chrono::nanoseconds(100));
    // Here is where a few questions come up.
    // - Are we actually able to kill the producers before the consumers?
    //   In the real setup, the audio thread is both a consumer and a producer,
    //   so there seems to be no way to strictly order those.
    //   So, do we instead split up destruction into two phases, one to stop producing,
    //   and the other to finish consuming the last actions?
    // - Why does it matter?
    //   In the normal state-passing cases it probably doesn't, but the guarantee that
    //   all enqueued functions are also executed seems fairly important, especially when
    //   this is used in other contexts as well
    // The only practical way to manage this issue, might be to do manual two-phase destruction
    // per usecase.
    // 
    // For this test, it is done by each producer incrementing the active_producers count, 
    // which means the consumer will run until all producers have decremented it back down,
    // and thus stopped producing items. This ensures, that the last call to
    // `e.run_queued_functions()` will happen strictly after the last call to `e.execute`.
    // 
    // This aproach probably makes sense in other contexts as well, though the `active_producers`
    // variable should probably be encapsulated in some scoped lock or similar.
    run = false;
    for (auto& p : producers) p.join();
    consumer.join();
    REQUIRE(count == expected_count);
  }
}
