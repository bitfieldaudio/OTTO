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
    synth,
    drums,
    sampler,
    looper,
    envelope,

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

  /// Possible alignments for floating widgets, like overlays
  enum struct Alignment {
    top_left,
    top_center,
    top_right,
    center_left,
    center,
    center_right,
    bottom_left,
    bottom_center,
    bottom_right
  };

  /// Two-way padding
  struct Padding {
    float horizontal = 0;
    float vertical = 0;
  };

  /// An absolute or relative position on screen
  struct Position {

    /// An absolute position of the top left corner
    struct Absolute : vg::Point {
      using Point::Point;
    };

    struct Relative {
      Alignment alignment = Alignment::center;
      Padding padding = {};

      /// Get the absolute position of a box given the size
      auto absolute(vg::Size size = {}) const noexcept -> Absolute;
    };

  private:
    std::variant<Relative, Absolute> _data;
  };

  struct Overlay : Widget {

    /// Draw the overlay at its correct position
    void draw(vg::Canvas&) override final;

  protected:

    virtual void draw_impl(vg::Canvas&) = 0;

  private:
    Position _position;
  };

} // namespace otto::core::ui
