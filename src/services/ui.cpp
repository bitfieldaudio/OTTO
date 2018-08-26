#include "ui.hpp"

#include <map>

#include "util/locked.hpp"

#include "core/globals.hpp"
#include "services/engines.hpp"
#include "services/state.hpp"

namespace otto::service::ui {

  using namespace core::ui;

  static constexpr const char* initial_engine = "Synth";

  // Local vars
  namespace {
    struct EmptyScreen : Screen {
      void draw(vg::Canvas& ctx) {}
    } empty_screen;

    std::string _selected_engine_name = "";
    Screen* cur_screen = &empty_screen;

    PressedKeys keys;
    std::multimap<Key, KeyHandler> key_handlers;
    struct KeyPress {
      Key key;
    };
    struct KeyRelease {
      Key key;
    };
    using KeyEvent = mpark::variant<KeyPress, KeyRelease>;
    util::atomic_swap<std::vector<KeyEvent>> key_events;
    util::atomic_swap<std::vector<RotaryEvent>> rotary_events;
  } // namespace

  bool is_pressed(Key k) noexcept
  {
    return keys[static_cast<unsigned>(k)];
  }

  void select_engine(const std::string& engine_name)
  {
    _selected_engine_name = engine_name;

    auto engine = engines::by_name(engine_name);
    if (!engine) {
      engine = engines::by_name(initial_engine);
    }
    if (engine != nullptr) {
      display(engine->screen());
      _selected_engine_name = engine_name;
    }
  }

  void select_engine(core::engines::AnyEngine& engine)
  {
    display(engine.screen());
    _selected_engine_name = engine.name();
  }

  const std::string& selected_engine_name()
  {
    return _selected_engine_name;
  }

  static void register_screen_keys() {}

  void init()
  {
    register_screen_keys();

    auto load = [](const nlohmann::json& j) {
      if (j.is_object()) {
        _selected_engine_name = j["SelectedEngine"];
      }

      select_engine(_selected_engine_name);
    };

    auto save = []() { return nlohmann::json({{"SelectedEngine", _selected_engine_name}}); };

    service::state::attach("UI", load, save);
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
      if (first == last) return false;

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

    void keypress(Key key)
    {
      key_events.outer().push_back(KeyPress{key});
    }

    void rotary(RotaryEvent ev)
    {
      rotary_events.outer().push_back(ev);
    }

    void keyrelease(Key key)
    {
      key_events.outer().push_back(KeyRelease{key});
    }

    void flush_events()
    {
      key_events.swap();
      for (auto& event : key_events.inner()) {
        util::match( //
          event,
          [](KeyPress ev) {
            switch (ev.key) {
            case Key::red_up: cur_screen->rotary({Rotary::Red, 1}); break;
            case Key::red_down: cur_screen->rotary({Rotary::Red, -1}); break;
            case Key::blue_up: cur_screen->rotary({Rotary::Blue, 1}); break;
            case Key::blue_down: cur_screen->rotary({Rotary::Blue, -1}); break;
            case Key::white_up: cur_screen->rotary({Rotary::White, 1}); break;
            case Key::white_down: cur_screen->rotary({Rotary::White, -1}); break;
            case Key::green_up: cur_screen->rotary({Rotary::Green, 1}); break;
            case Key::green_down: cur_screen->rotary({Rotary::Green, -1}); break;
            default:
              keys[static_cast<unsigned>(ev.key)] = true;
              if (global_keypress(ev.key)) return;
              cur_screen->keypress(ev.key);
            }
          },
          [](KeyRelease& ev) {
            keys[static_cast<unsigned>(ev.key)] = false;
            cur_screen->keyrelease(ev.key);
          });
      }
      rotary_events.swap();
      for (auto& event : rotary_events.inner()) {
        cur_screen->rotary(event);
      }
    }
  } // namespace impl
} // namespace otto::service::ui
