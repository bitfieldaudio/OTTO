#pragma once

#include <cmath>
#include <functional>
#include <iterator>
#include <memory>
#include <tuple>
#include <type_traits>

#include "type_traits.hpp"

namespace otto::util {

  /// \namespace otto::util::iterator
  /// This namespace contains custom iterator types and general helper classes for working with
  /// containers
  ///
  /// \attention `otto::util::iterator` is an inline namespace, meaning all members can and should
  /// be accessed directly from the `otto::util` namespace i.e. as `util::float_step(...)`, not
  /// `util::iterator::float_step(...)`. It is only a separate namespace for clarification of
  /// documentation and name resolution.


  /// \namespace otto::util::iterator::view
  ///
  /// This namespace contains lazily evaluated "views" into containers.

  inline namespace iterator {
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

      template<typename Impl>
      using difference_type_t = typename difference_type<Impl>::type;

      // Value type

      template<typename Impl, typename T = void>
      struct value_type {
        using type = typename std::iterator_traits<Impl>::value_type;
      };

      template<typename Impl>
      struct value_type<Impl, std::void_t<typename Impl::value_type>> {
        using type = typename Impl::value_type;
      };

      template<typename Impl>
      using value_type_t = typename value_type<Impl>::type;

      // Pointer type

      template<typename Impl, typename T = void>
      struct pointer {
        using type = value_type_t<Impl>*;
      };

      template<typename Impl>
      struct pointer<Impl, std::void_t<typename Impl::pointer>> {
        using type = typename Impl::pointer;
      };

      template<typename Impl>
      using pointer_t = typename pointer<Impl>::type;

      // Reference type

      template<typename Impl, typename T = void>
      struct reference_impl {
        using type = value_type_t<Impl>&;
      };

      template<typename Impl>
      struct reference_impl<Impl, std::void_t<typename std::iterator_traits<Impl>::reference>> {
        using type = typename std::iterator_traits<Impl>::reference;
      };

      template<typename Impl, typename T = void>
      struct reference {
        using type = typename reference_impl<Impl>::type;
      };

      template<typename Impl>
      struct reference<Impl, std::void_t<typename Impl::reference>> {
        using type = typename Impl::reference;
      };

      template<typename Impl>
      using reference_t = typename reference<Impl>::type;

      // Iterator category

      template<typename Impl, typename T = void>
      struct iterator_category {
        using type = typename std::iterator_traits<Impl>::iterator_category;
      };

      template<typename Impl>
      struct iterator_category<Impl, std::void_t<typename Impl::iterator_category>> {
        using type = typename Impl::iterator_category;
      };

      template<typename Impl>
      using iterator_category_t = typename iterator_category<Impl>::type;
    } // namespace detail

    ///
    /// Zero overhead wrapper to create iterators
    ///
    /// \tparam Impl must define the following member functions:
    /// ```
    /// void           Impl::advance(difference_type);
    /// reference      Impl::dereference();
    /// bool           Impl::equal(const Impl&);
    /// ```
    /// For random access iterators, it must also define
    /// ```
    /// std::ptrdiff_t Impl::difference(const Impl&);
    /// ```
    /// Other than those, it must define a copy constructor, and the member
    /// types `iterator_category` and `value_type`, Any other of the five
    /// `iterator_traits` types will also be used from `Impl` if avaliable
    template<typename Derived,
             typename ValueType,
             typename Category,
             typename Reference = ValueType&,
             typename Pointer = ValueType*,
             typename Difference = std::ptrdiff_t>
    struct iterator_facade {
      // For std::iterator_traits
      using value_type = ValueType;
      using iterator_category = Category;
      using reference = Reference;
      using pointer = Pointer;
      using difference_type = Difference;

      /* Operators */

      // Increment (Any)

      Derived& operator++()
      {
        derived().advance(1);
        return derived();
      }

      Derived operator++(int)
      {
        auto old = derived();
        derived().advance(1);
        return old;
      }

      // Dereference (Any)
      decltype(auto) operator*()
      {
        return derived().dereference();
      }

      decltype(auto) operator*() const
      {
        return derived().dereference();
      }

      decltype(auto) operator-> ()
      {
        return derived().dereference();
      }

      decltype(auto) operator-> () const
      {
        return derived().dereference();
      }

      // Comparison (Any)
      bool operator==(const Derived& r) const
      {
        return derived().equal(r);
      }

      bool operator!=(const Derived& r) const
      {
        return !derived().equal(r);
      }

    private:
      Derived& derived()
      {
        return static_cast<Derived&>(*this);
      }

      const Derived& derived() const
      {
        return static_cast<const Derived&>(*this);
      }
    };

    template<typename Derived, typename ValueType, typename Reference, typename Pointer, typename Difference>
    struct iterator_facade<Derived, ValueType, std::bidirectional_iterator_tag, Reference, Pointer, Difference>
      : iterator_facade<Derived, ValueType, std::input_iterator_tag, Reference, Pointer, Difference> {
      using Super = iterator_facade<Derived, ValueType, std::input_iterator_tag, Reference, Pointer, Difference>;

      using typename Super::difference_type;
      using iterator_category = std::bidirectional_iterator_tag;
      using typename Super::pointer;
      using typename Super::reference;
      using typename Super::value_type;

      using Super::operator=;
      using Super::operator++;
      using Super::operator*;
      using Super::operator->;
      using Super::operator==;
      using Super::operator!=;

      // Decrement (Bidirectional)

      Derived& operator--()
      {
        derived().advance(-1);
        return derived();
      }

      Derived operator--(int)
      {
        auto old = derived();
        derived().advance(-1);
        return old;
      }

    private:
      Derived& derived()
      {
        return static_cast<Derived&>(*this);
      }

      const Derived& derived() const
      {
        return static_cast<const Derived&>(*this);
      }
    };

    template<typename Derived, typename Va, typename Re, typename Po, typename Di>
    struct iterator_facade<Derived, Va, std::random_access_iterator_tag, Re, Po, Di>
      : iterator_facade<Derived, Va, std::bidirectional_iterator_tag, Re, Po, Di> {
      using Super = iterator_facade<Derived, Va, std::bidirectional_iterator_tag, Re, Po, Di>;

      using typename Super::difference_type;
      using iterator_category = std::random_access_iterator_tag;
      using typename Super::pointer;
      using typename Super::reference;
      using typename Super::value_type;

      using Super::operator=;

      using Super::operator++;
      using Super::operator*;
      using Super::operator->;
      using Super::operator==;
      using Super::operator!=;

      using Super::operator--;

      // Arithmetics (Random access)

      Derived operator+(difference_type d) const
      {
        Derived res{derived()};
        res.derived().advance(d);
        return res;
      }

      Derived operator-(difference_type d) const
      {
        Derived res{derived()};
        res.derived().advance(-d);
        return res;
      }

      difference_type operator-(const Derived& d) const
      {
        return derived().difference(d);
      }

      // Inequality (Random access)

      bool operator<(const Derived& d) const
      {
        return derived().difference(d) < 0;
      }

      bool operator>(const Derived& d) const
      {
        return derived().difference(d) > 0;
      }

      bool operator<=(const Derived& d) const
      {
        return derived().difference(d) <= 0;
      }

      bool operator>=(const Derived& d) const
      {
        return derived().difference(d) >= 0;
      }

      // Compound assignment (Random access)

      Derived& operator+=(difference_type d)
      {
        derived().advance(d);
        return derived();
      }

      Derived& operator-=(difference_type d)
      {
        derived().advance(-d);
        return derived();
      }

      // Offset dereference (Random access)

      reference operator[](difference_type d)
      {
        return *(*this + d);
      }

    private:
      Derived& derived()
      {
        return static_cast<Derived&>(*this);
      }

      const Derived& derived() const
      {
        return static_cast<const Derived&>(*this);
      }

    }; // iterator_facade


    /// A simple sequence of data, defined by a pair of iterators.
    ///
    /// This simple class lets you use a pair of iterators where a container
    /// is expected.
    template<typename BIter, typename EIter>
    struct sequence {
      using iterator = std::common_type_t<BIter, EIter>;

      sequence(BIter f, EIter l) : first{f}, last{l} {}

      BIter begin()
      {
        return first;
      }

      EIter end()
      {
        return last;
      }

      auto rbegin()
      {
        return std::make_reverse_iterator(last);
      }

      auto rend()
      {
        return std::make_reverse_iterator(first);
      }

      auto&& front()
      {
        return *first;
      }

      BIter first;
      EIter last;
    };

    /// A sequence where begin and end iterators are created for each call to begin and end functions
    template<typename BIterFactory, typename EIterFactory>
    struct lazy_sequence {
      using iterator = std::common_type_t<std::invoke_result_t<BIterFactory>, std::invoke_result_t<BIterFactory>>;

      lazy_sequence(BIterFactory&& f, EIterFactory&& l) : first{std::move(f)}, last{std::move(l)} {}

      auto begin()
      {
        return first();
      }

      auto end()
      {
        return last();
      }

      auto rbegin()
      {
        return std::make_reverse_iterator(end());
      }

      auto rend()
      {
        return std::make_reverse_iterator(begin());
      }

      auto&& front()
      {
        return *begin();
      }

      BIterFactory first;
      EIterFactory last;
    };

    /// \class float_step_iterator
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
    /// `operator-`, they are guarantied to be reachable from the other
    /// using `operator++` or `operator--` as applicable, as long as the
    /// `step` member variable on the mutating iterator is unchanged.
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
      using iterator_category =
        std::common_type_t<typename detail::iterator_category<I>::type, std::bidirectional_iterator_tag>;

      /*
       * Initialization
       */

      /// Construct an iterator, pointing to `ptr`
      float_step_iterator(const wrapped_type& iter, float step = 1.f) : step{step}, iter{iter} {}

      /// Copy constructor
      float_step_iterator(const float_step_iterator& r) : step{r.step}, _error{r._error}, iter{r.iter} {}

      /// Move constructor
      float_step_iterator(float_step_iterator&& r)
        : step{std::move(r.step)}, _error{std::move(r._error)}, iter{std::move(r.iter)}
      {}

      // Default assignment operator
      float_step_iterator& operator=(const float_step_iterator&) = default;
      float_step_iterator& operator=(float_step_iterator&&) = default;

      /* Iterator operators */

      /// Dereference the iterator
      ///
      /// Propagates to the dereference operator of <ptr>
      decltype(auto) operator*()
      {
        return *iter;
      }
      decltype(auto) operator*() const
      {
        return *iter;
      }

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
      auto operator<(const float_step_iterator& r) const
        -> decltype(std::declval<wrapped_type>() < std::declval<wrapped_type>())
      {
        return iter < r.iter || (iter == r.iter && _error < r._error);
      }

      /// Compare greater than
      ///
      /// Only avaliable if `wrapped_type` is greater than comparable to itself.
      /// If the two wrapped instances are equal, the error values are compared.
      auto operator>(const float_step_iterator& r) const
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
      float_step_iterator& operator+=(difference_type n)
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

      float_step_iterator operator+(difference_type d)
      {
        auto res = *this;
        res += d;
        return res;
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
      auto operator-=(difference_type n)
        -> std::enable_if_t<std::is_base_of_v<std::bidirectional_iterator_tag, iterator_category>, float_step_iterator&>
      {
        return *this += -n;
      }

      auto operator-(difference_type d)
        -> std::enable_if_t<std::is_base_of_v<std::bidirectional_iterator_tag, iterator_category>, float_step_iterator>
      {
        auto res = *this;
        res -= d;
        return res;
      }


      /// Decrement this by one
      ///
      /// \effects Same as `*this += -1`
      /// \returns A reference to this
      /// \requires `wrapped_type` shall be at least a Bidirectional Iterator, or
      /// this function will not exist.
      auto operator--()
        -> std::enable_if_t<std::is_base_of_v<std::bidirectional_iterator_tag, iterator_category>, float_step_iterator&>
      {
        return *this += -1;
      }

      /// Decrement this by one
      ///
      /// \effects Same as `*this += -1`
      /// \returns A copy of this pre increment
      /// \requires `wrapped_type` shall be at least a Bidirectional Iterator, or
      /// this function will not exist.
      auto operator--(int)
        -> std::enable_if_t<std::is_base_of_v<std::bidirectional_iterator_tag, iterator_category>, float_step_iterator&>
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
      auto difference(const float_step_iterator& rhs) -> std::enable_if_t<
        std::is_same_v<typename std::iterator_traits<wrapped_type>::iterator_category, std::random_access_iterator_tag>,
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
    float_step_iterator(const Iterator& iter, float step)->float_step_iterator<Iterator>;

    /// Create a float_step_iterator
    template<typename I, typename V = typename detail::value_type<std::decay_t<I>>::type>
    auto float_step(I&& iter, float step = 1)
    {
      return float_step_iterator<std::decay_t<I>, V>{std::forward<I>(iter), step};
    }

    /// Generating iterator

    namespace detail {} // namespace detail


    ///
    /// Generating iterator
    ///
    /// Supplied with a generator function, this iterator will generate a value
    /// each time its called.
    ///
    template<typename Generator>
    struct generating_iterator
      : iterator_facade<generating_iterator<Generator>, util::invoke_result_t<Generator>, std::input_iterator_tag> {
      using value_type = util::invoke_result_t<Generator>;
      using iterator_category = std::input_iterator_tag;

      generating_iterator(Generator generator) : generator{std::move(generator)} {}

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

      bool equal(const generating_iterator& o) const
      {
        return o.val == val;
      }

    private:
      value_type val;
      Generator generator;
    };

    ///
    /// Create a generating iterator
    ///
    template<typename Generator>
    generating_iterator<Generator> generator(Generator&& gen)
    {
      return generating_iterator<Generator>(std::forward<Generator>(gen));
    }

    /// Zipped iterator
    ///
    /// Iterates over multiple iterators at the same time
    ///
    /// Its very useful with structured bindings and `for` loops. Using the helper
    /// function \ref zip(), you can iterate over multiple ranges like
    /// this:
    /// ```
    /// for (auto&& [r1, r2] : util::zip(range1, range2)) {
    ///   ...
    /// }
    /// ```
    template<typename... Iterators>
    struct zipped_iterator : iterator_facade<zipped_iterator<Iterators...>,
                                             std::tuple<detail::value_type_t<Iterators>...>,
                                             std::common_type_t<typename detail::iterator_category<Iterators>::type...>,
                                             std::tuple<detail::reference_t<Iterators>...>> {
    private:
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
          return tuple_deref_impl<N + 1>(
            iters,
            std::tuple_cat(std::move(t2), std::tuple<std::tuple_element_t<N, reference>>(*(std::get<N>(iters)))));
        } else {
          // NRVO does not apply since its recieved as an rvalue refference
          return std::move(t2);
        }
      }

    public:
      using value_type = std::tuple<detail::value_type_t<Iterators>...>;
      using reference = std::tuple<detail::reference_t<Iterators>...>;
      using iterator_category = std::common_type_t<detail::iterator_category_t<Iterators>...>;

      zipped_iterator(Iterators... iterators) : iterators{std::move(iterators)...} {}

      zipped_iterator(std::tuple<Iterators...> iterators) : iterators{iterators} {}

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

      bool equal(const zipped_iterator& o) const
      {
        return tuple_equals_impl<0>(iterators, o.iterators);
      }

      std::tuple<Iterators...> iterators;
    };

    /// Create a zipped iterator from iterators
    template<typename... Iterators>
    zipped_iterator<Iterators...> zip_iters(Iterators... iters)
    {
      return zipped_iterator<Iterators...>(iters...);
    }

    template<typename... Ranges>
    struct ZippedRange {
      ZippedRange(Ranges&&... ranges) : first{std::begin(ranges)...}, last{std::end(ranges)...} {}

      auto begin()
      {
        return first;
      }

      auto begin() const
      {
        return first;
      }

      auto end()
      {
        return last;
      }

      auto end() const
      {
        return last;
      }

      zipped_iterator<std::decay_t<decltype(std::begin(std::declval<Ranges>()))>...> first;

      zipped_iterator<std::decay_t<decltype(std::end(std::declval<Ranges>()))>...> last;
    };

    /// Create a ZippedRange from ranges
    ///
    /// Its very useful with structured bindings and `for` loops, letting you iterate
    /// over multiple containers at once:
    /// ```
    /// for (auto&& [r1, r2] : util::zip(range1, range2)) {
    ///   ...
    /// }
    /// ```
    template<typename... Ranges>
    auto zip(Ranges&&... ranges)
    {
      return ZippedRange<Ranges...>(std::forward<Ranges>(ranges)...);
    }


    /****************************************************************************/
    /* ADJACENT PAIR ITERATORS                                                  */
    /****************************************************************************/

    template<typename Iter>
    struct adjacent_pair_iterator : iterator_facade<adjacent_pair_iterator<Iter>,
                                                    std::pair<detail::value_type_t<Iter>, detail::value_type_t<Iter>>,
                                                    detail::iterator_category_t<Iter>,
                                                    std::pair<detail::reference_t<Iter>, detail::reference_t<Iter>>> {
      using value_type = std::pair<detail::value_type_t<Iter>, detail::value_type_t<Iter>>;
      using reference = std::pair<detail::reference_t<Iter>, detail::reference_t<Iter>>;
      using iterator_category = typename detail::iterator_category<Iter>::type;

      adjacent_pair_iterator(Iter iter) : prev{iter}, cur{std::next(iter)} {}

      void advance(int n)
      {
        std::advance(cur, n);
        std::advance(prev, n);
      }

      reference dereference()
      {
        return {*prev, *cur};
      }

      bool equal(const adjacent_pair_iterator& o) const
      {
        return cur == o.cur;
      }

      Iter prev;
      Iter cur;
    };

    template<typename Range>
    struct AdjacentRange {
      using iterator = adjacent_pair_iterator<typename std::decay_t<Range>::iterator>;

      AdjacentRange(Range& range) : first{std::begin(range)}, last{std::end(range)}
      {
        if (first != last) {
          // No pair starting with last element
          last--;
        }
      }

      AdjacentRange(Range&& range) : first{std::begin(range)}, last{std::end(range)}
      {
        if (first != last) {
          // No pair starting with last element
          last--;
        }
      }


      auto begin()
      {
        return first;
      }

      auto end()
      {
        return last;
      }

      iterator first;
      iterator last;
    };

    template<typename Range>
    auto adjacent_pairs(Range& rng)
    {
      return AdjacentRange{rng};
    }

    template<typename BIter, typename EIter>
    auto adjacent_pairs(BIter f, EIter l)
    {
      return AdjacentRange{util::sequence(f, l)};
    }

    ///
    /// Transform iterator
    ///
    template<typename WrappedIter, typename Callable>
    struct transform_iterator
      : iterator_facade<transform_iterator<WrappedIter, Callable>,
                        std::decay_t<util::invoke_result_t<Callable, detail::reference_t<WrappedIter>>>,
                        detail::iterator_category_t<WrappedIter>,
                        util::invoke_result_t<Callable, detail::reference_t<WrappedIter>>> {
      transform_iterator(WrappedIter iter, Callable callable)
        : iter(std::move(iter)), callable{std::make_shared<Callable>(std::move(callable))}
      {}

      transform_iterator(WrappedIter iter, transform_iterator other) : iter(std::move(iter)), callable{other.callable}
      {}

      void advance(int n)
      {
        std::advance(iter, 1);
      }

      decltype(auto) dereference()
      {
        return std::invoke(*callable, *iter);
      }

      bool equal(const transform_iterator& o) const
      {
        return iter == o.iter;
      }

      auto difference(const transform_iterator& o) const
      {
        return iter - o.iter;
      }

      WrappedIter iter;
      std::shared_ptr<Callable> callable;
    };

    ///
    /// Filter iterator
    ///
    template<typename WrappedIter, typename Predicate>
    struct filter_iterator : iterator_facade<filter_iterator<WrappedIter, Predicate>,
                                             detail::value_type_t<WrappedIter>,
                                             detail::iterator_category_t<WrappedIter>,
                                             detail::reference_t<WrappedIter>> {
      static_assert(
        std::is_same_v<std::decay_t<decltype(*std::declval<WrappedIter>())>, detail::value_type_t<WrappedIter>>);

      filter_iterator(WrappedIter iter, WrappedIter last, Predicate callable)
        : iter(std::move(iter)), last(last), callable{std::make_shared<Predicate>(std::move(callable))}
      {
        nextvalid();
      }

      filter_iterator(WrappedIter iter, WrappedIter last, std::shared_ptr<Predicate> callable)
        : iter(std::move(iter)), last(last), callable{std::move(callable)}
      {
        nextvalid();
      }

      filter_iterator(WrappedIter iter, WrappedIter last, filter_iterator other)
        : iter(std::move(iter)), last(last), callable{other.callable}
      {
        nextvalid();
      }

      void nextvalid()
      {
        while (iter != last && !std::invoke(*callable, *iter)) {
          ++iter;
        }
      }

      void advance(int n)
      {
        for (int i = 0; i < n; i++) {
          while (iter != last && !std::invoke(*callable, *++iter))
            ;
        }
      }

      decltype(auto) dereference()
      {
        return *iter;
      }

      bool equal(const filter_iterator& o) const
      {
        return iter == o.iter;
      }

      auto difference(const filter_iterator& o) const
      {
        return iter - o.iter;
      }

      WrappedIter iter;
      WrappedIter last;
      std::shared_ptr<Predicate> callable;
    };

    ///
    /// Circular Iterator
    ///
    template<typename WrappedIter>
    struct circular_iterator : iterator_facade<circular_iterator<WrappedIter>,
                                               detail::value_type_t<WrappedIter>,
                                               detail::iterator_category_t<WrappedIter>,
                                               detail::reference_t<WrappedIter>> {
      static_assert(
        std::is_same_v<std::decay_t<decltype(*std::declval<WrappedIter>())>, detail::value_type_t<WrappedIter>>);

      circular_iterator(WrappedIter iter, WrappedIter first, WrappedIter last)
        : iter(std::move(iter)), first(std::move(first)), last(std::move(last))
      {}

      void advance(int n)
      {
        for (int i = 0; i < std::abs(n); i++) {
          if (n > 0) {
            iter++;
            if (iter == last) iter = first;
          } else {
            if (iter == first) iter = last;
            iter--;
          }
        }
      }

      decltype(auto) dereference()
      {
        return *iter;
      }

      bool equal(const circular_iterator& o) const
      {
        return iter == o.iter;
      }

      auto difference(const circular_iterator& o) const
      {
        return iter - o.iter;
      }

      WrappedIter iter;
      WrappedIter first, last;
    };

    namespace detail {

      template<typename Ref>
      struct with_index {
        std::size_t index;
        Ref val;
      };
    } // namespace detail

    template<typename WrappedIter>
    struct indexed_iterator : iterator_facade<indexed_iterator<WrappedIter>,
                                              std::pair<std::size_t, detail::value_type_t<WrappedIter>>,
                                              detail::iterator_category_t<WrappedIter>,
                                              std::pair<std::size_t, detail::reference_t<WrappedIter>>> {
      static_assert(
        std::is_same_v<std::decay_t<decltype(*std::declval<WrappedIter>())>, detail::value_type_t<WrappedIter>>);

      indexed_iterator(WrappedIter iter, std::size_t index = 0) : iter(std::move(iter)), index(index) {}

      void advance(int n)
      {
        std::advance(iter, n);
        index += n;
      }

      auto dereference()
      {
        return std::pair<std::size_t, detail::reference_t<WrappedIter>>(index, *iter);
      }

      bool equal(const indexed_iterator& o) const
      {
        return iter == o.iter;
      }

      auto difference(const indexed_iterator& o) const
      {
        return iter - o.iter;
      }

      WrappedIter iter;
      std::size_t index = 0;
    };


    struct counting_iterator : iterator_facade<counting_iterator, int, std::output_iterator_tag, int> {
      using value_type = int;
      counting_iterator(int value = 0) : value_(value) {}

      int dereference() const noexcept
      {
        return value_;
      }

      void advance(int n) noexcept
      {
        value_ += n;
      }

      bool equal(const counting_iterator& o) const noexcept
      {
        return value_ == o.value_;
      }

      int difference(const counting_iterator& o) const noexcept
      {
        return value_ - o.value_;
      }

    private:
      int value_;
    };


  } // namespace iterator

  namespace view {

    template<typename Range>
    auto reverse(Range&& r)
    {
      using std::rbegin, std::rend;
      return sequence(rbegin(r), rend(r));
    }

    template<typename Range, typename Callable>
    auto transform(Range&& r, Callable&& c)
    {
      using std::begin, std::end;
      using transformiter = transform_iterator<decltype(begin(r)), std::decay_t<Callable>>;
      auto first = transformiter(begin(r), std::forward<Callable>(c));
      auto last = transformiter(end(r), first);
      return sequence(first, last);
    }

    template<typename Range, typename Predicate>
    auto filter(Range&& r, Predicate&& c)
    {
      using std::begin, std::end;
      using filteriter = filter_iterator<decltype(begin(r)), std::decay_t<Predicate>>;
      auto ptr = std::make_shared<Predicate>(std::forward<Predicate>(c));
      auto first = [&r, &c, ptr] { return filteriter(begin(r), end(r), ptr); };
      auto last = [&r, &c, ptr] { return filteriter(end(r), end(r), ptr); };
      return lazy_sequence(std::move(first), std::move(last));
    }

    template<typename Range>
    auto circular(Range&& r)
    {
      using std::begin, std::end;
      using CircIter = circular_iterator<decltype(begin(r))>;
      auto first = CircIter(begin(r), begin(r), end(r));
      auto last = CircIter(end(r), begin(r), end(r));
      return sequence(first, last);
    }

    template<typename Range>
    auto indexed(Range&& r)
    {
      using std::begin, std::end;
      using Iter = indexed_iterator<decltype(begin(r))>;
      auto first = Iter(begin(r));
      auto last = Iter(end(r));
      return sequence(first, last);
    }

    template<typename Range>
    auto subrange(Range&& r, std::size_t begin_idx, std::size_t end_idx)
    {
      using std::begin, std::end;
      return sequence(begin(r) + begin_idx, std::min(begin(r) + end_idx, end(r)));
    }

    /// A range of ints [lo;hi[
    inline auto ints(int lo, int hi)
    {
      return sequence(counting_iterator(lo), counting_iterator(hi));
    }

    template<typename Range>
    auto to_vec(Range&& r)
    {
      using std::begin, std::end;
      using Iter = std::decay_t<decltype(begin(r))>;
      std::vector<iterator::detail::value_type_t<Iter>> res;
      for (auto&& e : r) {
        res.push_back(e);
      }
      return res;
    }

  } // namespace view

} // namespace otto::util
