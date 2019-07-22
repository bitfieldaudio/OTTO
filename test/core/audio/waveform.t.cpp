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

    ch::Output<int> start;
    ch::Output<int> length = file_len;

    ch::Timeline timeline;
    timeline.apply(&start).rampTo(file_len - 1, 600).finishFn([&m = *start.inputPtr()] { m.setPlaybackSpeed(m.getPlaybackSpeed() * -1); m.resetTime(); });
    timeline.apply(&length).rampTo(0, 400).finishFn([&m = *length.inputPtr()] { m.setPlaybackSpeed(m.getPlaybackSpeed() * -1); m.resetTime(); });

    std::vector<Point> points;
    test::show_gui([&](Canvas& ctx) {
      timeline.step(1);
      points.clear();

      float x = 10;
      wf.for_points(300, start, std::min(start + length, file_len), [&](float y) {
        points.emplace_back(x, 200 - y * 50);
        x += 1;
      });

      ctx.beginPath();
      ctx.plotLines(points.begin(), points.end());
      ctx.stroke(Colors::White);
    });
  }

} // namespace otto::test
