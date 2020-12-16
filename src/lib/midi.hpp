#pragma once

#include <array>
#include <span>
#include <variant>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include "lib/util/exception.hpp"

#include "lib/itc/reducer.hpp"

namespace otto::midi {

  namespace detail {
    inline float freq_table[128];


    constexpr std::array<const char*, 128> note_names = {{
      "C-2",  "C#-2", "D-2", "D#-2", "E-2", "F-2",  "F#-2", "G-2",  "G#-2", "A-2", "A#-2", "B-2", "C-1", "C#-1", "D-1",
      "D#-1", "E-1",  "F-1", "F#-1", "G-1", "G#-1", "A-1",  "A#-1", "B-1",  "C0",  "C#0",  "D0",  "D#0", "E0",   "F0",
      "F#0",  "G0",   "G#0", "A0",   "A#0", "B0",   "C1",   "C#1",  "D1",   "D#1", "E1",   "F1",  "F#1", "G1",   "G#1",
      "A1",   "A#1",  "B1",  "C2",   "C#2", "D2",   "D#2",  "E2",   "F2",   "F#2", "G2",   "G#2", "A2",  "A#2",  "B2",
      "C3",   "C#3",  "D3",  "D#3",  "E3",  "F3",   "F#3",  "G3",   "G#3",  "A3",  "A#3",  "B3",  "C4",  "C#4",  "D4",
      "D#4",  "E4",   "F4",  "F#4",  "G4",  "G#4",  "A4",   "A#4",  "B4",   "C5",  "C#5",  "D5",  "D#5", "E5",   "F5",
      "F#5",  "G5",   "G#5", "A5",   "A#5", "B5",   "C6",   "C#6",  "D6",   "D#6", "E6",   "F6",  "F#6", "G6",   "G#6",
      "A6",   "A#6",  "B6",  "C7",   "C#7", "D7",   "D#7",  "E7",   "F7",   "F#7", "G7",   "G#7", "A7",  "A#7",  "B7",
      "C8",   "C#8",  "D8",  "D#8",  "E8",  "F8",   "F#8",  "G8",
    }};

  } // namespace detail


  inline void generateFreqTable(double tuning = 440)
  {
    for (int i = 0; i < 128; i++) {
      detail::freq_table[i] = tuning * std::pow(2.0, double(i - 69) / double(12));
    }
  }

  inline float note_freq(int key) noexcept
  {
    [[maybe_unused]] static bool once = (generateFreqTable(), true);
    return detail::freq_table[key];
  }


  /// A type that represents a value in the range [0; 1], stored as an int from
  /// 0 to `divisor`
  template<std::integral Int, Int divisor>
  struct fixed_point_ratio {
    fixed_point_ratio() = default;
    fixed_point_ratio(Int i) noexcept : value(i) {}
    fixed_point_ratio(const fixed_point_ratio&) noexcept = default;
    fixed_point_ratio& operator=(const fixed_point_ratio& f) noexcept = default;

    fixed_point_ratio& operator=(float f) noexcept
    {
      value = std::clamp(f, 0.f, 1.f) * divisor;
    }

    Int integral() const noexcept
    {
      return value;
    }
    float floating() const noexcept
    {
      return std::clamp(value / float(divisor), 0.f, 1.f);
    }

    operator float() const noexcept
    {
      return floating();
    }

    auto operator<=>(const fixed_point_ratio&) const = default;
    bool operator==(const fixed_point_ratio&) const = default;

  private:
    Int value = 0;
  };

  constexpr int note_number(std::string_view sv) noexcept
  {
    // std::find is not constexpr, so i roll my own
    auto iter = detail::note_names.cbegin();
    constexpr auto last = detail::note_names.cend();
    for (int i = 0; iter != last; ++i, ++iter) {
      if (*iter == sv) {
        return i;
      }
    }
    return -1;
  }

  struct NoteOn {
    std::uint8_t note = 0;
    fixed_point_ratio<std::uint8_t, 1 << 7> velocity = 0;
    std::uint8_t channel = 0;

    auto operator<=>(const NoteOn&) const = default;
  };

  struct NoteOff {
    std::uint8_t note = 0;
    fixed_point_ratio<std::uint8_t, 1 << 7> velocity = 0;
    std::uint8_t channel = 0;

    auto operator<=>(const NoteOff&) const = default;
  };

  struct Aftertouch {
    fixed_point_ratio<std::uint8_t, 1 << 7> aftertouch = 0;
    std::uint8_t channel = 0;

    auto operator<=>(const Aftertouch&) const = default;
  };

  struct PolyAftertouch {
    std::uint8_t note = 0;
    fixed_point_ratio<std::uint8_t, 1 << 7> aftertouch = 0;
    std::uint8_t channel = 0;

    auto operator<=>(const PolyAftertouch&) const = default;
  };

  struct PitchBend {
    fixed_point_ratio<std::uint16_t, 1 << 14> pitch_bend = 0;
    std::uint8_t channel = 0;

    auto operator<=>(const PitchBend&) const = default;
  };

  using MidiEvent = std::variant<NoteOn, NoteOff, Aftertouch, PolyAftertouch, PitchBend>;

  using IMidiHandler = IEventHandler<NoteOn, NoteOff, Aftertouch, PolyAftertouch, PitchBend>;

  struct MidiHandler : IMidiHandler {
    void handle(NoteOn) noexcept override {}
    void handle(NoteOff) noexcept override {}
    void handle(Aftertouch) noexcept override {}
    void handle(PolyAftertouch) noexcept override {}
    void handle(PitchBend) noexcept override {}
  };

  inline MidiEvent from_bytes(std::span<std::uint8_t> bytes)
  {
    std::uint8_t status = bytes[0];
    std::uint8_t evt = status & 0xF0;
    std::uint8_t chan = status & 0x0F;
    const auto byte_n = [&](int idx) {
      if (idx >= bytes.size()) {
        throw util::exception("Invalid midi event");
      }
      return bytes[idx];
    };
    if (evt == 0x80) {
      return NoteOff{.note = byte_n(1), .velocity = byte_n(2), .channel = chan};
    }
    if (evt == 0x90) {
      return NoteOn{.note = byte_n(1), .velocity = byte_n(2), .channel = chan};
    }
    if (evt == 0xA0) {
      return PolyAftertouch{.note = byte_n(1), .aftertouch = byte_n(2), .channel = chan};
    }
    if (evt == 0xD0) {
      return Aftertouch{.aftertouch = byte_n(1), .channel = chan};
    }
    if (evt == 0xE0) {
      return PitchBend{.pitch_bend = (byte_n(2) << 7) | (byte_n(1)), .channel = chan};
    }
    throw util::exception("Invalid midi event");
  }

  inline std::ostream& operator<<(std::ostream& os, const NoteOn& e)
  {
    return os << fmt::format("{{channel = {}, note = {}, velocity = {}}}", e.channel, e.note, e.velocity);
  }

  inline std::ostream& operator<<(std::ostream& os, const NoteOff& e)
  {
    return os << fmt::format("{{channel = {}, note = {}, velocity = {}}}", e.channel, e.note, e.velocity);
  }

  inline std::ostream& operator<<(std::ostream& os, const Aftertouch& e)
  {
    return os << fmt::format("{{channel = {}, aftertouch = {}}}", e.channel, e.aftertouch);
  }

  inline std::ostream& operator<<(std::ostream& os, const PolyAftertouch& e)
  {
    return os << fmt::format("{{channel = {}, note = {}, aftertouch = {}}}", e.channel, e.note, e.aftertouch);
  }

  inline std::ostream& operator<<(std::ostream& os, const PitchBend& e)
  {
    return os << fmt::format("{{channel = {}, bend = {}}}", e.channel, e.pitch_bend);
  }

} // namespace otto::midi
