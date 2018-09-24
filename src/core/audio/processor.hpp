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
  struct is_audio_processor {}; // TODO: Implementation

  template<typename T>
  struct audio_frame_channels;

  template<std::size_t N>
  struct audio_frame_channels<std::array<float, N>> {
    static constexpr auto value = N;
  };

  /// A handle to an audio buffer
  struct AudioBufferHandle {
    using iterator = float*;
    using const_iterator = const float*;

    AudioBufferHandle(float* data, std::size_t length, int& reference_count)
      : _data(data), _length(length), _reference_count(&reference_count)
    {
      (*_reference_count)++;
    }

    ~AudioBufferHandle()
    {
      if (_reference_count) (*_reference_count)--;
    };

    AudioBufferHandle(AudioBufferHandle&& rhs)
      : _data(rhs._data), _length(rhs._length), _reference_count(rhs._reference_count)
    {
      rhs._data = nullptr;
      rhs._reference_count = nullptr;
    }

    AudioBufferHandle(const AudioBufferHandle& rhs)
      : _data(rhs._data), _length(rhs._length), _reference_count(rhs._reference_count)
    {
      (*_reference_count)++;
    }

    int reference_count() const
    {
      return *_reference_count;
    }

    float* data() const
    {
      return _data;
    }

    std::size_t size() const
    {
      return _length;
    }

    iterator begin()
    {
      return _data;
    }
    iterator end()
    {
      return _data + _length;
    }
    iterator begin() const
    {
      return _data;
    }
    iterator end() const
    {
      return _data + _length;
    }

    float& operator[](std::size_t i)
    {
      return _data[i];
    }

    const float& operator[](std::size_t i) const
    {
      return _data[i];
    }

    void release()
    {
      (*_reference_count)--;
      _reference_count = nullptr;
      _data = nullptr;
    }

    void clear()
    {
      std::fill(begin(), end(), 0);
    }

    /// Get only a slice of the audio.
    ///
    /// \param idx The index to start from
    /// \param length The number of frames to keep in the slice
    ///   If `length` is negative, `nframes - idx` will be used
    /// \requires parameter `idx` shall be in the range `[0, _length)`, and
    /// `length` shall be in range `[0, nframes - idx]`
    AudioBufferHandle slice(int idx, int length = -1)
    {
      length = length < 0 ? _length - idx : length;
      return {_data + idx, length, *_reference_count};
    }

    float* data()
    {
      return _data;
    }

  private:
    float* _data;
    const std::size_t _length;
    int* _reference_count;
  };

  template<std::size_t Channels>
  struct MultiChannelAudioBufferHandle;

  template<>
  struct MultiChannelAudioBufferHandle<0> {
    void clear() {}

    std::array<float*, 0> data()
    {
      return {};
    }
  };

  template<>
  struct MultiChannelAudioBufferHandle<1> {
    static constexpr std::size_t channel_count = 1;

    using iterator = util::zipped_iterator<AudioBufferHandle::iterator>;
    using const_iterator = util::zipped_iterator<AudioBufferHandle::const_iterator>;

    MultiChannelAudioBufferHandle(const AudioBufferHandle& handle) : _handle(handle) {}

    std::size_t size() const
    {
      return _handle.size();
    }

    iterator begin()
    {
      return {_handle.begin()};
    }
    iterator end()
    {
      return {_handle.end()};
    }
    iterator begin() const
    {
      return {_handle.begin()};
    }
    iterator end() const
    {
      return {_handle.end()};
    }

    std::tuple<float&> operator[](std::size_t i)
    {
      return {_handle[i]};
    }

    std::tuple<const float&> operator[](std::size_t i) const
    {
      return {_handle[i]};
    }

    void release()
    {
      _handle.release();
    }

    void clear()
    {
      _handle.clear();
    }

    std::array<float*, channel_count> data()
    {
      return {_handle.data()};
    }

  private:
    AudioBufferHandle _handle;
  };

  template<>
  struct MultiChannelAudioBufferHandle<2> {
    static constexpr std::size_t channel_count = 2;

    using iterator =
      util::zipped_iterator<AudioBufferHandle::iterator, AudioBufferHandle::iterator>;
    using const_iterator =
      util::zipped_iterator<AudioBufferHandle::const_iterator, AudioBufferHandle::const_iterator>;

    MultiChannelAudioBufferHandle(const AudioBufferHandle& left, const AudioBufferHandle& right)
      : _left_handle(left), _right_handle(right)
    {}

    std::size_t size() const
    {
      return std::min(_left_handle.size(), _right_handle.size());
    }

    iterator begin()
    {
      return {_left_handle.begin(), _right_handle.begin()};
    }
    iterator end()
    {
      return {_left_handle.end(), _right_handle.end()};
    }
    iterator begin() const
    {
      return {_left_handle.begin(), _right_handle.begin()};
    }
    iterator end() const
    {
      return {_left_handle.end(), _right_handle.end()};
    }

    std::pair<float&, float&> operator[](std::size_t i)
    {
      return {_left_handle[i], _right_handle[i]};
    }

    std::pair<const float&, const float&> operator[](std::size_t i) const
    {
      return {_left_handle[i], _right_handle[i]};
    }

    void release()
    {
      _left_handle.release();
      _right_handle.release();
    }

    void clear()
    {
      _left_handle.clear();
      _right_handle.clear();
    }

    std::array<float*, channel_count> data()
    {
      return {_left_handle.data(), _right_handle.data()};
    }

  private:
    AudioBufferHandle _left_handle;
    AudioBufferHandle _right_handle;
  };

  struct AudioBufferPool {
    AudioBufferPool(std::size_t buffer_size) : buffer_size(buffer_size)
    {
      // For now this is hardcoded, which is nice, cause we notice if we suddenly are using too many
      // buffers
      reserve(4);
    }

    AudioBufferHandle allocate()
    {
      for (int i = 0; i < reference_counts.size(); i++) {
        if (reference_counts[i] < 1) {
          if (i > _max_val) {
            LOGI("Using {} buffers", i + 1);
            _max_val = i;
          }
          reference_counts[i] = 0;
          int index = i * buffer_size;
          return {data.get() + index, buffer_size, reference_counts[i]};
        }
      }
      DLOGI("Allocating a new audio buffer. this pool now has {} buffers", _avaliable_buffers);
      reserve(_avaliable_buffers + 1);
      return allocate();
    }

    template<std::size_t N>
    MultiChannelAudioBufferHandle<N> allocate_multi()
    {
      if constexpr (N == 1) return allocate();
      if constexpr (N == 2) return {allocate(), allocate()};
    }

    AudioBufferHandle allocate_clear()
    {
      auto res = allocate();
      res.clear();
      return res;
    }

    template<std::size_t N>
    MultiChannelAudioBufferHandle<N> allocate_multi_clear()
    {
      if constexpr (N == 1) return allocate_clear();
      if constexpr (N == 2) return {allocate_clear(), allocate_clear()};
    }

    void reserve(std::size_t n)
    {
      if (_avaliable_buffers > 0) {
        LOGF("Requested {} buffers. only {} avaliable", n, _avaliable_buffers);
        return;
      }
      if (n > _avaliable_buffers) {
        data = std::make_unique<float[]>(n * buffer_size);
        _avaliable_buffers = n;
        reference_counts.resize(_avaliable_buffers, 0);
      }
    }

  private:
    const std::size_t buffer_size;
    std::vector<int> reference_counts;
    std::size_t _avaliable_buffers = 0;
    std::unique_ptr<float[]> data;
    std::size_t _max_val = -1;
  };

  /// Non-owning package of data passed to audio processors
  template<int N>
  struct ProcessData {
    static constexpr int channels = N;

    MultiChannelAudioBufferHandle<channels> audio;
    midi::shared_vector<midi::AnyMidiEvent> midi;

    long nframes;

    template<int outN = 0>
    ProcessData<outN> midi_only()
    {
      return {{}, midi, nframes};
    }

    ProcessData audio_only()
    {
      return {audio, {}, nframes};
    }

    template<std::size_t NN>
    auto redirect(const MultiChannelAudioBufferHandle<NN>& buf)
    {
      return ProcessData<NN>{buf, midi, nframes};
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
      auto res = *this;
      length = length < 0 ? nframes - idx : length;
      res.nframes = length;
      if constexpr (channels != 0) {
        res.audio = audio.slice(idx, length);
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
