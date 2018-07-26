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
      case PlayMode::poly: return "Poly";
      case PlayMode::mono: return "Mono";
      case PlayMode::unison: return "Unison";
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

  static void draw_bg(Canvas& ctx);
  static void draw_x_arrow(Canvas& ctx, Colour c, float pos);
  static void draw_y_arrow(Canvas& ctx, Colour c, float pos);

  void EnvelopeScreen::draw(Canvas& ctx)
  {
    const float a = props.attack.normalize() / 4.f;
    const float d = props.decay.normalize() / 4.f + a;
    const float s = props.sustain.normalize();
    const float r = (props.release.normalize() + 3.f) / 4.f;
    draw_bg(ctx);
    draw_x_arrow(ctx, Colours::Blue, a);
    draw_x_arrow(ctx, Colours::Green, d);
    draw_y_arrow(ctx, Colours::Yellow, s);
    draw_x_arrow(ctx, Colours::Red, r);

    ctx.beginPath();
    ctx.moveTo(45.9,                       188.7);
    ctx.lineTo(45.9 + a * 240.f,           188.7 - 137.f);
    ctx.lineTo(45.9 + d * 240.f,           188.7 - s * 137.f);
    ctx.lineTo(45.9 + (3.f / 4.f) * 240.f, 188.7 - s * 137.f);
    ctx.lineTo(45.9 + r * 240.f,           188.7);
    ctx.lineWidth(2.f);
    ctx.stroke(Colours::White);
  }

  static void draw_x_arrow(Canvas& ctx, Colour c, float pos)
  {
    ctx.save();
    ctx.translate(pos * 240.f, 0.f);
    ctx.beginPath();
    ctx.moveTo(49.9, 206.6);
    ctx.lineTo(45.9, 199.7);
    ctx.lineTo(41.9, 206.6);
    ctx.lineTo(44.9, 206.6);
    ctx.lineTo(44.9, 211.2);
    ctx.bezierCurveTo(44.9, 211.8, 45.4, 212.2, 45.9, 212.2);
    ctx.bezierCurveTo(46.5, 212.2, 46.9, 211.8, 46.9, 211.2);
    ctx.lineTo(46.9, 206.6);
    ctx.lineTo(49.9, 206.6);
    ctx.closePath();
    ctx.fill(c);
    ctx.restore();
  }

  static void draw_y_arrow(Canvas& ctx, Colour c, float pos)
  {
    ctx.save();
    ctx.translate(0.f, -pos * 137.f);
    ctx.beginPath();
    ctx.moveTo(36.3, 188.7);
    ctx.lineTo(29.4, 184.7);
    ctx.lineTo(29.4, 187.7);
    ctx.lineTo(23.8, 187.7);
    ctx.bezierCurveTo(23.3, 187.7, 22.8, 188.2, 22.8, 188.7);
    ctx.bezierCurveTo(22.8, 189.3, 23.3, 189.7, 23.8, 189.7);
    ctx.lineTo(29.4, 189.7);
    ctx.lineTo(29.4, 192.7);
    ctx.lineTo(36.3, 188.7);
    ctx.closePath();
    ctx.fill(c);
    ctx.restore();
  }

  static void draw_bg(Canvas& ctx)
  {
    // Laag1/linegroup2/end
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(48.8, 51.7);
    ctx.lineTo(42.3, 51.7);
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(61, 63, 65));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // Laag1/linegroup2/6
    ctx.beginPath();
    ctx.moveTo(45.8, 71.7);
    ctx.lineTo(42.3, 71.7);
    ctx.stroke();

    // Laag1/linegroup2/5
    ctx.beginPath();
    ctx.moveTo(45.8, 92.1);
    ctx.lineTo(42.3, 92.1);
    ctx.stroke();

    // Laag1/linegroup2/4
    ctx.beginPath();
    ctx.moveTo(45.8, 111.7);
    ctx.lineTo(42.3, 111.7);
    ctx.stroke();

    // Laag1/linegroup2/3
    ctx.beginPath();
    ctx.moveTo(45.8, 131.7);
    ctx.lineTo(42.3, 131.7);
    ctx.stroke();

    // Laag1/linegroup2/2
    ctx.beginPath();
    ctx.moveTo(45.8, 151.7);
    ctx.lineTo(42.3, 151.7);
    ctx.stroke();

    // Laag1/linegroup2/1
    ctx.beginPath();
    ctx.moveTo(45.8, 171.7);
    ctx.lineTo(42.3, 171.7);
    ctx.stroke();

    // Laag1/linegroup
    ctx.restore();

    // Laag1/linegroup/end
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(285.5, 193.7);
    ctx.lineTo(285.5, 184.2);
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(61, 63, 65));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // Laag1/linegroup/11
    ctx.beginPath();
    ctx.moveTo(265.5, 193.7);
    ctx.lineTo(265.5, 189.2);
    ctx.stroke();

    // Laag1/linegroup/10
    ctx.beginPath();
    ctx.moveTo(245.5, 193.7);
    ctx.lineTo(245.5, 189.2);
    ctx.stroke();

    // Laag1/linegroup/9
    ctx.beginPath();
    ctx.moveTo(225.5, 193.7);
    ctx.lineTo(225.5, 189.2);
    ctx.stroke();

    // Laag1/linegroup/8
    ctx.beginPath();
    ctx.moveTo(205.5, 193.7);
    ctx.lineTo(205.5, 189.2);
    ctx.stroke();

    // Laag1/linegroup/7
    ctx.beginPath();
    ctx.moveTo(185.5, 193.7);
    ctx.lineTo(185.5, 189.2);
    ctx.stroke();

    // Laag1/linegroup/6
    ctx.beginPath();
    ctx.moveTo(165.5, 193.7);
    ctx.lineTo(165.5, 189.2);
    ctx.stroke();

    // Laag1/linegroup/5
    ctx.beginPath();
    ctx.moveTo(145.5, 193.7);
    ctx.lineTo(145.5, 189.2);
    ctx.stroke();

    // Laag1/linegroup/4
    ctx.beginPath();
    ctx.moveTo(125.5, 193.7);
    ctx.lineTo(125.5, 189.2);
    ctx.stroke();

    // Laag1/linegroup/3
    ctx.beginPath();
    ctx.moveTo(105.5, 193.7);
    ctx.lineTo(105.5, 189.2);
    ctx.stroke();

    // Laag1/linegroup/2
    ctx.beginPath();
    ctx.moveTo(85.5, 193.7);
    ctx.lineTo(85.5, 189.2);
    ctx.stroke();

    // Laag1/linegroup/1
    ctx.beginPath();
    ctx.moveTo(65.5, 193.7);
    ctx.lineTo(65.5, 189.2);
    ctx.stroke();

    // Laag1/horizontalline
    ctx.restore();
    ctx.beginPath();
    ctx.moveTo(45.9, 188.7);
    ctx.lineTo(285.5, 188.7);
    ctx.lineWidth(2.0);
    ctx.strokeStyle(Colour::bytes(61, 63, 65));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // Laag1/verticalline
    ctx.beginPath();
    ctx.moveTo(45.9, 51.7);
    ctx.lineTo(45.9, 188.7);
    ctx.stroke();
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

    ctx.font(Fonts::Bold, 40);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Play Mode", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(to_string(props.play_mode), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Portamento", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:3.2}", props.portamento), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Octave", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:+}", props.octave), {width - x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Transpose", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:+}", props.transpose), {width - x_pad, y_pad + 3 * space});
  }

} // namespace otto::core::audio
