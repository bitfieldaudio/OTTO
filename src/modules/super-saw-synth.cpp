#include <string>

#include "core/ui/drawing.hpp"
#include "modules/super-saw-synth.hpp"
#include "modules/super-saw-synth.faust.h"

#include "core/globals.hpp"

#include "util/math.hpp"

namespace top1::modules {

  void SuperSawSynth::display() {
    Globals::ui.display(*screen);
  }

  void SuperSawSynth::process(audio::ProcessData& data) {
    for (auto &&nEvent : data.midi) {
      nEvent.match([&] (midi::NoteOnEvent *e) {
          if (e->channel == 0) {
            props.key = e->key;
            props.trigger = 1;
            props.velocity = float(e->velocity)/128.f;
          }
        }, [] (auto) {});
    }
    FaustSynthModule::process(data);
    for (auto &&nEvent : data.midi) {
      nEvent.match([&] (midi::NoteOffEvent *e) {
          if (e->channel == 0) {
            if (e->key == props.key) {
              props.trigger = 0;
            }
          }
        }, [] (auto) {});
    };
  }

} // top1::modules

  /****************************************/
  /* Screen drawing                       */
  /****************************************/

namespace top1::ui::drawing {

  class HandSaw : public Drawable {
  public:

    Colour HandleStroke = Colours::Red;
    Colour HandleFill = Colours::Black;
    Colour BladeStroke = Colours::Green;
    Colour BladeFill = Colours::Black;

    float toothSize = 4; // px

    void draw(Canvas& ctx) override {
      // Saw blade
      ctx.beginPath();
      ctx.strokeStyle(BladeStroke);
      ctx.fillStyle(BladeFill);
      ctx.moveTo(145, 8);
      ctx.lineTo(0, 37);
      ctx.lineTo(2, 48);
      { // Teeth
        const float length = 164;
        float nTeeth = length / toothSize;
        nTeeth = (int) nTeeth; // Round to fit, no half teeth
        float rToothSize = length / nTeeth;
        const float y = 48 - 2;
        float x = 6;
        ctx.lineTo(4, 48);
        for (int i = 0; i < nTeeth; i++) {
          ctx.lineTo(x, 48);
          ctx.lineTo(x, y);
          x = 6 + i * rToothSize;
        }
        ctx.lineTo(x, 48);
        ctx.lineTo(170, 48);
      }
      ctx.lineTo(172, 43);
      ctx.pathWinding(Winding::CW);
      ctx.moveTo(9 + 2, 42);
      ctx.arc(9, 42, 2, 0, 6.28318531, 1);
      ctx.fill();
      ctx.stroke();

      // Saw handle
      ctx.beginPath();
      ctx.strokeStyle(HandleStroke);
      ctx.fillStyle(HandleFill);
      ctx.moveTo(179, 0);
      ctx.lineTo(144, 6);
      ctx.lineTo(148, 31);
      ctx.lineTo(171, 45);
      ctx.lineTo(199, 38);
      ctx.lineTo(179, 0);
      ctx.pathWinding(Winding::CW);
      ctx.moveTo(172, 11);
      ctx.lineTo(185, 34);
      ctx.lineTo(177, 36);
      ctx.lineTo(164, 23);
      ctx.lineTo(164, 12);
      ctx.lineTo(172, 11);
      ctx.fill();
      ctx.stroke();
    }
  };
} // top1::ui::drawing

namespace top1::modules {
  // SuperSawSynthScreen definition
  class SuperSawSynthScreen : public ui::ModuleScreen<SuperSawSynth> {

    // Drawing data
    ui::drawing::HandSaw saws[4];

    virtual void draw(ui::drawing::Canvas& ctx) override;
    virtual bool keypress(ui::Key key) override;
    virtual void rotary(ui::RotaryEvent e) override;

  public:
    using ui::ModuleScreen<SuperSawSynth>::ModuleScreen;
  };

  bool SuperSawSynthScreen::keypress(ui::Key key) {
    switch (key) {
    default:
      return false;
    }
  }

  void SuperSawSynthScreen::rotary(ui::RotaryEvent e) {
    
  }

  // Main drawing method
  void SuperSawSynthScreen::draw(ui::drawing::Canvas& ctx) {
    using namespace ui;
    using namespace drawing;
    using math::vec;

    { // Log and saws
      Point c1 = {70, 170}; // Front circle center
      Point c2 = {250, 110}; // Back circle center
      float radius = 40;

      vec cc = vec(c2 - c1);
      vec cr = cc * (radius / cc.len()); // cc adjusted to be radius in length
      vec nc = -cr.hat(); // cr rotated 90°
      Point p1 = c1 + nc; // start of top line
      Point p2 = c1 - nc; // start of bottom line
      Point q1 = c2 + nc; // end of top line
      Point q2 = c2 - nc; // end of bottom line

      // Back circle points
      Point bc1 = q1 + cr;
      Point bc2 = c2 + cr;
      Point bc3 = q2 + cr;

      // Saw placement
      const int nSaws = 4;
      const float padding = 2.5; // Extra space added to ends of the log. unit: vbs
      vec vbs = cc / (nSaws + 1 + 2 * padding); // vector between saws

      // Draw dark half of back circle
      // ctx.beginPath();
      // ctx.moveTo(q1);
      // ctx.arcTo(bc4, bc5, radius);
      // ctx.arcTo(bc6, q2, radius);
      // ctx.stroke(Colours::Blue.dimmed);

      // Draw the rest
      ctx.beginPath();
      ctx.moveTo(q1 - vbs * (1 + padding));
      ctx.lineTo(q1);
      ctx.arcTo(bc1, bc2, radius);
      ctx.arcTo(bc3, q2, radius);
      ctx.lineTo(p2);
      ctx.stroke(Colours::Blue);

      // Draw cuts

      static float a1 = nc.angle() - M_PI; // Start angle (used for drawing the segment)
      static float a2 = cc.angle(); // End angle (used for drawing the segment)
      vec ev = vec::angleAndLen(a2, radius); // Vector from center to end point
      for (int i = nSaws - 1; i >= 0; i--) {
        Point lp1 = (i == 0) ? p1 : p1 + vbs * (i + padding); // Start of line
        Point lp2 = p1 + vbs * (i + padding + 1); // end of line
        Point ccp = lp2 - nc; // center of circle
        Point ep = ccp + ev; // segment end point

        float sawPosAmount = 1 - i % 2;// 0 is at the handle, 1 is at tip of the blade
        float sawAngleAmount = i % 2; // 0 is minAngle, 1 is maxAngle
        float sawOpacity = 0.7;
        float sawDim = 0.2 * i;

        static float sawVOffs = 4;

        Point sawPivot = lp2;
        float minAngle = vec(vec(sawPivot.x, ep.y - sawVOffs) - ep).angle();
        float maxAngle = - minAngle;
        float sawAngle = minAngle + ((maxAngle - minAngle) * sawAngleAmount);

        saws[i].BladeStroke = Colours::Green.dim(sawDim);
        saws[i].HandleStroke = Colours::Red.dim(sawDim);

        // Draw saw
        ctx.save();
        ctx.globalAlpha(sawOpacity);
        ctx.rotateAround(sawAngle, sawPivot);
        ctx.translate(ep - Point(50 + ((1 - sawPosAmount) * 90), 48 + sawVOffs));
        ctx.draw(saws[i]);
        ctx.restore();

        //Draw some black to cover the saw
        ctx.beginPath();
        ctx.moveTo(lp1 - nc);
        ctx.lineTo(lp1);
        ctx.lineTo(lp2);
        ctx.arc(ccp, radius, a1, 0);
        ctx.fill(Colours::Black);

        // Draw the strokes
        ctx.beginPath();
        ctx.moveTo(lp1);
        ctx.lineTo(lp2);
        ctx.arc(ccp, radius, a1, a2);
        ctx.stroke(Colours::Blue);
      }
      ctx.beginPath();
      ctx.circle(c1, radius);
      ctx.fill(Colours::Black);
      ctx.stroke(Colours::Blue);
    }


  }

  // SuperSawSynth Constructor, depends on SuperSawSynthScreen definition
  SuperSawSynth::SuperSawSynth() :
    FaustSynthModule (new FAUSTCLASS(), &props),
    screen (new SuperSawSynthScreen(this)) {}

}
