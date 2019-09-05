#include "synth_example.hpp"

#include "core/ui/vector_graphics.hpp"
#include "services/application.hpp"
#include "services/ui_manager.hpp"

namespace otto::engines {

    using namespace ui;
    using namespace ui::vg;

    //----------------------//
    // Voice implementation
    float EngineClassName::Voice::operator()() noexcept
    {
      // Always update the frequency
      sine_osc.freq(frequency());

      // Return the output
      return sine_osc();
    }

    EngineClassName::Voice::Voice(Pre& pre) noexcept : VoiceBase(pre)
    {
      // Constructor for the voices. Any on_change handlers would go in here
    }

    void EngineClassName::Voice::on_note_on(float freq_target) noexcept
    {
      // What should happen on a new voice trigger?
    }

    void EngineClassName::Voice::on_note_off() noexcept
    {
      // What should happen on a voice release?
    }

    //------------------------//
    // Preprocessor
    EngineClassName::Pre::Pre(Props& props) noexcept : PreBase(props)
    {
      // Constructor for the Preprocessor
    }

    void EngineClassName::Pre::operator()() noexcept
    {
      // Call operator. Note that it does not return a value.
      // No audio should be calculated here - only any variable changes that all voices depend on.
      // Examples could be a free-running LFO.
    }

    //------------------------//
    // Postprocessor
    EngineClassName::Post::Post(Pre& pre) noexcept : PostBase(pre)
    {
      // Constructor. Takes care of linking appropriate variables to props
      // Here we place any on_change handlers. For this example, we want the output level to change
      // when we change the 'level' property.
      // This allows us to keep the properties simple (say, floats from 0 to 1), while having more
      // complex variables depend on them.
      props.level.on_change().connect([this](float lv) {
          output_level = lv * lv * 4;
      });
    }

    float EngineClassName::Post::operator()(float in) noexcept
    {
      // Call operator for the Postprocessor.
      // Here we perform the volume scaling in this example
      return in * output_level;
    }

    // EngineClassName ////////////////////////////////////////////////////////////////

    audio::ProcessData<1> EngineClassName::process(audio::ProcessData<1> data)
    {
      return voice_mgr_.process(data);
    }

    // EngineClassNameScreen /////////////////////////////////////////////////////////
    // Here we construct what is drawn on screen. We also handle keypresses and encoder events
    struct EngineClassNameScreen : EngineScreen<EngineClassName> {

        // What is drawn on screen
        void draw(Canvas& ctx) override;
        // How keypresses are handled.
        bool keypress(Key key) override;
        // How encoder turns are handled
        void encoder(EncoderEvent e) override;

        using EngineScreen<EngineClassName>::EngineScreen;
    };

    EngineClassName::EngineClassName()
            : SynthEngine<EngineClassName>(std::make_unique<EngineClassNameScreen>(this)), voice_mgr_(props)
    {}

    // Implementation //

    // Keypresses are (for synths) usually only encoderclicks handled in a switch statement.
    // Here we have nothing to do in this example.
    bool EngineClassNameScreen::keypress(Key key)
    {
      return true;
    }

    // Encoder turns usually change the properties (which then might change other parameters through
    // its on_change handler.)
    void EngineClassNameScreen::encoder(EncoderEvent e)
    {
      auto& props = engine.props;

      // Here, we let the blue encoder change the level property.
      // The other encoders do nothing.
      switch (e.encoder) {
        case Encoder::blue:
          props.level.step(e.steps);
          break;
        case Encoder::green:
          break;
        case Encoder::yellow:
          break;
        case Encoder::red:
          break;
      }
    }

    // Now for the drawing
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
      ctx.fillText("Level", {x_pad, y_pad});

      // Write the number to the right
      ctx.beginPath();
      ctx.fillStyle(Colours::Blue);
      ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
      ctx.fillText(fmt::format("{:1}", engine.props.level), {width - x_pad, y_pad});
    }

} // namespace otto::engines
