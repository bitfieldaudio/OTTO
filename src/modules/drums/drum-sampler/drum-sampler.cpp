#include <algorithm>

#include "drum-sampler.hpp"
#include "core/globals.hpp"
#include "core/ui/module-ui.hpp"
#include "core/ui/drawing.hpp"
#include "core/ui/icons.hpp"
#include "util/soundfile.hpp"
#include "util/exception.hpp"

namespace otto::ui::vg {

  const static vg::Size topWFsize = {210, 20};
  const static vg::Point topWFpos = {60, 20};
  const static vg::Size arrowSize = {20, 20};
  const static vg::Point arrowPos = {280, 20};
  const static vg::Size pitchSize = {30, 20};
  const static vg::Point pitchPos = {20, 40};
  const static vg::Size mainWFsize = {280, 170};
  const static vg::Point mainWFpos = {20, 50};

  namespace Colours {

    const Colour TopWF = Blue.dim(0.2);
    const Colour TopWFCur = Blue.brighten(0.5);
    const Colour TopWFActive = White;
    const Colour WFGrid = 0x303040;
  }

} // otto::ui::drawing


namespace otto::modules {

  DrumSampler::DrumSampler() :
    SynthModule(&props),
    maxSampleSize (16 * Globals::samplerate),
    sampleData (maxSampleSize),
    editScreen (new DrumSampleScreen(this)) {

    Globals::events.samplerateChanged.add([&] (int sr) {
        maxSampleSize = 16 * sr;
        sampleSpeed = sampleSampleRate / float(sr);
      });

  }

  fs::path DrumSampler::samplePath(std::string name) {
    if (name.empty()) {
      throw util::exception("DrumSampler: Got empty sample name. Is one specified in data/modules.json?");
    }
    auto path = Globals::data_dir / "samples" / "drums" / (name + ".wav");
    if (!fs::exists(path)) {
      path = Globals::data_dir / "samples" / "drums" / (name + ".aiff");
    }
    if (!fs::exists(path)) {
      throw util::exception("DrumSampler: Specified sample path not found: {}", path.c_str());
    }
    return path;
  }

  audio::ProcessData<1> DrumSampler::process(audio::ProcessData<0> data) {
    for (auto &&nEvent : data.midi) {
      util::match(nEvent, [&] (midi::NoteOnEvent& e) {
          if (e.channel == 1) {
            currentVoiceIdx = e.key % nVoices;
            auto &&voice = props.voiceData[currentVoiceIdx];
            voice.playProgress = (voice.fwd()) ? 0 : voice.length() - 1;
            voice.trigger = true;
          }
        }, [] (auto&&) {});
    }

    proc_buf.clear();

    for (auto &&voice : props.voiceData) {

      float playSpeed = voice.speed * sampleSpeed;

      // Process audio
      if (voice.playProgress >= 0 && playSpeed > 0) {
        if (voice.fwd()) {
          if (voice.loop() && voice.trigger) {
            for(int i = 0; i < data.nframes; ++i) {
              proc_buf[i][0] += sampleData[voice.in + voice.playProgress];
              voice.playProgress += playSpeed;
              if (voice.playProgress >= voice.length()) {
                voice.playProgress = 0;
              }
            }
          } else {
            int frms = std::min<int>(data.nframes, voice.length() - voice.playProgress);
            for(int i = 0; i < frms; ++i) {
              proc_buf[i][0] += sampleData[voice.in + voice.playProgress];
              voice.playProgress += playSpeed;
            }
            if (voice.playProgress >= voice.length()) {
              voice.playProgress = -1;
            }
          }
        } else {
          if (voice.loop() && voice.trigger) {
            for(int i = 0; i < data.nframes; ++i) {
              proc_buf[i][0] += sampleData[voice.in + voice.playProgress];
              voice.playProgress -= playSpeed;
              if (voice.playProgress < 0) {
                voice.playProgress = voice.length() -1;
              }
            }
          } else {
            int frms = std::min<int>(data.nframes, voice.playProgress);
            for(int i = 0; i < frms; ++i) {
              proc_buf[i][0] += sampleData[voice.in + voice.playProgress];
              voice.playProgress -= playSpeed;
            }
          }
        }
      }
    }

    for (auto &&nEvent : data.midi) {
      util::match(nEvent,
        [&] (midi::NoteOffEvent& e) {
          if (e.channel == 1) {
            auto &&voice = props.voiceData[e.key % nVoices];
            voice.trigger = false;
            if (voice.stop()) {
              voice.playProgress = -1;
            }
          }
        }, [] (auto&&) {});
    };

    return data.redirect(proc_buf);
  }

  void DrumSampler::display() {
    Globals::ui.display(*editScreen);
  }

  void DrumSampler::load() {

    auto path = samplePath(props.sampleName);
    std::size_t rs = 0;
    if (!(path.empty() || props.sampleName.get().empty())) {
      try {
        util::SoundFile sf;
        sf.open(path);
        rs = std::min<int>(maxSampleSize, sf.length());
        sampleData.resize(rs);
        sf.read_samples(sampleData.data(), rs);

        sampleSampleRate = sf.info.samplerate;
        sampleSpeed = sampleSampleRate / float(Globals::samplerate);
        if (sf.length() == 0) LOGD << "Empty sample file";
      } catch (util::exception& e) {
        LOGE << "Failure while trying to load sample file '"
             << path.c_str() << "':\n" << e.what();
      }
    } else {
      sampleData.resize(0);
      LOGI << "Empty sampleName";
    }

    for (auto &&v : props.voiceData) {
      v.in.mode.max = rs;
      v.out.mode.max = rs;
    }

    // Auto assign voices

    for (int i = 0; i < nVoices; ++i) {
      auto &&vd = props.voiceData[i];
      if (vd.in < 0 || vd.out >= rs) {
        vd.in = i * (rs / nVoices);
        vd.out = (i + 1) * rs / nVoices;
      }
    }

    editScreen->topWFW.range({0, rs});
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


  DrumSampleScreen::DrumSampleScreen(DrumSampler *m)
    : ui::ModuleScreen<DrumSampler> (m),
      topWFW(module->sampleData, ui::vg::topWFsize),
      mainWFW (module->sampleData, ui::vg::mainWFsize) {}

  void modules::DrumSampleScreen::draw(ui::vg::Canvas &ctx) {
    using namespace ui::vg;

    Colour colourCurrent;

    ctx.callAt(topWFpos, [&] () {
        topWFW.draw(ctx);
        ctx.stroke(Colours::TopWF);
        for (int i = 0; i < DrumSampler::nVoices; ++i) {
          auto& voice = module->props.voiceData[i];
          bool isActive = voice.playProgress >= 0;
          bool isCurrent = i == module->currentVoiceIdx;
          if (isActive && !isCurrent) {
            Colour baseColour = Colours::TopWF;
            float mix = voice.playProgress / float(voice.out - voice.in);

            if (mix < 0) mix = 1;
            if (voice.fwd()) mix = 1 - mix; //voice is not reversed

            Colour colour = baseColour.mix(Colours::TopWFActive, mix);
            topWFW.draw_range(ctx, {std::size_t(voice.in), std::size_t(voice.out)});
            ctx.stroke(colour);
          }
        }
        {
          auto& voice = module->props.voiceData[module->currentVoiceIdx];
          Colour baseColour = Colours::TopWFCur;
          float mix = voice.playProgress / float(voice.out - voice.in);

          if (mix < 0) mix = 1;
          if (voice.fwd()) mix = 1 - mix; //voice is not reversed

          colourCurrent = baseColour.mix(Colours::TopWFActive, mix);
          topWFW.draw_range(ctx, {std::size_t(voice.in), std::size_t(voice.out)});
          ctx.stroke(colourCurrent);
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
        mainWFW.range({std::size_t(voice.in), std::size_t(voice.out)});
        ctx.stroke(colourCurrent);

        mainWFW.draw(ctx);

        ctx.beginPath();
        ctx.circle(mainWFW.point(mainWFW.range().in), 3);
        ctx.fill(Colours::Blue);

        ctx.beginPath();
        ctx.circle(mainWFW.point(mainWFW.range().out), 3);
        ctx.fill(Colours::Green);
      });

  }

} // otto::module
