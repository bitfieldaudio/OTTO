#pragma once
#include "core/engine/engine.hpp"
#include "core/ui/screen.hpp"

namespace otto::core::engine {

  /// An engine representing no engine.
  ///
  /// Used either as an "OFF" engine, or while the active engine is being switched.
  ///
  /// For synths, the audio processing should just return an empty buffer, and for
  /// fx it returns the input. Any others should be fairly obvious then.
  template<EngineType ET>
  struct NullEngine;

  template<>
  struct NullEngine<EngineType::effect> : EffectEngine<NullEngine<EngineType::effect>> {
    static constexpr util::string_ref name = "OFF";
    struct Props {
      DECL_REFLECTION_EMPTY(Props);
    } props;
    NullEngine();

    audio::ProcessData<2> process(audio::ProcessData<1> data) noexcept override;
  };

  template<>
  struct NullEngine<EngineType::arpeggiator>
    : ArpeggiatorEngine<NullEngine<EngineType::arpeggiator>> {
    static constexpr util::string_ref name = "OFF";
    struct Props {
      DECL_REFLECTION_EMPTY(Props);
    } props;
    NullEngine();
    audio::ProcessData<0> process(audio::ProcessData<0> data) noexcept override;
  };

  template<>
  struct NullEngine<EngineType::synth> : SynthEngine<NullEngine<EngineType::synth>> {
    static constexpr util::string_ref name = "OFF";
    struct Props {
      DECL_REFLECTION_EMPTY(Props);
    } props;

    NullEngine();
    audio::ProcessData<1> process(audio::ProcessData<1> data) noexcept override;

    voices::IVoiceManager& voice_mgr() override
    {
      return voice_mgr_;
    }

  private:
    struct Pre : voices::PreBase<Pre, Props> {
      using voices::PreBase<Pre, Props>::PreBase;
    };
    struct Voice : voices::VoiceBase<Voice, Pre> {
      using voices::VoiceBase<Voice, Pre>::VoiceBase;
      float operator()() noexcept
      {
        return 0;
      }
    };

    struct Post : voices::PostBase<Post, Voice> {};
    using VoiceManager = voices::VoiceManager<Post, 6>;
    VoiceManager voice_mgr_ = {props};
  };

} // namespace otto::core::engine
