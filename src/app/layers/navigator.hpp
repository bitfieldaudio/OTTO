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
    /// Access the previously selected screen/handler pair
    ScreenWithHandlerPtr prev_screen() noexcept;

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
  struct NavKeyMap final : IInputLayer, IScreen, util::ISerializable {
    struct Conf : Config<Conf> {
      static constexpr auto name = "NavKeyMap";
      chrono::duration peek_timeout = 500ms;
      LEDColor deselected_color = {0x20, 0x20, 0x20};
      LEDColor selected_color = {0xFF, 0xFF, 0xFF};
      DECL_VISIT(peek_timeout, deselected_color, selected_color);
    };

    NavKeyMap(Conf conf, util::smart_ptr<Navigator> n = std::make_unique<Navigator>());

    Navigator& nav();
    const Navigator& nav() const;

    std::unordered_map<Key, ScreenWithHandlerPtr>& current_binds();
    const std::unordered_map<Key, ScreenWithHandlerPtr>& current_binds() const;

    void bind_nav_key(Key key, ScreenWithHandlerPtr scrn, bool shift_held = false);

    void handle(KeyPress e) noexcept override;
    void handle(KeyRelease e) noexcept override;
    void handle(EncoderEvent e) noexcept override;

    /// Get as a screen/handler pair
    ScreenWithHandlerPtr screen();

    void draw(skia::Canvas& ctx) noexcept override;

    void leds(LEDColorSet& output) noexcept override;

    [[nodiscard]] KeySet key_mask() const noexcept override;
    [[nodiscard]] LedSet led_mask() const noexcept override;

    void serialize_into(json::value& json) const override;

    void deserialize_from(const json::value& json) override;

  private:
    Conf conf;
    util::smart_ptr<Navigator> nav_;
    chrono::time_point last_nav_time_;
    bool shift_held = false;
    std::unordered_map<Key, ScreenWithHandlerPtr> binds_;
    std::unordered_map<Key, ScreenWithHandlerPtr> shift_binds_;
  };
} // namespace otto
