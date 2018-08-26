#pragma once

#include "core/ui/canvas.hpp"

namespace otto::core::ui {

  /// Represents a physical key
  enum struct Key {
    none = 0,

    red_up,
    red_down,
    red_click,
    blue_up,
    blue_down,
    blue_click,
    white_up,
    white_down,
    white_click,
    green_up,
    green_down,
    green_click,

    left,
    right,
    shift,
    oct_up,
    oct_down,

    play,
    rec,
    track_1,
    track_2,
    track_3,
    track_4,

    // Globals:
    quit,

    tape,
    mixer,
    metronome,
    sequencer,
    synth,
    drums,
    sampler,
    looper,
    envelope,
    voices,

    loop,
    loop_in,
    loop_out,

    ret,

    lift,
    drop,
    cut,

    /// Number of keys
    n_keys,
  };

  using PressedKeys = bool[util::underlying(Key::n_keys)];

  /// A [Drawable]() with a defined size
  ///
  /// Intended as a base class for widgets.
  struct Widget : vg::Drawable {
    vg::Size size;

    Widget() {}

    explicit Widget(vg::Size size) //
      : Drawable(), size(size)
    {}
  };

  enum struct Rotary { Blue, Green, White, Red };

  /// Passed to `Screen::rotary`
  struct RotaryEvent {
    /// The rotary at which the event occured
    Rotary rotary;

    /// The amount of steps the rotary was turned. Negative means CCW
    int clicks;
  };

  /// Represents a view that covers the entire screen
  ///
  /// If it belongs to a engine, use [engines::EngineScreen]().
  struct Screen : vg::Drawable {
    Screen() : Drawable() {}
    virtual ~Screen() {}

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

    /// This should be used for handling rotary events
    virtual void rotary(RotaryEvent) {}

    /// Run by MainUI when switching to this screen
    virtual void on_show() {}

    /// Run by MainUI when switching to another screen
    virtual void on_hide() {}
  };

} // namespace otto::core::ui
