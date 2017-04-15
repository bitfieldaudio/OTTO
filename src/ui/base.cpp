#include "base.h"
#include "utils.h"
#include "../globals.h"

#include <gtkmm/drawingarea.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>

#include <thread>

// GTK wrapper. I want to keep gtk as far away from everything as possible,
// since i probably want to avoid using it in the end.
// Also this will help possibly adding graphical controls for testing
class MainGTKView : public Gtk::DrawingArea {
public:
  MainGTKView() {
    this->set_size_request(MainUI::WIDTH, MainUI::HEIGHT);
  };
  virtual ~MainGTKView() {};
protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override {
    return MainUI::getInstance().draw(cr);
  }
};

void MainUI::mainRoutine() {
  auto app = Gtk::Application::create("TOP-1");

  Gtk::Window win;
  win.set_title("TOP-1");
  win.set_default_size(WIDTH, HEIGHT);
  win.set_resizable(false);

  MainGTKView main;
  win.add(main);
  main.show();

  app->run(win);
}

void MainUI::init() {
  auto& self = getInstance();

  self.uiThread = std::thread(MainUI::mainRoutine);
  self.uiThread.join();
}

bool MainUI::draw(const Cairo::RefPtr<Cairo::Context>& cr) {
  using namespace drawing;

  cr->rectangle(0, 0, WIDTH, HEIGHT);
  cr->set_source(COLOUR_BLACK);
  cr->fill();
  return getInstance().currentScreen->draw(cr);
}

bool DefaultScreen::draw(const ContextPtr& cr) {
  using namespace drawing;

  auto text1 = Pango::Layout::create(cr);
  text1->set_text("TOP-1");
  text1->set_font_description(font1);
  int tw1, th1;
  text1->get_pixel_size(tw1, th1);

  auto text2 = Pango::Layout::create(cr);
  text2->set_text("Totally Original Project");
  text2->set_font_description(font2);
  int tw2, th2;
  text2->get_pixel_size(tw2, th2);

  cr->set_source(COLOUR_WHITE);

  cr->move_to((WIDTH - tw1) / 2, (HEIGHT - th1 - th2) / 2);
  text1->show_in_cairo_context(cr);

  cr->move_to((WIDTH - tw2) / 2, (HEIGHT - th2 + th1) / 2);
  text2->show_in_cairo_context(cr);
  return true;
}
