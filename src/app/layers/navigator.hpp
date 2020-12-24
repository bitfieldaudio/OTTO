#pragma once

#include "lib/chrono.hpp"
#include "lib/graphics.hpp"

#include "app/input.hpp"
#include "app/services/config.hpp"

namespace otto {
  /// Handles a navigation "stack", which in fact only allows you to
  /// go back one level.
  ///
  /// Forwards all events and draw calls to the current screen/handler pair
  ///
  /// Can itself be used as a screen/handler pair, delegating to the selected
  /// screen.
  struct Navigator final : IScreen, IInputLayer {
    void navigate_to(ScreenWithHandlerPtr screen);
    /// Navigate back, returning false if no previous screen was available
    bool navigate_back();

    void handle(KeyPress e) noexcept override;
    void handle(KeyRelease e) noexcept override;
    void handle(EncoderEvent e) noexcept override;
    void draw(skia::Canvas& ctx) noexcept override;
    void leds(LEDColorSet& output) noexcept override;

    /// Access the currently selected screen/handler pair
    ScreenWithHandlerPtr current_screen() noexcept;

    [[nodiscard]] KeySet key_mask() const noexcept override;
    [[nodiscard]] LedSet led_mask() const noexcept override;

  private:
    ScreenWithHandlerPtr current_screen_ = nullptr;
    ScreenWithHandlerPtr prev_screen_ = nullptr;
  };

  /// A Keymapping wrapper for a navigator
  ///
  /// Lets you bind navigation keys, and handles momentary navigation
  ///
  /// A momentary press is when you hold the key _longer_ than the given timeout
  ///
  /// In case of a momentary press, the navigator will return to the previous
  /// screen on release
  ///
  /// Forwards all unhandled events to the navigator, which in turn forwards
  /// them to the current screen.
  ///
  /// TODO: Consider splitting momentary detection out into its own component
  /// if it becomes useful in other places
  struct NavKeyMap final : IInputLayer, IScreen {
    struct Conf : Config<Conf> {
      static constexpr auto name = "Navigation Keys";
      chrono::duration peek_timeout = 500ms;
      LEDColor deselected_color = {0x08, 0x08, 0x08};
      LEDColor selected_color = {0x80, 0x80, 0x80};
      DECL_VISIT(peek_timeout, deselected_color, selected_color);
    };

    NavKeyMap(util::smart_ptr<Navigator> n = std::make_unique<Navigator>(), Conf::Handle conf = {});

    Navigator& nav();
    const Navigator& nav() const;

    void bind_nav_key(Key key, ScreenWithHandlerPtr scrn);

    void handle(KeyPress e) noexcept override;
    void handle(KeyRelease e) noexcept override;
    void handle(EncoderEvent e) noexcept override;

    /// Get as a screen/handler pair
    ScreenWithHandlerPtr screen();

    void draw(skia::Canvas& ctx) noexcept override;

    void leds(LEDColorSet& output) noexcept override;

    [[nodiscard]] KeySet key_mask() const noexcept override;
    [[nodiscard]] LedSet led_mask() const noexcept override;

  private:
    Conf::Handle conf;
    util::smart_ptr<Navigator> nav_;
    chrono::time_point last_nav_time_;
    std::unordered_map<Key, ScreenWithHandlerPtr> binds_;
  };
} // namespace otto
