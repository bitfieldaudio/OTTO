#include "mainui.hpp"

#include <map>

#include "core/globals.hpp"
#include "services/state.hpp"
#include "core/engines/engine_manager.hpp"

namespace otto::ui {
  static constexpr const char * initial_engine = "TapeDeck";

  // Local vars
  namespace {
    struct EmptyScreen : Screen {
      void draw(vg::Canvas& ctx) {}
    } empty_screen;

    std::string selected_engine_name = "";
    Screen* cur_screen = &empty_screen;

    PressedKeys keys;
    std::multimap<Key, key_handler> key_handlers;
  }

  bool is_pressed(Key k) noexcept
  {
    return keys[static_cast<unsigned>(k)];
  }

  void selectEngine(std::string engine_name) {
    selected_engine_name = engine_name;

    auto engine = engines::getEngineByName(engine_name);
    if (!engine) {
      engine = engines::getEngineByName(initial_engine);
    }

    display(engine->screen());
  }

  static void registerScreenKeys()
  {
    registerKeyHandler(Key::tape, [](Key k){ selectEngine("TapeDeck"); });
    registerKeyHandler(Key::mixer, [](Key k){ selectEngine("Mixer"); });
    registerKeyHandler(Key::synth, [](Key k){ selectEngine("Synth"); });
    registerKeyHandler(Key::drums, [](Key k){ selectEngine("Drums"); });
    registerKeyHandler(Key::metronome, [](Key k){ selectEngine("Metronome"); });
  }

  void init() {
    registerScreenKeys();

    auto load = [](const nlohmann::json &j) {
      if (j.is_object()) {
        selected_engine_name = j["SelectedEngine"];
      }

      selectEngine(selected_engine_name);
    };

    auto save = []() {
      return nlohmann::json({
        {"SelectedEngine", selected_engine_name}
      });
    };

    services::state::attach("UI", load, save);
  }

  void display(Screen& screen)
  {
    cur_screen->on_hide();
    cur_screen = &screen;
    cur_screen->on_show();
  }

  void registerKeyHandler(Key k, key_handler handler)
  {
    key_handlers.insert({k, handler});
  }

  namespace impl {
    static bool global_keypress(Key key)
    {
      if (key == Key::quit) {
        global::exit(global::ErrorCode::user_exit);
        return true;
      }

      auto result = key_handlers.equal_range(key);
      int count = std::distance(result.first, result.second);
      if (count == 0) {
        return false;
      }

    	for (auto it = result.first; it != result.second; it++) {
        it->second(key);
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
