#include "ui_manager.hpp"

#include "services/state_manager.hpp"
#include "services/engine_manager.hpp"

namespace otto::services {

  using namespace core::ui;

  bool UIManager::is_pressed(Key k) noexcept
  {
    return keys[static_cast<unsigned>(k)];
  }

  void UIManager::select_engine(const std::string& engine_name)
  {
    _selected_engine_name = engine_name;

    auto engine = Application::current().engine_manager->by_name(engine_name);
    if (!engine) {
      engine = Application::current().engine_manager->by_name(initial_engine);
    }
    if (engine != nullptr) {
      display(engine->screen());
      _selected_engine_name = engine_name;
    }
  }

  void UIManager::select_engine(core::engine::AnyEngine& engine)
  {
    display(engine.screen());
    _selected_engine_name = engine.name();
  }

  const std::string& UIManager::selected_engine_name()
  {
    return _selected_engine_name;
  }

  UIManager::UIManager()
  {
    auto load = [this](const nlohmann::json& j) {
      if (j.is_object()) {
        _selected_engine_name = j["SelectedEngine"];
      }
      select_engine(_selected_engine_name);
    };

    auto save = [this]() { return nlohmann::json({{"SelectedEngine", _selected_engine_name}}); };

    Application::current().state_manager->attach("UI", load, save);
  }

  void UIManager::display(Screen& screen)
  {
    cur_screen->on_hide();
    cur_screen = &screen;
    cur_screen->on_show();
  }

  core::ui::Screen* UIManager::current_screen()
  {
    return cur_screen;
  }

  void UIManager::register_key_handler(Key k, KeyHandler press_handler, KeyHandler release_handler)
  {
    key_handlers.emplace(k, std::pair{std::move(press_handler), std::move(release_handler)});
  }

  bool UIManager::handle_global(Key key, bool is_press)
  {
    if (key == Key::quit) {
      Application::current().exit(Application::ErrorCode::user_exit);
      return true;
    }

    auto [first, last] = key_handlers.equal_range(key);
    if (first == last) return false;

    for (auto&& [key, funcs] : util::sequence(first, last)) {
      auto& func = is_press ? funcs.first : funcs.second;
      if (func) func(key);
    }

    return true;
  }

  void UIManager::draw_frame(vg::Canvas& ctx)
  {
    ctx.lineWidth(2);
    ctx.lineCap(vg::Canvas::LineCap::ROUND);
    ctx.lineJoin(vg::Canvas::Canvas::LineJoin::ROUND);
    cur_screen->draw(ctx);
  }

  void UIManager::keypress(Key key)
  {
    key_events.outer().push_back(KeyPress{key});
  }

  void UIManager::rotary(RotaryEvent ev)
  {
    rotary_events.outer().push_back(ev);
  }

  void UIManager::keyrelease(Key key)
  {
    key_events.outer().push_back(KeyRelease{key});
  }

  void UIManager::flush_events()
  {
    key_events.swap();
    for (auto& event : key_events.inner()) {
      util::match(event,
                  [this](KeyPress ev) {
                    keys[static_cast<unsigned>(ev.key)] = true;
                    if (handle_global(ev.key)) return;
                    cur_screen->keypress(ev.key);
                  },
                  [this](KeyRelease& ev) {
                    keys[static_cast<unsigned>(ev.key)] = false;
                    if (handle_global(ev.key, false)) return;
                    cur_screen->keyrelease(ev.key);
                  });
    }

    rotary_events.swap();
    for (auto& event : rotary_events.inner()) {
      cur_screen->rotary(event);
    }
  }
} // namespace otto::services
