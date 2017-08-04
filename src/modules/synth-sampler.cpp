#include "synth-sampler.h"

#include <algorithm>

#include "../utils.h"
#include "../ui/utils.h"
#include "../ui/icons.h"
#include "../globals.h"
#include "../util/sndfile.h"
#include "../util/match.h"

namespace module {

SynthSampler::SynthSampler() :
  SynthModule(&data),
  maxSampleSize (16 * GLOB.samplerate),
  sampleData (maxSampleSize),
  editScreen (new SynthSampleScreen(this)) {

  GLOB.events.samplerateChanged.add([&] (uint sr) {
    maxSampleSize = 16 * sr;
    sampleSpeed = sampleSampleRate / float(sr);
  });

}

void SynthSampler::process(uint nframes) {
  for (auto &&nEvent : GLOB.midiEvents) {
    nEvent.match([&] (NoteOnEvent *e) {
       if (e->channel == 0) {
         data.playProgress = (data.fwd()) ? 0 : data.length() - 1;
         data.trigger = true;
       }
    }, [] (MidiEvent *) {});
  }

  float playSpeed = data.speed * sampleSpeed;

  // Process audio
  if (data.playProgress >= 0 && playSpeed > 0) {
    if (data.fwd()) {
      if (data.loop() && data.trigger) {
        for(int i = 0; i < nframes; ++i) {
          GLOB.audioData.proc[i] += sampleData[data.in + data.playProgress];
          data.playProgress += playSpeed;
          if (data.playProgress >= data.length()) {
            data.playProgress = 0;
          }
        }
      } else {
        int frms = std::min<int>(nframes, data.length() - data.playProgress);
        for(int i = 0; i < frms; ++i) {
          GLOB.audioData.proc[i] += sampleData[data.in + data.playProgress];
          data.playProgress += playSpeed;
        }
        if (data.playProgress >= data.length()) {
          data.playProgress = -1;
        }
      }
    } else {
      if (data.loop() && data.trigger) {
        for(int i = 0; i < nframes; ++i) {
          GLOB.audioData.proc[i] += sampleData[data.in + data.playProgress];
          data.playProgress -= playSpeed;
          if (data.playProgress < 0) {
            data.playProgress = data.length() -1;
          }
        }
      } else {
        int frms = std::min<int>(nframes, data.playProgress);
        for(int i = 0; i < frms; ++i) {
          GLOB.audioData.proc[i] += sampleData[data.in + data.playProgress];
          data.playProgress -= playSpeed;
        }
      }
    }
  }

  for (auto &&nEvent : GLOB.midiEvents) {
    nEvent.match([&] (NoteOffEvent *e) {
       if (e->channel == 0) {
         data.trigger = false;
         if (data.stop()) {
           data.playProgress = -1;
         }
       }
    }, [] (MidiEvent *) {});
  };
}

void SynthSampler::display() {
  GLOB.ui.display(editScreen);
}

void SynthSampler::load() {
  top1::SndFile<1> sf (samplePath(data.sampleName));

  size_t rs = std::min(maxSampleSize, sf.size());

  sampleData.resize(rs);
  sf.read(sampleData.data(), rs);

  sampleSampleRate = sf.samplerate;
  sampleSpeed = sampleSampleRate / float(GLOB.samplerate);

  data.in.max = rs;
  data.out.max = rs;

  // Auto assign voices
  if (data.in < 0 || data.out >= rs) {
    data.in = 0;
    data.out = rs;
  }

  auto &mwf = editScreen->mainWF;
  mwf->clear();
  for (auto &&s : sampleData) {
    mwf->addFrame(s);
  }

  auto &wf = editScreen->topWF;
  wf->clear();
  for (auto &&s : sampleData) {
    wf->addFrame(s);
  }
  editScreen->topWFW.viewRange = {0, wf->size() - 1};

  if (sf.size() == 0) LOGI << "Empty sample file";
  sf.close();
}

void SynthSampler::init() {
  load();
}
}

/****************************************/
/* SampleEditScreen                     */
/****************************************/

bool module::SynthSampleScreen::keypress(ui::Key key) {
  using namespace ui;
  auto& data = module->data;
  switch (key) {
  case K_BLUE_UP: data.in.inc(); return true;
  case K_BLUE_DOWN: data.in.dec(); return true;
  case K_GREEN_UP: data.out.inc(); return true;
  case K_GREEN_DOWN: data.out.dec(); return true;
  case K_WHITE_UP: data.speed.inc(); return true;
  case K_WHITE_DOWN: data.speed.dec(); return true;
  case K_WHITE_CLICK: data.speed.reset(); return true;
  case K_RED_UP: data.mode.inc(); return true;
  case K_RED_DOWN: data.mode.dec(); return true;
  }
}

namespace drawing {

const static drawing::Size topWFsize = {210, 20};
const static drawing::Point topWFpos = {60, 20};
const static drawing::Size arrowSize = {20, 20};
const static drawing::Point arrowPos = {280, 20};
const static drawing::Size pitchSize = {30, 20};
const static drawing::Point pitchPos = {20, 40};
const static drawing::Size mainWFsize = {280, 170};
const static drawing::Point mainWFpos = {20, 50};

namespace Colours {

const Colour TopWF = Blue.dim(0.2);
const Colour TopWFCur = Blue.brighten(0.5);
const Colour TopWFActive = White;
const Colour WFGrid = 0x303040;
}
}

module::SynthSampleScreen::SynthSampleScreen(SynthSampler *m) :
  ModuleScreen (m),
  topWF (new Waveform(
     module->sampleData.size() / drawing::topWFsize.w / 4.0, 1.0)
         ),
  topWFW (topWF, drawing::topWFsize),
  mainWF (new Waveform(50, 1.0)),
  mainWFW (mainWF, drawing::mainWFsize) {}

void module::SynthSampleScreen::draw(drawing::Canvas &ctx) {
  using namespace drawing;

  Colour colourCurrent;
  auto& data = module->data;

  ctx.callAt(topWFpos, [&] () {
    topWFW.drawRange(ctx, topWFW.viewRange, Colours::TopWF);
    Colour baseColour = Colours::TopWFCur;
    float mix = data.playProgress / float(data.out - data.in);

    if (mix < 0) mix = 1;
    if (data.fwd()) mix = 1 - mix; //data is not reversed

    colourCurrent = baseColour.mix(Colours::TopWFActive, mix);
    topWFW.drawRange(ctx, {
        std::size_t(std::round(data.in / topWF->ratio)),
        std::size_t(std::round(data.out / topWF->ratio))
      }, colourCurrent);
  });

  icons::Arrow icon;

  if (data.fwd()) {
    icon.dir = icons::Arrow::Right;
  } else {
    icon.dir = icons::Arrow::Left;
  }

  if (data.stop()) {
    icon.stopped = true;
  }

  if (data.loop()) {
    icon.looping = true;
  }

  icon.size = arrowSize;
  icon.colour = Colours::Red;
  ctx.drawAt(arrowPos, icon);

  ctx.beginPath();
  ctx.fillStyle(Colours::White);
  ctx.font(FONT_NORM);
  ctx.font(15);
  ctx.textAlign(TextAlign::Left, TextAlign::Baseline);
  ctx.fillText(fmt::format("×{:.2F}", data.speed.get()), pitchPos);

  ctx.callAt(
    mainWFpos, [&] () {

    mainWFW.lineCol = colourCurrent;
    mainWFW.minPx = 5;
    mainWFW.viewRange = {
      std::size_t(std::round(data.in / mainWF->ratio)),
      std::size_t(std::round(data.out / mainWF->ratio))};

    mainWFW.draw(ctx);

    ctx.beginPath();
    ctx.circle(mainWFW.point(mainWFW.viewRange.in), 2);
    ctx.fill(Colours::Blue);

    ctx.beginPath();
    ctx.circle(mainWFW.point(mainWFW.viewRange.in), 5);
    ctx.stroke(Colours::Blue);

    ctx.beginPath();
    ctx.circle(mainWFW.point(mainWFW.viewRange.out), 2);
    ctx.fill(Colours::Green);

    ctx.beginPath();
    ctx.circle(mainWFW.point(mainWFW.viewRange.out), 5);
    ctx.stroke(Colours::Green);
  });

}
