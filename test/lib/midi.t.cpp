#include "testing.t.hpp"

#include "lib/midi.hpp"

using namespace otto;
using namespace otto::midi;


auto from_bytes(auto... bytes)
{
  std::vector<std::uint8_t> data = {static_cast<std::uint8_t>(bytes)...};
  return midi::from_bytes(data);
}

template<typename E>
auto wce_from_bytes(auto... bytes)
{
  auto evt = from_bytes(bytes...);
  INFO(evt);
  return std::get<WithChannel<E>>(evt);
}

template<typename E>
MidiEventWithChannel make_wce(std::uint8_t channel, E e)
{
  return WithChannel<E>{e, channel};
}

auto approx = [](float f) { return test::approx(f).margin(0.01); };

TEST_CASE ("midi::from_bytes") {
  SUBCASE ("NoteOff") {
    auto evt = wce_from_bytes<NoteOff>(0x80, 0x12, 0x7F);
    REQUIRE(evt.channel == 0);
    REQUIRE(evt.note == 0x12);
    REQUIRE(evt.velocity == approx(1.0));
  }

  SUBCASE ("NoteOn") {
    auto evt = wce_from_bytes<NoteOn>(0x91, 0x23, 0x40);
    REQUIRE(evt.channel == 1);
    REQUIRE(evt.note == 0x23);
    REQUIRE(evt.velocity == approx(0.5));
  }

  SUBCASE ("Aftertouch") {
    auto evt = wce_from_bytes<Aftertouch>(0xD2, 0x40);
    REQUIRE(evt.channel == 2);
    REQUIRE(evt.aftertouch == approx(0.5));
    evt = wce_from_bytes<Aftertouch>(0xDf, 0x00);
    REQUIRE(evt.channel == 15);
    REQUIRE(evt.aftertouch == approx(0.0));
  }

  SUBCASE ("PolyAftertouch") {
    auto evt = wce_from_bytes<PolyAftertouch>(0xA2, 0x7f, 0x40);
    REQUIRE(evt.channel == 2);
    REQUIRE(evt.note == 127);
    REQUIRE(evt.aftertouch == approx(0.5));
  }

  SUBCASE ("PitchBend") {
    auto evt = wce_from_bytes<PitchBend>(0xEF, 0x00, 0x00);
    REQUIRE(evt.channel == 15);
    REQUIRE(evt.pitch_bend == approx(0.0));
    REQUIRE(wce_from_bytes<PitchBend>(0xEF, 0x40, 0x00).pitch_bend == approx(64.f / 16384.f));
    REQUIRE(wce_from_bytes<PitchBend>(0xEF, 0x7f, 0x00).pitch_bend == approx(127.f / 16384.f));
    REQUIRE(wce_from_bytes<PitchBend>(0xEF, 0x00, 0x40).pitch_bend == approx(0.5));
    REQUIRE(wce_from_bytes<PitchBend>(0xEF, 0x7F, 0x7F).pitch_bend == approx(1.f));
  }
}
