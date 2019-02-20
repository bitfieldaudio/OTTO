#pragma once

#include "core/engine/engine.hpp"

#include "core/audio/faust.hpp"
#include "core/voices/voice_manager.hpp"

#include <Gamma/Envelope.h>
#include <Gamma/Oscillator.h>

namespace otto::engines {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  struct OTTOFMSynth : SynthEngine, EngineWithEnvelope {
    struct OperatorProps : Properties<> {
      using Properties::Properties;
      // clang-format off
      //Envelopes
      Property<float> feedback                = {this, "feedback",  0,   has_limits::init(0, 0.4),  steppable::init(0.01)};
      Property<float> mAtt                    = {this, "mAtt",      0.2, has_limits::init(0,    1),  steppable::init(0.01)};
      Property<float> mDecrel                 = {this, "mDecrel",   0.5, has_limits::init(0,    1),  steppable::init(0.01)};
      Property<float> mSuspos                 = {this, "mSuspos",   0.5, has_limits::init(0,    1),  steppable::init(0.01)};
      //Oscillator
      Property<float> detune                  = {this, "detune",    0,   has_limits::init(-1,   1),  steppable::init(0.01)};
      Property<int> ratio_idx                 = {this, "ratio_idx", 0,   has_limits::init(0,    18), steppable::init(1)};
      //Amp
      Property<float> outLev                  = {this, "outLev",    1,   has_limits::init(0, 1),    steppable::init(0.01)};
      // clang-format on
    };

    /// Useful structs
    struct Fraction {
        int numerator;
        int denominator;

        constexpr Fraction(int n = 1, int d = 1) : numerator(n), denominator(d) {}

        operator float() const
        {
          return float(numerator) / float(denominator);
        }

        std::string to_string() const
        {
          return fmt::format("{}/{}", numerator, denominator);
        }
    };

    /// Used for graphics.
    enum struct Drawside {
        left,
        middle,
        right,
        // Number of sides
                n_sides,
    };

    struct Operatorline {
        int start;
        int end;
        Drawside side;

        constexpr Operatorline(int st = 1, int en = 2, Drawside si = Drawside::middle)
                : start(st), end(en), side(si)
        {}
    };

    struct Algorithm {
        std::array<bool, 4> modulator_flags = {false, false, false, false};
        std::vector<Operatorline> operator_lines;

        Algorithm(std::initializer_list<int> modulator_idx = {},
                  std::vector<Operatorline> op_lines = {})
                : operator_lines(op_lines)
        {
          for (auto&& idx : modulator_idx) {
            modulator_flags[idx] = true;
          }
        }
    };

    struct Props : Properties<> {
      using Properties::Properties;
      Property<int> algN = {this, "algN",    0,   has_limits::init(0, 10),    steppable::init(1)};
      Property<float> fmAmount = {this, "fmAmount",    1,   has_limits::init(0, 1),    steppable::init(0.01)};

      std::array<OperatorProps,4> operators = {{{this,"op0"}, {this,"op1"}, {this,"op2"}, {this,"op3"}}};

      std::array<Fraction, 19> fractions = {{{1, 1},
                                            {1, 64},
                                            {1, 32},
                                            {3, 32},
                                            {1, 8},
                                            {5, 16},
                                            {1, 2},
                                            {5, 8},
                                            {2, 1},
                                            {3, 2},
                                            {3, 4},
                                            {1, 4},
                                            {5, 32},
                                            {1, 16},
                                            {5, 8},
                                            {4, 1},
                                            {7, 4},
                                            {7, 16},
                                            {7, 2}}};

      std::array<Algorithm, 11> algorithms = {
              {Algorithm({1, 2, 3},
                         {Operatorline(3, 2, Drawside::middle), Operatorline(2, 1, Drawside::middle),
                          Operatorline(1, 0, Drawside::middle)}),
                      Algorithm({1, 2, 3},
                                {Operatorline(3, 1, Drawside::left), Operatorline(2, 1, Drawside::right),
                                 Operatorline(1, 0, Drawside::middle)}),
                      Algorithm({1, 2, 3},
                                {Operatorline(3, 0, Drawside::left), Operatorline(2, 1, Drawside::middle),
                                 Operatorline(1, 0, Drawside::middle)}),
                      Algorithm({1, 2, 3},
                                {Operatorline(3, 2, Drawside::left), Operatorline(3, 1, Drawside::left),
                                 Operatorline(2, 0, Drawside::right), Operatorline(1, 0, Drawside::right)}),
                      Algorithm({2, 3},
                                {Operatorline(3, 2, Drawside::middle), Operatorline(2, 1, Drawside::left),
                                 Operatorline(2, 0, Drawside::left)}),
                      Algorithm({2, 3},
                                {Operatorline(3, 2, Drawside::middle), Operatorline(2, 1, Drawside::middle)}),
                      Algorithm({1, 2, 3},
                                {Operatorline(3, 0, Drawside::left), Operatorline(2, 0, Drawside::right),
                                 Operatorline(1, 0, Drawside::middle)}),
                      Algorithm({1, 3},
                                {Operatorline(3, 2, Drawside::middle), Operatorline(1, 0, Drawside::middle)}),
                      Algorithm({3},
                                {Operatorline(3, 2, Drawside::middle), Operatorline(3, 1, Drawside::right),
                                 Operatorline(3, 0, Drawside::left)}),
                      Algorithm({3}, {Operatorline(3, 2, Drawside::middle)}), Algorithm({})}};


    } props;

    struct FMOperator {

      //Custom version of the 'Sine' in Gamma. We need to call it with a phase offset
      //instead of a frequency offset. (Phase modulation, not frequency modulation)
      struct FMSine : public gam::AccumPhase<> {
          FMSine(float frq=440, float phs=0) : AccumPhase<>(frq, phs, 1){}
          ///Generate next sample with phase offset
          float operator()(float) noexcept;
      };

      FMOperator(float frq=440, float outlevel=1, bool modulator=false){}

      FMSine sine;
      gam::ADSR<> env;

      bool modulator; ///If it is a modulator, use the envelope.
      float outlevel;
      float feedback; ///TODO:Implement in call operator
      float fm_amount;

      float freq_ratio;
      float detune_amount;

      float operator()(float);

      void freq(float); ///Set frequency

      float level(); /// Get current level


    };

    OTTOFMSynth();

    audio::ProcessData<1> process(audio::ProcessData<1>) override;

    ui::Screen& envelope_screen() override
    {
      return voice_mgr_.envelope_screen();
    }

    ui::Screen& voices_screen() override
    {
      return voice_mgr_.settings_screen();
    }

  private:
      struct Pre : voices::PreBase<Pre, Props> {

          Pre(Props&) noexcept;

          void operator()() noexcept;
      };

      struct Voice : voices::VoiceBase<Voice, Pre> {
          //The workhorse. Implements the FM algorithms.
          float algos(int);

          std::array<FMOperator,4> operators;

          void reset_envelopes();
          void release_envelopes();

          void set_frequencies();

          Voice(Pre&) noexcept;

          float operator()() noexcept;
          void on_note_on() noexcept;
          void on_note_off() noexcept;

      private:
          friend struct OTTOFMSynthScreen;
      };

      struct Post : voices::PostBase<Post, Voice> {

          Post(Pre&) noexcept;

          float operator()(float) noexcept;
      };

    voices::VoiceManager<Post, 6> voice_mgr_;
  };
} // namespace otto::engines
