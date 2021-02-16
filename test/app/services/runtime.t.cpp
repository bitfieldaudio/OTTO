#include "testing.t.hpp"

#include "app/services/runtime.hpp"

using namespace otto;
using namespace otto::services;

// TEST_CASE ("RuntimeLock") {
//  int iteration = 0;
//  for (; iteration < 10000; iteration++) {
//    // LOGI("Iteration {}", iteration);
//
//    /// The data needed by the threads
//    struct Data {
//      /// The loop condition for the application
//      std::atomic_bool run = true;
//
//      std::atomic_int actual_count = 0;
//      std::atomic_int expected_count = 0;
//
//      std::array<std::pair<itc::QueueExecutor, std::thread>, 3> threads;
//    } data;
//
//    // Allows recursion easier than lambdas
//    struct Incrementer {
//      void operator()()
//      {
//        int i = data.expected_count;
//        // choose "random" other queue to add function to
//        auto& [e2, t2] = data.threads[i % data.threads.size()];
//        for (int j = i % 2; j >= 0; j--) {
//          data.expected_count++;
//          e2.execute([&ac = data.actual_count] { ac++; });
//        }
//        if (data.run) {
//          // also execute this function on the other thread
//          e2.execute(*this);
//        } else {
//          // Only some of the time when stopping
//          if (i % 4 == 0) {
//            e2.execute(*this);
//          }
//        }
//      }
//      Data& data;
//    } inc = {data};
//
//    RuntimeController rt;
//
//    std::atomic_int threads_ready = 0;
//
//    int i = 0;
//    for (auto& [e, t] : data.threads) {
//      t = std::thread([&, &e = e] {
//        auto lock = rt.acquire(e);
//        threads_ready++;
//        while (lock.should_run()) {
//          e.run_queued_functions_blocking(10ns);
//        }
//        data.run = false;
//        lock.sync_exit();
//      });
//      i++;
//    }
//    for (int i = 0; i < 100; i++) inc();
//
//    while (threads_ready != data.threads.size())
//      ;
//    // Let the threads run for a little while
//    rt.wait_for_stop(200ns);
//    for (auto& [e, t] : data.threads) t.join();
//    REQUIRE(data.actual_count == data.expected_count);
//    REQUIRE(data.expected_count > data.threads.size());
//  }
//}
