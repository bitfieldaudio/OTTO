#include "hammond.hpp"

#include "core/ui/vector_graphics.hpp"

#include "hammond.faust.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  /*
   * Declarations
   */

  struct HammondSynthScreen : EngineScreen<HammondSynth> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<HammondSynth>::EngineScreen;
  };

  // HammondSynth ////////////////////////////////////////////////////////////////

  HammondSynth::HammondSynth()
    : SynthEngine("Woody", props, std::make_unique<HammondSynthScreen>(this)),
      voice_mgr_(props),
      faust_(std::make_unique<FAUSTCLASS>(), props)
  {}

  audio::ProcessData<1> HammondSynth::process(audio::ProcessData<1> data)
  {
    voice_mgr_.process_before(data.midi_only());
    auto res = faust_.process(data.midi_only());
    voice_mgr_.process_after(data.midi_only());
    return res;
  }

  /*
   * HammondSynthScreen
   */

  bool HammondSynthScreen::keypress(Key key)
  {
    return false;
  }

  void HammondSynthScreen::rotary(RotaryEvent e)
  {
    switch (e.rotary) {
    case Rotary::Blue: engine.props.drawbar1.step(e.clicks); break;
    case Rotary::Green: engine.props.drawbar2.step(e.clicks); break;
    case Rotary::White: engine.props.drawbar3.step(e.clicks); break;
    case Rotary::Red: engine.props.leslie.step(e.clicks); break;
    }
  }

  void HammondSynthScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    ctx.font(Fonts::Norm, 35);

    // Gray Base Layers
    ctx.group([&] {
      // Ring 1 Base
      ctx.beginPath();
      ctx.circle({160, 120}, 55);
      ctx.lineWidth(6.0);
      ctx.strokeStyle(Colours::Gray50);
      ctx.lineCap(Canvas::LineCap::ROUND);
      ctx.lineJoin(Canvas::LineJoin::ROUND);
      ctx.stroke();

      // Ring 2 Base
      ctx.beginPath();
      ctx.circle({160, 120}, 75);
      ctx.stroke();

      // Ring 3 Base
      ctx.beginPath();
      ctx.circle({160, 120}, 95);
      ctx.stroke();
    });

    // Coloured Parameters
    ctx.group([&] {
      // Ring 1
      ctx.beginPath();
      ctx.rotateAround(55, {160, 120});
      ctx.arc(160, 120, 55, 0, (2 * M_PI * engine.props.drawbar3), false);
      ctx.lineWidth(6.0);
      ctx.strokeStyle(Colours::Yellow);
      ctx.lineCap(Canvas::LineCap::ROUND);
      ctx.lineJoin(Canvas::LineJoin::ROUND);
      ctx.stroke();

      // Ring 2
      ctx.beginPath();
      ctx.arc(160, 120, 75, 0, (2 * M_PI * engine.props.drawbar2), false);
      ctx.strokeStyle(Colours::Green);
      ctx.stroke();

      // Ring 3
      ctx.beginPath();
      ctx.arc(160, 120, 95, 0, (2 * M_PI * engine.props.drawbar1), false);
      ctx.strokeStyle(Colours::Blue);
      ctx.stroke();
    });

    // middle red ring
    ctx.group([&] {
      // Ring Base
      ctx.beginPath();
      ctx.circle({160, 120}, 25);
      ctx.lineWidth(6.0);
      ctx.strokeStyle(Colours::Red);
      ctx.lineCap(Canvas::LineCap::ROUND);
      ctx.lineJoin(Canvas::LineJoin::ROUND);
      ctx.stroke();

      engine.props.phasor.refresh_links();
      float rotation = engine.props.phasor * 2 * M_PI;

      // Inner Ring Base
      ctx.beginPath();
      ctx.rotateAround(rotation, {160, 120});
      ctx.circle({160, 107.5}, 12.5);
      ctx.stroke();
    });
    ///
  }
} // namespace otto::engines
