#pragma once

#include <array>
#include <cmath>
#include <atomic>

#include "util/iterator.hpp"
#include "util/algorithm.hpp"
#include "util/math.hpp"

namespace top1 {

  /// @N The ringbuffer size is `1 << N`
  template<typename T, std::size_t N>
  class basic_tape_buffer {
  public:

    /*
     * Constants
     */

    using value_type = T;
    static constexpr std::size_t buffer_size = 1 << N;

    /// Specification for iterator
    ///
    /// Take a look at <iterator_adaptor>
    struct IteratorImpl {
      using value_type        = value_type;
      using iterator_category = std::bidirectional_iterator_tag;

      IteratorImpl(basic_tape_buffer& owner)
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

      basic_tape_buffer& owner;
      value_type* value;
    };

    using iterator = float_step_iterator<iterator_adaptor<IteratorImpl>>;

    /*
     * Initialization
     */

    basic_tape_buffer() {}

    basic_tape_buffer(basic_tape_buffer&) = delete;

    /// Movable
    basic_tape_buffer(basic_tape_buffer&&)
    {
      // TODO;
    }

    /*
     * Member functions
     */

  private:

    void advance(int n = 1)
    {
      current_index += n;
    }

    value_type& cur_value()
    {
      return buffer[modulo(current_index, buffer_size)];
    }


    /*
     * Member variables
     */

    using buffer_type = std::array<value_type, buffer_size>;

    /// The number of loaded elements going forwards from <current_index>
    std::size_t fw_length = 0;
    /// The number of loaded elements going backwards from <current_index>
    std::size_t bw_length = 0;
    /// The offset of the beginning of the buffer, relative to the beginning of
    /// the file
    std::size_t buffer_offset = 0;

    /// The current index into the buffer.
    std::atomic_int current_index = 0;

    buffer_type buffer;
  };

}
