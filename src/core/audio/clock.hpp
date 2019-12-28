#pragma once

#include "util/assert.hpp"

namespace otto::core::clock {

  using Time = unsigned int;
  /// Number of microsteps per beat, i.e. fourth of whole note.
  static constexpr Time microsteps = 192;

  /// Constants for manipulating time in beats
  namespace notes {
    inline constexpr const Time whole = 4 * microsteps;
    inline constexpr const Time half = whole / 2;
    inline constexpr const Time quarter = whole / 4;
    inline constexpr const Time quartertriplet = whole / 6;
    inline constexpr const Time eighth = whole / 8;
    inline constexpr const Time eighthtriplet = whole / 12;
    inline constexpr const Time sixteenth = whole / 16;
    inline constexpr const Time thirtysecond = whole / 32;
    inline constexpr const Time sixtyfourth = whole / 64;

    /// Alias to @ref quarter
    inline constexpr const Time beat = quarter;
  }; // namespace notes

  struct ClockRange {
    Time begin;
    Time end;

    /// The lowest time in this range
    operator Time() const
    {
      return time();
    }

    /// The lowest time in this range
    Time time() const
    {
      return begin;
    }

    /// Check whether this range contains a multiple of n
    ///
    /// @requires count > 0
    bool contains_multiple(Time n) const noexcept
    {
      return count_multiple(n) > 0;
    }

    bool contains_multiple(Time n, float offset) const noexcept
    {
      return count_multiple(n, offset) > 0;
    }

    /// Counts the number of times this range contains a multiple of n
    ///
    /// @requires count > 0
    int count_multiple(Time n) const noexcept
    {
      OTTO_ASSERT(n > 0);
      return (std::max(end, Time{1}) - 1) / n - (std::max(begin, Time{1}) - 1) / n;
    }

    int count_multiple(Time n, float offset) const noexcept
    {
      OTTO_ASSERT(n > 0);
      return (std::max(end - (Time)(n * offset), Time{1}) - 1) / n - (std::max(begin - (Time)(n * offset), Time{1}) - 1) / n;
    }

    int position_of_multiple(Time n) const noexcept
    {
      OTTO_ASSERT(n > 0);
      return begin / n;
    }
  };

  struct ClockCounter {

    ClockRange current() const noexcept{
      return current_;
    };

    ClockRange step(Time n) noexcept
    {
      return current_ = {current_.end, current_.end + n};
    }

    ClockRange jump(Time t) noexcept
    {
      return current_ = {t, t};
    }

    void reset() noexcept 
    {
      current_ = {0, 0};
    }

  private:
    ClockRange current_ = {0, 0};
  };

} // namespace otto::core::clock
