#if OTTO_UI_EGL

#include <fcntl.h>
#include <linux/input.h>
#include <string>
#include <vector>
#include "core/globals.hpp"
#include "core/ui/mainui.hpp"
#include "filesystem.hpp"
#include "services/logger.hpp"

namespace otto::ui {
  static auto constexpr key_release = 0;
  static auto constexpr key_press   = 1;
  static auto constexpr key_repeat  = 2;

  // This is the number of events to read from keyboard/mouse input at one time.
  static auto constexpr event_buffer_size = 64;

  namespace fs = otto::filesystem;

  static bool ends_with(const std::string& s, const std::string& suffix)
  {
    return s.rfind(suffix) == (s.size() - suffix.size());
  }

  static int open_device(const std::string& device_type)
  {
    auto path = fs::path("/dev/input/by-id");

    for (const auto& entry : fs::directory_iterator(path)) {
      auto file = entry.path().string();
      if (ends_with(file, device_type)) {
        auto fullpath = path / file;
        auto fd       = open(fullpath.c_str(), O_RDONLY | O_NONBLOCK);
        if (fd < 0) {
          LOGE << "Couldn't open a file descriptor for " << fullpath.string();
          return -1;
        }

        auto result = ioctl(fd, EVIOCGRAB, 1);
        if (result != 0) {
          LOGE << "Couldn't get exclusive input access to "
               << fullpath.string();
          return -1;
        }

        return fd;
      }
    }

    return -1;
  }

  std::vector<input_event> read_events(int device)
  {
    struct input_event events[event_buffer_size];
    int rd = read(device, events, sizeof(events));
    if (rd <= 0) {
      return std::vector<input_event>();
    }

    int count = rd / sizeof(struct input_event);
    return std::vector<input_event>(events, events + count);
  }

  void read_mouse()
  {
    static int mouse = open_device("event-mouse");

    if (mouse == -1) {
      throw global::exception(global::ErrorCode::input_error,
                              "Could not find a mouse or touchscreen!");
    }

    auto events = read_events(mouse);
    for (const auto& event : events) {
      switch (event.type) {
      case EV_KEY:
        switch (event.value) {
        case key_press: LOGI << "Mouse button down: " << event.code; break;

        case key_release: LOGI << "Mouse button up: " << event.code; break;
        }

      case EV_REL:
        switch (event.code) {
        case 0: LOGI << "Mouse moved left/right: " << event.value; break;

        case 1: LOGI << "Mouse moved left/right: " << event.value; break;
        }

      case EV_ABS:
        LOGI << "Mouse absolute event: " << event.code << ", " << event.value;
        break;
      }
    }
  }

  static Key translate_key(int key_code, bool ctrl)
  {
    switch (key_code) {
    // Rotaries
    case KEY_Q: return ctrl ? Key::blue_click : Key::blue_up;
    case KEY_A: return ctrl ? Key::blue_click : Key::blue_down;
    case KEY_W: return ctrl ? Key::green_click : Key::green_up;
    case KEY_S: return ctrl ? Key::green_click : Key::green_down;
    case KEY_E: return ctrl ? Key::white_click : Key::white_up;
    case KEY_D: return ctrl ? Key::white_click : Key::white_down;
    case KEY_R: return ctrl ? Key::red_click : Key::red_up;
    case KEY_F: return ctrl ? Key::red_click : Key::red_down;

    case KEY_LEFT: return Key::left;
    case KEY_RIGHT:
      return Key::right;

    // Tapedeck
    case KEY_SPACE: return Key::play;
    case KEY_Z: return Key::rec;
    case KEY_F1: return Key::track_1;
    case KEY_F2: return Key::track_2;
    case KEY_F3: return Key::track_3;
    case KEY_F4:
      return Key::track_4;

    // Numbers
    case KEY_T:
      if (ctrl) {
        return Key::tape;
      }
      break;
    case KEY_Y:
      if (ctrl) {
        return Key::mixer;
      }
      break;
    case KEY_U:
      if (ctrl) {
        return Key::synth;
      }
      break;
    case KEY_G:
      if (ctrl) {
        return Key::metronome;
      }
      break;
    case KEY_H:
      if (ctrl) {
        return Key::sampler;
      }
      break;
    case KEY_J:
      if (ctrl) {
        return Key::drums;
      }
      break;
    case KEY_K:
      if (ctrl) {
        return Key::envelope;
      }
      break;

    case KEY_L: return Key::loop;
    case KEY_I: return Key::loop_in;
    case KEY_O: return Key::loop_out;

    case KEY_X: return Key::cut;
    case KEY_C:
      if (ctrl) {
        return Key::lift;
      }
      break;

    case KEY_V:
      if (ctrl) {
        return Key::drop;
      }
      break;

    case KEY_LEFTSHIFT:
    case KEY_RIGHTSHIFT: return Key::shift;

    case KEY_ESC: return Key::quit;
    }

    return Key::none;
  }

  void read_keyboard()
  {
    static bool leftCtrl  = false;
    static bool rightCtrl = false;
    static int keyboard   = open_device("event-kbd");
    if (keyboard == -1) {
      throw global::exception(global::ErrorCode::input_error,
                              "Could not find a keyboard!");
    }

    auto events = read_events(keyboard);
    for (const auto& event : events) {
      if (event.type == EV_KEY) {
        auto pressed = event.value != 0;

        switch (event.code) {
        case KEY_LEFTCTRL: leftCtrl = pressed; break;

        case KEY_RIGHTCTRL: rightCtrl = pressed;
        }

        Key k = translate_key(event.code, leftCtrl || rightCtrl);
        switch (event.value) {
        case key_release: impl::keyrelease(k); break;

        case key_press: impl::keypress(k); break;

        case key_repeat:
          switch (k) {
          case Key::red_up:
          case Key::red_down:
          case Key::blue_up:
          case Key::blue_down:
          case Key::white_up:
          case Key::white_down:
          case Key::green_up:
          case Key::green_down:
          case Key::left:
          case Key::right: impl::keypress(k); break;

          default: break;
          }
          break;
        }
      }
    }
  }
} // namespace otto::ui

#endif // OTTO_UI_EGL
