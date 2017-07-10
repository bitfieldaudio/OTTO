#pragma once

#include <nanocanvas/NanoCanvas.h>

#include <thread>

#include "../module.h"

namespace ui {

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

  // Tapedeck
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

/**
 * Anything that can be drawn on screen.
 * Holds a pointer to its parent
 */
class Drawable {
public:

  Drawable() {};

  /**
   * Draw this widget to the context.
   * Called from the parent's draw method.
   * @param ctx the canvas to draw on.
   */
  virtual void draw(NanoCanvas::Canvas& ctx) = 0;

};

class Widget : public Drawable {
public:
  float h, w;

  Widget() {}
  Widget(float w, float h) : w (w), h (h) {}

  virtual void drawAt(NanoCanvas::Canvas &ctx,
   float x, float y) {
    ctx.save();
    ctx.translate(x, y);
    draw(ctx);
    ctx.restore();
  }

  virtual void drawAt(NanoCanvas::Canvas &ctx,
   float x, float y, float w, float h) {
    this->h = h;
    this->w = w;
    ctx.save();
    ctx.translate(x, y);
    draw(ctx);
    ctx.restore();
  }

};

/**
 * A specific view/window.
 * If it belongs to a module, use ModuleScreen.
 */
class Screen : public Drawable {
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
};

/**
 * A screen that belongs to a module of type M
 */
template<class M>
class ModuleScreen : public Screen {
protected:
  M *module;

public:
  using ptr = std::shared_ptr<ModuleScreen<M>>;

  ModuleScreen() :
    Screen() {}

  ModuleScreen(M *module)
    : module (module),
    Screen () {}

  virtual ~ModuleScreen() {}
};


/**
 * The default screen, shown on boot
 */
class DefaultScreen : public Screen {
public:
  void draw(NanoCanvas::Canvas& ctx) override;
  bool keypress(Key key) override;
};

}
