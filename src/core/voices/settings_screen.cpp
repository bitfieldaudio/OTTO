#include "voice_manager.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::core::voices {

  struct SettingsScreen : ui::Screen {
    SettingsScreen(details::SettingsProps& props) : props(props) {}

    bool keypress(ui::Key) override;
    void draw(ui::vg::Canvas&) override;
    void rotary(ui::RotaryEvent ev) override;

    details::SettingsProps& props;
  };

  namespace details {
    std::unique_ptr<ui::Screen> make_settings_screen(SettingsProps& props)
    {
      return std::make_unique<SettingsScreen>(props);
    }
  } // namespace details

  using namespace ui;
  using namespace ui::vg;

  bool SettingsScreen::keypress(ui::Key key)
  {
    switch (key) {
      case ui::Key::oct_up: props.octave.step(1); break;
      case ui::Key::oct_down: props.octave.step(-1); break;
      default: return false; ;
    }
    return true;
  }

  void SettingsScreen::rotary(ui::RotaryEvent ev)
  {
    switch (ev.rotary) {
    case Rotary::blue: props.play_mode.step(ev.clicks); break;
    case Rotary::green: props.portamento.step(ev.clicks); break;
    case Rotary::yellow: props.octave.step(ev.clicks); break;
    case Rotary::red: props.transpose.step(ev.clicks); break;
    }
  }

  void SettingsScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("play mode", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(to_string(props.play_mode), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("portamento", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:3.2}", props.portamento), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("octave", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:+}", props.octave), {width - x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("transpose", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:+}", props.transpose), {width - x_pad, y_pad + 3 * space});
  }

} // namespace otto::core::voices
