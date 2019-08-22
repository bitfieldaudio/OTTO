#include "voice_manager.hpp"

#include "core/ui/vector_graphics.hpp"
#include "util/string_conversions.hpp"

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
    return false;
  }

  void SettingsScreen::encoder(ui::EncoderEvent ev)
  {
    using details::PlayMode;
    switch (ev.encoder) {
    case Encoder::blue: props.play_mode.step(ev.steps); break;
    case Encoder::green: {
      switch (props.play_mode.get()) {
        case PlayMode::poly: props.rand.step(ev.steps); break;
        case PlayMode::mono: props.sub.step(ev.steps); break;
        case PlayMode::unison: props.detune.step(ev.steps); break;
        case PlayMode::interval: props.interval.step(util::math::sgn(ev.steps)); break;
      }; break;
    }
    case Encoder::yellow: props.portamento.step(ev.steps); break;
    case Encoder::red: {
      // Fuck it. I can do binary logic myself.
      if (ev.steps > 0) props.legato = props.legato != props.retrig;
      else props.legato = props.legato == props.retrig;
      props.retrig = !props.retrig;
      break;
    }
    }
  }

  void SettingsScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;
    using details::PlayMode;

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float y_shift = -12;
    constexpr float space = (height - 2.f * y_pad) / 3.f;
    constexpr float green_x = width - 2.5f * x_pad;

    ctx.font(Fonts::Norm, 60);
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Bottom);
    ctx.fillText(util::to_string(props.play_mode.get()).data(), {3.5f * x_pad, y_pad + 0.6f * space + y_shift});

    ctx.font(Fonts::Norm, 35);
    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);
    ctx.fillText(aux_setting(props.play_mode), {green_x, y_pad - 0.2 * space + y_shift});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Bottom);
    switch (props.play_mode.get()) {
      case PlayMode::poly: {
        ctx.fillText(fmt::format("{:3.2}", props.rand), {green_x, y_pad + 0.8f * space + y_shift});
        break;
      }
      case PlayMode::mono: {
        ctx.fillText(fmt::format("{:3.2}", props.sub), {green_x, y_pad + 0.8f * space + y_shift});
        break;
      }
      case PlayMode::unison: {
        ctx.fillText(fmt::format("{:3.2}", props.detune), {green_x, y_pad + 0.8f * space + y_shift});
        break;
      }
      case PlayMode::interval: {
        ctx.fillText(fmt::format("{:+}", props.interval), {green_x, y_pad + 0.8f * space + y_shift});
        break;
      }
    };

    //------------------------------//
    // Portamento
    ctx.globalCompositeOperation(CompositeOperation::XOR);
    //Background. Note, colour doesn't matter for this,
    //it is only to get the logic to work
    ctx.beginPath();
    ctx.fillStyle(Colours::Gray50);
    ctx.roundedRect({x_pad, y_pad + space + y_shift}, {width - 2 * x_pad, space}, 10);
    ctx.fill();

    // Fill
    constexpr float fudge = 3.f;
    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.roundedRect({x_pad + fudge, y_pad + space + y_shift}, {(width - 2 * x_pad - fudge) * props.portamento, space}, 10);
    ctx.fill();

    // Text
    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);
    ctx.fillText("portamento", {width * 0.5, y_pad + 1.5 * space + y_shift});

    ctx.globalCompositeOperation(CompositeOperation::SOURCE_OVER);

    // Rectangle
    ctx.beginPath();
    ctx.strokeStyle(Colours::Yellow);
    ctx.roundedRect({x_pad, y_pad + space + y_shift}, {width - 2 * x_pad, space}, 10);
    ctx.stroke();

    //--------------------------//
    // Legato settings
    constexpr float top_part_length = 70;
    ctx.beginPath();
    ctx.strokeStyle(Colours::Red);
    ctx.moveTo(x_pad, y_pad + 2.5 * space + 0.5 * y_shift);
    ctx.lineTo(x_pad + top_part_length, y_pad + 2.5 * space + 0.5 * y_shift);
    ctx.moveTo(width - x_pad, y_pad + 2.5 * space + 0.5 * y_shift);
    ctx.lineTo(width - x_pad - top_part_length, y_pad + 2.5 * space + 0.5 * y_shift);
    ctx.moveTo(x_pad, y_pad + 3.5 * space);
    ctx.lineTo(width - x_pad, y_pad + 3.5 * space);
    ctx.stroke();

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);
    ctx.fillText("legato", {width * 0.5, y_pad + 2.5 * space + 0.5 * y_shift});

    ctx.beginPath();
    if (props.legato) ctx.fillStyle(Colours::Red);
    else ctx.fillStyle(Colours::Gray50);
    ctx.font(30);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("envelope", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    if (props.retrig) ctx.fillStyle(Colours::Red);
    else ctx.fillStyle(Colours::Gray50);
    ctx.font(30);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText("portamento", {width - x_pad, y_pad + 3 * space});
  }

} // namespace otto::core::voices
