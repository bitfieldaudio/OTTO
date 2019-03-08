#include "chorus.hpp"

#include "core/ui/vector_graphics.hpp"

#include "util/iterator.hpp"
#include "util/utility.hpp"

namespace otto::engines {

    using namespace ui;
    using namespace ui::vg;

    struct ChorusScreen : EngineScreen<Chorus> {
        void draw(Canvas& ctx) override;
        bool keypress(Key key) override;
        void rotary(RotaryEvent e) override;

        using EngineScreen<Chorus>::EngineScreen;
    };

    Chorus::Chorus()
            : EffectEngine("Chorus", props, std::make_unique<ChorusScreen>(this))
    {
      props.delay.on_change().connect([this](float delay) {
        chorus.delay(delay);
      });

      props.rate.on_change().connect([this](float rate) {
        chorus.freq(rate);
      });

      props.feedback.on_change().connect([this](float fbk) {
        chorus.fbk(fbk);
      });

      props.depth.on_change().connect([this](float depth) {
        chorus.depth(depth);
      });
    }
  }

  bool ChorusScreen::keypress(ui::Key key)
  {
    return false;
  }

    audio::ProcessData<2> Chorus::process(audio::ProcessData<1> data)
    {
      // Allocate two audio buffers (left and right channels)
      auto buf = Application::current().audio_manager->buffer_pool().allocate_multi<2>();
      // Fill buffers with processed samples
      for (auto&& [dat, bufL, bufR] : util::zip(data.audio, buf[0], buf[1]))
        chorus(dat, bufL, bufR);
      // Reassign (redirect) processed data to original data
      return data.redirect(buf);
    }

    // SCREEN //

    void ChorusScreen::rotary(ui::RotaryEvent ev)
    {
        auto& props = engine.props;
        switch (ev.rotary) {
            case Rotary::blue: props.delay.step(ev.clicks); break;
            case Rotary::green: props.rate.step(ev.clicks); break;
            case Rotary::yellow: props.feedback.step(ev.clicks); break;
            case Rotary::red: props.depth.step(ev.clicks); break;
        }
    }

    bool ChorusScreen::keypress(ui::Key key)
    {
        return false;
    }

    void ChorusScreen::draw(ui::vg::Canvas& ctx)
    {
        using namespace ui::vg;
        using util::math::vec;

        auto& props = engine.props;

        ctx.font(Fonts::Norm, 35);

        constexpr float x_pad = 30;
        constexpr float y_pad = 50;
        constexpr float space = (height - 2.f * y_pad) / 3.f;

        ctx.beginPath();
        ctx.fillStyle(Colours::Blue);
        ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
        ctx.fillText("Delay", {x_pad, y_pad});

        ctx.beginPath();
        ctx.fillStyle(Colours::Blue);
        ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
        ctx.fillText(fmt::format("{:1.2}", props.delay), {width - x_pad, y_pad});

        ctx.beginPath();
        ctx.fillStyle(Colours::Green);
        ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
        ctx.fillText("Rate", {x_pad, y_pad + space});

        ctx.beginPath();
        ctx.fillStyle(Colours::Green);
        ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
        ctx.fillText(fmt::format("{:1.2}", props.rate), {width - x_pad, y_pad + space});

        ctx.beginPath();
        ctx.fillStyle(Colours::Yellow);
        ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
        ctx.fillText("Feedback", {x_pad, y_pad + 2 * space});

        ctx.beginPath();
        ctx.fillStyle(Colours::Yellow);
        ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
        ctx.fillText(fmt::format("{:1.2}", props.feedback), {width - x_pad, y_pad + 2 * space});

        ctx.beginPath();
        ctx.fillStyle(Colours::Red);
        ctx.textAlign(HorizontalAlign::Left, VerticalAlign::Middle);
        ctx.fillText("Depth", {x_pad, y_pad + 3 * space});

        ctx.beginPath();
        ctx.fillStyle(Colours::Red);
        ctx.textAlign(HorizontalAlign::Right, VerticalAlign::Middle);
        ctx.fillText(fmt::format("{:1.2}", props.depth), {width - x_pad, y_pad + 3 * space});
    }

} // namespace otto::engines
