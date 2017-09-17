#pragma once

#include <array>
#include <cmath>
#include <atomic>
#include <memory>

#include "util/iterator.hpp"
#include "util/algorithm.hpp"
#include "util/math.hpp"

namespace top1 {

  struct Producer;

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
    struct WriteIteratorImpl {
      using value_type        = value_type;
      using iterator_category = std::bidirectional_iterator_tag;

      WriteIteratorImpl(tape_buffer& owner)
        : owner (owner)
      {}

      WriteIteratorImpl(const WriteIteratorImpl& o)
        : owner (o.owner)
      {}


      void advance(int n)
      {
        owner.advance_write(n);
        value = &owner.cur_value();
      }

      bool compare(const WriteIteratorImpl& r) const
      {
        return value == r.value;
      }

      value_type& dereference() { return *value; }

      tape_buffer& owner;
      value_type* value;
    };

    /// Specification for iterator
    ///
    /// Take a look at <iterator_adaptor>
    struct ReadIteratorImpl {
      using value_type        = value_type;
      using iterator_category = std::bidirectional_iterator_tag;
      using reference         = value_type;

      ReadIteratorImpl(tape_buffer& owner)
        : owner (owner)
      {}

      ReadIteratorImpl(const WriteIteratorImpl& o)
        : owner (o.owner)
      {}


      void advance(int n)
      {
        owner.advance_read(n);
        value = &owner.cur_value();
      }

      bool compare(const WriteIteratorImpl& r) const
      {
        return value == r.value;
      }

      value_type dereference() { return *value; }

      tape_buffer& owner;
      const value_type* value;
    };

    using iterator = typename top1::float_step_iterator<iterator_adaptor<WriteIteratorImpl>>;
    using const_iterator = typename top1::float_step_iterator<iterator_adaptor<ReadIteratorImpl>>;

    /* Initialization */

    tape_buffer();
    ~tape_buffer();

    tape_buffer(tape_buffer&) = delete;
    tape_buffer(tape_buffer&&) = delete;

    /* Member functions */

    /// Get an iterator that moves forward, at speed `speed`
    iterator write(float speed = 1.f)
    {
      return iterator({*this}, speed);
    }

    /// Get an iterator that moves forward, at speed `speed`
    const_iterator read(float speed = 1.f)
    {
      return const_iterator({*this}, speed);
    }

    std::size_t position() const
    {
      return current_position;
    }

    /// Move the point `n` forward. `n` can be negative
    /// Updates `write_head` and `write_tail`
    void advance_write(int n = 1);

    /// Move the point `n` forward. `n` can be negative
    /// Does not mark section for writing
    void advance_read(int n = 1);

    /// Get a refference to the value at point
    value_type& cur_value();

    void jump_to(std::size_t);

  private:

    /* Member variables */

    using buffer_type = std::array<value_type, buffer_size>;

    /// The current file position
    /// This variable should only be modified by the consumer - to everyone else
    /// it is read only!
    std::atomic_size_t current_position = 0;

    // Beginning/end of loaded section. File position, *not* buffer index
    // These variables should only be modified by the producer
    std::atomic_size_t head;
    std::atomic_size_t tail;

    struct WriteSect {
      std::size_t head;
      std::size_t tail;
    };

    std::atomic<WriteSect> write_sect;

    buffer_type buffer;

    // Defined in implementation file
    friend struct Producer;
    std::unique_ptr<Producer> producer;

  };
}
