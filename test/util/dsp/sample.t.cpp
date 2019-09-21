#include "testing.t.hpp"

#include "util/algorithm.hpp"

#include "util/dsp/sample.hpp"

namespace otto::dsp {

  namespace view = util::view;

  ///
  /// TODO
  /// ====
  ///
  /// - Test loop points
  /// - Test playback speed
  /// - All of the above when playing in reverse
  TEST_CASE ("Sample") {
    std::vector<float> data;
    std::generate_n(std::back_inserter(data), 100, [i = 0]() mutable { return i++; });

    Sample sample = Sample{data};

    SECTION ("Upon construction, the Sample plays back the audio directly") {
      REQUIRE(sample.size() == 100);
      int n = 0;
      for (auto&& [i, f] : view::indexed(sample)) {
        REQUIRE(f == i);
        n = i + 1;
      }
      REQUIRE(n == 100);
    }

    SECTION ("Changing the start point to 50 makes it only play back half the sample") {
      sample.start_point(50);
      REQUIRE(sample.size() == 50);
      int n = 0;
      for (auto&& [i, f] : view::indexed(sample)) {
        REQUIRE(f == 50 + i);
        n = i + 1;
      }
      REQUIRE(n == 50);
    }

    SECTION ("Changing the end point to 50 makes it only play back the first half the sample") {
      sample.end_point(50);
      REQUIRE(sample.size() == 50);
      int n = 0;
      for (auto&& [i, f] : view::indexed(sample)) {
        REQUIRE(f == i);
        n = i + 1;
      }
      REQUIRE(n == 50);
    }

    SECTION ("Setting the end point to before the start point moves the start point to be equal to the new end point") {
      sample.start_point(50);
      sample.end_point(40);
      REQUIRE(sample.start_point() == 40);
      REQUIRE(sample.end_point() == 40);
    }

    SECTION ("Setting the start point to after the end point moves the end point to be equal to the new start point") {
      sample.end_point(40);
      sample.start_point(50);
      REQUIRE(sample.start_point() == 50);
      REQUIRE(sample.end_point() == 50);
    }

    SECTION ("Setting the start point to be > audio_data.size() clamps it") {
      sample.end_point(50);
      sample.start_point(101);
      REQUIRE(sample.start_point() == 100);
    }

    SECTION ("Setting the start point to be > audio_data.size() clamps it") {
      sample.start_point(50);
      sample.end_point(101);
      REQUIRE(sample.end_point() == 100);
    }

    SECTION ("Setting the end point to be == the start point results in an empty range") {
      sample.start_point(50);
      sample.end_point(50);
      REQUIRE(sample.size() == 0);
      for (auto&& f : sample) {
        FAIL();
      }
    }

    SECTION ("Fade in time scales the audio data linearly") {
      // Non-default start/end points
      sample.start_point(10);
      sample.end_point(90);
      sample.fade_in_time(10);
      REQUIRE(sample.fade_in_time() == 10);

      auto expected = view::to_vec(view::subrange(data, 10, 90));
      float scale = 0;
      for (auto& f : view::subrange(expected, 0, 10)) {
        f *= scale;
        scale += 0.1;
      }
      REQUIRE(sample.size() == expected.size());
      REQUIRE_THAT(view::to_vec(sample), Catch::Approx(expected).margin(0.05));
    }

    SECTION ("Fade out time scales the audio data linearly towards the end") {
      // Non-default start/end points
      sample.start_point(10);
      sample.end_point(90);
      sample.fade_out_time(10);
      REQUIRE(sample.fade_out_time() == 10);
      auto expected = view::to_vec(view::subrange(data, 10, 90));
      float scale = 1;
      for (auto& f : view::subrange(expected, expected.size() - 10, expected.size())) {
        f *= scale;
        scale -= 0.1;
      }
      REQUIRE(sample.size() == expected.size());
      REQUIRE_THAT(view::to_vec(sample), Catch::Approx(expected).margin(0.05));
    }

    SECTION ("Reverse") {
      sample.playback_speed(-1);

      SECTION ("Sample plays audio in reverse") {
        REQUIRE(sample.size() == 100);
        auto expected = view::to_vec(view::reverse(data));
        REQUIRE_THAT(view::to_vec(sample), Catch::Equals(expected));
      }

      SECTION ("start points work in reverse") {
        sample.start_point(10);
        REQUIRE(sample.size() == 90);
        auto expected = view::to_vec(view::reverse(view::subrange(data, 10, 100)));
        REQUIRE_THAT(view::to_vec(sample), Catch::Equals(expected));
      }

      SECTION ("end points work in reverse") {
        sample.end_point(90);
        REQUIRE(sample.size() == 90);
        auto expected = view::to_vec(view::reverse(view::subrange(data, 0, 90)));
        REQUIRE_THAT(view::to_vec(sample), Catch::Equals(expected));
      }

      SECTION ("start/end points work in reverse") {
        sample.start_point(10);
        sample.end_point(90);

        REQUIRE(sample.size() == 80);

        auto expected = view::to_vec(view::reverse(view::subrange(data, 10, 90)));
        REQUIRE_THAT(view::to_vec(sample), Catch::Equals(expected));
      }

      SECTION ("Fade in works in reverse") {
        // Non-default start/end points
        sample.start_point(10);
        sample.end_point(90);
        sample.fade_in_time(10);
        REQUIRE(sample.fade_in_time() == 10);

        auto expected = view::to_vec(view::subrange(data, 10, 90));
        float scale = 0;
        for (auto& f : view::subrange(expected, 0, 10)) {
          scale += 0.1;
          f *= scale;
        }
        util::reverse(expected);

        REQUIRE(sample.size() == expected.size());
        REQUIRE_THAT(view::to_vec(sample), Catch::Approx(expected).margin(0.05));
      }

      SECTION ("Fade out works in reverse") {
        // Non-default start/end points
        sample.start_point(10);
        sample.end_point(90);
        sample.fade_out_time(10);
        REQUIRE(sample.fade_out_time() == 10);
        auto expected = view::to_vec(view::subrange(data, 10, 90));
        float scale = 1;
        for (auto& f : view::subrange(expected, expected.size() - 10, expected.size())) {
          scale -= 0.1;
          f *= scale;
        }
        util::reverse(expected);

        REQUIRE(sample.size() == expected.size());
        REQUIRE_THAT(view::to_vec(sample), Catch::Approx(expected).margin(0.05));
      }
    }
  }
} // namespace otto::dsp
