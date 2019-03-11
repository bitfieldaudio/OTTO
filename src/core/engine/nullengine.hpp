#pragma once
#include "core/engine/engine.hpp"
#include "core/ui/screen.hpp"

namespace otto::core::engine {

  /// A engine representing no engine.
  /// 
  /// Used either as an "OFF" engine, or while the active engine is being switched.
  /// 
  /// For synths, the audio processing should just return an empty buffer, and for
  /// fx it returns the input. Any others should be fairly obvious then
  template<EngineType ET>
  struct NullEngine;

  template<>
  struct NullEngine<EngineType::effect> : EffectEngine {
    props::Properties<> props;
    NullEngine();

    audio::ProcessData<2> process(audio::ProcessData<1> data) noexcept override;
  };

  template<>
  struct NullEngine<EngineType::arpeggiator> : ArpeggiatorEngine {
    props::Properties<> props;
    NullEngine();
    audio::ProcessData<0> process(audio::ProcessData<0> data) noexcept override;
  };

  template<>
  struct NullEngine<EngineType::synth> : SynthEngine{
    props::Properties<> props;
    NullEngine();
    audio::ProcessData<1> process(audio::ProcessData<1> data) noexcept override;
  };

}
