#include "engine_selector_screen.hpp"

namespace otto::core::engine {

  void placeholder_engine_icon(ui::IconData& i, nvg::Canvas& ctx)
  {
    ctx.beginPath();
    ctx.roundedRect({0, 0}, i.size, i.size.min() / 4.f);
    ctx.stroke(i.color, i.line_width);
    ctx.beginPath();
    ctx.circle(i.size.center(), i.size.min() / 4.f);
    ctx.fill(i.color);
  }

  void EngineSelectorScreen::action(SelectedEngine::action, int selected)
  {
    selected_engine_ = selected;
    ui::vg::timeline().apply(&engine_scroll_).then<ch::RampTo>(selected, 500, ch::EaseOutExpo());
  }

  void EngineSelectorScreen::action(SelectedPreset::action, int selected)
  {
    selected_preset_ = selected;
    ui::vg::timeline().apply(&preset_scroll_).then<ch::RampTo>(selected, 500, ch::EaseOutExpo());
    bool is_first = selected == 0;
    if (!is_first != new_indicator_transparency_.endValue()) {
      ui::vg::timeline().apply(&new_indicator_transparency_).then<ch::RampTo>(!is_first, 500, ch::EaseOutExpo());
    }
  }

  void EngineSelectorScreen::action(CurrentScreen::action, int screen)
  {
    ui::vg::timeline().apply(&page_flip_).then<ch::RampTo>(screen, 500, ch::EaseOutExpo());
  }

  void EngineSelectorScreen::action(PublishEngineNames::action, gsl::span<const util::string_ref> names)
  {
    OTTO_ASSERT(!names.empty());
		first_engine_is_off_ = names[0] == "OFF";
    engines.clear();
    util::transform(names, std::back_inserter(engines), [](auto&& name) { return EngineSelectorData{name}; });
  }

  void EngineSelectorScreen::draw(nvg::Canvas& ctx)
  {
    using namespace core::ui;
    using namespace core::ui::vg;
    constexpr float font_size = 48;
    constexpr float line_height = 52;
    constexpr float left_pad = 13;
    constexpr float icon_size = 26;
    constexpr float icon_pad = 13;
    constexpr Color deselected_col = Colors::White.dim(0.1);

    constexpr float page_flip_limit = left_pad + icon_size + icon_pad;

    const float right_page_position = vg::width - page_flip_ * (vg::width - page_flip_limit);

    ctx.group([&] {
      const Color text_color = deselected_col.dim(page_flip_);

      ctx.clip(0, 0, right_page_position, vg::height);
      ctx.globalCompositeOperation(CompositeOperation::XOR);
      ctx.beginPath();
      ctx.rect({0, 0}, {right_page_position, 240});
      ctx.fill(Colors::Black);

      ctx.beginPath();
      ctx.rect({0, line_height * 2.f}, {320, line_height});
      ctx.fill(Colors::Blue);

      float y = -line_height * (engine_scroll_ - 2);

      ctx.beginPath();
      ctx.font(Fonts::LightItalic, font_size);
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Baseline);
      ctx.fillStyle(text_color.dim(0.5));
      ctx.fillText("Engine", {left_pad, y - left_pad});

      for (auto&& [i, engine]: util::view::indexed(engines)) {
        auto icon = engine.icon;
        icon.set_size({icon_size, icon_size});
        icon.set_color(text_color);
        icon.set_line_width(4.f);
        ctx.drawAt({left_pad, y + (line_height - icon_size) / 2.f}, icon);
        ctx.beginPath();
				auto font = (first_engine_is_off_ && i == 0) ? Fonts::NormItalic : Fonts::Norm;
        ctx.font(font, font_size);
        ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Baseline);
        ctx.fillStyle(text_color);
        ctx.fillText(engine.name, {left_pad + icon_size + icon_pad, y + (line_height + icon_size) / 2.f + 2});
        y += line_height;
      }
    });

    if (page_flip_ > 0) {
      const auto plus_fade = std::max(1 - page_flip_, new_indicator_transparency_.value());
      const auto plus_color = Colors::Red.brighten(0.1).fade(plus_fade);

      auto plus_icon = ui::Icon(ui::icons::plus_clockwise_circle_arrow, {icon_size, icon_size}, plus_color, 4.f);

      ctx.drawAt({left_pad, left_pad}, [&] {
        ctx.rotateAround({icon_size / 2, icon_size / 2}, plus_fade * M_PI);
        plus_icon.draw(ctx);
      });

      ctx.group([&] {
        const Color text_color = deselected_col.fade(1 - page_flip_);
        ctx.translate(right_page_position, 0);

        ctx.globalCompositeOperation(CompositeOperation::XOR);
        ctx.beginPath();
        ctx.rect({0, 0}, {320, 240});
        ctx.fill(Colors::Black);

        ctx.beginPath();
        ctx.rect({0, line_height * 2.f}, {320, line_height});
        ctx.fill(Colors::Green);

        float y = -line_height * (preset_scroll_ - 2);

        ctx.beginPath();
        ctx.font(Fonts::LightItalic, font_size);
        ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Baseline);
        ctx.fillStyle(text_color.dim(0.5));
        ctx.fillText("Preset", {left_pad, y - left_pad});

        for (auto&& [i, preset] : util::view::indexed(engines.at(selected_engine_).presets)) {
          const Font font = i == 0 ? Fonts::NormItalic : Fonts::Norm;
          ctx.beginPath();
          ctx.font(font, font_size);
          ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Baseline);
          ctx.fillStyle(text_color);
          ctx.fillText(preset, {left_pad, y + (line_height + icon_size) / 2.f + 2});
          y += line_height;
        }
      });
    }
  }
} // namespace otto::core::engine
