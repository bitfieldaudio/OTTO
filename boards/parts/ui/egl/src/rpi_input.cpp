#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <string>
#include <vector>
#include "core/globals.hpp"
#include "services/ui.hpp"
#include "util/filesystem.hpp"
#include "services/logger.hpp"

#include "board/ui/keys.hpp"

namespace otto::board::ui {

  using namespace otto::core::ui;

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
          LOGE("Couldn't open a file descriptor for {}", fullpath.string());
          return -1;
        }

        auto result = ioctl(fd, EVIOCGRAB, 1);
        if (result != 0) {
          LOGE("Couldn't get exclusive input access to {}", fullpath.string());
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
        case key_press: LOGI("Mouse button down: {}", event.code); break;

        case key_release: LOGI("Mouse button up: {}", event.code); break;
        }

      case EV_REL:
        switch (event.code) {
        case 0: LOGI("Mouse moved left/right: {}", event.value); break;

        case 1: LOGI("Mouse moved left/right: {}", event.value); break;
        }

      case EV_ABS:
        LOGI("Mouse absolute event: {}, {}", event.code, event.value);
        break;
      }
    }
  }

  void read_keyboard()
  {
    static Modifiers left;
    static Modifiers right;
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
          case KEY_LEFTCTRL:   left.set(Modifier::ctrl,   pressed); break;
          case KEY_RIGHTCTRL:  right.set(Modifier::ctrl,  pressed); break;
          case KEY_LEFTALT:    left.set(Modifier::alt,    pressed); break;
          case KEY_RIGHTALT:   right.set(Modifier::alt,   pressed); break;
          case KEY_LEFTSHIFT:  left.set(Modifier::shift,  pressed); break;
          case KEY_RIGHTSHIFT: right.set(Modifier::shift, pressed); break;
          case KEY_LEFTMETA:   left.set(Modifier::super,  pressed); break;
          case KEY_RIGHTMETA:  right.set(Modifier::super, pressed); break;
        }

        Action action = [event] {
          switch (event.value) {
          case key_release: return Action::release;
          case key_press: return Action::press;
          case key_repeat: return Action::repeat;
          }
        }();

        handle_keyevent(action, left | right, board::ui::Key(event.code));
      }
    }
  }
} // namespace otto::ui
