#pragma once

#include <Gamma/Envelope.h>
#include <Gamma/Filter.h>
#include <Gamma/Oscillator.h>

#include "core/voices/voice_manager.hpp"
#include "goss.hpp"

namespace otto::engines::goss {

  struct Voice : voices::VoiceBase<Voice> {
    Voice(Audio& a) noexcept;

    float operator()() noexcept;

    void on_note_on(float) noexcept;
    void on_note_off() noexcept;

    void action(itc::prop_change<&Props::click>, float c) noexcept;

  private:
    Audio& audio;

    std::array<gam::Osc<>, 3> models;
    gam::Osc<> percussion;
    gam::AD<> perc_env{0.001, 0.2};
    gam::ADSR<> env_ = {0.1f, 0.1f, 0.7f, 2.0f, 1.f, -4.f};
  };

  struct Audio {
    Audio() noexcept;

    void action(Actions::rotation_variable, std::atomic<float>&) noexcept;
    void action(itc::prop_change<&Props::leslie>, float l) noexcept;
    void action(itc::prop_change<&Props::model>, int m) noexcept;
    void action(itc::prop_change<&Props::drawbar2>, float d2) noexcept;

    template<typename Tag, typename... Args>
    auto action(itc::Action<Tag, Args...> a, Args... args) noexcept
      -> std::enable_if_t<itc::ActionReciever::is<voices::VoiceManager<Voice, 6>, itc::Action<Tag, Args...>>>
    {
      voice_mgr_.action(a, args...);
    }

    float operator()() noexcept;

    audio::ProcessData<1> process(audio::ProcessData<1>) noexcept;

  private:
    friend Voice;

    std::atomic<float>* shared_rotation = nullptr;

    static constexpr int number_of_models = 3;
    static constexpr int model_size = 9;
    using model_type = std::array<int, model_size>;
    /// Number of sine cycles for each drawbar. multiplied by 2.
    // Note: perhaps all could be divided by 2 but then we get a cusp for the second drawbar.
    static constexpr model_type cycles = {1, 3, 2, 4, 6, 8, 10, 12, 16};
    /// The drawbar settings. correspond to typical hammond drawbars in ascending order.
    static constexpr std::array<model_type, number_of_models> model_params = {{{1, 1, 1, 1, 1, 1, 1, 1, 1},
                                                                              {8, 8, 0, 0, 0, 0, 3, 8, 1},
                                                                              {8, 7, 6, 5, 4, 5, 6, 7, 1}}};
    void generate_model(gam::Osc<>&, model_type);

    float leslie = 0.f;
    float drawbar2 = 0.f;

    int model = 0;

    float leslie_speed_hi = 0.f;
    float leslie_speed_lo = 0.f;
    float leslie_amount_hi = 0.f;
    float leslie_amount_lo = 0.f;

    gam::LFO<> leslie_filter_hi;
    gam::LFO<> leslie_filter_lo;
    gam::LFO<> pitch_modulation_lo;
    gam::LFO<> pitch_modulation_hi;

    gam::AccumPhase<> rotation;

    gam::Biquad<> lpf;
    gam::Biquad<> hpf;

    voices::VoiceManager<Voice, 6> voice_mgr_ = {*this};
  };
} // namespace otto::engines::goss
