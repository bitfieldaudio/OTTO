#include "base.h"
#include "mainui.h"
#include "utils.h"
#include "../globals.h"

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>

#include <cairomm/xlib_surface.h>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::mutex currently_drawing;
std::condition_variable renderFrame;

static void render_routine() {
  std::unique_lock<std::mutex> lock (currently_drawing);
  MainUI& self = MainUI::getInstance();

  while(GLOB.running) {
    self.cairo->push_group();
    self.draw(self.cairo);
    self.cairo->pop_group_to_source();
    self.cairo->paint();
    self.surface->flush();
    renderFrame.wait(lock);
  }
}

static ui::Key keyboardKey(int xKey) {
  using namespace ui;
  switch (xKey) {

    // Rotaries
  case XK_q:     return K_RED_UP;
  case XK_a:     return K_RED_DOWN;
  case XK_w:     return K_BLUE_UP;
  case XK_s:     return K_BLUE_DOWN;
  case XK_e:     return K_WHITE_UP;
  case XK_d:     return K_WHITE_DOWN;
  case XK_r:     return K_GREEN_UP;
  case XK_f:     return K_GREEN_DOWN;

    // Tapedeck
  case XK_space: return K_PLAY;
  case XK_z:     return K_REC;
  case XK_F1:    return K_TRACK_1;
  case XK_F2:    return K_TRACK_2;
  case XK_F3:    return K_TRACK_3;
  case XK_F4:    return K_TRACK_4;

    // Numbers
  case XK_1:     return K_1;
  case XK_2:     return K_2;
  case XK_3:     return K_3;
  case XK_4:     return K_4;
  case XK_5:     return K_5;
  case XK_6:     return K_6;
  case XK_7:     return K_7;
  case XK_8:     return K_8;
  case XK_9:     return K_9;
  case XK_0:     return K_0;

  default:       return K_NONE;
  }
}

static void event_routine(Display *display) {
  MainUI& self = MainUI::getInstance();

  XEvent e;
  while(GLOB.running) {
    XNextEvent(display, &e);

    ui::Key key;
    switch (e.type) {
    case KeyPress:
      int keysym = XkbKeycodeToKeysym(
        display,
        e.xkey.keycode,
        0,
        e.xkey.state & ShiftMask ? 1 : 0);

      key = keyboardKey(keysym);
      if (key) self.keypress(key);
      //case ClientMessage:
      //GLOB.running = false;
    }
  }
}

void MainUI::mainRoutine() {
  auto& self = getInstance();

  XInitThreads();
  auto *display = XOpenDisplay(NULL);

  if (display == NULL) {
    fprintf(stderr, "Cannot open display\n");
    exit(1);
  }

  int screen = DefaultScreen(display);
  Window window = XCreateSimpleWindow(
    display,
    DefaultRootWindow(display),
    0, 0,
    drawing::WIDTH, drawing::HEIGHT,
    0, 0, 0);
  XSizeHints *sizeH = XAllocSizeHints();
  sizeH->flags = PSize | PMinSize | PMaxSize;
  sizeH->min_width = sizeH->max_width = drawing::WIDTH;
  sizeH->min_height = sizeH->max_height = drawing::HEIGHT;
  XSetWMNormalHints(display, window, sizeH);
  XSelectInput(display, window, KeyPressMask);
  XMapWindow(display, window);

  Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", false);
  XSetWMProtocols(display, window, &WM_DELETE_WINDOW, 1);

  self.surface = Cairo::XlibSurface::create(
    display, window, DefaultVisual(display, screen),
    drawing::WIDTH, drawing::HEIGHT);

  self.cairo = Cairo::Context::create(self.surface);

  std::thread renderThread = std::thread(render_routine);
  std::thread eventThread  = std::thread(event_routine, display);

  while (GLOB.running) {
    renderFrame.notify_all();
    std::this_thread::sleep_for(std::chrono::milliseconds(100/6));
  }

}
