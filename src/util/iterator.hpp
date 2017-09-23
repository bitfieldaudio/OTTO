#pragma once

#include <iterator>
#include <cmath>
#include <iterator>
#include <type_traits>

namespace top1 {

  namespace detail {

    // Difference type

    template<typename Impl, typename T = void>
    struct difference_type {
      using type = std::ptrdiff_t;
    };

    template<typename Impl>
    struct difference_type<Impl, std::void_t<typename Impl::difference_type>> {
      using type = typename Impl::difference_type;
    };

    // Value type

    template<typename Impl, typename T = void>
    struct value_type {
      using type = typename Impl::value_type;
    };

    template<typename Impl>
    struct value_type<Impl,
      std::void_t<typename std::iterator_traits<Impl>::value_type>>
    {
      using type = typename std::iterator_traits<Impl>::value_type;
    };

    // Pointer type

    template<typename Impl, typename T = void>
    struct pointer {
      using type = typename value_type<Impl>::type*;
    };

    template<typename Impl>
    struct pointer<Impl, std::void_t<typename Impl::pointer>> {
      using type = typename Impl::pointer;
    };

    // Reference type

    template<typename Impl, typename T = void>
    struct reference {
      using type = typename value_type<Impl>::type&;
    };

    template<typename Impl>
    struct reference<Impl, std::void_t<typename Impl::reference>>
    {
      using type = typename Impl::reference;
    };

    // Iterator category

    template<typename Impl, typename T = void>
    struct iterator_category
    {
      using type = typename Impl::iterator_category;
    };

    template<typename Impl>
    struct iterator_category<Impl,
      std::void_t<typename std::iterator_traits<Impl>::iterator_category>>
    {
      using type = typename std::iterator_traits<Impl>::iterator_category;
    };
  }


  /*
   * Iterator Adaptor
   */
  
  template<typename Impl, typename Category = void>
  class iterator_adaptor_impl : public Impl {
  public:
    // For std::type_traits
    using difference_type = typename detail::difference_type<Impl>::type;
    using value_type = typename detail::value_type<Impl>::type;
    using pointer = typename detail::pointer<Impl>::type;
    using reference = typename detail::reference<Impl>::type;
    using iterator_category = typename detail::iterator_category<Impl>::type;

    /* Initialization */

    template<typename... Args>
    iterator_adaptor_impl(Args&&... args)
      : Impl {std::forward<Args>(args)...} {}

    using Impl::operator=;

    /* Operators */

    // Increment (Any)

    iterator_adaptor_impl& operator++()
    {
      auto old = *this;
      Impl::advance(1);
      return old;
    }

    iterator_adaptor_impl& operator++(int)
    {
      Impl::advance(1);
      return *this;
    }

    iterator_adaptor_impl& operator+=(difference_type d)
    {
      Impl::advance(d);
      return *this;
    }

    // Dereference (Any)
    decltype(auto) operator*()
    {
      return Impl::dereference();
    }

    decltype(auto) operator*() const
    {
      return Impl::dereference();
    }

    decltype(auto) operator->()
    {
      return Impl::dereference();
    }

    decltype(auto) operator->() const
    {
      return Impl::dereference();
    }

    // Comparison (Any)
    bool operator==(const iterator_adaptor_impl& r)
    {
      return Impl::compare(r);
    }

    bool operator!=(const iterator_adaptor_impl& r)
    {
      return !Impl::compare(r);
    }

  };

  template<typename Impl>
  class iterator_adaptor_impl<Impl, std::bidirectional_iterator_tag>
    : public iterator_adaptor_impl<Impl, void>
  {
    using Super = iterator_adaptor_impl<Impl, void>;
  public:
    using typename Super::difference_type;
    using typename Super::value_type;
    using typename Super::pointer;
    using typename Super::reference;
    using typename Super::iterator_category;

    template<typename... Args>
    iterator_adaptor_impl(Args&&... args)
      : Super {std::forward<Args>(args)...} {}

    using Super::operator=;

    using Super::operator++;
    using Super::operator*;
    using Super::operator->;
    using Super::operator==;
    using Super::operator!=;

    // Decrement (Bidirectional)

    iterator_adaptor_impl& operator--()
    {
      auto old = *this;
      Impl::advance(-1);
      return old;
    }

    iterator_adaptor_impl& operator--(int)
    {
      Impl::advance(-1);
      return *this;
    }

    iterator_adaptor_impl& operator-=(difference_type d)
    {
      Impl::advance(-d);
      return *this;
    }

  };

  template<typename Impl>
  class iterator_adaptor_impl<Impl, std::random_access_iterator_tag>
    : public iterator_adaptor_impl<Impl, std::bidirectional_iterator_tag>
  {
    using Super = iterator_adaptor_impl<Impl, std::bidirectional_iterator_tag>;
  public:
    using typename Super::difference_type;
    using typename Super::value_type;
    using typename Super::pointer;
    using typename Super::reference;
    using typename Super::iterator_category;

    template<typename... Args>
    iterator_adaptor_impl(Args&&... args)
      : Super {std::forward<Args>(args)...} {}

    using Super::operator=;

    using Super::operator++;
    using Super::operator*;
    using Super::operator->;
    using Super::operator==;
    using Super::operator!=;

    using Super::operator--;

    // Arithmetics (Random access)

    iterator_adaptor_impl operator+(difference_type d) const
    {
      iterator_adaptor_impl res {*this};
      res.Impl::advance(d);
      return res;
    }

    iterator_adaptor_impl operator-(difference_type d) const
    {
      iterator_adaptor_impl res {*this};
      res.Impl::advance(-d);
      return res;
    }

    difference_type operator-(const iterator_adaptor_impl& d) const
    {
      return Impl::distance(d);
    }

    // Inequality (Random access)

    bool operator<(const iterator_adaptor_impl& d) const
    {
      return Impl::compare(d) < 0;
    }

    bool operator>(const iterator_adaptor_impl& d) const
    {
      return Impl::compare(d) > 0;
    }

    bool operator<=(const iterator_adaptor_impl& d) const
    {
      return Impl::compare(d) <= 0;
    }

    bool operator>=(const iterator_adaptor_impl& d) const
    {
      return Impl::compare(d) >= 0;
    }

    // Compound assignment (Random access)

    iterator_adaptor_impl& operator+=(difference_type d)
    {
      Impl::advance(d);
      return *this;
    }

    iterator_adaptor_impl& operator-=(difference_type d)
    {
      Impl::advance(-d);
      return *this;
    }

    // Offset dereference (Random access)

    reference operator[](difference_type d)
    {
      return *(*this + d);
    }

  };

  ///
  /// Zero overhead wrapper to create iterators
  ///
  /// @Impl must define the following member functions:
  /// ```
  /// void advance(difference_type);
  /// reference dereference();
  /// int compare(const Impl&);
  /// ```
  /// Other than those, it must define a copy constructor, and either the member
  /// types `iterator_category` and `value_type`, or a specialization of
  /// `std::iterator_traits`. Any other of the five `iterator_traits` types will
  /// also be read used from `Impl` if avaliable
  ///
  template<typename Impl>
  using iterator_adaptor = iterator_adaptor_impl<Impl,
    typename detail::iterator_category<Impl>::type>;



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
  /// @I A random access iterator that will be wrapped.
  /// @V The value type.
  template<typename I,
    typename V = typename detail::value_type<I>::type>
  class float_step_iterator {
  public:
    /*
     * Member types
     */

    using self_type = float_step_iterator;
    using ptr_type = I;

    // for `std::iterator_traits`
    using difference_type = float;
    using value_type = V;
    using pointer = typename detail::pointer<I>::type;
    using reference = typename detail::reference<I>::type;
    using iterator_category = std::bidirectional_iterator_tag;

    /*
     * Initialization
     */

    /// Construct an iterator, pointing to `ptr`
    float_step_iterator(ptr_type ptr, float step = 1.f)
      : ptr {ptr}, step {step}
    {}

    /// Copy constructor
    float_step_iterator(self_type& r)
      : ptr {r.ptr},
        step {r.step},
        _error {r._error}
    {}

    /// Move constructor
    float_step_iterator(self_type&& r)
      : ptr {std::move(r.ptr)},
        step {std::move(r.step)},
        _error {std::move(r._error)}
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
    /// Propagates to the dereference operator of <ptr>
    reference operator*()
    {
      return *ptr;
    }

    /// Dereference the iterator
    ///
    /// Propagates to the dereference operator of <ptr>
    const reference operator*() const
    {
      return *ptr;
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
      return ret += n;
    }

    /// Get a copy of this, decremented by `n`
    ///
    /// Guarrantied to return an iterator equal to this incremented
    /// `n` times. "Equal" in this case is stronger than
    /// <operator==>, as <step> will also be the same.
    self_type operator-(int n) const
    {
      self_type ret {*this};
      return ret -= n;
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
  };

}
