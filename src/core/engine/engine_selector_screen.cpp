#include "engine_selector_screen.hpp"

#include "core/ui/vector_graphics.hpp"
#include "services/preset_manager.hpp"

namespace otto::core::engine {

  using namespace otto::core::ui;
  using namespace otto::core::ui::vg;

  EngineSelectorScreen::EngineSelectorScreen(IEngineDispatcher& ed)
    : engine_wid(engine_names, eng_opts([&ed](int idx) -> IEngine& { return ed.select((ed.allow_off) ? idx - 1 : idx); })),
      preset_wid(preset_names, prst_opts([&ed]() -> IEngine& { return ed.current(); })),
      _on_show([this, &ed] { engine_wid.select(ed.allow_off ? ed.current_idx() + 1 : ed.current_idx()); }),
      _engine_dispatcher(ed)
  {
    if (ed.allow_off) engine_names.push_back("OFF");
    util::transform(ed.make_name_list(), std::back_inserter(engine_names),
                    [](auto& sv) { return std::string(sv); });
  }


  SelectorWidget::Options EngineSelectorScreen::eng_opts(
    std::function<IEngine&(int)>&& select_eg) noexcept
  {
    SelectorWidget::Options opts;
    opts.on_select = [this, sl = std::move(select_eg)](int idx) {
      auto& eg = sl(idx);
      try {
        preset_wid.items(Application::current().preset_manager->preset_names(eg.name()));
      } catch (services::PresetManager::exception& e) {
      }
    };
    opts.item_colour = Colours::Gray50;
    opts.size = {120, 200};
    return opts;
  }

  SelectorWidget::Options EngineSelectorScreen::prst_opts(
    std::function<IEngine&()>&& cur_eg) noexcept
  {
    SelectorWidget::Options opts;
    opts.on_select = [cur_eg = std::move(cur_eg)](int idx) {
      try {
      Application::current().preset_manager->apply_preset(cur_eg(), idx);
      } catch (util::exception& e) {
        LOGE(e.what());
      }
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

  bool EngineSelectorScreen::keypress(Key key)
  {
    switch (key) {
    case ui::Key::blue_click: [[fallthrough]];
    case ui::Key::green_click: [[fallthrough]];
    case ui::Key::yellow_click: [[fallthrough]];
    case ui::Key::red_click: {
      std::string name = "Preset" + std::to_string(preset_wid.nitems() + 1);
      Application::current().preset_manager->create_preset(
        _engine_dispatcher.current().name(), name, _engine_dispatcher.current().to_json());
      preset_wid.items(Application::current().preset_manager->preset_names(_engine_dispatcher.current().name()));
      preset_wid.select(preset_wid.nitems() - 1, true);
      break;
    }
    default: return false;
    }
    return true;
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
