#include "potion.hpp"
#include "services/application.hpp"
#include "services/ui_manager.hpp"
#include <iterator>

#include "core/ui/vector_graphics.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  /*
   * Declarations
   */

  struct PotionSynthScreen : EngineScreen<PotionSynth> {
    bool shift = false;

    std::array<int, 4> view_order = {0,1,2,3};
    void swap_order(int);
    void draw(Canvas& ctx) override;
    void draw_waveslots(Canvas& ctx);
    void draw_lfo_and_curve(Canvas& ctx);
    void draw_waveform(Canvas& ctx, Point, Size, Colour, int, int);
    void draw_waveforms(Canvas& ctx);
    void draw_level(Canvas& ctx);
    void draw_filename(Canvas& ctx);

    bool keypress(Key key) override;
    void encoder(EncoderEvent e) override;

    int cur_wave = 0;

    using EngineScreen<PotionSynth>::EngineScreen;
  };

  // PotionSynth ////////////////////////////////////////////////////////////////

  PotionSynth::PotionSynth()
    : SynthEngine<PotionSynth>(std::make_unique<PotionSynthScreen>(this)), voice_mgr_(props)
  {
    /// Load filenames into vector
    std::string path = Application::current().data_dir / "wavetables";
    for (const auto& entry : filesystem::directory_iterator(path)) {
      props.filenames.push_back(entry.path().filename());
    }
    util::sort(props.filenames);

    /// Set up on_change handlers for the file names
    props.lfo_osc.wave1.file.on_change().connect([this](std::string fl) {
      // Check if file exists and locate index
      auto idx = util::find(props.filenames, fl);
      if (idx != props.filenames.end()) {
        props.file_it[0] = idx;
      }
      load_wavetable(0, fl);
    });
    props.lfo_osc.wave2.file.on_change().connect([this](std::string fl) {
      // Check if file exists and locate index
      auto idx = util::find(props.filenames, fl);
      if (idx != props.filenames.end()) {
        props.file_it[1] = idx;
      }
      load_wavetable(1, fl);
    });
    props.curve_osc.wave1.file.on_change().connect([this](std::string fl) {
      // Check if file exists and locate index
      auto idx = util::find(props.filenames, fl);
      if (idx != props.filenames.end()) {
        props.file_it[2] = idx;
      }
      load_wavetable(2, fl);
    });
    props.curve_osc.wave2.file.on_change().connect([this](std::string fl) {
      // Check if file exists and locate index
      auto idx = util::find(props.filenames, fl);
      if (idx != props.filenames.end()) {
        props.file_it[3] = idx;
      }
      load_wavetable(3, fl);
    });



    /// Load waveforms from random files (temporary).
    props.lfo_osc.wave1.file.set(props.filenames[0]);
    props.lfo_osc.wave2.file.set(props.filenames[1]);
    props.curve_osc.wave1.file.set(props.filenames[2]);
    props.curve_osc.wave2.file.set(props.filenames[3]);
  }

  void PotionSynth::load_wavetable(int wt_number, std::string filename)
  {
    AudioFile<float> aux;
    bool loaded = aux.load(Application::current().data_dir / "wavetables" / filename);
    int num_samples = 1;
    if (loaded) {
      props.wavetables[wt_number].resize(aux.getNumSamplesPerChannel());
      props.samplerates[wt_number] = aux.getSampleRate();
      util::copy(aux.samples[0], props.wavetables[wt_number].elems());
      num_samples = aux.getNumSamplesPerChannel();
    } else {
      props.wavetables[wt_number].resize(1);
      props.samplerates[wt_number] = 1;
      props.wavetables[wt_number][0] = 0;
    }
    for (auto&& v : voice_mgr_.voices()) {
      switch (wt_number) {
      case 0:
        v.lfo_osc.waves[0].buffer(props.wavetables[0], num_samples, 1);
        break;
      case 1:
        v.lfo_osc.waves[1].buffer(props.wavetables[1], num_samples, 1);
        break;
      case 2:
        v.curve_osc.waves[0].buffer(props.wavetables[2], num_samples, 1);
        break;
      case 3:
        v.curve_osc.waves[1].buffer(props.wavetables[3], num_samples, 1);
        break;
      default: break;
      }
    }
    DLOGI("arraysize: {}", props.wavetables[wt_number].size());
  }

  PotionSynth::Pre::Pre(Props& props) noexcept : PreBase(props) {}

  void PotionSynth::Pre::operator()() noexcept {}

  PotionSynth::Post::Post(Pre& pre) noexcept : PostBase(pre) {}

  float PotionSynth::Post::operator()(float in) noexcept
  {
    if (pre.last_voice) {
      props.lfo_osc.pan_position = pre.last_voice->lfo_pan;
      props.curve_osc.pan_position = pre.last_voice->curve.value() + 1;
    }
    return in;
  }

  audio::ProcessData<1> PotionSynth::process(audio::ProcessData<1> data)
  {
    return voice_mgr_.process(data);
  }

  PotionSynth::Voice::Voice(Pre& pre) noexcept : VoiceBase(pre)
  {
    /// On_change handlers for the lfo and curve/envelope
    props.lfo_osc.lfo_speed.on_change().connect([this](float speed) { lfo.freq(speed * 3); }).call_now(props.lfo_osc.lfo_speed);
    props.curve_osc.curve_length.on_change().connect(
      [this](float decaytime) { curve.decay((1-decaytime) * 15 + 0.2); });
    /// On_change handlers for the wavetable volumes
    props.lfo_osc.wave1.volume.on_change().connect([this](float v) { lfo_osc.pan.volume1(v); });
    props.lfo_osc.wave2.volume.on_change().connect([this](float v) { lfo_osc.pan.volume2(v); });
    props.curve_osc.wave1.volume.on_change().connect([this](float v) { curve_osc.pan.volume1(v); });
    props.curve_osc.wave2.volume.on_change().connect([this](float v) { curve_osc.pan.volume2(v); });

    curve.finish();
  }

  void PotionSynth::Voice::on_note_on(float freq_target) noexcept
  {
    lfo.phase(0.f);
    curve.reset(-2);
    pre.last_voice = this;
  }

  float PotionSynth::Voice::operator()() noexcept
  {
    for (int osc = 0; osc < 2; osc++) {
      lfo_osc.waves[osc].freq(frequency());
      curve_osc.waves[osc].freq(frequency());
    }
    /// Set panning positions
    lfo_pan = lfo.tri();
    lfo_osc.pan.pos(lfo_pan);
    curve_osc.pan.pos(curve() + 1);
    /// Get next sample from wavetables
    float result = lfo_osc() + curve_osc();
    return result;
  }

  float PotionSynth::DualWavePlayer::operator()() noexcept
  {
    return pan(waves[0](), waves[1]());
  }

  /*
   * PotionSynthScreen
   */
  void PotionSynthScreen::swap_order(int slot)
  {
    int* it = util::find(view_order, slot);
    std::iter_swap(view_order.begin(), it);
  }

  bool PotionSynthScreen::keypress(Key key)
  {
    switch (key) {
    case ui::Key::blue_click: {
      swap_order(0);
      cur_wave = 0;
      break;
    }
    case ui::Key::green_click: {
      swap_order(1);
      cur_wave = 1;
      break;
    }
    case ui::Key::yellow_click: {
      swap_order(2);
      cur_wave = 2;
      break;
    }
    case ui::Key::red_click: {
      swap_order(3);
      cur_wave = 3;
      break;
    }
    default: return false; ;
    }
    return true;
  }

  void PotionSynthScreen::encoder(EncoderEvent e)
  {
    auto& props = engine.props;
    switch (e.encoder) {
    case Encoder::blue: props.lfo_osc.lfo_speed.step(e.steps); break;
    case Encoder::green: props.curve_osc.curve_length.step(e.steps); break;
    case Encoder::yellow:
      switch (cur_wave) {
      case 0: props.lfo_osc.wave1.volume.step(e.steps); break;
      case 1: props.lfo_osc.wave2.volume.step(e.steps); break;
      case 2: props.curve_osc.wave1.volume.step(e.steps); break;
      case 3: props.curve_osc.wave2.volume.step(e.steps); break;
      default: break;
      }
      break;
    case Encoder::red:
      switch (cur_wave) {
      case 0:
        if (e.steps > 0 && props.file_it[0] < props.filenames.end() - 1) {
          // Clockwise, go up
          props.file_it[0]++;
          props.lfo_osc.wave1.file.set(*props.file_it[0]);
        } else if (e.steps < 0 && props.file_it[0] > props.filenames.begin()) {
          // Counterclockwise, go down
          props.file_it[0]--;
          props.lfo_osc.wave1.file.set(*props.file_it[0]);
        }
        break;
      case 1:
        if (e.steps > 0 && props.file_it[1] < props.filenames.end() - 1) {
          // Clockwise, go up
          props.file_it[1]++;
          props.lfo_osc.wave2.file.set(*props.file_it[1]);
        } else if (e.steps < 0 && props.file_it[1] > props.filenames.begin()) {
          // Counterclockwise, go down
          props.file_it[1]--;
          props.lfo_osc.wave2.file.set(*props.file_it[1]);
        }
        break;
      case 2:
        if (e.steps > 0 && props.file_it[2] < props.filenames.end() - 1) {
          // Clockwise, go up
          props.file_it[2]++;
          props.curve_osc.wave1.file.set(*props.file_it[2]);
        } else if (e.steps < 0 && props.file_it[2] > props.filenames.begin()) {
          // Counterclockwise, go down
          props.file_it[2]--;
          props.curve_osc.wave1.file.set(*props.file_it[2]);
        }
        break;
      case 3:
        if (e.steps > 0 && props.file_it[3] < props.filenames.end() - 1) {
          // Clockwise, go up
          props.file_it[3]++;
          props.curve_osc.wave2.file.set(*props.file_it[3]);
        } else if (e.steps < 0 && props.file_it[3] > props.filenames.begin()) {
          // Counterclockwise, go down
          props.file_it[3]--;
          props.curve_osc.wave2.file.set(*props.file_it[3]);
        }
        break;
      default: break;
      }
      break;
    }
  }

  using namespace ui::vg;

  void PotionSynthScreen::draw(Canvas& ctx)
  {
    using namespace ui::vg;
    using namespace core::ui::vg;

    shift = services::Controller::current().is_pressed(ui::Key::shift);

    ctx.font(Fonts::Norm, 35);

    draw_waveslots(ctx);
    draw_waveforms(ctx);
    draw_level(ctx);
    draw_filename(ctx);

  }

  void PotionSynthScreen::draw_waveslots(ui::vg::Canvas& ctx)
  {
    float sq_size = 25;
    float center_x = width / 2;
    float center_y = 45;
    float dist = 20;

    ctx.lineWidth(6.f);


    ///LFO and curve indicators
    //LFO
    ctx.beginPath();
    ctx.arc(center_x - dist - sq_size/2, center_y, dist, -M_PI_2, M_PI_2, true);
    ctx.stroke(Colours::White);

    float rotation = - engine.props.lfo_osc.pan_position * M_PI_2;

    ctx.save();
    ctx.rotateAround(rotation, {center_x - dist - sq_size/2, center_y});
    ctx.beginPath();
    ctx.circle( {center_x - 2 * dist - sq_size/2, center_y}, 8);
    ctx.fillStyle(Colours::Blue);
    ctx.fill();
    ctx.restore();

    //Curve
    ctx.beginPath();
    ctx.arc(center_x + dist + sq_size/2, center_y, dist, -M_PI_2, M_PI_2, false);
    ctx.stroke(Colours::White);

    rotation = engine.props.curve_osc.pan_position * M_PI_2;

    ctx.save();
    ctx.rotateAround(rotation, {center_x + dist + sq_size/2, center_y});
    ctx.beginPath();
    ctx.circle( {center_x + 2 * dist + sq_size/2, center_y}, 8);
    ctx.fillStyle(Colours::Green);
    ctx.fill();
    ctx.restore();


    ///Squares
    ctx.beginPath();
    ctx.centeredSquare({center_x - dist, center_y - dist}, sq_size);
    if (cur_wave != 0) ctx.fill(Colours::Black);
    else ctx.fill(Colours::Blue);
    ctx.stroke(Colours::Blue);

    ctx.beginPath();
    ctx.centeredSquare({center_x - dist, center_y + dist}, sq_size);
    if (cur_wave != 1) ctx.fill(Colours::Black);
    else ctx.fill(Colours::Green);
    ctx.stroke(Colours::Green);

    ctx.beginPath();
    ctx.centeredSquare({center_x + dist, center_y - dist}, sq_size);
    if (cur_wave != 2) ctx.fill(Colours::Black);
    else ctx.fill(Colours::Yellow);
    ctx.stroke(Colours::Yellow);

    ctx.beginPath();
    ctx.centeredSquare({center_x + dist, center_y + dist}, sq_size);
    if (cur_wave != 3) ctx.fill(Colours::Black);
    else ctx.fill(Colours::Red);
    ctx.stroke(Colours::Red);

    ///Text and numbers
    // LFO
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", std::round(100 * engine.props.lfo_osc.lfo_speed)), {20, center_y + 20});

    ctx.beginPath();
    ctx.fillStyle(Colours::White);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("lfo", 20, center_y - 20);

    // Env
    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", std::round(100 * engine.props.curve_osc.curve_length)),
                 width - 20, center_y + 20);

    // wavetable/env digit/env
    ctx.beginPath();
    ctx.fillStyle(Colours::White);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText("env", width - 20, center_y - 20);


  }

  void PotionSynthScreen::draw_waveform(ui::vg::Canvas& ctx, Point start, Size scale, Colour cl, int steps, int wt) {
    ctx.lineWidth(6.0);
    ctx.lineCap(Canvas::LineCap::ROUND);

    ctx.beginPath();
    ctx.moveTo(start.x, start.y);
    float * val = engine.props.wavetables[wt].begin();
    int step = engine.props.wavetables[wt].size() / steps;
    //Draw only some of the values. Number of samples must be smaller
    //than number of steps.
    for (int i = 0; i < steps - 1; i++) {
      start.x += scale.w;
      val += step;
      ctx.lineTo(start.x, start.y - (*val) * scale.h);
    }
    start.x += scale.w;
    val = engine.props.wavetables[wt].end() - 1;
    ctx.lineTo(start.x, start.y - (*val) * scale.h);
    ctx.stroke(cl);
  }

  void PotionSynthScreen::draw_waveforms(ui::vg::Canvas& ctx) {
    ///Draw big waveform
    constexpr int steps = 100;
    float x_scale = 1.6;
    float x_start = width/2 + 16 - steps * x_scale / 2;

    float y_middle = 138;
    float y_scale = 35;
    draw_waveform(ctx, {x_start, y_middle}, {x_scale, y_scale}, Colours::White, steps, view_order[0]);

    ///Draw small waveforms
    constexpr int steps_small = 50;
    x_scale = 1.0;
    x_start = 50 - steps_small * x_scale / 2;
    y_middle = 110;
    float y_jump = 30;
    y_scale = 10;

    for (int i=1; i<4; i++) {
      // Choose colour
      Colour cl;
      switch (view_order[i]) {
        case 0: cl = Colours::Blue.mix(Colours::White, 0.2); break;
        case 1: cl = Colours::Green.mix(Colours::White, 0.2); break;
        case 2: cl = Colours::Yellow.mix(Colours::White, 0.2); break;
        case 3: cl = Colours::Red.mix(Colours::White, 0.2); break;
        default: break;
      }
      draw_waveform(ctx, {x_start, y_middle}, {x_scale, y_scale}, cl, steps_small, view_order[i]);
      y_middle += y_jump;
    }

  }
  void PotionSynthScreen::draw_level(ui::vg::Canvas& ctx)
  {
    float line_top = 100;
    float line_bot = 180;
    float line_x = width - 33;
    float bar_width = 20.f;
    ctx.beginPath();
    ctx.moveTo(line_x, line_top);
    ctx.lineTo(line_x, line_bot);
    ctx.lineWidth(6.0);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.closePath();
    ctx.stroke(Colours::Gray50);

    // Horizontal line
    float cur_level = 0;
    switch (cur_wave) {
    case 0: cur_level = engine.props.lfo_osc.wave1.volume.normalize(); break;
    case 1: cur_level = engine.props.lfo_osc.wave2.volume.normalize(); break;
    case 2: cur_level = engine.props.curve_osc.wave1.volume.normalize(); break;
    case 3: cur_level = engine.props.curve_osc.wave2.volume.normalize(); break;
    default: break;
    }
    ctx.beginPath();
    ctx.moveTo(line_x - 0.5 * bar_width, line_bot - cur_level * (line_bot - line_top));
    ctx.lineTo(line_x + 0.5 * bar_width, line_bot - cur_level * (line_bot - line_top));
    ctx.lineWidth(6.0);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.closePath();
    ctx.stroke(Colours::Yellow);
  }
  void PotionSynthScreen::draw_filename(ui::vg::Canvas& ctx)
  {
    float y_pos = height - 30;
    float x_pos = (float) width / 2;
    float text_width = 100;
    ctx.beginPath();
    ctx.fillStyle(Colours::Gray50);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);
    switch (cur_wave) {
    case 0: {
      ctx.fillText(engine.props.lfo_osc.wave1.file, {x_pos, y_pos});
      text_width = ctx.measureText(engine.props.lfo_osc.wave1.file);
      break;
    }
    case 1: {
      ctx.fillText(engine.props.lfo_osc.wave2.file, {x_pos, y_pos});
      text_width = ctx.measureText(engine.props.lfo_osc.wave2.file);
      break;
    }
    case 2: {
      ctx.fillText(engine.props.curve_osc.wave1.file, {x_pos, y_pos});
      text_width = ctx.measureText(engine.props.curve_osc.wave1.file);
      break;
    }
    case 3: {
      ctx.fillText(engine.props.curve_osc.wave2.file, {x_pos, y_pos});
      text_width = ctx.measureText(engine.props.curve_osc.wave2.file);
      break;
    }
    default: break;
    }
    //Arrowheads
    int x = x_pos + text_width/2 + 20;
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
    x = x_pos - text_width/2 - 20;
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
} // namespace otto::engines

// namespace otto::engines
