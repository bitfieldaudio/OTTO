#pragma once

#include "core/ui/base.hpp"

namespace top1::ui {

  class MainUI : public Screen {

    static void mainRoutine();

    bool globKeyPre(Key key);
    bool globKeyPost(Key key);

  public:

    ui::PressedKeys keys;
    DefaultScreen defaultScreen;

    MainUI() :
      currentScreen (&defaultScreen){}

    MainUI(MainUI&) = delete;
    MainUI(MainUI&&) = delete;

    void init() override;
    void exit() override;

    Screen* currentScreen;

    std::thread uiThread;

    void display(Screen& screen);

    void draw(drawing::Canvas& ctx) override;
    bool keypress(Key key) override;
    bool keyrelease(Key key) override;
  };

} // top1::ui
