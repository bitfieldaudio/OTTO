#include "selector_widget.hpp"

namespace otto::ui {

  SelectorWidget::SelectorWidget(std::vector<std::string>& items,
                                 Options&& p_options)
    : Widget(p_options.size),
      options(std::move(p_options)),
      _selected_item(options.initial_selection),
      _items(&items)
  {}

  void SelectorWidget::draw(vg::Canvas& ctx)
  {
    using namespace vg;

    _selected_item = std::clamp(_selected_item, 0, nitems());
    int vitems =
      std::min(nitems(), (int) std::ceil(size.h / options.item_height));
    _top_item =
      std::clamp(_top_item, _selected_item - vitems + 1, _selected_item);

    vitems = std::min(vitems, nitems() - _top_item);

    for (int i = 0; i < vitems; i++) {
      const int idx = _top_item + i;

      if (idx == _selected_item) {
        ctx.beginPath();
        ctx.rect({0, i * options.item_height}, {size.w, options.item_height});
        ctx.fill(options.item_colour);
        ctx.fillStyle(Colours::Black);
      } else {
        ctx.fillStyle(options.item_colour);
      }
      ctx.beginPath();
      ctx.textAlign(TextAlign::Left, TextAlign::Middle);
      ctx.font(Fonts::Light, options.font_size);
      ctx.fillText((*_items)[idx], {5.f, (i + 0.5f) * options.item_height},
                   size.w - 10.f);
    }
  }

  bool SelectorWidget::prev(int n) noexcept
  {
    return next(-n);
  }

  bool SelectorWidget::next(int n) noexcept
  {
    const int idx = std::clamp(_selected_item + n, 0, nitems() - 1);
    if (select(idx)) {
      return idx == n;
    }
    return false;
  }

  bool SelectorWidget::select(int idx, bool no_callback) noexcept
  {
    if (idx == _selected_item) return true;
    if (idx < 0 || idx >= nitems()) return false;
    _selected_item = idx;
    if (!no_callback) options.on_select(idx);
    return true;
  }

  int SelectorWidget::selected_item() const noexcept
  {
    return _selected_item;
  }

  int SelectorWidget::nitems() const noexcept
  {
    return _items->size();
  }

  const std::vector<std::string>& SelectorWidget::items() const noexcept
  {
    return *_items;
  }

  const std::vector<std::string>& SelectorWidget::items(
    const std::vector<std::string>& vec) noexcept
  {
    _items = &vec;
    _top_item = 0;
    _selected_item = 0;
    return *_items;
  }
} // namespace otto::ui
