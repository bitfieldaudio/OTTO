#include "core/engine/engine_selector_screen.hpp"
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

  TEST_CASE ("EngineSelectorScreen", "[.graphics]") {
    using Sender = itc::DirectActionSender<EngineSelectorScreen>;

    EngineSelectorScreen screen;
    Sender sender = {screen};
    sender.push(PublishEngineNames::action::data(engine_names));

    struct Props : InputHandler {
      Sender sender;

      SelectedEngine::Prop<Sender> selected_engine_idx = {sender, 0, limits(0, engine_names.size() - 1)};
      SelectedPreset::Prop<Sender> selected_preset_idx = {sender, 0, limits(0, 12)};
      CurrentScreen::Prop<Sender> current_screen = {sender, 0, limits(0, 1)};

      Props(const Sender& sender) : sender(sender)
      {
        selected_engine_idx.on_change().connect([&] { selected_preset_idx = 0; });
      }

      void encoder(EncoderEvent e) override
      {
        switch (e.encoder) {
          case Encoder::blue:
            if (current_screen != 0)
              current_screen = 0;
            else
              selected_engine_idx.step(e.steps);
            break;
          case Encoder::green:
            if (current_screen != 1)
              current_screen = 1;
            else
              selected_preset_idx.step(e.steps);
            break;
          default: break;
        }
      }

      bool keypress(Key key) override
      {
        switch (key) {
          case Key::blue_click: //
            current_screen = 1;
            return true;
          default: return false;
        }
      }

    } props{sender};

    test::show_gui([&](nvg::Canvas& ctx) { screen.draw(ctx); }, &props);
  }

} // namespace otto
