#pragma once

#include <boost/stl_interfaces/iterator_interface.hpp>
#include <boost/stl_interfaces/view_interface.hpp>
#include <ranges>

#include "lib/util/concepts.hpp"
#include "lib/util/utility.hpp"

namespace otto::util {
  /// A subrange is simply an iterator-sentinel pair.  This one is a bit simpler
  /// than the one in std::ranges; its missing a bunch of constructors, prev(),
  /// next(), and advance().
  ///
  /// This is needed because libstdc++ views are broken on clang until clang implements
  /// lazy concept evaluation: https://reviews.llvm.org/D60939
  template<typename Iterator, typename Sentinel>
  struct subrange : boost::stl_interfaces::view_interface<subrange<Iterator, Sentinel>>, std::ranges::view_base {
    subrange() = default;
    constexpr subrange(Iterator it, Sentinel s) : first_(it), last_(s) {}

    constexpr auto begin() const
    {
      return first_;
    }
    constexpr auto end() const
    {
      return last_;
    }

  private:
    Iterator first_;
    Sentinel last_;
  };

  /// Get a view of a range
  ///
  /// If passed a view, returns a copy of that view. If passed a range, returns a `subrange` of that range
  template<typename Range>
  auto all(Range&& range)
  {
    if constexpr (std::ranges::view<Range>) {
      return FWD(range);
    } else {
      return subrange<decltype(range.begin()), decltype(range.end())>(range.begin(), range.end());
    }
  }

  /// A template alias that denotes the type of all(r) for some Range r.
  template<typename Range>
  using all_view = decltype(all(std::declval<Range>()));

  static_assert(std::ranges::view<all_view<std::array<int, 4>&>>);
} // namespace otto::util
