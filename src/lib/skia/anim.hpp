#pragma once

#include <choreograph/Choreograph.h>

#include "app/services/graphics.hpp"

namespace otto::skia {

  template<typename T>
  struct Anim {
    Anim(T value, double seconds = 0.25) : timeline_(graphics->timeline()), output_(value), seconds_(seconds) {}

    Anim& operator=(T t)
    {
      timeline_.apply(&output_).template then<choreograph::RampTo>(t, seconds_);
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

    operator choreograph::Output<T> &()
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
    [[no_unique_address]] core::ServiceAccessor<services::Graphics> graphics;
    choreograph::Timeline& timeline_;
    choreograph::Output<T> output_;
    double seconds_;
  };

  template<typename T>
  struct ReturnTo {
    ReturnTo(T base_value, double hold_seconds = 1.0, double anim_seconds = 0.2)
      : timeline_(graphics->timeline()), output_(base_value), base_value_(base_value), hold_seconds_(hold_seconds), anim_seconds_(anim_seconds)
    {}

    ReturnTo& operator=(T t)
    {
      timeline_.apply(&output_)
        .template then<choreograph::RampTo>(t, anim_seconds_)
        .template then<choreograph::Hold>(t, hold_seconds_)
        .template then<choreograph::RampTo>(base_value_, anim_seconds_);
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

    operator choreograph::Output<T> &()
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
    [[no_unique_address]] core::ServiceAccessor<services::Graphics> graphics;
    choreograph::Timeline& timeline_;
    choreograph::Output<T> output_;
    T base_value_;
    double hold_seconds_;
    double anim_seconds_;
  };

} // namespace otto::skia
