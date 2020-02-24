#include "wifi_selector_screen.hpp"

#include <nanorange.hpp>

#include "core/ui/vector_graphics.hpp"

namespace otto::board::wifi {

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

  void WriterUI::clear() noexcept
  {
    *this = WriterUI();
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

  // NetworkSelectorScreen

  using Subscreen = WFSSSubscreen;

  void placeholder_network_icon(core::ui::IconData& i, nvg::Canvas& ctx)
  {
    ctx.beginPath();
    ctx.roundedRect({0, 0}, i.size, i.size.min() / 4.f);
    ctx.stroke(i.color, i.line_width);
    ctx.beginPath();
    ctx.circle(i.size.center(), i.size.min() / 4.f);
    ctx.fill(i.color);
  }

  using namespace core::input;

  void NetworkSelectorScreen::action(EncoderAction, EncoderEvent e)
  {
    if (current_screen == +Subscreen::network_selection) {
      switch (e.encoder) {
        case Encoder::blue: {
          selected_network_ += e.steps;
          // Vertical scroll
          core::ui::vg::timeline().apply(&network_scroll_).then<ch::RampTo>(selected_network_, 500, ch::EaseOutExpo());
          // Reset horizontal scroll
          core::ui::vg::timeline()
            .apply(&network_scroll_horizontal_)
            .then<ch::Hold>(0.f, 1000)
            .then<ch::RampTo>(1.f, 1000)
            .then<ch::Hold>(1.f, 1000)
            .finishFn([& m = *network_scroll_horizontal_.inputPtr()] { m.resetTime(); });
          break;
        }
        default: break;
      }
    } else if (current_screen == +Subscreen::password) {
      switch (e.encoder) {
        case Encoder::blue: password_writer.cycle_char(e.steps); break;
        case Encoder::green: password_writer.cycle_group(e.steps); break;
        case Encoder::yellow: password_writer.step_idx(e.steps); break;
        case Encoder::red:
          if (e.steps < 0) navigate_to(Subscreen::network_selection);
          if (e.steps > 0) {
            // Try to connect?
            // Perhaps sanitize password string - remove trailing spaces, etc.
          }
          break;
        default: break;
      }
    }
  }

  void NetworkSelectorScreen::action(KeyPressAction, Key key)
  {
    switch (key) {
      case Key::blue_click: navigate_to(Subscreen::password); break;
      default: break;
    }
  }

  void NetworkSelectorScreen::navigate_to(Subscreen screen)
  {
    current_screen = screen;
    core::ui::vg::timeline().apply(&page_flip_).then<ch::RampTo>(screen._to_integral(), 500, ch::EaseOutExpo());
  }

  core::ui::Icon NetworkSelectorScreen::strength_icons(int s)
  {
    return core::ui::Icon{placeholder_network_icon};
  }

  void NetworkSelectorScreen::draw(nvg::Canvas& ctx)
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

    const float password_page_pos = (1 - page_flip_) * vg::width;

    if (page_flip_ < 1) {
      ctx.group([&] {
        const Color text_color = deselected_col.dim(page_flip_);

        float first_name_y = -line_height * (network_scroll_ - 2);

        ctx.beginPath();
        ctx.font(Fonts::LightItalic, font_size);
        ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Baseline);
        ctx.fillStyle(text_color.dim(0.5));
        ctx.fillText("Wi-Fi Networks", {left_pad, first_name_y - left_pad});

        auto draw_names = [&](Color text_color, bool scroll) {
          float y = first_name_y;
          for (auto&& [i, network] : util::view::indexed(networks)) {
            auto icon = strength_icons(network.strength);
            icon.set_size({icon_size, icon_size});
            icon.set_color(text_color);
            icon.set_line_width(4.f);
            ctx.drawAt({left_pad, y + (line_height - icon_size) / 2.f}, icon);
            ctx.beginPath();
            auto font = Fonts::Norm;
            ctx.font(font, font_size);
            ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Baseline);
            ctx.fillStyle(text_color);
            float x_pos_start = left_pad + icon_size + icon_pad;
            float x_pos_scrolled = x_pos_start - std::max(0.f, x_pos_start + ctx.measureText(network.name) + left_pad - vg::width) * network_scroll_horizontal_ * scroll;
            ctx.save();
            ctx.clip(x_pos_start, 0, vg::width - x_pos_start - left_pad, vg::height);
            ctx.fillText(network.name, {x_pos_scrolled, y + (line_height + icon_size) / 2.f + 2});
            ctx.restore();
            y += line_height;
          }
        };
        draw_names(text_color, false);
        ctx.group([&] {
          ctx.clip(0, line_height * 2.f, 320, line_height);
          ctx.beginPath();
          ctx.rect({0, line_height * 2.f}, {320, line_height});
          ctx.fill(Colors::Blue);
          draw_names(Colors::Black, true);
        });
      });
    }

    if (page_flip_ > 0) {
      ctx.group([&] {
        ctx.translate(password_page_pos, 0);
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
        ctx.fillText("Password", {left_pad, text_y - left_pad});

        ctx.beginPath();
        ctx.font(Fonts::Norm, font_size);
        ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Baseline);
        const auto password_str = password_writer.to_string(false);
        const auto cursor_pos = password_writer.cursor();
        auto cursor_left = ctx.measureText(password_str.substr(0, cursor_pos));
        auto cursor_right = ctx.measureText(password_str.substr(0, cursor_pos + 1));

        ctx.fillStyle(Colors::Black);
        ctx.fillText(password_str, {left_pad, text_y + (line_height + icon_size) / 2.f + 2});

        ctx.group([&] {
          ctx.clip(left_pad + cursor_left, line_height * 2.f, cursor_right - cursor_left, line_height);
          ctx.beginPath();
          ctx.rect({0, 0}, {320, 240});
          ctx.fill(Colors::Yellow);

          ctx.fillStyle(Colors::Black);
          ctx.fillText(password_str, {left_pad, text_y + (line_height + icon_size) / 2.f + 2});
        });

        ctx.group([&] {
          constexpr float w = (320 - 2 * left_pad) / 26;
          constexpr float h = (240 - 3 * line_height - 2 * left_pad) / 3;

          ctx.translate(left_pad, line_height * 3.f + left_pad);

          ctx.font(Fonts::Norm, 20);
          ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);

          const char cur_char = password_str.at(cursor_pos);


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
} // namespace otto::board::wifi
