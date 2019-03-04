#include "FDNReverb.hpp"
#include <numeric>
#include "core/ui/vector_graphics.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"


#define TDEC\
	typename Tv,\
	template<typename> class LoopFilter,\
	template<typename> class Si,\
	class Td

#define TARG Tv,LoopFilter,Si,Td

///FDNReverb
template<TDEC>
FDNReverb<TARG>::FDNReverb(){
  decay(1);
  refreshMatrix();
  for (int i=0; i<4; i++) mCombs.push_back(gam::Multitap<Tv, Si, gam::Domain1>(512.f, num_taps));
  for (int i=0; i<3; i++) mAllpasses.push_back(gam::Comb<Tv, Si, float, gam::Domain1>(512.f));
}

template<TDEC>
FDNReverb<TARG>& FDNReverb<TARG>::resizeComb(std::initializer_list<unsigned> delays){
  for(unsigned i=0; i<mCombs.size(); ++i){
    unsigned d = delays.begin()[i];
    mCombs[i].maxDelay(d);
    for (unsigned j=0; j<num_taps; j++) {
      mCombs[i].delay(d*(num_taps*num_taps - j*j)/(num_taps*num_taps), j);
    }
  }
  decay(decay());
  return *this;
}

template<TDEC>
FDNReverb<TARG>& FDNReverb<TARG>::resizeAllpass(std::initializer_list<unsigned> delays){
  for(unsigned i=0; i<mAllpasses.size(); ++i){
    unsigned d = delays.begin()[i];
    mAllpasses[i].maxDelay(d);
    mAllpasses[i].delay(d);
    mAllpasses[i].allPass(0.71); // all use the same feedback amount
  }
  return *this;
}

template<TDEC>
FDNReverb<TARG>& FDNReverb<TARG>::resize(
        std::initializer_list<unsigned> combDelays,
        std::initializer_list<unsigned> allpassDelays
){
  return resizeComb(combDelays).resizeAllpass(allpassDelays);
}

template<TDEC>
FDNReverb<TARG>& FDNReverb<TARG>::decay(float v){
  mDecay = v;
  float decaySamples = v * Td::spu();
  for(unsigned i=0; i<mCombs.size(); i++) mFilters[i].gain(0.15);
  return *this;
}

template<TDEC>
FDNReverb<TARG>& FDNReverb<TARG>::damping(float v){
  for(unsigned i=0; i<mCombs.size(); i++) mFilters[i].damping(v);
  return *this;
}

template<TDEC>
inline std::array<Tv, 2> FDNReverb<TARG>::operator()(Tv in){

  //Pass input trhough allpass filters
  for(unsigned i=0; i<mAllpasses.size(); ++i){
    in = mAllpasses[i](in);
  }

  // Parallel delay lines fill 4*mCombs vector.
  // Inserts input and previous filtered feedback
  std::array<Tv, 16> from_delaylines;
  std::array<Tv, 4> after_delaylines;

  for(unsigned i=0; i<mCombs.size(); i++){
    for (unsigned j=0; j<num_taps; j++) {
      from_delaylines[i*num_taps + j] = mCombs[i].read(j);
    }
  }


  //Multiply with matrix: Hadamard(16)*Hadamard(Line of 4-by-4)
  for (int i=0; i<mCombs.size(); i++) {
    after_delaylines[i] = std::inner_product(matrix[i].begin(), matrix[i].end(), from_delaylines.begin(), 0.f);
  }

  //Get stereo output (Weight 4 outputs into 2 delay lines)
  std::array<Tv, 2> res = {(after_delaylines[0] + after_delaylines[2]), (after_delaylines[1] + after_delaylines[3])};

  //Filter 4 delay lines and insert into buffer
  for (int i=0; i<mCombs.size(); i++) {
    mCombs[i].write(in + mFilters[i](after_delaylines[i]));
  }

  return res;

  return res;
}

template<TDEC>
void FDNReverb<TARG>::refreshMatrix() {
  std::vector<std::vector<int>> hadamard = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                           {1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1},
                                           {1,1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,1,-1,-1},
                                           {1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,1,-1,-1,1},
                                           {1,1,1,1,-1,-1,-1,-1,1,1,1,1,-1,-1,-1,-1},
                                           {1,-1,1,-1,-1,1,-1,1,1,-1,1,-1,-1,1,-1,1},
                                           {1,1,-1,-1,-1,-1,1,1,1,1,-1,-1,-1,-1,1,1},
                                           {1,-1,-1,1,-1,1,1,-1,1,-1,-1,1,-1,1,1,-1},
                                           {1,1,1,1,1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1},
                                           {1,-1,1,-1,1,-1,1,-1,-1,1,-1,1,-1,1,-1,1},
                                           {1,1,-1,-1,1,1,-1,-1,-1,-1,1,1,-1,-1,1,1},
                                           {1,-1,-1,1,1,-1,-1,1,-1,1,1,-1,-1,1,1,-1},
                                           {1,1,1,1,-1,-1,-1,-1,-1,-1,-1,-1,1,1,1,1},
                                           {1,-1,1,-1,-1,1,-1,1,-1,1,-1,1,1,-1,1,-1},
                                           {1,1,-1,-1,-1,-1,1,1,-1,-1,1,1,1,1,-1,-1},
                                           {1,-1,-1,1,-1,1,1,-1,-1,1,1,-1,1,-1,-1,1}};

  std::array<std::array<float, 16>, 4> reducer = {{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                           {1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1,1,-1},
                                           {1,1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,1,-1,-1},
                                           {1,-1,-1,1,1,-1,-1,1,1,-1,-1,1,1,-1,-1,1}}};

  //calculate matrix
  // for now, just use the reducer matrix
  /*
  for (int i=0; i<mCombs.size()*num_taps; i++) {
    for (int j=0; i<mCombs.size(); j++) {
      matrix[j][i] = std::inner_product(reducer[j].begin(), reducer[j].end(), hadamard[i].begin(), 0);
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

//------------------------------------------//
///Reverb Engine
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
            : EffectEngine("Kratos", props, std::make_unique<KratosReverbScreen>(this))
    {
      //reverb.resize({1307, 1637, 1811, 1931}, {1051, 337, 113});
      reverb.resize(gam::JCREVERB);
      // Set decay length, in seconds
      reverb.decay(2);

      // Set high-frequency damping factor in [0, 1]
      reverb.damping(0.4);
    }


    audio::ProcessData<2> KratosReverb::process(audio::ProcessData<1> data)
    {
      auto buf = Application::current().audio_manager->buffer_pool().allocate_multi<2>();
      for (auto&& [dat, bufL, bufR] : util::zip(data.audio, buf[0], buf[1])) {
        auto frm = reverb(dat);
        //bufL = frm[0];
        //bufR = frm[1];
        bufL = frm;
        bufR = frm;
      }
      return data.redirect(buf);
    }

    // SCREEN //

    void KratosReverbScreen::rotary(ui::RotaryEvent ev)
    {
      auto& props = engine.props;
      switch (ev.rotary) {
        case Rotary::blue: props.spread.step(ev.clicks); break;
        case Rotary::green: props.length.step(ev.clicks); break;
        case Rotary::yellow: props.shimmer.step(ev.clicks); break;
        case Rotary::red: props.damping.step(ev.clicks); break;
      }
    }

    bool KratosReverbScreen::keypress(ui::Key key)
    {
      return false;
    }

    void KratosReverbScreen::draw(ui::vg::Canvas& ctx) {
      using namespace ui::vg;
      using util::math::vec;

      auto &props = engine.props;
    }



} // namespace otto::engines