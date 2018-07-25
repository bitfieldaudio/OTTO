#pragma once

#include <chrono>
#include <deque>

namespace otto::core::ui::animation {

  namespace chrono = std::chrono;

  template<typename _Timeline>
  struct AnimationBase {
    using timeline_t = _Timeline;
    using duration_t = typename timeline_t::duration_t;
    using time_point_t = typename timeline_t::time_point_t;

    AnimationBase(timeline_t& tml) noexcept : _timeline(tml) {}

    virtual void update(time_point_t t) = 0;
    virtual auto length() -> duration_t = 0;

  protected:
    timeline_t& _timeline;
  };

  template<typename _Val, typename _Timeline, typename... Procedures>
  struct Animation : AnimationBase<_Timeline> {
    using Base = AnimationBase<_Timeline>;
    using value_type = _Val;
    using timeline_t = typename Base::timeline_t;
    using duration_t = typename Base::duration_t;
    using time_point_t = typename Base::time_point_t;

    template<typename callable_t>
    constexpr static bool is_procedure_v =
      std::is_invocable_r_v<callable_t, bool(value_type&, time_point_t)>;

    template<typename callable_t>
    constexpr static bool is_procedure_maker_v =
      is_procedure_v<std::decay_t<std::invoke_result_t<callable_t, Animation&>>>;

    Animation(value_type& v, timeline_t& tl) : _value(v), Base(tl) {}

    template<typename ProcedureMaker>
    auto then(ProcedureMaker&& proc) -> std::enable_if_t<
      is_procedure_maker_v<ProcedureMaker>,
      Animation<value_type, timeline_t, Procedures..., std::decay_t<decltype(proc(*this))>>>;

    template<typename ProcedureMaker>
    auto replace(ProcedureMaker&& proc)
      -> std::enable_if_t<is_procedure_maker_v<ProcedureMaker>,
                          Animation<value_type, timeline_t, std::decay_t<decltype(proc(*this))>>>;

    auto timeline() noexcept -> timeline_t&;

    auto value() noexcept -> value_type&;

  private:
    value_type* _value;
  };

  template<typename Clock = chrono::steady_clock, typename Duration = chrono::milliseconds>
  struct Timeline {
    using clock_t = Clock;
    using duration_t = Duration;
    using time_point_t = chrono::time_point<Clock, Duration>;

    auto now() -> time_point_t;

    /// Start the timeline.
    void start();

    template<typename T>
    auto push(T& val) -> Animation<T, Timeline>&;

  private:
    time_point_t epoch;
    std::deque<AnimationBase<Timeline>> animations;
  };

  namespace detail {
    template<typename FuncRef, typename TimePoint, typename Duration>
    auto apply_time_mod(FuncRef&& func, TimePoint t, TimePoint begin, Duration duration)
      -> TimePoint
    {
      float f = (t - begin).count() / duration.count();
      return begin + Duration{func(f) * duration.count()};
    }

    template<typename FuncRef, typename TimePoint>
    auto apply_time_mod(FuncRef&& func, TimePoint t, TimePoint begin, TimePoint end) -> TimePoint
    {
      return apply_time_mod(func, t, begin, end - begin);
    }
  } // namespace detail

  inline namespace time_mods {
    auto ease_in_out(float x) noexcept -> float
    {
      return x * x * x - 3 * (x - 1) * x * x;
    }

  } // namespace time_mods

  /// Procedures
  inline namespace procs {
    template<typename ValueRef>
    auto set(ValueRef&& v)
    {
      using value_type = std::decay_t<ValueRef>;

      return [v = std::forward<ValueRef>(v)](auto& animation) {
        return [v = std::forward<ValueRef>(v)](value_type& ref, auto time) {
          ref = std::forward<ValueRef>(v);
          return true;
        };
      };
    }

    template<typename Duration>
    auto wait(Duration d)
    {
      return [d](auto& animation) {
        return
          [end = animation.timeline().now()](const auto& ref, auto time) { return time >= end; };
      };
    }

    template<typename Value, typename Duration, typename TimeModifier>
    auto ramp(Value length, Duration dur, TimeModifier tmod)
    {
      return [=](auto& animation) {
        return [=, begin = animation.timeline().now(), init = animation.value()](const auto& ref,
                                                                                 auto time) {
          float f = (time - begin).count() / dur.count();
          f = tmod(f);
          ref = init + f * length;
        };
      };
    }

    template<typename Value, typename Duration, typename TimeModifier>
    auto ramp_to(Value target, Duration dur, TimeModifier tmod)
    {
      return
        [=](auto& animation) { return ramp(target - animation.value(), dur, tmod)(animation); };
    }
  } // namespace procs

} // namespace otto::core::ui::animation
