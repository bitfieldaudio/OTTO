#include "settings.hpp"

#include "services/ui_manager.hpp"
#include "services/controller.hpp"
#include "core/ui/vector_graphics.hpp"

namespace otto::services {

  using namespace core;
  using namespace ui;
  using namespace ui::vg;

  struct SettingsMenu : Drawable {
    template<typename Func>
    SettingsMenu(Func&& f) : draw_(std::forward<Func>(f)) {};

    void draw(Canvas& ctx) override {
      if (draw_) draw_(ctx);
    }

    std::function<void(Canvas&)> draw_;
  };

  struct Settings::Screen : ui::Screen {

    Screen();

    void encoder(EncoderEvent) override;
    void draw(ui::vg::Canvas& ctx) override;

    void scroll_to(int i);

    SettingsMenu& cur_menu(int offset = 0);

    ch::Output<float> scroll_position = 0;
    std::vector<std::unique_ptr<SettingsMenu>> menus;
  };

  Settings::Settings() : screen_(std::make_unique<Screen>()) {
    UIManager::current().register_screen_selector(ScreenEnum::settings, [this] () -> auto& {
      return *screen_;
    });

    Controller::current().register_key_handler(Key::settings, [] (auto) {
      UIManager::current().display(ScreenEnum::settings);
    });

  }

  Settings::Screen::Screen() {
    menus.push_back(std::make_unique<SettingsMenu>([] (Canvas& ctx) {
      ctx.font(Fonts::Bold, 30);
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Top);
      ctx.fillStyle(Colors::White);
      ctx.fillText("Test 1", {0,0});
    }));
    menus.push_back(std::make_unique<SettingsMenu>([] (Canvas& ctx) {
      ctx.font(Fonts::Bold, 30);
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Top);
      ctx.fillStyle(Colors::White);
      ctx.fillText("Test 2", {0,0});
    }));
    menus.push_back(std::make_unique<SettingsMenu>([] (Canvas& ctx) {
      ctx.font(Fonts::Bold, 30);
      ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Top);
      ctx.fillStyle(Colors::White);
      ctx.fillText("Test 3", {0,0});
    }));
  }

  void Settings::Screen::scroll_to(int i) {
    UIManager::current().timeline().apply(&scroll_position).then<ch::RampTo>(i, 250);
  }

  SettingsMenu& Settings::Screen::cur_menu(int offset) {
    auto n = menus.size();
    return *menus[(((int(scroll_position) + offset) % n + n) % n)];
  }

  void Settings::Screen::encoder(EncoderEvent evt) {
    auto n = menus.size();
    scroll_to((((int(scroll_position) + evt.steps) % n) + n) % n);
  }

  void Settings::Screen::draw(Canvas& ctx) {

    auto p = Point{20, 20};
    const auto m_width = 280;
    const auto sp = scroll_position - int(scroll_position);

    if (sp != 0) {
      ctx.group([&] {
        ctx.globalAlpha(1 - sp);
        ctx.drawAt(p + Point{(0 - sp) * m_width, 0}, cur_menu(0));
        ctx.globalAlpha(sp);
        ctx.drawAt(p + Point{(1 - sp) * m_width, 0}, cur_menu(1));
      });
    } else {
      ctx.drawAt(p, cur_menu());
    }

    ctx.beginPath();
    ctx.moveTo(20, 200);
    ctx.lineTo(300, 200);
    ctx.stroke(Colours::Gray60);

    auto width = 280 / float(menus.size());
    auto start = width * scroll_position;

    ctx.beginPath();
    ctx.moveTo(20 + start, 200);
    ctx.lineTo(20 + start + width, 200);
    ctx.stroke(Colors::White);
  }

} // namespace otto::services
