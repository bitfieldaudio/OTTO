#include "gammasampler.hpp"

#include "core/ui/vector_graphics.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"

#include "services/audio_manager.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct SamplerScreen : EngineScreen<Sampler> {
    void draw(Canvas& ctx) override;
    void encoder(EncoderEvent e) override;

    using EngineScreen<Sampler>::EngineScreen;
  };

  struct SamplerEnvelopeScreen : EngineScreen<Sampler> {
    void draw(Canvas& ctx) override;
    void encoder(EncoderEvent e) override;

    AudioFile<float> waveform;

    using EngineScreen<Sampler>::EngineScreen;
  };

  Sampler::Sampler()
    : SynthEngine<Sampler>(std::make_unique<SamplerScreen>(this)),
      _envelope_screen(std::make_unique<SamplerEnvelopeScreen>(this))
  {
    samplefile.load((Application::current().data_dir / "samples" / "sample.wav").c_str());
    samplecontainer.source(&samplefile.samples[0][0], samplefile.getNumSamplesPerChannel(), true);
    sample.buffer(samplecontainer, (double) samplefile.getSampleRate(),
                  samplefile.getNumChannels());
    finish();
    frames = sample.frames();

    _lo_filter.type(gam::LOW_PASS);
    _lo_filter.freq(20);
    _hi_filter.type(gam::HIGH_PASS);
    _hi_filter.freq(20000);

    // On_change handlers
    props.startpoint.on_change().connect([this](float pt) { sample.min(pt * frames); });
    props.endpoint.on_change().connect([this](float pt) { sample.max(pt * frames); });
    props.fadein.on_change().connect(
      [this](float fd) { sample.fade((int) fd * 1000, (int) props.fadeout * 1000); });
    props.fadeout.on_change().connect(
      [this](float fd) { sample.fade((int) props.fadein * 1000, (int) fd * 1000); });
    props.filter.on_change().connect([this](float freq) {
      if (freq > 10) {
        _lo_filter.freq(20000);
        _hi_filter.freq(freq * freq * freq * 0.2);
      } else {
        _lo_filter.freq(freq * freq * 200);
        _hi_filter.freq(20);
      }
    });
    props.speed.on_change().connect([this](float spd) { sample.rate(spd); });
  }

  void Sampler::restart()
  {
    sample.reset();
  }

  void Sampler::finish()
  {
    sample.finish();
  }

  float Sampler::operator()() noexcept
  {
    if (props.loop) sample.loop();
    return sample();
  }

  void Sampler::load_file(fs::path path)
  {
    samplefile.load((Application::current().data_dir / "samples" / "sample.wav").c_str());
    samplecontainer.source(&samplefile.samples[0][0], samplefile.getNumSamplesPerChannel());
    sample.buffer(samplecontainer, (double) samplefile.getSampleRate(),
                  samplefile.getNumChannels());
  }

  audio::ProcessData<1> Sampler::process(audio::ProcessData<1> data)
  {
    for (auto& ev : data.midi) {
      util::match(ev,
                  [this](midi::NoteOnEvent& ev) {
                    note_on = true;
                    restart();
                  },
                  [this](midi::NoteOffEvent& ev) {
                    note_on = false;
                    if (props.cut) finish();
                  },
                  [](auto&&) {});
    }
    for (auto&& frm : data.audio) {
      frm = _hi_filter(_lo_filter(sample())) * props.volume;
      if (props.loop && note_on && sample.done()) restart();
    }
    return data;
  }

  ui::Screen& Sampler::envelope_screen()
  {
    return *_envelope_screen;
  }

  ui::Screen& Sampler::voices_screen()
  {
    return *_envelope_screen;
  }

  // MAIN SCREEN //

  void SamplerScreen::encoder(ui::EncoderEvent ev)
  {
    auto& props = engine.props;
    //auto& sample = engine.sample;
    switch (ev.encoder) {
    case ui::Encoder::blue: props.volume.step(ev.steps); break;
    case ui::Encoder::green: props.filter.step(ev.steps); break;
    case ui::Encoder::yellow: props.speed.step(ev.steps); break;
    case ui::Encoder::red:
      if (props.cut && props.loop) {
        props.loop = false;
      } else if (props.cut && !props.loop) {
        props.cut = false;
      } else if (!props.cut && !props.loop) {
        props.loop = true;
      } else if (!props.cut && props.loop) {
        props.cut = true;
      }
    }
  }

  void SamplerScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    auto& props = engine.props;
    //auto& sample = engine.sample;

    ctx.font(Fonts::Norm, 20);

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Volume", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1}", engine.props.volume), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Filter", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:2.2}", engine.props.filter), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Speed", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.speed), {width - x_pad, y_pad + 2 * space});

    if (props.cut) ctx.fillText("CUT", {100, 170});
    if (props.loop) ctx.fillText("LOOP", {100, 195});
  }

  // ENVELOPE SCREEN //

  void SamplerEnvelopeScreen::encoder(ui::EncoderEvent ev)
  {
    //auto& sample = engine.sample;
    switch (ev.encoder) {
    case ui::Encoder::blue: engine.props.startpoint.step(ev.steps); break;
    case ui::Encoder::green: engine.props.endpoint.step(ev.steps); break;
    case ui::Encoder::yellow: engine.props.fadein.step(ev.steps); break;
    case ui::Encoder::red: engine.props.fadeout.step(ev.steps); break;
    }
  }

  void SamplerEnvelopeScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    // auto& props = engine.props;
    //auto& sample = engine.sample;

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Start", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.startpoint), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("End", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.endpoint), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("FadeIn", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.fadein), {width - x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("FadeOut", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.fadeout), {width - x_pad, y_pad + 3 * space});
    /*
    if (engine.sample.size() <= 0) return;

    ctx.beginPath();

    ctx.moveTo(10, 120);
    auto waveform = engine.sample.waveform();
    float size = waveform.end() - waveform.begin();

    for (float i = 0; i < 300; i += 2) {
      float x = 10.f + i;
      float y = *(waveform.begin() + float(i) / 300.f * size) * 50.f;
      ctx.lineTo(x, 120.f - y);
    }
    for (float i = 299; i >= 0; i -= 2) {
      float x = 10.f + i;
      float y = *(waveform.begin() + float(i) / 300.f * size) * 50.f;
      ctx.lineTo(x, 120.f + y);
    }
    ctx.closePath();
    ctx.fill(Colours::White);

    auto wfm_idx = [&] (int idx) {
      return (idx - sample.start_point()) / sample.waveform_scale();
    };

    auto draw_line = [&] (int point, Colour c) {
      float idx = wfm_idx(point);
      float x = 10 + 300.f * idx / size;
      float y = *(waveform.begin() + idx) * 50.f;
      ctx.beginPath();
      ctx.moveTo(x, 120);
      ctx.lineTo(x, 120 - y);
      ctx.circle({x, 120 - y}, 3);
      ctx.lineWidth(3);
      ctx.stroke(c);
    };

    if (sample.loop_start() != sample.start_point()) {
      draw_line(sample.loop_start(), Colours::Yellow);
    }

    if (sample.loop_end() != sample.end_point()) {
      draw_line(sample.loop_end(), Colours::Red);
    }
     */
  }

} // namespace otto::engines
