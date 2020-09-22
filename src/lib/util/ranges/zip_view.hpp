#pragma once

#include <boost/stl_interfaces/iterator_interface.hpp>
#include <boost/stl_interfaces/view_interface.hpp>
#include <ranges>

#include "lib/util/concepts.hpp"
#include "lib/util/utility.hpp"

#include "lib/util/ranges/all_view.hpp"

namespace otto::util {

  /// Tuple-like reference type for zip_view
  ///
  /// The concept @ref std::indirectly_writable requires a shallow-const reference type.
  /// This is an implementation of that.
  template<typename... Refs>
  struct zip_reference {
    zip_reference(std::tuple<Refs...> r) : refs_(std::move(r)) {}
    template<typename... Others>
    requires(std::is_convertible_v<Others&, Refs>&&...) //
      zip_reference(std::tuple<Others...>& r)
      : refs_(r)
    {}
    template<typename... Others>
    requires(std::is_convertible_v<const Others&, Refs>&&...) //
      zip_reference(const std::tuple<Others...>& r)
      : refs_(r)
    {}
    template<typename... Others>
    requires(std::is_convertible_v<Others&, Refs>&&...) //
      zip_reference(zip_reference<Others...>& r)
      : refs_(r)
    {}
    template<typename... Others>
    requires(std::is_convertible_v<const Others&, Refs>&&...) //
      zip_reference(const zip_reference<Others...>& r)
      : refs_(r)
    {}

    auto operator=(const zip_reference& r) const
    {
      refs_ = r.refs_;
    }

    template<typename... Others>
    requires(std::assignable_from<std::tuple<Refs...>&, const std::tuple<Others...>&>) //
      auto
      operator=(const std::tuple<Others...>& r) const
    {
      refs_ = r;
    }

    template<typename... Others>
    requires(std::assignable_from<Refs, Others>&&...) //
      auto
      operator=(const zip_reference<Others...>& r) const
    {
      for_each(zip(refs_, r.refs_), [](auto&& pair) { pair.first = pair.second; });
    }

    operator std::tuple<Refs...>() const noexcept
    {
      return refs_;
    }

    template<typename... Others>
    requires(std::is_convertible_v<Refs, Others>&&...) //
    operator std::tuple<Others...>() const noexcept
    {
      return refs_;
    }

    template<std::size_t I>
    requires(I < sizeof...(Refs)) //
      decltype(auto) get() const noexcept
    {
      return std::get<I>(refs_);
    }

  private:
    template<typename...>
    friend struct zip_reference;
    mutable std::tuple<Refs...> refs_;
  };

  static_assert(std::is_assignable_v<zip_reference<int&, float&>, zip_reference<const int&, const float&>>);
  static_assert(std::is_convertible_v<std::tuple<int, float>&, zip_reference<int&, float&>>);
  static_assert(std::is_convertible_v<const std::tuple<int, float>&, zip_reference<const int&, const float&>>);

} // namespace otto::util

namespace std {
  template<typename... Refs>
  struct tuple_size<otto::util::zip_reference<Refs...>> : std::integral_constant<std::size_t, sizeof...(Refs)> {};

  template<std::size_t I, typename... Refs>
  struct tuple_element<I, otto::util::zip_reference<Refs...>> : std::tuple_element<I, std::tuple<Refs...>> {};

  template<typename... Args1, typename... Args2, template<typename> typename T1Q, template<typename> typename T2Q>
  requires(std::common_reference_with<T1Q<Args1>, T2Q<Args2>>&&...) struct basic_common_reference<
    otto::util::zip_reference<Args1...>,
    std::tuple<Args2...>,
    T1Q,
    T2Q> {
    using type = otto::util::zip_reference<std::common_reference_t<T1Q<Args1>, T2Q<Args2>>...>;
  };

  template<typename... Args1, typename... Args2, template<typename> typename T1Q, template<typename> typename T2Q>
  requires(std::common_reference_with<T1Q<Args1>, T2Q<Args2>>&&...) struct basic_common_reference<
    std::tuple<Args1...>,
    otto::util::zip_reference<Args2...>,
    T1Q,
    T2Q> {
    using type = otto::util::zip_reference<std::common_reference_t<T1Q<Args1>, T2Q<Args2>>...>;
  };
} // namespace std

namespace otto::util {

  /// Sentinel for zip_view
  template<std::input_iterator... Iters>
  requires(sizeof...(Iters) > 0) struct zip_sentinel {
    constexpr zip_sentinel() : iters() {}
    constexpr zip_sentinel(Iters... iters) : iters(std::move(iters)...) {}
    std::tuple<Iters...> iters;
  };

  /// Iterator for zip_view
  template<std::input_iterator... Iters>
  requires(sizeof...(Iters) > 0) //
    struct zip_iterator : boost::stl_interfaces::proxy_iterator_interface<
                            zip_iterator<Iters...>,
                            std::common_type_t<typename std::iterator_traits<Iters>::iterator_category...>,
                            std::tuple<std::iter_value_t<Iters>...>,
                            zip_reference<std::iter_reference_t<Iters>...>> //
  {
    using value_type = std::tuple<std::iter_value_t<Iters>...>;
    using reference = zip_reference<std::iter_reference_t<Iters>...>;

    constexpr zip_iterator() : iters_() {}
    constexpr zip_iterator(Iters... iters) : iters_(std::move(iters)...) {}

    constexpr reference operator*() const noexcept
    {
      return transform(iters_, [](auto&& iter) -> decltype(auto) { return *iter; });
    }

    constexpr zip_iterator& operator+=(std::ptrdiff_t i) noexcept
    {
      for_each(iters_, [i](auto& iter) { iter += i; });
      return *this;
    }

    constexpr auto operator-(const zip_iterator& other) const noexcept
    {
      return std::get<0>(iters_) - std::get<0>(other.iters_);
    }

    constexpr bool operator==(const zip_iterator& other) const
    {
      bool res = true;
      for_each(util::zip(iters_, other.iters_), [&](auto&& pair) {
        if (pair.first != pair.second) res = false;
      });
      return res;
    }

    constexpr bool operator==(const zip_sentinel<Iters...>& sentinel) const
    {
      bool res = false;
      for_each(util::zip(iters_, sentinel.iters), [&](auto&& pair) {
        if (pair.first == pair.second) res = true;
      });
      return res;
    }

  private:
    std::tuple<Iters...> iters_;
  };

  static_assert(std::indirectly_readable<zip_iterator<int*>>);
  static_assert(std::random_access_iterator<zip_iterator<int*, float*>>);
  static_assert(std::indirectly_writable<zip_iterator<int*>, std::tuple<int>>);

  template<std::ranges::view... Ranges>
  struct zip_view : boost::stl_interfaces::view_interface<zip_view<Ranges...>> {
    using base_type = std::tuple<Ranges...>;

    constexpr zip_view() = default;
    constexpr zip_view(Ranges... rngs) : base_(std::move(rngs)...) {}

    base_type base() const
    {
      return base_;
    }

    constexpr auto begin()
    {
      return std::apply([](auto&... views) { return zip_iterator(views.begin()...); }, base_);
    }

    constexpr auto end()
    {
      return std::apply([](auto&... views) { return zip_sentinel(views.end()...); }, base_);
    }

    constexpr auto begin() const
    {
      return std::apply([](auto&... views) { return zip_iterator(views.begin()...); }, base_);
    }

    constexpr auto end() const
    {
      return std::apply([](auto&... views) { return zip_sentinel(views.end()...); }, base_);
    }

  private:
    base_type base_;
  };

  template<std::ranges::view... Ranges>
  zip_view(Ranges...) -> zip_view<Ranges...>;

  template<std::ranges::viewable_range... Ranges>
  auto zip(Ranges&&... rngs)
  {
    return zip_view(all(FWD(rngs))...);
  }
} // namespace otto::util

namespace std {
  // Required for std::sort to work with zip_iterator.  Without this
  // overload, std::sort eventually tries to call std::swap(*it1, *it2),
  // *it1 and *it2 are rvalues, and std::swap() takes mutable lvalue
  // references.  That makes std::swap(*it1, *it2) ill-formed.
  //
  // Note that this overload does not conflict with any other swap()
  // overloads, since this one takes rvalue reference parameters.
  //
  // Also note that this overload has to be in namespace std only because
  // ADL cannot find it anywhere else.  If
  // zip_iterator::reference/std::tuple's template parameters were not
  // builtins, this overload could be in whatever namespace those template
  // parameters were declared in.
  template<typename... Ts>
  void swap(std::tuple<Ts&...>&& lhs, std::tuple<Ts&...>&& rhs)
  {
    using std::swap;
    otto::util::for_each(otto::util::zip(lhs, rhs), [](auto&& pair) { swap(pair.first, pair.second); });
  }

} // namespace std
