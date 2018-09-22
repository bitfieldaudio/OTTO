#include "master.hpp"

#include "core/globals.hpp"
#include "core/ui/vector_graphics.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"

#include "master.faust.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct MasterScreen : EngineScreen<Master> {
    void draw(Canvas& ctx) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<Master>::EngineScreen;
  };

  Master::Master()
    : Engine("Master", props, std::make_unique<MasterScreen>(this)),
      faust_(std::make_unique<faust_master>(), props)
  {}


  audio::ProcessData<2> Master::process(audio::ProcessData<2> data)
  {
    for (auto& frm : data) {
      frm[0] *= props.volume * props.volume * 0.80;
      frm[1] *= props.volume * props.volume * 0.80;
    }
    return faust_.process(data);
  }

  // SCREEN //

  void MasterScreen::rotary(ui::RotaryEvent ev)
  {
    auto& props = engine.props;
    props.volume.step(ev.clicks);
  }

  void MasterScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    auto& props = engine.props;

    ctx.font(Fonts::Bold, 40);

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Baseline);
    ctx.fillText("Volume", {160, 60});

    ctx.font(Fonts::Bold, 100);

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Top);
    ctx.fillText(fmt::format("{}", (int) std::round(props.volume * 100.0)), {160, 70});
  }

} // namespace otto::engines
