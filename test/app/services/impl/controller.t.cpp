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

struct LogicThreadStub final : services::LogicThread {
  itc::ImmediateExecutor& executor() noexcept override
  {
    return executor_;
  }

private:
  itc::ImmediateExecutor executor_;
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

struct StubMCUCommunicator final : services::MCUCommunicator {
  std::span<std::uint8_t> read() override
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
  StubMCUCommunicator com;
  Handler handler;
  auto app = services::start_app(core::make_handle<LogicThreadStub>(), //
                                 core::make_handle<services::MCUController>(&com, std::make_unique<TestHWMap>()));
  core::ServiceAccessor<services::MCUController> ctrl;
  ctrl->set_input_handler(handler);

  SUBCASE ("Read seq0 keypress") {
    com.data = {1, 0, 0, 0, 0, 0, 0, 0};
    ctrl->read_input_data();
    REQUIRE(handler.events == Events{KeyPress{Key::seq0}});
  }
  SUBCASE ("Read seq1 keypress") {
    com.data = {2, 0, 0, 0, 0, 0, 0, 0};
    ctrl->read_input_data();
    REQUIRE(handler.events == Events{KeyPress{Key::seq1}});
  }
  SUBCASE ("Read seq0 and seq1 keypress") {
    com.data = {3, 0, 0, 0, 0, 0, 0, 0};
    ctrl->read_input_data();
    REQUIRE(handler.events == Events{KeyPress{Key::seq0}, KeyPress{Key::seq1}});
  }
  SUBCASE ("Read more keypresses") {
    com.data = {5, 3, 0, 0, 0, 0, 0, 0};
    ctrl->read_input_data();
    REQUIRE(handler.events ==
            Events{KeyPress{Key::seq0}, KeyPress{Key::seq2}, KeyPress{Key::channel0}, KeyPress{Key::channel1}});
  }
  SUBCASE ("No recurring keypresses") {
    com.data = {1, 0, 0, 0, 0, 0, 0, 0};
    ctrl->read_input_data();
    com.data = {1, 0, 0, 0, 0, 0, 0, 0};
    ctrl->read_input_data();
    REQUIRE(handler.events == Events{KeyPress{Key::seq0}});
  }
  SUBCASE ("KeyRelease") {
    com.data = {5, 3, 0, 0, 0, 0, 0, 0};
    ctrl->read_input_data();
    handler.events.clear();

    com.data = {4, 3, 0, 0, 0, 0, 0, 0};
    ctrl->read_input_data();
    REQUIRE(handler.events == Events{KeyRelease{Key::seq0}});
  }

  SUBCASE ("Single EncoderEvent") {
    com.data = {0, 0, 0, 0, 20, 0, 0, 0};
    ctrl->read_input_data();
    REQUIRE(handler.events == Events{EncoderEvent{Encoder::blue, 20}});
  }

  SUBCASE ("Two EncoderEvents") {
    com.data = {0, 0, 0, 0, 20, 0, 0, 0};
    ctrl->read_input_data();
    com.data = {0, 0, 0, 0, 40, 0, 0, 0};
    ctrl->read_input_data();
    REQUIRE(handler.events == Events{EncoderEvent{Encoder::blue, 20}, EncoderEvent{Encoder::blue, 20}});
  }

  SUBCASE ("Negative EncoderEvents") {
    com.data = {0, 0, 0, 0, 20, 0, 0, 0};
    ctrl->read_input_data();
    com.data = {0, 0, 0, 0, 0, 0, 0, 0};
    ctrl->read_input_data();
    REQUIRE(handler.events == Events{EncoderEvent{Encoder::blue, 20}, EncoderEvent{Encoder::blue, -20}});
  }

  SUBCASE ("EncoderEvents with rollover") {
    com.data = {0, 0, 0, 0, 255, 0, 0, 0};
    ctrl->read_input_data();
    com.data = {0, 0, 0, 0, 0, 0, 0, 0};
    ctrl->read_input_data();
    REQUIRE(handler.events == Events{EncoderEvent{Encoder::blue, -1}, EncoderEvent{Encoder::blue, 1}});
  }

  SUBCASE ("Rollover limits") {
    SUBCASE ("lower") {
      com.data = {0, 0, 0, 0, 128, 0, 0, 0};
      ctrl->read_input_data();
      REQUIRE(handler.events == Events{EncoderEvent{Encoder::blue, -128}});
    }
    SUBCASE ("upper") {
      com.data = {0, 0, 0, 0, 127, 0, 0, 0};
      ctrl->read_input_data();
      REQUIRE(handler.events == Events{EncoderEvent{Encoder::blue, 127}});
    }
  }

  SUBCASE ("Errors") {
    SUBCASE ("Too little data") {
      com.data = {0, 0, 0, 0, 0, 0, 0};
      REQUIRE_THROWS_WITH_AS(ctrl->read_input_data(), "Data had invalid length. Got 7 bytes, expected 8", util::exception);
    }
    SUBCASE ("Too much data") {
      com.data = {0, 0, 0, 0, 0, 0, 0, 0, 0};
      REQUIRE_THROWS_WITH_AS(ctrl->read_input_data(), "Data had invalid length. Got 9 bytes, expected 8", util::exception);
    }
  }
}

TEST_CASE("MCUController thread")
