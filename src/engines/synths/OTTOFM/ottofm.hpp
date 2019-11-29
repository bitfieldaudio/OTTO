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
  using Sender = EngineSender<Audio, OttofmScreen, voices::SettingsScreen, voices::EnvelopeScreen>;

  struct Actions {
    /// Use this to publish variables shared between audio and screen.
    /// In this case, activity levels of the operators.
    using activity0_variable = itc::Action<struct activity0_variable_tag, std::atomic<float>&>;
    using activity1_variable = itc::Action<struct activity1_variable_tag, std::atomic<float>&>;
    using activity2_variable = itc::Action<struct activity2_variable_tag, std::atomic<float>&>;
    using activity3_variable = itc::Action<struct activity3_variable_tag, std::atomic<float>&>;
  };

  //TODO: Is it okay with two senders? Or should operator props take a reference?
  struct OperatorProps {
    Sender sender;
    // Envelopes
    Sender::Prop<struct feedback_tag, float> feedback = {sender, 0, limits(0, 0.4), step_size(0.01)};
    Sender::Prop<struct mAtt_tag, float> mAtt = {sender, 0.2f, limits(0.f, 1.f), step_size(0.01f)};
    Sender::Prop<struct mDecrel, float> mDecrel = {sender, 0.5, limits(0, 1), step_size(0.01)};
    Sender::Prop<struct mSuspos_tag, float> mSuspos = {sender, 0.5, limits(0, 1), step_size(0.01)};
    // Oscillator
    Sender::Prop<struct detune_tag, float> detune = {sender, 0, limits(-1, 1), step_size(0.01)};
    Sender::Prop<struct ratio_idx_tag, int> ratio_idx = {sender, 0, limits(0, 19), step_size(1)};
    // Amp
    Sender::Prop<struct outLev_tag, float> outLev = {sender, 1, limits(0, 1), step_size(0.01)};
    
    float current_level = 0;

    DECL_REFLECTION(OperatorProps, feedback, mAtt, mDecrel, mSuspos, detune, ratio_idx, outLev);
  };

  struct Props : voices::SynthPropsBase<Sender> {
    Sender::Prop<struct algN_tag, int, wrap> algN = {sender, 0, limits(0, 10), step_size(1)};
    Sender::Prop<struct fmAmount_tag, float> fmAmount = {sender, 1, limits(0, 1), step_size(0.01)};
    std::array<OperatorProps, 4> operators;
    Sender::Prop<struct cur_op_tag, int> cur_op = {sender, 0, limits(0, 3)};

    DECL_REFLECTION(Props, envelope, settings, algN, fmAmount, operators, cur_op);
  };

  struct OttofmEngine : core::engine::SynthEngine<OttofmEngine> {
    static constexpr auto name = "otto.FM";
    using Audio = Audio;
    using Screen = OttofmScreen;
    using Props = Props;

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

} //namespace otto::engines::fm