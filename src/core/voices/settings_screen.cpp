#include "voice_manager.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::core::voices {

  struct SettingsScreen : ui::Screen {
    SettingsScreen(details::SettingsProps& props) : props(props) {}

    bool keypress(ui::Key) override;
    void draw(ui::vg::Canvas&) override;
    void encoder(ui::EncoderEvent ev) override;

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
      case ui::Key::plus: props.octave.step(1); break;
      case ui::Key::minus: props.octave.step(-1); break;
      case ui::Key::blue_click: props.legato = !props.legato;
      case ui::Key::yellow_click: props.retrig = !props.retrig;
      default: return false; ;
    }
    return true;
  }

  void SettingsScreen::encoder(ui::EncoderEvent ev)
  {
    using details::PlayMode;
    switch (ev.encoder) {
    case Encoder::blue: props.play_mode.step(ev.steps); break;
    case Encoder::green: {
      switch (props.play_mode) {
        case PlayMode::poly: props.drift.step(ev.steps);
        case PlayMode::mono: props.sub.step(ev.steps);
        case PlayMode::unison: props.detune.step(ev.steps);
        case PlayMode::interval: props.interval.step(util::math::sgn(ev.steps));
      };
    }
    case Encoder::yellow: props.portamento.step(ev.steps); break;
    case Encoder::red: props.transpose.step(ev.steps); break;
    }
  }

  void SettingsScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    using details::PlayMode;

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
    ctx.fillText(aux_setting(props.play_mode), {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    switch (props.play_mode) {
      case PlayMode::poly:
        ctx.fillText(fmt::format("{:3.2}", props.drift), {width - x_pad, y_pad + space});
      case PlayMode::mono:
        ctx.fillText(fmt::format("{:3.2}", props.sub), {width - x_pad, y_pad + space});
      case PlayMode::unison:
        ctx.fillText(fmt::format("{:3.2}", props.detune), {width - x_pad, y_pad + space});
      case PlayMode::interval:
        ctx.fillText(fmt::format("{}", props.interval), {width - x_pad, y_pad + space});
    };

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("portamento", {x_pad, y_pad + 2 * space});

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
