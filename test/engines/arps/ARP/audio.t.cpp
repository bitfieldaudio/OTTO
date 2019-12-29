#include "engines/arps/ARP/audio.hpp"
#include "testing.t.hpp"

#define REQUIRE_VEC_EQ(Actual, ...) REQUIRE_THAT(util::view::to_vec(Actual), Catch::Equals(std::vector __VA_ARGS__))

namespace otto::engines::arp {

  namespace view = util::view;

  TEST_CASE ("ARP", "[engines]") {
    auto run_twice = [](auto&& func) {
      for (auto i : view::ints(0, 2)) {
        INFO("Wraps: " << i);
        func();
      }
    };

    SECTION ("Octave/playmodes") {
      auto vec_transform_int = [](auto&& vec) {
        return view::to_vec(view::transform(FWD(vec), [](auto&& x) { return static_cast<int>(FWD(x)); }));
      };

      auto note_arr = [](auto... args) {
        NoteArray res;
        util::indexed_for_each(std::tuple(args...), [&](auto i, auto note) {
          res.push_back({static_cast<std::uint8_t>(note), static_cast<std::int8_t>(i)});
        });
        return res;
      };

      auto test_arp = [&](OctaveModeFunc om, PlayModeFunc pm, NoteArray input, std::vector<std::vector<int>> output, ArpeggiatorState state = {}) {
        for (auto i : view::ints(0, 2)) {
          INFO("cycle: " << i);
          std::vector<std::vector<int>> res;
          for (auto&& [i, output] : view::indexed(output)) {
            res.push_back(vec_transform_int(om(state, input, pm)));
          }
          REQUIRE_THAT(res, Catch::Equals(output));
        }
      };

      SECTION ("standard/manual") {
        test_arp(octave_modes::standard, play_modes::manual, note_arr(1, 2, 4, 3), {{1}, {2}, {4}, {3}});
      }
      SECTION ("standard/up") {
        test_arp(octave_modes::standard, play_modes::up, note_arr(1, 2, 3), {{1}, {2}, {3}});
      }
      SECTION ("standard/down") {
        test_arp(octave_modes::standard, play_modes::down, note_arr(1, 2, 3), {{3}, {2}, {1}});
      }
      SECTION ("standard/updown") {
        test_arp(octave_modes::standard, play_modes::updown, note_arr(0, 5, 12), {{0}, {5}, {12}, {5}});
      }
      SECTION ("standard/downup") {
        test_arp(octave_modes::standard, play_modes::downup, note_arr(0, 5, 12), {{12}, {5}, {0}, {5}});
      }
      SECTION ("standard/updowninc") {
        test_arp(octave_modes::standard, play_modes::updowninc, note_arr(0, 5, 12), {{0}, {5}, {12}, {12}, {5}, {0}});
      }
      SECTION ("standard/downupinc") {
        test_arp(octave_modes::standard, play_modes::downupinc, note_arr(0, 5, 12), {{12}, {5}, {0}, {0}, {5}, {12}});
      }
      SECTION ("upunison/up") {
        test_arp(octave_modes::octaveupunison, play_modes::up, note_arr(1, 2, 3),
                 {{1, 1 + 12}, {2, 2 + 12}, {3, 3 + 12}});
      }
      SECTION ("octaveup/manual") {
        test_arp(octave_modes::octaveup, play_modes::manual, note_arr(0, 12), {{0}, {12}, {12}, {24}});
      }
      SECTION ("octaveup/up") {
        test_arp(octave_modes::octaveup, play_modes::up, note_arr(0), {{0}, {12}});
        test_arp(octave_modes::octaveup, play_modes::up, note_arr(0, 1), {{0}, {1}, {12}, {13}});
        test_arp(octave_modes::octaveup, play_modes::up, note_arr(0, 12), {{0}, {12}, {12}, {24}});
      }
      SECTION ("octaveup/down") {
        test_arp(octave_modes::octaveup, play_modes::down, note_arr(0, 5, 12), {{24}, {17}, {12}, {12}, {5}, {0}});
      }

      SECTION ("octaveup/updown") {
        test_arp(octave_modes::octaveup, play_modes::updown, note_arr(0, 5, 12),
                 {{0}, {5}, {12}, {12}, {17}, {24}, {17}, {12}, {12}, {5}});
      }

      SECTION ("fifthunison/chord") {
        test_arp(octave_modes::fifthunison, play_modes::chord, note_arr(0, 7, 12), {{0, 7, 12, 14, 19}});
      }

      SECTION ("octavedownup/up") {
        test_arp(octave_modes::octavedownup, play_modes::up, note_arr(12, 13, 14), {{0}, {1}, {2}, {24}, {25}, {26}});
      }

      SECTION ("octavedownup/down") {
        test_arp(octave_modes::octavedownup, play_modes::down, note_arr(12, 13, 14), {{26}, {25}, {24}, {2}, {1}, {0}});
      }
    }
  }
} // namespace otto::engines::arp
