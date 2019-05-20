#include "ui_manager.hpp"

#include "services/audio_manager.hpp"
#include "services/engine_manager.hpp"
#include "services/state_manager.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::services {

  using namespace core::ui;
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

  void UIManager::select_engine(core::engine::IEngine& engine)
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
  void UIManager::draw_frame(vg::Canvas& ctx)
  {
    ctx.lineWidth(6);
    ctx.lineCap(vg::Canvas::LineCap::ROUND);
    ctx.lineJoin(vg::Canvas::Canvas::LineJoin::ROUND);
    ctx.group([&] {
      cur_screen->draw(ctx);
    });

    ctx.group([&] {
      ctx.beginPath();
      ctx.fillStyle(vg::Colours::White);
      ctx.font(vg::Fonts::Norm, 12);
      std::string cpu_time = fmt::format("{}%", int(100 * Application::current().audio_manager->cpu_time()));
      ctx.fillText(cpu_time, {290, 230});
    });

    _frame_count++;
  }

} // namespace otto::services
