#pragma once

#include <algorithm>
#include <ranges>

#include <boost/stl_interfaces/iterator_interface.hpp>
#include <boost/stl_interfaces/view_interface.hpp>

#include "lib/util/concepts.hpp"

namespace otto::util {

  template<std::ranges::view Range, util::callable<bool(std::ranges::range_reference_t<Range>)> Callable>
  struct filter_view : boost::stl_interfaces::v1::view_interface<filter_view<Range, Callable>>, std::ranges::view_base {
    using BaseIter = std::ranges::iterator_t<Range>;
    struct sentinel_t {};
    struct iterator_t : boost::stl_interfaces::iterator_interface<iterator_t,
                                                                  std::forward_iterator_tag,
                                                                  std::iter_value_t<BaseIter>,
                                                                  std::iter_reference_t<BaseIter>> {
      using value_type = std::iter_value_t<BaseIter>;
      using reference = std::iter_reference_t<BaseIter>;

      constexpr iterator_t() = default;
      constexpr iterator_t(filter_view* parent, BaseIter iter) : parent_(parent), iter_(std::move(iter)) {}

      constexpr reference operator*() const noexcept
      {
        return *iter_;
      }
      constexpr iterator_t& operator++() noexcept
      {
        iter_ = std::find_if(++iter_, std::end(parent_->base_), std::ref(*parent_->callable_));
        return *this;
      }
      using boost::stl_interfaces::iterator_interface<iterator_t,
                                                      std::forward_iterator_tag,
                                                      std::iter_value_t<BaseIter>,
                                                      std::iter_reference_t<BaseIter>>::operator++;

      constexpr bool operator==(const iterator_t& other) const
      {
        return iter_ == other.iter_;
      }
      constexpr bool operator==(const sentinel_t& s) const
      {
        return iter_ == std::end(parent_->base_);
      }

    private:
      filter_view* parent_ = nullptr;
      BaseIter iter_;
    };

    filter_view() = default;

    filter_view(Range base, Callable callable)
      : base_(base), callable_(std::move(callable)), cached_begin_(std::ranges::find_if(base_, std::ref(*callable_)))
    {}

    Range& base() const
    {
      return base_;
    }

    constexpr auto begin()
    {
      return iterator_t(this, cached_begin_);
    }

    constexpr auto end()
    {
      if constexpr (std::ranges::common_range<Range>) {
        return iterator_t(this, std::end(base_));
      } else {
        return sentinel_t();
      }
    }

  private:
    Range base_;
    std::optional<Callable> callable_;
    BaseIter cached_begin_;
  };

  template<std::ranges::viewable_range Range, std::predicate<std::ranges::range_reference_t<Range>> Pred>
  auto filter(Range&& r, Pred&& p)
  {
    return filter_view(all(FWD(r)), FWD(p));
  }

} // namespace otto::util
