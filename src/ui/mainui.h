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

  ui::ContextPtr cairo;
  Cairo::RefPtr<Cairo::Surface> surface;
  std::thread uiThread;

  bool draw(const ui::ContextPtr& cr) override;
  bool keypress(ui::Key key) override;

  static void init();

  static MainUI& getInstance() {
    static MainUI instance;
    return instance;
  }
};
