#pragma once

#include <thread>

#include "core/ui/canvas.hpp"

namespace otto::ui {

  /**
   * Used for keypresses
   */
  enum Key {
    K_NONE = 0,

    K_RED_UP,
    K_RED_DOWN,
    K_RED_CLICK,
    K_BLUE_UP,
    K_BLUE_DOWN,
    K_BLUE_CLICK,
    K_WHITE_UP,
    K_WHITE_DOWN,
    K_WHITE_CLICK,
    K_GREEN_UP,
    K_GREEN_DOWN,
    K_GREEN_CLICK,

    K_LEFT,
    K_RIGHT,
    K_SHIFT,

    K_PLAY,
    K_REC,
    K_TRACK_1,
    K_TRACK_2,
    K_TRACK_3,
    K_TRACK_4,

    // Globals:
    K_QUIT,

    // Numbers
    K_1,
    K_2,
    K_3,
    K_4,
    K_5,
    K_6,
    K_7,
    K_8,
    K_9,
    K_0,

    K_TAPE,
    K_MIXER,
    K_METRONOME,
    K_SYNTH,
    K_DRUMS,
    K_SAMPLER,
    K_LOOPER,

    K_LOOP,
    K_LOOP_IN,
    K_LOOP_OUT,

    K_LIFT,
    K_DROP,
    K_CUT,
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
    // cppcheck-suppress unusedStructMember
    int clicks;
  };

  /**
   * Represents a view that covers the entire screen
   *
   * If it belongs to a module, use <ui::ModuleScreen>.
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
    virtual void init() {}
    /*
     * Run by MainUI when switching to another screen
     */
    virtual void exit() {}
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
