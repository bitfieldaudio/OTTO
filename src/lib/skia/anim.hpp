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
    [[no_unique_address]] core::ServiceAccessor<services::Graphics> graphics;
    choreograph::Timeline& timeline_;
    choreograph::Output<T> output_;
    double seconds_;
  };

} // namespace otto::skia
