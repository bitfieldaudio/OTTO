#pragma once

#include <algorithm>
#include <ranges>
#include <span>

#include "lib/util/ranges.hpp"

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
    explicit audio_buffer(std::span<float> d, std::int8_t* ref_count) noexcept;

    audio_buffer(const audio_buffer& rhs) noexcept = delete;
    /// Copy assignment. NOTE: Deep, i.e., Modifies the values in the buffer
    audio_buffer& operator=(const audio_buffer& rhs);

    audio_buffer(audio_buffer&& rhs) noexcept;
    audio_buffer& operator=(audio_buffer&& rhs) noexcept;

    ~audio_buffer() noexcept;

    [[nodiscard]] iterator begin() noexcept;
    [[nodiscard]] iterator end() noexcept;

    [[nodiscard]] const_iterator begin() const noexcept;
    [[nodiscard]] const_iterator end() const noexcept;

    [[nodiscard]] float* data() noexcept;
    [[nodiscard]] float* data() const noexcept;

    [[nodiscard]] std::size_t size() const noexcept;

    /// Fill buffer with zeros
    audio_buffer& clear() noexcept;

    float& operator[](std::size_t i) noexcept;
    const float& operator[](std::size_t i) const noexcept;

  private:
    std::span<float> data_;
    std::int8_t* ref_count_;
  };

  static_assert(std::ranges::contiguous_range<audio_buffer>);
  static_assert(std::ranges::sized_range<audio_buffer>);
  static_assert(std::ranges::random_access_range<audio_buffer>);

  struct stereo_audio_buffer {
    audio_buffer left;
    audio_buffer right;

    stereo_audio_buffer(audio_buffer&& l, audio_buffer&& r) noexcept : left(std::move(l)), right(std::move(r)) {}
    stereo_audio_buffer(stereo_audio_buffer&&) = default;

    /// Copy assignment. NOTE: Deep, i.e., Modifies the values in the buffer
    stereo_audio_buffer& operator=(const stereo_audio_buffer& rhs)
    {
      left = rhs.left;
      right = rhs.right;
      return *this;
    }

    stereo_audio_buffer& clear() & noexcept
    {
      left.clear();
      right.clear();
      return *this;
    }
    stereo_audio_buffer&& clear() && noexcept
    {
      left.clear();
      right.clear();
      return std::move(*this);
    }

    [[nodiscard]] auto zipped() noexcept
    {
      return util::zip(left, right);
    }

    [[nodiscard]] auto zipped() const noexcept
    {
      return util::zip(left, right);
    }

    [[nodiscard]] auto begin() noexcept
    {
      return zipped().begin();
    }
    [[nodiscard]] auto begin() const noexcept
    {
      return zipped().begin();
    }

    [[nodiscard]] auto end() noexcept
    {
      return zipped().end();
    }
    [[nodiscard]] auto end() const noexcept
    {
      return zipped().end();
    }
  };

  /// An init-time fixed-size pool to allocate {@ref audio_buffer}s of varying sizes.
  struct AudioBufferPool {
    explicit AudioBufferPool(std::size_t max_buf_count, std::size_t bufsize);

    /// Allocate an audio buffer
    [[nodiscard]] audio_buffer allocate(std::size_t multiplier = 1) noexcept;
    [[nodiscard]] stereo_audio_buffer allocate_stereo(const std::size_t multiplier = 1) noexcept
    {
      return {allocate(multiplier), allocate(multiplier)};
    }

    [[nodiscard]] std::span<const float> data() const noexcept;

  private:
    std::size_t bufsize_;
    std::vector<std::int8_t> ref_counts_;
    std::vector<float> data_;
  };

} // namespace otto::util
