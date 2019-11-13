#pragma once

#include "core/ui/canvas.hpp"
#include "core/input.hpp"

namespace otto::core::ui {

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

  /// Represents a view that covers the entire screen
  ///
  /// If it belongs to a engine, use [engines::EngineScreen]().
  struct Screen : vg::Drawable {
    Screen() : Drawable() {}
    virtual ~Screen() {}
    /// Run by MainUI when switching to this screen
    virtual void on_show() {}

    /// Run by MainUI when switching to another screen
    virtual void on_hide() {}
  };


  struct ScreenAndInput {
    ScreenAndInput(core::ui::Screen& s, core::input::InputHandler& i) noexcept : screen_(&s), input_(&i) {}

    ScreenAndInput(const ScreenAndInput&) = default;
    ScreenAndInput& operator=(const ScreenAndInput&) = default;

    core::ui::Screen& screen() noexcept
    {
      return *screen_;
    }

    core::input::InputHandler& input() noexcept
    {
      return *input_;
    }

  private:
    core::ui::Screen* screen_;
    core::input::InputHandler* input_;
  };

} // namespace otto::core::ui
