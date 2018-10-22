#pragma once

#include <vector>
#include <functional>
#include "core/ui/screen.hpp"
#include "core/ui/vector_graphics.hpp"

namespace otto::core::ui {

  /// A menu-style generic selector widget
  ///
  /// \module widgets
  struct SelectorWidget : Widget {

    /// Immutable widget options
    struct Options {
      /// Invoked with the newly selected index.
      std::function<void(int idx)> on_select = [](int) {};
      /// Unselected text colour.
      vg::Colour item_colour = vg::Colours::Gray50;
      /// Selected text colour.
      vg::Colour selected_item_colour = vg::Colours::Blue;
      /// Height of each item
      float item_height = 35.f;
      float font_size = 30.f;
      /// Dimensions of the widget. Initializes [Widget::size]()
      vg::Size size = {300, 240};
      /// Initial value for `_selected_item`
      int initial_selection = 0;
    } const options;

    /// Construct with options.
    SelectorWidget(std::vector<std::string>& items, Options&& options);

    /// Draw to canvas
    void draw(vg::Canvas&) override;

    /// Select previous item
    ///
    /// \param n Number of iterations. If the provided number of steps could not
    /// be taken, the maximum possible steps are taken instead. In that case,
    /// returns `false`
    ///
    /// \returns `true` on success, otherwie `false`
    bool prev(int n = 1) noexcept;

    /// Select next item
    ///
    /// \param n Number of iterations. If the provided number of steps could not
    /// be taken, the maximum possible steps are taken instead. In that case,
    /// returns `false`
    ///
    /// \returns `true` on success, otherwise `false`
    bool next(int n = 1) noexcept;

    /// Select an item by index
    ///
    /// If `idx` is less than `0`, or greater than the number of items, no
    /// action is taken, and `false` is returned.
    ///
    /// \param no_callback If true, `options.on_select` will not be called.
    ///
    /// \postconditions
    /// `selected_item() == idx` unless `false` was returned.
    bool select(int idx, bool no_callback = false) noexcept;

    /// Get the index of the currently selected item
    int selected_item() const noexcept;

    /// Number of items
    int nitems() const noexcept;

    /// Access the referenced item names
    const std::vector<std::string>& items() const noexcept;

    /// Set the vector of referenced items
    ///
    /// \effects
    /// Assign `ref` to [items]()
    /// select the first item and scroll to the top.
    ///
    /// \postconditions `items() == ref`
    const std::vector<std::string>& items(const std::vector<std::string>& ref) noexcept;

    /// Avoid temporaries
    void items(const std::vector<std::string>&&) = delete;

  private:
    int _selected_item = 0;
    int _top_item = 0;
    const std::vector<std::string> * _items;
  };
}
