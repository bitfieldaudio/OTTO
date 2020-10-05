#include "testing.t.hpp"

#include <queue>

#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/graphics.hpp"
#include "app/services/logic_thread.hpp"

#include "app/services/runtime.hpp"

#include "lib/util/with_limits.hpp"

using namespace otto;
using services::Command;
using services::Packet;

constexpr std::uint8_t operator"" _u8(unsigned long long int v) noexcept
{
  return static_cast<std::uint8_t>(v);
}

template<std::derived_from<itc::IExecutor> Executor>
struct LogicThreadStub final : services::LogicThread {
  Executor& executor() noexcept override
  {
    return executor_;
  }

private:
  Executor executor_;
};

struct StubMCUPort final : services::MCUPort {
  void write(const Packet& p) override
  {
    OTTO_UNREACHABLE();
  }

  Packet read() override
  {
    if (data.empty()) return {};
    auto res = data.front();
    data.pop();
    return res;
  }

  void stop() override {}

  std::queue<Packet> data;
};

using Events = std::vector<std::variant<KeyPress, KeyRelease, EncoderEvent>>;

struct Handler final : InputHandler {
  void handle(KeyPress e) noexcept override
  {
    events.push_back(e);
  }
  void handle(KeyRelease e) noexcept override
  {
    events.push_back(e);
  }
  void handle(EncoderEvent e) noexcept override
  {
    events.push_back(e);
  }

  Events events;
};

TEST_CASE ("Controller::read_input_data") {
  StubMCUPort port;
  services::MCUCommunicator com = {&port};
  Handler handler;
  com.handler = &handler;

  SUBCASE ("Read keypresses") {
    Packet p = {Command::key_events};
    auto presses = std::span(p.data.data(), 8);
    auto releases = std::span(p.data.data() + 8, 8);
    util::set_bit(presses, util::enum_integer(Key::seq0), true);
    util::set_bit(presses, util::enum_integer(Key::unassigned_f), true);
    util::set_bit(releases, util::enum_integer(Key::seq5), true);
    com.handle_packet(p);
    REQUIRE(handler.events == Events{KeyPress{Key::seq0}, KeyRelease{Key::seq5}, KeyPress{Key::unassigned_f}});
  }
  SUBCASE ("Read encoderevents") {
    Packet p = {Command::encoder_events, {10, 2, 251, 0}};
    com.handle_packet(p);
    REQUIRE(handler.events == Events{EncoderEvent{Encoder::blue, 10}, EncoderEvent{Encoder::green, 2},
                                     EncoderEvent{Encoder::yellow, -5}});
  }
}

TEST_CASE ("Controller thread") {
  StubMCUPort port;
  Handler handler;
  auto app = services::start_app(core::make_handle<LogicThreadStub<itc::QueueExecutor>>(), //
                                 services::ConfigManager::make(), services::Controller::make(&port));
  core::ServiceAccessor<services::Controller> ctrl;
  core::ServiceAccessor<LogicThreadStub<itc::QueueExecutor>> logic_thread;
  ctrl->set_input_handler(handler);

  port.data.push({Command::encoder_events, {10, 2, 251, 0}});
  std::this_thread::sleep_for(50ms);
  logic_thread->executor().run_queued_functions();
  REQUIRE(handler.events ==
          Events{EncoderEvent{Encoder::blue, 10}, EncoderEvent{Encoder::green, 2}, EncoderEvent{Encoder::yellow, -5}});
}