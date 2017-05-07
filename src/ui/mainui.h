#pragma once

#include "base.h"

class MainUI : public ui::Screen {

  MainUI() :
    currentScreen (new ui::DefaultScreen){}

  static void mainRoutine();

  bool globKeyPre(ui::Key key);
  bool globKeyPost(ui::Key key);

public:

  ui::Screen *currentScreen;

  std::thread uiThread;

  void draw(NanoCanvas::Canvas& ctx) override;
  bool keypress(ui::Key key, bool shift) override;
  bool keyrelease(ui::Key key, bool shift) override;

  static void init();

  static MainUI& getInstance() {
    static MainUI instance;
    return instance;
  }
};
