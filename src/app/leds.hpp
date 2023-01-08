#pragma once

#include "lib/util/func_interface.hpp"
#include "lib/util/visitor.hpp"

#include "lib/json.hpp"
#include "lib/skia/color.hpp"

#include "app/input.hpp"

namespace otto {

  enum struct Led : std::uint8_t {
    channel0 = util::enum_integer(Key::channel0),
    channel1 = util::enum_integer(Key::channel1),
    channel2 = util::enum_integer(Key::channel2),
    channel3 = util::enum_integer(Key::channel3),
    channel4 = util::enum_integer(Key::channel4),
    channel5 = util::enum_integer(Key::channel5),
    channel6 = util::enum_integer(Key::channel6),
    channel7 = util::enum_integer(Key::channel7),
    channel8 = util::enum_integer(Key::channel8),
    channel9 = util::enum_integer(Key::channel9),
    seq0 = util::enum_integer(Key::seq0),
    seq1 = util::enum_integer(Key::seq1),
    seq2 = util::enum_integer(Key::seq2),
    seq3 = util::enum_integer(Key::seq3),
    seq4 = util::enum_integer(Key::seq4),
    seq5 = util::enum_integer(Key::seq5),
    seq6 = util::enum_integer(Key::seq6),
    seq7 = util::enum_integer(Key::seq7),
    seq8 = util::enum_integer(Key::seq8),
    seq9 = util::enum_integer(Key::seq9),
    seq10 = util::enum_integer(Key::seq10),
    seq11 = util::enum_integer(Key::seq11),
    seq12 = util::enum_integer(Key::seq12),
    seq13 = util::enum_integer(Key::seq13),
    seq14 = util::enum_integer(Key::seq14),
    seq15 = util::enum_integer(Key::seq15),
    shift = util::enum_integer(Key::shift),
    sends = util::enum_integer(Key::sends),
    plus = util::enum_integer(Key::plus),
    mixer = util::enum_integer(Key::mixer),
    minus = util::enum_integer(Key::minus),
    fx1 = util::enum_integer(Key::fx1),
    fx2 = util::enum_integer(Key::fx2),
    master = util::enum_integer(Key::master),
    play = util::enum_integer(Key::play),
    record = util::enum_integer(Key::record),
    arp = util::enum_integer(Key::arp),
    slots = util::enum_integer(Key::slots),
    twist1 = util::enum_integer(Key::twist1),
    twist2 = util::enum_integer(Key::twist2),
    looper = util::enum_integer(Key::looper),
    external = util::enum_integer(Key::external),
    sampler = util::enum_integer(Key::sampler),
    envelope = util::enum_integer(Key::envelope),
    voices = util::enum_integer(Key::voices),
    settings = util::enum_integer(Key::settings),
    sequencer = util::enum_integer(Key::sequencer),
    synth = util::enum_integer(Key::synth),
    page_a = util::enum_integer(Key::page_a),
    page_b = util::enum_integer(Key::page_b),
    page_c = util::enum_integer(Key::page_c),
    page_d = util::enum_integer(Key::page_d),
    sigma = util::enum_integer(Key::sigma),
    omega = util::enum_integer(Key::omega),
  };

  using LedSet = util::enum_bitset<Led>;

  namespace led_groups {
    inline const LedSet seq = {Led::seq0,  Led::seq1,  Led::seq2,  Led::seq3, Led::seq4,  Led::seq5,
                               Led::seq6,  Led::seq7,  Led::seq8,  Led::seq9, Led::seq10, Led::seq11,
                               Led::seq12, Led::seq13, Led::seq14, Led::seq15};
    inline const LedSet channel = {Led::channel0, Led::channel1, Led::channel2, Led::channel3, Led::channel4,
                                   Led::channel5, Led::channel6, Led::channel7, Led::channel8, Led::channel9};
    inline const LedSet piano = seq | channel;

    inline const LedSet pages = {Led::page_a, Led::page_b, Led::page_c, Led::page_d};

    inline const LedSet screens = {Led::sends,     Led::mixer,   Led::fx1,      Led::fx2,    Led::master,
                                   Led::arp,       Led::slots,   Led::twist1,   Led::twist2, Led::looper,
                                   Led::external,  Led::sampler, Led::envelope, Led::voices, Led::settings,
                                   Led::sequencer, Led::synth};

    inline const LedSet commands = {Led::shift, Led::plus, Led::minus, Led::play, Led::record, Led::sigma, Led::omega};

    inline const LedSet func = pages | screens | commands;
  } // namespace led_groups

  inline tl::optional<Led> led_from(Key k)
  {
    return util::enum_cast<Led>(util::enum_integer(k));
  }

  inline tl::optional<Key> key_from(Led l)
  {
    return util::enum_cast<Key>(util::enum_integer(l));
  }

  struct LEDColor {
    uint8_t r = 0, g = 0, b = 0;

    void serialize_into(json::value& json) const;
    void deserialize_from(const json::value& json);

    static LEDColor from_skia(skia::Color color)
    {
      return {.r = color.red(), .g = color.green(), .b = color.blue()};
    }

    constexpr auto operator<=>(const LEDColor&) const = default;

    friend std::ostream& operator<<(std::ostream& os, LEDColor lc);
  };

  using LEDColorSet = util::enum_map<Led, LEDColor>;

  namespace led_colors {
    constexpr LEDColor black = {0, 0, 0};
    constexpr LEDColor red = {0xFF, 0x00, 0x00};
    constexpr LEDColor green = {0x00, 0xFF, 0x00};
    constexpr LEDColor blue = {0x00, 0x00, 0xFF};
    constexpr LEDColor yellow = {0x80, 0x80, 0x00};
    constexpr LEDColor white = {0xFF, 0xFF, 0xFF};

    constexpr LEDColor inactive = {0x02, 0x02, 0x02};
  } // namespace led_colors

  /// The interface of an object that controls LED colors.
  ///
  /// Basically the `IDrawable` of LEDs.
  ///
  /// Should be used on the graphics thread.
  struct ILedController {
    virtual ~ILedController() = default;
    virtual void leds(LEDColorSet& leds) noexcept = 0;
    using Func = util::FuncInterface<&ILedController::leds>;
  };

  /// An `ILedController` with an empty `leds` function
  ///
  /// Can be used as a base class, to later override `leds`
  struct LedController : ILedController {
    void leds(LEDColorSet& leds) noexcept override {}
  };
} // namespace otto
