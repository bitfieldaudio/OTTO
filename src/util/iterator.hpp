#pragma once

#include <iterator>
#include <cmath>
#include <functional>
#include <type_traits>

namespace top1 {

  namespace detail {

    /// A function object used to call `operator*()`
    struct dereference {

      /// @return `*iter`
      template<typename Iter>
      decltype(auto) operator()(Iter&& iter) const {
        return *iter;
      }

      /// @return `*iter`
      template<typename Iter>
      decltype(auto) operator()(const Iter&& iter) const {
        return *iter;
      }
    };
  }

  /// An iterator wrapper to iterate with a non-integer ratio
  ///
  /// This iterates through contiguous data, or simply increments an
  /// integer value, with floating point steps. It keeps track of the
  /// error, and corrects it while iterating.
  ///
  /// The most common use case is iterating over data at a non-integer
  /// rate ratio. In the TOP-1 it is used to read sound samples at a
  /// different rate than how they were recorded.
  ///
  /// When used to iterator through data, it is preferred to use
  /// `first < last` as the loop condition, as opposed to the
  /// conventional `first != last`. The need for doing this depends on
  /// the relationship between the `first` and `last` iterators. If
  /// one was created from the other, using <operator+> or
  /// <operator->, they are guarantied to be reachable from the other
  /// using <operator++> or <operator--> as applicable, as long as the
  /// <step> member variable on the mutating iterator is unchanged.
  ///
  /// `float_step_iterator` nearly models a random access iterator,
  /// missing only a few operations, that may be added in the future.
  /// but should not be used as such. It does however model a
  /// Bidirectional iterator.
  ///
  /// @I Not required to be an iterator. It may be any
  ///    incrementable type, such as an integer. If it is an iterator
  ///    however, it is required to be random access.
  ///
  /// @Dereference The type of the function object used to
  ///    "dereference" the iterator. By default it is a wrapper around
  ///    `operator*()`, and can therefore be left untouched for
  ///    wrapping iterators or pointers.
  template<typename I, typename Dereference = detail::dereference,
    typename = std::enable_if_t<std::is_invocable_v<Dereference, I>>>
  class float_step_iterator {

    /*
     * Member types
     */

    using self_type = float_step_iterator;
    using ptr_type = I;

    // for `std::iterator_traits`
    using difference_type = float;
    using value_type = std::invoke_result_t<Dereference, I>;
    using pointer = value_type*;
    using reference = value_type&;
    using iterator_category = std::bidirectional_iterator_tag;

    /*
     * Initialization
     */

    /// Construct an iterator, pointing to `ptr`
    float_step_iterator(ptr_type ptr, float step = 1.f,
      Dereference d = Dereference {}) :
      ptr {ptr}, step {step}, dereference {d}
    {}

      /// Copy constructor
      float_step_iterator(self_type& r) :
        ptr {r.ptr},
        step {r.step},
        _error {r._error},
        dereference {r.dereference}
    {}

    /// Move constructor
    float_step_iterator(self_type&& r) :
      ptr {std::move(r.ptr)},
      step {std::move(r.step)},
      _error {std::move(r._error)},
      dereference {std::move(r.dereference)}
    {}

    // Default assignment operator
    self_type& operator=(self_type&) = default;

    // Default assignment operator
    self_type& operator=(self_type&&) = default;

    /*
     * Operators
     */

    /// Dereference the iterator
    ///
    /// Invokes the function object <dereference> on the underlying
    /// pointer.
    value_type& operator*()
    {
      return std::invoke(dereference, ptr);
    }

    /// Dereference the iterator
    const value_type& operator*() const
    {
      return std::invoke(dereference, ptr);
    }

    /// Compare equal
    ///
    /// Requires members <ptr> and <_error> to be equal.
    /// Ignores <step>, as it has no effect on the dereferenced value.
    bool operator==(const self_type& r) const
    {
      return ptr == r.ptr && _error == r._error;
    }

    /// Compare not-equal
    ///
    /// Defined as `!(*this == r)`
    bool operator!=(const self_type& r) const
    {
      return !(*this == r);
    }

    /// Compare less than
    ///
    /// Compares the <ptr> member. Behaviour is undefined if
    /// <tape_buffer> is not the same for both iterators.
    bool operator<(const self_type& r) const
    {
      return ptr < r.ptr;
    }

    /// Compare greater than
    ///
    /// Compares the <ptr> member. Behaviour is undefined if
    /// <tape_buffer> is not the same for both iterators.
    bool operator>(const self_type& r) const
    {
      return ptr > r.ptr;
    }

    /// Compare less than or equal
    ///
    /// Compares the <ptr> member. Behaviour is undefined if
    /// <tape_buffer> is not the same for both iterators.
    bool operator<=(const self_type& r) const
    {
      return ptr <= r.ptr;
    }

    /// Compare greater than or equal
    ///
    /// Compares the <ptr> member. Behaviour is undefined if
    /// <tape_buffer> is not the same for both iterators.
    bool operator>=(const self_type& r) const
    {
      return ptr >= r.ptr;
    }

    /// Increment this iterator
    ///
    /// Increments <ptr> by <step> + <_error>, wrapping around to
    /// the beginning of the buffer if necessary. Sets the new
    /// <_error> value accordingly.
    ///
    /// @return A copy of this iterator pre-increment.
    self_type operator++()
    {
      self_type old = *this;
      *this += 1;
      return old;
    }

    /// Increment this iterator
    ///
    /// Increments <ptr> by <step> + <_error>, wrapping around to
    /// the beginning of the buffer if necessary. Sets the new
    /// <_error> value accordingly.
    ///
    /// @return A reference to this iterator post-increment.
    self_type& operator++(int)
    {
      *this += 1;
      return *this;
    }

    /// Decrement this iterator
    ///
    /// Decrements <ptr> by <step> - <_error>, wrapping around to
    /// the beginning of the buffer if necessary. Sets the new
    /// <_error> value accordingly.
    ///
    /// @return A copy of this iterator pre-decrement.
    self_type operator--()
    {
      self_type old = *this;
      *this -= 1;
      return old;
    }

    /// Decrement this iterator
    ///
    /// Decrements <ptr> by <step> + <_error>, wrapping around to
    /// the beginning of the buffer if necessary. Sets the new
    /// <_error> value accordingly.
    ///
    /// @return A reference to this iterator post-decrement.
    self_type& operator--(int)
    {
      *this -= 1;
      return *this;
    }

    /// Get a copy of this, incremented by `n`
    ///
    /// Guarrantied to return an iterator equal to this incremented
    /// `n` times. "Equal" in this case is stronger than
    /// <operator==>, as <step> will also be the same.
    self_type operator+(int n) const
    {
      self_type ret {*this};
      return std::move(ret += n);
    }

    /// Get a copy of this, decremented by `n`
    ///
    /// Guarrantied to return an iterator equal to this incremented
    /// `n` times. "Equal" in this case is stronger than
    /// <operator==>, as <step> will also be the same.
    self_type operator-(int n) const
    {
      self_type ret {*this};
      return std::move(ret -= n);
    }

    /// Get the real difference between this and `o`
    ///
    /// Takes the error values into account.
    difference_type operator-(const self_type& o) const {
      return float(ptr - o.ptr) + (_error - o._error);
    }

    /// Increment this by `n`
    ///
    /// Guarrantied to be equal to calling <operator++> `n` times
    ///
    /// @return `*this`
    self_type& operator+=(int n)
    {
      float intPart = 0;
      _error = std::modf(_error + step * n, &intPart);
      ptr += std::size_t(intPart);
      return *this;
    }

    /// Decrement this by `n`
    ///
    /// Guarrantied to be equal to calling <operator--> `n` times
    ///
    /// @return `*this`
    self_type& operator-=(int n)
    {
      float intPart = 0;
      _error = std::modf(ptr + _error - step * n, &intPart);
      ptr += std::size_t(intPart);
      return *this;
    }

    /*
     * Member functions
     */

    /// Get a copy of the underlying pointer.
    ptr_type data() const {
      return ptr;
    }

    /// The inaccuracy of the element this iterator points to.
    ///
    /// While <step> is an integer, this value will be constant.
    /// Otherwise it is in the range `[0, 1)`, signifying the
    /// fractional part of the real index. I.e.
    /// `ptr + error() == real_index`.
    float error() const {
      return _error;
    }

    /*
     * Member Variables
     */

    /// The size of one step
    ///
    /// When incrementing, <ptr> will be effectively be incremented by
    /// this value.
    ///
    /// Changing this value does not invalidate any iterator, but be
    /// aware that an end iterator previously created using
    /// `*this + n` might no longer be reachable by incrementing this.
    /// If you need to change the iterator step while looping, prefer
    /// using `iter < last` over `iter != last`
    float step = 1.f;

  private:

    /// See getter, <error>
    float _error = 0.f;

    /// The underlying pointer
    ///
    /// For public, read only access, use <data>
    ptr_type ptr;

    /// Instance of the function object used to dereference <ptr>
    Dereference dereference {};

  };
}
