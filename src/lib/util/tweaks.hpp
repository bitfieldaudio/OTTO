
#include <any>
#include <unordered_map>

#include "lib/util/mutex.hpp"
#include "lib/util/string_ref.hpp"

namespace otto::util {

#ifdef OTTO_TWEAKS_ENABLED
  constexpr bool tweaks_enabled = true;
#else
  constexpr bool tweaks_enabled = false;
#endif

  namespace tweak_details {
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
    extern util::shared_mutex<std::unordered_map<util::string_ref, std::any>> tweaks;
  } // namespace tweak_details

  template<std::copy_constructible T>
  void set_tweak(util::string_ref name, T value)
  {
    if constexpr (tweaks_enabled) {
      auto tweaks = tweak_details::tweaks.lock();
      tweaks->insert_or_assign(name, std::any(value));
    }
  }

  inline tl::optional<std::any> get_tweak_any(util::string_ref key)
  {
    if constexpr (tweaks_enabled) {
      auto tweaks = tweak_details::tweaks.lock_shared();
      if (auto found = tweaks->find(key); found != tweaks->end()) {
        return found->second;
      }
    }
    return tl::nullopt;
  }


  /// A value that can be tweaked at runtime to help experiment with various parameters during development
  ///
  /// Usage:
  /// ```cpp
  /// ctx.lineTo({0.0, tweak("test_line_y", 5.0f)});
  /// ```
  /// In builds with tweaks disabled (release builds), the default value will be returned, and the function should be
  /// inlined completely. In builds with tweaks enabled, the value will default to `5.0f`, and can be changed at runtime
  /// using `otto::util::set_tweak("test_line_y", 6.0f)`.
  template<std::copy_constructible T>
  inline T tweak(util::string_ref key, T default_value)
  {
    if constexpr (!tweaks_enabled) {
      return default_value;
    }

    if (auto res = get_tweak_any(key)) {
      return std::any_cast<T>(res.value());
    }
    set_tweak(key, default_value);
    return default_value;
  }
} // namespace otto::util
