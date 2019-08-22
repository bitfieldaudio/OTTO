/// \file
/// Audio Processors are anything that can process audio/midi.
/// They run on the audio thread, and are called by the audio system (Jack).
/// Formally, an audio processor is defined as having a method matching
/// this signature:
///
/// ```cpp
/// void process(const ProcessData&);
/// ```
///
/// This method _must_ not be called from anywhere other than the main
/// audio system and its delegates.
///
/// If another thread needs access to any of this data, e.g. the audio/midi
/// data, they need an audio processor to read it and store it. It is up to the
/// engine in question to handle thread safety.

#pragma once

#include <exception>
#include <functional>
#include <gsl/span>

#include "core/audio/audio_buffer_pool.hpp"
#include "core/audio/clock.hpp"
#include "core/audio/midi.hpp"

#include "util/audio.hpp"

namespace otto::core::audio {

  /// Non-owning package of data passed to audio processors
  template<int N>
  struct ProcessData {
    static constexpr int channels = N;

    std::array<AudioBufferHandle, channels> audio;
    midi::shared_vector<midi::AnyMidiEvent> midi;
    clock::ClockRange clock;
    long nframes;

    ProcessData(std::array<AudioBufferHandle, channels> audio,
                midi::shared_vector<midi::AnyMidiEvent> midi = {},
                clock::ClockRange clock = {}) noexcept;

    ProcessData<0> midi_only();

    ProcessData audio_only();

    template<std::size_t NN>
    ProcessData<NN> with(const std::array<AudioBufferHandle, NN>& buf);

    ProcessData<1> with(const AudioBufferHandle& buf);

    /// Get only a slice of the audio.
    ///
    /// \param idx The index to start from
    /// \param length The number of frames to keep in the slice
    ///   If `length` is negative, `nframes - idx` will be used
    /// \requires parameter `idx` shall be in the range `[0, nframes)`, and
    /// `length` shall be in range `[0, nframes - idx]`
    ProcessData slice(int idx, int length = -1);

    std::array<float*, channels> raw_audio_buffers();
  };

  using TestType = std::vector<struct Tag>;

  /// Non-owning package of data passed to audio processors
  template<>
  struct ProcessData<0> {
    static constexpr int channels = 0;

    midi::shared_vector<midi::AnyMidiEvent> midi;
    clock::ClockRange clock;
    long nframes;

    ProcessData(midi::shared_vector<midi::AnyMidiEvent> midi, clock::ClockRange clock, long nframes) noexcept;
    ProcessData(midi::shared_vector<midi::AnyMidiEvent> midi, long nframes) noexcept : ProcessData(midi, {}, nframes) {}

    template<std::size_t NN>
    ProcessData<NN> with(const std::array<AudioBufferHandle, NN>& buf);
    ProcessData<1> with(const AudioBufferHandle& buf);

    std::array<float*, 0> raw_audio_buffers();
  };

  /// Non-owning package of data passed to audio processors
  template<>
  struct ProcessData<1> {
    static constexpr int channels = 1;

    AudioBufferHandle audio;
    midi::shared_vector<midi::AnyMidiEvent> midi;
    clock::ClockRange clock;
    long nframes;

    ProcessData(AudioBufferHandle audio,
                midi::shared_vector<midi::AnyMidiEvent> midi = {},
                clock::ClockRange clock = {}) noexcept;

    ProcessData(std::array<AudioBufferHandle, channels> audio,
                midi::shared_vector<midi::AnyMidiEvent> midi = {},
                clock::ClockRange clock = {}) noexcept
      : ProcessData(audio[0], midi, clock)
    {}

    ProcessData<0> midi_only();
    ProcessData audio_only();

    template<std::size_t NN>
    ProcessData<NN> with(const std::array<AudioBufferHandle, NN>& buf);
    ProcessData<1> with(const AudioBufferHandle& buf);

    /// Get only a slice of the audio.
    ///
    /// \param idx The index to start from
    /// \param length The number of frames to keep in the slice
    ///   If `length` is negative, `nframes - idx` will be used
    /// \requires parameter `idx` shall be in the range `[0, nframes)`, and
    /// `length` shall be in range `[0, nframes - idx]`
    ProcessData slice(int idx, int length = -1);

    std::array<float*, channels> raw_audio_buffers();
  };


} // namespace otto::core::audio

#include "processor.inl"
