#pragma once

#include "core/ui/canvas.hpp"

namespace otto::ui {

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

    loop,
    loop_in,
    loop_out,

    lift,
    drop,
    cut,
  };

  using PressedKeys = bool[256];

  class Widget : public vg::SizedDrawable {
  public:
    Widget() {}
    explicit Widget(vg::Size size) : SizedDrawable (size) {}

  };

  enum class Rotary {
    Blue,
    Green,
    White,
    Red
  };


  /**
   * Passed to `Screen::rotary`
   */
  struct RotaryEvent {
    /// The rotary at which the event occured
    Rotary rotary;

    /// The amount of steps the rotary was turned. Negative means CCW
    int clicks;
  };

  /**
   * Represents a view that covers the entire screen
   *
   * If it belongs to a engine, use <ui::EngineScreen>.
   */
  class Screen : public vg::Drawable {
  public:

    using ptr = std::unique_ptr<Screen>;

    Screen() : Drawable() {}
    virtual ~Screen() {}
    /**
     * Run by MainUI when a key is pressed
     *
     * @key the pressed key
     * @return true if the key was used.
     */
    virtual bool keypress(Key) {
      return false;
    }
    /**
     * Run by MainUI when a key is released
     *
     * @key the released key
     * @return true if the key was used.
     */
    virtual bool keyrelease(Key) {
      return false;
    }

    /**
     * This should be used for handling rotary events
     */
    virtual void rotary(RotaryEvent) {}

    /**
     * Run by MainUI when switching to this screen
     */
    virtual void on_show() {}
    /*
     * Run by MainUI when switching to another screen
     */
    virtual void on_hide() {}
  };


  /**
   * The default screen, shown on boot
   */
  class DefaultScreen : public Screen {
  public:
    void draw(vg::Canvas& ctx) override;
    bool keypress(Key key) override;
  };

}
