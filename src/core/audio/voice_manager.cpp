#include "voice_manager.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::core::audio {

  struct EnvelopeScreen : ui::Screen {

    EnvelopeScreen(EnvelopeProps& props)
      : props (props)
    {}

    void draw(ui::vg::Canvas&) override;
    void rotary(ui::RotaryEvent ev) override;

    EnvelopeProps& props;
  };

  struct SettingsScreen : ui::Screen {

    SettingsScreen(SettingsProps& props)
      : props (props)
    {}

    void draw(ui::vg::Canvas&) override;
    void rotary(ui::RotaryEvent ev) override;

    SettingsProps& props;
  };

  namespace detail {
    std::unique_ptr<ui::Screen> make_envelope_screen(EnvelopeProps& props)
    {
      return std::make_unique<EnvelopeScreen>(props);
    }

    std::unique_ptr<ui::Screen> make_settings_screen(SettingsProps& props)
    {
      return std::make_unique<SettingsScreen>(props);
    }
  }

  std::string to_string(PlayMode pm) noexcept
  {
    switch (pm) {
      case PlayMode::poly: return "poly";
      case PlayMode::mono: return "mono";
      case PlayMode::unison: return "unison";
      default: return "";
    };
  }

  using namespace ui;
  using namespace ui::vg;

  // ENVELOPE SCREEN //////////////////////////////////////////////////////////

  void EnvelopeScreen::rotary(RotaryEvent ctx) {
    switch (ctx.rotary) {
    case Rotary::Blue:
      props.attack.step(ctx.clicks);
      break;
    case Rotary::Green:
      props.decay.step(ctx.clicks);
      break;
    case Rotary::White:
      props.sustain.step(ctx.clicks);
      break;
    case Rotary::Red:
      props.release.step(ctx.clicks);
      break;
    }
  }

  void EnvelopeScreen::draw(Canvas& ctx)
  {
    constexpr auto b = vg::Box{ 30.f, 60.f, 260.f, 110.f };
    const float spacing = 10.f;
    const float max_width = (b.width - 3 * spacing) / 3.f;
    const float aw = max_width * props.attack.normalize(); 
    const float dw = max_width * props.decay.normalize(); 
    const float sh = b.height * props.sustain.normalize(); 
    const float rw = max_width * props.release.normalize(); 

    ctx.lineWidth(6.f);

    const float arc_size = 0.9;

    ctx.beginPath();
    ctx.moveTo(b.x, b.y + b.height + spacing);
    ctx.lineTo(b.x + b.width, b.y + b.height + spacing);
    ctx.stroke(Colours::White);

    ctx.beginPath();
    ctx.moveTo(b.x, b.y + b.height);
    ctx.quadraticCurveTo({b.x + aw * arc_size, b.y + b.height * arc_size}, {b.x + aw, b.y}); // curve
    ctx.lineTo(b.x + aw, b.y + b.height);
    ctx.closePath();
    ctx.stroke(Colours::Blue);
    ctx.fill(Colours::Blue);

    ctx.beginPath();
    ctx.moveTo(b.x + aw + spacing, b.y + b.height);
    ctx.lineTo(b.x + aw + spacing, b.y);
    ctx.quadraticCurveTo({b.x + aw + spacing + dw * (1 - arc_size), b.y + (b.height - sh) * arc_size}, {b.x + aw + spacing + dw, b.y + b.height - sh}); // curve
    ctx.lineTo(b.x + aw + spacing + dw, b.y + b.height);
    ctx.closePath();
    ctx.stroke(Colours::Green);
    ctx.fill(Colours::Green);

    ctx.beginPath();
    ctx.moveTo(b.x + aw + spacing + dw + spacing,      b.y + b.height - sh);
    ctx.lineTo(b.x + b.width - spacing - rw, b.y + b.height - sh);
    ctx.lineTo(b.x + b.width - spacing - rw, b.y + b.height);
    ctx.lineTo(b.x + aw + spacing + dw + spacing, b.y + b.height);
    ctx.closePath();
    ctx.stroke(Colours::Yellow);
    ctx.fill(Colours::Yellow);

    ctx.beginPath();
    ctx.moveTo(b.x + b.width - rw, b.y + b.height);
    ctx.lineTo(b.x + b.width - rw, b.y + b.height - sh);
    ctx.quadraticCurveTo({b.x + b.width - rw * arc_size, b.y + b.height - sh * (1 - arc_size)}, {b.x + b.width,      b.y + b.height});
    ctx.closePath();
    ctx.stroke(Colours::Red);
    ctx.fill(Colours::Red);
  }

  // SETTINGS SCREEN //////////////////////////////////////////////////////////

  void SettingsScreen::rotary(ui::RotaryEvent ev)
  {
    switch (ev.rotary) {
      case Rotary::Blue: props.play_mode.step(ev.clicks); break;
      case Rotary::Green: props.portamento.step(ev.clicks); break;
      case Rotary::White: props.octave.step(ev.clicks); break;
      case Rotary::Red: props.transpose.step(ev.clicks); break;
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

} // namespace otto::core::audio
