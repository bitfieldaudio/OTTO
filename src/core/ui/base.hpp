#pragma once

#include <thread>

#include "core/ui/canvas.hpp"

namespace top1::ui {

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

class Widget : public drawing::SizedDrawable {
public:
  Widget() {}
  Widget(drawing::Size size) : SizedDrawable (size) {}

};
/**
 * Represents a view that covers the entire screen
 * If it belongs to a module, use <ui::ModuleScreen>.
 */
class Screen : public drawing::Drawable {
public:

  using ptr = std::shared_ptr<Screen>;

  Screen() : Drawable() {}
  /**
   * Run by MainUI when a key is pressed
   * @param key the pressed key
   * @return true if the key was used.
   */
  virtual bool keypress(Key) {
    return false;
  };
  /**
   * Run by MainUI when a key is released
   * @param key the released key
   * @return true if the key was used.
   */
  virtual bool keyrelease(Key) {
    return false;
  };

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
  void draw(drawing::Canvas& ctx) override;
  bool keypress(Key key) override;
};

}
