#include "lib/itc/executor.hpp"
#include "testing.t.hpp"

#include "lib/logging.hpp"

#include <thread>

using namespace otto::lib;
using namespace otto::lib::itc;
using namespace std::literals;

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

TEST_CASE (doctest::may_fail(true) * "ExecutorLock") {
  int iteration = 0;
  for (; iteration < 1000; iteration++) {
    // LOGI("Iteration {}", iteration);

    /// The data needed by the threads
    struct Data {
      /// The loop condition for the application
      std::atomic_bool run = true;

      std::atomic_int actual_count = 0;
      std::atomic_int expected_count = 0;

      std::array<std::pair<QueueExecutor, std::thread>, 10> threads;
    } data;

    // Allows recursion easier than lambdas
    struct Incrementer {
      void operator()()
      {
        int i = data.expected_count;
        // choose "random" other queue to add function to
        auto& [e2, t2] = data.threads[i % data.threads.size()];
        for (int j = i % 2; j >= 0; j--) {
          data.expected_count++;
          e2.execute([&ac = data.actual_count] { ac++; });
        }
        if (data.run) {
          // also execute this function on the other thread
          e2.execute(*this);
        } else {
          // Only some of the time when stopping
          if (i % 4 == 0) {
            e2.execute(*this);
          }
        }
      }
      Data& data;
    } inc = {data};

    ExecutorLockable lockable;

    std::atomic_int threads_ready = 0;

    int i = 0;
    for (auto& [e, t] : data.threads) {
      t = std::thread([&, &e = e, i] {
        auto lock = lockable.acquire();
        threads_ready++;
        while (data.run) {
          e.run_queued_functions_blocking(10ns);
        }
        lock.exit_synchronized(e);
      });
      i++;
    }
    for (int i = 0; i < 100; i++) inc();

    while (threads_ready != data.threads.size())
      ;
    // Let the threads run for a little while
    std::this_thread::sleep_for(std::chrono::nanoseconds(200));
    data.run = false;
    for (auto& [e, t] : data.threads) t.join();
    REQUIRE(data.actual_count == data.expected_count);
    REQUIRE(data.expected_count > data.threads.size());
  }
}
