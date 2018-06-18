#include "log_slider.hpp"
#include <cmath>
namespace otto::util::dsp {
  LogSlider::LogSlider()
  {
  }
  LogSlider::~LogSlider()
  {
  }

  /*
    BELOW IS THE CORE DEAL OF THE LOGARITHMIC SLIDER

    x: proportion          (0)  |-----------|(1)
    y: value        (minValue)  |-----------|(maxValue)


    To get a logarithmic scale, we have to solve the following:
    y = a * exp(b * x)

    (x1;y1) = (0;minValue)
    (x2;y2) = (1;maxValue)

    B and A have to be computed every time minValue or maxValue are changed.

    b = (log(y2/y1)) / (x2 - x1)
    a = y1 / (exp(b * x1)) OR a = y2 / (exp(b * x2))

    So in our case,
    b = log(maxValue/minValue)
    a = minValue
  */
  void LogSlider::updateLogCoefficients()
  {
      a = minValue;
      b = log(maxValue / minValue);
  }

  // TODO: optimize with exp / log approximations
  double LogSlider::proportionOfLengthToValue(double proportion)
  {
      double value = a * exp(b * proportion);
      return value;
  }
  double LogSlider::valueToProportionOfLength(double value)
  {
      double proportion = log(value / a) / b;
      return proportion;
  }

  void LogSlider::setRange(double newMinimum, double newMaximum)
  {
      minValue = newMinimum;
      maxValue = newMaximum;
      updateLogCoefficients();
  }

}
