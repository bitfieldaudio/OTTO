#include "core/ui/vector_graphics.hpp"
#include "util/string_conversions.hpp"
#include "voices_ui.hpp"

namespace otto::core::voices {

  using namespace ui;
  using namespace ui::vg;

  static std::string aux_setting(PlayMode pm) noexcept
  {
    switch (pm) {
      case PlayMode::poly: return "rand";
      case PlayMode::mono: return "sub";
      case PlayMode::unison: return "detune";
      case PlayMode::interval: return "interv.";
    };
    return "";
  }

  void SettingsScreen::action(portamento_tag::action, float portamento) noexcept
  {
    this->portamento = portamento;
  }
  void SettingsScreen::action(legato_tag::action, bool legato) noexcept
  {
    this->legato = legato;
  }
  void SettingsScreen::action(retrig_tag::action, bool retrig) noexcept
  {
    this->retrig = retrig;
  }
  void SettingsScreen::action(play_mode_tag::action, PlayMode play_mode) noexcept
  {
    this->play_mode = play_mode;
    play_mode_str = play_mode._to_string();
    aux_name = aux_setting(play_mode);
  }
  void SettingsScreen::action(rand_tag::action, float rand) noexcept
  {
    if (play_mode == +PlayMode::poly) aux_value = fmt::format("{:3.2}", rand);
  }
  void SettingsScreen::action(sub_tag::action, float sub) noexcept
  {
    if (play_mode == +PlayMode::mono) aux_value = fmt::format("{:3.2}", sub);
  }
  void SettingsScreen::action(detune_tag::action, float detune) noexcept
  {
    if (play_mode == +PlayMode::unison) aux_value = fmt::format("{:3.2}", detune);
  }
  void SettingsScreen::action(interval_tag::action, int interval) noexcept
  {
    if (play_mode == +PlayMode::unison) aux_value = fmt::format("{:+}", interval);
  }

  void SettingsScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float y_shift = -12;
    constexpr float space = (height - 2.f * y_pad) / 3.f;
    constexpr float green_x = width - 2.5f * x_pad;

    ctx.font(Fonts::Norm, 60);
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Bottom);
    ctx.fillText(play_mode_str, {3.5f * x_pad, y_pad + 0.6f * space + y_shift});

    ctx.font(Fonts::Norm, 35);
    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);
    ctx.fillText(aux_name, {green_x, y_pad - 0.2 * space + y_shift});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Bottom);
    ctx.fillText(aux_value, {green_x, y_pad + 0.8f * space + y_shift});

    //------------------------------//
    // Portamento
    ctx.globalCompositeOperation(CompositeOperation::XOR);
    // Background. Note, colour doesn't matter for this,
    // it is only to get the logic to work
    ctx.beginPath();
    ctx.fillStyle(Colours::Gray50);
    ctx.roundedRect({x_pad, y_pad + space + y_shift}, {width - 2 * x_pad, space}, 10);
    ctx.fill();

    // Fill
    constexpr float fudge = 3.f;
    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.roundedRect({x_pad + fudge, y_pad + space + y_shift}, {(width - 2 * x_pad - fudge) * portamento, space}, 10);
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
    ctx.fillStyle(legato ? Colours::Red : Colours::Gray50);
    ctx.font(30);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("envelope", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(retrig ? Colours::Red : Colours::Gray50);
    ctx.font(30);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText("portamento", {width - x_pad, y_pad + 3 * space});
  }

} // namespace otto::core::voices
