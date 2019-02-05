#pragma once

#include "core/engine/engine.hpp"

#include "core/audio/faust.hpp"
#include "core/audio/voice_manager.hpp"

#include <Gamma/Oscillator.h>
#include <Gamma/Filter.h>

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct GossSynth : SynthEngine, EngineWithEnvelope {

    struct Props : Properties<> {

      Property<float> drawbar1      = {this, "drawbar1",    1,   has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> drawbar2      = {this, "drawbar2",    0.2,   has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> drawbar3      = {this, "drawbar3",    0.2,   has_limits::init(0, 1),    steppable::init(0.01)};
      Property<float> leslie        = {this, "leslie",      0.3, has_limits::init(0, 1),    steppable::init(0.01)};

    } props;

    GossSynth();

    audio::ProcessData<1> process(audio::ProcessData<1>) override;

    ui::Screen& envelope_screen() override {
      return voice_mgr_.envelope_screen();
    }

    ui::Screen& voices_screen() override {
      return voice_mgr_.settings_screen();
    }

  private:
    audio::VoiceManager<6> voice_mgr_;

    struct Voice {
        Props& props;
        std::array<gam::Sine<>, 3> pipes;
        gam::LFO<> pitch_modulation;

        float operator()() noexcept;

        float frequency() noexcept;
    };
    std::array<Voice, 6> voices = {{{props}, {props}, {props}, {props}, {props}, {props}}};

    struct PostProcessing {
        Props& props;
        float leslie_speed_hi;
        float leslie_speed_lo;
        float leslie_amount_hi;
        float leslie_amount_lo;

        gam::Biquad<> lpf;
        gam::Biquad<> hpf;
        gam::LFO<> leslie_filter_hi;
        gam::LFO<> leslie_filter_lo;


        float operator()(float) noexcept;

        PostProcessing(Props &props) noexcept;

    };
    PostProcessing post_processing = {props};
  };
} // namespace otto::engines


