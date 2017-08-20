#include "metronome.hpp"

#include "core/globals.hpp"
#include <string>
#include <cmath>

#include "metronome.faust.h"

namespace top1::module {

  Metronome::Metronome() :
    Module(&data),
    audio::FaustWrapper(new FAUSTCLASS, &data),
    screen (new MetronomeScreen(this)) {}

  void Metronome::process(audio::ProcessData& data) {
    float BPsample = this->data.bpm/60.0/(float)GLOB.samplerate;
    float beat = GLOB.tapedeck.position() * BPsample;
    uint framesTillNext = std::fmod(beat, 1)/BPsample * GLOB.tapedeck.state.playSpeed;

    if (framesTillNext < data.nframes
        && GLOB.tapedeck.state.playing()
        && GLOB.tapedeck.state.playSpeed/BPsample > 1) {
      data.process([this](auto& d){FaustWrapper::process(d);},
                   framesTillNext);
      this->data.trigger = true;
      data.process([this](audio::ProcessData& d){FaustWrapper::process(d);},
                   data.nframes - framesTillNext);
      this->data.trigger = false;
    } else {
      FaustWrapper::process(data);
    }
  }

  void Metronome::display() {
    GLOB.ui.display(screen);
  }

  void Metronome::postBuffers(audio::ProcessData& data) {
    for (uint i = 0; i < data.nframes; i++) {
      graph.add(outBuffer[0][i]);
      data.audio.outL[i] += outBuffer[0][i];
      data.audio.outR[i] += outBuffer[0][i];
    }
  }

  // Bars
  BeatPos Metronome::closestBar(TapeTime time) {
    double fpb = (GLOB.samplerate)*60/(double)data.bpm;
    BeatPos prevBar = time/fpb;
    TapeTime prevBarTime = getBarTime(prevBar);
    if (time - prevBarTime > fpb/2) {
      return prevBar + 1;
    }
    return prevBar;
  }

  TapeTime Metronome::getBarTime(BeatPos bar) {
    double fpb = (GLOB.samplerate)*60/(double)data.bpm;
    return bar * fpb;
  }

  TapeTime Metronome::getBarTimeRel(BeatPos bar) {
    if (bar == 0) return closestBar(GLOB.tapedeck.position());
    double fpb = (GLOB.samplerate)*60/(double)data.bpm;
    BeatPos curBar = GLOB.tapedeck.position()/fpb;
    TapeTime curBarTime = getBarTime(curBar);
    TapeTime diff = GLOB.tapedeck.position() - curBarTime;
    if (diff > fpb/2) {
      curBar += 1;
      if (bar > 0) bar -= 1;
    } else if (diff > 0) {
      if (bar < 0) bar += 1;
    }
    return getBarTime(curBar + bar);
  }

  bool MetronomeScreen::keypress(ui::Key key) {
    using namespace ui;
    switch (key) {
    case K_RED_UP:
      module->data.gain.inc();
      return true;
    case K_RED_DOWN:
      module->data.gain.dec();
      return true;
    case K_BLUE_UP:
      module->data.bpm.inc();
      return true;
    case K_BLUE_DOWN:
      module->data.bpm.dec();
      return true;
    case K_GREEN_UP:
      module->data.tone.inc();
      return true;
    case K_GREEN_DOWN:
      module->data.tone.dec();
      return true;
    default:
      return false;
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
      float y = 180 - module->data.tone.normalized() * 140;
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
      ctx.circle(x, 180 - module->data.gain.normalized() * 140, 3);
      ctx.fill();
      ctx.restore();
    }

    // Labels
    ctx.beginPath();
    ctx.font(FONT_LIGHT);
    ctx.font(25);
    ctx.textAlign(TextAlign::Left, TextAlign::Middle);
    ctx.fillStyle(Colours::Green);
    ctx.fillText("TONE", 20, 210);

    ctx.beginPath();
    ctx.font(FONT_LIGHT);
    ctx.font(25);
    ctx.textAlign(TextAlign::Center, TextAlign::Middle);
    ctx.fillStyle(Colours::Blue);
    ctx.fillText("BPM", 160, 210);

    ctx.beginPath();
    ctx.font(FONT_LIGHT);
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

      float BPsample(module->data.bpm/60.0/(float)GLOB.samplerate);
      float beat(GLOB.tapedeck.position() * BPsample);
      float factor((std::fmod(beat, 2)));
      factor = factor < 1 ? (factor * 2 - 1) : ((1 - factor) * 2 + 1);
      factor = std::sin(factor * M_PI/2);
      factor *= 0.2 + 0.8 * (1 - module->data.bpm.normalized());
      // float a(1);
      // factor(factor > 0 ? smoothMotion(factor, a) : -smoothMotion(-factor, a));
      float rotation(factor * M_PI/3);

      ctx.translate(50, 105);
      ctx.rotate(rotation);
      ctx.translate(-50, -105);

      ctx.strokeStyle(Colours::Blue);
      ctx.lineWidth(2);

      // PENDULUM
      float y(75 * module->data.bpm.normalized());
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
    ctx.font(FONT_LIGHT);
    ctx.font(32);
    ctx.textAlign(TextAlign::Center, TextAlign::Middle);
    ctx.fillText(std::to_string((int)module->data.bpm), 50, 120);

  }

}
