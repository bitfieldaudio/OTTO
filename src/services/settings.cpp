#include "settings.hpp"

#include "core/ui/vector_graphics.hpp"
#include "services/controller.hpp"
#include "services/ui_manager.hpp"

namespace otto::services {

  using namespace core;
  using namespace core::input;
  using namespace core::ui;
  using namespace core::ui::vg;
  using Screen = Settings::Screen;
  using Menu = Settings::Menu;
  // using Page = Menu::Page;

  // void Page::draw(Canvas& ctx)
  // {
  //   ctx.font(Fonts::Bold, 30);
  //   ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Top);
  //   ctx.fillStyle(Colors::White);
  //   ctx.fillText("Test 1", {0, 0});
  // }

  struct Settings::Screen : ui::Screen {
    Screen();

    // void encoder(EncoderEvent) override;
    void draw(ui::vg::Canvas& ctx) override;

    void scroll_to(int i);

    // Page& cur_page(int offset = 0);

    ch::Output<float> scroll_position = 0;
  };

  Settings::Settings() : screen_(std::make_unique<Screen>())
  {
    // UIManager::current().register_screen_selector(
    //   ScreenEnum::settings, [this]() -> auto& { return *screen_; });

    Controller::current().register_key_handler(Key::settings,
                                               [] { UIManager::current().display(ScreenEnum::settings); });
  }

  Settings::Screen::Screen()
  {
    // menus.push_back(std::make_unique<SettingsMenu>([](Canvas& ctx) {
    //   ctx.font(Fonts::Bold, 30);
    //   ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Top);
    //   ctx.fillStyle(Colors::White);
    //   ctx.fillText("Test 1", {0, 0});
    // }));
    // menus.push_back(std::make_unique<SettingsMenu>([](Canvas& ctx) {
    //   ctx.font(Fonts::Bold, 30);
    //   ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Top);
    //   ctx.fillStyle(Colors::White);
    //   ctx.fillText("Test 2", {0, 0});
    // }));
    // menus.push_back(std::make_unique<SettingsMenu>([](Canvas& ctx) {
    //   ctx.font(Fonts::Bold, 30);
    //   ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Top);
    //   ctx.fillStyle(Colors::White);
    //   ctx.fillText("Test 3", {0, 0});
    // }));
  }

  void Settings::Screen::scroll_to(int i)
  {
    timeline().apply(&scroll_position).then<ch::RampTo>(i, 250);
  }

  // Page& Settings::Screen::cur_page(int offset)
  // {
  // return *menus[util::math::modulo(int(scroll_position + offset), menus.size())];
  // }

  // void Settings::Screen::encoder(EncoderEvent evt)
  // {
  //   // scroll_to(util::math::modulo(int(scroll_position + evt.steps), menus.size()));
  // }

  void Settings::Screen::draw(Canvas& ctx)
  {
    // auto p = Point{20, 20};
    // const auto m_width = 280;
    const auto sp = scroll_position - int(scroll_position);

    if (sp != 0) {
      ctx.group([&] {
        ctx.globalAlpha(1 - sp);
        // ctx.drawAt(p + Point{(0 - sp) * m_width, 0}, cur_menu(0));
        ctx.globalAlpha(sp);
        // ctx.drawAt(p + Point{(1 - sp) * m_width, 0}, cur_menu(1));
      });
    } else {
      // ctx.drawAt(p, cur_menu());
    }

    ctx.beginPath();
    ctx.moveTo(20, 200);
    ctx.lineTo(300, 200);
    ctx.stroke(Colours::Gray60);

    // auto width = 280 / float(menus.size());
    // auto start = width * scroll_position;

    ctx.beginPath();
    // ctx.moveTo(20 + start, 200);
    // ctx.lineTo(20 + start + width, 200);
    ctx.stroke(DefaultColors::White);
  }

} // namespace otto::services
