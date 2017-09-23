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

  struct Producer;

  // A simple array wrapper that provides an iterator that wraps across to the
  // end
  // `N` should be a power of two. Otherwise performance will be terrible!
  template<typename T, std::size_t N>
  struct wrapping_array {
    using value_type = T;
    static constexpr std::size_t size = N;

    std::array<value_type, size> storage;

    /// Get the buffer position corresponding to `position`
    static constexpr std::size_t wrap(std::size_t index)
    {
      return index % size;
    }

    /// Specification for iterator
    ///
    /// Take a look at <iterator_adaptor>
    struct IteratorImpl {
      using value_type        = value_type;
      using iterator_category = std::random_access_iterator_tag;

      IteratorImpl(value_type* begin, std::size_t index)
        : value (begin + wrap(index)), index (index)
      {}

      void advance(int n)
      {
        auto newIndex = wrap(index + n);
        value += (newIndex - index);
        index = newIndex;
      }

      bool compare(const IteratorImpl& r) const
      {
        return value == r.value;
      }

      value_type& dereference() { return *value; }

      value_type* value;
      std::size_t index;
    };

    /// Specification for iterator
    ///
    /// Take a look at <iterator_adaptor>
    struct ConstIteratorImpl {
      using value_type        = value_type;
      using iterator_category = std::random_access_iterator_tag;

      ConstIteratorImpl(value_type* begin, std::size_t index)
        : value (begin + wrap(index)), index (index)
      {}

      void advance(int n)
      {
        auto newIndex = wrap(index + n);
        value += (newIndex - index);
        index = newIndex;
      }

      bool compare(const ConstIteratorImpl& r) const
      {
        return value == r.value;
      }

      value_type dereference() { return *value; }

      value_type* value;
      std::size_t index;
    };

    using iterator = iterator_adaptor<IteratorImpl>;
    using const_iterator = iterator_adaptor<ConstIteratorImpl>;

    iterator begin() {return {storage.data(), 0U};}
    const_iterator begin() const {return {storage.data(), 0U};}
    value_type* data() {return storage.data(); }

    value_type& operator[](std::size_t idx) {
      return storage[wrap(idx)];
    }
  };

  /// A ringbuffer which allows consuming in both directions. It's
  /// single-consumer, single-producer, and provides a bidirectional, variable
  /// speed iterator for consuming.
  class tape_buffer {
  public:

    /* Constants */

    using value_type = std::array<float, 4>;
    static constexpr std::size_t buffer_size = 1 << 18;
    static constexpr std::size_t max_length = 8 * 60 * 44100;

    /// Specification for iterator
    ///
    /// Take a look at <iterator_adaptor>
    struct IteratorImpl {
      using value_type        = value_type;
      using iterator_category = std::bidirectional_iterator_tag;
      using reference         = value_type;

      IteratorImpl(tape_buffer& owner)
        : owner (owner)
      {}

      IteratorImpl(const IteratorImpl& o)
        : owner (o.owner)
      {}


      void advance(int n)
      {
        owner.advance(n);
        value = &owner.cur_value();
      }

      bool compare(const IteratorImpl& r) const
      {
        return value == r.value;
      }

      value_type dereference() { return *value; }

      tape_buffer& owner;
      const value_type* value;
    };

    using iterator = typename top1::float_step_iterator<iterator_adaptor<IteratorImpl>>;

    /* Initialization */

    tape_buffer();
    ~tape_buffer();

    tape_buffer(tape_buffer&) = delete;
    tape_buffer(tape_buffer&&) = delete;

    /* Member functions */

    /// Get an iterator that moves forward, at speed `speed`
    iterator read(float speed = 1.f)
    {
      return iterator({*this}, speed);
    }

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
      auto first = std::begin(buffer);
      int write_n;
      if (speed > 0) {
        write_n = n / speed;
        first += current_position - write_n;
        written = {current_position - write_n, current_position - 1};
      } else if (speed < 0) {
        write_n = n / -speed;
        first += current_position + 1;
        written = {current_position + 1, current_position + write_n};
      }

      auto gen = generator([&, iter = first] () mutable {
          value_type val = *iter; // Copy
          return std::invoke(func, std::move(val));
        });

      std::copy_n(gen, write_n, std::move(first));

      // Atomically update `write_sect`
      audio::Section<int> new_sect;
      auto expected_sect = write_sect.load();
      do {
        new_sect = expected_sect + written;
      } while (!write_sect.compare_exchange_weak(expected_sect, new_sect));
    }

    /// Jumps the tape to absolute position `p`
    ///
    /// Use sparingly - a jump clears the entire buffer
    void jump_to(std::size_t p);

  // private:

    /* Member variables */

    using buffer_type = wrapping_array<value_type, buffer_size>;

    /// The current file position
    /// This variable should only be modified by the consumer - to everyone else
    /// it is read only!
    std::atomic_int current_position = 0;

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
