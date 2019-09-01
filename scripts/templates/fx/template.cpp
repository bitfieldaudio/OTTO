#include "fx_example.hpp"

#include "core/ui/vector_graphics.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"

namespace otto::engines {

  using namespace ui;
  using namespace ui::vg;

  // The screen must be declared first. It should always have these three methods
  struct EngineClassNameScreen : EngineScreen<EngineClassName> {
    // What is drawn on the screen
    void draw(Canvas& ctx) override;
    // How keypresses are handled
    bool keypress(Key key) override;
    // How encoder turns are handled
    void encoder(EncoderEvent e) override;

    using EngineScreen<EngineClassName>::EngineScreen;
  };

  EngineClassName::EngineClassName() : EffectEngine<EngineClassName>(std::make_unique<EngineClassNameScreen>(this))
  {
    // Constructor for the effect.

    // Set properties of objects you are using:
    filter.type(gam::LOW_PASS);

    props.flt_freq.on_change()
      .connect([this](float f) {
        // Lets the filter sweep from 200 Hz to 12000 Hz.
        filter.freq(10000 * f + 200);
      })
      .call_now(props.flt_freq);
    // Note the call_now() method. This calls the on_change handler under the construction,
    // so you can set variables that might otherwise be uninitialised until you start changing
    // the properties.
  }

  audio::ProcessData<2> EngineClassName::process(audio::ProcessData<1> data)
  {
    // Process call for the effect. This processes an entire audio buffer at a time.

    // Allocate two audio buffers (left and right channels)
    auto buf = Application::current().audio_manager->buffer_pool().allocate_multi<2>();

    // Fill buffers with processed samples
    for (auto&& [dat, bufL, bufR] : util::zip(data.audio, buf[0], buf[1])) {
      // Process one sample. We just want to let the filter work on one sample
      // and put that in both channels for super boring stereo.
      bufL = filter(dat);
      bufR = bufL;
    }

    // Return original data with new processed audio
    return data.with(buf);
  }

  // SCREEN //

  void EngineClassNameScreen::encoder(ui::EncoderEvent ev)
  {
    auto& props = engine.props;
    // The blue encoder changes the frequency of the filter.
    // The others do nothing.
    switch (ev.encoder) {
      case Encoder::blue: {
        props.flt_freq.step(ev.steps);
        break;
      }
      case Encoder::green: {
        break;
      }
      case Encoder::yellow: {
        break;
      }
      case Encoder::red: {
        break;
      }
    }
  }

  bool EngineClassNameScreen::keypress(ui::Key key)
  {
    return false;
  }

  void EngineClassNameScreen::draw(ui::vg::Canvas& ctx)
  {
    using namespace ui::vg;

    ctx.font(Fonts::Norm, 35);
    constexpr float x_pad = 30;
    constexpr float y_pad = 50;

    // Write the text to the left
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
    ctx.fillText("Freq", {x_pad, y_pad});

    // Write the number to the right
    ctx.beginPath();
    ctx.fillStyle(Colours::Blue);
    ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
    ctx.fillText(fmt::format("{:1}", engine.props.flt_freq), {width - x_pad, y_pad});
  }

} // namespace otto::engines
