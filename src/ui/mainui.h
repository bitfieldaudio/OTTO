#pragma once

#include "base.h"

class MainUI : public ui::Screen {

  static void mainRoutine();

  bool globKeyPre(ui::Key key);
  bool globKeyPost(ui::Key key);

public:

  MainUI() :
    currentScreen (new ui::DefaultScreen){}

  MainUI(MainUI&) = delete;
  MainUI(MainUI&&) = delete;

  void init();
  void exit();

  ui::Screen *currentScreen;

  std::thread uiThread;

  void display(ui::Screen *screen);

  void draw(NanoCanvas::Canvas& ctx) override;
  bool keypress(ui::Key key, bool shift) override;
  bool keyrelease(ui::Key key, bool shift) override;
};
