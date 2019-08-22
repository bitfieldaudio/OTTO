#pragma once

#include "engine.hpp"
#include "engine_dispatcher.hpp"

#include "core/ui/screen.hpp"
#include "core/ui/widgets/selector_widget.hpp"

namespace otto::core::engine {

  struct EngineSelectorScreen : ui::Screen {
    EngineSelectorScreen(IEngineDispatcher&);

    void encoder(ui::EncoderEvent) override;

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

    ui::SelectorWidget::Options eng_opts(std::function<IEngine&(int)>&&) noexcept;
    ui::SelectorWidget::Options prst_opts(std::function<IEngine&()>&&) noexcept;
  };

} // namespace otto::core::engine
