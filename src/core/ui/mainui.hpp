#pragma once

#include "core/ui/base.hpp"

namespace top1::ui {

  class MainUI : public Screen {

    bool globKeyPre(Key key);
    bool globKeyPost(Key key);

  public:

    static void mainRoutine();

    ui::PressedKeys keys;
    DefaultScreen defaultScreen;

    MainUI() :
      currentScreen (&defaultScreen){}

    MainUI(MainUI&) = delete;
    MainUI(MainUI&&) = delete;

    void init() override;
    void exit() override;

    Screen* currentScreen;

    void display(Screen& screen);

    void draw(drawing::Canvas& ctx) override;
    bool keypress(Key key) override;
    bool keyrelease(Key key) override;
  };

} // top1::ui
