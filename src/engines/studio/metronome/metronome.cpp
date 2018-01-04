#include "metronome.hpp"

#include "core/globals.hpp"
#include "core/audio/audio_manager.hpp"
#include "core/engines/engine_manager.hpp"
#include <string>
#include <cmath>

#include "metronome.faust.h"

#include "util/timer.hpp"

namespace otto::engines {
  struct MetronomeScreen : EngineScreen<Metronome> {
    void drawMetronome(ui::vg::Canvas&);

    using EngineScreen<Metronome>::EngineScreen;

    void rotary(ui::RotaryEvent) override;

    void draw(ui::vg::Canvas&) override;
  };

  Metronome::Metronome()
    : Engine("Metronome", props, std::make_unique<MetronomeScreen>(this)),
      audio::FaustWrapper<0, 1>(std::make_unique<FAUSTCLASS>(), props)
  {}

  Metronome::~Metronome() {}

  audio::ProcessData<1> Metronome::process(audio::ProcessData<0> data) {
    TIME_SCOPE("Metronome::process");

    float BPsample = props.bpm / 60.0 / (float) audio::samplerate();
    float beat = engines::tapeState::position() * BPsample;
    int framesTillNext = std::fmod(beat, 1)/BPsample * engines::tapeState::playSpeed();

    if (framesTillNext < data.nframes
      && engines::tapeState::playing()
      && engines::tapeState::playSpeed()/BPsample > 1) {
      FaustWrapper::process(data.slice(0, framesTillNext));
      props.trigger = true;
      FaustWrapper::process(data.slice(framesTillNext));
      props.trigger = false;
    } else {
      FaustWrapper::process(data);
    }

    for (auto frm : FaustWrapper::proc_buf) {
      graph.add(frm[0]);
    }

    return data.redirect(FaustWrapper::proc_buf);
  }

  // Bars
  BeatPos Metronome::closestBar(TapeTime time) {
    double fpb = (audio::samplerate())*60/(double)props.bpm;
    BeatPos prevBar = time/fpb;
    TapeTime prevBarTime = getBarTime(prevBar);
    if (time - prevBarTime > fpb/2) {
      return prevBar + 1;
    }
    return prevBar;
  }

  TapeTime Metronome::getBarTime(BeatPos bar) {
    double fpb = (audio::samplerate())*60/(double)props.bpm;
    return bar * fpb;
  }

  TapeTime Metronome::getBarTimeRel(BeatPos bar) {
    if (bar == 0) {
      return closestBar(engines::tapeState::position());
    }

    double fpb = (audio::samplerate())*60/(double)props.bpm;
    BeatPos curBar = engines::tapeState::position()/fpb;
    TapeTime curBarTime = getBarTime(curBar);
    TapeTime diff = engines::tapeState::position() - curBarTime;
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
    float fpb = (audio::samplerate())*60/(float)props.bpm;
    return time / fpb;
  }

  std::size_t Metronome::time_for_bar(float bar) const
  {
    float fpb = (audio::samplerate())*60/(float)props.bpm;
    return bar * fpb;
  }

  void MetronomeScreen::rotary(ui::RotaryEvent e) {
    switch(e.rotary) {
    case ui::Rotary::Red:
      engine.props.gain.step(e.clicks); break;
    case ui::Rotary::Blue:
      engine.props.bpm.step(e.clicks); break;
    case ui::Rotary::Green:
      engine.props.tone.step(e.clicks); break;
    case ui::Rotary::White:
      break;
    }
  }

  void MetronomeScreen::draw(ui::vg::Canvas &ctx) {
    using namespace ui::vg;

    ctx.lineJoin(Canvas::LineJoin::ROUND);
    ctx.lineCap(Canvas::LineCap::ROUND);

    ctx.save();
    ctx.translate(110, 40);
    drawMetronome(ctx);
    ctx.restore();

    {
      // Tone meter
      ctx.save();
      float y = 180 - engine.props.tone.mode.normalize() * 140;
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
      float y = 180 - engine.graph * 140;
      float x = 280;
      engine.graph.clear();
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
      ctx.circle(x, 180 - engine.props.gain.mode.normalize() * 140, 3);
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
  void MetronomeScreen::drawMetronome(ui::vg::Canvas &ctx) {
    using namespace ui::vg;
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

      float BPsample(engine.props.bpm/60.0/(float)audio::samplerate());
      float beat(engines::tapeState::position() * BPsample);
      float factor((std::fmod(beat, 2)));
      factor = factor < 1 ? (factor * 2 - 1) : ((1 - factor) * 2 + 1);
      factor = std::sin(factor * M_PI/2);
      factor *= 0.2 + 0.8 * (1 - engine.props.bpm.mode.normalize());
      // float a(1);
      // factor(factor > 0 ? smoothMotion(factor, a) : -smoothMotion(-factor, a));
      float rotation(factor * M_PI/3);

      ctx.translate(50, 105);
      ctx.rotate(rotation);
      ctx.translate(-50, -105);

      ctx.strokeStyle(Colours::Blue);
      ctx.lineWidth(2);

      // PENDULUM
      float y(75 * engine.props.bpm.mode.normalize());
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
    ctx.fillText(std::to_string((int)engine.props.bpm), 50, 120);

  }

}
