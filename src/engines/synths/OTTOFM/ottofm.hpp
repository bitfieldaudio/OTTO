#pragma once

#include "core/engine/engine.hpp"
#include "core/ui/screen.hpp"
#include "core/voices/voice_manager.hpp"
#include "core/voices/voices_ui.hpp"
#include "itc/prop.hpp"
#include "util/reflection.hpp"

namespace otto::engines::ottofm {

  using namespace core;
  using namespace core::engine;
  using namespace props;

  /// For defining frequency ratios
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

  static const std::array<Fraction, 20> fractions = {{{1, 1},
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
                                                      {7, 2},
                                                      {0, 1}}};

  /// Used for graphics. Defined here for the Algorithm definitions below.
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

  /// Defines the algorithms and gives instructions on how to draw them
  static const std::array<Algorithm, 11> algorithms = {
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
     Algorithm({3}, {Operatorline(3, 2, Drawside::middle)}), 
     Algorithm({})}};

  struct OttofmScreen;
  struct Audio;
  using Sender = EngineSender<Audio, OttofmScreen, voices::SettingsScreen, voices::EnvelopeScreen>;

  struct Actions {
    /// Use this to publish variables shared between audio and screen.
    /// In this case, activity levels of the operators.
    using activity0_variable = itc::Action<struct activity0_variable_tag, std::atomic<float>&>;
    using activity1_variable = itc::Action<struct activity1_variable_tag, std::atomic<float>&>;
    using activity2_variable = itc::Action<struct activity2_variable_tag, std::atomic<float>&>;
    using activity3_variable = itc::Action<struct activity3_variable_tag, std::atomic<float>&>;
  };

  // Properties per operator. Tag types must be templated to differentiate them //
  template<int I>
  struct feedback_tag;

  template<int I>
  struct mAtt_tag;

  template<int I>
  struct mDecrel_tag;

  template<int I>
  struct mSuspos_tag;

  template<int I>
  struct detune_tag;

  template<int I>
  struct ratio_idx_tag;

  template<int I>
  struct outLev_tag;

  struct Props : voices::SynthPropsBase<Sender> {

    template<int I>
    struct OperatorProps {
      Sender sender;
      // Envelopes
      Sender::Prop<feedback_tag<I>, float> feedback = {sender, 0, limits(0, 0.4), step_size(0.01)};
      Sender::Prop<mAtt_tag<I>, float> mAtt = {sender, 0.2f, limits(0.f, 1.f), step_size(0.01f)};
      Sender::Prop<mDecrel_tag<I>, float> mDecrel = {sender, 0.5, limits(0, 1), step_size(0.01)};
      Sender::Prop<mSuspos_tag<I>, float> mSuspos = {sender, 0.5, limits(0, 1), step_size(0.01)};
      // Oscillator
      Sender::Prop<detune_tag<I>, float> detune = {sender, 0, limits(-1, 1), step_size(0.01)};
      Sender::Prop<ratio_idx_tag<I>, int> ratio_idx = {sender, 0, limits(0, 19), step_size(1)};
      // Amp
      Sender::Prop<outLev_tag<I>, float> outLev = {sender, 1, limits(0, 1), step_size(0.01)};

      float current_level = 0;

      DECL_REFLECTION(OperatorProps, feedback, mAtt, mDecrel, mSuspos, detune, ratio_idx, outLev);
    };

    Sender::Prop<struct algN_tag, int, wrap> algN = {sender, 0, limits(0, 10), step_size(1)};
    Sender::Prop<struct fmAmount_tag, float> fmAmount = {sender, 1, limits(0, 1), step_size(0.01)};
    std::tuple<OperatorProps<0>, OperatorProps<1>, OperatorProps<2>, OperatorProps<3>> operators = {{sender},
                                                                                                    {sender},
                                                                                                    {sender},
                                                                                                    {sender}};
    Sender::Prop<struct cur_op_tag, int> cur_op = {sender, 0, limits(0, 3)};

    DECL_REFLECTION(Props, envelope, settings, algN, fmAmount, operators, cur_op);
  };

  struct OttofmEngine : core::engine::SynthEngine<OttofmEngine> {
    static constexpr auto name = "OTTO.FM";
    OttofmEngine();

    void encoder(core::input::EncoderEvent e) override;
    bool keypress(core::input::Key key) override;

    core::ui::ScreenAndInput screen() override;
    core::ui::ScreenAndInput envelope_screen() override;
    core::ui::ScreenAndInput voices_screen() override;

    const std::unique_ptr<Audio> audio;

    DECL_REFLECTION(OttofmEngine, props);

  private:
    const std::unique_ptr<OttofmScreen> screen_;
    voices::SettingsScreen voice_screen_;
    voices::EnvelopeScreen env_screen_;

    Sender sender_ = {*audio, *screen_, voice_screen_, env_screen_};
    Props props{sender_};

    // Probably easier like this instead of an array
    std::atomic<float> activity0_ = 0;
    std::atomic<float> activity1_ = 0;
    std::atomic<float> activity2_ = 0;
    std::atomic<float> activity3_ = 0;
  };

} // namespace otto::engines::ottofm

#include "screen.hpp"
#include "audio.hpp"
