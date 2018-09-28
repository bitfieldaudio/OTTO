#include "nuke.hpp"

#include "core/globals.hpp"
#include "core/ui/vector_graphics.hpp"

#include "nuke.faust.hpp"

namespace otto::engines {

using namespace ui;
using namespace ui::vg;

/*
   * Declarations
   */

struct NukeSynthScreen : EngineScreen<NukeSynth> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<NukeSynth>::EngineScreen;

};

// NukeSynth ////////////////////////////////////////////////////////////////

NukeSynth::NukeSynth()
    : SynthEngine("Nuke", props, std::make_unique<NukeSynthScreen>(this)),
      voice_mgr_(props),
      faust_(std::make_unique<FAUSTCLASS>(), props)
{}

audio::ProcessData<1> NukeSynth::process(audio::ProcessData<1> data)
{
    voice_mgr_.process_before(data.midi_only());
    auto res = faust_.process(data.midi_only());
    voice_mgr_.process_after(data.midi_only());
    return res;
}

/*
   * NukeSynthScreen
   */

bool NukeSynthScreen::keypress(Key key)
{
    return false;
}

void NukeSynthScreen::rotary(RotaryEvent e)
{
    switch (e.rotary) {
    case Rotary::Blue:
        engine.props.wave.step(e.clicks);
        break;
    case Rotary::Green:
        engine.props.aux.step(e.clicks);
        break;
    case Rotary::White:
        engine.props.relation.step(e.clicks);
        break;
    case Rotary::Red:
        engine.props.filter.step(e.clicks);
        break;
    }
}

using namespace ui::vg;

void NukeSynthScreen::draw(Canvas& ctx)
{
    // Nuke/StaticGraphics
    ctx.group([&]{
        // Nuke/StaticGraphics/Tubing
        ctx.beginPath();
        ctx.moveTo(242.2, 180.5);
        ctx.lineTo(206.6, 180.5);
        ctx.bezierCurveTo(203.4, 180.5, 200.7, 177.9, 200.7, 174.6);
        ctx.lineTo(200.7, 154.0);
        ctx.lineWidth(6.0);
        ctx.strokeStyle(Colours::Gray50);
        ctx.lineCap(Canvas::LineCap::ROUND);
        ctx.lineJoin(Canvas::LineJoin::ROUND);
        ctx.stroke();

        // Nuke/StaticGraphics/Tubing
        ctx.beginPath();
        ctx.moveTo(148.4, 123.0);
        ctx.lineTo(165.0, 123.0);
        ctx.lineTo(165.0, 73.0);
        ctx.lineTo(165.0, 52.9);
        ctx.bezierCurveTo(165.0, 43.1, 173.0, 35.1, 182.9, 35.1);
        ctx.lineTo(182.9, 35.1);
        ctx.bezierCurveTo(192.7, 35.1, 200.7, 43.1, 200.7, 52.9);
        ctx.lineTo(200.7, 154.0);
        ctx.stroke();

        // Nuke/StaticGraphics/Tubing
        ctx.beginPath();
        ctx.moveTo(149.5, 63.9);
        ctx.lineTo(165.0, 63.9);
        ctx.stroke();

        // Nuke/StaticGraphics/Tubing
        ctx.beginPath();
        ctx.moveTo(68.3, 123.0);
        ctx.lineTo(96.6, 123.0);
        ctx.stroke();

        // Nuke/StaticGraphics/Tubing
        ctx.beginPath();
        ctx.moveTo(68.3, 63.9);
        ctx.lineTo(96.6, 63.9);
        ctx.stroke();

        // Nuke/StaticGraphics/Glass
        ctx.beginPath();
        ctx.moveTo(113.0, 35.1);
        ctx.lineTo(113.0, 39.0);
        ctx.bezierCurveTo(103.1, 42.9, 96.2, 52.8, 96.7, 64.3);
        ctx.bezierCurveTo(97.3, 77.3, 107.7, 88.0, 120.7, 88.9);
        ctx.bezierCurveTo(135.8, 89.9, 148.4, 78.0, 148.4, 63.1);
        ctx.bezierCurveTo(148.4, 52.1, 141.6, 42.8, 132.1, 39.0);
        ctx.lineTo(132.1, 35.1);
        ctx.strokeStyle(Colours::White);
        ctx.stroke();

        // Nuke/StaticGraphics/Glass
        ctx.beginPath();
        ctx.moveTo(291.5, 35.1);
        ctx.lineTo(291.5, 197.2);
        ctx.bezierCurveTo(291.5, 201.2, 288.2, 204.5, 284.2, 204.5);
        ctx.lineTo(249.5, 204.5);
        ctx.bezierCurveTo(245.5, 204.5, 242.2, 201.2, 242.2, 197.2);
        ctx.lineTo(242.2, 35.1);
        ctx.stroke();

        // Nuke/StaticGraphics/BlueGlass
        ctx.beginPath();
        ctx.moveTo(29.0, 49.7);
        ctx.bezierCurveTo(29.0, 41.6, 35.5, 35.1, 43.6, 35.1);
        ctx.lineTo(48.6, 35.1);
        ctx.bezierCurveTo(56.7, 35.1, 63.2, 41.6, 63.2, 49.7);
        ctx.lineTo(63.2, 189.9);
        ctx.bezierCurveTo(63.2, 197.9, 56.7, 204.5, 48.6, 204.5);
        ctx.lineTo(43.6, 204.5);
        ctx.bezierCurveTo(35.5, 204.5, 29.0, 197.9, 29.0, 189.9);
        ctx.lineTo(29.0, 49.7);
        ctx.closePath();
        ctx.stroke();

        // Nuke/StaticGraphics/BlueEndTubing
        ctx.beginPath();
        ctx.moveTo(73.3, 69.0);
        ctx.lineTo(73.3, 58.6);
        ctx.stroke();

        // Nuke/StaticGraphics/BlueTubing
        ctx.beginPath();
        ctx.moveTo(73.3, 65.7);
        ctx.lineTo(63.2, 65.7);
        ctx.lineTo(63.2, 61.7);
        ctx.lineTo(73.3, 61.7);
        ctx.stroke();

        // Nuke/StaticGraphics/BlueEndTubing
        ctx.beginPath();
        ctx.moveTo(73.3, 128.2);
        ctx.lineTo(73.3, 117.8);
        ctx.stroke();

        // Nuke/StaticGraphics/BlueTubing
        ctx.beginPath();
        ctx.moveTo(73.3, 125.0);
        ctx.lineTo(63.2, 125.0);
        ctx.lineTo(63.2, 121.0);
        ctx.lineTo(73.3, 121.0);
        ctx.stroke();

        // Nuke/StaticGraphics/YellowGlass
        ctx.beginPath();
        ctx.moveTo(210.5, 64.0);
        ctx.bezierCurveTo(214.7, 64.0, 218.0, 67.3, 218.0, 71.5);
        ctx.lineTo(218.0, 151.5);
        ctx.bezierCurveTo(218.0, 155.7, 214.7, 159.0, 210.5, 159.0);
        ctx.lineTo(191.0, 159.0);
        ctx.bezierCurveTo(186.8, 159.0, 183.5, 155.7, 183.5, 151.5);
        ctx.lineTo(183.5, 71.5);
        ctx.bezierCurveTo(183.5, 67.3, 186.8, 64.0, 191.0, 64.0);
        ctx.stroke();

        // Nuke/StaticGraphics/GreenBox
        ctx.beginPath();
        ctx.moveTo(148.4, 101.0);
        ctx.lineTo(148.4, 195.0);
        ctx.bezierCurveTo(148.4, 200.1, 144.3, 204.3, 139.2, 204.3);
        ctx.lineTo(105.9, 204.3);
        ctx.bezierCurveTo(100.8, 204.3, 96.7, 200.1, 96.7, 195.0);
        ctx.lineTo(96.7, 101.0);
        ctx.stroke();
    });

    // temporary float
    // needs some love to get the animation working.
    float pivalue1 = 1.2 * M_PI * engine.props.relation ;
    float pivalue2 = 1.8 * M_PI / engine.props.relation ;

    //green circle
    ctx.beginPath();
    ctx.lineWidth(6.0);
    ctx.arc(122.5,63,14,pivalue1,pivalue2,true);
    ctx.closePath();
    ctx.fill(Colours::Green);
    ctx.stroke(Colours::Green);

    // Nuke/FullBGLayer
    ctx.beginPath();
    ctx.moveTo(254.0, 193.0);
    ctx.lineTo(254.0, 64.9);
    ctx.lineTo(279.5, 64.9);
    ctx.lineTo(279.5, 193.0);
    ctx.lineTo(254.0, 193.0);
    ctx.closePath();
    ctx.fillStyle(Colours::Gray50);
    ctx.fill();
    ctx.strokeStyle(Colours::Gray50);
    ctx.stroke();

    // Nuke/RedLayer
    ctx.beginPath();
    ctx.moveTo(279.5, 193.5);
    ctx.lineTo(254.0, 193.5);
    ctx.lineTo(254.0, 84.3 + engine.props.filter * 1.1);
    ctx.lineTo(279.5, 84.3 + engine.props.filter * 1.1);
    ctx.lineTo(279.5, 193.5);
    ctx.closePath();
    ctx.fillStyle(Colours::Red);
    ctx.fill();
    ctx.strokeStyle(Colours::Red);
    ctx.stroke();

    // Nuke/BlueLayer
    ctx.beginPath();
    ctx.moveTo(279.5, 79.9 + engine.props.filter);
    ctx.lineTo(254.0, 79.9 + engine.props.filter);
    ctx.lineTo(254.0, 77.8 + engine.props.filter * 0.80);
    ctx.lineTo(279.5, 77.8 + engine.props.filter * 0.80);
    ctx.lineTo(279.5, 79.9 + engine.props.filter);
    ctx.closePath();
    ctx.strokeStyle(Colours::Blue);
    ctx.fillStyle(Colours::Blue);
    ctx.fill();
    ctx.stroke();

    // Nuke/PinkLayer
    ctx.beginPath();
    ctx.moveTo(254.0, 64.9 + engine.props.filter * 0.55);
    ctx.lineTo(279.5, 64.9 + engine.props.filter * 0.55);
    ctx.strokeStyle(Colours::Pink);
    ctx.stroke();

    //waveform
    ctx.group([&]{
        ctx.rotateAround(0.5 * M_PI,{0,52});
        float dial = engine.props.wave.normalize() * 4.f;
        //  Dial takes values between 0 and 4 and returns a list of line endpoints
        //  Position at integer values are hardcoded. In between, they are
        //  interpolated between surrounding integer value position
        //  The points lie in a 1x4 box

        // Pure waves (integer positions)
        //  first row is x-coords, second row is y-coords
        // NOTE: These can be moved into the if-statement -- we never need more than
        // two of them in a single function call

        using util::math::vec;

        std::valarray<vec> const pw_square = {{0, 1}, {0, 1}, {0, 0}, {2, 0},
                                              {2, 1}, {2, 1}, {2, 0}, {4, 0}, {4, 1}};
        std::valarray<vec> const square = {{0, 1}, {1, 1}, {1, 0}, {2, 0},
                                           {2, 1}, {3, 1}, {3, 0}, {4, 0}, {4, 1}};
        std::valarray<vec> const below_triangle = {
            {4 / 5, 1},     {4 / 5, 1},     {2 * 4 / 5, 0},
            {2 * 4 / 5, 0}, {3 * 4 / 5, 1}, {3 * 4 / 5, 1}, {4 * 4 / 5, 0},
            {4 * 4 / 5, 0}, {4, 1}};
        std::valarray<vec> const triangle = {
            {4 / 5, 1},     {2 * 4 / 5, 0}, {3 * 4 / 5, 1},
            {3 * 4 / 5, 1}, {3 * 4 / 5, 1}, {4 * 4 / 5, 0}, {4, 1},
            {4, 1},         {4, 1}};
        std::valarray<vec> const saw = {{0, 1}, {2, 0}, {2, 1}, {2, 1},
                                        {2, 1}, {4, 0}, {4, 1}, {4, 1}, {4, 1}};
        std::valarray<vec> const hs_saw = {{0, 1}, {1, 0}, {1, 1}, {2, 0},
                                           {2, 1}, {3, 0}, {3, 1}, {4, 0}, {4, 1}};

        // Initialise points
        auto points = pw_square;
        // fractional part of dial
        auto frac = dial - std::floor(dial);

        if (dial >= 0 && dial < 1)
            points = pw_square * (1 - frac) + square * frac;
        else if (dial >= 1 && dial < 2)
            points = square * (1 - frac) + below_triangle * frac;
        else if (dial >= 2 && dial < 3)
            points = triangle * (1 - frac) + saw * frac;
        else if (dial >= 3 && dial < 4)
            points = saw * (1 - frac) + hs_saw * frac;
        else if (dial == 4)
            points = hs_saw * 0;

        // Move the points to the correct positions
        points = points * vec{65.f / 4.f, 12.f};

        ctx.beginPath();
        ctx.plotLines(std::begin(points), std::end(points));
        points = points + vec{65.f, 0};
        ctx.plotLines(std::begin(points), std::end(points));
        ctx.stroke(Colours::Blue);
    });

    // Nuke/GreenValueBox
    ctx.beginPath();
    ctx.moveTo(136.9, 193.0);
    ctx.lineTo(108.1, 193.0);
    ctx.lineTo(108.1, 112.0 + engine.props.relation * 26.5);
    ctx.lineTo(136.9, 112.0 + engine.props.relation * 26.5);
    ctx.lineTo(136.9, 193.0);
    ctx.closePath();
    ctx.fillStyle(Colours::Green);
    ctx.fill();
    ctx.strokeStyle(Colours::Green);
    ctx.stroke();

    // Nuke/YellowValue
    ctx.beginPath();
    ctx.moveTo(206.5, 148.6);
    ctx.lineTo(195.0, 148.6);
    ctx.lineTo(195.0, 88.9 + engine.props.aux * 20);
    ctx.lineTo(206.5, 88.9 + engine.props.aux * 20);
    ctx.lineTo(206.5, 148.6);
    ctx.closePath();
    ctx.fillStyle(Colours::Yellow);
    ctx.fill();
    ctx.strokeStyle(Colours::Yellow);
    ctx.stroke();

    // Nuke/WhiteLine
    ctx.beginPath();
    ctx.moveTo(200.7, 166.0);
    ctx.lineTo(200.7, 127.0);
    ctx.strokeStyle(Colours::White);
    ctx.stroke();
}


}
// namespace otto::engines
