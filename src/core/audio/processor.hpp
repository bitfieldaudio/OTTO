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
/// audio system and it's deligates.
///
/// If another thread needs access to any of this data, e.g. the audio/midi
/// data, They need an audio processor to read it and store it. It is up to the
/// engine in question to handle thread safety.

#pragma once

#include <exception>
#include <functional>
#include <gsl/span>

#include "core/audio/midi.hpp"

#include "util/audio.hpp"

namespace otto::core::audio {

  /**
   * Checks if a type qualifies as an <AudioProcessor>
   */
  template<typename...>
  struct is_audio_processor {
  }; // TODO: Implementation

  template<typename T>
  struct audio_frame_channels;

  template<std::size_t N>
  struct audio_frame_channels<std::array<float, N>> {
    static constexpr auto value = N;
  };


  namespace detail {
    // No including "core/globals.hpp" in headers
    void registerAudioBufferResize(std::function<void(int)>);
  } // namespace detail

  /**
   * A DynArray that resizes to fit the RealTime bufferSize.
   *
   * This is the container used in AudioProcessors, and it should be used
   * in any place where the realtime data is copied out. It is resized on
   * the bufferSizeChanged event
   */
  template<typename T, std::size_t factor = 1>
  class RTBuffer : public util::dyn_array<T> {
  public:
    RTBuffer(std::size_t initial_size = 0)
      : util::dyn_array<T>(initial_size * factor)
    {
      detail::registerAudioBufferResize(
        [this](std::size_t newSize) { resize(newSize); });
    }

    void resize(std::size_t new_size)
    {
      util::dyn_array<T>::resize(new_size * factor);
    }
  };

  /**
   * A DynArray that resizes to fit the RealTime bufferSize.
   *
   * This is the container used in AudioProcessors, and it should be used
   * in any place where the realtime data is copied out. It is resized on
   * the bufferSizeChanged event
   */
  template<int N>
  using ProcessBuffer = RTBuffer<std::array<float, N>, 1>;

  /// Non-owning package of data passed to audio processors
  template<int N>
  struct ProcessData {
    static constexpr int channels = N;

    gsl::span<std::array<float, channels>> audio;
    std::vector<midi::AnyMidiEvent> midi;

    long nframes;
    long offset = 0;

    template<int outN = 0>
    ProcessData<outN> midi_only()
    {
      return {{nullptr, nullptr}, midi, nframes};
    }

    ProcessData audio_only()
    {
      return {audio, {nullptr, nullptr}, nframes};
    }

    template<typename T>
    auto redirect(T& buf)
    {
      return ProcessData<
        audio_frame_channels<std::decay_t<decltype(buf[0])>>::value>{
        {buf.data(), nframes}, midi, nframes};
    }

    /// Get only a slice of the audio.
    ///
    /// \param idx The index to start from
    /// \param length The number of frames to keep in the slice
    ///   If `length` is negative, `nframes - idx` will be used
    /// \requires parameter `idx` shall be in the range `[0, nframes)`, and
    /// `length` shall be in range `[0, nframes - idx]`
    ProcessData slice(int idx, int length = -1)
    {
      auto res    = *this;
      length      = length < 0 ? nframes - idx : length;
      res.nframes = length;
      res.offset += idx;
      if constexpr (channels != 0) {
        res.audio = {audio.data() + idx, std::size_t(length)};
      }
      return res;
    }

    decltype(auto) begin()
    {
      return audio.begin();
    }
    decltype(auto) end()
    {
      return audio.end();
    }
    decltype(auto) begin() const
    {
      return audio.begin();
    }
    decltype(auto) end() const
    {
      return audio.end();
    }
  };

} // namespace otto::core::audio
