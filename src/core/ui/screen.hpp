#pragma once

#include "core/ui/canvas.hpp"
#include "services/controller.hpp"

namespace otto::core::ui {

  /// Represents a physical key
  using Key = services::Key;
  using Encoder = services::Encoder;
  using EncoderEvent = services::EncoderEvent;

  using PressedKeys = bool[Key::_size()];

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
    virtual void encoder(EncoderEvent) {}

    /// Run by MainUI when switching to this screen
    virtual void on_show() {}

    /// Run by MainUI when switching to another screen
    virtual void on_hide() {}
  };

} // namespace otto::core::ui
