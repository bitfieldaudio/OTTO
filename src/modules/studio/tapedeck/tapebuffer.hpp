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
    struct IteratorImpl {
      using value_type        = value_type;
      using iterator_category = std::bidirectional_iterator_tag;

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

      value_type& dereference() { return *value; }

      tape_buffer& owner;
      value_type* value;
    };

    /// Specification for iterator
    ///
    /// Take a look at <iterator_adaptor>
    struct ConstIteratorImpl {
      using value_type        = value_type;
      using iterator_category = std::bidirectional_iterator_tag;
      using reference         = value_type;

      ConstIteratorImpl(tape_buffer& owner)
        : owner (owner)
      {}

      ConstIteratorImpl(const IteratorImpl& o)
        : owner (o.owner)
      {}


      void advance(int n)
      {
        owner.advance_const(n);
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
    using const_iterator = typename top1::float_step_iterator<iterator_adaptor<ConstIteratorImpl>>;

    /* Initialization */

    tape_buffer();
    ~tape_buffer();

    tape_buffer(tape_buffer&) = delete;
    tape_buffer(tape_buffer&&) = delete;

    /* Member functions */

    /// Get an iterator that moves forward, at speed `speed`
    iterator iter(float speed = 1.f)
    {
      return iterator({*this}, speed);
    }

    /// Get an iterator that moves forward, at speed `speed`
    const_iterator citer(float speed = 1.f)
    {
      return const_iterator({*this}, speed);
    }

    std::size_t position() const
    {
      return current_position;
    }

    /// Move the point `n` forward. `n` can be negative
    /// Updates `write_head` and `write_tail`
    void advance(int n = 1);

    /// Move the point `n` forward. `n` can be negative
    /// Does not mark section for writing
    void advance_const(int n = 1);

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
