#pragma once

#include "core/ui/base.hpp"

namespace top1::ui {

  class MainUI : public Screen {

    static void mainRoutine();

    bool globKeyPre(Key key);
    bool globKeyPost(Key key);

  public:

    ui::PressedKeys keys;

    MainUI() :
      currentScreen (new DefaultScreen){}

    MainUI(MainUI&) = delete;
    MainUI(MainUI&&) = delete;

    void init() override;
    void exit() override;

    Screen::ptr currentScreen;

    std::thread uiThread;

    void display(Screen::ptr screen);

    void draw(drawing::Canvas& ctx) override;
    bool keypress(Key key) override;
    bool keyrelease(Key key) override;
  };

} // top1::ui
