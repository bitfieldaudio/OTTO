#pragma once

#include "core/engine/engine.hpp"
#include "core/voices/voice_manager.hpp"

#include <initializer_list>
#include <Gamma/scl.h>
#include <Gamma/Types.h>
#include <Gamma/Delay.h>
#include <Gamma/Filter.h>
#include <Gamma/Spatial.h>

/// \tparam Tv			Value (sample) type
/// \tparam LoopFilter	Filter to insert in comb feedback loop
/// \tparam Si			Interpolation strategy
/// \tparam Td			Domain type
/// \ingroup Spatial
constexpr unsigned num_taps = 4;

template<
        typename Tv = gam::real,
        template<typename> class LoopFilter = gam::Loop1P,
        template<typename> class Si = gam::ipl::Trunc,
        class Td = gam::DomainObserver
>
class FDNReverb : public Td {
public:

    typedef std::vector<gam::Multitap<Tv, Si, gam::Domain1>> DelayLines;
    typedef std::vector<gam::Comb<Tv, Si, float, gam::Domain1>> Allpasses;

    FDNReverb();

    /// Resize delay lines

    /// \param[in] combDelays		comb delay sizes in samples
    /// \param[in] allpassDelays	allpass delay sizes in samples
    FDNReverb& resize(
            std::initializer_list<unsigned> combDelays,
            std::initializer_list<unsigned> allpassDelays
    );

    /// Set comb delay sizes in samples
    FDNReverb& resizeComb(std::initializer_list<unsigned> delays);

    ///Resize the number of filters
    FDNReverb& resizeFilters(std::initializer_list<unsigned> delays);

    /// Set allpass delay sizes in samples
    FDNReverb& resizeAllpass(std::initializer_list<unsigned> delays);

    /// Set decay length
    FDNReverb& decay(float v);

    /// Set damping factor
    FDNReverb& damping(float v);

    /// Filter next sample
    std::array<Tv, 2> operator()(Tv in);

    void refreshMatrix();

    /// Get sum of comb delay taps
    Tv read(std::initializer_list<unsigned> delays) const;


    /// Get decay length
    float decay() const { return mDecay; }

    DelayLines& combs(){ return mCombs; }

    void print() const;

private:
    float mDecay;
    DelayLines mCombs;
    std::array<LoopFilter<Tv>, 4> mFilters;
    std::array<std::array<float, 16>, 4> matrix;
    Allpasses mAllpasses;




    virtual void onDomainChange(double r){
      decay(decay());
    }
};

///Reverb Engine
namespace otto::engines {

    using namespace core;
    using namespace core::engine;
    using namespace props;

    struct KratosReverb : EffectEngine {

        struct Props : Properties<> {

            Property<float> spread     = {this, "spread",     0,  has_limits::init(0, 1),    steppable::init(0.01)};
            Property<float> shimmer = {this, "shimmer", 0,  has_limits::init(0, 0.8), steppable::init(0.01)};
            Property<float> length  = {this, "length",  0.5,  has_limits::init(0, 1),    steppable::init(0.01)};
            Property<float> damping   = {this, "damping",  1, has_limits::init(0, 2),   steppable::init(0.01)};

        } props;

        KratosReverb();

        audio::ProcessData<2> process(audio::ProcessData<1>) override;

    private:
      //FDNReverb<> reverb;
      gam::ReverbMS<> reverb;
    };

} // namespace otto::engines
