#include "audio_buffer.hpp"
#include "lib/logging.hpp"

namespace otto::util {

  audio_buffer::audio_buffer(std::span<float> d, std::int8_t* ref_count) noexcept : data_(d), ref_count_(ref_count)
  {
    if (ref_count_) (*ref_count_)++;
  }

  audio_buffer::audio_buffer(audio_buffer&& rhs) noexcept : data_(rhs.data_), ref_count_(rhs.ref_count_)
  {
    rhs.ref_count_ = nullptr;
  }

  audio_buffer::~audio_buffer() noexcept
  {
    if (ref_count_) (*ref_count_)--;
  }

  audio_buffer::iterator audio_buffer::end() noexcept
  {
    return &*std::end(data_);
  }

  audio_buffer::iterator audio_buffer::begin() noexcept
  {
    return &*std::begin(data_);
  }

  audio_buffer::const_iterator audio_buffer::end() const noexcept
  {
    return &*std::cend(data_);
  }

  audio_buffer::const_iterator audio_buffer::begin() const noexcept
  {
    return &*std::cbegin(data_);
  }

  audio_buffer& audio_buffer::clear() noexcept
  {
    std::fill(begin(), end(), 0);
    return *this;
  }

  std::size_t audio_buffer::size() const noexcept
  {
    return data_.size();
  }

  float* audio_buffer::data() const noexcept
  {
    return data_.data();
  }

  float* audio_buffer::data() noexcept
  {
    return data_.data();
  }

  float& audio_buffer::operator[](std::size_t i) noexcept
  {
    return data_[i];
  }

  const float& audio_buffer::operator[](std::size_t i) const noexcept
  {
    return data_[i];
  }

  audio_buffer& audio_buffer::operator=(const audio_buffer& rhs)
  {
    std::copy(rhs.begin(), rhs.end(), begin());
    return *this;
  }

  // AudioBufferPool

  AudioBufferPool::AudioBufferPool(std::size_t max_buf_count, std::size_t bufsize) : bufsize_(bufsize)
  {
    ref_counts_.resize(max_buf_count);
    data_.resize(max_buf_count * bufsize_);
  }

  audio_buffer AudioBufferPool::allocate(const std::size_t multiplier) noexcept
  {
    // Find unused buffer
    int idx = 0;
    int n_found = 0;
    int actual_rc = 0;
    for (const int rc : ref_counts_) {
      if (rc >= 0) actual_rc = rc;
      if (actual_rc == 0) {
        n_found++;
        if (n_found == multiplier) break;
      } else {
        n_found = 0;
      }
      idx++;
    }
    // TODO: error handling?
    OTTO_ASSERT(n_found == multiplier);

    auto first_idx = idx - multiplier + 1;
    ref_counts_[first_idx] = 0;
    // When multiplier is > 1, refcounts of all but the first used buffer
    // are set to -1, to indicate
    for (int i = 1; i < multiplier; i++) {
      ref_counts_[first_idx + i] = -1;
    }
    // Clear remaining -1s when using a space that was previously used for a larger buffer
    for (int i = first_idx + multiplier; i < ref_counts_.size(); i++) {
      if (ref_counts_[i] >= 0) break;
      ref_counts_[i] = 0;
    }
    return audio_buffer({data_.data() + bufsize_ * first_idx, bufsize_ * n_found}, &ref_counts_[first_idx]);
  }

  std::span<const float> AudioBufferPool::data() const noexcept
  {
    return data_;
  }
} // namespace otto::util
