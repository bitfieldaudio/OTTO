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
      case ScreenEnum::sampler_envelope: return LED(Key::envelope);
      case ScreenEnum::synth: return LED(Key::synth);
      case ScreenEnum::synth_selector: return LED(Key::synth);
      case ScreenEnum::synth_envelope: return LED(Key::envelope);
      case ScreenEnum::settings: return LED(Key::settings);
      case ScreenEnum::external: return LED(Key::external);
      case ScreenEnum::twist1: return LED(Key::twist1);
      case ScreenEnum::twist2: return LED(Key::twist2);
    }
    OTTO_UNREACHABLE;
  }

  tl::optional<KeyMode> key_mode_for(ScreenEnum screen)
  {
    switch (screen) {
      case ScreenEnum::arp: [[fallthrough]];
      case ScreenEnum::arp_selector: [[fallthrough]];
      case ScreenEnum::voices: [[fallthrough]];
      case ScreenEnum::synth_selector: [[fallthrough]];
      case ScreenEnum::synth_envelope: [[fallthrough]];
      case ScreenEnum::synth: return KeyMode::midi;

      case ScreenEnum::sampler: [[fallthrough]];
      case ScreenEnum::sampler_envelope: [[fallthrough]];
      case ScreenEnum::looper: [[fallthrough]];
      case ScreenEnum::sequencer: return KeyMode::seq;
      default: return tl::nullopt;
    }
  }

  using namespace core::ui;
  void UIManager::display(ScreenEnum screen)
  {
    state.current_screen = screen;
  }

  UIManager::UIManager()
  {
    state.current_screen.on_change().connect([&](auto new_val) {
      display(screen_selectors_[new_val]());
      for (auto scrn : ScreenEnum::_values()) {
        if (scrn != new_val) Controller::current().set_color(led_for_screen(scrn), LEDColor::Black);
      }
      Controller::current().set_color(led_for_screen(new_val), LEDColor::White);
      DLOGI("Select screen {}", new_val._to_string());
      key_mode_for(new_val).map([&](auto&& km) { state.key_mode.set(km); });
    });

    state.active_channel.on_change().connect([&](auto chan) { state.current_screen = state.current_screen.get(); });

    state.octave.on_change().connect([&](auto octave) {
      LEDColor c = [&] {
        switch (std::abs(octave)) {
          case 1: return LEDColor::Blue;
          case 2: return LEDColor::Green;
          case 3: return LEDColor::Yellow;
          case 4: return LEDColor::Red;
          default: return LEDColor::Black;
        };
      }();
      Controller::current().set_color(LED{Key::plus}, octave > 0 ? c : LEDColor::Black);
      Controller::current().set_color(LED{Key::minus}, octave < 0 ? c : LEDColor::Black);
    });

    Application::current().events.post_init.connect([&] {
      Controller::current().register_key_handler(Key::plus, [&](auto&&) { state.octave.step(1); });
      Controller::current().register_key_handler(Key::minus, [&](auto&&) { state.octave.step(-1); });
    });

    auto load = [this](const nlohmann::json& j) { util::deserialize(state, j); };
    auto save = [this] { return util::serialize(state); };

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
    ctx.lineCap(vg::LineCap::ROUND);
    ctx.lineJoin(vg::LineJoin::ROUND);
    ctx.group([&] {
      ctx.clip(0, 0, 320, 240);
      cur_screen->draw(ctx);

      ctx.group([&] {
        ctx.beginPath();
        ctx.fillStyle(vg::Colours::White);
        ctx.font(vg::Fonts::Norm, 12);
        std::string cpu_time = fmt::format("{}%", int(100 * Application::current().audio_manager->cpu_time()));
        ctx.fillText(cpu_time, {290, 230});
      });

      signals.on_draw.emit(ctx);
    });

    Controller::current().flush_leds();
    _frame_count++;

    auto now = chrono::clock::now();
    timeline_.step(chrono::duration_cast<chrono::milliseconds>(now - last_frame).count());
    last_frame = now;
  }

} // namespace otto::services
