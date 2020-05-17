#pragma once

#include <cmath>
#include <functional>
#include <iterator>
#include <memory>
#include <nanorange.hpp>
#include <tl/optional.hpp>
#include <tuple>
#include <type_traits>

#include "type_traits.hpp"
#include "utility.hpp"

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
    namespace iter_detail {

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
    } // namespace iter_detail

    ///
    /// Zero overhead wrapper to create iterators
    ///
    /// \tparam Impl must define the following member functions:
    /// ```cpp
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
             typename Pointer = std::decay_t<Reference>*,
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

      pointer operator->()
      {
        return &derived().dereference();
      }

      pointer operator->() const
      {
        return &derived().dereference();
      }

      // Comparison (Any)
      friend bool operator==(const Derived& l, const Derived& r)
      {
        return l.equal(r);
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

    /// A sequence where begin and end iterators are created for each call to begin and end functions
    template<typename BIterFactory, typename EIterFactory>
    struct lazy_sequence : nano::view_interface<lazy_sequence<BIterFactory, EIterFactory>> {
      using iterator = std::invoke_result_t<BIterFactory>;
      using sentinel = std::invoke_result_t<BIterFactory>;

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
    template<typename I, typename V = typename iter_detail::value_type<I>::type>
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
        std::common_type_t<typename iter_detail::iterator_category<I>::type, std::bidirectional_iterator_tag>;

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
    float_step_iterator(const Iterator& iter, float step) -> float_step_iterator<Iterator>;

    /// Create a float_step_iterator
    template<typename I, typename V = typename iter_detail::value_type<std::decay_t<I>>::type>
    auto float_step(I&& iter, float step = 1)
    {
      return float_step_iterator<std::decay_t<I>, V>{std::forward<I>(iter), step};
    }

    /// Generating iterator

    namespace iter_detail {} // namespace iter_detail

    ///
    /// Generating iterator
    ///
    /// Supplied with a generator function, this iterator will generate a value
    /// each time its called.
    ///
    template<typename Generator>
    struct generating_iterator
      : iterator_facade<generating_iterator<Generator>, std::invoke_result_t<Generator>, std::input_iterator_tag> {
      using value_type = typename std::invoke_result_t<Generator>::value_type;
      using iterator_category = std::input_iterator_tag;

      static_assert(nano::assignable_from<Generator&, Generator>);

      generating_iterator() {}
      generating_iterator(Generator generator) : generator{std::move(generator)} {}
      generating_iterator(generating_iterator&&) = default;

      void advance(int n)
      {
        for (int i = 0; i < n; i++) {
          val = std::invoke(*generator);
        }
      }

      value_type dereference()
      {
        return *val;
      }

      bool equal(const generating_iterator& o) const
      {
        return o.val == val;
      }

      bool operator==(nano::default_sentinel_t)
      {
        return !val.has_value();
      }

      bool operator!=(nano::default_sentinel_t)
      {
        return val.has_value();
      }

    private:
      tl::optional<value_type> val = tl::nullopt;
      tl::optional<Generator> generator = tl::nullopt;
    };


    /// Create a Generating range
    ///
    /// @param Generator Must have type: `tl::optional<T>()`. Returning `tl::nullopt` means
    /// the end has been reached
    template<typename Generator>
    auto generator(Generator&& gen)
    {
      return nano::subrange(generating_iterator<Generator>(std::forward<Generator>(gen)), nano::default_sentinel);
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
    struct zipped_iterator
      : iterator_facade<zipped_iterator<Iterators...>,
                        std::tuple<iter_detail::value_type_t<Iterators>...>,
                        std::common_type_t<typename iter_detail::iterator_category<Iterators>::type...>,
                        std::tuple<iter_detail::reference_t<Iterators>...>> {
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
          // NRVO does not apply since its received as an rvalue refference
          return std::move(t2);
        }
      }

    public:
      using value_type = std::tuple<iter_detail::value_type_t<Iterators>...>;
      using reference = std::tuple<iter_detail::reference_t<Iterators>...>;
      using iterator_category = std::common_type_t<iter_detail::iterator_category_t<Iterators>...>;

      zipped_iterator() = default;

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
      ZippedRange(Ranges&&... ranges) : first{nano::begin(ranges)...}, last{nano::end(ranges)...} {}

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

      zipped_iterator<std::decay_t<decltype(nano::begin(std::declval<Ranges>()))>...> first;

      zipped_iterator<std::decay_t<decltype(nano::end(std::declval<Ranges>()))>...> last;
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
    struct adjacent_pair_iterator
      : iterator_facade<adjacent_pair_iterator<Iter>,
                        std::pair<iter_detail::value_type_t<Iter>, iter_detail::value_type_t<Iter>>,
                        iter_detail::iterator_category_t<Iter>,
                        std::pair<iter_detail::reference_t<Iter>, iter_detail::reference_t<Iter>>> {
      using value_type = std::pair<iter_detail::value_type_t<Iter>, iter_detail::value_type_t<Iter>>;
      using reference = std::pair<iter_detail::reference_t<Iter>, iter_detail::reference_t<Iter>>;
      using iterator_category = typename iter_detail::iterator_category<Iter>::type;

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
      return AdjacentRange{nano::subrange(f, l)};
    }

    ///
    /// Circular Iterator
    ///
    template<typename WrappedIter>
    struct circular_iterator : iterator_facade<circular_iterator<WrappedIter>,
                                               iter_detail::value_type_t<WrappedIter>,
                                               iter_detail::iterator_category_t<WrappedIter>,
                                               iter_detail::reference_t<WrappedIter>> {
      static_assert(
        std::is_same_v<std::decay_t<decltype(*std::declval<WrappedIter>())>, iter_detail::value_type_t<WrappedIter>>);

      // Iterator requires weakly_incrementable, which requires default constructible
      circular_iterator() = default;

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

    template<typename WrappedIter>
    struct indexed_iterator;

    namespace iter_detail {

      template<typename Ref>
      struct with_index {
        int index;
        Ref val;
      };

      template<typename WrappedIter>
      using indexed_super = iterator_facade<indexed_iterator<WrappedIter>,
                                            iter_detail::with_index<iter_detail::value_type_t<WrappedIter>>,
                                            std::common_type_t<iter_detail::iterator_category_t<WrappedIter>>,
                                            iter_detail::with_index<iter_detail::reference_t<WrappedIter>>>;
    } // namespace iter_detail


    template<typename WrappedIter>
    struct indexed_iterator : iter_detail::indexed_super<WrappedIter> {
      static_assert(
        std::is_same_v<std::decay_t<decltype(*std::declval<WrappedIter>())>, iter_detail::value_type_t<WrappedIter>>);

      using Super = iter_detail::indexed_super<WrappedIter>;
      using typename Super::difference_type;
      using typename Super::iterator_category;
      using typename Super::pointer;
      using typename Super::reference;
      using typename Super::value_type;

      indexed_iterator(WrappedIter iter = {}, int index = 0) : iter(std::move(iter)), index(index) {}

      void advance(int n)
      {
        std::advance(iter, n);
        index += n;
      }

      auto dereference()
      {
        return reference{index, *iter};
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
      int index = 0;
    };
  } // namespace iterator

  namespace view {

    template<typename Range>
    auto circular(Range&& r)
    {
      using std::begin, std::end;
      using CircIter = circular_iterator<decltype(begin(r))>;
      auto first = CircIter(begin(r), begin(r), end(r));
      auto last = CircIter(end(r), begin(r), end(r));
      return nano::subrange(first, last);
    }

    template<typename Range>
    auto indexed(Range&& r)
    {
      using std::begin, std::end;
      using Iter = indexed_iterator<decltype(begin(r))>;
      static_assert(nano::weakly_incrementable<Iter>);
      static_assert(nano::input_or_output_iterator<Iter>);
      static_assert(nano::sentinel_for<Iter, Iter>);
      auto first = Iter(begin(r));
      auto last = Iter(end(r));
      return nano::subrange(first, last);
    }

    template<typename Range>
    auto subrange(Range&& r, std::size_t begin_idx, std::size_t end_idx)
    {
      using std::begin, std::end;
      return nano::subrange(begin(r) + begin_idx, std::min(begin(r) + end_idx, end(r)));
    }

    template<typename Range>
    auto to_vec(Range&& r)
    {
      using std::begin, std::end;
      using Iter = std::decay_t<decltype(begin(r))>;
      std::vector<iterator::iter_detail::value_type_t<Iter>> res;
      for (auto&& e : r) {
        res.push_back(e);
      }
      return res;
    }

  } // namespace view

} // namespace otto::util
