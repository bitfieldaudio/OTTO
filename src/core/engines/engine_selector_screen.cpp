#include "engine_selector_screen.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::engines {

  using namespace otto::ui;
  using namespace otto::ui::vg;

  SelectorWidget::Options EngineSelectorScreen::eng_opts(
    std::function<void(int)>&& on_select) noexcept
  {
        SelectorWidget::Options opts;
        opts.on_select = [this, sl = std::move(on_select)](int idx) {
          preset_names = {engine_names[idx],
                          "what",
                          "is",
                          "this",
                          "PRESET CALLLED",
                          "one",
                          "two",
                          "three",
                          "four",
                          "five",
                          "six",
                          "seven",
                          "eight",
                          "nine",
                          "ten",
                          "eleven",
                          "twelve",
                          "thirteen",
                          "fourteen",
                          "fifteen",
                          "sixteen",
                          "seventeen",
                          "eighteen",
                          "nineteen",
                          "twenty"};
          preset_wid.items(preset_names);
          sl(idx);
        };
        opts.item_colour = Colours::Blue;
        opts.size = {120, vg::HEIGHT};
        return opts;
  }

  SelectorWidget::Options EngineSelectorScreen::prst_opts(
    std::function<void(int)>&& on_select) noexcept
  {
        SelectorWidget::Options opts;
        opts.on_select = std::move(on_select);
        opts.item_colour = Colours::Green;
        opts.size = {120, vg::HEIGHT};
        return opts;
  }

  void EngineSelectorScreen::rotary(RotaryEvent e)
  {
    switch (e.rotary) {
    case Rotary::Blue:
      engine_wid.prev(e.clicks);
      break;
    case Rotary::Green:
      preset_wid.prev(e.clicks);
      break;
    default:;
    }
  }

  void EngineSelectorScreen::draw(vg::Canvas& ctx)
  {
    ctx.drawAt({40, 0}, engine_wid);
    ctx.drawAt({160, 0}, preset_wid);
  }

  void EngineSelectorScreen::on_show()
  {
    engine_wid.options.on_select(engine_wid.selected_item());
  }

  void EngineSelectorScreen::on_hide()
  {}

} // namespace otto::engines
