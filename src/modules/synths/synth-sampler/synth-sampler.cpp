#include "synth-sampler.hpp"

#include <algorithm>

#include "util/math.hpp"
#include "core/ui/drawing.hpp"
#include "core/ui/icons.hpp"
#include "core/globals.hpp"
#include "util/soundfile.hpp"

namespace top1::modules {

  SynthSampler::SynthSampler() :
    SynthModule(&props),
    maxSampleSize (16 * Globals::samplerate),
    sampleData (maxSampleSize),
    editScreen (new SynthSampleScreen(this)) {

    Globals::events.samplerateChanged.add([&] (uint sr) {
        maxSampleSize = 16 * sr;
        sampleSpeed = sampleSampleRate / float(sr);
      });

  }

  fs::path SynthSampler::samplePath(std::string name) {
    auto wav_path = Globals::data_dir / "samples" / "synth" / (name + ".wav");
    if (!fs::exists(wav_path)) {
      return Globals::data_dir / "samples" / "synth" / (name + ".aiff");
    }
    return wav_path;
  }

  void SynthSampler::process(const audio::ProcessData& data) {
    for (auto &&nEvent : data.midi) {
      nEvent.match([&] (midi::NoteOnEvent& e) {
          if (e.channel == 0) {
            props.playProgress = (props.fwd()) ? 0 : props.length() - 1;
            props.trigger = true;
          }
        }, [] (auto) {});
    }

    float playSpeed = props.speed * sampleSpeed;

    // Process audio
    if (props.playProgress >= 0 && playSpeed > 0) {
      if (props.fwd()) {
        if (props.loop() && props.trigger) {
          for(int i = 0; i < data.nframes; ++i) {
            data.audio.proc[i] += sampleData[props.in + props.playProgress];
            props.playProgress += playSpeed;
            if (props.playProgress >= props.length()) {
              props.playProgress = 0;
            }
          }
        } else {
          int frms = std::min<int>(data.nframes, props.length() - props.playProgress);
          for(int i = 0; i < frms; ++i) {
            data.audio.proc[i] += sampleData[props.in + props.playProgress];
            props.playProgress += playSpeed;
          }
          if (props.playProgress >= props.length()) {
            props.playProgress = -1;
          }
        }
      } else {
        if (props.loop() && props.trigger) {
          for(int i = 0; i < data.nframes; ++i) {
            data.audio.proc[i] += sampleData[props.in + props.playProgress];
            props.playProgress -= playSpeed;
            if (props.playProgress < 0) {
              props.playProgress = props.length() -1;
            }
          }
        } else {
          int frms = std::min<int>(data.nframes, props.playProgress);
          for(int i = 0; i < frms; ++i) {
            data.audio.proc[i] += sampleData[props.in + props.playProgress];
            props.playProgress -= playSpeed;
          }
        }
      }
    }

    for (auto &&nEvent : data.midi) {
      nEvent.match([&] (midi::NoteOffEvent& e) {
          if (e.channel == 0) {
            props.trigger = false;
            if (props.stop()) {
              props.playProgress = -1;
            }
          }
        }, [] (auto) {});
    };
  }

  void SynthSampler::display() {
    Globals::ui.display(*editScreen);
  }

  void SynthSampler::load() {

    auto path = samplePath(props.sampleName);
    std::size_t rs = 0;
    if (!(path.empty() || props.sampleName.get().empty())) {
      SoundFile sf;
      sf.open(path);
      rs = std::min<int>(maxSampleSize, sf.length());
      sampleData.resize(rs);
      sf.read_samples(sampleData.data(), rs);

      sampleSampleRate = sf.info.samplerate;
      sampleSpeed = sampleSampleRate / float(Globals::samplerate);
      if (sf.length() == 0) LOGD << "Empty sample file";
    } else {
      sampleData.resize(0);
      LOGI << "Empty sampleName";
    }

    props.in.mode.max = rs;
    props.out.mode.max = rs;

    // Auto assign voices
    if (props.in < 0 || props.out >= rs) {
      props.in = 0;
      props.out = rs;
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

  bool SynthSampleScreen::keypress(ui::Key key) { return false; }

  void SynthSampleScreen::rotary(ui::RotaryEvent e) {
    switch (e.rotary) {
    case ui::Rotary::Blue:
      module->props.in.step(e.clicks); break;
    case ui::Rotary::Green:
      module->props.out.step(e.clicks); break;
    case ui::Rotary::White:
      module->props.speed.step(e.clicks); break;
    case ui::Rotary::Red:
      module->props.mode.step(e.clicks); break;
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
    auto& props = module->props;

    ctx.callAt(topWFpos, [&] () {
        topWFW.drawRange(ctx, topWFW.viewRange, Colours::TopWF);
        Colour baseColour = Colours::TopWFCur;
        float mix = props.playProgress / float(props.out - props.in);

        if (mix < 0) mix = 1;
        if (props.fwd()) mix = 1 - mix; //data is not reversed

        colourCurrent = baseColour.mix(Colours::TopWFActive, mix);
        topWFW.drawRange(ctx, {
            std::size_t(std::round(props.in / topWF->ratio)),
              std::size_t(std::round(props.out / topWF->ratio))
              }, colourCurrent);
      });

    icons::Arrow icon;

    if (props.fwd()) {
      icon.dir = icons::Arrow::Right;
    } else {
      icon.dir = icons::Arrow::Left;
    }

    if (props.stop()) {
      icon.stopped = true;
    }

    if (props.loop()) {
      icon.looping = true;
    }

    icon.size = arrowSize;
    icon.colour = Colours::Red;
    ctx.drawAt(arrowPos, icon);

    ctx.beginPath();
    ctx.fillStyle(Colours::White);
    ctx.font(Fonts::Norm);
    ctx.font(15);
    ctx.textAlign(TextAlign::Left, TextAlign::Baseline);
    ctx.fillText(fmt::format("×{:.2F}", props.speed.get()), pitchPos);

    ctx.callAt(
      mainWFpos, [&] () {

        mainWFW.lineCol = colourCurrent;
        mainWFW.minPx = 5;
        mainWFW.viewRange = {
          std::size_t(std::round(props.in / mainWF->ratio)),
          std::size_t(std::round(props.out / mainWF->ratio))};

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
