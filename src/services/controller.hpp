#pragma once

#include <array>
#include <better_enum.hpp>
#include <cstdint>
#include <foonathan/array/flat_map.hpp>
#include <vector>

#include "util/locked.hpp"
#include "util/variant.hpp"

#include "core/service.hpp"
#include "services/application.hpp"

namespace otto::board::ui {
  enum struct Action;
  struct Modifiers;
  enum struct Key;
  void handle_keyevent(board::ui::Action, board::ui::Modifiers, board::ui::Key);
} // namespace otto::board::ui

namespace otto::services {

  BETTER_ENUM(FuncKey,
              std::uint8_t,
              master = 0,
              plus = 1,
              minus = 2,
              sends = 3,
              routing = 4,
              rec = 5,
              fx1 = 6,
              fx2 = 7,
              play = 8,
              looper = 9,
              sequencer = 10,
              sampler = 11,
              settings = 12,
              arp = 13,
              synth = 14,
              envelope = 15,
              external = 16,
              shift = 17,
              slots = 18,
              twist1 = 19,
              twist2 = 20)

  BETTER_ENUM(Encoder, std::uint8_t, blue = 0, green = 1, yellow = 2, red = 3)

  BETTER_ENUM(ChannelKey,
              std::uint8_t,
              N0 = 0,
              N1 = 1,
              N2 = 2,
              N3 = 3,
              N4 = 4,
              N5 = 5,
              N6 = 6,
              N7 = 7,
              N8 = 8,
              N9 = 9)

  BETTER_ENUM(SeqKey,
              std::uint8_t,
              N0 = 0,
              N1 = 1,
              N2 = 2,
              N3 = 3,
              N4 = 4,
              N5 = 5,
              N6 = 6,
              N7 = 7,
              N8 = 8,
              N9 = 9,
              N10 = 10,
              N11 = 11,
              N12 = 12,
              N13 = 13,
              N14 = 14,
              N15 = 15)

  BETTER_ENUM(Key,
              std::uint8_t,
              blue_click = Encoder::blue,
              green_click = Encoder::green,
              yellow_click = Encoder::yellow,
              red_click = Encoder::red,

              master = (1 << 6) | FuncKey::master,
              plus = (1 << 6) | FuncKey::plus,
              minus = (1 << 6) | FuncKey::minus,
              sends = (1 << 6) | FuncKey::sends,
              routing = (1 << 6) | FuncKey::routing,
              rec = (1 << 6) | FuncKey::rec,
              fx1 = (1 << 6) | FuncKey::fx1,
              fx2 = (1 << 6) | FuncKey::fx2,
              play = (1 << 6) | FuncKey::play,
              looper = (1 << 6) | FuncKey::looper,
              sequencer = (1 << 6) | FuncKey::sequencer,
              sampler = (1 << 6) | FuncKey::sampler,
              settings = (1 << 6) | FuncKey::settings,
              arp = (1 << 6) | FuncKey::arp,
              synth = (1 << 6) | FuncKey::synth,
              envelope = (1 << 6) | FuncKey::envelope,
              external = (1 << 6) | FuncKey::external,
              shift = (1 << 6) | FuncKey::shift,
              slots = (1 << 6) | FuncKey::slots,
              twist1 = (1 << 6) | FuncKey::twist1,
              twist2 = (1 << 6) | FuncKey::twist2,

              C0 = (2 << 6) | ChannelKey::N0,
              C1 = (2 << 6) | ChannelKey::N1,
              C2 = (2 << 6) | ChannelKey::N2,
              C3 = (2 << 6) | ChannelKey::N3,
              C4 = (2 << 6) | ChannelKey::N4,
              C5 = (2 << 6) | ChannelKey::N5,
              C6 = (2 << 6) | ChannelKey::N6,
              C7 = (2 << 6) | ChannelKey::N7,
              C8 = (2 << 6) | ChannelKey::N8,
              C9 = (2 << 6) | ChannelKey::N9,

              S0 = (3 << 6) | SeqKey::N0,
              S1 = (3 << 6) | SeqKey::N1,
              S2 = (3 << 6) | SeqKey::N2,
              S3 = (3 << 6) | SeqKey::N3,
              S4 = (3 << 6) | SeqKey::N4,
              S5 = (3 << 6) | SeqKey::N5,
              S6 = (3 << 6) | SeqKey::N6,
              S7 = (3 << 6) | SeqKey::N7,
              S8 = (3 << 6) | SeqKey::N8,
              S9 = (3 << 6) | SeqKey::N9,
              S10 = (3 << 6) | SeqKey::N10,
              S11 = (3 << 6) | SeqKey::N11,
              S12 = (3 << 6) | SeqKey::N12,
              S13 = (3 << 6) | SeqKey::N13,
              S14 = (3 << 6) | SeqKey::N14,
              S15 = (3 << 6) | SeqKey::N15)

  struct EncoderEvent {
    EncoderEvent(Encoder e, int steps) : encoder(e), steps(steps) {}
    /// The Encoder at which the event occured
    Encoder encoder;
    /// The number of steps the encoder was turned. Negative means CCW
    int steps;
  };

  struct KeyEvent {
    Key key;
  };

  struct KeyPressEvent : KeyEvent {
    KeyPressEvent(Key k) : KeyEvent{k} {}
  };

  struct KeyReleaseEvent : KeyEvent {
    KeyReleaseEvent(Key k) : KeyEvent{k} {}
  };

  struct LED {
    LED(Key k) : key(k) {}

    Key key;
  };

  struct LEDColor {
    LEDColor() = default;
    LEDColor(std::uint32_t rgb) : r((rgb >> 16) & 0xFF), g((rgb >> 8) & 0xFF), b(rgb & 0xFF) {}
    LEDColor(float r, float g, float b) : r(r * 255), g(g * 255), b(b * 255) {}

    std::uint8_t r = 0, g = 0, b = 0;

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

  struct Controller : core::Service {
    /// Function type for key handlers
    using KeyHandler = std::function<void(Key k)>;

    using Event = util::variant<EncoderEvent, KeyPressEvent, KeyReleaseEvent>;
    using EventBag = std::vector<Event>;

    static std::unique_ptr<Controller> make_dummy();
    static Controller& current() noexcept {
      return Application::current().controller;
    }

    /// Actually executes the key and encoder events
    /// 
    /// Should only be called by graphics thread, once per frame
    void flush_events();

    virtual void set_color(LED, LEDColor) = 0;
    virtual void flush_leds() = 0;
    virtual void clear_leds() = 0;

    /// Check if a key is currently pressed.
    bool is_pressed(Key k) noexcept;

    /// Register a key handler
    void register_key_handler(Key k,
                              KeyHandler press_handler,
                              KeyHandler release_handler = nullptr);


  protected:
    /// Dispatches to the event handler for the current screen, and handles
    /// global keys.
    ///
    /// Can be executed from a separate thread
    void keypress(Key key);

    /// Dispatches to the event handler for the current screen, and handles
    /// global keys.
    ///
    /// Can be executed from a separate thread, but must be the same thread as keypress
    void keyrelease(Key key);

    /// Send encoder event
    ///
    /// Can be executed from a separate thread
    void encoder(EncoderEvent ev);

    /// Temporary solution
    ///
    /// @TODO replace with something cleaner
    friend void ::otto::board::ui::handle_keyevent(board::ui::Action,
                                                   board::ui::Modifiers,
                                                   board::ui::Key);

  private:
    bool handle_global(Key key, bool is_press = true);

    foonathan::array::flat_map<Key, std::pair<KeyHandler, KeyHandler>> key_handlers;
    std::array<bool, Key::_size()> keys;
    util::double_buffered<EventBag> events;
  };
} // namespace otto::services

namespace std {
  template<>
  struct hash<otto::services::Key> {
    using argument_type = otto::services::Key;
    using result_type = std::uint8_t;

    result_type operator()(argument_type const& s) const noexcept
    {
      return s._to_index();
    }
  };
} // namespace std
