#pragma once
#include "processor.hpp"

namespace otto::core::audio {

  inline void validate_audio(AudioBufferHandle& audio)
  {
#ifndef NDEBUG
    for (auto& frm : audio) {
      if (std::isnan(frm)) {
        LOGE("ProcessData was constructed with a frame containing NAN");
      } else if (frm == INFINITY) {
        LOGE("ProcessData was constructed with a frame containing INFINITY");
      } else if (frm == -INFINITY) {
        LOGE("ProcessData was constructed with a frame containing -INFINITY");
      } else {
        break;
      }
      // Set breakpoint here to catch error where it happens
      frm = 0;
      LOGE("The frame was set to zero here, but will crash the audio service in release builds!");
    }
#endif
  }

  template<int N>
  ProcessData<N>::ProcessData(std::array<AudioBufferHandle, channels> audio,
                              midi::shared_vector<midi::AnyMidiEvent> midi,
                              clock::ClockRange clock) noexcept
    : audio(audio), midi(midi), clock(clock), nframes(audio[0].size())
  {
    util::for_each(audio, validate_audio);
  }

  template<int N>
  ProcessData<0> ProcessData<N>::midi_only()
  {
    return {midi, clock, nframes};
  }

  template<int N>
  ProcessData<N> ProcessData<N>::audio_only()
  {
    return {audio, {}, clock, nframes};
  }

  template<int N>
  template<std::size_t NN>
  ProcessData<NN> ProcessData<N>::with(const std::array<AudioBufferHandle, NN>& buf)
  {
    return ProcessData<NN>{buf, midi, clock};
  }

  template<int N>
  ProcessData<1> ProcessData<N>::with(const AudioBufferHandle& buf)
  {
    return ProcessData<1>{buf, midi, clock};
  }

  /// Get only a slice of the audio.
  ///
  /// \param idx The index to start from
  /// \param length The number of frames to keep in the slice
  ///   If `length` is negative, `nframes - idx` will be used
  /// \requires parameter `idx` shall be in the range `[0, nframes)`, and
  /// `length` shall be in range `[0, nframes - idx]`
  template<int N>
  ProcessData<N> ProcessData<N>::slice(int idx, int length)
  {
    auto res = *this;
    length = length < 0 ? nframes - idx : length;
    res.nframes = length;
    res.audio = audio.slice(idx, length);
    return res;
  }

  template<int N>
  auto ProcessData<N>::raw_audio_buffers() -> std::array<float*, channels>
  {
    return {util::generate_array<channels>([&](int n) { return audio[n].data(); })};
  }

  // ProcessData<0> //

  inline ProcessData<0>::ProcessData(midi::shared_vector<midi::AnyMidiEvent> midi,
                                     clock::ClockRange clock,
                                     long nframes) noexcept
    : midi(midi), clock(clock), nframes(nframes)
  {}

  template<std::size_t NN>
  ProcessData<NN> ProcessData<0>::with(const std::array<AudioBufferHandle, NN>& buf)
  {
    return ProcessData<NN>{buf, midi, clock, nframes};
  }

  inline ProcessData<1> ProcessData<0>::with(const AudioBufferHandle& buf)
  {
    return ProcessData<1>{buf, midi, clock};
  }

  inline std::array<float*, 0> ProcessData<0>::raw_audio_buffers()
  {
    return {};
  }

  // ProcessDaata<1> //

  inline ProcessData<1>::ProcessData(AudioBufferHandle audio,
                                     midi::shared_vector<midi::AnyMidiEvent> midi,
                                     clock::ClockRange clock) noexcept
    : audio(audio), midi(midi), clock(clock), nframes(audio.size())
  {
    validate_audio(audio);
  }

  inline ProcessData<0> ProcessData<1>::midi_only()
  {
    return {midi, clock, nframes};
  }

  inline ProcessData<1> ProcessData<1>::audio_only()
  {
    return {audio, {}, clock};
  }

  template<std::size_t NN>
  inline ProcessData<NN> ProcessData<1>::with(const std::array<AudioBufferHandle, NN>& buf)
  {
    return ProcessData<NN>{buf, midi, clock};
  }

  inline ProcessData<1> ProcessData<1>::with(const AudioBufferHandle& buf)
  {
    return ProcessData<1>{buf, midi, clock};
  }

  /// Get only a slice of the audio.
  ///
  /// \param idx The index to start from
  /// \param length The number of frames to keep in the slice
  ///   If `length` is negative, `nframes - idx` will be used
  /// \requires parameter `idx` shall be in the range `[0, nframes)`, and
  /// `length` shall be in range `[0, nframes - idx]`
  inline ProcessData<1> ProcessData<1>::slice(int idx, int length)
  {
    auto res = *this;
    length = length < 0 ? nframes - idx : length;
    res.nframes = length;
    res.audio = audio.slice(idx, length);
    return res;
  }

  inline std::array<float*, 1> ProcessData<1>::raw_audio_buffers()
  {
    return {audio.data()};
  }

} // namespace otto::core::audio
