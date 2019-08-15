#include "testing.t.hpp"

#include <choreograph/Choreograph.h>

#include "core/audio/waveform.hpp"

#include <AudioFile.h>

namespace otto::test {

  using namespace core::audio;

  TEST_CASE ("Waveform", "[.][graphics][waveform]") {
    AudioFile<float> file;
    file.load("data/samples/test.wav");

    Waveform wf = {{file.samples[0].data(), file.getNumSamplesPerChannel()}, 300};

    using namespace core::ui::vg;

    auto file_len = file.getNumSamplesPerChannel();
    REQUIRE(file_len > 1);

    ch::Output<int> start = 0;
    ch::Output<int> length = file_len - 1;

    ch::Time duration = 4000;

    ch::Timeline timeline;
    timeline.apply(&start).rampTo(length, duration, ch::EaseOutQuad())
      .then<ch::RampTo>(0, duration)
      .then<ch::Hold>(0, 2 * duration);
    timeline.apply(&length).holdUntil(2 * duration)
      .then<ch::RampTo>(0, duration, ch::EaseOutExpo())
      .then<ch::RampTo>(file_len - 1, duration).then<ch::Hold>(4000, duration);
    //timeline.apply(&start).rampTo(file_len - 1, duration).finishFn([& m = *start.inputPtr()] {
    //  m.setPlaybackSpeed(m.getPlaybackSpeed() * -1);
    //  m.resetTime();
    //});
    //timeline.apply(&length).rampTo(0, duration).finishFn([& m = *length.inputPtr()] {
    //  m.setPlaybackSpeed(m.getPlaybackSpeed() * -1);
    //  m.resetTime();
    //});

    auto view = wf.view(300, start, start + length);
    test::show_gui([&](Canvas& ctx) {
      timeline.step(1);
      wf.view(view, std::max(0.f, start - 0.2f * std::min(length(), file_len - start)),
              std::min(start + length * 1.2f, float(file_len - 1)));

      float x = 10;
      ctx.beginPath();
      auto iter = view.begin();
      ctx.moveTo(x, 200 - *iter * 50);
      auto b = view.iter_for_time(start);
      for (; iter < b; iter++) {
        ctx.lineTo(x, 200 - *iter * 50);
        x += 1;
      }
      ctx.stroke(Colors::Gray);

      ctx.beginPath();
      ctx.moveTo(x, 200 - *iter * 50);
      for (auto e = view.iter_for_time(std::min(start + length, file_len)); iter < e; iter++) {
        ctx.lineTo(x, 200 - *iter * 50);
        x += 1;
      }
      ctx.stroke(Colors::White);

      ctx.beginPath();
      ctx.moveTo(x, 200 - *iter * 50);
      for (; iter < view.end(); iter++) {
        ctx.lineTo(x, 200 - *iter * 50);
        x += 1;
      }
      ctx.stroke(Colors::Gray);
    });
  }

} // namespace otto::test
