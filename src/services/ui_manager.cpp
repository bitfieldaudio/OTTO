#include "ui_manager.hpp"

#include "services/audio_manager.hpp"
#include "services/engine_manager.hpp"
#include "services/state_manager.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::services {

  LED led_for_screen(ScreenEnum screen)
  {
    switch (screen) {
      case ScreenEnum::sends: return LED(Key::sends);
      case ScreenEnum::routing: return LED(Key::routing);
      case ScreenEnum::fx1: return LED(Key::fx1);
      case ScreenEnum::fx1_selector: return LED(Key::fx1);
      case ScreenEnum::fx2: return LED(Key::fx2);
      case ScreenEnum::fx2_selector: return LED(Key::fx2);
      case ScreenEnum::looper: return LED(Key::looper);
      case ScreenEnum::arp: return LED(Key::arp);
      case ScreenEnum::arp_selector: return LED(Key::arp);
      case ScreenEnum::voices: return LED(Key::envelope);
      case ScreenEnum::master: return LED(Key::master);
      case ScreenEnum::sequencer: return LED(Key::sequencer);
      case ScreenEnum::sampler: return LED(Key::sampler);
      case ScreenEnum::synth: return LED(Key::synth);
      case ScreenEnum::synth_selector: return LED(Key::synth);
      case ScreenEnum::envelope: return LED(Key::envelope);
      case ScreenEnum::settings: return LED(Key::settings);
      case ScreenEnum::external: return LED(Key::external);
      case ScreenEnum::twist1: return LED(Key::twist1);
      case ScreenEnum::twist2: return LED(Key::twist2);
    }
  }

  using namespace core::ui;
  void UIManager::display(ScreenEnum screen)
  {
    auto new_state = state_;
    new_state.current_screen = screen;
    display(screen_selectors_[screen]());
    set_state(new_state);
  }

  void UIManager::set_state(State state)
  {
    Controller::current().set_color(led_for_screen(state_.current_screen), LEDColor::Black);
    state_ = state;
    Controller::current().set_color(led_for_screen(state_.current_screen), LEDColor::White);
  }

  UIManager::UIManager()
  {
    auto load = [this](const nlohmann::json& j) {
      if (j.is_object()) {
        j.at("current_screen").get_to(state_.current_screen);
        j.at("active_channel").get_to(state_.active_channel);
      }
      display(state_.current_screen);
    };

    auto save = [this] {
      return nlohmann::json::object(
        {{"current_screen", state_.current_screen}, {"active_channel", state_.active_channel}});
    };

    Application::current().state_manager->attach("UI", load, save);
  }

  void UIManager::display(Screen& screen)
  {
    cur_screen->on_hide();
    cur_screen = &screen;
    cur_screen->on_show();
  }

  core::ui::Screen& UIManager::current_screen()
  {
    return *cur_screen;
  }

  void UIManager::register_screen_selector(ScreenEnum se, ScreenSelector ss)
  {
    screen_selectors_[se] = ss;
  }

  void UIManager::draw_frame(vg::Canvas& ctx)
  {
    ctx.lineWidth(6);
    ctx.lineCap(vg::Canvas::LineCap::ROUND);
    ctx.lineJoin(vg::Canvas::Canvas::LineJoin::ROUND);
    ctx.group([&] { cur_screen->draw(ctx); });

    ctx.group([&] {
      ctx.beginPath();
      ctx.fillStyle(vg::Colours::White);
      ctx.font(vg::Fonts::Norm, 12);
      std::string cpu_time = fmt::format("{}%", int(100 * Application::current().audio_manager->cpu_time()));
      ctx.fillText(cpu_time, {290, 230});
    });

    Controller::current().flush_leds();
    _frame_count++;
  }

} // namespace otto::services
