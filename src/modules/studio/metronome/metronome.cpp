#include "metronome.hpp"

#include "core/globals.hpp"
#include <string>
#include <cmath>

#include "metronome.faust.h"

#include "util/timer.hpp"

namespace top1::modules {

  using TapeTime = unsigned;

  class MetronomeScreen : public ui::ModuleScreen<Metronome> {

    void drawMetronome(ui::drawing::Canvas&);

  public:
    using ui::ModuleScreen<Metronome>::ModuleScreen;

    void rotary(ui::RotaryEvent) override;

    void draw(ui::drawing::Canvas&) override;

  };

  Metronome::Metronome()
    : Module(&props),
      audio::FaustWrapper(std::make_unique<FAUSTCLASS>(), props),
    screen (std::make_unique<MetronomeScreen>(this))
  {
  }

  Metronome::~Metronome() {}

  void Metronome::process(const audio::ProcessData& data) {
    TIME_SCOPE("Metronome::process");
    float BPsample = props.bpm/60.0/(float)Globals::samplerate;
    float beat = Globals::tapedeck.position() * BPsample;
    int framesTillNext = std::fmod(beat, 1)/BPsample * Globals::tapedeck.state.playSpeed;

    if (framesTillNext < data.nframes
      && Globals::tapedeck.state.playing()
      && Globals::tapedeck.state.playSpeed/BPsample > 1) {
      FaustWrapper::process({buf.data(), framesTillNext});
      props.trigger = true;
      FaustWrapper::process({buf.data(), data.nframes - framesTillNext});
      props.trigger = false;
    } else {
      FaustWrapper::process({buf.data(), data.nframes});
    }
    indexed_for(buf.begin(), buf.end(), [&](float f, auto i) {
        graph.add(f);
        data.audio.outL[i] += f;
        data.audio.outR[i] += f;
      });
  }

  void Metronome::display() {
    Globals::ui.display(*screen);
  }

  // Bars
  BeatPos Metronome::closestBar(TapeTime time) {
    double fpb = (Globals::samplerate)*60/(double)props.bpm;
    BeatPos prevBar = time/fpb;
    TapeTime prevBarTime = getBarTime(prevBar);
    if (time - prevBarTime > fpb/2) {
      return prevBar + 1;
    }
    return prevBar;
  }

  TapeTime Metronome::getBarTime(BeatPos bar) {
    double fpb = (Globals::samplerate)*60/(double)props.bpm;
    return bar * fpb;
  }

  TapeTime Metronome::getBarTimeRel(BeatPos bar) {
    if (bar == 0) return closestBar(Globals::tapedeck.position());
    double fpb = (Globals::samplerate)*60/(double)props.bpm;
    BeatPos curBar = Globals::tapedeck.position()/fpb;
    TapeTime curBarTime = getBarTime(curBar);
    TapeTime diff = Globals::tapedeck.position() - curBarTime;
    if (diff > fpb/2) {
      curBar += 1;
      if (bar > 0) bar -= 1;
    } else if (diff > 0) {
      if (bar < 0) bar += 1;
    }
    return getBarTime(curBar + bar);
  }

  float Metronome::bar_for_time(std::size_t time) const
  {
    float fpb = (Globals::samplerate)*60/(float)props.bpm;
    return time / fpb;
  }

  std::size_t Metronome::time_for_bar(float bar) const
  {
    float fpb = (Globals::samplerate)*60/(float)props.bpm;
    return bar * fpb;
  }

  void MetronomeScreen::rotary(ui::RotaryEvent e) {
    switch(e.rotary) {
    case ui::Rotary::Red:
      module->props.gain.step(e.clicks); break;
    case ui::Rotary::Blue:
      module->props.bpm.step(e.clicks); break;
    case ui::Rotary::Green:
      module->props.tone.step(e.clicks); break;
    case ui::Rotary::White:
      break;
    }
  }

  void MetronomeScreen::draw(ui::drawing::Canvas &ctx) {
    using namespace ui::drawing;

    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.lineCap(Canvas::LineCap::ROUND);

    ctx.save();
    ctx.translate(110, 40);
    drawMetronome(ctx);
    ctx.restore();

    {
      // Tone meter
      ctx.save();
      float y = 180 - module->props.tone.mode.normalize() * 140;
      float x = 40;
      ctx.strokeStyle(Colours::Green.dimmed);
      ctx.lineCap(Canvas::LineCap::ROUND);
      ctx.beginPath();
      ctx.moveTo(x, 40);
      ctx.lineTo(x, y);
      ctx.stroke();
      ctx.strokeStyle(Colours::Green);
      ctx.beginPath();
      ctx.moveTo(x, y);
      ctx.lineTo(x, 180);
      ctx.stroke();
      ctx.fillStyle(Colours::Green);
      ctx.beginPath();
      ctx.circle(x, y, 3);
      ctx.fill();
      ctx.restore();
    }

    {
      // Gain meter
      ctx.save();
      float y = 180 - module->graph * 140;
      float x = 280;
      module->graph.clear();
      ctx.beginPath();
      ctx.lineCap(Canvas::LineCap::ROUND);
      ctx.strokeStyle(Colours::Red.dimmed);
      ctx.moveTo(x, 40);
      ctx.lineTo(x, y);
      ctx.stroke();
      ctx.strokeStyle(Colours::Red);
      ctx.beginPath();
      ctx.moveTo(x, y);
      ctx.lineTo(x, 180);
      ctx.stroke();
      ctx.fillStyle(Colours::Red);
      ctx.beginPath();
      ctx.circle(x, 180 - module->props.gain.mode.normalize() * 140, 3);
      ctx.fill();
      ctx.restore();
    }

    // Labels
    ctx.beginPath();
    ctx.font(Fonts::Light);
    ctx.font(25);
    ctx.textAlign(TextAlign::Left, TextAlign::Middle);
    ctx.fillStyle(Colours::Green);
    ctx.fillText("TONE", 20, 210);

    ctx.beginPath();
    ctx.font(Fonts::Light);
    ctx.font(25);
    ctx.textAlign(TextAlign::Center, TextAlign::Middle);
    ctx.fillStyle(Colours::Blue);
    ctx.fillText("BPM", 160, 210);

    ctx.beginPath();
    ctx.font(Fonts::Light);
    ctx.font(25);
    ctx.textAlign(TextAlign::Right, TextAlign::Middle);
    ctx.fillStyle(Colours::Red);
    ctx.fillText("GAIN", 300, 210);

  }
  void MetronomeScreen::drawMetronome(ui::drawing::Canvas &ctx) {
    using namespace ui::drawing;
    // Metronome Background
    {
      ctx.save();

      // #BG_BOX
      ctx.beginPath();
      ctx.strokeStyle(Colours::Gray60);
      ctx.lineWidth(2);
      ctx.moveTo(42, 100);
      ctx.lineTo(42, 5);
      ctx.lineTo(58, 5);
      ctx.lineTo(58, 100);
      ctx.stroke();

      // #Outline_Top
      ctx.beginPath();
      ctx.strokeStyle(Colours::Gray70);
      ctx.lineWidth(2);
      ctx.moveTo(10, 100);
      ctx.lineTo(35, 0);
      ctx.lineTo(65, 0);
      ctx.lineTo(90, 100);
      ctx.stroke();

      ctx.restore();
    }

    // Pendulum
    {
      ctx.save();

      float BPsample(module->props.bpm/60.0/(float)Globals::samplerate);
      float beat(Globals::tapedeck.position() * BPsample);
      float factor((std::fmod(beat, 2)));
      factor = factor < 1 ? (factor * 2 - 1) : ((1 - factor) * 2 + 1);
      factor = std::sin(factor * M_PI/2);
      factor *= 0.2 + 0.8 * (1 - module->props.bpm.mode.normalize());
      // float a(1);
      // factor(factor > 0 ? smoothMotion(factor, a) : -smoothMotion(-factor, a));
      float rotation(factor * M_PI/3);

      ctx.translate(50, 105);
      ctx.rotate(rotation);
      ctx.translate(-50, -105);

      ctx.strokeStyle(Colours::Blue);
      ctx.lineWidth(2);

      // PENDULUM
      float y(75 * module->props.bpm.mode.normalize());
      ctx.beginPath();
      ctx.moveTo(38, 15 + y);
      ctx.lineTo(62, 15 + y);
      ctx.lineTo(58, 26 + y);
      ctx.lineTo(42, 26 + y);
      ctx.lineTo(38, 15 + y);

      // ARM
      ctx.moveTo(50, 100);
      ctx.lineTo(50, 6);
      ctx.stroke();

      ctx.restore();
    }

    // Outline Bottom
    ctx.beginPath();
    ctx.strokeStyle(Colours::Gray70);
    ctx.fillStyle(Colours::Black);
    ctx.lineWidth(2);
    ctx.moveTo(10, 101);
    ctx.lineTo(90, 101);
    ctx.lineTo(100, 141);
    ctx.lineTo(0, 141);
    ctx.lineTo(10, 101);
    ctx.fill();
    ctx.stroke();

    // BPM text
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.font(Fonts::Light);
    ctx.font(32);
    ctx.textAlign(TextAlign::Center, TextAlign::Middle);
    ctx.fillText(std::to_string((int)module->props.bpm), 50, 120);

  }

}
