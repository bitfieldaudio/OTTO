#include "testing.t.hpp"

#include "lib/alsamixer.hpp"

#include "lib/util/ranges.hpp"

using namespace otto;

TEST_CASE ("alsamixer", "[.interactive]") {
  alsa::Mixer mixer = {"default"};
  auto elems = get_elems(mixer);
  SECTION ("List elements & controls") {
    fmt::print("Alsamixer, per-channel controls\n");
    for (auto& elem : elems) {
      fmt::print("{}\n", elem);
      for (auto& ctrl : get_controls(elem)) {
        fmt::print("  {} {}: {}\n", ctrl->get_name(), alsa::channel_name(ctrl->get_channel()), ctrl->value_str());
      }
    }
    fmt::print("-------------------------------\n");
  }
  SECTION ("List elements & all-channel controls") {
    fmt::print("Alsamixer, all-channel controls\n");
    for (auto& elem : elems) {
      fmt::print("{}\n", elem);
      for (auto& ctrl : get_controls_all_channels(elem)) {
        fmt::print("  {}: {}\n", ctrl->get_name(), ctrl->value_str());
      }
    }
    fmt::print("-------------------------------\n");
  }
}
