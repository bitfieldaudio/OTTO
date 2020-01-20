#include "audio.hpp"

#include "services/application.hpp"
#include "util/math.hpp"

namespace otto::engines::goss {

  Voice::Voice(Audio& a) noexcept : audio(a)
  {
    // Point player to a table for safety
    voice_player.source(audio.models[0].table());
    // Point percussion to table
    percussion_player.source(audio.percussion.table());

    perc_env.finish();
    env_.finish();
    env_.attack(0.01);
    env_.decay(0.5);
    env_.sustain(1.f);
    env_.release(4.f);
  }

  float Voice::operator()() noexcept
  {
    float fundamental = frequency() * (1 + 0.012 * audio.leslie * audio.pitch_modulation_hi.cos()) * 0.5;
    voice_player.freq(fundamental);
    percussion_player.freq(frequency());
    float s = voice_player() + (percussion_player() + noise() * 0.4) * perc_env();
    float s_drive = util::math::fasttanh3(audio.gain * s) * audio.output_scaling;
    return s_drive * env_();
  }

  void Voice::on_note_on(float freq_target) noexcept
  {
    env_.resetSoft();
    perc_env.resetSoft();
  }

  void Voice::on_note_off() noexcept
  {
    env_.release();
  }

  void Voice::action(itc::prop_change<&Props::click>, float cl) noexcept
  {
    // perc_env.decay(cl);
    perc_env.amp(cl * cl * cl * 0.5f);
  }

  void Voice::action(itc::prop_change<&Props::model>, int m) noexcept
  {
    voice_player.source(audio.models[m].table());
  }

  // Audio
  Audio::Audio(itc::Shared<float> rotation) noexcept : shared_rotation_(rotation)
  {
    // Generate models
    for (auto&& [m, p] : util::zip(models, model_params)) {
      generate_model(m, p);
    }

    // Generate percussion table
    percussion.addSine(4, 0.5, 0);
    percussion.addSine(6, 1.0, 0);

    lpf.type(gam::LOW_PASS);
    lpf.freq(1800);
    lpf.res(1);
    hpf.type(gam::HIGH_PASS);
    hpf.freq(1800);
    hpf.res(1);

    leslie_filter_hi.phase(0.5);
    leslie_filter_lo.phase(0.5);
  }

  void Audio::generate_model(gam::Osc<>& osc, model_type param)
  {
    osc.resize(2048);
    for (auto&& [i, s] : util::view::indexed(param)) {
      osc.addSine(cycles[i], (float) s / ((float) (model_size + cycles[i] * cycles[i])));
    }
  }

  void Audio::action(itc::prop_change<&Props::drive>, float d) noexcept
  {
    gain = d + 0.1;
    output_scaling = 6.f / (1 + 4 * util::math::fasttanh3(d));
  }

  void Audio::action(itc::prop_change<&Props::leslie>, float l) noexcept
  {
    leslie = l;

    leslie_speed_lo = leslie * 10;
    leslie_speed_hi = leslie * 2;
    leslie_filter_hi.freq(leslie_speed_hi);
    leslie_filter_lo.freq(leslie_speed_lo);
    leslie_amount_hi = leslie * 0.5;
    leslie_amount_lo = leslie * 0.5;
    pitch_modulation_hi.freq(leslie * leslie_speed_hi);

    rotation.freq(leslie_speed_hi / 4.f);
  }

  float Audio::operator()() noexcept
  {
    // TODO: Once per buffer
    shared_rotation_ = rotation.nextPhase();

    // Gets summed sample from all voices
    float voices = voice_mgr_();
    // Leslie
    float s_lo = voices * (1 + leslie_amount_lo * leslie_filter_lo.cos());
    float s_hi = hpf(voices) * (1 + leslie_amount_hi * leslie_filter_hi.cos());
    return s_lo + s_hi;
  }

  audio::ProcessData<1> Audio::process(audio::ProcessData<0> data) noexcept
  {
    auto buf = services::AudioManager::current().buffer_pool().allocate();
    for (auto& m : data.midi) voice_mgr_.handle_midi(m);
    for (float& f : buf) {
      f = (*this)();
    }
    return data.with(buf);
  }
} // namespace otto::engines::goss
