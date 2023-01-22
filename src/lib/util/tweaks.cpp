#include "tweaks.hpp"

namespace otto::util {
  namespace tweak_details {
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    util::shared_mutex<std::unordered_map<util::string_ref, std::any>> tweaks;
  } // namespace tweak_details
} // namespace otto::util
