#include "testing.t.hpp"

#include "app/services/controller.hpp"
#include "app/services/runtime.hpp"

using namespace otto;
using namespace otto::drivers;

chrono::microseconds parse_hearbeat(Packet p)
{
  std::uint64_t count = 0;
  for (int i = 0; i < 8; i++) {
    count |= (std::uint64_t(p.data[i]) << i * 8);
  }
  return chrono::microseconds(count);
};

TEST_CASE ("MCUEventLog", "[.interactive]") {
  services::RuntimeController rt;
  services::ConfigManager conman = services::ConfigManager::make_default();
  auto port = drivers::MCUPort::make_default(conman);
  services::MCUCommunicator mcu(rt, port.get());
  struct Handler : InputHandler {
    void handle(KeyPress e) noexcept override
    {
      LOGI("↓ {}", util::enum_name(e.key));
    }
    void handle(KeyRelease e) noexcept override
    {
      LOGI("↑ {}", util::enum_name(e.key));
    }
    void handle(EncoderEvent e) noexcept override
    {
      LOGI("{} {:+}", util::enum_name(e.encoder), e.steps);
    }
  } handler;
  mcu.handler = &handler;
  auto thread = std::jthread([&](const std::stop_token& t) {
    while (!t.stop_requested()) {
      auto packet = port->read();
      if (packet && packet->cmd == drivers::Command::heartbeat) {
        LOGI("HEARTBEAT: {}", parse_hearbeat(*packet));
      } else {
        mcu.handle_packet(*packet);
      }
    }
  });
  rt.wait_for_stop();
}

TEST_CASE ("MCUClockDrift", "[.interactive]") {
  services::RuntimeController rt;
  services::ConfigManager conman = services::ConfigManager::make_default();
  auto port = drivers::MCUPort::make_default(conman);
  auto thread = std::jthread([&](const std::stop_token& t) {
    bool is_first = true;
    chrono::time_point local_start;
    chrono::duration mcu_start;
    while (!t.stop_requested()) {
      auto packet = port->read();
      if (packet && packet->cmd == drivers::Command::heartbeat) {
        if (is_first) {
          local_start = chrono::clock::now();
          mcu_start = parse_hearbeat(*packet);
          is_first = false;
        }
        auto local_time = chrono::clock::now() - local_start;
        auto mcu_time = parse_hearbeat(*packet) - mcu_start;
        auto diff = chrono::duration_cast<chrono::microseconds>(mcu_time - local_time);

        LOGI("MCU time: {:10}, Diff: {:10}, M/L: {:.4f}", chrono::duration_cast<chrono::microseconds>(mcu_time), diff,
             double(mcu_time.count()) / double(local_time.count()));
      }
    }
  });
  rt.wait_for_stop();
}
