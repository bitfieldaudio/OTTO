#include "engine_selector_screen.hpp"

#include "core/ui/vector_graphics.hpp"
#include "services/preset_manager.hpp"

namespace otto::core::engine {

  using namespace otto::core::ui;
  using namespace otto::core::ui::vg;

  SelectorWidget::Options EngineSelectorScreen::eng_opts(
    std::function<AnyEngine&(int)>&& select_eg) noexcept
  {
    SelectorWidget::Options opts;
    opts.on_select = [this, sl = std::move(select_eg), empty_vec = std::vector<std::string>()](int idx) {
      auto& eg = sl(idx);
      try {
        preset_wid.items(empty_vec);
        preset_wid.items(Application::current().preset_manager->preset_names(eg.name()));
      } catch (services::PresetManager::exception& e) {
      }
    };
    opts.item_colour = Colours::Gray50;
    opts.size = {120, vg::height};
    return opts;
  }

  SelectorWidget::Options EngineSelectorScreen::prst_opts(
    std::function<AnyEngine&()>&& cur_eg) noexcept
  {
    SelectorWidget::Options opts;
    opts.on_select = [cur_eg = std::move(cur_eg)](int idx) {
      Application::current().preset_manager->apply_preset(cur_eg(), idx);
    };
    opts.item_colour = Colours::Gray50;
    opts.selected_item_colour = Colours::Green;
    opts.size = {140, 200};
    return opts;
  }

  void EngineSelectorScreen::rotary(RotaryEvent e)
  {
    switch (e.rotary) {
    case Rotary::blue: engine_wid.prev(e.clicks); break;
    case Rotary::green: preset_wid.prev(e.clicks); break;
    default:;
    }
  }

  void EngineSelectorScreen::draw(vg::Canvas& ctx)
  {
    ctx.drawAt({10, 0}, engine_wid);
    ctx.drawAt({160, 0}, preset_wid);
  }

  void EngineSelectorScreen::on_show()
  {
    if (_on_show) _on_show();
  }

  void EngineSelectorScreen::on_hide() {}

} // namespace otto::core::engine
