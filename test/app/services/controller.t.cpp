#include "testing.t.hpp"

#include <queue>

#include "app/services/config.hpp"
#include "app/services/controller.hpp"
#include "app/services/graphics.hpp"
#include "app/services/logic_thread.hpp"

#include "app/services/runtime.hpp"

#include "lib/util/with_limits.hpp"

#include "stubs/controller.hpp"
#include "stubs/logic_thread.hpp"

using namespace otto;
using drivers::Command;
using drivers::Packet;

using Events = std::vector<IInputHandler::variant>;

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
  test::StubMCUPort port;
  services::MCUCommunicator com = {&port};
  Handler handler;
  com.handler = &handler;

  SECTION ("Read keypresses") {
    Packet p = {Command::key_events};
    auto presses = std::span(p.data.data(), 8);
    auto releases = std::span(p.data.data() + 8, 8);
    util::set_bit(presses, util::enum_integer(Key::seq0), true);
    util::set_bit(presses, util::enum_integer(Key::unassigned_f), true);
    util::set_bit(releases, util::enum_integer(Key::seq5), true);
    com.handle_packet(p);
    REQUIRE(handler.events == Events{KeyPress{Key::seq0}, KeyRelease{Key::seq5}, KeyPress{Key::unassigned_f}});
  }
  SECTION ("Read encoderevents") {
    Packet p = {Command::encoder_events, {10, 2, 251, 0}};
    com.handle_packet(p);
    REQUIRE(handler.events == Events{EncoderEvent{Encoder::blue, 10}, EncoderEvent{Encoder::green, 2},
                                     EncoderEvent{Encoder::yellow, -5}});
  }
}

TEST_CASE ("Controller thread") {
  otto::test::StubMCUPort port;
  Handler handler;
  auto app =
    services::start_app(services::LogicThread::make(), //
                        services::ConfigManager::make(), services::Controller::make([&port] { return &port; }));
  core::ServiceAccessor<services::Controller> ctrl;
  core::ServiceAccessor<services::LogicThread> logic_thread;
  ctrl->set_input_handler(handler);

  port.data.push({Command::encoder_events, {10, 2, 251, 0}});
  std::this_thread::sleep_for(50ms);
  logic_thread->executor().run_queued_functions();
  REQUIRE(handler.events ==
          Events{EncoderEvent{Encoder::blue, 10}, EncoderEvent{Encoder::green, 2}, EncoderEvent{Encoder::yellow, -5}});
}
