#pragma once

#include <bitset>
#include <compare>
#include <cstdint>

#include <fmt/format.h>

#include "lib/util/enum.hpp"

#include "lib/chrono.hpp"
#include "lib/itc/eventsender.hpp"
#include "lib/itc/reducer.hpp"

namespace otto {

  enum struct Key : std::uint8_t {
    channel0 = 1,
    channel1 = 2,
    channel2 = 3,
    channel3 = 4,
    channel4 = 5,
    channel5 = 6,
    channel6 = 7,
    channel7 = 8,
    channel8 = 9,
    channel9 = 10,
    seq0 = 11,
    seq1 = 12,
    seq2 = 13,
    seq3 = 14,
    seq4 = 15,
    seq5 = 16,
    seq6 = 17,
    seq7 = 18,
    seq8 = 19,
    seq9 = 20,
    seq10 = 21,
    seq11 = 22,
    seq12 = 23,
    seq13 = 24,
    seq14 = 25,
    seq15 = 26,
    blue_enc_click = 27,
    green_enc_click = 28,
    yellow_enc_click = 29,
    red_enc_click = 30,
    shift = 31,
    sends = 32,
    plus = 33,
    mixer = 34,
    minus = 35,
    fx1 = 36,
    fx2 = 37,
    master = 38,
    play = 39,
    record = 40,
    arp = 41,
    slots = 42,
    twist1 = 43,
    twist2 = 44,
    looper = 45,
    external = 46,
    sampler = 47,
    envelope = 48,
    voices = 49,
    settings = 50,
    sequencer = 51,
    synth = 52,
    page_a = 53,
    page_b = 54,
    page_c = 55,
    page_d = 56,
    sigma = 57,
    omega = 58,
  };

  using KeySet = util::enum_bitset<Key>;

  namespace key_groups {
    inline const KeySet seq = {Key::seq0,  Key::seq1,  Key::seq2,  Key::seq3, Key::seq4,  Key::seq5,
                               Key::seq6,  Key::seq7,  Key::seq8,  Key::seq9, Key::seq10, Key::seq11,
                               Key::seq12, Key::seq13, Key::seq14, Key::seq15};
    inline const KeySet channel = {Key::channel0, Key::channel1, Key::channel2, Key::channel3, Key::channel4,
                                   Key::channel5, Key::channel6, Key::channel7, Key::channel8, Key::channel9};
    inline const KeySet piano = seq | channel;
    inline const KeySet enc_clicks = {Key::blue_enc_click, Key::green_enc_click, Key::yellow_enc_click,
                                      Key::red_enc_click};

    inline const KeySet pages = {Key::page_a, Key::page_b, Key::page_c, Key::page_d};

    inline const KeySet screens = {Key::sends,     Key::mixer,   Key::fx1,      Key::fx2,    Key::master,
                                   Key::arp,       Key::slots,   Key::twist1,   Key::twist2, Key::looper,
                                   Key::external,  Key::sampler, Key::envelope, Key::voices, Key::settings,
                                   Key::sequencer, Key::synth};

    inline const KeySet commands = {Key::shift, Key::plus, Key::minus, Key::play, Key::record, Key::sigma, Key::omega};

    inline const KeySet func = pages | screens | commands;

  } // namespace key_groups

  enum struct Encoder : std::uint8_t {
    blue,
    green,
    yellow,
    red,
  };

  inline Key click_for(Encoder e)
  {
    switch (e) {
      case Encoder::blue: return Key::blue_enc_click;
      case Encoder::green: return Key::green_enc_click;
      case Encoder::yellow: return Key::yellow_enc_click;
      case Encoder::red: return Key::red_enc_click;
    }
    OTTO_UNREACHABLE();
  }

  inline tl::optional<std::uint8_t> channel_number_for(Key k)
  {
    if (key_groups::channel.test(k)) return {static_cast<std::uint8_t>(k) - static_cast<std::uint8_t>(Key::channel0)};
    return tl::nullopt;
  }

  inline tl::optional<Key> channel_key(int n)
  {
    if (n < 10) return Key(static_cast<std::uint8_t>(Key::channel0) + static_cast<std::uint8_t>(n));
    return tl::nullopt;
  }

  inline tl::optional<Key> seq_key(int n)
  {
    if (n < 16) return Key(static_cast<std::uint8_t>(Key::seq0) + static_cast<std::uint8_t>(n));
    return tl::nullopt;
  }

  template<typename Event>
  struct TimedEvent : Event {
    chrono::time_point timestamp = chrono::clock::now();
    auto operator<=>(const TimedEvent&) const = default;
    bool operator==(const TimedEvent& e) const = default;
    auto operator<=>(const Event& e) const
    {
      return e <=> static_cast<const Event&>(*this);
    }
    bool operator==(const Event& e) const
    {
      return e == static_cast<const Event&>(*this);
    }
  };

  struct UntimedKeyEvent {
    Key key = {};
    auto operator<=>(const UntimedKeyEvent&) const = default;
  };

  struct UntimedKeyPress : UntimedKeyEvent {
    auto operator<=>(const UntimedKeyPress&) const = default;
  };

  struct UntimedKeyRelease : UntimedKeyEvent {
    auto operator<=>(const UntimedKeyRelease&) const = default;
  };

  struct UntimedEncoderEvent {
    Encoder encoder = {};
    int steps = 0;
    auto operator<=>(const UntimedEncoderEvent&) const = default;
  };


  using KeyEvent = TimedEvent<UntimedKeyEvent>;
  using KeyPress = TimedEvent<UntimedKeyPress>;
  using KeyRelease = TimedEvent<UntimedKeyRelease>;
  using EncoderEvent = TimedEvent<UntimedEncoderEvent>;
  using IInputHandler = IEventHandler<KeyPress, KeyRelease, EncoderEvent>;

  struct InputHandler : IInputHandler {
    void handle(KeyPress) noexcept override {}
    void handle(KeyRelease) noexcept override {}
    void handle(EncoderEvent) noexcept override {}
  };

  template<itc::AState State>
  struct InputReducer : itc::Reducer<State, KeyPress, KeyRelease, EncoderEvent> {
    using itc::Reducer<State, KeyPress, KeyRelease, EncoderEvent>::Reducer;
    void reduce(KeyPress e, State& state) noexcept override {}
    void reduce(KeyRelease e, State& state) noexcept override {}
    void reduce(EncoderEvent e, State& state) noexcept override {}
  };

  using InputEventSender = itc::EventSender<KeyPress, KeyRelease, EncoderEvent>;

  inline std::ostream& operator<<(std::ostream& os, const UntimedKeyPress& e)
  {
    return os << fmt::format("{{{}}}", util::enum_name(e.key));
  }

  inline std::ostream& operator<<(std::ostream& os, const UntimedKeyRelease& e)
  {
    return os << fmt::format("{{{}}}", util::enum_name(e.key));
  }

  inline std::ostream& operator<<(std::ostream& os, const UntimedEncoderEvent& e)
  {
    return os << fmt::format("{{{}, {}}}", util::enum_name(e.encoder), e.steps);
  }

  template<typename Event>
  inline std::ostream& operator<<(std::ostream& os, const TimedEvent<Event>& e)
  {
    return os << fmt::format("{{{} @ {}}}", static_cast<const Event&>(e), e.timestamp.time_since_epoch());
  }

} // namespace otto
