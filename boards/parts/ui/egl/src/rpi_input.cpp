#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <string>
#include <thread>
#include <vector>

#include "core/globals.hpp"
#include "services/logger.hpp"
#include "services/ui.hpp"
#include "util/filesystem.hpp"

#include "board/ui/keys.hpp"

namespace otto::board::ui {

  using namespace otto::core::ui;

  static auto constexpr key_release = 0;
  static auto constexpr key_press = 1;
  static auto constexpr key_repeat = 2;

  // This is the number of events to read from keyboard/mouse input at one time.
  static auto constexpr event_buffer_size = 64;

  namespace fs = otto::filesystem;

  static bool ends_with(const std::string& s, const std::string& suffix)
  {
    return s.rfind(suffix) == (s.size() - suffix.size());
  }

  static int open_device(const std::string& device_type, bool block = false)
  {
    auto path = fs::path("/dev/input/by-id");

    for (const auto& entry : fs::directory_iterator(path)) {
      auto file = entry.path().string();
      if (ends_with(file, device_type)) {
        auto fullpath = path / file;
        auto fd = open(fullpath.c_str(), O_RDONLY | (block ? 0 : O_NONBLOCK));
        LOGI("Opening device {}", fullpath);
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

      case EV_ABS: LOGI("Mouse absolute event: {}, {}", event.code, event.value); break;
      }
    }
  }

  void read_encoders()
  {
    auto file = fopen("/dev/ttyACM0", "r");
    if (file == nullptr) {
      LOGW("Encoder device not found (expected /dev/ttyACM0). Continuing without it");
      return;
    }

    char* line = nullptr;
    std::size_t len;
    std::size_t read;

    while (global::running()) {
      read = getline(&line, &len, file);
      if (len >= 2) {
        if (line[1] == 'P') {
          switch (line[0]) {
          case 'B': service::ui::impl::keypress(core::ui::Key::blue_click); break;
          case 'G': service::ui::impl::keypress(core::ui::Key::green_click); break;
          case 'Y': service::ui::impl::keypress(core::ui::Key::white_click); break;
          case 'R': service::ui::impl::keypress(core::ui::Key::red_click); break;
          default: break;
          }
          continue;
        }
        RotaryEvent rot;
        switch (line[0]) {
        case 'B': rot.rotary = Rotary::Blue; break;
        case 'G': rot.rotary = Rotary::Green; break;
        case 'Y': rot.rotary = Rotary::White; break;
        case 'R': rot.rotary = Rotary::Red; break;
        default: rot.rotary = Rotary{-1};
        }
        if (rot.rotary == Rotary{-1}) continue;
        char* end = line + len;
        rot.clicks = std::strtol(line + 1, &end, 10);
        service::ui::impl::rotary(rot);
      }
    }
  }

  void read_keyboard()
  {
    Modifiers left;
    Modifiers right;
    int keyboard = [] {
      int dev = open_device("0-event-kbd", true);
      if (dev < 0) dev = open_device("event-kbd", true);
      return dev;
    }();
    std::thread encoder_thread = std::thread{[] { read_encoders(); }};

    if (keyboard == -1) {
      throw global::exception(global::ErrorCode::input_error, "Could not find a keyboard!");
    }

    while (global::running()) {
      auto events = read_events(keyboard);
      for (const auto& event : events) {
        if (event.type == EV_KEY) {
          auto pressed = event.value != 0;

          switch (event.code) {
          case KEY_LEFTCTRL: left.set(Modifier::ctrl, pressed); break;
          case KEY_RIGHTCTRL: right.set(Modifier::ctrl, pressed); break;
          case KEY_LEFTALT: left.set(Modifier::alt, pressed); break;
          case KEY_RIGHTALT: right.set(Modifier::alt, pressed); break;
          case KEY_LEFTSHIFT: left.set(Modifier::shift, pressed); break;
          case KEY_RIGHTSHIFT: right.set(Modifier::shift, pressed); break;
          case KEY_LEFTMETA: left.set(Modifier::super, pressed); break;
          case KEY_RIGHTMETA: right.set(Modifier::super, pressed); break;
          }

          Action action = [event] {
            switch (event.value) {
            case key_release: return Action::release;
            case key_press: return Action::press;
            case key_repeat: return Action::repeat;
            default: return Action{-1};
            }
          }();

          handle_keyevent(action, left | right, board::ui::Key(event.code));
        }
      }
    }
  }
} // namespace otto::board::ui
