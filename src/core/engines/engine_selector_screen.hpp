#pragma once

#include "engine.hpp"
#include "engine_dispatcher.hpp"

#include "core/ui/screen.hpp"
#include "core/ui/widgets/selector_widget.hpp"

namespace otto::engines {

  struct EngineSelectorScreen : ui::Screen {

    template<EngineType ET>
    EngineSelectorScreen(EngineDispatcher<ET>&);

    void rotary(ui::RotaryEvent) override;

    void draw(ui::vg::Canvas&) override;

    void on_show() override;
    void on_hide() override;

  private:
    std::vector<std::string> engine_names;
    std::vector<std::string> preset_names;
    ui::SelectorWidget engine_wid;
    ui::SelectorWidget preset_wid;

    ui::SelectorWidget::Options eng_opts(std::function<AnyEngine&(int)>&&) noexcept;
    ui::SelectorWidget::Options prst_opts(std::function<AnyEngine&()>&&) noexcept;
  };

  // Constructor implementation

  /// \exclude
  template<EngineType ET>
  EngineSelectorScreen::EngineSelectorScreen(EngineDispatcher<ET>& ed)
    : engine_wid(engine_names, eng_opts([&ed](int idx) -> AnyEngine& {
                   return ed.select(std::size_t{idx});
                 })),
      preset_wid(preset_names, prst_opts([&ed]() -> AnyEngine& { return ed.current(); }))
  {
    engine_names.reserve(ed.engines().size());
    util::transform(ed.engines(), std::back_inserter(engine_names),
                    [](auto&& e) { return e->name(); });
  }

}
