#include "audio.hpp"

#include "util/math.hpp"

namespace otto::engines::ottofm {

  // VOICE //
  Voice::Voice(Audio& a) noexcept : audio(a)
  {
    util::for_each(operators, [](auto& op) { op.finish(); });
    env_.finish();
  }

  void Voice::on_note_on(float freq_target) noexcept
  {
    reset_envelopes();
  }

  void Voice::on_note_off() noexcept
  {
    release_envelopes();
  }

  void Voice::reset_envelopes() noexcept
  {
    util::for_each(operators, [](auto& op) { op.reset(); });
    env_.reset();
  }

  void Voice::release_envelopes() noexcept
  {
    util::for_each(operators, [](auto& op) { op.release(); });
    env_.release();
  }

  void Voice::set_frequencies() noexcept
  {
    util::for_each(operators, [this](auto& op) { op.freq(frequency()); });
  }

  // Voice process. We apply voice volume and increment voice frequency with next() manually,
  // since we are overwriting the default process method.
  core::audio::ProcessData<1> Voice::process(core::audio::ProcessData<1> data) noexcept
  {
    auto callOps = [&] {
      auto& [op0, op1, op2, op3] = operators;
      float aux = 0;
      switch (audio.algN_) {
        case 0: return op0(op1(op2(op3(0))));
        case 1: return op0(op1(op2(0) + op3(0)));
        case 2: return op0(op1(op2(0)) + op3(0));
        case 3: aux = op3(0); return op0(op1(aux) + op2(aux));
        case 4: aux = op2(op3(0)); return (op0(aux) + op1(aux));
        case 5: return (op0(0) + op1(op2(op3(0))));
        case 6: return op0(op1(0) + op2(0) + op3(0));
        case 7: return (op0(op1(0)) + op2(op3(0)));
        case 8: aux = op3(0); return (op0(aux) + op1(aux) + op2(aux));
        case 9: return (op0(0) + op1(0) + op2(op3(0)));
        case 10: return (op0(0) + op1(0) + op2(0) + op3(0));
        default: return 0.f;
      }
    };
    for (auto& f : data.audio) {
      next();
      set_frequencies();
      f = callOps() * volume() * env_();
    }
    return data;
  }

  // Audio //

  audio::ProcessData<1> Audio::process(audio::ProcessData<1> data) noexcept
  {
    util::indexed_for_each(voice_mgr_.last_triggered_voice().operators,
                           [&](auto i, auto& op) { shared_activity[i] = op.get_activity_level(); });

    return voice_mgr_.process(data);
  }


} // namespace otto::engines::ottofm
