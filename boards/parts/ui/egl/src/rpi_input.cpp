#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <string>
#include <thread>
#include <vector>

#include "services/log_manager.hpp"
#include "services/ui_manager.hpp"
#include "util/filesystem.hpp"

#include "board/ui/keys.hpp"
#include "board/ui/egl_ui_manager.hpp"

namespace otto::services {

  using namespace otto::core::ui;
  using namespace otto::board::ui;

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
      throw Application::exception(Application::ErrorCode::input_error,
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

  void EGLUIManager::read_encoders()
  {

  }

  void EGLUIManager::read_keyboard()
  {

  }
} // namespace otto::board::ui
