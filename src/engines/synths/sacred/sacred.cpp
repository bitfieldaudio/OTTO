#include "sacred.hpp"

#include "core/globals.hpp"
#include "core/ui/vector_graphics.hpp"

#include "sacred.faust.hpp"

namespace otto::engines {

using namespace ui;
using namespace ui::vg;

/*
   * Declarations
   */

struct SacredSynthScreen : EngineScreen<SacredSynth> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<SacredSynth>::EngineScreen;

};

// SacredSynth ////////////////////////////////////////////////////////////////

SacredSynth::SacredSynth()
    : SynthEngine("Sacred", props, std::make_unique<SacredSynthScreen>(this)),
      voice_mgr_(props),
      faust_(std::make_unique<FAUSTCLASS>(), props)
{}

audio::ProcessData<1> SacredSynth::process(audio::ProcessData<1> data)
{
    voice_mgr_.process_before(data.midi_only());
    auto res = faust_.process(data.midi_only());
    voice_mgr_.process_after(data.midi_only());
    return res;
}

/*
   * SacredSynthScreen
   */

bool SacredSynthScreen::keypress(Key key)
{
    return false;
}

void SacredSynthScreen::rotary(RotaryEvent e)
{
    switch (e.rotary) {
    case Rotary::Blue:
        engine.props.drawbar1.step(e.clicks);
        break;
    case Rotary::Green:
        engine.props.drawbar2.step(e.clicks);
        break;
    case Rotary::White:
        engine.props.drawbar3.step(e.clicks);
        break;
    case Rotary::Red:
        engine.props.leslie.step(e.clicks);
        break;
    }
}

void SacredSynthScreen::draw(ui::vg::Canvas& ctx)
{
    using namespace ui::vg;

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    /// albert's experimental part
    // Gray Base Layers
    ctx.group([&]{
        // Gray Connector Line Top Right
        ctx.beginPath();
        ctx.moveTo(228.3, 80.7);
        ctx.lineTo({194.1 / engine.props.drawbar3}, 99.9); //Triangle Top Right
        ctx.lineWidth(6.0);
        ctx.strokeStyle(Colours::Gray50);
        ctx.stroke();

        // Gray Connector Line Top Left
        ctx.beginPath();
        ctx.moveTo(92.3, 80.7);
        ctx.lineTo({125.9* engine.props.drawbar1}, 99.9); //Triangle Top Left
        ctx.stroke();

        // Gray Connector Line Bottom
        ctx.beginPath();
        ctx.moveTo(160.3, 198.6);
        ctx.lineTo(160.3, {159.0 / engine.props.drawbar2}); //Triangle Bottom
        ctx.stroke();

        // Base Hectagon
        ctx.beginPath();
        ctx.moveTo(228.3, 80.7);
        ctx.lineTo(160.3, 41.4);
        ctx.lineTo(92.3, 80.7);
        ctx.lineTo(92.3, 159.3);
        ctx.lineTo(160.3, 198.6);
        ctx.lineTo(228.3, 159.3);
        ctx.lineTo(228.3, 80.7);
        ctx.closePath();
        ctx.stroke();
    });

    // Coloured Lines
    ctx.group([&]{
        // Blue Line 1
        ctx.beginPath();
        ctx.lineWidth(6.0);
        ctx.moveTo(228.3, 159.3);
        ctx.lineTo(160.3, {159.3 / engine.props.drawbar2}); //Triangle Bottom
        ctx.strokeStyle(Colours::Blue);
        ctx.lineCap(Canvas::LineCap::ROUND);
        ctx.lineJoin(Canvas::LineJoin::ROUND);
        ctx.stroke();

        // Green Line 1
        ctx.beginPath();
        ctx.moveTo({194.1 / engine.props.drawbar3}, 99.9); //Triangle Top Right
        ctx.lineTo(160.3, 41.4);
        ctx.strokeStyle(Colours::Green);
        ctx.stroke();

        // Red Line 1 (top)
        ctx.beginPath();
        ctx.moveTo(160.3, 41.4);
        ctx.lineTo({125.9 * engine.props.drawbar1}, 99.9);  //Triangle Top Left
        ctx.strokeStyle(Colours::Red);
        ctx.stroke();

        // Green Line 2
        ctx.beginPath();
        ctx.moveTo(228.3, 159.3);
        ctx.lineTo({194.1 / engine.props.drawbar3}, 99.9); //Triangle Top Right
        ctx.strokeStyle(Colours::Green);
        ctx.stroke();

        // Red Line 2
        ctx.beginPath();
        ctx.moveTo(92.3, 159.3);
        ctx.lineTo({125.9 * engine.props.drawbar1}, 99.9);  //Triangle Top Left
        ctx.strokeStyle(Colours::Red);
        ctx.stroke();

        // Blue Line 2
        ctx.beginPath();
        ctx.moveTo(92.3, 159.3);
        ctx.lineTo(160.3, {159.3 / engine.props.drawbar2}); //Triangle Bottom
        ctx.strokeStyle(Colours::Blue);
        ctx.stroke();

        // Main Triangle
        ctx.beginPath();
        ctx.moveTo(160.3, {159.0 / engine.props.drawbar2}); //Triangle Bottom
        ctx.lineTo({194.1 / engine.props.drawbar3}, 99.9); //Triangle Top Right
        ctx.lineTo(160.3, 99.9);
        ctx.lineTo({125.9 * engine.props.drawbar1}, 99.9);  //Triangle Top Left
        ctx.lineTo(160.3, {159.0 / engine.props.drawbar2}); //Triangle Bottom
        ctx.closePath();
        ctx.strokeStyle(Colours::Yellow);
        ctx.stroke();

    });
    ///
}
} // namespace otto::engines
