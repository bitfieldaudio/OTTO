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

  struct OttofmScreen;
  struct Audio;

  struct Props : voices::SynthPropsBase {
    template<int I>
    struct OperatorProps {
      template<typename Tag>
      using i_tag = meta::list<Tag, meta::c<I>>;

      OperatorProps() = default;
      OperatorProps(const OperatorProps&) = delete;

      // Envelopes
      itc::GAProp<i_tag<struct feedback_tag>, float> feedback = {0, limits(0, 0.4), step_size(0.01)};
      itc::GAProp<i_tag<struct attack_tag>, float> attack = {0.2f, limits(0.f, 1.f), step_size(0.01f)};
      itc::GAProp<i_tag<struct decay_release_tag>, float> decay_release = {0.5, limits(0, 1), step_size(0.01)};
      itc::GAProp<i_tag<struct suspos_tag>, float> suspos = {0.5, limits(0, 1), step_size(0.01)};
      // Oscillator
      itc::GAProp<i_tag<struct detune_tag>, float> detune = {0, limits(-1, 1), step_size(0.01)};
      itc::GAProp<i_tag<struct ratio_idx_tag>, int> ratio_idx = {0, limits(0, 19), step_size(1)};
      // Amp
      itc::GAProp<i_tag<struct out_level_tag>, float> out_level = {1, limits(0, 1), step_size(0.01)};

      float current_level = 0;

      DECL_REFLECTION(OperatorProps, feedback, attack, decay_release, suspos, detune, ratio_idx, out_level);
    };

    itc::GAProp<struct algorithm_idx_tag, int, wrap> algorithm_idx = {0, limits(0, 10), step_size(1)};
    itc::GAProp<struct fm_amount_tag, float> fm_amount = {1, limits(0, 1), step_size(0.01)};
    itc::GAProp<struct cur_op_tag, int> cur_op = {0, limits(0, 3)};

    std::tuple<OperatorProps<0>, OperatorProps<1>, OperatorProps<2>, OperatorProps<3>> operators;

    DECL_REFLECTION(Props, envelope, settings, algorithm_idx, fm_amount, operators, cur_op);
  };

  struct OttofmEngine : core::engine::SynthEngine<OttofmEngine> {
    static constexpr auto name = "OTTO.FM";
    OttofmEngine();

    void encoder(core::input::EncoderEvent e) override;
    bool keypress(core::input::Key key) override;

    core::ui::ScreenAndInput screen() override;
    core::ui::ScreenAndInput envelope_screen() override;
    core::ui::ScreenAndInput voices_screen() override;

  private:
    std::array<itc::Shared<float>::Storage, 4> activities_;
    const std::unique_ptr<OttofmScreen> screen_;

    voices::SettingsScreen voice_screen_;
    voices::EnvelopeScreen env_screen_;

  public:
    const std::unique_ptr<Audio> audio;
    Props props;

    DECL_REFLECTION(OttofmEngine, props);
  };

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
      if (numerator == 0) return fmt::format("0");
      else return fmt::format("{}/{}", numerator, denominator);
    }
  };

  /// Used for graphics. Defined here for the Algorithm definitions below.
  enum struct Drawside {
    left,
    middle,
    right,
    // Number of sides
    n_sides,
  };

  struct Operatorline {
    int start = 1;
    int end = 2;
    Drawside side = Drawside::middle;
  };

  struct Algorithm {
    std::array<bool, 4> modulator_flags = {false, false, false, false};
    util::local_vector<Operatorline, 4> operator_lines;

    Algorithm(std::initializer_list<int> modulator_idx = {}, util::local_vector<Operatorline, 4> op_lines = {})
      : operator_lines(op_lines)
    {
      for (auto&& idx : modulator_idx) {
        modulator_flags[idx] = true;
      }
    }
  };

  const std::array<Fraction, 20> fractions = {{
    {1, 1}, {1, 64}, {1, 32}, {3, 32}, {1, 8}, {5, 16}, {1, 2}, {5, 8},  {2, 1}, {3, 2},
    {3, 4}, {1, 4},  {5, 32}, {1, 16}, {5, 8}, {4, 1},  {7, 4}, {7, 16}, {7, 2}, {0, 1},
  }};

  /// Defines the algorithms and gives instructions on how to draw them
  const std::array<Algorithm, 11> algorithms = {{
    Algorithm({1, 2, 3},
              {
                {3, 2, Drawside::middle},
                {2, 1, Drawside::middle},
                {1, 0, Drawside::middle},
              }),
    Algorithm({1, 2, 3},
              {
                {3, 1, Drawside::left},
                {2, 1, Drawside::right},
                {1, 0, Drawside::middle},
              }),
    Algorithm({1, 2, 3},
              {
                {3, 0, Drawside::left},
                {2, 1, Drawside::middle},
                {1, 0, Drawside::middle},
              }),
    Algorithm({1, 2, 3},
              {
                {3, 2, Drawside::left},
                {3, 1, Drawside::left},
                {2, 0, Drawside::right},
                {1, 0, Drawside::right},
              }),
    Algorithm({2, 3},
              {
                {3, 2, Drawside::middle},
                {2, 1, Drawside::left},
                {2, 0, Drawside::left},
              }),
    Algorithm({2, 3},
              {
                {3, 2, Drawside::middle},
                {2, 1, Drawside::middle},
              }),
    Algorithm({1, 2, 3},
              {
                {3, 0, Drawside::left},
                {2, 0, Drawside::right},
                {1, 0, Drawside::middle},
              }),
    Algorithm({1, 3},
              {
                {3, 2, Drawside::middle},
                {1, 0, Drawside::middle},
              }),
    Algorithm({3},
              {
                {3, 2, Drawside::middle},
                {3, 1, Drawside::right},
                {3, 0, Drawside::left},
              }),
    Algorithm({3},
              {
                {3, 2, Drawside::middle},
              }),
    Algorithm({}),
  }};


} // namespace otto::engines::ottofm
