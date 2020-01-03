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
    using Sender = itc::DirectActionSender<EngineSelectorScreen>;

    EngineSelectorScreen screen;
    Sender sender = {screen};
    sender.push(PublishEngineNames::action::data(engine_names));

    struct Props : InputHandler {
      Sender sender;

      SelectedEngine::Prop<Sender> selected_engine_idx = {sender, 0, limits(0, engine_names.size() - 1)};
      SelectedPreset::Prop<Sender> selected_preset_idx = {sender, 0, limits(0, 12)};
      CurrentScreen::Prop<Sender> current_screen = {sender, +ESSSubscreen::engine_selection};
      WriterUI preset_name_writer;

      Props(const Sender& sender) : sender(sender)
      {
        selected_engine_idx.on_change().connect([&] { selected_preset_idx = 0; });
      }

      void encoder(EncoderEvent e)
      {
        if (current_screen == ESSSubscreen::engine_selection) {
          switch (e.encoder) {
            case Encoder::blue: selected_engine_idx.step(e.steps); break;
            case Encoder::green: current_screen = +ESSSubscreen::preset_selection; break;
            default: break;
          }
        } else if (current_screen == ESSSubscreen::preset_selection) {
          switch (e.encoder) {
            case Encoder::blue: current_screen = +ESSSubscreen::engine_selection; break;
            case Encoder::green: selected_preset_idx.step(e.steps); break;
            case Encoder::red:
              if (e.steps > 0) current_screen = +ESSSubscreen::new_preset;
              break;
            default: break;
          }
        } else if (current_screen == ESSSubscreen::new_preset) {
          switch (e.encoder) {
            case Encoder::blue:
              preset_name_writer.cycle_char(e.steps);
              sender.push(NewPresetName::action::data(preset_name_writer.to_string()));
              break;
            case Encoder::green:
              preset_name_writer.cycle_group(e.steps);
              sender.push(NewPresetName::action::data(preset_name_writer.to_string()));
              break;
            case Encoder::yellow:
              preset_name_writer.step_idx(e.steps);
              sender.push(CursorPos::action::data(preset_name_writer.cursor()));
              break;
            case Encoder::red:
              if (e.steps < 0) current_screen = +ESSSubscreen::preset_selection;
              break;
            default: break;
          }
        }
      }

      bool keypress(Key key)
      {
        switch (key) {
          case Key::blue_click: //
            current_screen = +ESSSubscreen::engine_selection;
            return true;
          default: return false;
        }
      }

    } props{sender};

    test::show_gui([&](nvg::Canvas& ctx) { screen.draw(ctx); }, &props);
  }

  TEST_CASE ("WriterUI") {
    WriterUI ws;

    SUBCASE ("Starts out with empty string") {
      REQUIRE(ws.to_string() == "");
    }

    SUBCASE ("Changing first letter to 9") {
      ws.cycle_char(-1);
      REQUIRE(ws.to_string() == "9");
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
      REQUIRE(ws.to_string() == "y a");
    }

    SUBCASE ("Two letters") {
      ws.cycle_char(1);
      ws.step_idx(1);
      ws.cycle_char(2);
      REQUIRE(ws.to_string() == "AB");
    }

    SUBCASE ("cycling to a shorter group and cycling back doesnt change char") {
      ws.cycle_char(25);
      ws.cycle_group(2);
      ws.cycle_group(-1);
      REQUIRE(ws.to_string() == "Y");
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
