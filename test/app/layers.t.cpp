#include "testing.t.hpp"

#include "app/layers.hpp"

using namespace otto;

namespace {
  using Events = std::vector<std::variant<UntimedKeyPress, UntimedKeyRelease, UntimedEncoderEvent>>;

  struct StubInputLayer final : ConstInputLayer {
    StubInputLayer(util::enum_bitset<Key> keys) : ConstInputLayer(keys) {}

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
} // namespace

TEST_CASE ("InputLayer") {
  LayerStack stack;

  SECTION ("Basics") {
    StubInputLayer l1 = {{Key::channel0, Key::channel1, Key::channel2}};
    stack.add_layer(l1);
    CAPTURE(&l1);
    REQUIRE(stack.layer_for(Key::arp) == nullptr);
    REQUIRE(stack.layer_for(Key::channel0) == &l1);
    REQUIRE(stack.layer_for(Key::channel1) == &l1);
    REQUIRE(stack.layer_for(Key::channel2) == &l1);

    StubInputLayer l2 = {{Key::seq0, Key::seq1}};
    stack.add_layer(l2);
    CAPTURE(&l2);

    REQUIRE(stack.layer_for(Key::seq0) == &l2);
    REQUIRE(stack.layer_for(Key::seq1) == &l2);
    REQUIRE(stack.layer_for(Key::channel0) == &l1);

    StubInputLayer l3 = {{Key::seq0}};
    stack.add_layer(l3);
    CAPTURE(&l3);

    REQUIRE(stack.layer_for(Key::seq0) == &l3);
    REQUIRE(stack.layer_for(Key::seq1) == &l2);
    REQUIRE(stack.layer_for(Key::channel0) == &l1);
  }

  SECTION ("Encoder events are masked by their corresponding click") {
    StubInputLayer l1 = {{Key::red_enc_click}};
    stack.add_layer(l1);

    StubInputLayer l2 = {{Key::red_enc_click}};
    stack.add_layer(l2);

    StubInputLayer l3 = {{Key::blue_enc_click}};
    stack.add_layer(l3);

    SECTION ("1") {
      stack.handle(EncoderEvent{Encoder::red});
      REQUIRE(l1.events.empty());
      REQUIRE(l2.events.size() == 1);
      REQUIRE(l3.events.empty());
    }

    SECTION ("2") {
      stack.handle(EncoderEvent{Encoder::blue});
      REQUIRE(l1.events.empty());
      REQUIRE(l2.events.empty());
      REQUIRE(l3.events.size() == 1);
    }

    SECTION ("3") {
      stack.handle(EncoderEvent{Encoder::green});
      REQUIRE(l1.events.empty());
      REQUIRE(l2.events.empty());
      REQUIRE(l3.events.empty());
    }
  }
}

struct StubLEDLayer final : ConstLEDLayer {
  StubLEDLayer(LEDColor color, util::enum_bitset<Led> leds) : ConstLEDLayer(leds), color(color) {}

  void leds(LEDColorSet& colors) noexcept override
  {
    for (Led l : util::enum_values<Led>()) {
      colors[l] = color;
    }
  }

  LEDColor color;
};

TEST_CASE ("LEDLayer") {
  LayerStack stack;

  StubLEDLayer red = {led_colors::red, led_groups::seq};
  stack.add_layer(red);
  StubLEDLayer green = {led_colors::green, led_groups::channel};
  stack.add_layer(green);
  StubLEDLayer blue = {led_colors::blue, led_groups::func};
  stack.add_layer(blue);

  REQUIRE(stack.layer_for(Led::seq0) == &red);
  REQUIRE(stack.layer_for(Led::channel0) == &green);
  REQUIRE(stack.layer_for(Led::arp) == &blue);

  LEDColorSet colors;
  SECTION ("led processing") {
    stack.leds(colors);

    for (auto&& [k, v] : colors) {
      if (led_groups::seq.test(k)) {
        REQUIRE(v == led_colors::red);
      } else if (led_groups::channel.test(k)) {
        REQUIRE(v == led_colors::green);
      } else if (led_groups::func.test(k)) {
        REQUIRE(v == led_colors::blue);
      } else {
        FAIL("All LEDs should be covered");
      }
    }
  }

  StubLEDLayer white = {led_colors::white, {Led::arp}};
  stack.add_layer(white);

  SECTION ("stacked led processing") {
    stack.leds(colors);

    for (auto&& [k, v] : colors) {
      if (k == Led::arp) {
        REQUIRE(v == led_colors::white);
      } else if (led_groups::seq.test(k)) {
        REQUIRE(v == led_colors::red);
      } else if (led_groups::channel.test(k)) {
        REQUIRE(v == led_colors::green);
      } else if (led_groups::func.test(k)) {
        REQUIRE(v == led_colors::blue);
      } else {
        FAIL("All LEDs should be covered");
      }
    }
  }
}
