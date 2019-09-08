#include <services/audio_manager.hpp>
#include "sampler.hpp"

#include "core/ui/vector_graphics.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"

#include "services/audio_manager.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct SamplerMainScreen : EngineScreen<Sampler>{
    void draw(Canvas& ctx) override;
    void encoder(EncoderEvent e) override;
    bool keypress(Key key) override;
    void draw_filename(Canvas& ctx);

    void draw_envelope(Canvas& ctx);

    audio::WaveformView& _wfv;

    SamplerMainScreen(Sampler* e, audio::WaveformView& wfv) : EngineScreen<Sampler>(e), _wfv(wfv) {};

    using EngineScreen<Sampler>::EngineScreen;

  };

  struct SamplerEnvelopeScreen : EngineScreen<Sampler> {
    void draw(Canvas& ctx) override;
    void encoder(EncoderEvent e) override;

    void draw_arrowhead_left(ui::vg::Canvas& ctx, float x, float y_pos, float side_length, Colour cl);
    void draw_arrowhead_right(ui::vg::Canvas& ctx, float x, float y_pos, float side_length, Colour cl);

    void draw_envelope(Canvas& ctx);

    bool shift = false;

    audio::WaveformView& _wfv;

    SamplerEnvelopeScreen(Sampler* e, audio::WaveformView& wfv) : EngineScreen<Sampler>(e), _wfv(wfv) {};

    using EngineScreen<Sampler>::EngineScreen;

  };

  Sampler::Sampler()
    : MiscEngine<Sampler>(std::make_unique<SamplerMainScreen>(this, wfv)),
      _envelope_screen(std::make_unique<SamplerEnvelopeScreen>(this, wfv))
  {
    // Load filenames into vector. TODO: Move this out to enclosing sequencer
    std::string samples_path = Application::current().data_dir / "samples";
    for (const auto& entry : filesystem::recursive_directory_iterator(samples_path)) {
      if (!entry.is_regular_file()) continue;
      auto path = entry.path().string().substr(samples_path.size() + 1);
      DLOGI("Found sample file {}", path);
      props.filenames.push_back(path);
    }
    util::sort(props.filenames);

    // Set up on_change handler for the file name
    props.file.on_change().connect([this](std::string fl) {
      // Check if file exists and locate index
      auto idx = util::find(props.filenames, fl);
      if (idx != props.filenames.end()) {
        props.file_it = idx;
      }
      load_file(fl);
    });
    props.file = props.filenames.front();

    // Filter stuff
    _lo_filter.type(gam::LOW_PASS);
    _lo_filter.freq(20);
    _hi_filter.type(gam::HIGH_PASS);
    _hi_filter.freq(20000);


    // More on_change handlers
    props.startpoint.on_change().connect([this](int pt) {
      sample.min((double)pt);
      props.length = props.num_samples - pt + props.endpoint;
      update_wf();
      update_scaling(sample.min(), sample.max() - 1);
      /// Clamp fadetime. When the startpoint is changed,
      /// it makes sense for the fadein to give way
      if (props.fadein + props.fadeout > props.length)
        props.fadein.set(props.length - props.fadeout - 1);
    }).call_now();

    props.endpoint.on_change().connect([this](int pt) {
      sample.max(sample.frames() + (double)pt);
      props.length = props.num_samples - props.startpoint + pt;
      update_wf();
      update_scaling(sample.min(), sample.max() - 1);
      /// Clamp fadetime. When the endpoint is changed,
      /// it makes sense for the fadeout to give way
      if (props.fadein + props.fadeout > props.length)
        props.fadeout.set(props.length - props.fadein - 1);
    }).call_now();

    props.fadein.on_change().connect([this](int fd) {
        auto sr = services::AudioManager::current().samplerate();
        env_.attack( (float)(fd * fd) / (float)sr );
        // If sum of fadeout and and fadein is too large, make fadeout smaller
        if (props.fadeout + fd > props.num_samples)
          props.fadeout.set(props.num_samples - fd - 1);
    }).call_now();

    props.fadeout.on_change().connect([this](int fd) {
      auto sr = services::AudioManager::current().samplerate();
      env_.release( (float)fd / (float)sr );
      // If sum of fadeout and and fadein is too large, make fadein smaller
      if (props.fadein + fd > props.num_samples)
        props.fadein.set(props.num_samples - fd - 1);
    }).call_now();

    props.filter.on_change()
      .connect([this](float freq) {
        if (freq > 10) {
          _lo_filter.freq(20000);
          _hi_filter.freq(freq * freq * freq * 0.2);
        } else {
          _lo_filter.freq(freq * freq * 200);
          _hi_filter.freq(20);
        }
      })
      .call_now();

    props.speed.on_change().connect([this](float spd) { sample.rate(spd); }).call_now();

    env_.finish();

  }

  void Sampler::restart()
  {
    sample.reset();
    env_.reset();
    env_countdown = props.length - props.fadeout;
  }

  void Sampler::finish()
  {
    sample.finish();
    env_.finish();
  }

  float Sampler::progress() const noexcept
  {
    return sample.done() ? 1.f : (sample.pos() - sample.min()) / float(sample.max() - sample.min());
  }

  //This is not used currently
  float Sampler::operator()() noexcept
  {
    return sample();
  }

  void Sampler::load_file(std::string filename)
  {
    bool loaded = samplefile.load(Application::current().data_dir / "samples" / filename);
    int num_samples = 1;
    if (loaded) {
      num_samples = samplefile.samples[0].size();
      props.samplerate = samplefile.getSampleRate();
      props.samplecontainer.resize(num_samples);
      props.samplecontainer.assign(samplefile.samples[0]);
      sample.buffer(props.samplecontainer, (double) props.samplerate, 1);

      // Check file

      for (auto& f : props.samplecontainer) {
        if (f == NAN or f == INFINITY or props.samplecontainer.size() == 0) {
          props.samplecontainer.resize(1);
          props.samplerate = 1;
          props.samplecontainer[0] = 0;
          sample.buffer(props.samplecontainer, (double) props.samplerate, 1);
          props.error = "Invalid file";
          goto end;
        }
      }

      DLOGI("Loaded sample file {}. Length: {}. SR: {}", filename, num_samples, props.samplerate);
      props.error = "";
    } else {
      LOGE("Error Loading sample file {}", filename);
      props.samplecontainer.resize(1);
      props.samplerate = 1;
      props.samplecontainer[0] = 0;
      sample.buffer(props.samplecontainer, (double) props.samplerate, 1);
      props.error = "Unknown Error (check log)";
    }
  end:
    props.waveform = {{props.samplecontainer.elems(), props.samplecontainer.size()}, 300};
    //auto& envscr = *dynamic_cast<SamplerEnvelopeScreen*>(_envelope_screen.get());
    update_wf();
    sample.finish();

    props.startpoint = 0;
    props.endpoint = 0;
    props.startpoint.max = num_samples - 1;
    props.endpoint.min =  -num_samples + 1;

    props.fadein = 0;
    props.fadeout = 0;
    props.fadein.max = num_samples - 1;
    props.fadeout.max = num_samples - 1;

    props.num_samples = num_samples;
    props.length = props.num_samples;
  }

  //This is used
  void Sampler::process(audio::AudioBufferHandle audio, bool triggered)
  {
    if (triggered && !note_on) {
      note_on = true;
      restart();
    } else if (!triggered && note_on) {
      note_on = false;
    }
    for (auto&& frm : audio) {
      if (env_countdown == 0) {
        env_.release();
        note_on = false;
        env_countdown--;
      }
       if (note_on) env_countdown--;

      frm += _hi_filter(_lo_filter(sample())) * props.volume * env_();
    }
  }

  void Sampler::update_scaling(int start, int end)
  {
    x_scale_factor = (width - 2 * 30) / (wfv.point_for_time(end).first - wfv.point_for_time(start).first);
  }

  void Sampler::update_wf()
  {
    auto start = sample.min();
    auto end = sample.max();

    // A waveform with the skipped ends showing
    //props.waveform.view(wfv, std::max(0.f, float(start) - 0.2f * float(end - start)),
    //                           std::min(float(start + (end - start) * 1.2f), float(sample.size() - 1)));

    // Only the playing section
    props.waveform.view(wfv, float(start), float(end));
  }

  void Sampler::draw_waveform(ui::vg::Canvas &ctx, int start, int end , float y_scale)
  {
    // Waveform
    // Positions
    float x_1 = 30;
    float x_2 = width - x_1;

    float y_bot = height - 70;

    float x_start = x_1 - wfv.point_for_time(start).first;
    float x = x_start;
    auto iter = wfv.begin();
    ctx.group([&] {

        ctx.scaleTowards({x_scale_factor, 1}, {x_1, y_bot});

        ctx.beginPath();
        ctx.moveTo(x, y_bot - *iter * y_scale);
        auto b = wfv.iter_for_time(start);
        for (; iter < b; iter++) {
          ctx.lineTo(x, y_bot - *iter * y_scale);
          x += 1;
        }
        ctx.lineTo(x, y_bot - *iter * y_scale);
        ctx.lineTo(x, y_bot);
        ctx.lineTo(x_start, y_bot);
        ctx.fill(Colors::Gray);

        // At this point, x = x_1.

        ctx.beginPath();
        ctx.moveTo(x, y_bot - *iter * y_scale);
        for (auto e = wfv.iter_for_time(end); iter < e; iter++) {
          ctx.lineTo(x, y_bot - *iter * y_scale);
          x += 1;
        }
        ctx.lineTo(x, y_bot);
        ctx.lineTo(x_1, y_bot);
        ctx.fill(Colors::White);

        // Now, x = x_2 in the scaled image.
        // Unscaled, we need to record the transition
        float sample_end = x;

        ctx.beginPath();
        ctx.moveTo(x, y_bot - *iter * y_scale);
        for (; iter < wfv.end(); iter++) {
          ctx.lineTo(x, y_bot - *iter * y_scale);
          x += 1;
        }
        ctx.lineTo(x, y_bot);
        ctx.lineTo(sample_end, y_bot);
        ctx.fill(Colors::Gray);
    });
  }

  // MAIN SCREEN //

  void SamplerMainScreen::encoder(ui::EncoderEvent ev)
  {
    auto& props = engine.props;
    // auto& sample = engine.sample;
    switch (ev.encoder) {
      case ui::Encoder::blue: props.volume.step(ev.steps); break;
      case ui::Encoder::green: props.filter.step(ev.steps); break;
      case ui::Encoder::yellow: props.speed.step(ev.steps); break;
      case ui::Encoder::red: {
        if (ev.steps > 0 && props.file_it < props.filenames.end() - 1) {
          // Clockwise, go up
          props.file_it++;
          props.file.set(*props.file_it);
        } else if (ev.steps < 0 && props.file_it > props.filenames.begin()) {
          // Counterclockwise, go down
          props.file_it--;
          props.file.set(*props.file_it);
        }
        break;
      }
    }
  }

  bool SamplerMainScreen::keypress(Key key)
  {
    switch (key) {
      case ui::Key::yellow_click: engine.props.speed = -engine.props.speed; break;
      default: return false; ;
    }
    return true;
  }

  void SamplerMainScreen::draw_filename(ui::vg::Canvas& ctx)
  {
    float y_pos = height - 30;
    float x_pos = width / 2;
    float text_width = 100;
    ctx.beginPath();
    ctx.fillStyle(Colours::Gray50);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);
    ctx.fillText(engine.props.file, {x_pos, y_pos});
    text_width = ctx.measureText(engine.props.file);
    // Arrowheads
    float x = x_pos + text_width / 2 + 20;
    int side_length = 10;
    ctx.group([&] {
      ctx.beginPath();
      ctx.moveTo(x, y_pos);
      ctx.lineTo(x - side_length, y_pos - side_length);
      ctx.lineTo(x - side_length, y_pos + side_length);
      ctx.closePath();
      ctx.stroke(Colours::Red);
      ctx.fill(Colours::Red);
    });
    x = x_pos - text_width / 2 - 20;
    ctx.group([&] {
      ctx.beginPath();
      ctx.moveTo(x, y_pos);
      ctx.lineTo(x + side_length, y_pos - side_length);
      ctx.lineTo(x + side_length, y_pos + side_length);
      ctx.closePath();
      ctx.stroke(Colours::Red);
      ctx.fill(Colours::Red);
    });
  }

  void SamplerMainScreen::draw_envelope(otto::nvg::Canvas &ctx)
  {
    constexpr auto b = vg::Box{31.f, height - 60, 258, 50.f};
    const float spacing = 15.f;
    //const float max_width = (b.width - 3 * spacing) / 3.f;
    const float aw = props.fadein.normalize();
    const float rw = props.fadeout.normalize();

    ctx.lineWidth(6.f);

    //Fade-in
    ctx.beginPath();
    ctx.moveTo(b.x - 1, b.y);
    ctx.lineTo(b.x + (b.width - 2 * spacing) * aw, b.y);
    ctx.stroke(Colours::Gray50);

    //Midpoint
    ctx.beginPath();
    ctx.moveTo(b.x + (b.width - 2 * spacing) * aw + spacing - 1, b.y);
    ctx.lineTo(b.x + b.width - spacing - (b.width - 2 * spacing) * rw + 1.f, b.y);
    ctx.stroke(Colours::Gray70);

    //Fadeout
    ctx.beginPath();
    ctx.moveTo(b.x + b.width - (b.width - 2 * spacing) * rw, b.y);
    ctx.lineTo(b.x + b.width + 1, b.y);
    ctx.stroke(Colours::Gray50);
  }

  void SamplerMainScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    // auto& props = engine.props;
    // auto& sample = engine.sample;

    ctx.font(Fonts::Norm, 35);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    /*

    if (props.error.empty()) {
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
    } else {
      ctx.beginPath();
      ctx.font(Fonts::Norm, 25);
      ctx.fillStyle(Colours::Red);
      ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);
      ctx.fillText(props.error, {160, 120}, 200);
      Box box = ctx.measureText(props.error, {160, 120}, 200);
      ctx.beginPath();
      ctx.rect(box).stroke(Colours::Red);
    }

     */

    draw_filename(ctx);

    engine.draw_waveform(ctx, props.startpoint, props.num_samples + props.endpoint, 40.f);
    draw_envelope(ctx);

  }

  // ENVELOPE SCREEN //
  void SamplerEnvelopeScreen::draw_arrowhead_left(ui::vg::Canvas& ctx, float x, float y_pos, float side_length, Colour cl)
  {
    ctx.beginPath();
    ctx.moveTo(x, y_pos);
    ctx.lineTo(x + side_length, y_pos + side_length* 0.5);
    ctx.lineTo(x + side_length, y_pos - side_length* 0.5);
    ctx.closePath();
    ctx.stroke(cl);
    ctx.fill(cl);
  }

  void SamplerEnvelopeScreen::draw_arrowhead_right(ui::vg::Canvas& ctx, float x, float y_pos, float side_length, Colour cl)
  {
    ctx.beginPath();
    ctx.moveTo(x, y_pos);
    ctx.lineTo(x - side_length, y_pos - side_length * 0.5);
    ctx.lineTo(x - side_length, y_pos + side_length * 0.5);
    ctx.closePath();
    ctx.stroke(cl);
    ctx.fill(cl);
  }

  void SamplerEnvelopeScreen::draw_envelope(otto::nvg::Canvas &ctx)
  {
    constexpr auto b = vg::Box{31.f, height - 60, 258, 50.f};
    const float spacing = 15.f;
    //const float max_width = (b.width - 3 * spacing) / 3.f;
    const float aw = props.fadein.normalize();
    const float rw = props.fadeout.normalize();

    constexpr float height = 30.f;

    ctx.lineWidth(6.f);


    //Fade-in
    ctx.beginPath();
    ctx.moveTo(b.x - 1, b.y);
    ctx.lineTo(b.x + (b.width - 2 * spacing) * aw, b.y);
    ctx.lineTo(b.x + (b.width - 2 * spacing) * aw, b.y + height);
    ctx.closePath();
    ctx.fill(Colours::Yellow);
    ctx.stroke(Colours::Yellow);

    //Midpoint
    ctx.beginPath();
    ctx.moveTo(b.x + (b.width - 2 * spacing) * aw + spacing - 1, b.y);
    ctx.lineTo(b.x + b.width - spacing - (b.width - 2 * spacing) * rw + 1.f, b.y);
    ctx.lineTo(b.x + b.width - spacing - (b.width - 2 * spacing) * rw + 1.f, b.y + height);
    ctx.lineTo(b.x + (b.width - 2 * spacing) * aw + spacing - 1, b.y + height);
    ctx.closePath();
    ctx.fill(Colours::Gray70);
    ctx.stroke(Colours::Gray70);

    //Fadeout
    ctx.beginPath();
    ctx.moveTo(b.x + b.width - (b.width - 2 * spacing) * rw, b.y);
    ctx.lineTo(b.x + b.width - (b.width - 2 * spacing) * rw, b.y + height);
    ctx.lineTo(b.x + b.width + 1, b.y);
    ctx.closePath();
    ctx.fill(Colours::Red);
    ctx.stroke(Colours::Red);
  }


  void SamplerEnvelopeScreen::encoder(ui::EncoderEvent ev)
  {
    auto& props = engine.props;
    shift = services::Controller::current().is_pressed(ui::Key::shift);
    constexpr int speedup = 10;
    switch (ev.encoder) {
      case ui::Encoder::blue: {
        if(props.startpoint < props.num_samples + props.endpoint - props.startpoint.step_size * (speedup + 1) - 1 || util::math::sgn(ev.steps) < 0)
          props.startpoint.step(ev.steps * (1 + speedup * !shift));
        break;
      }

      case ui::Encoder::green: {
        if(props.endpoint > -props.num_samples + props.startpoint + props.endpoint.step_size * (speedup + 1) + 1 || util::math::sgn(ev.steps) > 0)
          props.endpoint.step(ev.steps * (1 + speedup * !shift));
        break;
      }
      case ui::Encoder::yellow: engine.props.fadein.exp_step(ev.steps); break;
      case ui::Encoder::red: engine.props.fadeout.exp_step(ev.steps); break;
    }
  }

  void SamplerEnvelopeScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    auto& props = engine.props;

    engine.draw_waveform(ctx, props.startpoint, props.num_samples + props.endpoint, 120.f);

    // Start/End markers
    constexpr float y_pos = 30;
    constexpr float x_pos = 40;
    constexpr float arrow_size = 10;
    constexpr float spacing = 15;

    auto clb = props.startpoint != 0 ? Colours::Blue : Colours:: Gray50;
    draw_arrowhead_left(ctx, x_pos - spacing, y_pos, arrow_size, clb);
    draw_arrowhead_right(ctx, x_pos + spacing, y_pos, arrow_size, Colours::Blue);


    auto clg = props.endpoint != 0 ? Colours::Green : Colours::Gray50;
      draw_arrowhead_right(ctx, width - x_pos + spacing, y_pos, arrow_size, clg);
    draw_arrowhead_left(ctx, width - x_pos - spacing, y_pos, arrow_size, Colours::Green);

    draw_envelope(ctx);


  }


} // namespace otto::engines
