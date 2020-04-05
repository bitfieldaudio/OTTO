#include "ui_manager.hpp"

#include "core/ui/vector_graphics.hpp"
#include "services/audio_manager.hpp"
#include "services/controller.hpp"
#include "services/engine_manager.hpp"
#include "services/state_manager.hpp"

namespace otto::services {

  using otto::core::input::Key;

  LED led_for_screen(ScreenEnum screen)
  {
    switch (screen) {
      case ScreenEnum::sends: return LED(otto::core::input::Key::sends);
      case ScreenEnum::routing: return LED(otto::core::input::Key::routing);
      case ScreenEnum::fx1: return LED(otto::core::input::Key::fx1);
      case ScreenEnum::fx1_selector: return LED(otto::core::input::Key::fx1);
      case ScreenEnum::fx2: return LED(otto::core::input::Key::fx2);
      case ScreenEnum::fx2_selector: return LED(otto::core::input::Key::fx2);
      case ScreenEnum::looper: return LED(otto::core::input::Key::looper);
      case ScreenEnum::arp: return LED(otto::core::input::Key::arp);
      case ScreenEnum::arp_selector: return LED(otto::core::input::Key::arp);
      case ScreenEnum::voices: return LED(otto::core::input::Key::envelope);
      case ScreenEnum::master: return LED(otto::core::input::Key::master);
      case ScreenEnum::sequencer: return LED(otto::core::input::Key::sequencer);
      case ScreenEnum::sampler: return LED(otto::core::input::Key::sampler);
      case ScreenEnum::sampler_envelope: return LED(otto::core::input::Key::envelope);
      case ScreenEnum::synth: return LED(otto::core::input::Key::synth);
      case ScreenEnum::synth_selector: return LED(otto::core::input::Key::synth);
      case ScreenEnum::synth_envelope: return LED(otto::core::input::Key::envelope);
      case ScreenEnum::settings: return LED(otto::core::input::Key::settings);
      case ScreenEnum::external: return LED(otto::core::input::Key::external);
      case ScreenEnum::twist1: return LED(otto::core::input::Key::twist1);
      case ScreenEnum::twist2: return LED(otto::core::input::Key::twist2);
      case ScreenEnum::saveslots: return LED(otto::core::input::Key::slots);
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
    state.current_screen.observe(this, [&](auto new_val) {
      if (!screen_selectors_[new_val]) return;
      display(screen_selectors_[new_val]());
      for (auto scrn : ScreenEnum::_values()) {
        if (scrn != new_val) Controller::current().set_color(led_for_screen(scrn), LEDColor::Black);
      }
      Controller::current().set_color(led_for_screen(new_val), LEDColor::White);
      DLOGI("Select screen {}", new_val._to_string());
      key_mode_for(new_val).map([&](auto&& km) { state.key_mode.set(km); });
    });

    state.active_channel.observe_no_imidiate_call(this, [this, old_chan = state.active_channel.get()](auto new_chan) mutable {
      if (new_chan == old_chan) return;
      old_chan = new_chan;
      state.current_screen = state.current_screen.get();
    });

    state.octave.observe_no_imidiate_call(this, [&](auto octave) {
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

    Application::current().events.post_init.connect([this] {
      Controller::current().register_key_handler(Key::plus, [this] { state.octave.step(1); });
      Controller::current().register_key_handler(Key::minus, [this] { state.octave.step(-1); });
    });

    auto load = [this](const nlohmann::json& j) { util::deserialize(state, j); };
    auto save = [this] { return util::serialize(state); };

    Application::current().state_manager->attach("UI", load, save);
  }

  void UIManager::display(ScreenAndInput sai)
  {
    cur_sai.screen().on_hide();
    cur_sai = sai;
    cur_sai.screen().on_show();
  }

  core::ui::Screen& UIManager::current_screen()
  {
    return cur_sai.screen();
  }

  core::input::InputHandler& UIManager::current_input_handler()
  {
    return cur_sai.input();
  }

  void UIManager::register_screen_selector(ScreenEnum se, ScreenSelector ss)
  {
    screen_selectors_[se] = ss;
  }

  void UIManager::draw_frame(vg::Canvas& ctx)
  {
    action_queue_.pop_call_all();
    ctx.lineWidth(6);
    ctx.lineCap(vg::LineCap::ROUND);
    ctx.lineJoin(vg::LineJoin::ROUND);
    ctx.group([&] {
      ctx.clip(0, 0, 320, 240);
      current_screen().draw(ctx);

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
    vg::timeline().step(chrono::duration_cast<chrono::milliseconds>(now - last_frame).count());
    last_frame = now;
  }

  void UIManager::register_screen_key(core::input::Key key, ScreenEnum se)
  {
    Controller::current().register_key_handler(
      key,
      [this, se] {
        reset_timer();
        display(se);
      },
      [this] {
        if (timer_done()) {
          display(pop_back());
        } else {
          push_back(state.current_screen);
        }
      });
  }
  void UIManager::register_screen_key(core::input::Key key, ScreenEnum s, ScreenEnum sm, core::input::Key modifier)
  {
    Controller::current().register_key_handler(
      key,
      [this, s, sm, modifier] {
        reset_timer();
        if (Controller::current().is_pressed(modifier)) {
          display(sm);
        } else {
          display(s);
        }
      },
      [this] {
        if (timer_done()) {
          display(pop_back());
        } else {
          push_back(state.current_screen);
        }
      });
  }

  ScreenEnum UIManager::pop_back()
  {
    return screen_stack;
  }
  void UIManager::push_back(ScreenEnum se)
  {
    screen_stack = se;
  }

  void UIManager::reset_timer()
  {
    press_time = chrono::clock::now();
  }

  bool UIManager::timer_done()
  {
    return (chrono::clock::now() - press_time) > peek_time;
  }

} // namespace otto::services
