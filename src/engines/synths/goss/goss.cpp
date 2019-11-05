#include "goss.hpp"

#include "screen.hpp"
#include "audio.hpp"

#include "services/audio_manager.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines::goss {

  GossEngine::GossEngine()
    : screen_(std::make_unique<GossScreen>()), //
      audio_(std::make_unique<Audio>()),
      graphics_sndr_(services::UIManager::current().make_sndr(*screen_)),
      audio_sndr_(services::AudioManager::current().make_sndr(*audio_))
  {
    sndr_.push(Actions::rotation_variable::data(rotation_));
  }

#if false

  float GossSynth::Voice::operator()() noexcept
  {
    float fundamental = frequency() * (1 + 0.012 * props.leslie * pre.pitch_modulation_hi.cos()) * 0.5;
    pipes[0].freq(fundamental);
    pipes[1].freq(fundamental);
    pipes[2].freq(fundamental);
    percussion.freq(frequency());
    return pipes[0]() + pipes[1]() * props.drawbar1 + pipes[2]() * props.drawbar2 + percussion() * perc_env();
  }

  GossSynth::Voice::Voice(Pre& pre) noexcept : VoiceBase(pre) {
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
    props.click.on_change().connect([this](float cl) {
        perc_env.decay(cl * 2);
        perc_env.amp(3 * cl);
    }).call_now(props.click);

  }

  void GossSynth::Voice::on_note_on(float freq_target) noexcept {
    perc_env.resetSoft();
  }

  GossSynth::Pre::Pre(Props& props) noexcept : PreBase(props)
  {
    leslie_filter_hi.phase(0.5);
    leslie_filter_lo.phase(0.5);
  }

  void GossSynth::Pre::operator()() noexcept {
    props.rotation_value = rotation.nextPhase();
  }

  /// Constructor. Takes care of linking appropriate variables to props
  GossSynth::Post::Post(Pre& pre) noexcept : PostBase(pre)
  {
    lpf.type(gam::LOW_PASS);
    lpf.freq(1800);
    lpf.res(1);
    hpf.type(gam::HIGH_PASS);
    hpf.freq(1800);
    hpf.res(1);
  }

  float GossSynth::Post::operator()(float in) noexcept
  {
    float s_lo = lpf(in) * (1 + pre.leslie_amount_lo * pre.leslie_filter_lo.cos());
    float s_hi = hpf(in) * (1 + pre.leslie_amount_hi * pre.leslie_filter_hi.cos());
    return s_lo + s_hi;
  }

  audio::ProcessData<1> GossSynth::process(audio::ProcessData<1> data)
  {
    return voice_mgr_.process(data);
  }
#endif

} // namespace otto::engines::goss
