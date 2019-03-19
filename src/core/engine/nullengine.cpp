#include "nullengine.hpp"

#include "core/ui/vector_graphics.hpp"
#include "services/audio_manager.hpp"

namespace otto::core::engine {

  struct OffScreen : ui::Screen {
    void draw(ui::vg::Canvas& ctx) override;
  };

  NullEngine<EngineType::effect>::NullEngine()
    : EffectEngine<NullEngine<EngineType::effect>>(std::make_unique<OffScreen>())
  {}

  audio::ProcessData<2> NullEngine<EngineType::effect>::process(audio::ProcessData<1> data) noexcept
  {
    auto out = Application::current().audio_manager->buffer_pool().allocate_multi_clear<2>();
    return data.redirect(out);
  }

  NullEngine<EngineType::arpeggiator>::NullEngine()
    : ArpeggiatorEngine<NullEngine<EngineType::arpeggiator>>(std::make_unique<OffScreen>())
  {}

  audio::ProcessData<0> NullEngine<EngineType::arpeggiator>::process(
    audio::ProcessData<0> data) noexcept
  {
    return data;
  }

  NullEngine<EngineType::synth>::NullEngine()
    : SynthEngine<NullEngine<EngineType::synth>>(std::make_unique<OffScreen>())
  {}

  audio::ProcessData<1> NullEngine<EngineType::synth>::process(audio::ProcessData<1> data) noexcept
  {
    return Application::current().audio_manager->buffer_pool().allocate_clear();
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
