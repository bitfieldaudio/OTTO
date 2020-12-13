#include "testing.t.hpp"

#include "app/input/navigator.hpp"

using namespace otto;

struct Screen : IScreen {
  void draw(skia::Canvas& ctx) noexcept override {}
};

TEST_CASE ("navigator") {
  ScreenWithHandler a = {std::make_unique<Screen>(), std::make_unique<InputHandler>()};
  ScreenWithHandler b = {std::make_unique<Screen>(), std::make_unique<InputHandler>()};
  ScreenWithHandler c = {std::make_unique<Screen>(), std::make_unique<InputHandler>()};

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
  ScreenWithHandler arp = {std::make_unique<Screen>(), std::make_unique<InputHandler>()};
  ScreenWithHandler synth = {std::make_unique<Screen>(), std::make_unique<InputHandler>()};
  ScreenWithHandler c = {std::make_unique<Screen>(), std::make_unique<InputHandler>()};

  Navigator nav;
  NavKeyMap nkm = {&nav, 100ms};

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
