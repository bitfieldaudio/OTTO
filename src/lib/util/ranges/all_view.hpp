#pragma once

#include <ranges>

#include <boost/stl_interfaces/iterator_interface.hpp>
#include <boost/stl_interfaces/view_interface.hpp>

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
  struct subrange : boost::stl_interfaces::v1::view_interface<subrange<Iterator, Sentinel>>, std::ranges::view_base {
    subrange() = default;
    template<typename Range>
    constexpr subrange(Range&& r) : first_(std::begin(r)), last_(std::end(r))
    {}
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

  template<typename Range>
  subrange(Range&&) -> subrange<std::ranges::iterator_t<Range>, std::ranges::sentinel_t<Range>>;

  /// Get a view of a range
  ///
  /// If passed a view, returns a copy of that view. If passed a range, returns a `subrange` of that range
  template<typename Range>
  auto all(Range&& range)
  {
    if constexpr (std::ranges::view<Range>) {
      return FWD(range);
    } else {
      return subrange(FWD(range));
    }
  }

  /// A template alias that denotes the type of all(r) for some Range r.
  template<typename Range>
  using all_view = decltype(all(std::declval<Range>()));

  static_assert(std::ranges::view<all_view<std::array<int, 4>&>>);

  /// Python-style slicing of a range by start/end indexes.
  template<std::ranges::viewable_range Range>
  auto slice(Range&& r, std::ptrdiff_t start, std::ptrdiff_t end)
  {
    return subrange(start > 0 ? std::begin(r) + start : std::end(r) + start,
                    end > 0 ? std::begin(r) + end : std::end(r) + end);
  }
} // namespace otto::util

namespace std::ranges {
  template<typename Iterator, typename Sentinel>
  constexpr inline bool enable_borrowed_range<otto::util::subrange<Iterator, Sentinel>> = true;
}
