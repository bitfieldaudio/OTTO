#include "FDNReverb.hpp"
#include <algorithm>
#include <numeric>
#include "core/ui/vector_graphics.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"


#define TDEC                                                                                       \
  typename Tv,                                                                                     \
    template<typename>                                                                             \
    class LoopFilter,                                                                              \
    template<typename>                                                                             \
    class Si, class Td

#define TARG Tv, LoopFilter, Si, Td

/// FDNReverb
template<TDEC>
FDNReverb<TARG>::FDNReverb()
{
  decay(1);
  refreshMatrix();
  for (int i = 0; i < 4; i++)
    mCombs.push_back(gam::Multitap<Tv, Si, gam::Domain1>(512.f, num_taps));
  for (int i = 0; i < 3; i++) mAllpasses.push_back(gam::Comb<Tv, Si, float, gam::Domain1>(512.f));
}

template<TDEC>
FDNReverb<TARG>& FDNReverb<TARG>::resizeComb(std::initializer_list<unsigned> delays)
{
  for (unsigned i = 0; i < mCombs.size(); ++i) {
    unsigned d = delays.begin()[i];
    mCombs[i].maxDelay(d);
    for (unsigned j = 0; j < num_taps; j++) {
      mCombs[i].delay(d * (num_taps * num_taps - j * j) / (num_taps * num_taps), j);
    }
  }
  decay(decay());
  return *this;
}

template<TDEC>
FDNReverb<TARG>& FDNReverb<TARG>::resizeAllpass(std::initializer_list<unsigned> delays)
{
  for (unsigned i = 0; i < mAllpasses.size(); ++i) {
    unsigned d = delays.begin()[i];
    mAllpasses[i].maxDelay(d);
    mAllpasses[i].delay(d);
    mAllpasses[i].allPass(0.71); // all use the same feedback amount
  }
  return *this;
}

template<TDEC>
FDNReverb<TARG>& FDNReverb<TARG>::resize(std::initializer_list<unsigned> combDelays,
                                         std::initializer_list<unsigned> allpassDelays)
{
  return resizeComb(combDelays).resizeAllpass(allpassDelays);
}

template<TDEC>
FDNReverb<TARG>& FDNReverb<TARG>::decay(float v)
{
  mDecay = v;
  // float decaySamples = v * Td::spu();
  for (unsigned i = 0; i < mCombs.size(); i++) mFilters[i].gain(0.15);
  return *this;
}

template<TDEC>
FDNReverb<TARG>& FDNReverb<TARG>::damping(float v)
{
  for (unsigned i = 0; i < mCombs.size(); i++) mFilters[i].damping(v);
  return *this;
}

template<TDEC>
inline std::array<Tv, 2> FDNReverb<TARG>::operator()(Tv in)
{
  // Pass input trhough allpass filters
  for (unsigned i = 0; i < mAllpasses.size(); ++i) {
    in = mAllpasses[i](in);
  }

  // Parallel delay lines fill 4*mCombs vector.
  // Inserts input and previous filtered feedback
  std::array<Tv, 16> from_delaylines;
  std::array<Tv, 4> after_delaylines;

  for (unsigned i = 0; i < mCombs.size(); i++) {
    for (unsigned j = 0; j < num_taps; j++) {
      from_delaylines[i * num_taps + j] = mCombs[i].read(j);
    }
  }


  // Multiply with matrix: Hadamard(16)*Hadamard(Line of 4-by-4)
  for (int i = 0; i < mCombs.size(); i++) {
    after_delaylines[i] =
      std::inner_product(matrix[i].begin(), matrix[i].end(), from_delaylines.begin(), 0.f);
  }

  // Get stereo output (Weight 4 outputs into 2 delay lines)
  std::array<Tv, 2> res = {(after_delaylines[0] + after_delaylines[2]),
                           (after_delaylines[1] + after_delaylines[3])};

  // Filter 4 delay lines and insert into buffer
  for (int i = 0; i < mCombs.size(); i++) {
    mCombs[i].write(in + mFilters[i](after_delaylines[i]));
  }

  return res;

  return res;
}

template<TDEC>
void FDNReverb<TARG>::refreshMatrix()
{
  std::vector<std::vector<int>> hadamard = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1},
    {1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1},
    {1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1},
    {1, 1, 1, 1, -1, -1, -1, -1, 1, 1, 1, 1, -1, -1, -1, -1},
    {1, -1, 1, -1, -1, 1, -1, 1, 1, -1, 1, -1, -1, 1, -1, 1},
    {1, 1, -1, -1, -1, -1, 1, 1, 1, 1, -1, -1, -1, -1, 1, 1},
    {1, -1, -1, 1, -1, 1, 1, -1, 1, -1, -1, 1, -1, 1, 1, -1},
    {1, 1, 1, 1, 1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, -1, 1, -1, 1, -1, 1, -1, -1, 1, -1, 1, -1, 1, -1, 1},
    {1, 1, -1, -1, 1, 1, -1, -1, -1, -1, 1, 1, -1, -1, 1, 1},
    {1, -1, -1, 1, 1, -1, -1, 1, -1, 1, 1, -1, -1, 1, 1, -1},
    {1, 1, 1, 1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1},
    {1, -1, 1, -1, -1, 1, -1, 1, -1, 1, -1, 1, 1, -1, 1, -1},
    {1, 1, -1, -1, -1, -1, 1, 1, -1, -1, 1, 1, 1, 1, -1, -1},
    {1, -1, -1, 1, -1, 1, 1, -1, -1, 1, 1, -1, 1, -1, -1, 1}};

  std::array<std::array<float, 16>, 4> reducer = {
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
     {1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1},
     {1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1},
     {1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1, 1, -1, -1, 1}}};

  // calculate matrix
  // for now, just use the reducer matrix
  /*
  for (int i=0; i<mCombs.size()*num_taps; i++) {
    for (int j=0; i<mCombs.size(); j++) {
      matrix[j][i] = std::inner_product(reducer[j].begin(), reducer[j].end(), hadamard[i].begin(),
  0);
    }
  }
   */
  matrix = reducer;
}

/*
template<TDEC>
inline Tv FDNReverb<TARG>::read(std::initializer_list<unsigned> delays) const {
  Tv res = Tv(0);
  for(unsigned i=0; i<mCombs.size(); i){
    res = mCombs[i].read(delays.begin()[i]);
  }
  return res;
}
 */

/// Simple Pitch shifter
template<typename Tv>
SimplePitchShift<Tv>::SimplePitchShift()
{
  this->maxdelay(10000);
  this->crossfade(1000);

  for (int i = 0; i < 2; i++) {
    amp[i].attack(0.9 * _crossfade / gam::sampleRate());
    amp[i].decay(0.f);
    amp[i].sustain(1.0);
    amp[i].release(0.9 * _crossfade / gam::sampleRate());
    amp[i].finish();
  }

  lfo_delay[1].phase(0.5);
}

template<typename Tv>
Tv SimplePitchShift<Tv>::operator()(Tv in) noexcept
{
  Tv res = Tv(0);
  for (int i = 0; i < 2; i++) {
    delay_amount[i] -= 1;
    if (delay_amount[i] < 0)
      delay_amount[i] = 0;
    else if (delay_amount[i] < _crossfade) {
      amp_amount[i] = 0.f;
      amp[i].release();
    }

    if (delay_amount[(i + 1) % 2] == _crossfade) {
      delay_amount[i] = _maxdelay + _crossfade;
      amp_amount[i] = 1.;
      amp[i].reset();
    }

    delay[i].delaySamples(delay_amount[i]);
    res += delay[i](in) * amp[i]();
  }
  return res;
}

template<typename Tv>
void SimplePitchShift<Tv>::crossfade(int cf)
{
  _crossfade = cf;
  for (int i = 0; i < 2; i++) {
    delay[i].maxDelay((float) (_maxdelay + _crossfade) / gam::sampleRate());
  }
  _frac = cf / _maxdelay;
}

template<typename Tv>
void SimplePitchShift<Tv>::maxdelay(int md)
{
  _maxdelay = md;
  for (int i = 0; i < 2; i++) {
    delay[i].maxDelay((float) (_maxdelay + _crossfade) / gam::sampleRate());
  }
  _frac = _crossfade / md;
}


//------------------------------------------//
/// Reverb Engine
namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct KratosReverbScreen : EngineScreen<KratosReverb> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<KratosReverb>::EngineScreen;
  };

  KratosReverb::KratosReverb()
    : EffectEngine<KratosReverb>(std::make_unique<KratosReverbScreen>(this))
  {
    // reverb.resize({1307, 1637, 1811, 1931}, {1051, 337, 113});
    reverb.resize(gam::JCREVERB);

    shimmer_filter.type(gam::LOW_PASS);
    shimmer_filter.freq(18000);

    pre_filter.type(gam::LOW_PASS);

    output_delay[0].maxDelay(211.f / gam::sampleRate());
    output_delay[1].maxDelay(179.f / gam::sampleRate());

    props.filter.on_change().connect(
      [this](float flt) { pre_filter.freq(3000 + flt * flt * 17000); });
    props.shimmer.on_change().connect([this](float sh) { shimmer_amount = sh * 0.03; });
    props.length.on_change().connect([this](float len) { reverb.decay(3.f * len); });
    props.damping.on_change().connect([this](float damp) { reverb.damping(damp); });
  }


  audio::ProcessData<2> KratosReverb::process(audio::ProcessData<1> data)
  {
    auto buf = Application::current().audio_manager->buffer_pool().allocate_multi<2>();
    for (auto&& [dat, bufL, bufR] : util::zip(data.audio, buf[0], buf[1])) {
      auto frm = reverb(pre_filter(dat) + last_sample * shimmer_amount);
      last_sample = dc_block(shimmer_filter(pitchshifter(frm)));

      bufL = output_delay[0](frm);
      bufR = output_delay[1](frm);
    }
    return data.redirect(buf);
  }

  // SCREEN //

  void KratosReverbScreen::rotary(ui::RotaryEvent ev)
  {
    auto& props = engine.props;
    switch (ev.rotary) {
    case Rotary::blue: props.filter.step(ev.clicks); break;
    case Rotary::green: props.length.step(ev.clicks); break;
    case Rotary::yellow: props.shimmer.step(ev.clicks); break;
    case Rotary::red: props.damping.step(ev.clicks); break;
    }
  }

  bool KratosReverbScreen::keypress(ui::Key key)
  {
    return false;
  }

  void KratosReverbScreen::draw(ui::vg::Canvas& ctx)
  {
    {
      using namespace ui::vg;
      using util::math::vec;

      auto& props = engine.props;

      // declaration of star radius of first group of stars
      float starradius = 3;
      vec direction = vec{3, -2} * (engine.props.length.normalize() * 3 + 0.6);
      float minscale = 0.55;
      float frontscale =
        std::min(1.f, (minscale + engine.props.damping.normalize() * (1 - minscale) * 2));
      float backscale =
        std::min(1.f, (minscale + (1 - engine.props.damping.normalize()) * (1 - minscale) * 2));

      // 1st group of stars.
      ctx.group([&] {
        ctx.beginPath();
        ctx.circle({126.6, 75.2}, starradius);
        ctx.fillStyle(Colours::Yellow.dim(1 - engine.props.shimmer.normalize()));
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({228.8, 162.3}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({186.8, 81.3}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({259.0, 28.3}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({207.6, 192.4}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({154.8, 93.3}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({144.3, 26.3}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({257.8, 193.0}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({223.5, 128.3}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({294.1, 181.6}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({52.7, 190.3}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({106.6, 42.2}, starradius);
        ctx.fill();
      });

      // declaration of star radius of second group of stars
      float secondstarradius = 2;

      ctx.group([&] {
        // 2nd group of stars.
        ctx.beginPath();
        ctx.circle({255.3, 168.8}, secondstarradius);
        ctx.fillStyle(Colours::Yellow.dim(1 - engine.props.shimmer.normalize()));

        // (stars)
        ctx.beginPath();
        ctx.circle({149.5, 60.6}, secondstarradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({200.6, 164.6}, secondstarradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({77.6, 164.7}, secondstarradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({175.2, 48.8}, secondstarradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({228.0, 147.9}, secondstarradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({228.6, 206.1}, secondstarradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({294.0, 106.1}, secondstarradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({159.3, 112.0}, secondstarradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({289.7, 202.0}, secondstarradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({45.9, 164.4}, secondstarradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({100.4, 212.8}, secondstarradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({100.5, 65.7}, secondstarradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({213.7, 83.2}, secondstarradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({213.0, 91.9}, secondstarradius);
        ctx.fill();
      });

      // 3rd group of stars. for tobias.
      ctx.group([&] {
        ctx.beginPath();
        ctx.circle({273, 68}, starradius);
        ctx.fillStyle(Colours::Yellow.dim(1 - engine.props.shimmer.normalize()));
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({255, 118}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({220, 57}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({200, 87}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({203, 142}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({113, 123}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({106, 176}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({159, 164}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({154, 190}, starradius);
        ctx.fill();

        // (stars)
        ctx.beginPath();
        ctx.circle({182, 185}, starradius);
        ctx.fill();
      });

      // mass value
      ctx.save();
      ctx.font(Fonts::Norm, 40);
      ctx.fillStyle(Colours::Blue);
      ctx.fillText(fmt::format("{}", std::round(props.filter * 100)), 22.9, 76.2);

      // mass text
      ctx.font(Fonts::Norm, 25);
      ctx.fillStyle(Colours::White);
      ctx.fillText("treble", 22.9, 35.4);

      ctx.restore();

      // stars value
      ctx.save();
      ctx.font(Fonts::Norm, 40);
      ctx.fillStyle(Colours::Yellow);
      ctx.fillText(fmt::format("{}", std::round(props.shimmer * 100)), 22.9, 147.9);

      // stars text
      ctx.font(Fonts::Norm, 25);
      ctx.fillStyle(Colours::White);
      ctx.fillText("stars", 22.9, 106.1);

      ctx.restore();


      // Green Dot at the end
      ctx.beginPath();
      ctx.circle({241.1, 85.3}, 3);
      ctx.lineWidth(6.0);
      ctx.strokeStyle(Colours::Green);
      ctx.stroke();

      // WormHole/GreenLine
      ctx.beginPath();
      ctx.moveTo(144.3, 151.2);
      ctx.lineTo(241.1, 85.3);
      ctx.lineWidth(6.0);
      ctx.strokeStyle(Colours::Green);
      ctx.lineCap(Canvas::LineCap::ROUND);
      ctx.lineJoin(Canvas::LineJoin::ROUND);
      ctx.stroke();

      // WormHole/BackPad
      ctx.group([&] {
        Point translation = direction * 5;

        ctx.beginPath();
        ctx.translate(translation);
        ctx.lineWidth(6 / backscale);
        ctx.scaleTowards(backscale, {192.714, 118.458});
        ctx.moveTo(226.4, 176.1);
        ctx.lineTo(226.4, 95.0);
        ctx.lineTo(159.0, 60.8);
        ctx.lineTo(159.0, 103.6);
        ctx.bezierCurveTo(159.0, 79.2, 172.3, 68.2, 192.7, 78.2);
        ctx.bezierCurveTo(213.1, 88.2, 226.4, 108.7, 226.4, 135.3);
        ctx.bezierCurveTo(226.4, 161.9, 213.9, 169.8, 192.7, 159.0);
        ctx.lineTo(226.4, 176.1);
        ctx.closePath();
        ctx.fillStyle(Colours::White);
        ctx.fill();
        ctx.strokeStyle(Colours::White);
        ctx.stroke();
      });

      // WormHole/BackOutterRing
      ctx.group([&] {
        Point translation = direction * 4.7;

        ctx.beginPath();
        ctx.translate(translation);
        ctx.lineWidth(6 / backscale);
        ctx.scaleTowards(backscale, {192.714, 118.458});
        ctx.moveTo(170.3, 113.6);
        ctx.bezierCurveTo(170.1, 111.6, 169.9, 109.6, 169.9, 107.6);
        ctx.bezierCurveTo(169.9, 91.1, 178.9, 83.7, 192.7, 90.4);
        ctx.bezierCurveTo(206.5, 97.2, 215.5, 111.1, 215.5, 129.0);
        ctx.bezierCurveTo(215.5, 147.0, 207.0, 152.3, 192.7, 145.1);
        ctx.bezierCurveTo(191.2, 144.3, 189.7, 143.4, 188.3, 142.5);
        ctx.strokeStyle(Colours::Red);
        ctx.stroke();
      });

      // WormHole/InnerRing1
      ctx.group([&] {
        Point translation = direction * -1;

        ctx.beginPath();
        ctx.translate(translation);
        ctx.moveTo(182.3, 113.6);
        ctx.bezierCurveTo(182.3, 106.1, 186.4, 102.7, 192.7, 105.8);
        ctx.bezierCurveTo(199.0, 108.9, 203.1, 115.2, 203.1, 123.5);
        ctx.bezierCurveTo(203.1, 131.7, 199.3, 134.1, 192.7, 130.8);
        ctx.stroke(Colours::Red);
      });

      // WormHole/InnerRing2
      ctx.group([&] {
        Point translation = direction * 1;

        ctx.beginPath();
        ctx.translate(translation);
        ctx.moveTo(182.3, 113.6);
        ctx.bezierCurveTo(182.3, 106.1, 186.4, 102.7, 192.7, 105.8);
        ctx.bezierCurveTo(199.0, 108.9, 203.1, 115.2, 203.1, 123.5);
        ctx.bezierCurveTo(203.1, 131.7, 199.3, 134.1, 192.7, 130.8);
        ctx.stroke(Colours::Red);
      });

      // WormHole/InnerRing3
      ctx.group([&] {
        Point translation = direction * 3.2;

        ctx.beginPath();
        ctx.translate(translation);
        ctx.moveTo(182.3, 113.6);
        ctx.bezierCurveTo(182.3, 106.1, 186.4, 102.7, 192.7, 105.8);
        ctx.bezierCurveTo(199.0, 108.9, 203.1, 115.2, 203.1, 123.5);
        ctx.bezierCurveTo(203.1, 131.7, 199.3, 134.1, 192.7, 130.8);
        ctx.stroke(Colours::Red);
      });

      // WormHole/FrontInnerRing

      ctx.group([&] {
        Point translation = direction * -4.4;

        ctx.beginPath();
        ctx.translate(translation);
        ctx.lineWidth(6 / frontscale);
        ctx.scaleTowards(frontscale, {192.714, 118.458});
        ctx.moveTo(205.4, 124.2);
        ctx.bezierCurveTo(205.4, 134.2, 200.7, 137.2, 192.7, 133.1);
        ctx.bezierCurveTo(184.7, 129.1, 180.0, 121.4, 180.0, 112.2);
        ctx.bezierCurveTo(180.0, 103.0, 185.0, 98.9, 192.7, 102.7);
        ctx.bezierCurveTo(200.4, 106.5, 205.4, 114.2, 205.4, 124.2);
        ctx.closePath();
        ctx.lineCap(Canvas::LineCap::BUTT);
        ctx.lineJoin(Canvas::LineJoin::MITER);
        ctx.miterLimit(10.0);
        ctx.stroke(Colours::Red);
      });

      // WormHole/FrontRing
      ctx.group([&] {
        Point translation = direction * -4.8;

        ctx.beginPath();
        ctx.translate(translation);
        ctx.lineWidth(6 / frontscale);
        ctx.scaleTowards(frontscale, {192.714, 118.458});
        ctx.moveTo(215.5, 129.0);
        ctx.bezierCurveTo(215.5, 147.0, 207.0, 152.3, 192.7, 145.1);
        ctx.bezierCurveTo(178.4, 137.8, 169.9, 124.1, 169.9, 107.6);
        ctx.bezierCurveTo(169.9, 91.1, 178.9, 83.7, 192.7, 90.4);
        ctx.bezierCurveTo(206.5, 97.2, 215.5, 111.1, 215.5, 129.0);
        ctx.closePath();
        ctx.stroke(Colours::Red);
      });

      // WormHole/FrontPadGroup/FrontPad3
      ctx.group([&] {
        Point translation = direction * -5;

        ctx.beginPath();
        ctx.translate(translation);
        ctx.lineWidth(6 / frontscale);
        ctx.scaleTowards(frontscale, {192.714, 118.458});
        ctx.moveTo(192.7, 158.6);
        ctx.lineTo(226.4, 175.7);
        ctx.lineTo(226.4, 134.9);
        ctx.bezierCurveTo(226.4, 161.5, 213.9, 169.4, 192.7, 158.6);
        ctx.closePath();
        ctx.fill();
        ctx.strokeStyle(Colour::bytes(250, 249, 249));
        ctx.lineCap(Canvas::LineCap::ROUND);
        ctx.lineJoin(Canvas::LineJoin::ROUND);
        ctx.stroke();

        // WormHole/FrontPadGroup/FrontPad2
        ctx.beginPath();
        ctx.moveTo(159.0, 60.4);
        ctx.lineTo(159.0, 103.2);
        ctx.bezierCurveTo(159.0, 78.8, 172.3, 67.8, 192.7, 77.8);
        ctx.bezierCurveTo(213.1, 87.9, 226.4, 108.3, 226.4, 134.9);
        ctx.lineTo(226.4, 94.6);
        ctx.lineTo(159.0, 60.4);
        ctx.closePath();
        ctx.fill();
        ctx.stroke();

        // WormHole/FrontPadGroup/FrontPad1
        ctx.beginPath();
        ctx.moveTo(192.7, 158.6);
        ctx.bezierCurveTo(171.5, 147.9, 159.0, 127.6, 159.0, 103.2);
        ctx.lineTo(159.0, 141.6);
        ctx.lineTo(192.7, 158.6);
        ctx.closePath();
        ctx.fill();
        ctx.stroke();
      });


      // WormHole/GreenLineCheat
      ctx.group([&] {
        Point fixed = {144.3, 151.2};
        Point translation = vec(177.828 + 12, 128.387 - 8) + direction * -4.4;

        if (translation.x > fixed.x) {
          ctx.beginPath();
          ctx.moveTo(144.3, 151.2);
          ctx.lineTo(translation);
          ctx.lineWidth(6.0);
          ctx.strokeStyle(Colours::Green);
          ctx.lineCap(Canvas::LineCap::ROUND);
          ctx.lineJoin(Canvas::LineJoin::ROUND);
          ctx.stroke();
        }
      });

      // Green Dot
      ctx.beginPath();
      ctx.circle({144.3, 151.2}, 3);
      ctx.lineWidth(6.0);
      ctx.strokeStyle(Colours::Green);
      ctx.stroke();
    }
  }

} // namespace otto::engines
