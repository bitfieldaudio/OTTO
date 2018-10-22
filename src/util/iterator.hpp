#pragma once

#include <iterator>
#include <cmath>
#include <functional>
#include <type_traits>
#include <tuple>
#include <memory>

#include "type_traits.hpp"

namespace otto::util {

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
      using type = typename std::iterator_traits<Impl>::value_type;
    };

    template<typename Impl>
    struct value_type<Impl,
      std::void_t<typename Impl::value_type>>
    {
      using type = typename Impl::value_type;
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
      using type = typename std::iterator_traits<Impl>::reference;
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
      using type = typename std::iterator_traits<Impl>::iterator_category;
    };

    template<typename Impl>
    struct iterator_category<Impl,
      std::void_t<typename Impl::iterator_category>>
    {
      using type = typename Impl::iterator_category;
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

    using Impl::Impl;

    template<typename... Args>
    iterator_adaptor_impl(Args&&... args)
      : Impl {std::forward<Args>(args)...} {}

    iterator_adaptor_impl(const iterator_adaptor_impl& r)
      : Impl {static_cast<Impl>(r)} {}

    iterator_adaptor_impl(iterator_adaptor_impl&& r)
      : Impl {static_cast<Impl>(std::move(r))} {}

    virtual ~iterator_adaptor_impl() = default;

    iterator_adaptor_impl& operator=(const iterator_adaptor_impl&) = default;
    iterator_adaptor_impl& operator=(iterator_adaptor_impl&&) = default;

    using Impl::operator=;

    /* Operators */

    // Increment (Any)

    iterator_adaptor_impl& operator++()
    {
      Impl::advance(1);
      return *this;
    }

    iterator_adaptor_impl operator++(int)
    {
      auto old = *this;
      Impl::advance(1);
      return old;
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
    bool operator==(const iterator_adaptor_impl& r) const
    {
      return Impl::equal(r);
    }

    bool operator!=(const iterator_adaptor_impl& r) const
    {
      return !Impl::equal(r);
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

    iterator_adaptor_impl(const iterator_adaptor_impl&) = default;
    iterator_adaptor_impl(iterator_adaptor_impl&&) = default;
    iterator_adaptor_impl& operator=(const iterator_adaptor_impl&) = default;
    iterator_adaptor_impl& operator=(iterator_adaptor_impl&&) = default;

    using Super::operator=;

    using Super::operator++;
    using Super::operator*;
    using Super::operator->;
    using Super::operator==;
    using Super::operator!=;

    // Decrement (Bidirectional)

    iterator_adaptor_impl& operator--()
    {
      Impl::advance(-1);
      return *this;
    }

    iterator_adaptor_impl operator--(int)
    {
      auto old = *this;
      Impl::advance(-1);
      return old;
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

    iterator_adaptor_impl(const iterator_adaptor_impl&) = default;
    iterator_adaptor_impl(iterator_adaptor_impl&&) = default;
    iterator_adaptor_impl& operator=(const iterator_adaptor_impl&) = default;
    iterator_adaptor_impl& operator=(iterator_adaptor_impl&&) = default;

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
      return Impl::difference(d);
    }

    // Inequality (Random access)

    bool operator<(const iterator_adaptor_impl& d) const
    {
      return Impl::difference(d) < 0;
    }

    bool operator>(const iterator_adaptor_impl& d) const
    {
      return Impl::difference(d) > 0;
    }

    bool operator<=(const iterator_adaptor_impl& d) const
    {
      return Impl::difference(d) <= 0;
    }

    bool operator>=(const iterator_adaptor_impl& d) const
    {
      return Impl::difference(d) >= 0;
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

  }; // iterator_adaptor_impl


  /// A simple sequence of data, defined by a pair of iterators
  template<typename BIter, typename EIter>
  struct sequence {

    using iterator = std::common_type_t<BIter, EIter>;

    sequence(BIter f, EIter l)
      : first {f},
        last {l}
    {}

    BIter begin() {
      return first;
    }

    EIter end() {
      return last;
    }

    BIter first;
    EIter last;
  };

  ///
  /// Zero overhead wrapper to create iterators
  ///
  /// \tparam Impl must define the following member functions:
  /// ```
  /// void advance(difference_type);
  /// reference dereference();
  /// bool equal(const Impl&);
  /// ```
  /// For random access iterators, it must also define
  /// ```
  /// std::ptrdiff_t difference(const Impl&);
  /// ```
  /// Other than those, it must define a copy constructor, and the member
  /// types `iterator_category` and `value_type`, Any other of the five
  /// `iterator_traits` types will also be used from `Impl` if avaliable
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
  /// rate ratio. In the OTTO it is used to read sound samples at a
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
  /// It has the same iterator category as the wrapped iteratory, except for
  /// random access iterators, which will be wrapped as bidirectional iterators.
  /// This is because a lot of the random access optimizations dont really apply
  /// to this.
  ///
  /// \tparam I Any iterator that will be wrapped.
  /// \tparam V The value type.
  template<typename I, typename V = typename detail::value_type<I>::type>
  class float_step_iterator {
  public:
    /*
     * Member types
     */

    using wrapped_type = I;

    // for `std::iterator_traits`
    using value_type = V;
    using reference = typename std::iterator_traits<wrapped_type>::reference;
    using pointer = typename std::iterator_traits<wrapped_type>::pointer;
    using difference_type = typename std::iterator_traits<wrapped_type>::difference_type;
    using iterator_category = std::common_type_t<
      typename detail::iterator_category<I>::type, std::bidirectional_iterator_tag>;

    /*
     * Initialization
     */

    /// Construct an iterator, pointing to `ptr`
    float_step_iterator(const wrapped_type& iter, float step = 1.f)
      : step {step}, iter {iter}
    {}

    /// Copy constructor
    float_step_iterator(const float_step_iterator& r)
      : step {r.step},
        _error {r._error},
        iter {r.iter}
    {}

    /// Move constructor
    float_step_iterator(float_step_iterator&& r)
      : step {std::move(r.step)},
        _error {std::move(r._error)},
        iter {std::move(r.iter)}
    {}

    // Default assignment operator
    float_step_iterator& operator=(const float_step_iterator&) = default;
    float_step_iterator& operator=(float_step_iterator&&) = default;

    /* Iterator operators */

    /// Dereference the iterator
    ///
    /// Propagates to the dereference operator of <ptr>
    decltype(auto) operator*() {return *iter;}
    decltype(auto) operator*() const {return *iter;}

    /// Compare equal
    ///
    /// Requires members <ptr> and <_error> to be equal.
    /// Ignores <step>, as it has no effect on the dereferenced value.
    bool operator==(const float_step_iterator& r) const
    {
      return iter == r.iter && _error == r._error;
    }

    /// Compare inequal
    ///
    /// Implemented as if by `!(*this == r)`
    bool operator!=(const float_step_iterator& r) const
    {
      return !(*this == r);
    }

    /// Compare less than
    ///
    /// Only avaliable if `wrapped_type` is less than comparable to itself.
    /// If the two wrapped instances are equal, the error values are compared.
    auto operator <(const float_step_iterator& r) const
      -> decltype(std::declval<wrapped_type>() < std::declval<wrapped_type>())
    {
      return iter < r.iter || (iter == r.iter && _error < r._error);
    }

    /// Compare greater than
    ///
    /// Only avaliable if `wrapped_type` is greater than comparable to itself.
    /// If the two wrapped instances are equal, the error values are compared.
    auto operator >(const float_step_iterator& r) const
      -> decltype(std::declval<wrapped_type>() > std::declval<wrapped_type>())
    {
      return iter > r.iter || (iter == r.iter && _error > r._error);
    }

    /// Compare less than or equal to
    ///
    /// Only avaliable if `wrapped_type` is less than comparable to itself.
    /// If the two wrapped instances are equal, the error values are compared.
    auto operator<=(const float_step_iterator& r) const
      -> decltype(std::declval<wrapped_type>() < std::declval<wrapped_type>())
    {
      return iter < r.iter || (iter == r.iter && _error <= r._error);
    }

    /// Compare greater than or equal to
    ///
    /// Only avaliable if `wrapped_type` is greater than comparable to itself.
    /// If the two wrapped instances are equal, the error values are compared.
    auto operator>=(const float_step_iterator& r) const
      -> decltype(std::declval<wrapped_type>() > std::declval<wrapped_type>())
    {
      return iter > r.iter || (iter == r.iter && _error >= r._error);
    }

    /// Get the number of iterations to get from `rhs` to this
    ///
    /// Takes the error values into account.
    std::ptrdiff_t operator-(const float_step_iterator& rhs) const
    {
      return (float(iter - rhs.iter) + (_error - rhs._error)) / step;
    }

    /// Increment this by `n`
    ///
    /// \effects Advance the iterator by `floor(error + n * speed)`, and store
    /// the remainder in `error`.
    ///
    /// \returns A reference to this
    float_step_iterator& operator+=(int n)
    {
      float intPart;
      _error = std::modf(_error + step * n, &intPart);
      if (_error < 0) {
        intPart -= 1;
        _error += 1;
      }
      std::advance(iter, intPart);
      return *this;
    }

    /// Increment this by one
    ///
    /// \effects Same as `*this += 1`
    /// \returns A reference to this
    float_step_iterator& operator++()
    {
      *this += 1;
      return *this;
    }

    /// Increment this by one
    ///
    /// \effects Same as `*this += 1`
    /// \returns A copy of this pre increment
    float_step_iterator operator++(int)
    {
      auto tmp = *this;
      operator++();
      return tmp;
    }

    /// Decrement this by `n`
    ///
    /// \effects Same as `*this += -n`
    /// \returns A reference to this
    /// \requires `wrapped_type` shall be at least a Bidirectional Iterator, or
    /// this function will not exist.
    auto operator-=(int n) -> std::enable_if_t<
      std::is_base_of_v<std::bidirectional_iterator_tag, iterator_category>,
      float_step_iterator&>
    {
      return *this += -n;
    }

    /// Decrement this by one
    ///
    /// \effects Same as `*this += -1`
    /// \returns A reference to this
    /// \requires `wrapped_type` shall be at least a Bidirectional Iterator, or
    /// this function will not exist.
    auto operator--() -> std::enable_if_t<
      std::is_base_of_v<std::bidirectional_iterator_tag, iterator_category>,
        float_step_iterator&>
    {
      return *this += -1;
    }

    /// Decrement this by one
    ///
    /// \effects Same as `*this += -1`
    /// \returns A copy of this pre increment
    /// \requires `wrapped_type` shall be at least a Bidirectional Iterator, or
    /// this function will not exist.
    auto operator--(int) -> std::enable_if_t<
        std::is_base_of_v<std::bidirectional_iterator_tag, iterator_category>,
        float_step_iterator&>
    {
      auto tmp = *this;
      *this += -1;
      return tmp;
    }

    /* Member functions */

    /// Get a copy of the underlying pointer.
    wrapped_type data() const
    {
      return iter;
    }

    /// The inaccuracy of the element this iterator points to.
    ///
    /// While <step> is an integer, this value will be constant.
    /// Otherwise it is in the range `[0, 1)`, signifying the
    /// fractional part of the real index. I.e.
    /// `ptr + error() == real_index`.
    float error() const
    {
      return _error;
    }

    /// The real numeric difference between this and `rhs`.
    ///
    /// Only avaliable if `wrapped_type` is random access.
    auto difference(const float_step_iterator& rhs) ->
    std::enable_if_t<std::is_same_v<
                       typename std::iterator_traits<
                         wrapped_type>::iterator_category,
                       std::random_access_iterator_tag>,
      float>
    {
      return (iter - rhs.iter) + (error() - rhs.error());
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
    wrapped_type iter;
  };

  template<typename Iterator>
  float_step_iterator(const Iterator& iter, float step) -> float_step_iterator<Iterator>;

  /// Create a float_step_iterator
  template<typename I, typename V =
    typename detail::value_type<std::decay_t<I>>::type>
  auto float_step(I&& iter, float step = 1)
  {
    return float_step_iterator<std::decay_t<I>,
      V>{std::forward<I>(iter), step};
  }

  ///
  /// Generating iterator
  ///
  template<typename Generator>
  class GeneratingIterImpl {
  public:
    using value_type = util::invoke_result_t<Generator>;
    using iterator_category = std::input_iterator_tag;

    GeneratingIterImpl(Generator generator)
      : generator {generator}
    {}

    void advance(int n)
    {
      for (int i = 0; i < n; i++) {
        val = std::invoke(generator);
      }
    }

    value_type& dereference()
    {
      return val;
    }

    bool equal(const GeneratingIterImpl& o) const
    {
      return o.val == val;
    }

    value_type val;
    Generator generator;
  };


  ///
  /// Generating iterator
  ///
  /// Supplied with a generator function, this iterator will generate a value
  /// each time its called.
  /// 
  template<typename Generator>
  using generating_iterator = iterator_adaptor<GeneratingIterImpl<Generator>>;

  ///
  /// Create a generating iterator
  /// 
  template<typename Generator>
  generating_iterator<Generator> generator(Generator&& gen) {
    return generating_iterator<Generator>(std::forward<Generator>(gen));
  }


  ///
  /// Zipped iterator
  ///
  template<typename... Iterators>
  class ZippedIteratorImpl {

    template<std::size_t N, typename Tuple>
    static bool tuple_equals_impl(const Tuple& t1, const Tuple& t2)
    {
      if constexpr (N < std::tuple_size_v<Tuple>) {
        auto res = std::get<N>(t1) == std::get<N>(t2);
        if (res) return true;
        return tuple_equals_impl<N + 1>(t1, t2);
      }
      return false;
    }

    template<std::size_t N, typename Tuple>
    static void tuple_advnc_impl(Tuple& t, int n)
    {
      if constexpr (N < std::tuple_size_v<Tuple>) {
        std::advance(std::get<N>(t), n);
        tuple_advnc_impl<N + 1>(t, n);
      }
    }

    template<std::size_t N, typename Tuple, typename Tuple2 = std::tuple<>>
    static auto tuple_deref_impl(const Tuple& iters, Tuple2&& t2 = {})
    {
      if constexpr (N < std::tuple_size_v<Tuple>) {
        return tuple_deref_impl<N + 1>(iters,
          std::tuple_cat(std::move(t2),
            std::tuple<std::tuple_element_t<N, reference>>(*(std::get<N>(iters)))));
      } else {
        return t2;
      }
    }

  public:
    using value_type = std::tuple<
      typename detail::value_type<Iterators>::type...>;
    using reference = std::tuple<
      typename detail::reference<Iterators>::type...>;
    using iterator_category = std::common_type_t<
      typename detail::iterator_category<Iterators>::type...>;

    ZippedIteratorImpl(Iterators... iterators)
      : iterators {iterators...}
    {}

    ZippedIteratorImpl(std::tuple<Iterators...> iterators)
      : iterators {iterators}
    {}

    void advance(int n)
    {
      tuple_advnc_impl<0>(iterators, n);
    }

    reference dereference()
    {
      return tuple_deref_impl<0>(iterators);
    }

    reference dereference() const
    {
      return tuple_deref_impl<0>(iterators);
    }

    bool equal(const ZippedIteratorImpl& o) const
    {
      return tuple_equals_impl<0>(iterators, o.iterators);
    }

    std::tuple<Iterators...> iterators;
  };


  ///
  /// Zipped iterator
  ///
  /// Iterates over multiple iterators at the same time
  ///
  /// Its very useful with structured bindings and `for` loops. Using the helper
  /// function [otto::util::zip], you can iterate over multiple ranges like
  /// this:
  /// ```
  /// for (auto&& [r1, r2] : util::zip(range1, range2)) {
  ///   ...
  /// }
  /// ```

  template<typename... Iterators>
  using zipped_iterator = iterator_adaptor<ZippedIteratorImpl<Iterators...>>;

  /// Create a zipped iterator from iterators
  template<typename... Iterators>
  zipped_iterator<Iterators...> zip_iters(Iterators... iters) {
    return zipped_iterator<Iterators...>(iters...);
  }

  template<typename... Ranges>
  struct ZippedRange {

    ZippedRange(Ranges&&... ranges)
      : first  {std::begin(ranges)...},
        last  {std::end(ranges)...}
    {}

    auto begin() { return first; }

    auto begin() const { return first; }

    auto end() { return last; }

    auto end() const { return last; }

    zipped_iterator<std::decay_t<
                      decltype(std::begin(std::declval<Ranges>()))>...> first;

    zipped_iterator<std::decay_t<
                      decltype(std::end(std::declval<Ranges>()))>...> last;
  };

  /// Create a zipped range from ranges
  template<typename... Ranges>
  auto zip(Ranges&&... ranges) {
    return ZippedRange<Ranges...>(std::forward<Ranges>(ranges)...);
  }


  /****************************************************************************/
  /* ADJACENT PAIR ITERATORS                                                  */
  /****************************************************************************/

  namespace detail {

    template<typename Iter>
    struct AdjacentIterImpl {
      using iter_value_type = typename detail::value_type<Iter>::type;
      using value_type = std::pair<iter_value_type, iter_value_type>;
      using iter_reference = typename detail::reference<Iter>::type;
      using reference = std::pair<iter_reference, iter_reference>;
      using iterator_category = typename detail::iterator_category<Iter>::type;

      AdjacentIterImpl(Iter iter)
        : prev {iter},
          cur {std::next(iter)}
      {}

      void advance(int n)
      {
        std::advance(cur, n);
        std::advance(prev, n);
      }

      reference dereference()
      {
        return {*prev, *cur};
      }

      bool equal(const AdjacentIterImpl& o) const
      {
        return cur == o.cur;
      }

      Iter prev;
      Iter cur;
    };

  }

  template<typename Iter>
  using adjacent_pair_iterator = iterator_adaptor<detail::AdjacentIterImpl<Iter>>;

  template<typename Range>
  struct AdjacentRange {

    using iterator = adjacent_pair_iterator<typename std::decay_t<Range>::iterator>;

    AdjacentRange(Range& range)
      : first  {std::begin(range)},
        last  {std::end(range)}
    {
      if (first != last) {
        // No pair starting with last element
        last--;
      }
    }

    AdjacentRange(Range&& range)
      : first  {std::begin(range)},
        last  {std::end(range)}
    {
      if (first != last) {
        // No pair starting with last element
        last--;
      }
    }


    auto begin() {
      return first;
    }

    auto end() {
      return last;
    }

    iterator first;
    iterator last;

  };

  template<typename Range>
  auto adjacent_pairs(Range& rng) {
    return AdjacentRange{rng};
  }

  template<typename BIter, typename EIter>
  auto adjacent_pairs(BIter f, EIter l) {
    return AdjacentRange{util::sequence(f, l)};
  }

  ///
  /// Transform iterator
  ///
  template<typename WrappedIter, typename Callable>
  class TransformIteratorImpl{
  public:
    using reference = util::invoke_result_t<Callable, typename detail::reference<WrappedIter>::type>;
    using value_type = typename std::decay_t<reference>;
    using iterator_category = detail::iterator_category<WrappedIter>;

    TransformIteratorImpl(WrappedIter iter, Callable callable)
      : iter (std::move(iter)), callable {std::make_shared<Callable>(std::move(callable))}
    {}

    TransformIteratorImpl(WrappedIter iter, TransformIteratorImpl other)
      : iter (std::move(iter)), callable {other.callable}
    {}

    void advance(int n)
    {
      std::advance(iter, 1);
    }

    reference dereference()
    {
      return std::invoke(*callable, *iter);
    }

    bool equal(const TransformIteratorImpl& o) const
    {
      return iter == o.iter;
    }

    auto difference(const TransformIteratorImpl& o) const
    {
      return iter - o.iter;
    }

    WrappedIter iter;
    std::shared_ptr<Callable> callable;
  };

  ///
  /// Transforming Iterator
  ///
  template<typename WrappedIter, typename Callable>
  using transform_iterator = iterator_adaptor<TransformIteratorImpl<WrappedIter, Callable>>;

  namespace view {

    template<typename Range, typename Callable>
    auto transform(Range&& r, Callable&& c) {
      using std::begin, std::end;
      using transformiter = transform_iterator<decltype(begin(r)), std::decay_t<Callable>>;
      auto first = transformiter(begin(r), std::forward<Callable>(c));
      auto last = transformiter(end(r), first);
      return sequence(first, last);
    }
  }

  ///
  /// Filter iterator
  ///
  template<typename WrappedIter, typename Predicate>
  class FilterIterImpl{
  public:

    using value_type = typename detail::value_type<WrappedIter>::type;
    using reference = typename detail::reference<WrappedIter>::type;
    using iterator_category = typename detail::iterator_category<WrappedIter>::type;

    static_assert(std::is_same_v<std::decay_t<decltype(*std::declval<WrappedIter>())>, value_type>);

    FilterIterImpl(WrappedIter iter, WrappedIter last, Predicate callable)
      : iter (std::move(iter)), last(last), callable {std::make_shared<Predicate>(std::move(callable))}
    {
      nextvalid();
    }

    FilterIterImpl(WrappedIter iter, WrappedIter last, FilterIterImpl other)
      : iter (std::move(iter)), last(last), callable {other.callable}
    {
      nextvalid();
    }

    void nextvalid() {
      while(iter != last && !std::invoke(*callable, *iter)){
	++iter;
      }
    }

    void advance(int n)
    {
      for (int i = 0; i < n; i++) {
        while (++iter != last && !std::invoke(*callable, *iter) );
      }
    }

    reference dereference()
    {
      return *iter;
    }

    bool equal(const FilterIterImpl& o) const
    {
      return iter == o.iter;
    }

    auto difference(const FilterIterImpl& o) const
    {
      return iter - o.iter;
    }

    WrappedIter iter;
    WrappedIter last;
    std::shared_ptr<Predicate> callable;
  };

  ///
  /// Filter Iterator
  ///
  template<typename WrappedIter, typename Predicate>
  using filter_iterator = iterator_adaptor<FilterIterImpl<WrappedIter, Predicate>>;

  namespace view {

    template<typename Range, typename Predicate>
    auto filter(Range&& r, Predicate&& c) {
      using std::begin, std::end;
      using filteriter = filter_iterator<decltype(begin(r)), std::decay_t<Predicate>>;
      auto first = filteriter(begin(r), end(r), std::forward<Predicate>(c));
      auto last = filteriter(end(r), end(r), first);
      return sequence(first, last);
    }
  }

}
