#pragma once

#include <algorithm>
#include <ranges>
#include <span>

#include "concepts.hpp"

namespace otto::util {

  /// Reference-counting span of floats with deep assignment
  ///
  /// Designed to work with {@ref AudioBufferPool} for allocation
  struct audio_buffer {
    using iterator = float*;
    using const_iterator = const float*;

    /// Construct a buffer.
    /// @param ref_count can be nullptr to disable reference counting.
    explicit audio_buffer(std::span<float> d, int* ref_count) noexcept;

    audio_buffer(const audio_buffer& rhs) noexcept;

    ~audio_buffer() noexcept;

    /// Copy assignment. NOTE: Deep, i.e., Modifies the values in the buffer
    audio_buffer& operator=(const util::range_of<const float> auto& rhs)
    {
      std::ranges::copy(rhs, data_);
      return *this;
    }

    iterator begin() noexcept;
    iterator end() noexcept;

    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    float* data() noexcept;
    float* data() const noexcept;

    std::size_t size() const noexcept;

    /// Fill buffer with zeros
    audio_buffer& clear() noexcept;

  private:
    std::span<float> data_;
    int* ref_count_;
  };

  static_assert(std::ranges::contiguous_range<audio_buffer>);
  static_assert(std::ranges::sized_range<audio_buffer>);
  static_assert(std::ranges::random_access_range<audio_buffer>);

  /// An init-time fixed-size pool to allocate {@ref audio_buffer}s of varying sizes.
  struct AudioBufferPool {
    explicit AudioBufferPool(std::size_t max_buf_count, std::size_t bufsize);

    /// Allocate an audio buffer
    audio_buffer allocate(const std::size_t multiplier = 1) noexcept;

    std::span<const float> data() const noexcept;

  private:
    std::size_t bufsize_;
    std::vector<int> ref_counts_;
    std::vector<float> data_;
  };

} // namespace otto::util
