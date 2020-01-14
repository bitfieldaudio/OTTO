#pragma once

#include <array>
#include <better_enum.hpp>
#include <cstdint>
#include <foonathan/array/flat_map.hpp>
#include <variant>
#include <vector>

#include "core/input.hpp"
#include "core/service.hpp"
#include "itc/action_sender.hpp"
#include "services/application.hpp"
#include "util/locked.hpp"
#include "util/thread.hpp"

namespace otto::board::ui {
  enum struct Action;
  struct Modifiers;
  enum struct Key;
  void handle_keyevent(board::ui::Action, board::ui::Modifiers, board::ui::Key);
} // namespace otto::board::ui

namespace otto::services {
  struct LED {
    LED(core::input::Key k) : key(k) {}

    core::input::Key key;
  };

  struct LEDColor {
    LEDColor() = default;
    LEDColor(std::uint32_t rgb) : r((rgb >> 16) & 0xFF), g((rgb >> 8) & 0xFF), b(rgb & 0xFF) {}
    LEDColor(std::uint8_t r, std::uint8_t g, std::uint8_t b) : r(r), g(g), b(b) {}

    std::uint8_t r = 0, g = 0, b = 0;

    LEDColor mix(LEDColor o, float f = 0.5) const noexcept
    {
      return (*this * (1.f - f)) + o * f;
    }

    LEDColor dim(float f = 0.5) const noexcept
    {
      return mix(0x000000, f);
    }

    LEDColor brighten(float f = 0.5) const noexcept
    {
      return mix(0xFFFFFF, f);
    }

    LEDColor operator*(float f) const noexcept
    {
      return {static_cast<std::uint8_t>(r * f), static_cast<std::uint8_t>(g * f), static_cast<std::uint8_t>(b * f)};
    }
    LEDColor operator/(float f) const noexcept
    {
      return {static_cast<std::uint8_t>(r / f), static_cast<std::uint8_t>(g / f), static_cast<std::uint8_t>(b / f)};
    }
    LEDColor operator+(LEDColor o) const noexcept
    {
      return {static_cast<std::uint8_t>(r + o.r), static_cast<std::uint8_t>(g + o.g),
              static_cast<std::uint8_t>(b + o.b)};
    }

    static const LEDColor Black;
    static const LEDColor White;
    static const LEDColor Blue;
    static const LEDColor Green;
    static const LEDColor Yellow;
    static const LEDColor Red;
  };

  // Definitions have to be outside struct
  inline const LEDColor LEDColor::Black = 0x000000;
  inline const LEDColor LEDColor::White = 0xFFFFFF;
  inline const LEDColor LEDColor::Blue = 0x0000FF;
  inline const LEDColor LEDColor::Green = 0x00FF00;
  inline const LEDColor LEDColor::Yellow = 0x888800;
  inline const LEDColor LEDColor::Red = 0xFF0000;

  struct Controller : core::Service, core::input::InputHandler {
    using Key = core::input::Key;
    using EncoderEvent = core::input::EncoderEvent;
    using KeyPressEvent = core::input::KeyPressEvent;
    using KeyReleaseEvent = core::input::KeyReleaseEvent;
    /// Function type for key handlers
    using KeyHandler = std::function<void(Key k)>;

    using Event = std::variant<EncoderEvent, KeyPressEvent, KeyReleaseEvent>;
    using EventBag = std::vector<Event>;

    Controller();

    static std::unique_ptr<Controller> make_dummy();
    static Controller& current() noexcept
    {
      return Application::current().controller;
    }

    virtual void set_color(LED, LEDColor) = 0;
    virtual void flush_leds() = 0;
    virtual void clear_leds() = 0;


    /// Check if a key is currently pressed.
    bool is_pressed(Key k) noexcept;

    /// Register a key handler
    void register_key_handler(Key k, KeyHandler press_handler, KeyHandler release_handler = nullptr);

    struct Signals {
      util::Signal<Event> on_input;
    } signals;

  protected:
    /// Dispatches to the event handler for the current screen, and handles
    /// global keys.
    ///
    /// Can be executed from a separate thread
    bool keypress(Key key) override;

    /// Dispatches to the event handler for the current screen, and handles
    /// global keys.
    ///
    /// Can be executed from a separate thread, but must be the same thread as keypress
    bool keyrelease(Key key) override;

    /// Send encoder event
    ///
    /// Can be executed from a separate thread
    void encoder(EncoderEvent ev) override;

    /// Temporary solution
    ///
    /// @TODO replace with something cleaner
    friend void ::otto::board::ui::handle_keyevent(board::ui::Action, board::ui::Modifiers, board::ui::Key);

  private:
    bool handle_global(Key key, bool is_press = true);

    template<typename... Receivers>
    friend struct ControllerSender;

    foonathan::array::flat_map<Key, std::pair<KeyHandler, KeyHandler>> key_handlers;
    std::array<bool, Key::_size()> keys;
    util::double_buffered<EventBag> events_;
    itc::ActionQueue action_queue_;

    /// Essentially the logic thread, since most logic will happen in key handlers and property change events
    util::triggered_thread key_handler_thread;
  };

  /// Sends actions on the logic thread
  template<typename... Receivers>
  struct ControllerSender : itc::ActionSender<Receivers...> {
    template<typename Tag, typename Type, typename... Mixins>
    using Prop = typename itc::ActionSender<Receivers...>::template Prop<Tag, Type, Mixins...>;
    ControllerSender(Receivers&... r) noexcept
      : itc::ActionSender<Receivers...>(Controller::current().action_queue_, r...)
    {}

    /// Push an action to be received by all receivers that support it
    template<typename Tag, typename... Args>
    void push(itc::ActionData<itc::Action<Tag, Args...>> action_data)
    {
      itc::ActionSender<Receivers...>::push(std::move(action_data));
      Controller::current().key_handler_thread.trigger();
    }
  };
} // namespace otto::services
