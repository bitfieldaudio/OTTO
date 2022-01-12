#pragma once

#include <algorithm>
#include <ranges>

#include <boost/stl_interfaces/iterator_interface.hpp>
#include <boost/stl_interfaces/view_interface.hpp>

#include "lib/util/concepts.hpp"

namespace otto::util {

  template<typename Derived,
           typename BaseIter,
           typename Category = typename std::iterator_traits<BaseIter>::iterator_category,
           typename ValueType = std::iter_value_t<BaseIter>,
           typename Reference = std::iter_reference_t<BaseIter>>
  using iterator_adaptor = boost::stl_interfaces::iterator_interface<Derived, Category, ValueType, Reference>;

  template<std::ranges::view Range, std::invocable<std::ranges::range_reference_t<Range>> Callable>
  struct transform_view : boost::stl_interfaces::v1::view_interface<transform_view<Range, Callable>>,
                          std::ranges::view_base {
    using BaseIter = std::ranges::iterator_t<Range>;
    struct sentinel_t {};
    struct iterator_t : iterator_adaptor<iterator_t, BaseIter> {
      using reference = std::invoke_result_t<Callable, std::iter_reference_t<BaseIter>>;
      using value_type = std::remove_reference_t<reference>;

      constexpr iterator_t() = default;
      constexpr iterator_t(transform_view* parent, BaseIter iter) : parent_(parent), iter_(std::move(iter)) {}

      constexpr reference operator*() const noexcept
      {
        return std::invoke(*parent_->callable_, *iter_);
      }
      constexpr iterator_t& operator++() noexcept
      {
        iter_++;
        return *this;
      }
      using iterator_adaptor<iterator_t, BaseIter>::operator++;

      constexpr iterator_t& operator--() noexcept requires std::ranges::bidirectional_range<Range>
      {
        iter_--;
        return *this;
      }
      using iterator_adaptor<iterator_t, BaseIter>::operator--;

      constexpr bool operator==(const iterator_t& other) const
      {
        return iter_ == other.iter_;
      }

      constexpr bool operator==(const sentinel_t&) const
      {
        return iter_ == std::end(parent_->base_);
      }

      constexpr auto operator-(const iterator_t& rhs) const //
        requires std::ranges::random_access_range<Range>
      {
        return iter_ - rhs.iter_;
      }

      constexpr auto operator+=(std::size_t n) //
        requires std::ranges::random_access_range<Range>
      {
        return iter_ += n;
      }

    private : transform_view* parent_ = nullptr;
      BaseIter iter_;
    };

    transform_view(Range base, Callable callable) : base_(base), callable_(callable) {}

    Range& base() const
    {
      return base_;
    }

    constexpr auto begin()
    {
      return iterator_t(this, std::begin(base_));
    }

    constexpr auto end()
    {
      if constexpr (std::ranges::common_range<Range>) {
        return iterator_t(this, std::end(base_));
      } else {
        return sentinel_t();
      }
    }

    constexpr auto size() //
      requires std::ranges::sized_range<Range>
    {
      return base_.size();
    }

    constexpr auto size() const //
      requires std::ranges::sized_range<const Range>
    {
      return base_.size();
    }

  private : Range base_;
    std::optional<Callable> callable_;
  };

  template<std::ranges::viewable_range Range, std::invocable<std::ranges::range_reference_t<Range>> Func>
  auto transform(Range&& r, Func&& p)
  {
    return transform_view(all(FWD(r)), FWD(p));
  }

} // namespace otto::util
