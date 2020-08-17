#include "testing.t.hpp"

#include <variant>

#include "lib/util/enum.hpp"

#include "app/services/impl/controller.hpp"
#include "app/services/impl/runtime.hpp"
#include "app/services/logic_thread.hpp"

using namespace otto;

using services::Encoder;
using services::EncoderEvent;
using services::Key;
using services::KeyPress;
using services::KeyRelease;

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

struct TestHWMap final : services::HardwareMap {
  int row_count() const noexcept override
  {
    return 4;
  }
  int col_count() const noexcept override
  {
    return 8;
  }

  tl::optional<Key> key_at(std::uint8_t r, std::uint8_t c) const noexcept override
  {
    if (r == 0) return util::enum_cast<Key>(util::enum_integer(Key::seq0) + c);
    if (r == 1) return util::enum_cast<Key>(util::enum_integer(Key::channel0) + c);
    return tl::nullopt;
  }

  std::uint8_t led_for(Key k) const noexcept override
  {
    return 0;
  }
};

struct StubMCUPort final : services::MCUPort {
  std::size_t write(std::span<std::uint8_t> data) override
  {
    OTTO_UNREACHABLE();
  }

  std::span<std::uint8_t> read(std::size_t count) override
  {
    return data;
  }

  std::vector<std::uint8_t> data;
};

using Events = std::vector<std::variant<KeyPress, KeyRelease, EncoderEvent>>;

struct Handler final : services::InputHandler {
  void handle(const KeyPress& e) noexcept override
  {
    events.push_back(e);
  }
  void handle(const KeyRelease& e) noexcept override
  {
    events.push_back(e);
  }
  void handle(const EncoderEvent& e) noexcept override
  {
    events.push_back(e);
  }

  Events events;
};

TEST_CASE ("MCUController::read_input_data") {
  StubMCUPort port;
  services::MCUCommunicator com = {&port, std::make_unique<TestHWMap>()};
  Handler handler;
  com.handler = &handler;

  SUBCASE ("Read seq0 keypress") {
    port.data = {1, 0, 0, 0, 0, 0, 0, 0};
    com.read_input_response();
    REQUIRE(handler.events == Events{KeyPress{Key::seq0}});
  }
  SUBCASE ("Read seq1 keypress") {
    port.data = {2, 0, 0, 0, 0, 0, 0, 0};
    com.read_input_response();
    REQUIRE(handler.events == Events{KeyPress{Key::seq1}});
  }
  SUBCASE ("Read seq0 and seq1 keypress") {
    port.data = {3, 0, 0, 0, 0, 0, 0, 0};
    com.read_input_response();
    REQUIRE(handler.events == Events{KeyPress{Key::seq0}, KeyPress{Key::seq1}});
  }
  SUBCASE ("Read more keypresses") {
    port.data = {5, 3, 0, 0, 0, 0, 0, 0};
    com.read_input_response();
    REQUIRE(handler.events ==
            Events{KeyPress{Key::seq0}, KeyPress{Key::seq2}, KeyPress{Key::channel0}, KeyPress{Key::channel1}});
  }
  SUBCASE ("No recurring keypresses") {
    port.data = {1, 0, 0, 0, 0, 0, 0, 0};
    com.read_input_response();
    port.data = {1, 0, 0, 0, 0, 0, 0, 0};
    com.read_input_response();
    REQUIRE(handler.events == Events{KeyPress{Key::seq0}});
  }
  SUBCASE ("KeyRelease") {
    port.data = {5, 3, 0, 0, 0, 0, 0, 0};
    com.read_input_response();
    handler.events.clear();

    port.data = {4, 3, 0, 0, 0, 0, 0, 0};
    com.read_input_response();
    REQUIRE(handler.events == Events{KeyRelease{Key::seq0}});
  }

  SUBCASE ("Single EncoderEvent") {
    port.data = {0, 0, 0, 0, 20, 0, 0, 0};
    com.read_input_response();
    REQUIRE(handler.events == Events{EncoderEvent{Encoder::blue, 20}});
  }

  SUBCASE ("Two EncoderEvents") {
    port.data = {0, 0, 0, 0, 20, 0, 0, 0};
    com.read_input_response();
    port.data = {0, 0, 0, 0, 40, 0, 0, 0};
    com.read_input_response();
    REQUIRE(handler.events == Events{EncoderEvent{Encoder::blue, 20}, EncoderEvent{Encoder::blue, 20}});
  }

  SUBCASE ("Negative EncoderEvents") {
    port.data = {0, 0, 0, 0, 20, 0, 0, 0};
    com.read_input_response();
    port.data = {0, 0, 0, 0, 0, 0, 0, 0};
    com.read_input_response();
    REQUIRE(handler.events == Events{EncoderEvent{Encoder::blue, 20}, EncoderEvent{Encoder::blue, -20}});
  }

  SUBCASE ("EncoderEvents with rollover") {
    port.data = {0, 0, 0, 0, 255, 0, 0, 0};
    com.read_input_response();
    port.data = {0, 0, 0, 0, 0, 0, 0, 0};
    com.read_input_response();
    REQUIRE(handler.events == Events{EncoderEvent{Encoder::blue, -1}, EncoderEvent{Encoder::blue, 1}});
  }

  SUBCASE ("Encoder rollover limits") {
    SUBCASE ("lower") {
      port.data = {0, 0, 0, 0, 128, 0, 0, 0};
      com.read_input_response();
      REQUIRE(handler.events == Events{EncoderEvent{Encoder::blue, -128}});
    }
    SUBCASE ("upper") {
      port.data = {0, 0, 0, 0, 127, 0, 0, 0};
      com.read_input_response();
      REQUIRE(handler.events == Events{EncoderEvent{Encoder::blue, 127}});
    }
  }

  SUBCASE ("Errors") {
    SUBCASE ("Too little data") {
      port.data = {0, 0, 0, 0, 0, 0, 0};
      REQUIRE_THROWS_WITH_AS(com.read_input_response(), "Data had invalid length. Got 7 bytes, expected 8",
                             util::exception);
    }
    SUBCASE ("Too much data") {
      port.data = {0, 0, 0, 0, 0, 0, 0, 0, 0};
      REQUIRE_THROWS_WITH_AS(com.read_input_response(), "Data had invalid length. Got 9 bytes, expected 8",
                             util::exception);
    }
  }
}


struct InputMockMCUPort final : services::MCUPort {
  std::size_t write(std::span<std::uint8_t> data) override
  {
    REQUIRE(std::ranges::equal(data, std::array{0_u8}));
    response_ready = true;
    return 1;
  }

  std::span<std::uint8_t> read(std::size_t count) override
  {
    if (!response_ready) return {};
    response_ready = false;
    return data;
  }

  std::vector<std::uint8_t> data;

private:
  bool response_ready = false;
};


TEST_CASE ("MCUController thread") {
  InputMockMCUPort port;
  Handler handler;
  auto app = services::start_app(core::make_handle<LogicThreadStub<itc::QueueExecutor>>(), //
                                 core::make_handle<services::MCUController>(&port, std::make_unique<TestHWMap>(),
                                                                            otto::services::MCUController::Config()));
  core::ServiceAccessor<services::MCUController> ctrl;
  core::ServiceAccessor<LogicThreadStub<itc::QueueExecutor>> logic_thread;
  ctrl->set_input_handler(handler);

  port.data = {3, 0, 0, 0, 0, 0, 0, 25};
  REQUIRE(handler.events == Events{});

  std::this_thread::sleep_for(50ms);
  logic_thread->executor().run_queued_functions();
  REQUIRE(handler.events == Events{KeyPress{Key::seq0}, KeyPress{Key::seq1}, EncoderEvent{Encoder::red, 25}});
}
