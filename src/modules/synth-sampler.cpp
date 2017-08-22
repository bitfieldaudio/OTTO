#include "modules/synth-sampler.hpp"

#include <algorithm>

#include "util/math.hpp"
#include "core/ui/drawing.hpp"
#include "core/ui/icons.hpp"
#include "core/globals.hpp"
#include "util/sndfile.hpp"

namespace top1::modules {

  SynthSampler::SynthSampler() :
    SynthModule(&data),
    maxSampleSize (16 * Globals::samplerate),
    sampleData (maxSampleSize),
    editScreen (new SynthSampleScreen(this)) {

    Globals::events.samplerateChanged.add([&] (uint sr) {
        maxSampleSize = 16 * sr;
        sampleSpeed = sampleSampleRate / float(sr);
      });

  }

  void SynthSampler::process(audio::ProcessData& data) {
    for (auto &&nEvent : data.midi) {
      nEvent.match([&] (midi::NoteOnEvent *e) {
          if (e->channel == 0) {
            this->data.playProgress = (this->data.fwd()) ? 0 : this->data.length() - 1;
            this->data.trigger = true;
          }
        }, [] (auto) {});
    }

    float playSpeed = this->data.speed * sampleSpeed;

    // Process audio
    if (this->data.playProgress >= 0 && playSpeed > 0) {
      if (this->data.fwd()) {
        if (this->data.loop() && this->data.trigger) {
          for(int i = 0; i < data.nframes; ++i) {
            data.audio.proc[i] += sampleData[this->data.in + this->data.playProgress];
            this->data.playProgress += playSpeed;
            if (this->data.playProgress >= this->data.length()) {
              this->data.playProgress = 0;
            }
          }
        } else {
          int frms = std::min<int>(data.nframes, this->data.length() - this->data.playProgress);
          for(int i = 0; i < frms; ++i) {
            data.audio.proc[i] += sampleData[this->data.in + this->data.playProgress];
            this->data.playProgress += playSpeed;
          }
          if (this->data.playProgress >= this->data.length()) {
            this->data.playProgress = -1;
          }
        }
      } else {
        if (this->data.loop() && this->data.trigger) {
          for(int i = 0; i < data.nframes; ++i) {
            data.audio.proc[i] += sampleData[this->data.in + this->data.playProgress];
            this->data.playProgress -= playSpeed;
            if (this->data.playProgress < 0) {
              this->data.playProgress = this->data.length() -1;
            }
          }
        } else {
          int frms = std::min<int>(data.nframes, this->data.playProgress);
          for(int i = 0; i < frms; ++i) {
            data.audio.proc[i] += sampleData[this->data.in + this->data.playProgress];
            this->data.playProgress -= playSpeed;
          }
        }
      }
    }

    for (auto &&nEvent : data.midi) {
      nEvent.match([&] (midi::NoteOffEvent *e) {
          if (e->channel == 0) {
            this->data.trigger = false;
            if (this->data.stop()) {
              this->data.playProgress = -1;
            }
          }
        }, [] (auto) {});
    };
  }

  void SynthSampler::display() {
    Globals::ui.display(editScreen);
  }

  void SynthSampler::load() {
    SndFile<1> sf (samplePath(data.sampleName));

    size_t rs = std::min(maxSampleSize, sf.size());

    sampleData.resize(rs);
    sf.read(sampleData.data(), rs);

    sampleSampleRate = sf.samplerate;
    sampleSpeed = sampleSampleRate / float(Globals::samplerate);

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
} // top1::module

namespace top1::ui::drawing {

  const static Size topWFsize = {210, 20};
  const static Point topWFpos = {60, 20};
  const static Size arrowSize = {20, 20};
  const static Point arrowPos = {280, 20};
  const static Size pitchSize = {30, 20};
  const static Point pitchPos = {20, 40};
  const static Size mainWFsize = {280, 170};
  const static Point mainWFpos = {20, 50};

  namespace Colours {

    const Colour TopWF = Blue.dim(0.2);
    const Colour TopWFCur = Blue.brighten(0.5);
    const Colour TopWFActive = White;
    const Colour WFGrid = 0x303040;
  }
} // top1::ui::drawing

namespace top1::modules {

  /****************************************/
  /* SampleEditScreen                     */
  /****************************************/

  bool SynthSampleScreen::keypress(ui::Key key) {
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
    default: return false;
    }
  }


  SynthSampleScreen::SynthSampleScreen(SynthSampler *m) :
    ui::ModuleScreen<SynthSampler> (m),
    topWF (new audio::Waveform(module->sampleData.size() / ui::drawing::topWFsize.w / 4.0, 1.0)
           ),
    topWFW (topWF, ui::drawing::topWFsize),
    mainWF (new audio::Waveform(50, 1.0)),
    mainWFW (mainWF, ui::drawing::mainWFsize) {}

  void modules::SynthSampleScreen::draw(ui::drawing::Canvas &ctx) {
    using namespace ui::drawing;

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
} // top1::module
