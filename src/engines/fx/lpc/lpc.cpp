#include "core/ui/vector_graphics.hpp"
#include "util/algorithm.hpp"
#include "util/dsp/yule_walker.hpp"

#include "lpc.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  struct LPCScreen : EngineScreen<LPC> {
    void draw(Canvas& ctx) override;
    bool keypress(Key key) override;
    void rotary(RotaryEvent e) override;

    using EngineScreen<LPC>::EngineScreen;
  };

  LPC::LPC() : EffectEngine("LPC", props, std::make_unique<LPCScreen>(this)) {}

  void LPC::makeSha(gsl::span<float> buffer, float sha_period, int lag)
  {
    util::fill(buffer, 0.f);
    for (int i = lag; i < buffer.size(); i += sha_period) {
      buffer[i] = 1;
    }
  }

  audio::ProcessData<2> LPC::process(audio::ProcessData<2> data)
  {
    // TODO: Add processing

    // auto acov = autocovariance_estimator(data, stored_data);
    // auto pitch = find_pitch(data);

    // Estimate coefficients
    // auto sigma_and_coeffs = ??
    // auto scratch_buffer = ??
    // solve_yule_walker(acov.subspan(0, props.order - 1), sigma_and_coeffs, scratch_buffer);

    // Update the filter coefficients and clear any internal state
    // filter.update_coefficients(sigma_and_coeffs.subspan(1, sigma_and_coeffs.size()))
    // filter.reset()

    // Create the source from:
    // 1. White noise
    // 2. Sha
    // 3. Harmonized Sha
    //

    // Filter the source


    // TODO :return the filter output as the engine output
    return data;
  }

  // SCREEN //

  void LPCScreen::rotary(ui::RotaryEvent ev)
  {
    // TODO: add shift + encoder behaviour
    auto& props = engine.props;
    switch (ev.rotary) {
    case Rotary::blue: props.pitch.step(ev.clicks); break;
    case Rotary::green: props.pitch_tracking.step(ev.clicks); break;
    case Rotary::yellow: props.detune.step(ev.clicks); break;
    case Rotary::red: props.snr.step(ev.clicks); break;
    }
  }

  bool LPCScreen::keypress(ui::Key key)
  {
    // TODO: add shift + encoder behaviour
    return false;
  }

  void LPCScreen::draw(ui::vg::Canvas& ctx)
  {
    // TODO
  }

} // namespace otto::engines
