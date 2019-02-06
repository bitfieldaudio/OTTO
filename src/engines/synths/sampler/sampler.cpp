#include "sampler.hpp"

#include "core/ui/vector_graphics.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"

#include "services/audio_manager.hpp"

namespace otto::engines {

  Sample::Sample(fs::path path)
  {
    util::SoundFile sf;
    try {
      sf.open(path);
      _size = sf.size();
      _audio_data.reserve(_size);
      _waveform.reserve(_size);
      sf.read_samples(std::back_inserter(_audio_data), _size);
      util::audio::EnvelopeFollower env_fol;
      util::transform(_audio_data, std::back_inserter(_waveform), env_fol);
      speed_modifier =
        sf.info.samplerate / float(Application::current().audio_manager->samplerate());
      _start_point = 0;
      _end_point = _size;
    } catch (util::exception& e) {
      LOGE(e.what());
      _audio_data.clear();
      _waveform.clear();
      _size = 0;
    }
  }

  auto Sample::size() const noexcept
  {
    return _size;
  }

  Sample::iterator Sample::begin(float stride) const
  {
    if (stride < 0) {
      return {*this, end_point(), stride * speed_modifier};
    }
    return {*this, start_point(), stride * speed_modifier};
  }

  Sample::iterator Sample::end(float stride) const
  {
    if (stride < 0) {
      return {*this, start_point(), stride * speed_modifier};
    }
    return {*this, end_point(), stride * speed_modifier};
  }

  util::sequence<std::vector<float>::const_iterator, std::vector<float>::const_iterator>
  Sample::waveform() const
  {
    return {_waveform.begin() + start_point() / waveform_scale(), _waveform.begin() + end_point() / waveform_scale()};
  }

  int Sample::waveform_scale() const
  {
    // TODO:
    return 1;
  }

  std::size_t Sample::start_point() const
  {
    if (_start_point < 0) return 0;
    return _start_point;
  }

  std::size_t Sample::end_point() const
  {
    if (_end_point < 0) return _size;
    return _end_point;
  }

  int Sample::loop_start() const
  {
    if (_loop_start < 0) return start_point();
    return _loop_start;
  }

  int Sample::loop_end() const
  {
    if (_loop_end < 0) return end_point();
    return _loop_end;
  }

  std::size_t Sample::start_point(int val)
  {
    val = std::clamp(val, 0, (int) end_point());
    _start_point = val;
    loop_start(loop_start());
    loop_end(loop_end());
    return _start_point;
  }

  std::size_t Sample::end_point(int val)
  {
    val = std::clamp(val, (int) start_point(), (int) _size);
    _end_point = val;
    return _end_point;
  }

  int Sample::loop_start(int val)
  {
    val = std::clamp(val, (int) start_point(), loop_end() - 1);
    _loop_start = val;
    return _loop_start;
  }

  int Sample::loop_end(int val)
  {
    val = std::clamp(val, (int) loop_start() + 1, (int) end_point());
    _loop_end = val;
    return _loop_end;
  }

  Sample::iterator::iterator(const Sample& sample, std::size_t index, float stride)
    : sample(sample), _index(index), _playback_speed(stride)
  {}

  Sample::iterator::iterator(const iterator& rhs) = default;

  Sample::iterator& Sample::iterator::operator=(const iterator& rhs)
  {
    assert(&this->sample == &rhs.sample);
    do_loop = rhs.do_loop;
    _index = rhs._index;
    _playback_speed = rhs._playback_speed;
    _error = rhs._error;
    return *this;
  }

  void Sample::iterator::advance(std::ptrdiff_t d)
  {
    float int_part;
    _error = std::modf(_error + _playback_speed * d, &int_part);
    if (_error < 0) {
      int_part -= 1;
      _error += 1;
    }
    for (int i = 0; i != std::abs(int_part); i++) {
      _index += int_part / std::abs(int_part);
      if (signed_index() == loop_end() && do_loop) {
        _index = std::abs(loop_start());
      }
    }
  }

  float Sample::iterator::dereference() const
  {
    if (start_point() == end_point() || signed_index() < start_point() ||
        signed_index() >= end_point())
      return 0.f;
    return sample._audio_data[_index];
  }

  bool Sample::iterator::equal(const Sample::iterator& rhs) const
  {
    return _index == rhs._index && (signed_index() == end_point() || _error == rhs._error);
  }

  std::size_t Sample::iterator::index() const
  {
    return _index;
  }

  int Sample::iterator::start_point() const
  {
    if (_playback_speed < 0) return -sample.end_point();
    return sample.start_point();
  }

  int Sample::iterator::end_point() const
  {
    if (_playback_speed < 0) return -sample.start_point();
    return sample.end_point();
  }

  int Sample::iterator::loop_start() const
  {
    if (_playback_speed < 0) return -sample.loop_end();
    return sample.loop_start();
  }

  int Sample::iterator::loop_end() const
  {
    if (_playback_speed < 0) return -sample.loop_start();
    return sample.loop_end();
  }

  int Sample::iterator::signed_index() const
  {
    if (_playback_speed < 0) return -_index;
    return _index;
  }


  // Sampler ----------------------------------------------------


  using namespace ui;
  using namespace ui::vg;

  struct SamplerScreen : EngineScreen<Sampler> {
    void draw(Canvas& ctx) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<Sampler>::EngineScreen;
  };

  struct SamplerEnvelopeScreen : EngineScreen<Sampler> {
    void draw(Canvas& ctx) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<Sampler>::EngineScreen;
  };

  Sampler::Sampler()
    : Engine("Sampler", props, std::make_unique<SamplerScreen>(this)),
      _envelope_screen(std::make_unique<SamplerEnvelopeScreen>(this))
  {
    load_file(Application::current().data_dir / "samples" / "sample.wav");
  }

  void Sampler::restart()
  {
    sample.begin(props.speed);
  }

  float Sampler::operator()() noexcept
  {
    float frm = *play_position;
    play_position++;
    return frm;
  }

  void Sampler::load_file(fs::path path)
  {
    sample = Sample(std::move(path));
    play_position = sample.end();
  }

  audio::ProcessData<1> Sampler::process(audio::ProcessData<1> data)
  {
    for (auto& ev : data.midi) {
      util::match(ev,
                  [this](midi::NoteOnEvent& ev) {
                    play_position = sample.begin(props.speed);
                    play_position.do_loop = sample.loop;
                  },
                  [this](midi::NoteOffEvent& ev) {
                    if (sample.cut) play_position = sample.end();
                    play_position.do_loop = false;
                  },
                  [](auto&&) {});
    }
    for (auto&& [frm] : data.audio) {
      frm = *play_position;
      play_position++;
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

  void SamplerScreen::rotary(ui::RotaryEvent ev)
  {
    auto& props = engine.props;
    auto& sample = engine.sample;
    switch (ev.rotary) {
    case ui::Rotary::blue: break;
    case ui::Rotary::green: props.filter.step(ev.clicks); break;
    case ui::Rotary::yellow: props.speed.step(ev.clicks); break;
    case ui::Rotary::red:
      if (sample.cut && sample.loop) {
        sample.loop = false;
      } else if (sample.cut && !sample.loop) {
        sample.cut = false;
      } else if (!sample.cut && !sample.loop) {
        sample.loop = true;
      } else if (!sample.cut && sample.loop) {
        sample.cut = true;
      }
    }
  }

  void SamplerScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    auto& props = engine.props;
    auto& sample = engine.sample;

    ctx.font(Fonts::Norm, 20);

    ctx.beginPath();
    if (sample.cut) ctx.fillText("CUT", {10, 40});
    if (sample.loop) ctx.fillText("LOOP", {10, 65});
    ctx.fillText(fmt::format("LS: {}", sample.loop_start()), {10, 80});
    ctx.fillText(fmt::format("LE: {}", sample.loop_end()), {10, 105});
    ctx.fillText(fmt::format("CUR: {}", engine.play_position.index()), {10, 130});
  }

  // ENVELOPE SCREEN //

  void SamplerEnvelopeScreen::rotary(ui::RotaryEvent ev)
  {
    auto& sample = engine.sample;
    switch (ev.rotary) {
    case ui::Rotary::blue: sample.start_point(sample.start_point() + ev.clicks * 100); break;
    case ui::Rotary::green: sample.end_point(sample.end_point() + ev.clicks * 100); break;
    case ui::Rotary::yellow: sample.loop_start(sample.loop_start() + ev.clicks * 100); break;
    case ui::Rotary::red: sample.loop_end(sample.loop_end() + ev.clicks * 100); break;
    }
  }

  void SamplerEnvelopeScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    // auto& props = engine.props;
    auto& sample = engine.sample;

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
  }

} // namespace otto::engines
