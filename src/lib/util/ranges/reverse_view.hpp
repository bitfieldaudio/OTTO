#pragma once

#include <boost/stl_interfaces/view_interface.hpp>

#include "all_view.hpp"

namespace otto::util {

  template<std::ranges::view Range>
  requires std::ranges::bidirectional_range<Range> //
  struct reverse_view : public boost::stl_interfaces::v1::view_interface<reverse_view<Range>>, std::ranges::view_base {
    reverse_view() = default;
    reverse_view(Range base) : base_(std::move(base)) {}

    Range& base()
    {
      return base_;
    }

    constexpr auto begin()
    {
      return std::make_reverse_iterator(base_.end());
    }

    constexpr auto end()
    {
      return std::make_reverse_iterator(base_.begin());
    }

    constexpr auto begin() const
    {
      return std::make_reverse_iterator(base_.end());
    }

    constexpr auto end() const
    {
      return std::make_reverse_iterator(base_.begin());
    }

    constexpr auto size() //
      requires std::ranges::sized_range<Range>
    {
      return std::ranges::size(base_);
    }

    constexpr auto size() const //
      requires std::ranges::sized_range<const Range>
    {
      return std::ranges::size(base_);
    }

  private : Range base_;
  };

  template<std::ranges::range Range>
  reverse_view(Range&&) -> reverse_view<all_view<Range>>;

  inline constexpr auto reverse = []<std::ranges::viewable_range Range>(Range&& r) { //
    return reverse_view(all(FWD(r)));
  };

} // namespace otto::util
