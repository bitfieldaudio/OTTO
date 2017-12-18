#include "mainui.hpp"

#include "core/globals.hpp"

namespace otto::ui {

  static constexpr const char * INITIAL_ENGINE = "TapeDeck";

  // Local vars
  namespace {

    struct EmptyScreen : Screen {

      void draw(vg::Canvas& ctx)
      {}

    } empty_screen;

    std::map<std::string, std::function<engines::AnyEngine *()>> engines = {
      { "TapeDeck", []() { return (engines::AnyEngine*)&global::tapedeck; } },
      { "Mixer", []() { return (engines::AnyEngine*)&global::mixer; } },
      { "Synth", []() { return (engines::AnyEngine*)&*global::synth; } },
      { "Drums", []() { return (engines::AnyEngine*)&*global::drums; } },
      { "Metronome", []() { return (engines::AnyEngine*)&global::metronome; } }
    };

    std::string selected_engine_name = "";
    Screen* cur_screen = &empty_screen;

    PressedKeys keys;
  }

  bool is_pressed(Key k) noexcept
  {
    return keys[static_cast<unsigned>(k)];
  }

  void selectEngine(std::string engine_name) {
    selected_engine_name = engine_name;

    auto getter = engines[engine_name];
    if (!getter) {
      getter = engines[INITIAL_ENGINE];
      selected_engine_name = INITIAL_ENGINE;
    }

    auto engine = getter();

    display(engine->screen());
  }

  void init() {
    selectEngine(selected_engine_name);
  }

  void display(Screen& screen)
  {
    cur_screen->on_hide();
    cur_screen = &screen;
    cur_screen->on_show();
  }

  nlohmann::json to_json() {
    auto obj = nlohmann::json::object();

    obj["SelectedEngine"] = selected_engine_name;

    return obj;
  }

  void from_json(const nlohmann::json &j) {
    if (j.is_object()) {
      selected_engine_name = j["SelectedEngine"];
    }
  }

  namespace impl {

    static bool global_keypress(Key key)
    {
      switch (key) {
      case Key::quit: global::exit(global::ErrorCode::user_exit); break;
      case Key::tape: selectEngine("TapeDeck"); break;
      case Key::mixer: selectEngine("Mixer"); break;
      case Key::synth: selectEngine("Synth"); break;
      case Key::drums: selectEngine("Drums"); break;
      case Key::metronome:
        selectEngine("Metronome");
        break;
      case ui::Key::play:
        if (global::tapedeck.state.playing()) {
          global::tapedeck.state.stop();
        } else {
          global::tapedeck.state.play();
        }
        break;
      default: return false;
      }
      return true;
    }

    void draw_frame(vg::Canvas& ctx)
    {
      ctx.lineWidth(2);
      ctx.lineCap(vg::Canvas::LineCap::ROUND);
      ctx.lineJoin(vg::Canvas::Canvas::LineJoin::ROUND);
      cur_screen->draw(ctx);
    }

    bool keypress(Key key)
    {
      switch (key) {
      case Key::red_up: cur_screen->rotary({Rotary::Red, 1}); break;
      case Key::red_down: cur_screen->rotary({Rotary::Red, -1}); break;
      case Key::blue_up: cur_screen->rotary({Rotary::Blue, 1}); break;
      case Key::blue_down: cur_screen->rotary({Rotary::Blue, -1}); break;
      case Key::white_up: cur_screen->rotary({Rotary::White, 1}); break;
      case Key::white_down: cur_screen->rotary({Rotary::White, -1}); break;
      case Key::green_up: cur_screen->rotary({Rotary::Green, 1}); break;
      case Key::green_down: cur_screen->rotary({Rotary::Green, -1}); break;
      default:
        keys[static_cast<unsigned>(key)] = true;
        if (global_keypress(key)) return true;
        return cur_screen->keypress(key);
      }
      return true;
    }

    bool keyrelease(Key key)
    {
      keys[static_cast<unsigned>(key)] = false;
      return cur_screen->keyrelease(key);
    }
  } // namespace impl

} // namespace otto::ui
