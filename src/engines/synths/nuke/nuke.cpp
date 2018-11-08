#include "nuke.hpp"

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
    case Rotary::Blue: engine.props.wave.step(e.clicks); break;
    case Rotary::Green: engine.props.aux.step(e.clicks); break;
    case Rotary::White: engine.props.relation.step(e.clicks); break;
    case Rotary::Red: engine.props.filter.step(e.clicks); break;
    }
}

using namespace ui::vg;

void NukeSynthScreen::draw(Canvas& ctx)
{
    // dots
    ctx.group([&] {
        ctx.beginPath();
        ctx.moveTo(286.6, 29.2);
        ctx.lineTo(287.0, 29.2);
        ctx.strokeStyle(Colours::Gray50);
        ctx.lineWidth(6.0);
        ctx.stroke();

        // Nuke/Dots/Dot
        ctx.beginPath();
        ctx.moveTo(193.4, 29.2);
        ctx.lineTo(193.7, 29.2);
        ctx.stroke();

        // Nuke/Dots/Dot
        ctx.beginPath();
        ctx.moveTo(286.6, 79.4);
        ctx.lineTo(287.0, 79.4);
        ctx.stroke();

        // Nuke/Dots/Dot
        ctx.beginPath();
        ctx.moveTo(193.4, 79.4);
        ctx.lineTo(193.7, 79.4);
        ctx.stroke();

        // Nuke/Dots/Dot
        ctx.beginPath();
        ctx.moveTo(286.6, 110.7);
        ctx.lineTo(287.0, 110.7);
        ctx.stroke();

        // Nuke/Dots/Dot
        ctx.beginPath();
        ctx.moveTo(193.4, 110.7);
        ctx.lineTo(193.7, 110.7);
        ctx.stroke();

        // Nuke/Dots/Dot
        ctx.beginPath();
        ctx.moveTo(286.6, 202.0);
        ctx.lineTo(287.0, 202.0);
        ctx.stroke();

        // Nuke/Dots/Dot
        ctx.beginPath();
        ctx.moveTo(193.4, 202.0);
        ctx.lineTo(193.7, 202.0);
        ctx.stroke();

        // Nuke/Dots/Dot
        ctx.beginPath();
        ctx.moveTo(153.8, 217.5);
        ctx.lineTo(154.1, 217.5);
        ctx.stroke();

        // Nuke/Dots/Dot
        ctx.beginPath();
        ctx.moveTo(33.0, 217.5);
        ctx.lineTo(33.4, 217.5);
        ctx.stroke();

        // Nuke/Dots/Dot
        ctx.beginPath();
        ctx.moveTo(153.8, 82.3);
        ctx.lineTo(154.1, 82.3);
        ctx.stroke();

        // Nuke/Dots/Dot
        ctx.beginPath();
        ctx.moveTo(33.0, 82.3);
        ctx.lineTo(33.4, 82.3);
        ctx.stroke();

        // Nuke/Dots/Dot
        ctx.beginPath();
        ctx.moveTo(153.8, 22.3);
        ctx.lineTo(154.1, 22.3);
        ctx.stroke();

        // Nuke/Dots/Dot
        ctx.beginPath();
        ctx.moveTo(33.0, 22.3);
        ctx.lineTo(33.4, 22.3);
        ctx.stroke();
    });

    // gray boxes
    ctx.group([&] {
        // Nuke/Boxes/KeyBox
        ctx.beginPath();
        ctx.moveTo(269.3, 76.4);
        ctx.lineTo(211.0, 76.4);
        ctx.bezierCurveTo(203.0, 76.4, 196.5, 70.0, 196.5, 62.0);
        ctx.lineTo(196.5, 47.6);
        ctx.bezierCurveTo(196.5, 39.6, 203.0, 33.2, 211.0, 33.2);
        ctx.lineTo(269.3, 33.2);
        ctx.bezierCurveTo(277.3, 33.2, 283.8, 39.6, 283.8, 47.6);
        ctx.lineTo(283.8, 62.0);
        ctx.bezierCurveTo(283.8, 70.0, 277.3, 76.4, 269.3, 76.4);
        ctx.closePath();
        ctx.lineWidth(6.0);
        ctx.strokeStyle(Colours::Gray50);
        ctx.lineCap(Canvas::LineCap::ROUND);
        ctx.lineJoin(Canvas::LineJoin::ROUND);
        ctx.stroke();

        // Nuke/Boxes/FilterBox
        ctx.beginPath();
        ctx.moveTo(269.3, 199.0);
        ctx.lineTo(211.0, 199.0);
        ctx.bezierCurveTo(203.0, 199.0, 196.5, 192.5, 196.5, 184.5);
        ctx.lineTo(196.5, 129.2);
        ctx.bezierCurveTo(196.5, 121.2, 203.0, 114.7, 211.0, 114.7);
        ctx.lineTo(269.3, 114.7);
        ctx.bezierCurveTo(277.3, 114.7, 283.8, 121.2, 283.8, 129.2);
        ctx.lineTo(283.8, 184.5);
        ctx.bezierCurveTo(283.8, 192.5, 277.3, 199.0, 269.3, 199.0);
        ctx.closePath();
        ctx.stroke();

        // Nuke/Boxes/WaveBox
        ctx.beginPath();
        ctx.moveTo(136.5, 214.5);
        ctx.lineTo(50.7, 214.5);
        ctx.bezierCurveTo(42.7, 214.5, 36.2, 208.1, 36.2, 200.1);
        ctx.lineTo(36.2, 100.7);
        ctx.bezierCurveTo(36.2, 92.7, 42.7, 86.3, 50.7, 86.3);
        ctx.lineTo(136.5, 86.3);
        ctx.bezierCurveTo(144.5, 86.3, 151.0, 92.7, 151.0, 100.7);
        ctx.lineTo(151.0, 200.1);
        ctx.bezierCurveTo(151.0, 208.1, 144.5, 214.5, 136.5, 214.5);
        ctx.closePath();
        ctx.stroke();
    });

    // dial
    ctx.group([&] {
        // Nuke/Dial/Low
        ctx.beginPath();
        ctx.moveTo(59.0, 57.5);
        ctx.bezierCurveTo(59.0, 38.5, 74.5, 23.0, 93.6, 23.0);
        ctx.lineWidth(6.0);
        ctx.strokeStyle(Colours::White);
        ctx.lineCap(Canvas::LineCap::ROUND);
        ctx.lineJoin(Canvas::LineJoin::ROUND);
        ctx.stroke();

        // Nuke/Dial/High
        ctx.beginPath();
        ctx.moveTo(93.6, 23.0);
        ctx.bezierCurveTo(112.7, 23.0, 128.1, 38.5, 128.1, 57.5);
        ctx.strokeStyle(Colours::Red);
        ctx.stroke();

        // Nuke/Dial/Base
        ctx.beginPath();
        ctx.moveTo(95.4, 57.5);
        ctx.bezierCurveTo(95.4, 58.5, 94.6, 59.3, 93.6, 59.3);
        ctx.bezierCurveTo(92.6, 59.3, 91.8, 58.5, 91.8, 57.5);
        ctx.bezierCurveTo(91.8, 56.6, 92.6, 55.8, 93.6, 55.8);
        ctx.bezierCurveTo(94.6, 55.8, 95.4, 56.6, 95.4, 57.5);
        ctx.closePath();
        ctx.stroke();

        float rotation = -1.57 + engine.props.aux * M_PI;

        // Nuke/Dial/Line
        ctx.beginPath();
        ctx.rotateAround(rotation, {93.58, 57.54});
        ctx.moveTo(93.6, 57.5);
        ctx.lineTo(93.6, 37.3);
        ctx.stroke();
    });

    // waveform
    ctx.group([&] {
        // move the entire group to point x,y
        ctx.translate(60,102);
        //
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

        std::valarray<vec> const pw_square = {{0, 1}, {0, 1}, {0, 0}, {2, 0}, {2, 1},
                                              {2, 1}, {2, 0}, {4, 0}, {4, 1}};
        std::valarray<vec> const square = {{0, 1}, {1, 1}, {1, 0}, {2, 0}, {2, 1},
                                           {3, 1}, {3, 0}, {4, 0}, {4, 1}};
        std::valarray<vec> const below_triangle = {{4 / 5, 1},     {4 / 5, 1},     {2 * 4 / 5, 0},
                                                   {2 * 4 / 5, 0}, {3 * 4 / 5, 1}, {3 * 4 / 5, 1},
                                                   {4 * 4 / 5, 0}, {4 * 4 / 5, 0}, {4, 1}};
        std::valarray<vec> const triangle = {{4 / 5, 1},     {2 * 4 / 5, 0}, {3 * 4 / 5, 1},
                                             {3 * 4 / 5, 1}, {3 * 4 / 5, 1}, {4 * 4 / 5, 0},
                                             {4, 1},         {4, 1},         {4, 1}};
        std::valarray<vec> const saw = {{0, 1}, {2, 0}, {2, 1}, {2, 1}, {2, 1},
                                        {4, 0}, {4, 1}, {4, 1}, {4, 1}};
        std::valarray<vec> const hs_saw = {{0, 1}, {1, 0}, {1, 1}, {2, 0}, {2, 1},
                                           {3, 0}, {3, 1}, {4, 0}, {4, 1}};

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
        ctx.lineWidth(6.0);
        ctx.plotLines(std::begin(points), std::end(points));
        ctx.stroke(Colours::Blue);
    });

    // hazard sign
    ctx.group([&] {
        // b=bottom l=left r=right
        //rotation value
        float hazardrotationvalueL = 0 + engine.props.relation * 0.3 ;
        float hazardrotationvalueR = 0 - engine.props.relation * 0.3 ;

        // nuke/B > L
        ctx.group([&]{
            ctx.beginPath();
            ctx.rotateAround({hazardrotationvalueL},{93.6,172.6});
            ctx.moveTo(93.6, 180.6);
            ctx.lineTo(93.6, 198.1);
            ctx.closePath();
            ctx.lineWidth(6.0);
            ctx.strokeStyle(Colours::Yellow);
            ctx.lineCap(Canvas::LineCap::ROUND);
            ctx.lineJoin(Canvas::LineJoin::ROUND);
            ctx.stroke();
        });
        // nuke/B > R
        ctx.group([&]{
            ctx.beginPath();
            ctx.rotateAround({hazardrotationvalueR},{93.6,172.6});
            ctx.moveTo(93.6, 180.6);
            ctx.lineTo(93.6, 198.1);
            ctx.closePath();
            ctx.lineWidth(6.0);
            ctx.strokeStyle(Colours::Yellow);
            ctx.lineCap(Canvas::LineCap::ROUND);
            ctx.lineJoin(Canvas::LineJoin::ROUND);
            ctx.stroke();
        });

        // nuke/R > L
        ctx.group([&]{
            ctx.beginPath();
            ctx.rotateAround({hazardrotationvalueL},{93.6,172.6});
            ctx.moveTo(100.5, 168.6);
            ctx.lineTo(115.6, 159.9);
            ctx.lineWidth(6.0);
            ctx.strokeStyle(Colours::Yellow);
            ctx.lineCap(Canvas::LineCap::ROUND);
            ctx.lineJoin(Canvas::LineJoin::ROUND);
            ctx.stroke();
        });

        // nuke/R > R
        ctx.group([&]{
            ctx.beginPath();
            ctx.rotateAround({hazardrotationvalueR},{93.6,172.6});
            ctx.moveTo(100.5, 168.6);
            ctx.lineTo(115.6, 159.9);
            ctx.lineWidth(6.0);
            ctx.strokeStyle(Colours::Yellow);
            ctx.lineCap(Canvas::LineCap::ROUND);
            ctx.lineJoin(Canvas::LineJoin::ROUND);
            ctx.stroke();
        });

        // nuke/L > L
        ctx.group([&]{
            ctx.beginPath();
            ctx.rotateAround({hazardrotationvalueL},{93.6,172.6});
            ctx.moveTo(86.7, 168.6);
            ctx.lineTo(71.5, 159.9);
            ctx.lineWidth(6.0);
            ctx.strokeStyle(Colours::Yellow);
            ctx.lineCap(Canvas::LineCap::ROUND);
            ctx.lineJoin(Canvas::LineJoin::ROUND);
            ctx.stroke();
        });

        // nuke/L > R
        ctx.group([&]{
            ctx.beginPath();
            ctx.rotateAround({hazardrotationvalueR},{93.6,172.6});
            ctx.moveTo(86.7, 168.6);
            ctx.lineTo(71.5, 159.9);
            ctx.lineWidth(6.0);
            ctx.strokeStyle(Colours::Yellow);
            ctx.lineCap(Canvas::LineCap::ROUND);
            ctx.lineJoin(Canvas::LineJoin::ROUND);
            ctx.stroke();
        });

        // outer ring B-L
        ctx.group([&]{
            ctx.beginPath();
            //ctx.circle({93.6,172.6},26);
            ctx.rotateAround(55, {93.6, 172.6});
            ctx.arc(93.6, 172.6, 26, M_PI, (M_PI + 0.29 * engine.props.relation), false);
            ctx.lineWidth(6.0);
            ctx.strokeStyle(Colours::Yellow);
            ctx.lineCap(Canvas::LineCap::ROUND);
            ctx.lineJoin(Canvas::LineJoin::ROUND);
            ctx.stroke();
        });

        // outer ring B-R
        ctx.group([&]{
            ctx.beginPath();
            //ctx.circle({93.6,172.6},26);
            ctx.rotateAround(55, {93.6, 172.6});
            ctx.arc(93.6, 172.6, 26, M_PI, (M_PI - 0.29 * engine.props.relation), true);
            ctx.lineWidth(6.0);
            ctx.strokeStyle(Colours::Yellow);
            ctx.lineCap(Canvas::LineCap::ROUND);
            ctx.lineJoin(Canvas::LineJoin::ROUND);
            ctx.stroke();
        });

        // outer ring L-L
        ctx.group([&]{
            ctx.beginPath();
            //ctx.circle({93.6,172.6},26);
            ctx.rotateAround(119.9, {93.6, 172.6});
            ctx.arc(93.6, 172.6, 26, M_PI, (M_PI + 0.29 * engine.props.relation), false);
            ctx.lineWidth(6.0);
            ctx.strokeStyle(Colours::Yellow);
            ctx.lineCap(Canvas::LineCap::ROUND);
            ctx.lineJoin(Canvas::LineJoin::ROUND);
            ctx.stroke();
        });

        // outer ring L-R
        ctx.group([&]{
            ctx.beginPath();
            //ctx.circle({93.6,172.6},26);
            ctx.rotateAround(119.9, {93.6, 172.6});
            ctx.arc(93.6, 172.6, 26, M_PI, (M_PI - 0.29 * engine.props.relation), true);
            ctx.lineWidth(6.0);
            ctx.strokeStyle(Colours::Yellow);
            ctx.lineCap(Canvas::LineCap::ROUND);
            ctx.lineJoin(Canvas::LineJoin::ROUND);
            ctx.stroke();
        });


        // outer ring R-L
        ctx.group([&]{
            ctx.beginPath();
            //ctx.circle({93.6,172.6},26);
            ctx.rotateAround(122, {93.6, 172.6});
            ctx.arc(93.6, 172.6, 26, M_PI, (M_PI + 0.29 * engine.props.relation), false);
            ctx.lineWidth(6.0);
            ctx.strokeStyle(Colours::Yellow);
            ctx.lineCap(Canvas::LineCap::ROUND);
            ctx.lineJoin(Canvas::LineJoin::ROUND);
            ctx.stroke();
        });

        // outer ring R-R
        ctx.group([&]{
            ctx.beginPath();
            //ctx.circle({93.6,172.6},26);
            ctx.rotateAround(122, {93.6, 172.6});
            ctx.arc(93.6, 172.6, 26, M_PI, (M_PI - 0.29 * engine.props.relation), true);
            ctx.lineWidth(6.0);
            ctx.strokeStyle(Colours::Yellow);
            ctx.lineCap(Canvas::LineCap::ROUND);
            ctx.lineJoin(Canvas::LineJoin::ROUND);
            ctx.stroke();
        });

        // Nuke/NukeHazard/MiddleCircle
        ctx.restore();
        ctx.beginPath();
        ctx.moveTo(101.6, 172.6);
        ctx.bezierCurveTo(101.6, 177.0, 98.0, 180.6, 93.6, 180.6);
        ctx.bezierCurveTo(89.2, 180.6, 85.6, 177.0, 85.6, 172.6);
        ctx.bezierCurveTo(85.6, 168.2, 89.2, 164.6, 93.6, 164.6);
        ctx.bezierCurveTo(98.0, 164.6, 101.6, 168.2, 101.6, 172.6);
        ctx.closePath();
        ctx.lineWidth(6.0);
        ctx.strokeStyle(Colours::Yellow);
        ctx.lineCap(Canvas::LineCap::ROUND);
        ctx.lineJoin(Canvas::LineJoin::ROUND);
        ctx.stroke();
    });

    // key
    ctx.group([&] {
        // Nuke/Key
        ctx.beginPath();
        ctx.moveTo(228.8, 54.5);
        ctx.bezierCurveTo(228.8, 59.2, 225.0, 63.0, 220.3, 63.0);
        ctx.bezierCurveTo(215.6, 63.0, 211.8, 59.2, 211.8, 54.5);
        ctx.bezierCurveTo(211.8, 49.8, 215.6, 46.0, 220.3, 46.0);
        ctx.bezierCurveTo(225.0, 46.0, 228.8, 49.8, 228.8, 54.5);
        ctx.closePath();
        ctx.lineWidth(6.0);
        ctx.strokeStyle(Colours::Pink);
        ctx.lineCap(Canvas::LineCap::ROUND);
        ctx.lineJoin(Canvas::LineJoin::ROUND);
        ctx.stroke();

        // Nuke/Key/Base
        ctx.beginPath();
        ctx.moveTo(228.8, 54.5);
        ctx.lineTo(268.6, 54.5);
        ctx.stroke();

        // Nuke/Key/Tooth 2
        ctx.beginPath();
        ctx.moveTo(260.6, 54.5);
        ctx.lineTo(260.6, 63.0);
        ctx.stroke();

        // Nuke/Key/Tooth 1
        ctx.beginPath();
        ctx.moveTo(249.6, 54.5);
        ctx.lineTo(249.6, 63.0);
        ctx.stroke();

        // Nuke/Key/Fill
        ctx.beginPath();
        ctx.moveTo(225.4, 47.7);
        ctx.lineTo(225.4, 61.1);
        ctx.stroke();
    });

    // Nuke/Separator
    ctx.beginPath();
    ctx.moveTo(55.1, 131.6);
    ctx.lineTo(132.0, 131.6);
    ctx.lineWidth(6.0);
    ctx.strokeStyle(Colours::Gray50);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.stroke();

    // Nuke/Green
    ctx.beginPath();
    ctx.moveTo(210.1, 157.2);
    ctx.lineTo(240.8, 162.8);
    ctx.bezierCurveTo(251.1, 164.7, 259.2, 173.3, 259.7, 183.8);
    ctx.bezierCurveTo(259.7, 184.3, 259.8, 184.7, 259.8, 185.2);
    ctx.lineTo(259.8, 187.3);
    ctx.strokeStyle(Colours::Green);
    ctx.stroke();
}
} // namespace otto::engines

// namespace otto::engines
