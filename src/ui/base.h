#pragma once

#include <cairomm/cairomm.h>
#include <pangomm/fontdescription.h>

#include <thread>

typedef Cairo::RefPtr<Cairo::Context> ContextPtr;

class Widget {
public:
  virtual bool draw(const ContextPtr& cr) = 0;
};

class Screen : public Widget {};

class DefaultScreen : public Screen {
  Pango::FontDescription font1;
  Pango::FontDescription font2;
public:
  DefaultScreen() :
    font1 ("Lato Light 40"),
    font2 ("Lato Light 13") {
  }
public:
  bool draw(const ContextPtr& cr) override;
};

class MainUI : public Widget {

  MainUI() :
    currentScreen (new DefaultScreen()){}

  static void mainRoutine();

public:

  const static uint WIDTH = 320;
  const static uint HEIGHT = 240;

  Screen *currentScreen;

  bool draw(const Cairo::RefPtr<Cairo::Context>& cr);

  Cairo::RefPtr<Cairo::Surface> mainSurface;
  std::thread uiThread;

  static void init();

  static MainUI& getInstance() {
    static MainUI instance;
    return instance;
  }
};
