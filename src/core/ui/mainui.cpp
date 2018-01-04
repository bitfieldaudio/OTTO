#include "mainui.hpp"

#include <map>

#include "core/globals.hpp"
#include "services/state.hpp"
#include "services/engine_manager.hpp"

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
    std::multimap<Key, KeyHandler> key_handlers;
  }

  bool is_pressed(Key k) noexcept
  {
    return keys[static_cast<unsigned>(k)];
  }

  void select_engine(const std::string& engine_name) {
    selected_engine_name = engine_name;

    auto engine = engines::by_name(engine_name);
    if (!engine) {
      engine = engines::by_name(initial_engine);
    }
    if (engine != nullptr) {
      select_engine(*engine);
    }

  }

  void select_engine(engines::AnyEngine& engine) {
    display(engine.screen());
    selected_engine_name = engine.name();
  }

  static void register_screen_keys()
  {
  }

  void init() {
    register_screen_keys();

    auto load = [](const nlohmann::json &j) {
      if (j.is_object()) {
        selected_engine_name = j["SelectedEngine"];
      }

      select_engine(selected_engine_name);
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

  void register_key_handler(Key k, KeyHandler handler)
  {
    key_handlers.emplace(k, handler);
  }

  namespace impl {
    static bool global_keypress(Key key)
    {
      if (key == Key::quit) {
        global::exit(global::ErrorCode::user_exit);
        return true;
      }

      auto [first, last] = key_handlers.equal_range(key);
      if (first == last)
        return false;

      for (auto it = first; it != last; it++) {
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
