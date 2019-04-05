#pragma once

#include <array>
#include <cmath>
#include <gsl/gsl>

#include "util/variant.hpp"
#include "util/algorithm.hpp"
#include "util/exception.hpp"

#include "services/log_manager.hpp"
#include "util/utility.hpp"

namespace otto::core::midi {

  namespace detail {

    inline double freq_table[128];

    constexpr std::array<const char*, 128> note_names = {
      {"C-2", "C#-2", "D-2", "D#-2", "E-2", "F-2", "F#-2", "G-2", "G#-2", "A-2", "A#-2", "B-2",
       "C-1", "C#-1", "D-1", "D#-1", "E-1", "F-1", "F#-1", "G-1", "G#-1", "A-1", "A#-1", "B-1",
       "C0",  "C#0",  "D0",  "D#0",  "E0",  "F0",  "F#0",  "G0",  "G#0",  "A0",  "A#0",  "B0",
       "C1",  "C#1",  "D1",  "D#1",  "E1",  "F1",  "F#1",  "G1",  "G#1",  "A1",  "A#1",  "B1",
       "C2",  "C#2",  "D2",  "D#2",  "E2",  "F2",  "F#2",  "G2",  "G#2",  "A2",  "A#2",  "B2",
       "C3",  "C#3",  "D3",  "D#3",  "E3",  "F3",  "F#3",  "G3",  "G#3",  "A3",  "A#3",  "B3",
       "C4",  "C#4",  "D4",  "D#4",  "E4",  "F4",  "F#4",  "G4",  "G#4",  "A4",  "A#4",  "B4",
       "C5",  "C#5",  "D5",  "D#5",  "E5",  "F5",  "F#5",  "G5",  "G#5",  "A5",  "A#5",  "B5",
       "C6",  "C#6",  "D6",  "D#6",  "E6",  "F6",  "F#6",  "G6",  "G#6",  "A6",  "A#6",  "B6",
       "C7",  "C#7",  "D7",  "D#7",  "E7",  "F7",  "F#7",  "G7",  "G#7",  "A7",  "A#7",  "B7",
       "C8",  "C#8",  "D8",  "D#8",  "E8",  "F8",  "F#8",  "G8"}};

  } // namespace detail

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


  struct MidiEvent {
    static constexpr std::size_t max_data_size = 2;
    using byte = unsigned char;

    enum class Type {
      NoteOff = 0b1000,
      NoteOn = 0b1001,
      ControlChange = 0b1011,
    };

    std::array<byte, 1> to_bytes()
    {
      return {byte((byte(type) << 4) | channel)};
    }

    static MidiEvent from_bytes(gsl::span<byte> bytes, int time = 0)
    {
      return {Type{bytes[0] >> 4}, bytes[0] & 0b1111, time};
    }

    Type type;

    int channel;
    int time;
  };

  struct NoteEvent : MidiEvent {
    byte key = 0;
    byte velocity = 0;

    constexpr NoteEvent(const MidiEvent& event) noexcept : MidiEvent(event) {}

    /// Construct a NoteEvent from a type, note as string, and optional velocity
    /// and channels
    ///
    /// \throws `util::exception` if `note` is not in `detail::note_names`
    constexpr NoteEvent(MidiEvent::Type type,
                        std::string_view note,
                        float velocity = 1,
                        byte channel = 0)
      : NoteEvent(type, note_number(note), velocity, channel)
    {}

    /// Construct a NoteEvent from a type, note as string, and optional velocity
    /// and channels
    ///
    /// \throws `util::exception` if `note` is not in `detail::note_names`
    constexpr NoteEvent(MidiEvent::Type type,
                        int note,
                        float velocity = 1,
                        byte channel = 0,
                        int time = 0)
      : MidiEvent{type, channel, time},
        key{gsl::narrow_cast<byte>(note)},
        velocity{gsl::narrow_cast<byte>(std::min(127.f, velocity * 127))}
    {}

    std::array<byte, 3> to_bytes()
    {
      return {byte((byte(type) << 4) | channel), key, velocity};
    }

    static NoteEvent from_bytes(gsl::span<byte> bytes, int time = 0)
    {
      return {Type{bytes[0] >> 4}, bytes[1], bytes[2] / 127.f, byte(bytes[0] & 0b1111), time};
    }
  };

  struct NoteOnEvent : NoteEvent {
    NoteOnEvent(const MidiEvent& event) : NoteEvent(event){};

    constexpr NoteOnEvent(int note, float velocity = 1.f, byte channel = 0, int time = 0)
      : NoteEvent{MidiEvent::Type::NoteOn, note, velocity, channel, time}
    {}

    static NoteOnEvent from_bytes(gsl::span<byte> bytes, int time = 0)
    {
      return {bytes[1], bytes[2] / 127.f, byte(bytes[0] & 0b1111), time};
    }
  };

  struct NoteOffEvent : NoteEvent {
    NoteOffEvent(const MidiEvent& event) : NoteEvent(event){};

    constexpr NoteOffEvent(int note, float velocity = 1, byte channel = 0, int time = 0)
      : NoteEvent{MidiEvent::Type::NoteOff, note, velocity, channel, time}
    {}

    static NoteOffEvent from_bytes(gsl::span<byte> bytes, int time = 0)
    {
      return {bytes[1], bytes[2] / 127.f, byte(bytes[0] & 0b1111), time};
    }
  };

  struct ControlChangeEvent : public MidiEvent {
    int controler = 0;
    int value = 0;

    ControlChangeEvent(const MidiEvent& event) : MidiEvent(event){};

    std::array<byte, 3> to_bytes()
    {
      return {byte((byte(type) << 4) | channel), byte(controler), byte(value)};
    }

    static ControlChangeEvent from_bytes(gsl::span<byte> bytes, int time = 0)
    {
      auto res = ControlChangeEvent(MidiEvent::from_bytes(bytes, time));
      res.controler = bytes[1];
      res.value = bytes[2];
      return res;
    }
  };

  using AnyMidiEvent = util::variant<MidiEvent, NoteOnEvent, NoteOffEvent, ControlChangeEvent>;

  inline AnyMidiEvent from_bytes(gsl::span<unsigned char> bytes, int time = 0)
  {
    if (bytes.size() < 3) throw util::exception("Midi event size must be >= 3 bytes");
    auto type = MidiEvent::Type(bytes[0] >> 4);
    auto velocity = bytes[2];
    switch (type) {
    case MidiEvent::Type::NoteOff: return NoteOffEvent::from_bytes(bytes, time);
    case MidiEvent::Type::NoteOn: {
      /// Per the MIDI specification, NoteOff events are also sent as NoteOn with velocity 0.
      if (velocity != 0)
        return NoteOnEvent::from_bytes(bytes, time);
      else
        return NoteOffEvent::from_bytes(bytes, time);
    }
    case MidiEvent::Type::ControlChange: return ControlChangeEvent::from_bytes(bytes, time);
    default: return MidiEvent::from_bytes(bytes, time);
    }
  }

  inline void generateFreqTable(double tuning = 440)
  {
    for (int i = 0; i < 128; i++) {
      detail::freq_table[i] = tuning * std::pow(2.0, double(i - 69) / double(12));
    }
  }

  constexpr const char* note_name(int key) noexcept
  {
    return detail::note_names[key];
  }

  inline float note_freq(int key) noexcept
  {
    return detail::freq_table[key];
  }

  template<typename T, typename Allocator = std::allocator<T>>
  struct shared_vector {
    using value_type = T;
    using vector_type = std::vector<T, Allocator>;
    using allocator_type = Allocator;
    using iterator = typename vector_type::iterator;

    shared_vector() = default;

    shared_vector(vector_type&& other) : _data(std::make_shared<vector_type>(std::move(other))) {}

    shared_vector(const vector_type& other) : _data(std::make_shared<vector_type>(other)) {}

    shared_vector(const allocator_type& alloc) : _data(std::make_shared<vector_type>(alloc)) {}

    auto begin()
    {
      return _data->begin();
    }
    auto end()
    {
      return _data->end();
    }
    auto begin() const
    {
      return _data->begin();
    }
    auto end() const
    {
      return _data->end();
    }
    auto cbegin() const
    {
      return _data->cbegin();
    }
    auto cend() const
    {
      return _data->cend();
    }

    auto&& front()
    {
      return _data->front();
    }
    auto&& back()
    {
      return _data->back();
    }
    auto&& front() const
    {
      return _data->front();
    }
    auto&& back() const
    {
      return _data->back();
    }

    auto& operator*()
    {
      return *_data;
    }
    auto& operator*() const
    {
      return *_data;
    }

    auto& operator-> ()
    {
      return &*_data;
    }
    auto& operator-> () const
    {
      return &*_data;
    }

    auto& operator[](std::size_t i)
    {
      return (_data)[i];
    }

    auto clear()
    {
      _data->clear();
    }

    auto push_back(const value_type& el)
    {
      _data->push_back(el);
    }

    template<typename... Ref>
    auto&& emplace_back(Ref&&... args)
    {
      return _data->emplace_back(std::forward<Ref>(args)...);
    }

    auto&& move_vector_out()
    {
      return std::move(*_data);
    }

  private:
    std::shared_ptr<vector_type> _data = std::make_shared<vector_type>();
  };


} // namespace otto::core::midi
