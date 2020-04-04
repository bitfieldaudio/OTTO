#include <AudioFile.h>
#include <choreograph/Choreograph.h>

#include "core/audio/waveform.hpp"
#include "testing.t.hpp"
#include "graphics.t.hpp"

namespace otto::test {

  using namespace core::audio;

  TEST_CASE ("[graphics] Waveform" * doctest::skip()) {
    AudioFile<float> file;
    file.load("data/samples/test.wav");

    Waveform wf = {{file.samples[0].data(), static_cast<std::size_t>(file.getNumSamplesPerChannel())}, 300};

    using namespace core::ui::vg;

    auto file_len = file.getNumSamplesPerChannel();
    REQUIRE(file_len > 1);

    ch::Output<int> start = 0;
    ch::Output<int> length = file_len - 1;

    ch::Time duration = 1000;

    ch::Timeline timeline;
    // timeline.apply(&start).rampTo(length, duration, ch::EaseOutQuad())
    //  .then<ch::RampTo>(0, duration)
    // .then<ch::Hold>(0, 2 * duration);
    timeline.apply(&length)
      .holdUntil(2 * duration)
      .then<ch::RampTo>(0, duration, ch::EaseOutExpo())
      .then<ch::RampTo>(file_len - 1, duration)
      .then<ch::Hold>(duration, duration);
    // timeline.apply(&start).rampTo(file_len - 1, duration).finishFn([& m = *start.inputPtr()] {
    //  m.setPlaybackSpeed(m.getPlaybackSpeed() * -1);
    //  m.resetTime();
    //});
    // timeline.apply(&length).rampTo(0, duration).finishFn([& m = *length.inputPtr()] {
    //  m.setPlaybackSpeed(m.getPlaybackSpeed() * -1);
    //  m.resetTime();
    //});

    auto view = wf.view(300, start, start + length);
    test::show_gui([&](Canvas& ctx) {
      timeline.step(1);
      wf.view(view, start, start + length);

      float y_bot = height - 70;
      float x_start = 10;
      float x = x_start;
      float y_scale = 40;
      auto iter = view.begin();
      ctx.group([&] {
        ctx.beginPath();
        ctx.moveTo(x, y_bot - *iter * y_scale);
        for (; iter < view.end(); iter++) {
          ctx.lineTo(x, y_bot - *iter * y_scale);
          x += 1;
        }
        ctx.lineTo(x, y_bot);
        ctx.lineTo(x_start, y_bot);
        ctx.fill(DefaultColors::White);
      });
    });
  }

} // namespace otto::test
