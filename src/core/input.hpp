#pragma once

#include "util/enum.hpp"

#include "itc/action.hpp"

namespace otto::core::input {

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

  BETTER_ENUM(ChannelKey, std::uint8_t, N0 = 0, N1 = 1, N2 = 2, N3 = 3, N4 = 4, N5 = 5, N6 = 6, N7 = 7, N8 = 8, N9 = 9)

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

  using EncoderAction = itc::Action<struct encoder_action_tag, EncoderEvent>;

  /// An object that handles input events
  ///
  /// Handles keypress/releases and encoder steps.
  struct InputHandler {
    /// Run by MainUI when a key is pressed
    ///
    /// \param key the pressed key
    /// \returns true if the key was used.
    virtual bool keypress(Key)
    {
      return false;
    }

    /// Run by MainUI when a key is released
    ///
    /// \param key the released key
    /// \returns true if the key was used.
    virtual bool keyrelease(Key)
    {
      return false;
    }

    /// Handle encoder events
    virtual void encoder(EncoderEvent) {}
  };

} // namespace otto::core::input

namespace std {
  template<>
  struct hash<otto::core::input::Key> {
    using argument_type = otto::core::input::Key;
    using result_type = std::uint8_t;

    result_type operator()(argument_type const& s) const noexcept
    {
      return s._to_index();
    }
  };
} // namespace std
