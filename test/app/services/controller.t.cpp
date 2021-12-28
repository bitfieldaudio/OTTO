#include "testing.t.hpp"

#include "app/services/controller.hpp"

#include <queue>

#include "lib/util/with_limits.hpp"

#include "app/services/config.hpp"
#include "app/services/graphics.hpp"
#include "app/services/logic_thread.hpp"
#include "app/services/runtime.hpp"

#include "stubs/controller.hpp"
#include "stubs/logic_thread.hpp"

using namespace otto;
using drivers::Command;
using drivers::Packet;

using Events = std::vector<std::variant<UntimedKeyPress, UntimedKeyRelease, UntimedEncoderEvent>>;

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
  services::RuntimeController rt;
  test::StubMCUPort port;
  services::MCUCommunicator com = {rt, &port};
  Handler handler;
  com.handler = &handler;

  SECTION ("Read keypresses") {
    Packet p = {Command::key_events};
    auto presses = std::span(p.data.data(), 8);
    auto releases = std::span(p.data.data() + 8, 8);
    util::set_bit(presses, util::enum_integer(Key::seq0), true);
    util::set_bit(presses, util::enum_integer(Key::omega), true);
    util::set_bit(releases, util::enum_integer(Key::seq5), true);
    com.handle_packet(p);
    REQUIRE(handler.events ==
            Events{UntimedKeyPress{Key::seq0}, UntimedKeyRelease{Key::seq5}, UntimedKeyPress{Key::omega}});
  }
  SECTION ("Read encoderevents") {
    Packet p = {Command::encoder_events, {10, 2, 251, 0}};
    com.handle_packet(p);
    REQUIRE(handler.events == Events{UntimedEncoderEvent{Encoder::blue, 10}, UntimedEncoderEvent{Encoder::green, 2},
                                     UntimedEncoderEvent{Encoder::yellow, -5}});
  }
}

TEST_CASE ("Controller thread") {
  otto::test::StubMCUPort port;
  Handler handler;
  services::RuntimeController rt;
  services::LogicThread logic_thread;
  services::ConfigManager confman;
  services::Controller ctrl(rt, confman, &port);
  auto stop = ctrl.set_input_handler(handler);

  port.data.push({Command::encoder_events, {10, 2, 251, 0}});
  std::this_thread::sleep_for(50ms);
  logic_thread.executor().run_queued_functions();
  REQUIRE(handler.events == Events{UntimedEncoderEvent{Encoder::blue, 10}, UntimedEncoderEvent{Encoder::green, 2},
                                   UntimedEncoderEvent{Encoder::yellow, -5}});
}
