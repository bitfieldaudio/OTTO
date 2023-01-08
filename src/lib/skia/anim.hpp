#pragma once

#include <choreograph/Choreograph.h>

#include "app/services/graphics.hpp"

namespace otto::skia {

  template<typename T>
  struct Anim : GraphicsDomain {
    Anim(T value, double seconds = 0.25) : output_(value), seconds_(seconds) {}

    Anim& operator=(T t)
    {
      timeline().apply(&output_).template then<choreograph::RampTo>(t, seconds_);
      return *this;
    }

    operator T() const noexcept
    {
      return output_.value();
    }

    T operator*() const noexcept
    {
      return output_.value();
    }

    operator choreograph::Output<T>&()
    {
      return output_;
    }

    auto& output() noexcept
    {
      return output_;
    }

    T value() const noexcept
    {
      return output_.value();
    }
    
    T target() const noexcept
    {
      return output_.endValue();
    }
    
    /// Start new animation if not already animating to the given target value
    void set_target(T target) noexcept {
      if (target != this->target()) {
        *this = target;
      }
    }

  private:
    choreograph::Output<T> output_;
    double seconds_;
  };


  template<typename T>
  struct ReturnTo : GraphicsDomain {
    ReturnTo(T base_value, double anim_seconds, double hold_seconds)
    {
      ReturnTo(base_value, anim_seconds, hold_seconds, anim_seconds);
    }

    ReturnTo(T base_value, double anim_seconds_1, double hold_seconds, double anim_seconds_2)
      : output_(base_value),
        base_value_(base_value),
        hold_seconds_(hold_seconds),
        anim_seconds_1(anim_seconds_1),
        anim_seconds_2(anim_seconds_2)
    {}

    ReturnTo& operator=(T t)
    {
      timeline()
        .apply(&output_)
        .template then<choreograph::RampTo>(t, anim_seconds_1)
        .template then<choreograph::Hold>(t, hold_seconds_)
        .template then<choreograph::RampTo>(base_value_, anim_seconds_2);
      return *this;
    }

    operator T() const noexcept
    {
      return output_.value();
    }

    T operator*() const noexcept
    {
      return output_.value();
    }

    operator choreograph::Output<T>&()
    {
      return output_;
    }

    auto& output() noexcept
    {
      return output_;
    }

    T value() const noexcept
    {
      return output_.value();
    }

  private:
    choreograph::Output<T> output_;
    T base_value_;
    double hold_seconds_;
    double anim_seconds_1;
    double anim_seconds_2;
  };

  template<typename T>
  struct KeyValueFade : GraphicsDomain {
    KeyValueFade(double fade_in_time, double hold_time, double fade_back_time)
      : key_(ReturnTo<T>{0, fade_in_time, hold_time + fade_back_time, fade_back_time}),
        value_(ReturnTo<T>{1, fade_in_time, hold_time, fade_back_time})
    {}

    void trigger() noexcept
    {
      key_ = 1;
      value_ = 0;
    }

    T key() const noexcept
    {
      return key_.value();
    }
    T value() const noexcept
    {
      return value_.value();
    }

  private:
    ReturnTo<T> key_;
    ReturnTo<T> value_;
  };

} // namespace otto::skia
