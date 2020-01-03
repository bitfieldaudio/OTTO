#include "engines/arps/ARP/audio.hpp"
#include "testing.t.hpp"

#define REQUIRE_VEC_EQ(Actual, ...) REQUIRE_THAT(util::view::to_vec(Actual), Catch::Equals(std::vector __VA_ARGS__))

namespace otto::engines::arp {

  namespace views = nano::views;

  TEST_CASE ("[engines] ARP") {
    auto run_twice = [](auto&& func) {
      for (auto i : views::iota(0, 2)) {
        INFO("Wraps: " << i);
        func();
      }
    };

    SUBCASE ("Octave/playmodes") {
      auto vec_transform_int = [](const auto& vec) {
        return util::view::to_vec(views::all(vec) | views::transform([](auto&& x) { return static_cast<int>(FWD(x)); }));
      };

      auto note_arr = [](auto... args) {
        NoteArray res;
        util::indexed_for_each(std::tuple(args...), [&](auto i, auto note) {
          res.push_back({static_cast<std::uint8_t>(note), static_cast<std::int8_t>(i)});
        });
        return res;
      };

      auto test_arp = [&](OctaveModeFunc om, PlayModeFunc pm, NoteArray input, std::vector<std::vector<int>> output, ArpeggiatorState state = {}) {
        for (auto i : views::iota(0, 2)) {
          INFO("cycle: " << i);
          std::vector<std::vector<int>> res;
          for (auto&& [i, output] : util::view::indexed(output)) {
            res.push_back(vec_transform_int(om(state, input, pm)));
          }
          REQUIRE(res == output);
        }
      };

      SUBCASE ("standard/manual") {
        test_arp(octave_modes::standard, play_modes::manual, note_arr(1, 2, 4, 3), {{1}, {2}, {4}, {3}});
      }
      SUBCASE ("standard/up") {
        test_arp(octave_modes::standard, play_modes::up, note_arr(1, 2, 3), {{1}, {2}, {3}});
      }
      SUBCASE ("standard/down") {
        test_arp(octave_modes::standard, play_modes::down, note_arr(1, 2, 3), {{3}, {2}, {1}});
      }
      SUBCASE ("standard/updown") {
        test_arp(octave_modes::standard, play_modes::updown, note_arr(0, 5, 12), {{0}, {5}, {12}, {5}});
      }
      SUBCASE ("standard/downup") {
        test_arp(octave_modes::standard, play_modes::downup, note_arr(0, 5, 12), {{12}, {5}, {0}, {5}});
      }
      SUBCASE ("standard/updowninc") {
        test_arp(octave_modes::standard, play_modes::updowninc, note_arr(0, 5, 12), {{0}, {5}, {12}, {12}, {5}, {0}});
      }
      SUBCASE ("standard/downupinc") {
        test_arp(octave_modes::standard, play_modes::downupinc, note_arr(0, 5, 12), {{12}, {5}, {0}, {0}, {5}, {12}});
      }
      SUBCASE ("upunison/up") {
        test_arp(octave_modes::octaveupunison, play_modes::up, note_arr(1, 2, 3),
                 {{1, 1 + 12}, {2, 2 + 12}, {3, 3 + 12}});
      }
      SUBCASE ("octaveup/manual") {
        test_arp(octave_modes::octaveup, play_modes::manual, note_arr(0, 12), {{0}, {12}, {12}, {24}});
      }
      SUBCASE ("octaveup/up") {
        test_arp(octave_modes::octaveup, play_modes::up, note_arr(0), {{0}, {12}});
        test_arp(octave_modes::octaveup, play_modes::up, note_arr(0, 1), {{0}, {1}, {12}, {13}});
        test_arp(octave_modes::octaveup, play_modes::up, note_arr(0, 12), {{0}, {12}, {12}, {24}});
      }
      SUBCASE ("octaveup/down") {
        test_arp(octave_modes::octaveup, play_modes::down, note_arr(0, 5, 12), {{24}, {17}, {12}, {12}, {5}, {0}});
      }

      SUBCASE ("octaveup/updown") {
        test_arp(octave_modes::octaveup, play_modes::updown, note_arr(0, 5, 12),
                 {{0}, {5}, {12}, {12}, {17}, {24}, {17}, {12}, {12}, {5}});
      }

      SUBCASE ("fifthunison/chord") {
        test_arp(octave_modes::fifthunison, play_modes::chord, note_arr(0, 7, 12), {{0, 7, 12, 14, 19}});
      }

      SUBCASE ("octavedownup/up") {
        test_arp(octave_modes::octavedownup, play_modes::up, note_arr(12, 13, 14), {{0}, {1}, {2}, {24}, {25}, {26}});
      }

      SUBCASE ("octavedownup/down") {
        test_arp(octave_modes::octavedownup, play_modes::down, note_arr(12, 13, 14), {{26}, {25}, {24}, {2}, {1}, {0}});
      }
    }
  }
} // namespace otto::engines::arp
