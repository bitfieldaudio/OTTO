#pragma once
#include <tl/optional.hpp>

#include "lib/util/utility.hpp"
namespace otto::util {

  template<std::regular T>
  struct change_checker {
    change_checker() = default;

    bool check_changed(const T& new_val)
    {
      bool res = !old_val_.has_value() || *old_val_ != new_val;
      old_val_ = new_val;
      return res;
    }

    const tl::optional<T>& old_val() const
    {
      return old_val_;
    }

  private:
    tl::optional<T> old_val_ = tl::nullopt;
  };
} // namespace otto::util
