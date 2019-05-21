#include "controller.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"

#include "services/ui_manager.hpp"

namespace otto::services {

  using Event = Controller::Event;
  using EventBag = Controller::EventBag;

  void Controller::keypress(Key key)
  {
    events.outer().push_back(KeyPressEvent{key});
  }

  void Controller::encoder(EncoderEvent ev)
  {
    events.outer().push_back(ev);
  }

  void Controller::keyrelease(Key key)
  {
    events.outer().push_back(KeyReleaseEvent{key});
  }

  bool Controller::is_pressed(Key k) noexcept
  {
    return keys[k._to_index()];
  }

  void Controller::register_key_handler(Key k, KeyHandler press_handler, KeyHandler release_handler)
  {
    key_handlers.emplace(k, std::pair{std::move(press_handler), std::move(release_handler)});
  }

  bool Controller::handle_global(Key key, bool is_press)
  {
    auto [first, last] = key_handlers.equal_range(key);
    if (first == last) return false;

    for (auto&& [key, funcs] : util::sequence(first, last)) {
      auto& func = is_press ? funcs.first : funcs.second;
      if (func) func(key);
    }

    return true;
  }

  void Controller::flush_events()
  {
    events.swap();
    for (auto& event : events.inner()) {
      util::match(event,
                  [this](KeyPressEvent& ev) {
                    keys[ev.key._to_index()] = true;
                    if (handle_global(ev.key)) return;
                    UIManager::current().current_screen().keypress(ev.key);
                  },
                  [this](KeyReleaseEvent& ev) {
                    keys[ev.key._to_index()] = false;
                    if (handle_global(ev.key, false)) return;
                    UIManager::current().current_screen().keyrelease(ev.key);
                  },
                  [](EncoderEvent& ev) {
                    UIManager::current().current_screen().encoder(ev);
                  });
    }
  }


  // DummyController //
  struct DummyController final : Controller {
    void set_color(LED, LEDColor) override {}
    void flush_leds() override {}
    void clear_leds() override {}
  };

  std::unique_ptr<Controller> Controller::make_dummy() {
    return std::make_unique<DummyController>();
  }

} // namespace otto::services
