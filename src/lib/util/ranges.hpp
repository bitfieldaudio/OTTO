#pragma once
#include "lib/util/ranges/all_view.hpp"
#include "lib/util/ranges/filter_view.hpp"
#include "lib/util/ranges/reverse_view.hpp"
#include "lib/util/ranges/transform_view.hpp"
#include "lib/util/ranges/zip_view.hpp"

namespace stdr = std::ranges;

namespace otto::util {
  template<std::ranges::viewable_range Range, std::invocable<std::ranges::range_reference_t<Range>> Func>
  auto filter_transform(Range&& r, Func&& p)
  {
    auto transf = transform(FWD(r), FWD(p));
    auto filt = filter(all(transf), [](auto&& opt) { return opt.has_value(); });
    return transform(all(filt), [](auto&& opt) -> decltype(auto) { return FWD(opt).value(); });
  }

  auto equal_range(auto& map, auto&& key)
  {
    auto [b, e] = map.equal_range(FWD(key));
    return subrange(b, e);
  }
} // namespace otto::util
