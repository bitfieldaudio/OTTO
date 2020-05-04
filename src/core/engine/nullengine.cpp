#include "nullengine.hpp"

#include "core/ui/vector_graphics.hpp"
#include "services/audio_manager.hpp"

namespace otto::core::engine {

  OffEngine<EngineType::effect>::OffEngine(itc::ActionChannel) {}

  audio::ProcessData<2> OffEngine<EngineType::effect>::Audio::process(audio::ProcessData<1> data) noexcept
  {
    auto out = Application::current().audio_manager->buffer_pool().allocate_multi_clear<2>();
    return data.with(out);
  }

  OffEngine<EngineType::arpeggiator>::OffEngine(itc::ActionChannel) {}

  audio::ProcessData<0> OffEngine<EngineType::arpeggiator>::Audio::process(audio::ProcessData<0> data) noexcept
  {
    return data;
  }

  void OffScreen::draw(ui::vg::Canvas& ctx)
  {
    ctx.fillStyle(ui::vg::Colours::Red);
    ctx.font(ui::vg::Fonts::Bold, 80);
    ctx.beginPath();
    ctx.textAlign(ui::vg::HorizontalAlign::Center, ui::vg::VerticalAlign::Middle);
    ctx.fillText("OFF", {160, 120});
  }
} // namespace otto::core::engine
