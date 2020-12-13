#pragma once

#include "lib/chrono.hpp"
#include "lib/graphics.hpp"

#include "app/input.hpp"

namespace otto {
  /// Handles a navigation "stack", which in fact only allows you to
  /// go back one level.
  ///
  /// Forwards all events and draw calls to the current screen/handler pair
  ///
  /// Can itself be used as a screen/handler pair, delegating to the selected
  /// screen.
  struct Navigator : IScreen, IInputHandler {
    void navigate_to(ScreenWithHandlerPtr screen);
    /// Navigate back, returning false if no previous screen was available
    bool navigate_back();

    void handle(KeyPress e) noexcept override;
    void handle(KeyRelease e) noexcept override;
    void handle(EncoderEvent e) noexcept override;
    void draw(skia::Canvas& ctx) noexcept override;

    /// Access the currently selected screen/handler pair
    ScreenWithHandlerPtr current_screen() noexcept;

  private:
    ScreenWithHandlerPtr current_screen_ = nullptr;
    ScreenWithHandlerPtr prev_screen_ = nullptr;
  };

  /// A Keymapping wrapper for a navigator
  ///
  /// Lets you bind navigation keys, and handles momentary navigation
  ///
  /// A momentary press is either
  ///  - if you release the nav key within a timeout of pressing it
  ///  - You press other keys while the navigation key is pressed
  ///  - You turn encoders while the navigation key is pressd
  ///
  /// In case of a momentary press, the navigator will return to the previous
  /// screen on release
  ///
  /// Forwards all unhandled events to the navigator, which in turn forwards
  /// them to the current screen.
  ///
  /// TODO: Consider splitting momentary detection out into its own component
  /// if it becomes useful in other places
  struct NavKeyMap : IInputHandler {
    NavKeyMap(util::any_ptr<Navigator> n, chrono::duration timeout = 500ms);

    Navigator& nav();

    void bind_nav_key(Key key, ScreenWithHandlerPtr scrn);

    void handle(KeyPress e) noexcept override;
    void handle(KeyRelease e) noexcept override;
    void handle(EncoderEvent e) noexcept override;

  private:
    util::any_ptr<Navigator> nav_;
    chrono::time_point last_nav_time_;
    util::enum_map<Key, ScreenWithHandlerPtr> binds_;
    chrono::duration momentary_timeout_ = 500ms;
  };
} // namespace otto
