#include "potion.hpp"
#include "services/application.hpp"
#include "services/ui_manager.hpp"

#include "core/ui/vector_graphics.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  /*
   * Declarations
   */

  struct PotionSynthScreen : EngineScreen<PotionSynth> {

    bool shift = false;

    void draw(Canvas& ctx) override;
    void draw_waveslots(Canvas& ctx);
    void draw_lfo_and_curve(Canvas& ctx);
    void draw_waveforms(Canvas& ctx);
    void draw_level(Canvas& ctx);
    void draw_filename(Canvas& ctx);

    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    int cur_wave = 0;

    using EngineScreen<PotionSynth>::EngineScreen;
  };

  // PotionSynth ////////////////////////////////////////////////////////////////

  PotionSynth::PotionSynth()
    : SynthEngine("Potion", props, std::make_unique<PotionSynthScreen>(this)),
      voice_mgr_(props)
  {
    ///Load filenames into vector
    std::string path = Application::current().data_dir / "wavetables";
    for (const auto & entry : filesystem::directory_iterator(path)) {
      props.filenames.push_back(entry.path().filename());
    }
    util::sort(props.filenames);

    ///Set up on_change handlers for the file names
    props.lfo_osc.wave1.file.on_change().connect([this](std::string fl) {
        //Check if file exists and locate index
        auto idx = util::find(props.filenames, fl);
        if (idx != props.filenames.end()) {
          props.file_it[0] = idx;
        }
        load_wavetable(0, fl);
    });
    props.lfo_osc.wave2.file.on_change().connect([this](std::string fl) {
        //Check if file exists and locate index
        auto idx = util::find(props.filenames, fl);
        if (idx != props.filenames.end()) {
          props.file_it[1] = idx;
        }
        load_wavetable(1, fl);
    });
    props.curve_osc.wave1.file.on_change().connect([this](std::string fl) {
        //Check if file exists and locate index
        auto idx = util::find(props.filenames, fl);
        if (idx != props.filenames.end()) {
          props.file_it[2] = idx;
        }
        load_wavetable(2, fl);
    });
    props.curve_osc.wave2.file.on_change().connect([this](std::string fl) {
        //Check if file exists and locate index
        auto idx = util::find(props.filenames, fl);
        if (idx != props.filenames.end()) {
          props.file_it[3] = idx;
        }
        load_wavetable(3, fl);
    });



    ///Load waveforms from random files (temporary).
    props.lfo_osc.wave1.file.set(props.filenames[0]);
    props.lfo_osc.wave2.file.set(props.filenames[1]);
    props.curve_osc.wave1.file.set(props.filenames[2]);
    props.curve_osc.wave2.file.set(props.filenames[3]);

  }

  void PotionSynth::load_wavetable(int wt_number, std::string filename)
  {
    AudioFile<float> aux;
    aux.load(Application::current().data_dir / "wavetables" / filename);
    props.wavetables[wt_number].resize(aux.getNumSamplesPerChannel());
    props.samplerates[wt_number] = aux.getSampleRate();
    util::copy(aux.samples[0], props.wavetables[wt_number].elems());
    for (auto&& v : voice_mgr_.voices()) {
      switch (wt_number) {
        case 0: v.lfo_osc.waves[0].buffer(props.wavetables[0], aux.getNumSamplesPerChannel(), 1); break;
        case 1: v.lfo_osc.waves[1].buffer(props.wavetables[1], aux.getNumSamplesPerChannel(), 1); break;
        case 2: v.curve_osc.waves[0].buffer(props.wavetables[2], aux.getNumSamplesPerChannel(), 1); break;
        case 3: v.curve_osc.waves[1].buffer(props.wavetables[3], aux.getNumSamplesPerChannel(), 1); break;
        default: break;
      }
    }
    DLOGI("arraysize: {}",props.wavetables[wt_number].size());
  }

  PotionSynth::Pre::Pre(Props& props) noexcept : PreBase(props)
  {

  }

  void PotionSynth::Pre::operator()() noexcept {}


  PotionSynth::Post::Post(Pre& pre) noexcept : PostBase(pre)
  {

  }

  float PotionSynth::Post::operator()(float in) noexcept
  {
    return in;
  }

  audio::ProcessData<1> PotionSynth::process(audio::ProcessData<1> data)
  {
    return voice_mgr_.process(data);
  }

  PotionSynth::Voice::Voice(Pre& pre) noexcept : VoiceBase(pre) {
    ///On_change handlers for the lfo and curve/envelope
    props.lfo_osc.lfo_speed.on_change().connect([this](float speed) {
      lfo.freq(speed*3);
    });
    props.curve_osc.curve_length.on_change().connect([this](float decaytime) {
      curve.decay(decaytime*10 + 0.2);
    });

    curve.finish();
  }

  void PotionSynth::Voice::on_note_on() noexcept {
    lfo.phase(0.f);
    curve.reset();
    for (int osc=0; osc<2; osc++) {
      lfo_osc.waves[osc].freq(frequency());
      curve_osc.waves[osc].freq(frequency());
    }

  }

  float PotionSynth::Voice::operator()() noexcept {
    ///Set panning positions
    lfo_osc.pan.pos(lfo.tri());
    curve_osc.pan.pos(curve());
    ///Get next sample from wavetables
    float result = lfo_osc() + curve_osc();
    return result;
  }

  float PotionSynth::DualWavePlayer::operator()() noexcept {
    return pan(waves[0]() * vol0, waves[1]() * vol1);
  }

  /*
   * PotionSynthScreen
   */

  bool PotionSynthScreen::keypress(Key key)
  {
    switch (key) {
      case ui::Key::blue_click: cur_wave = 0; break;
      case ui::Key::green_click: cur_wave = 1; break;
      case ui::Key::yellow_click: cur_wave = 2; break;
      case ui::Key::red_click: cur_wave = 3; break;
      default: return false; ;
    }
    return true;
  }

  void PotionSynthScreen::rotary(RotaryEvent e)
  {
    auto& props = engine.props;
    switch (e.rotary) {
      case Rotary::blue:
        props.lfo_osc.lfo_speed.step(e.clicks); break;
      case Rotary::green:
        props.curve_osc.curve_length.step(e.clicks); break;
      case Rotary::yellow:
        switch (cur_wave) {
          case 0: props.lfo_osc.wave1.volume.step(e.clicks); break;
          case 1: props.lfo_osc.wave2.volume.step(e.clicks); break;
          case 2: props.curve_osc.wave1.volume.step(e.clicks); break;
          case 3: props.curve_osc.wave2.volume.step(e.clicks); break;
          default:break;
        } break;
      case Rotary::red:
        switch (cur_wave) {
          case 0:
            if (e.clicks > 0 && props.file_it[0] < props.filenames.end() - 1) {
              //Clockwise, go up
              props.file_it[0]++;
              props.lfo_osc.wave1.file.set(*props.file_it[0]);
            } else if (e.clicks < 0 && props.file_it[0] > props.filenames.begin()) {
              //Counterclockwise, go down
              props.file_it[0]--;
              props.lfo_osc.wave1.file.set(*props.file_it[0]);
            }
            break;
          case 1:
            if (e.clicks > 0 && props.file_it[1] < props.filenames.end() - 1) {
              //Clockwise, go up
              props.file_it[1]++;
              props.lfo_osc.wave2.file.set(*props.file_it[1]);
            } else if (e.clicks < 0 && props.file_it[1] > props.filenames.begin()) {
              //Counterclockwise, go down
              props.file_it[1]--;
              props.lfo_osc.wave2.file.set(*props.file_it[1]);
            }
            break;
          case 2:
            if (e.clicks > 0 && props.file_it[2] < props.filenames.end() - 1) {
              //Clockwise, go up
              props.file_it[2]++;
              props.curve_osc.wave1.file.set(*props.file_it[2]);
            } else if (e.clicks < 0 && props.file_it[2] > props.filenames.begin()) {
              //Counterclockwise, go down
              props.file_it[2]--;
              props.curve_osc.wave1.file.set(*props.file_it[2]);
            }
            break;
          case 3:
            if (e.clicks > 0 && props.file_it[3] < props.filenames.end() - 1) {
              //Clockwise, go up
              props.file_it[3]++;
              props.curve_osc.wave2.file.set(*props.file_it[3]);
            } else if (e.clicks < 0 && props.file_it[3] > props.filenames.begin()) {
              //Counterclockwise, go down
              props.file_it[3]--;
              props.curve_osc.wave2.file.set(*props.file_it[3]);
            }
            break;
          default:break;
        }
      break;
    }
  }

  using namespace ui::vg;

  void PotionSynthScreen::draw(Canvas& ctx)
  {
    using namespace ui::vg;
    using namespace core::ui::vg;

    shift = Application::current().ui_manager->is_pressed(ui::Key::shift);

    ctx.font(Fonts::Norm, 35);

    draw_waveslots(ctx);
    draw_lfo_and_curve(ctx);
    draw_waveforms(ctx);
    draw_level(ctx);
    draw_filename(ctx);

    constexpr float x_pad = 30;
    constexpr float y_pad = 50;
    constexpr float space = (height - 2.f * y_pad) / 3.f;

    /*
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("C-Length", {x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.curve_osc.curve_length), {width - x_pad, y_pad});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("CurWave", {x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{}", cur_wave), {width - x_pad, y_pad + space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("LFO", {x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Yellow);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", engine.props.lfo_osc.lfo_speed), {width - x_pad, y_pad + 2 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("File", {x_pad, y_pad + 3 * space});

    ctx.beginPath();
    ctx.fillStyle(Colours::Red);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    switch(cur_wave) {
      case 0: ctx.fillText(engine.props.lfo_osc.wave1.file, {width - x_pad, y_pad + 3 * space}); break;
      case 1: ctx.fillText(engine.props.lfo_osc.wave2.file, {width - x_pad, y_pad + 3 * space}); break;
      case 2: ctx.fillText(engine.props.curve_osc.wave1.file, {width - x_pad, y_pad + 3 * space}); break;
      case 3: ctx.fillText(engine.props.curve_osc.wave2.file, {width - x_pad, y_pad + 3 * space}); break;
      default: break;
    }
     */



  }

  void PotionSynthScreen::draw_waveslots(ui::vg::Canvas& ctx) {
    float sq_size = 25;
    float center_x = width/2;
    float center_y = 45;
    float dist = 20;

    ctx.lineWidth(6.f);

    ctx.beginPath();
    ctx.centeredSquare({center_x - dist, center_y - dist}, sq_size);
    ctx.stroke(Colours::Blue);
    if (cur_wave == 0) ctx.fill(Colours::Blue);

    ctx.beginPath();
    ctx.centeredSquare({center_x - dist, center_y + dist}, sq_size);
    ctx.stroke(Colours::Green);
    if (cur_wave == 1) ctx.fill(Colours::Green);

    ctx.beginPath();
    ctx.centeredSquare({center_x + dist, center_y - dist}, sq_size);
    ctx.stroke(Colours::Yellow);
    if (cur_wave == 2) ctx.fill(Colours::Yellow);

    ctx.beginPath();
    ctx.centeredSquare({center_x + dist, center_y + dist}, sq_size);
    ctx.stroke(Colours::Red);
    if (cur_wave == 3) ctx.fill(Colours::Red);

    // LFO
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", std::round(100 * engine.props.lfo_osc.lfo_speed)), {16, 77});

    ctx.beginPath();
    ctx.fillStyle(Colours::White);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("lfo", 27.4, 35.0);

    //Env
    ctx.beginPath();
    ctx.fillStyle(Colours::Green);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1.2}", std::round(100 * engine.props.curve_osc.curve_length)), 255.2, 77.0);

    // wavetable/env digit/env
    ctx.beginPath();
    ctx.fillStyle(Colours::White);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText("env", 261.6, 36.0);

  }
  void PotionSynthScreen::draw_lfo_and_curve(ui::vg::Canvas& ctx) {

  }
  void PotionSynthScreen::draw_waveforms(ui::vg::Canvas& ctx) {

  }
  void PotionSynthScreen::draw_level(ui::vg::Canvas& ctx) {

    float line_top = 80;
    float line_bot = 170;
    float line_x = width - 50;
    float bar_width = 20.f;
    ctx.beginPath();
    ctx.moveTo(line_x, line_top);
    ctx.lineTo(line_x, line_bot);
    ctx.lineWidth(6.0);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.closePath();
    ctx.stroke(Colours::Yellow);

    // Horizontal line
    float cur_level;
    switch (cur_wave) {
      case 0: cur_level = engine.props.lfo_osc.wave1.volume.normalize(); break;
      case 1: cur_level = engine.props.lfo_osc.wave2.volume.normalize(); break;
      case 2: cur_level = engine.props.curve_osc.wave1.volume.normalize(); break;
      case 3: cur_level = engine.props.curve_osc.wave2.volume.normalize(); break;
      default: break;
    }
    ctx.beginPath();
    ctx.moveTo(
            line_x - 0.5 * bar_width,
            line_bot - cur_level * (line_bot - line_top));
    ctx.lineTo(
            line_x + 0.5 * bar_width,
            line_bot - cur_level * (line_bot - line_top));
    ctx.lineWidth(6.0);
    ctx.lineCap(Canvas::LineCap::ROUND);
    ctx.closePath();
    ctx.stroke(Colours::Yellow);

  }
  void PotionSynthScreen::draw_filename(ui::vg::Canvas& ctx) {
    float y_pos = height - 20;
    float x_pos = (float)width/2;
    ctx.beginPath();
    ctx.fillStyle(Colours::White);
    ctx.textAlign(HorizontalAlign::Center, VerticalAlign::Middle);
    switch(cur_wave) {
      case 0: ctx.fillText(engine.props.lfo_osc.wave1.file, {x_pos, y_pos}); break;
      case 1: ctx.fillText(engine.props.lfo_osc.wave2.file, {x_pos, y_pos}); break;
      case 2: ctx.fillText(engine.props.curve_osc.wave1.file, {x_pos, y_pos}); break;
      case 3: ctx.fillText(engine.props.curve_osc.wave2.file, {x_pos, y_pos}); break;
      default: break;
    }
  }
} // namespace otto::engines

// namespace otto::engines
