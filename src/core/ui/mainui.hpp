/// \file
/// This file contains the UI state. If you do not need access to this, but just
/// the library, look at `core/ui/widgets.hpp` and `core/ui/canvas.hpp` instead.

#pragma once

#include "core/ui/widget.hpp"
#include <json.hpp>

namespace otto::ui {

  /// The main ui loop
  ///
  /// This sets up all the device specific graphics, and calls
  /// [internal::draw_frame]() 60 times pr second, until [global::running] is
  /// false, or the graphics are exitted by the user. It is also responsible for
  /// listening to keyevents, and calling [internal::keypress]() and
  /// [internal::keyrelease]() as apropriate.
  ///
  /// On some platforms (OSX), all OpenGL calls must be made from the main
  /// thread, therefore this function is called from `main()`.
  ///
  /// One important note, is that this function is implemented in the graphics
  /// drivers, and not the expected implementation file. Currently the only
  /// graphics driver avaliable is `src/core/ui/glfw_impl.cpp`
  void main_ui_loop();

  /// Check if a key is currently pressed.
  bool is_pressed(Key k) noexcept;

  /// Display a screen.
  ///
  /// Calls [Screen::on_hide]() for the old screen, and then [Screen::on_show]()
  /// for the new screen
  void display(Screen& screen);

  void init();

  nlohmann::json serialize();

  void deserialize(const nlohmann::json& j);

  /// These functions are to be called only by the graphics drivers.
  namespace impl {

    /// Draws the current screen and overlays.
    void draw_frame(vg::Canvas& ctx);

    /// Dispatches to the event handler for the current screen, and handles
    /// global keys.
    bool keypress(Key key);

    /// Dispatches to the event handler for the current screen, and handles
    /// global keys.
    bool keyrelease(Key key);
  } // namespace impl

} // namespace otto::ui
