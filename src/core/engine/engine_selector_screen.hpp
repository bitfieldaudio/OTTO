#pragma once

#include "engine.hpp"
#include "engine_dispatcher.hpp"

#include "core/ui/screen.hpp"
#include "core/ui/widgets/selector_widget.hpp"

namespace otto::core::engine {

  struct EngineSelectorScreen : ui::Screen {
    template<EngineType ET>
    EngineSelectorScreen(EngineDispatcher<ET>&);

    void rotary(ui::RotaryEvent) override;

    bool keypress(ui::Key) override;

    void draw(ui::vg::Canvas&) override;

    void on_show() override;
    void on_hide() override;

  private:
    std::vector<std::string> engine_names;
    std::vector<std::string> preset_names;
    ui::SelectorWidget engine_wid;
    ui::SelectorWidget preset_wid;

    std::function<void()> _on_show = nullptr;

    ///Owner
    IEngineDispatcher& _engine_dispatcher;

    ui::SelectorWidget::Options eng_opts(std::function<AnyEngine&(int)>&&) noexcept;
    ui::SelectorWidget::Options prst_opts(std::function<AnyEngine&()>&&) noexcept;
  };

  // Constructor implementation

  /// \exclude
  template<EngineType ET>
  EngineSelectorScreen::EngineSelectorScreen(EngineDispatcher<ET>& ed)
    : engine_wid(engine_names, eng_opts([&ed](int idx) -> AnyEngine& {
                   if (ed.engine_factories()[idx].name == ed.current()->name()) return *ed.current();
                   return ed.select(static_cast<std::size_t>(idx));
                 })),
      preset_wid(preset_names, prst_opts([&ed]() -> AnyEngine& { return *ed.current(); })),
      _on_show([this, &ed] { engine_wid.select(ed.current_idx()); }),
      _engine_dispatcher(ed)
  {
    engine_names.reserve(ed.engine_factories().size());
    util::transform(ed.engine_factories(), std::back_inserter(engine_names),
                    [](auto&& e) { return e.name; });
  }

} // namespace otto::core::engine
