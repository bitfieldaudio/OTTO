#include "external.hpp"

#include "core/globals.hpp"
#include "core/ui/vector_graphics.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct ExternalScreen : EngineScreen<External> {
    void draw(Canvas& ctx) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<External>::EngineScreen;
  };

  External::External()
    : Engine("External", props, std::make_unique<ExternalScreen>(this))
  {}


  audio::ProcessData<1> External::process(audio::ProcessData<1> data)
  {
    for (auto& frm : data) {
      frm[0] *= props.gain * props.gain;
      graph.add(frm[0]);
    }
    return data;
  }

  // SCREEN //

  void ExternalScreen::rotary(ui::RotaryEvent ev)
  {
    auto& props = engine.props;
    props.gain.step(ev.clicks);
  }

  void ExternalScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    auto& props = engine.props;

    ctx.font(Fonts::Bold, 40);

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Baseline);
    ctx.fillText("EXTERNAL IN", {160, 60});

    ctx.font(Fonts::Bold, 100);

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Top);
    ctx.fillText(fmt::format("{}", (int) std::round(props.gain* 100.0)), {160, 70});

    ctx.beginPath();
    ctx.moveTo({40, 200});
    ctx.lineTo({40 + 240 * engine.graph.average, 200});
    ctx.lineWidth(6);
    ctx.stroke(Colours::White);

    engine.graph.clear();

  }

} // namespace otto::engines
