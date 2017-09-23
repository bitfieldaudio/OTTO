#include <algorithm>

#include "drum-sampler.hpp"
#include "core/globals.hpp"
#include "core/ui/module-ui.hpp"
#include "core/ui/drawing.hpp"
#include "core/ui/icons.hpp"
#include "util/soundfile.hpp"

namespace top1::ui::drawing {

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

} // top1::ui::drawing


namespace top1::modules {

  DrumSampler::DrumSampler() :
    SynthModule(&props),
    maxSampleSize (16 * Globals::samplerate),
    sampleData (maxSampleSize),
    editScreen (new DrumSampleScreen(this)) {

    Globals::events.samplerateChanged.add([&] (uint sr) {
        maxSampleSize = 16 * sr;
        sampleSpeed = sampleSampleRate / float(sr);
      });

  }

  fs::path DrumSampler::samplePath(std::string name) {
    auto wav_path = Globals::data_dir / "samples" / "drums" / (name + ".wav");
    if (!fs::exists(wav_path)) {
      return Globals::data_dir / "samples" / "drums" / (name + ".aiff");
    }
    return wav_path;
  }

  void DrumSampler::process(const audio::ProcessData& data) {
    for (auto &&nEvent : data.midi) {
      nEvent.match([&] (midi::NoteOnEvent& e) {
          if (e.channel == 1) {
            currentVoiceIdx = e.key % nVoices;
            auto &&voice = props.voiceData[currentVoiceIdx];
            voice.playProgress = (voice.fwd()) ? 0 : voice.length() - 1;
            voice.trigger = true;
          }
        }, [] (auto&&) {});
    }

    for (auto &&voice : props.voiceData) {

      float playSpeed = voice.speed * sampleSpeed;

      // Process audio
      if (voice.playProgress >= 0 && playSpeed > 0) {
        if (voice.fwd()) {
          if (voice.loop() && voice.trigger) {
            for(int i = 0; i < data.nframes; ++i) {
              data.audio.proc[i] += sampleData[voice.in + voice.playProgress];
              voice.playProgress += playSpeed;
              if (voice.playProgress >= voice.length()) {
                voice.playProgress = 0;
              }
            }
          } else {
            int frms = std::min<int>(data.nframes, voice.length() - voice.playProgress);
            for(int i = 0; i < frms; ++i) {
              data.audio.proc[i] += sampleData[voice.in + voice.playProgress];
              voice.playProgress += playSpeed;
            }
            if (voice.playProgress >= voice.length()) {
              voice.playProgress = -1;
            }
          }
        } else {
          if (voice.loop() && voice.trigger) {
            for(int i = 0; i < data.nframes; ++i) {
              data.audio.proc[i] += sampleData[voice.in + voice.playProgress];
              voice.playProgress -= playSpeed;
              if (voice.playProgress < 0) {
                voice.playProgress = voice.length() -1;
              }
            }
          } else {
            int frms = std::min<int>(data.nframes, voice.playProgress);
            for(int i = 0; i < frms; ++i) {
              data.audio.proc[i] += sampleData[voice.in + voice.playProgress];
              voice.playProgress -= playSpeed;
            }
          }
        }
      }
    }

    for (auto &&nEvent : data.midi) {
      nEvent.match([&] (midi::NoteOffEvent& e) {
          if (e.channel == 1) {
            auto &&voice = props.voiceData[e.key % nVoices];
            voice.trigger = false;
            if (voice.stop()) {
              voice.playProgress = -1;
            }
          }
        }, [] (auto&&) {});
    };
  }

  void DrumSampler::display() {
    Globals::ui.display(*editScreen);
  }

  void DrumSampler::load() {

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

    for (auto &&v : props.voiceData) {
      v.in.mode.max = rs;
      v.out.mode.max = rs;
    }

    // Auto assign voices

    for (uint i = 0; i < nVoices; ++i) {
      auto &&vd = props.voiceData[i];
      if (vd.in < 0 || vd.out >= rs) {
        vd.in = i * (rs / nVoices);
        vd.out = (i + 1) * rs / nVoices;
      }
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

  void DrumSampler::init() {
    load();
  }

  /****************************************/
  /* SampleEditScreen                     */
  /****************************************/

  bool DrumSampleScreen::keypress(ui::Key key) {
    using namespace ui;
    auto& voice = module->props.voiceData[module->currentVoiceIdx];
    switch (key) {
    case K_WHITE_CLICK: voice.speed.reset(); return true;
    default:
      return false;
    }
  }

  void DrumSampleScreen::rotary(ui::RotaryEvent e) {
    using namespace ui;
    auto& voice = module->props.voiceData[module->currentVoiceIdx];
    switch (e.rotary) {
    case Rotary::Blue:
      voice.in.step(e.clicks); break;
    case Rotary::Green:
      voice.out.step(e.clicks); break;
    case Rotary::White:
      voice.speed.step(e.clicks); break;
    case Rotary::Red:
      voice.mode.step(e.clicks); break;
    }
  }


  DrumSampleScreen::DrumSampleScreen(DrumSampler *m) :
    ui::ModuleScreen<DrumSampler> (m),
    topWF (new audio::Waveform(module->sampleData.size()
                               / ui::drawing::topWFsize.w / 4.0, 1.0)),
    topWFW (topWF, ui::drawing::topWFsize),
    mainWF (new audio::Waveform(50, 1.0)),
    mainWFW (mainWF, ui::drawing::mainWFsize) {}

  void modules::DrumSampleScreen::draw(ui::drawing::Canvas &ctx) {
    using namespace ui::drawing;

    Colour colourCurrent;

    ctx.callAt(topWFpos, [&] () {
        topWFW.drawRange(ctx, topWFW.viewRange, Colours::TopWF);
        for (uint i = 0; i < DrumSampler::nVoices; ++i) {
          auto& voice = module->props.voiceData[i];
          bool isActive = voice.playProgress >= 0;
          bool isCurrent = i == module->currentVoiceIdx;
          if (isActive && !isCurrent) {
            Colour baseColour = Colours::TopWF;
            float mix = voice.playProgress / float(voice.out - voice.in);

            if (mix < 0) mix = 1;
            if (voice.fwd()) mix = 1 - mix; //voice is not reversed

            Colour colour = baseColour.mix(Colours::TopWFActive, mix);
            topWFW.drawRange(ctx, {
                std::size_t(std::round(voice.in / topWF->ratio)),
                  std::size_t(std::round(voice.out / topWF->ratio))
                  }, colour);
          }
        }
        {
          auto& voice = module->props.voiceData[module->currentVoiceIdx];
          Colour baseColour = Colours::TopWFCur;
          float mix = voice.playProgress / float(voice.out - voice.in);

          if (mix < 0) mix = 1;
          if (voice.fwd()) mix = 1 - mix; //voice is not reversed

          colourCurrent = baseColour.mix(Colours::TopWFActive, mix);
          topWFW.drawRange(ctx, {
              std::size_t(std::round(voice.in / topWF->ratio)),
                std::size_t(std::round(voice.out / topWF->ratio))
                }, colourCurrent);
        }
      });

    auto& voice = module->props.voiceData[module->currentVoiceIdx];

    icons::Arrow icon;

    if (voice.fwd()) {
      icon.dir = icons::Arrow::Right;
    } else {
      icon.dir = icons::Arrow::Left;
    }

    if (voice.stop()) {
      icon.stopped = true;
    }

    if (voice.loop()) {
      icon.looping = true;
    }

    icon.size = arrowSize;
    icon.colour = Colours::Red;
    ctx.drawAt(arrowPos, icon);

    ctx.beginPath();
    ctx.fillStyle(Colours::White);
    ctx.font(Fonts::Norm);
    ctx.font(18);
    ctx.textAlign(TextAlign::Left, TextAlign::Baseline);
    ctx.fillText(fmt::format("×{:.2F}", voice.speed.get()), pitchPos);

    ctx.callAt(mainWFpos, [&] () {
        mainWFW.lineCol = colourCurrent;
        mainWFW.minPx = 5;
        mainWFW.viewRange = {
          std::size_t(std::round(voice.in / mainWF->ratio)),
          std::size_t(std::round(voice.out / mainWF->ratio))};

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
