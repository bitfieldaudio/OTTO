#include "testing.t.hpp"

#include "app/services/led_manager.hpp"

#include "app/services/controller.hpp"
#include "app/services/graphics.hpp"

using namespace otto;
using namespace otto::drivers;
using namespace otto::services;

namespace Catch {

  template<>
  struct StringMaker<Packet> {
    static std::string convert(Packet const& value)
    {
      return fmt::format("{{{}, {}}}", util::enum_name(value.cmd), fmt::join(value.data, ", "));
    }
  };

} // namespace Catch

TEST_CASE ("LedManager") {
  std::vector<Packet> packets;
  LedManager ledman([&](Packet p) { packets.push_back(p); });
  SECTION ("send_colors") {
    ledman.colors.fill(led_colors::black);
    ledman.send_colors({Led::channel0, Led::channel1, Led::channel2, Led::channel3, Led::channel4, Led::channel5});
    REQUIRE(packets.size() == 2);
    REQUIRE(packets[0] ==
            Packet{Command::leds_buffer,
                   {util::enum_integer(Led::channel0), 0, 0, 0, util::enum_integer(Led::channel1), 0, 0, 0,
                    util::enum_integer(Led::channel2), 0, 0, 0, util::enum_integer(Led::channel3), 0, 0, 0}});
    REQUIRE(packets[1] == Packet{Command::leds_commit,
                                 {util::enum_integer(Led::channel4), 0, 0, 0, //
                                  util::enum_integer(Led::channel5), 0, 0, 0, //
                                  255, 255, 255, 255, 255, 255, 255, 255}});
  }

  SECTION ("process") {
    struct LC : ILedController {
      void leds(LEDColorSet& colors) noexcept final
      {
        colors[Led::channel0] = led_colors::white;
      }
    } lc;
    ledman.colors.fill(led_colors::black);
    ledman.process(lc);
    REQUIRE(packets.size() == 1);
    REQUIRE(packets[0] == Packet{Command::leds_commit,
                                 {util::enum_integer(Led::channel0), 255, 255, 255, //
                                  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255}});
  }
}

TEST_CASE ("led perf", "[.interactive]") {
  ConfigManager cm;
  std::unique_ptr mcu = MCUPort::make_default(cm);
  LedManager ledman = LedManager::Sender(mcu.get());
  ledman.colors.fill({0x40, 0x00, 0x00});
  ledman.send_colors();

  std::this_thread::sleep_for(1s);

  ledman.colors.fill({0x00, 0x00, 0x40});
  ledman.send_colors();
}

TEST_CASE ("flash_leds", "[.interactive]") {
  ConfigManager cm;
  std::unique_ptr mcu = MCUPort::make_default(cm);
  LedManager ledman = LedManager::Sender(mcu.get());
  for (int i = 0; i < 100; i++) {
    ledman.colors.fill({0x20, 0x20, 0x20});
    ledman.send_colors();
    ledman.colors.fill({0x00, 0x00, 0x00});
    ledman.send_colors();
  }
}
