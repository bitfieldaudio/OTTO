#include "drum-sampler.hpp"

#include <algorithm>

#include "core/globals.hpp"
#include "core/ui/waveform_widget.hpp"
#include "core/ui/canvas.hpp"
#include "core/ui/drawing.hpp"
#include "core/ui/icons.hpp"
#include "util/soundfile.hpp"
#include "util/exception.hpp"
#include "core/audio/audio_manager.hpp"

namespace otto::engines {

  struct DrumSampleScreen : public EngineScreen<DrumSampler> {

    ui::widgets::Waveform<util::dyn_array<float>> topWFW;
    ui::widgets::Waveform<util::dyn_array<float>> mainWFW;

    DrumSampleScreen(DrumSampler *);

    void draw(ui::vg::Canvas&) override;

    bool keypress(ui::Key) override;
    void rotary(ui::RotaryEvent) override;
  };

  DrumSampler::DrumSampler()
    : DrumsEngine("Drum Sampler",
        props,
        std::make_unique<DrumSampleScreen>(this)),
      maxSampleSize(16 * audio::samplerate()),
      sampleData(maxSampleSize)
  {
    audio::events::samplerate_change().subscribe([this](int sr) {
      maxSampleSize = 16 * sr;
      sampleSpeed   = sampleSampleRate / float(sr);
    });
  }

  DrumSampler::~DrumSampler() = default;

  fs::path DrumSampler::samplePath(std::string name) {
    if (name.empty()) {
      throw util::exception("DrumSampler: Got empty sample name. Is one specified in data/engines.json?");
    }
    auto path = global::data_dir / "samples" / "drums" / (name + ".wav");
    if (!fs::exists(path)) {
      path = global::data_dir / "samples" / "drums" / (name + ".aiff");
    }
    if (!fs::exists(path)) {
      throw util::exception("DrumSampler: Specified sample path not found: {}", path.c_str());
    }
    return path;
  }

  audio::ProcessData<1> DrumSampler::process(audio::ProcessData<0> data) {
    for (auto &&nEvent : data.midi) {
      util::match(nEvent, [&] (midi::NoteOnEvent& e) {
          currentVoiceIdx = e.key % nVoices;
          auto &&voice = props.voiceData[currentVoiceIdx];
          voice.playProgress = (voice.fwd()) ? 0 : voice.length() - 1;
          voice.trigger = true;
        }, [] (auto&&) {});
    }

    proc_buf.clear();

    for (auto &&voice : props.voiceData) {

      float playSpeed = voice.pitch.mode.pow2() * sampleSpeed;

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
            for(int i = 0; i < data.nframes; ++i) {
              proc_buf[i][0] += sampleData[voice.in + voice.playProgress];
              voice.playProgress += playSpeed;
              if (voice.playProgress >= voice.length()) {
                voice.playProgress = -1;
                break;
              }
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
            for(int i = 0; i < data.nframes; ++i) {
              proc_buf[i][0] += sampleData[voice.in + voice.playProgress];
              voice.playProgress -= playSpeed;
              if (voice.playProgress < 0) break;
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

  void DrumSampler::load() {

    auto path = samplePath(props.sampleName);
    int rs = 0;
    if (!(path.empty() || props.sampleName.get().empty())) {
      try {
        util::SoundFile sf;
        sf.open(path);
        rs = std::min<int>(maxSampleSize, sf.length());
        sampleData.resize(rs);
        sf.read_samples(sampleData.data(), rs);

        sampleSampleRate = sf.info.samplerate;
        sampleSpeed = sampleSampleRate / float(audio::samplerate());
        LOG_IF_F(INFO, sf.length() == 0, "Empty sample file");
      } catch (util::exception& e) {
        LOG_F(ERROR, "Failure while trying to load sample file '{}':", path);
        LOG_F(ERROR, e.what());
      }
    } else {
      sampleData.resize(0);
      LOG_F(INFO, "Empty sampleName");
    }

    for (auto &&v : props.voiceData) {
      v.in.mode.min = 0;
      v.out.mode.min = 0;
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

    float max = *util::max_element(sampleData);

    // TODO: Is there a better solution than this dynamic_cast?
    auto& scrn = dynamic_cast<DrumSampleScreen&>(screen());
    scrn.topWFW.range({0, int(rs)});
    scrn.topWFW.top_val(max);
    scrn.mainWFW.top_val(max);
  }

  void DrumSampler::on_enable() {
    load();
  }

  /****************************************/
  /* SampleEditScreen                     */
  /****************************************/

  DrumSampleScreen::DrumSampleScreen(DrumSampler *m)
    : EngineScreen<DrumSampler> (m),
      topWFW(engine.sampleData, {273.9, 15.f}),
      mainWFW (engine.sampleData, {273.9, 100.2})
  {
    topWFW.radius_range = {0.5f, 0.5f};
    mainWFW.radius_range = {1.5f, 3.f};
  }

  bool DrumSampleScreen::keypress(ui::Key key) {
    using namespace ui;
    auto& voice = engine.props.voiceData[engine.currentVoiceIdx];
    switch (key) {
    case Key::white_click: voice.pitch.reset(); return true;
    default:
      return false;
    }
  }

  void DrumSampleScreen::rotary(ui::RotaryEvent e) {
    using namespace ui;
    auto& voice = engine.props.voiceData[engine.currentVoiceIdx];
    switch (e.rotary) {
    case Rotary::Blue:
      voice.in.step(e.clicks); break;
    case Rotary::Green:
      voice.out.step(e.clicks); break;
    case Rotary::White:
      voice.pitch.step(e.clicks); break;
    case Rotary::Red:
      voice.mode.step(e.clicks); break;
    }
  }


  using PlayMode = DrumSampler::Props::VoiceData::Mode;

  static void draw_play_mode(ui::vg::Canvas& ctx, PlayMode mode)
  {
    ctx.save();
    ctx.strokeStyle(ui::vg::Colour::bytes(228, 50, 41));

    switch (mode) {
    case PlayMode::FwdStop:
      // laag1/Play Until Stop/Play Icon
      ctx.beginPath();
      ctx.moveTo(166.4, 43.9);
      ctx.lineTo(183.5, 37.4);
      ctx.bezierCurveTo(183.9, 37.3, 183.9, 36.6, 183.5, 36.4);
      ctx.lineTo(178.2, 34.4);
      ctx.lineTo(166.4, 30.0);
      ctx.bezierCurveTo(166.0, 29.9, 165.7, 30.1, 165.7, 30.5);
      ctx.lineTo(165.7, 43.4);
      ctx.bezierCurveTo(165.7, 43.7, 166.0, 44.0, 166.4, 43.9);
      ctx.closePath();
      ctx.stroke();

      // laag1/Play Until Stop/until
      ctx.beginPath();
      ctx.moveTo(190.5, 33.8);
      ctx.lineTo(193.5, 37.1);
      ctx.lineTo(190.5, 40.3);
      ctx.stroke();

      // laag1/Play Until Stop/stop
      ctx.beginPath();
      ctx.moveTo(207.9, 41.2);
      ctx.lineTo(199.6, 41.2);
      ctx.lineTo(199.6, 33.0);
      ctx.lineTo(207.9, 33.0);
      ctx.lineTo(207.9, 41.2);
      ctx.closePath();
      ctx.stroke();
      break;
    case PlayMode::FwdLoop:
      // laag1/InfiniteRepeat Icon/arrow right
      ctx.beginPath();
      ctx.moveTo(179.8, 39.8);
      ctx.lineTo(182.8, 43.0);
      ctx.lineTo(179.8, 46.2);
      ctx.stroke();

      // laag1/InfiniteRepeat Icon/arrow left
      ctx.beginPath();
      ctx.moveTo(191.0, 34.1);
      ctx.lineTo(188.0, 30.8);
      ctx.lineTo(191.0, 27.6);
      ctx.stroke();

      // laag1/InfiniteRepeat Icon/repeat
      ctx.beginPath();
      ctx.moveTo(182.8, 43.0);
      ctx.lineTo(171.6, 43.0);
      ctx.bezierCurveTo(169.2, 43.0, 167.2, 41.0, 167.2, 38.5);
      ctx.lineTo(167.2, 35.4);
      ctx.bezierCurveTo(167.2, 32.9, 169.2, 30.9, 171.6, 30.9);
      ctx.lineTo(172.8, 30.9);
      ctx.lineTo(176.9, 30.9);
      ctx.bezierCurveTo(178.1, 30.9, 179.3, 31.3, 180.1, 32.2);
      ctx.lineTo(189.6, 41.7);
      ctx.bezierCurveTo(190.4, 42.5, 191.6, 43.0, 192.8, 43.0);
      ctx.lineTo(198.9, 43.0);
      ctx.bezierCurveTo(201.4, 43.0, 203.4, 41.0, 203.4, 38.5);
      ctx.lineTo(203.4, 35.4);
      ctx.bezierCurveTo(203.4, 32.9, 201.4, 30.9, 198.9, 30.9);
      ctx.lineTo(188.1, 30.9);
      ctx.stroke();
      break;

    case PlayMode::Fwd:
      // laag1/Play Icon
      ctx.beginPath();
      ctx.moveTo(178.0, 43.9);
      ctx.lineTo(195.1, 37.4);
      ctx.bezierCurveTo(195.6, 37.3, 195.6, 36.6, 195.1, 36.4);
      ctx.lineTo(189.8, 34.4);
      ctx.lineTo(178.0, 30.0);
      ctx.bezierCurveTo(177.7, 29.9, 177.3, 30.1, 177.3, 30.5);
      ctx.lineTo(177.3, 43.4);
      ctx.bezierCurveTo(177.3, 43.7, 177.7, 44.0, 178.0, 43.9);
      ctx.closePath();
      ctx.stroke();
      break;

    case PlayMode::BwdStop:
      // laag1/Play Until Stop REVERSE/Play Icon
      ctx.beginPath();
      ctx.moveTo(166.4, 43.9);
      ctx.lineTo(183.5, 37.4);
      ctx.bezierCurveTo(183.9, 37.3, 183.9, 36.6, 183.5, 36.4);
      ctx.lineTo(178.2, 34.4);
      ctx.lineTo(166.4, 30.0);
      ctx.bezierCurveTo(166.0, 29.9, 165.7, 30.1, 165.7, 30.5);
      ctx.lineTo(165.7, 43.4);
      ctx.bezierCurveTo(165.7, 43.7, 166.0, 44.0, 166.4, 43.9);
      ctx.closePath();
      ctx.stroke();

      // laag1/Play Until Stop REVERSE/until
      ctx.beginPath();
      ctx.moveTo(190.5, 33.8);
      ctx.lineTo(193.5, 37.1);
      ctx.lineTo(190.5, 40.3);
      ctx.stroke();

      // laag1/Play Until Stop REVERSE/stop
      ctx.beginPath();
      ctx.moveTo(207.9, 41.2);
      ctx.lineTo(199.6, 41.2);
      ctx.lineTo(199.6, 33.0);
      ctx.lineTo(207.9, 33.0);
      ctx.lineTo(207.9, 41.2);
      ctx.closePath();
      ctx.stroke();

      // laag1/Play Until Stop REVERSE/arrow

      // laag1/Play Until Stop REVERSE/arrow/arrow
      ctx.beginPath();
      ctx.moveTo(160.9, 40.2);
      ctx.lineTo(157.9, 36.9);
      ctx.lineTo(160.9, 33.7);
      ctx.stroke();

      // laag1/Play Until Stop REVERSE/arrow/lines
      ctx.beginPath();
      ctx.moveTo(168.8, 36.9);
      ctx.lineTo(158.0, 36.9);
      ctx.stroke();
      break;

    case PlayMode::BwdLoop:
      // laag1/InfiniteRepeat Icon REVERSE/arrowhead
      ctx.beginPath();
      ctx.moveTo(191.0, 34.1);
      ctx.lineTo(188.0, 30.8);
      ctx.lineTo(191.0, 27.6);
      ctx.stroke();

      // laag1/InfiniteRepeat Icon REVERSE/replay
      ctx.beginPath();
      ctx.moveTo(182.8, 43.0);
      ctx.lineTo(171.6, 43.0);
      ctx.bezierCurveTo(169.2, 43.0, 167.2, 41.0, 167.2, 38.5);
      ctx.lineTo(167.2, 35.4);
      ctx.bezierCurveTo(167.2, 32.9, 169.2, 30.9, 171.6, 30.9);
      ctx.lineTo(172.8, 30.9);
      ctx.lineTo(176.9, 30.9);
      ctx.bezierCurveTo(178.1, 30.9, 179.3, 31.3, 180.1, 32.2);
      ctx.lineTo(189.6, 41.7);
      ctx.bezierCurveTo(190.4, 42.5, 191.6, 43.0, 192.8, 43.0);
      ctx.lineTo(198.9, 43.0);
      ctx.bezierCurveTo(201.4, 43.0, 203.4, 41.0, 203.4, 38.5);
      ctx.lineTo(203.4, 35.4);
      ctx.bezierCurveTo(203.4, 32.9, 201.4, 30.9, 198.9, 30.9);
      ctx.lineTo(188.1, 30.9);
      ctx.stroke();

      // laag1/InfiniteRepeat Icon REVERSE/arrowhead2
      ctx.beginPath();
      ctx.moveTo(179.8, 39.8);
      ctx.lineTo(182.8, 43.0);
      ctx.lineTo(179.8, 46.2);
      ctx.stroke();

      // laag1/InfiniteRepeat Icon REVERSE/arrow

      // laag1/InfiniteRepeat Icon REVERSE/arrow/arrow
      ctx.beginPath();
      ctx.moveTo(162.4, 40.2);
      ctx.lineTo(159.4, 36.9);
      ctx.lineTo(162.4, 33.7);
      ctx.stroke();

      // laag1/InfiniteRepeat Icon REVERSE/arrow/lines
      ctx.beginPath();
      ctx.moveTo(170.3, 36.9);
      ctx.lineTo(159.5, 36.9);
      ctx.stroke();
      break;

    case PlayMode::Bwd:
      // laag1/Play Icon REVERSE/Groep/Play Icon
      ctx.beginPath();
      ctx.moveTo(178.0, 43.9);
      ctx.lineTo(195.1, 37.4);
      ctx.bezierCurveTo(195.6, 37.3, 195.6, 36.6, 195.1, 36.4);
      ctx.lineTo(189.8, 34.4);
      ctx.lineTo(178.0, 30.0);
      ctx.bezierCurveTo(177.7, 29.9, 177.3, 30.1, 177.3, 30.5);
      ctx.lineTo(177.3, 43.4);
      ctx.bezierCurveTo(177.3, 43.7, 177.7, 44.0, 178.0, 43.9);
      ctx.closePath();
      ctx.stroke();

      // laag1/Play Icon REVERSE/Groep/Groep/Groep/Pad
      ctx.beginPath();
      ctx.moveTo(172.6, 40.2);
      ctx.lineTo(169.6, 36.9);
      ctx.lineTo(172.6, 33.7);
      ctx.stroke();

      // laag1/Play Icon REVERSE/Groep/Pad
      ctx.beginPath();
      ctx.moveTo(180.5, 36.9);
      ctx.lineTo(169.7, 36.9);
      ctx.stroke();

      // laag1/Play Icon REVERSE/Groep/Groep/Groep/Pad
      ctx.beginPath();
      ctx.moveTo(172.6, 40.2);
      ctx.lineTo(169.6, 36.9);
      ctx.lineTo(172.6, 33.7);
      ctx.stroke();

      // laag1/Play Icon REVERSE/Groep/Pad
      ctx.beginPath();
      ctx.moveTo(180.5, 36.9);
      ctx.lineTo(169.7, 36.9);
      ctx.stroke();

      // laag1/Play Icon REVERSE/Groep/Groep/Groep/Pad
      ctx.beginPath();
      ctx.moveTo(172.6, 40.2);
      ctx.lineTo(169.6, 36.9);
      ctx.lineTo(172.6, 33.7);
      ctx.stroke();

      // laag1/Play Icon REVERSE/Groep/Pad
      ctx.beginPath();
      ctx.moveTo(180.5, 36.9);
      ctx.lineTo(169.7, 36.9);
      ctx.stroke();
    }

    ctx.restore();

  }

  static void draw_pitch(ui::vg::Canvas& ctx, float pitch)
  {
    using namespace ui::vg;

    // TODO: Cache!
    auto col_vals = util::math::split_values<5>(pitch < 0 ? pitch * 2 : pitch, -4, 4);
    auto const yellow = Colour::bytes(249, 182, 0);
    auto const white = Colours::White;
    auto const gray = Colour::bytes(112, 125, 132);

    // laag1/HigherLower/ArrowTop
    ctx.save();
    ctx.beginPath();
    ctx.moveTo(90.8, 28.2);
    ctx.lineTo(95.3, 24.7);
    ctx.lineTo(99.8, 28.2);
    ctx.lineWidth(2.0);
    ctx.stroke(gray.mix(yellow, col_vals[4]));

    // laag1/HigherLower/Top
    ctx.beginPath();
    ctx.moveTo(94.4, 31.9);
    ctx.lineTo(96.1, 31.9);
    ctx.stroke(gray.mix(yellow, col_vals[3]));

    // laag1/HigherLower/Mid
    ctx.beginPath();
    ctx.moveTo(93.4, 36.9);
    ctx.lineTo(97.1, 36.9);
    ctx.stroke(white.mix(yellow, col_vals[2]));

    // laag1/HigherLower/Bottom
    ctx.beginPath();
    ctx.moveTo(94.4, 41.9);
    ctx.lineTo(96.1, 41.9);
    ctx.stroke(gray.mix(yellow, col_vals[1]));

    // laag1/HigherLower/ArrowBottom
    ctx.beginPath();
    ctx.moveTo(99.8, 46.2);
    ctx.lineTo(95.3, 49.7);
    ctx.lineTo(90.8, 46.2);
    ctx.stroke(gray.mix(yellow, col_vals[0]));

    // laag1/Pitchshift Height
    ctx.font(24.3);
    ctx.font(Fonts::Norm);
    ctx.save();
    ctx.transform(1.000, 0.000, 0.000, 1.000, 111.4, 36.9);
    ctx.fillStyle(Colour::bytes(249, 182, 0));
    ctx.textAlign(TextAlign::Left, TextAlign::Middle);
    ctx.fillText(fmt::format("{:+.0f}", pitch * 12), 0, 0);
    ctx.restore();
  }

  void engines::DrumSampleScreen::draw(ui::vg::Canvas& ctx) {
    using namespace ui::vg;

    // laag1/Note
    ctx.font(24.3);
    ctx.font(Fonts::Mono);
    ctx.save();
    ctx.transform(1.000, 0.000, 0.000, 1.000, 43.4, 45.6);
    ctx.fillStyle(Colour::bytes(255, 255, 255));
    ctx.fillText(midi::note_name(engine.currentVoiceIdx + 24), 0, 0);
    ctx.restore();


    // laag1/Render Fx Tape
    ctx.restore();
    ctx.font(Fonts::Bold);
    ctx.font(12.2);
    ctx.fillStyle(Colour::bytes(112, 125, 132));
    ctx.fillText("render", 235.1, 35.3);
    ctx.fillText("fx tape", 235.1, 47.3);

    auto& voice = engine.props.voiceData[engine.currentVoiceIdx];

    const Colour pink = Colour::bytes(234, 163, 200);
    float progress = voice.playProgress / float(voice.length());
    progress = voice.bwd() ? 1 - progress : progress;
    Colour voice_col = pink.mix(Colours::White, progress);

    draw_pitch(ctx, voice.pitch);
    draw_play_mode(ctx, PlayMode(voice.mode.get()));

    ctx.callAt({22.2, 197.9}, [&] {
        // Draw full waveform
        ctx.beginPath();
        topWFW.draw(ctx, [] (auto& ctx, auto f, auto l) {
            ctx.plotLines(f, l);
          });
        ctx.stroke(Colour::bytes(228, 50, 41));

        ctx.beginPath();
        topWFW.draw_range(ctx, {voice.in, voice.out},
          [] (auto& ctx, auto f, auto l) {
            ctx.plotLines(f, l);
          });
        ctx.stroke(voice_col);

      });

    int in = std::max(0.f, voice.in - voice.length() / 4.f);
    int out = std::min(engine.sampleData.size() - 1.f, voice.out + voice.length() / 4.f);
    mainWFW.range({in, out});
    ctx.callAt({22.3, 73.3}, [&] {
        auto p1 = mainWFW.point_floor(voice.in);
        auto p2 = mainWFW.point_floor(voice.out);
        auto size = mainWFW.size;

        // Baseline
        ctx.beginPath();
        ctx.moveTo(0, size.h);
        ctx.lineTo(size.w, size.h);
        ctx.stroke(Colour::bytes(61, 63, 65));

        // Baseline markers
        ctx.beginPath();
        ctx.moveTo(p1.x, size.h);
        ctx.lineTo(p1.x + 1.f, size.h);
        ctx.moveTo(p2.x, size.h);
        ctx.lineTo(p2.x + 1.f, size.h);
        ctx.stroke(voice_col);

        // Gray parts
        ctx.beginPath();
        mainWFW.draw_range(ctx, {in, voice.in});
        mainWFW.draw_range(ctx, {voice.out, out});
        ctx.stroke(Colour::bytes(61, 63, 65));

        // Center part
        ctx.beginPath();
        mainWFW.draw_range(ctx, {voice.in, voice.out});
        ctx.stroke(voice_col);

        ctx.beginPath();
        ctx.circle(p1, 3.f);
        ctx.fill(Colours::Blue);

        ctx.beginPath();
        ctx.circle(p2, 3.f);
        ctx.fill(Colours::Green);

      });
  }

} // otto::engine
