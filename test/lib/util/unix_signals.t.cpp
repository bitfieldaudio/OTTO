#include "testing.t.hpp"

#include "lib/util/unix_signals.hpp"

#include "lib/chrono.hpp"

using namespace otto;

TEST_CASE ("unix_signals", "[.interactive]") {
  auto waiter = util::handle_signals({SIGINT}, [](int sig) { LOGI("Got signal"); });
  std::this_thread::sleep_for(3s);
}
