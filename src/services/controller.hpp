#pragma once

#include <better_enum.hpp>
#include <cstdint>
#include <foonathan/array/variant_bag.hpp>
#include <type_safe/strong_typedef.hpp>
#include <type_safe/floating_point.hpp>

#include "util/variant.hpp"

#include "core/service.hpp"
#include "core/ui/screen.hpp"

namespace otto::services {

  BETTER_ENUM(FuncKey,
              std::uint8_t,
              master,
              plus,
              minus,

              sends,
              routing,
              rec,
              fx1,
              fx2,
              play,
              looper,
              sequencer,
              sampler,
              settings,
              arp,
              synth,
              envelope,
              external,
              shift,
              slots,
              twist1,
              twist2)

  BETTER_ENUM(Encoder, std::uint8_t, blue, green, yellow, red)

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

  struct EncoderEvent {
    /// The Encoder at which the event occured
    Encoder encoder;
    /// The number of steps the encoder was turned. Negative means CCW
    int steps;
  };

  template<typename KeyType>
  struct KeyEvent {
    KeyType key;
  };

  template<typename KeyType>
  struct KeyPressEvent : KeyEvent<KeyType> {
    KeyPressEvent(KeyType k) : KeyEvent<KeyType>(k){};
  };

  template<typename KeyType>
  struct KeyReleaseEvent : KeyEvent<KeyType> {
    KeyReleaseEvent(KeyType k) : KeyEvent<KeyType>(k){};
  };

  struct LED {
    using Key = util::variant<FuncKey, ChannelKey, SeqKey> ;

    LED(Key k) : key(k) {}

    Key key;
  };

  struct LEDColor {
    LEDColor(std::uint32_t rgb) : r((rgb >> 16) & 0xFF), g((rgb >> 8 ) & 0xFF), b(rgb & 0xFF) {}
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
  inline const LEDColor LEDColor::Black  = 0x000000;
  inline const LEDColor LEDColor::White  = 0xFFFFFF;
  inline const LEDColor LEDColor::Blue   = 0x0000FF;
  inline const LEDColor LEDColor::Green  = 0x00FF00;
  inline const LEDColor LEDColor::Yellow = 0x888800;
  inline const LEDColor LEDColor::Red    = 0xFF0000;

  struct Controller {
    using Event = util::variant<EncoderEvent,
                                KeyPressEvent<Encoder>,
                                KeyReleaseEvent<Encoder>,
                                KeyPressEvent<FuncKey>,
                                KeyReleaseEvent<FuncKey>,
                                KeyPressEvent<ChannelKey>,
                                KeyReleaseEvent<ChannelKey>,
                                KeyPressEvent<SeqKey>,
                                KeyReleaseEvent<SeqKey>>;
    using EventBag = foonathan::array::variant_bag<EncoderEvent,
                                                   KeyPressEvent<Encoder>,
                                                   KeyReleaseEvent<Encoder>,
                                                   KeyPressEvent<FuncKey>,
                                                   KeyReleaseEvent<FuncKey>,
                                                   KeyPressEvent<ChannelKey>,
                                                   KeyReleaseEvent<ChannelKey>,
                                                   KeyPressEvent<SeqKey>,
                                                   KeyReleaseEvent<SeqKey>>;

    virtual EventBag get_events() = 0;

    virtual void set_color(LED, LEDColor) = 0;
    virtual void flush_leds() = 0;
    virtual void clear_leds() = 0;
  };
} // namespace otto::services
