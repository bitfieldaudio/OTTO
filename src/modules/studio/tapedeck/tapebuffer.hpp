#pragma once

#include <array>
#include <cmath>
#include <atomic>
#include <memory>

#include "util/iterator.hpp"
#include "util/algorithm.hpp"
#include "util/math.hpp"
#include "util/audio.hpp"

namespace top1 {

  // FDCL - Defined in tapebuffer.cpp
  struct Producer;

  // A simple array wrapper that provides an iterator that wraps across to the
  // end
  // `N` should be a power of two. Otherwise performance will be terrible!
  template<typename T, std::size_t N>
  struct wrapping_array {
    static constexpr std::size_t size = N;

    /// Get the buffer position corresponding to `position`
    static constexpr std::size_t wrap(std::size_t index)
    {
      return index % size;
    }

    /// Specification for iterator
    ///
    /// Take a look at <iterator_adaptor>
    template<typename Val>
    struct IteratorImpl {
      using value_type        = Val;
      using iterator_category = std::random_access_iterator_tag;

      IteratorImpl(value_type* begin, std::size_t index)
        : value (begin + wrap(index)), index (wrap(index))
      {}

      void advance(int n)
      {
        auto newIndex = wrap(index + n);
        value += (newIndex - index);
        index = newIndex;
      }

      bool equal(const IteratorImpl& r) const
      {
        return value == r.value;
      }

      std::ptrdiff_t difference(const IteratorImpl& r) const
      {
        return value - r.value;
      }

      value_type& dereference() { return *value; }

      value_type* value;
      std::size_t index;
    };

    using value_type = T;
    std::array<value_type, size> storage;
    using iterator = iterator_adaptor<IteratorImpl<value_type>>;
    using const_iterator = iterator_adaptor<IteratorImpl<const value_type>>;

    iterator begin() {return {storage.data(), 0U};}
    const_iterator begin() const {return {storage.data(), 0U};}
    value_type* data() {return storage.data(); }

    iterator iter(std::size_t index) {return {storage.data(), index};}
    const_iterator iter(std::size_t index) const {return {storage.data(), index};}
    const_iterator citer(std::size_t index) const {return {storage.data(), index};}

    value_type& operator[](std::size_t idx) {
      return storage[wrap(idx)];
    }
  };

  /// The buffer used for the tapedeck
  ///
  /// Provides reading from file, variable speed reading/writing in both
  /// directions and access to tape metadata, such as slices.
  class tape_buffer {
    using Value = std::array<float, 4>;
  public:

    /* Constants */

    static constexpr std::size_t buffer_size = 1 << 18;
    static constexpr std::size_t max_length = 8 * 60 * 44100;

    using value_type = Value;

    /* Initialization */

    tape_buffer();
    ~tape_buffer();

    tape_buffer(tape_buffer&) = delete;
    tape_buffer(tape_buffer&&) = delete;

    /* Member functions */

    std::size_t position() const
    {
      return current_position;
    }

    /// Move the point `n` forward. `n` can be negative
    void advance(int n = 1);

    /// Get a refference to the value at point
    value_type& cur_value();

    /// Write `n` frames from `iter`.
    ///
    /// `iter` will be slowed down/sped up according to `speed`. If `speed` is
    /// positive, the frames will be written "behind" the cursor, as in, the
    /// last frame will be positioned at `cursor - 1`. If `speed` is negative,
    /// the first frame in the range will be positioned at `cursor + 1`.
    /// If `speed` is `0`, nothing will be written
    template<typename UnaryFunc>
    void write_frames(int n, float speed, UnaryFunc&& func)
    {
      audio::Section<int> written;
      int write_n;
      if (speed > 0) {
        write_n = n / speed;
        written = {current_position - write_n, current_position - 1};
      } else if (speed < 0) {
        write_n = n / -speed;
        written = {current_position + 1, current_position + write_n};
      }

      for_each_n(buffer.iter(written.in), write_n,
        [&] (auto& frm) {
          std::invoke(func, frm);
        });

      // Atomically update `write_sect`
      audio::Section<int> new_sect;
      auto expected_sect = write_sect.load();
      do {
        new_sect = written;
        if (expected_sect.size() != 0) {
          new_sect += expected_sect;
        }
      } while (!write_sect.compare_exchange_weak(expected_sect, new_sect));
    }

    template<typename Iter>
    void read_frames(int n, float speed, Iter dst)
    {
      float error = 0.f;
      auto src = buffer.citer(current_position);
      for (int i = 0; i < n; i++, dst++) {
        float intpart = 0;
        error = std::modf(speed + error, &intpart);
        *dst = *src;
        std::advance(src, intpart);
      }
      advance(n * speed);
    }

    /// Jumps the tape to absolute position `p`
    ///
    /// Use sparingly - a jump clears the entire buffer
    void jump_to(std::size_t p);

    /* Member variables */

    using buffer_type = wrapping_array<value_type, buffer_size>;

    /// The current file position
    /// This variable should only be modified by the consumer - to everyone else
    /// it is read only!
    std::atomic_int current_position {0};

    // Beginning/end of loaded section. File position, *not* buffer index
    // These variables should only be modified by the producer
    std::atomic_int head {0};
    std::atomic_int tail {0};

    std::atomic<audio::Section<int>> write_sect;

    buffer_type buffer;

    // Defined in implementation file
    friend struct Producer;
    std::unique_ptr<Producer> producer;

  };
}
