#include "engine_selector_screen.hpp"

#include <nanorange.hpp>

namespace otto::core::engine {

  // WriterUI

  void WriterUI::step_idx(std::int8_t delta) noexcept
  {
    char_idx_ = std::clamp(char_idx_ + delta, 0, (std::int8_t) to_string(false).size() - 1);
  }

  void WriterUI::cycle_group(std::int8_t delta) noexcept
  {
    OTTO_ASSERT(char_idx_ < characters_.size());
    auto& [group, c] = characters_[char_idx_];
    group = std::clamp(group + delta, 0, (int) character_groups.size() - 1);
    c = std::clamp(c, std::int8_t(0), std::int8_t(character_groups[group].size() - 1));
  }

  void WriterUI::cycle_char(std::int8_t delta) noexcept
  {
    OTTO_ASSERT(char_idx_ < characters_.size());
    auto& [group, c] = characters_[char_idx_];
    c += delta;
    while (c >= int(character_groups[group].size())) {
      c -= character_groups[group].size();
      group++;
      group = util::math::modulo(group, character_groups.size());
    }
    while (c < 0) {
      group--;
      group = util::math::modulo(group, character_groups.size());
      c += character_groups[group].size();
    }
  }

  std::string WriterUI::to_string(bool trim) const noexcept
  {
    std::string result;
    result.resize(characters_.size(), ' ');
    nano::transform(characters_, result.begin(), [](auto pair) {
      auto&& [group, c] = pair;
      return character_groups[group][c];
    });
    if (trim) {
      result = util::trim(result);
    } else {
      result = result.substr(0, std::min(result.find_last_not_of(" ") + 3, result.size()));
    }
    return result;
  }


  // EngineSelectorScreen

  using Subscreen = ESSSubscreen;

  void placeholder_engine_icon(ui::IconData& i, nvg::Canvas& ctx)
  {
    ctx.beginPath();
    ctx.roundedRect({0, 0}, i.size, i.size.min() / 4.f);
    ctx.stroke(i.color, i.line_width);
    ctx.beginPath();
    ctx.circle(i.size.center(), i.size.min() / 4.f);
    ctx.fill(i.color);
  }

  using namespace core::input;

  void EngineSelectorScreen::action(EncoderAction, EncoderEvent e)
  {
    if (current_screen == +ESSSubscreen::engine_selection) {
      switch (e.encoder) {
        case Encoder::blue: return_channel.push(SelectedEngine::action::data(selected_engine_ + e.steps)); break;
        case Encoder::green: navigate_to(ESSSubscreen::preset_selection); break;
        default: break;
      }
    } else if (current_screen == +ESSSubscreen::preset_selection) {
      switch (e.encoder) {
        case Encoder::blue: navigate_to(ESSSubscreen::engine_selection); break;
        case Encoder::green: return_channel.push(SelectedPreset::action::data(selected_preset_ + e.steps)); break;
        case Encoder::red:
          if (e.steps > 0) navigate_to(ESSSubscreen::new_preset);
          break;
        default: break;
      }
    } else if (current_screen == +ESSSubscreen::new_preset) {
      switch (e.encoder) {
        case Encoder::blue: preset_name_writer.cycle_char(e.steps); break;
        case Encoder::green: preset_name_writer.cycle_group(e.steps); break;
        case Encoder::yellow: preset_name_writer.step_idx(e.steps); break;
        case Encoder::red:
          if (e.steps < 0) navigate_to(ESSSubscreen::preset_selection);
          break;
        default: break;
      }
    }
  }

  void EngineSelectorScreen::action(KeyPressAction, Key key)
  {
    switch (key) {
      case Key::blue_click: navigate_to(ESSSubscreen::preset_selection); break;
      default: break;
    }
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

  void EngineSelectorScreen::navigate_to(Subscreen screen)
  {
    current_screen = screen;
    ui::vg::timeline().apply(&page_flip_).then<ch::RampTo>(screen._to_integral(), 500, ch::EaseOutExpo());
  }

  void EngineSelectorScreen::action(PublishEngineData::action, EngineSelectorData data)
  {
    auto found = nano::find_if(engines, [&](auto&& e) { return e.name == data.name; });
    if (found == engines.end()) {
      engines.emplace_back(std::move(data));
    } else {
      *found = data;
    }
    first_engine_is_off_ = engines[0].name == "OFF";
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

    const float preset_page_pos = vg::width - std::min(page_flip_.value(), 1.f) * (vg::width - page_flip_limit) -
                                  std::max(0.f, page_flip_ - 1) * page_flip_limit;
    const float new_preset_page_pos = (1 - std::max(0.f, page_flip_ - 1)) * vg::width;

    if (page_flip_ < 2) {
      ctx.group([&] {
        const Color text_color = deselected_col.dim(page_flip_);

        float first_name_y = -line_height * (engine_scroll_ - 2);

        ctx.beginPath();
        ctx.font(Fonts::LightItalic, font_size);
        ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Baseline);
        ctx.fillStyle(text_color.dim(0.5));
        ctx.fillText("Engine", {left_pad, first_name_y - left_pad});

        auto draw_names = [&](Color text_color) {
          float y = first_name_y;
          for (auto&& [i, engine] : util::view::indexed(engines)) {
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
        };
        draw_names(text_color);
        ctx.group([&] {
          ctx.clip(0, line_height * 2.f, 320, line_height);
          ctx.beginPath();
          ctx.rect({0, line_height * 2.f}, {320, line_height});
          ctx.fill(Colors::Blue);
          draw_names(Colors::Black);
        });
      });
    }

    if (page_flip_ > 0 && page_flip_ < 2) {
      const auto plus_fade = std::max(1 - page_flip_, new_indicator_transparency_.value());
      const auto plus_color = Colors::Red.brighten(0.1).fade(plus_fade);

      auto plus_icon = ui::Icon(ui::icons::plus_clockwise_circle_arrow, {icon_size, icon_size}, plus_color, 4.f);

      ctx.group([&] {
        ctx.translate(preset_page_pos, 0);

        ctx.beginPath();
        ctx.rect({0, 0}, {320, 240});
        ctx.fill(Colors::Black);

        ctx.drawAt({left_pad - preset_page_pos, left_pad}, [&] {
          ctx.rotateAround({icon_size / 2, icon_size / 2}, plus_fade * M_PI);
          plus_icon.draw(ctx);
        });

        ctx.beginPath();
        ctx.rect({0, line_height * 2.f}, {320, line_height});
        ctx.fill(Colors::Green);

        const float first_name_y = -line_height * (preset_scroll_ - 2);
        const Color text_color = deselected_col.fade(1 - page_flip_);

        ctx.beginPath();
        ctx.font(Fonts::LightItalic, font_size);
        ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Baseline);
        ctx.fillStyle(text_color.dim(0.5));
        ctx.fillText("Preset", {left_pad, first_name_y - left_pad});

        auto draw_names = [&](Color text_color) {
          float y = first_name_y;
          for (auto&& [i, preset] : util::view::indexed(engines.at(selected_engine_).presets)) {
            const Font font = i == 0 ? Fonts::NormItalic : Fonts::Norm;
            ctx.beginPath();
            ctx.font(font, font_size);
            ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Baseline);
            ctx.fillStyle(text_color);
            ctx.fillText(preset, {left_pad, y + (line_height + icon_size) / 2.f + 2});
            y += line_height;
          }
        };

        draw_names(text_color);
        ctx.group([&] {
          ctx.clip(0, line_height * 2.f, 320, line_height);
          ctx.beginPath();
          ctx.rect({0, line_height * 2.f}, {320, line_height});
          ctx.fill(Colors::Green);

          draw_names(Colors::Black);
        });
      });
    }

    if (page_flip_ > 1) {
      ctx.group([&] {
        ctx.translate(new_preset_page_pos, 0);
        ctx.beginPath();
        ctx.rect({0, 0}, {320, 240});
        ctx.fill(Colors::Black);

        ctx.beginPath();
        ctx.rect({0, line_height * 2.f}, {320, line_height});
        ctx.fill(Colors::White);

        constexpr float text_y = line_height * 2.f;

        ctx.beginPath();
        ctx.font(Fonts::LightItalic, font_size);
        ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Baseline);
        ctx.fillStyle(deselected_col.dim(0.5));
        ctx.fillText("New Preset", {left_pad, text_y - left_pad});

        ctx.beginPath();
        ctx.font(Fonts::Norm, font_size);
        ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Baseline);
        const auto new_preset_name = preset_name_writer.to_string();
        const auto cursor_pos = preset_name_writer.cursor();
        auto cursor_left = ctx.measureText(new_preset_name.substr(0, cursor_pos));
        auto cursor_right = ctx.measureText(new_preset_name.substr(0, cursor_pos + 1));

        ctx.fillStyle(Colors::Black);
        ctx.fillText(new_preset_name, {left_pad, text_y + (line_height + icon_size) / 2.f + 2});

        ctx.group([&] {
          ctx.clip(left_pad + cursor_left, line_height * 2.f, cursor_right - cursor_left, line_height);
          ctx.beginPath();
          ctx.rect({0, 0}, {320, 240});
          ctx.fill(Colors::Yellow);

          ctx.fillStyle(Colors::Black);
          ctx.fillText(new_preset_name, {left_pad, text_y + (line_height + icon_size) / 2.f + 2});
        });

        ctx.group([&] {
          constexpr float w = (320 - 2 * left_pad) / 26;
          constexpr float h = (240 - 3 * line_height - 2 * left_pad) / 3;

          ctx.translate(left_pad, line_height * 3.f + left_pad);

          ctx.font(Fonts::Norm, 20);
          ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);

          const char cur_char = new_preset_name.at(cursor_pos);

          for (const auto& [y, group] : util::view::indexed(WriterUI::character_groups)) {
            for (const auto& [x, c] : util::view::indexed(group)) {
              std::string s;
              s.push_back(c);
              const Point center = Point(x * w + 1, y * h) + Vec2(w, h) / 2.f;
              if (c == cur_char) {
                ctx.beginPath();
                ctx.rect(x * w, y * h, w, h);
                ctx.fill(Colors::Blue);
                ctx.beginPath();
                ctx.fillStyle(Colors::Black);
                ctx.fillText(s, center);
              } else {
                ctx.beginPath();
                ctx.fillStyle(deselected_col.dim(0.5));
                ctx.fillText(s, center);
              }
            }
          }
        });
      });
    }
  }
} // namespace otto::core::engine
