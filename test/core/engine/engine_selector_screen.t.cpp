#include "core/engine/engine_selector_screen.hpp"
#include "graphics.t.hpp"
#include "testing.t.hpp"


namespace otto {

  using namespace core::engine;
  using namespace core::input;
  using namespace core::props;

  constexpr std::array<util::string_ref, 4> engine_names = {
    "OTTO.FM",
    "Goss",
    "Potion",
    "Subtraction",
  };

  TEST_CASE ("[graphics] EngineSelectorScreen" * doctest::skip()) {
    EngineSelectorScreen screen;

    struct Props : InputHandler, util::OwnsObservers {
      SelectedEngine::GAProp<> selected_engine_idx = {0, limits(0, engine_names.size() - 1)};
      SelectedPreset::GAProp<> selected_preset_idx = {0, limits(0, 12)};

      Props() 
      {
        selected_engine_idx.observe(this, [&] { selected_preset_idx = 0; });
      }

    } props;

    test::show_gui([&](nvg::Canvas& ctx) { screen.draw(ctx); }, &props);
  }

  TEST_CASE ("WriterUI") {
    WriterUI ws;

    SUBCASE ("Starts out with empty string") {
      REQUIRE(ws.to_string() == "");
    }

    SUBCASE ("Changing first letter to ?") {
      ws.cycle_char(-1);
      REQUIRE(ws.to_string() == "?");
    }

    SUBCASE ("Changing first letter to A") {
      ws.cycle_char(1);
      REQUIRE(ws.to_string() == "A");
    }

    SUBCASE ("Changing first letter to B") {
      ws.cycle_char(2);
      REQUIRE(ws.to_string() == "B");
    }

    SUBCASE ("Jumping two groups and trim start") {
      ws.step_idx(3);
      ws.cycle_char(-12);
      ws.step_idx(2);
      ws.cycle_char(27);
      REQUIRE(ws.to_string() == "= a");
    }

    SUBCASE ("Two letters") {
      ws.cycle_char(1);
      ws.step_idx(1);
      ws.cycle_char(2);
      REQUIRE(ws.to_string() == "AB");
    }

    SUBCASE ("No trim preserves all spaces at beginning, and two at the end") {
      ws.step_idx(2);
      ws.cycle_char(1);
      ws.step_idx(1);
      ws.cycle_char(2);
      REQUIRE(ws.to_string(false) == " AB  ");
    }
  }

} // namespace otto
