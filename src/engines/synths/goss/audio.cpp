#include "audio.hpp"

namespace otto::engines::goss {

  Voice::Voice(Audio& a) noexcept : audio(a)
  {
    pipes[0].resize(1024);
    pipes[0].addSine(1, 1, 0);
    pipes[0].addSine(3, 1, 0);
    pipes[0].addSine(2, 1, 0);

    pipes[1].resize(1024);
    pipes[1].addSine(4, 1, 0);
    pipes[1].addSine(16, 0.3, 0);

    pipes[2].resize(1024);
    pipes[2].addSine(6, 0.5, 0);
    pipes[2].addSine(8, 1, 0);
    pipes[2].addSine(10, 0.5, 0);
    pipes[2].addSine(12, 1, 0);
    pipes[2].addSine(16, 0.5, 0);

    percussion.resize(1024);
    percussion.addSine(4, 0.5, 0);
    percussion.addSine(6, 1.0, 0);

    perc_env.finish();
    env_.finish();
    env_.attack(1.2);
    env_.decay(0.5);
    env_.sustain(1.f);
    env_.release(4.f); 
  }

  float Voice::operator()() noexcept
  {
    float fundamental = frequency() * (1 + 0.012 * audio.leslie * audio.pitch_modulation_hi.cos()) * 0.5;
    pipes[0].freq(fundamental);
    pipes[1].freq(fundamental);
    pipes[2].freq(fundamental);
    percussion.freq(frequency());
    float s = pipes[0]() + pipes[1]() * audio.drawbar1 + pipes[2]() * audio.drawbar2 + percussion() * perc_env();
    return s * env_();
  }

  void Voice::on_note_on(float freq_target) noexcept
  {
    env_.resetSoft();
    perc_env.resetSoft();
  }

  void Voice::on_note_off() noexcept
  {
    env_.release();
    perc_env.release();
  }

  void Voice::action(itc::prop_change<&Props::click>, float cl) noexcept
  {
    perc_env.decay(cl * 2);
    perc_env.amp(3 * cl);
  }

  Audio::Audio() noexcept
  {
    lpf.type(gam::LOW_PASS);
    lpf.freq(1800);
    lpf.res(1);
    hpf.type(gam::HIGH_PASS);
    hpf.freq(1800);
    hpf.res(1);

    leslie_filter_hi.phase(0.5);
    leslie_filter_lo.phase(0.5);
  }

  void Audio::action(Actions::rotation_variable, std::atomic<float>& ref) noexcept
  {
    shared_rotation = &ref;
  }

  void Audio::action(itc::prop_change<&Props::drawbar1>, float d1) noexcept
  {
    drawbar1 = d1;
  }
  void Audio::action(itc::prop_change<&Props::drawbar2>, float d2) noexcept
  {
    drawbar2 = d2;
  }

  void Audio::action(itc::prop_change<&Props::leslie>, float l) noexcept
  {
    leslie = l;

    leslie_speed_lo = leslie * 10;
    leslie_speed_hi = leslie * 3;
    leslie_filter_hi.freq(leslie_speed_hi);
    leslie_filter_lo.freq(leslie_speed_lo);
    leslie_amount_hi = leslie * 0.3;
    leslie_amount_lo = leslie * 0.5;
    pitch_modulation_lo.freq(leslie_speed_hi);
    pitch_modulation_hi.freq(leslie);

    rotation.freq(leslie_speed_hi / 4.f);
  }

  float Audio::operator()() noexcept
  {
    // TODO: Once per buffer
    *shared_rotation = rotation.nextPhase();

    float voices = voice_mgr_();

    float s_lo = lpf(voices) * (1 + leslie_amount_lo * leslie_filter_lo.cos());
    float s_hi = hpf(voices) * (1 + leslie_amount_hi * leslie_filter_hi.cos());
    return s_lo + s_hi;
  }

  audio::ProcessData<1> Audio::process(audio::ProcessData<1> data) noexcept
  {
    for (auto& m : data.midi) voice_mgr_.handle_midi(m);
    for (float& f : data.audio) {
      f = (*this)();
    }
    return data;
  }
} // namespace otto::engines::goss
