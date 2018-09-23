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

    // Text
    ctx.font(Fonts::Bold, 26);
    ctx.fillStyle(Colour::bytes(255, 255, 255));
    ctx.fillText("master volume", 86.6, 189.9);

    // Dot
    ctx.save();
    ctx.beginPath();
    ctx.circle({160,110},4);
    ctx.fillStyle(Colours::Green);
    ctx.fill();
    ctx.lineWidth(6.0);
    ctx.strokeStyle(Colour::bytes(147, 192, 34));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // Dial
    float rotation = -2.15 + engine.props.volume * 4.3;

    ctx.save();
    ctx.rotateAround(rotation,{160,110});
    ctx.beginPath();
    ctx.moveTo(160.0, 110.8);
    ctx.lineTo(160.0, 73.4);
    ctx.stroke();
    ctx.restore();

    // Outer circle
    ctx.restore();
    ctx.beginPath();
    ctx.moveTo(109.4, 144.9);
    ctx.bezierCurveTo(102.8, 135.1, 99.0, 123.4, 99.0, 110.8);
    ctx.bezierCurveTo(99.0, 77.1, 126.3, 49.8, 160.0, 49.8);
    ctx.bezierCurveTo(193.7, 49.8, 221.0, 77.1, 221.0, 110.8);
    ctx.bezierCurveTo(221.0, 122.6, 217.6, 133.7, 211.8, 143.0);
    ctx.lineWidth(6.0);
    ctx.strokeStyle(Colour::bytes(99, 99, 99));
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();
    ctx.restore();


  }

} // namespace otto::engines
