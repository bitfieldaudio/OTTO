#include "testing.t.hpp"

#include "app/layers/navigator.hpp"

#include "app/services/graphics.hpp"

using namespace otto;

namespace {

  struct Screen : ScreenBase {
    void draw(skia::Canvas& ctx) noexcept override {}
  };

  struct StubInputLayer : ConstInputLayer, InputHandler {
    using ConstInputLayer::ConstInputLayer;
  };
} // namespace

TEST_CASE ("navigator") {
  ScreenWithHandler a = {std::make_unique<Screen>(), std::make_unique<StubInputLayer>(KeySet{})};
  ScreenWithHandler b = {std::make_unique<Screen>(), std::make_unique<StubInputLayer>(KeySet{})};
  ScreenWithHandler c = {std::make_unique<Screen>(), std::make_unique<StubInputLayer>(KeySet{})};

  Navigator nav;

  REQUIRE(nav.current_screen() == nullptr);
  nav.navigate_to(a);
  REQUIRE(nav.current_screen() == a);
  REQUIRE(nav.navigate_back() == false);
  REQUIRE(nav.current_screen() == a);
  nav.navigate_to(b);
  REQUIRE(nav.current_screen() == b);
  REQUIRE(nav.navigate_back() == true);
  REQUIRE(nav.current_screen() == a);
  nav.navigate_to(b);
  nav.navigate_to(c);
  REQUIRE(nav.current_screen() == c);
  REQUIRE(nav.navigate_back() == true);
  REQUIRE(nav.current_screen() == b);
  REQUIRE(nav.navigate_back() == false);
  REQUIRE(nav.current_screen() == b);
}

TEST_CASE ("NavKeyMap") {
  ScreenWithHandler arp = {std::make_unique<Screen>(), std::make_unique<StubInputLayer>(KeySet{})};
  ScreenWithHandler synth = {std::make_unique<Screen>(), std::make_unique<StubInputLayer>(KeySet{})};
  ScreenWithHandler c = {std::make_unique<Screen>(), std::make_unique<StubInputLayer>(KeySet{})};

  Navigator nav;
  NavKeyMap nkm = {NavKeyMap::Conf{.peek_timeout = 100ms}, &nav};

  nkm.bind_nav_key(Key::arp, arp);
  nkm.bind_nav_key(Key::synth, synth);

  SECTION ("Bind/press") {
    REQUIRE(nav.current_screen() == nullptr);
    nkm.handle(KeyPress{Key::arp});
    REQUIRE(nav.current_screen() == arp);
  }

  SECTION ("Permanent navigation when held for less than the timeout") {
    nav.navigate_to(synth);
    auto time = chrono::clock::now();
    nkm.handle(KeyPress{Key::arp, time});
    REQUIRE(nav.current_screen() == arp);
    nkm.handle(KeyRelease{Key::arp, time + 99ms});
    REQUIRE(nav.current_screen() == arp);
  }

  SECTION ("Momentary navigation when held for longer than the timeout") {
    nav.navigate_to(synth);
    auto time = chrono::clock::now();
    nkm.handle(KeyPress{Key::arp, time});
    REQUIRE(nav.current_screen() == arp);
    nkm.handle(KeyRelease{Key::arp, time + 101ms});
    REQUIRE(nav.current_screen() == synth);
  }

  SECTION ("LED Mask") {
    auto mask = nkm.led_mask();
    REQUIRE(mask == LedSet({Led::arp, Led::synth}));
  }

  SECTION ("Key Mask") {
    auto mask = nkm.key_mask();
    REQUIRE(mask == KeySet({Key::arp, Key::synth}));
  }

  SECTION ("serialization") {
    nav.navigate_to(synth);
    auto json = util::serialize(nkm);
    nav.navigate_to(arp);
    util::deserialize_from(json, nkm);
    REQUIRE(nav.current_screen() == synth);
  }

  /*
   * Can be implemented if deemed necessary, it probably depends on the timeout
  SECTION ("Momentary navigation when receiving other presses while pressed") {
    nav.navigate_to(synth);
    nkm.handle(KeyPress{Key::arp});
    REQUIRE(nav.current_screen() == arp);
    std::this_thread::sleep_for(150ms);
    nkm.handle(KeyPress{Key::channel0});
    nkm.handle(KeyRelease{Key::arp});
    REQUIRE(nav.current_screen() == synth);
  }

  SECTION ("Momentary navigation when receiving encoder events while pressed") {
    nav.navigate_to(synth);
    nkm.handle(KeyPress{Key::arp});
    REQUIRE(nav.current_screen() == arp);
    std::this_thread::sleep_for(150ms);
    nkm.handle(EncoderEvent{});
    nkm.handle(KeyRelease{Key::arp});
    REQUIRE(nav.current_screen() == synth);
  }

  // But not for other keyreleases, as to not confuse key combos
  SECTION ("Permanent navigation when receiving other release events while pressed") {
    nav.navigate_to(synth);
    nkm.handle(KeyPress{Key::arp});
    REQUIRE(nav.current_screen() == arp);
    std::this_thread::sleep_for(150ms);
    nkm.handle(KeyRelease{Key::channel0});
    nkm.handle(KeyRelease{Key::arp});
    REQUIRE(nav.current_screen() == arp);
  }
  */
}
