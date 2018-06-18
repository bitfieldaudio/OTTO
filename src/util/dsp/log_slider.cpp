#include <cmath>
#include "log_slider.hpp"
namespace otto::util::dsp {
  /**
    BELOW IS THE CORE DEAL OF THE LOGARITHMIC SLIDER

    x: proportion          (0)  |-----------|(1)
    y: value        (min_value)  |-----------|(max_value)


    To get a logarithmic scale, we have to solve the following:
    y = a * exp(b * x)

    (x1;y1) = (0;min_value)
    (x2;y2) = (1;max_value)

    B and A have to be computed every time min_value or max_value are changed.

    b = (log(y2/y1)) / (x2 - x1)
    a = y1 / (exp(b * x1)) OR a = y2 / (exp(b * x2))

    So in our case,
    b = log(max_value/min_value)
    a = min_value
  */
  void LogSlider::update_log_coefficients()
  {
      a = min_value;
      b = std::log(max_value / min_value);
  }

  // TODO: optimize with exp / log approximations
  double LogSlider::proportion_of_length_to_value(double proportion) noexcept
  {
      double value = a * std::exp(b * proportion);
      return value;
  }
  double LogSlider::value_to_proportion_of_length(double value) noexcept
  {
      double proportion = std::log(value / a) / b;
      return proportion;
  }

  void LogSlider::set_range(double new_minimum, double new_maximum)
  {
      min_value = new_minimum;
      max_value = new_maximum;
      update_log_coefficients();
  }

}
