#pragma once
#include "processor.hpp"

namespace otto::core::audio {

  template<int N>
  ProcessData<N>::ProcessData(std::array<AudioBufferHandle, channels> audio,
                              midi::shared_vector<midi::AnyMidiEvent> midi,
                              long nframes) noexcept
    : audio(audio), midi(midi), nframes(nframes)
  {}

  template<int N>
  ProcessData<N>::ProcessData(std::array<AudioBufferHandle, channels> audio,
                              midi::shared_vector<midi::AnyMidiEvent> midi) noexcept
    : audio(audio), midi(midi), nframes(audio[0].size())
  {}

  template<int N>
  ProcessData<N>::ProcessData(std::array<AudioBufferHandle, channels> audio) noexcept
    : audio(audio), midi(), nframes(audio[0].size())
  {}

  template<int N>
  ProcessData<0> ProcessData<N>::midi_only()
  {
    return {midi, nframes};
  }

  template<int N>
  ProcessData<N> ProcessData<N>::audio_only()
  {
    return {audio, {}, nframes};
  }

  template<int N>
  template<std::size_t NN>
  ProcessData<NN> ProcessData<N>::redirect(const std::array<AudioBufferHandle, NN>& buf)
  {
    return ProcessData<NN>{buf, midi, nframes};
  }

  template<int N>
  ProcessData<1> ProcessData<N>::redirect(const AudioBufferHandle& buf)
  {
    return ProcessData<1>{buf, midi, nframes};
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
                                     long nframes) noexcept
    : midi(midi), nframes(nframes)
  {}

  template<std::size_t NN>
  ProcessData<NN> ProcessData<0>::redirect(const std::array<AudioBufferHandle, NN>& buf)
  {
    return ProcessData<NN>{buf, midi, nframes};
  }

  inline ProcessData<1> ProcessData<0>::redirect(const AudioBufferHandle& buf)
  {
    return ProcessData<1>{buf, midi, nframes};
  }

  inline std::array<float*, 0> ProcessData<0>::raw_audio_buffers()
  {
    return {};
  }

  // ProcessDaata<1> //

  inline ProcessData<1>::ProcessData(AudioBufferHandle audio,
                                     midi::shared_vector<midi::AnyMidiEvent> midi,
                                     long nframes) noexcept
    : audio(audio), midi(midi), nframes(nframes)
  {}

  inline ProcessData<1>::ProcessData(AudioBufferHandle audio,
                                     midi::shared_vector<midi::AnyMidiEvent> midi) noexcept
    : audio(audio), midi(midi), nframes(audio.size())
  {}

  inline ProcessData<1>::ProcessData(AudioBufferHandle audio) noexcept
    : audio(audio), midi(), nframes(audio.size())
  {}

  inline ProcessData<1>::ProcessData(std::array<AudioBufferHandle, channels> audio,
                                     midi::shared_vector<midi::AnyMidiEvent> midi,
                                     long nframes) noexcept
    : audio(audio[0]), midi(midi), nframes(nframes)
  {}

  inline ProcessData<1>::ProcessData(std::array<AudioBufferHandle, channels> audio,
                                     midi::shared_vector<midi::AnyMidiEvent> midi) noexcept
    : audio(audio[0]), midi(midi), nframes(audio[0].size())
  {}

  inline ProcessData<1>::ProcessData(std::array<AudioBufferHandle, channels> audio) noexcept
    : audio(audio[0]), midi(), nframes(audio[0].size())
  {}


  inline ProcessData<0> ProcessData<1>::midi_only()
  {
    return {midi, nframes};
  }

  inline ProcessData<1> ProcessData<1>::audio_only()
  {
    return {audio, {}, nframes};
  }

  template<std::size_t NN>
  inline ProcessData<NN> ProcessData<1>::redirect(const std::array<AudioBufferHandle, NN>& buf)
  {
    return ProcessData<NN>{buf, midi, nframes};
  }

  inline ProcessData<1> ProcessData<1>::redirect(const AudioBufferHandle& buf)
  {
    return ProcessData<1>{buf, midi, nframes};
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

// kak: other_file=processor.hpp
